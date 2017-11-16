#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<deque>
using namespace std;
typedef struct g{
    int goLeft, goRight;
    int goUp, goDown;
    int vis;
}GLOBAL;
GLOBAL global[12][12][6];
typedef struct p{
    int row, col, go, from;
}LOCAL;
LOCAL pre[12][12][6], toQ;
deque<LOCAL> Q;
int UP=0, DOWN=1, LEFT=2, RIGHT=3;
int ti, tj, flag, cnt;

void initialize(){
    Q.clear();
    flag = 0;
    cnt = 1;
    memset(global, 0, sizeof(global));
    memset(pre, -1, sizeof(pre));
}

int canGo(int row, int col, int dir){
    if(global[row][col][dir].goUp==1)return 1;
    if(global[row][col][dir].goDown==1)return 1;
    if(global[row][col][dir].goLeft==1)return 1;
    if(global[row][col][dir].goRight==1)return 1;
    return 0;
}

void assignPoint(int x, int y, char*str){
    int i, len = strlen(str);
    if(str[0]=='N'){
        for(i=1;i<len;i++){
            if(str[i]=='F') global[x][y][DOWN].goUp=1;
            else if(str[i]=='L')global[x][y][DOWN].goLeft=1;
            else if(str[i]=='R')global[x][y][DOWN].goRight=1;
        }
    }
    else if(str[0]=='S'){
        for(i=1;i<len;i++){
            if(str[i]=='F') global[x][y][UP].goDown=1;
            else if(str[i]=='L')global[x][y][UP].goRight=1;
            else if(str[i]=='R')global[x][y][UP].goLeft=1;
        }
    }
    else if(str[0]=='W'){
        for(i=1;i<len;i++){
            if(str[i]=='F') global[x][y][RIGHT].goLeft=1;
            else if(str[i]=='L')global[x][y][RIGHT].goDown=1;
            else if(str[i]=='R')global[x][y][RIGHT].goUp=1;
        }
    }
    else if(str[0]=='E'){
        for(i=1;i<len;i++){
            if(str[i]=='F') global[x][y][LEFT].goRight=1;
            else if(str[i]=='L')global[x][y][LEFT].goUp=1;
            else if(str[i]=='R')global[x][y][LEFT].goDown=1;
        }
    }
}

void enqueue(int si, int sj, int to){
    GLOBAL now;
    global[si][sj][to].vis = 1;
    now = global[si][sj][to];
    if(si==ti && sj==tj){
        flag = 1;
        return;
    }
    if(now.goUp){
        toQ.row = si, toQ.col = sj;
        toQ.from = to, toQ.go = UP;
        Q.push_back(toQ);
    }
    if(now.goDown){
        toQ.row = si, toQ.col = sj;
        toQ.from = to, toQ.go = DOWN;
        Q.push_back(toQ);
    }
    if(now.goLeft){
        toQ.row = si, toQ.col = sj;
        toQ.from = to, toQ.go = LEFT;
        Q.push_back(toQ);
    }
    if(now.goRight){
        toQ.row = si, toQ.col = sj;
        toQ.from = to, toQ.go = RIGHT;
        Q.push_back(toQ);
    }
}

void BFS(int si, int sj, char dir){
    LOCAL now;

    if(dir=='E'){
        enqueue(si, sj+1, LEFT);
        pre[si][sj+1][LEFT].row = si;
        pre[si][sj+1][LEFT].col = sj;
        pre[si][sj+1][LEFT].from = -2;
    }
    else if(dir=='W'){
        enqueue(si, sj-1, RIGHT);
        pre[si][sj-1][RIGHT].row = si;
        pre[si][sj-1][RIGHT].col = sj;
        pre[si][sj-1][RIGHT].from = -2;
    }
    else if(dir=='S'){
        enqueue(si+1, sj, UP);
        pre[si+1][sj][UP].row = si;
        pre[si+1][sj][UP].col = sj;
        pre[si+1][sj][UP].from = -2;
    }
    else if(dir=='N'){
        enqueue(si-1, sj, DOWN);
        pre[si-1][sj][DOWN].row = si;
        pre[si-1][sj][DOWN].col = sj;
        pre[si-1][sj][DOWN].from = -2;
    }

    while(!Q.empty()){
        now = Q.front(); Q.pop_front();
        if(now.go==UP && canGo(now.row-1, now.col, DOWN) && global[now.row-1][now.col][DOWN].vis==0){
            enqueue(now.row-1, now.col, DOWN);
            pre[now.row-1][now.col][DOWN].row = now.row;
            pre[now.row-1][now.col][DOWN].col = now.col;
            pre[now.row-1][now.col][DOWN].from = now.from;
        }
        if(now.go==DOWN && canGo(now.row+1, now.col, UP) && global[now.row+1][now.col][UP].vis==0){
            enqueue(now.row+1, now.col, UP);
            pre[now.row+1][now.col][UP].row = now.row;
            pre[now.row+1][now.col][UP].col = now.col;
            pre[now.row+1][now.col][UP].from = now.from;
        }
        if(now.go==LEFT && canGo(now.row, now.col-1, RIGHT) && global[now.row][now.col-1][RIGHT].vis==0){
            enqueue(now.row, now.col-1, RIGHT);
            pre[now.row][now.col-1][RIGHT].row = now.row;
            pre[now.row][now.col-1][RIGHT].col = now.col;
            pre[now.row][now.col-1][RIGHT].from = now.from;
        }
        if(now.go==RIGHT && canGo(now.row, now.col+1, LEFT) && global[now.row][now.col+1][LEFT].vis==0){
            enqueue(now.row, now.col+1, LEFT);
            pre[now.row][now.col+1][LEFT].row = now.row;
            pre[now.row][now.col+1][LEFT].col = now.col;
            pre[now.row][now.col+1][LEFT].from = now.from;
        }
        if(flag==1) break;
    }
}

void printAns(int i, int j, int dir){
    if(dir==-2){
        printf("  (%d,%d)", i, j);
        return;
    }
    printAns(pre[i][j][dir].row, pre[i][j][dir].col, pre[i][j][dir].from);
    if(cnt%10==0) printf("  (%d,%d)", i, j);
    else if(cnt%10==9) printf(" (%d,%d)\n", i, j);
    else printf(" (%d,%d)", i, j);
    cnt++;
}

int main(){
    int i, j;
    int si, sj;
    char name[22], tmp[10], dir;

    while(scanf("%s", name) && strcmp(name, "END")){
        scanf("%d%d%s%d%d", &si, &sj, tmp, &ti, &tj);
        dir = tmp[0];
        initialize();
        while(scanf("%d", &i)==1 && i){
            scanf("%d", &j);
            while(scanf("%s", tmp) && tmp[0]!='*'){
                assignPoint(i, j, tmp);
            }
        }
        for(i=0;i<4;i++){
            global[ti][tj][i].goUp = 1;
            global[ti][tj][i].goDown = 1;
            global[ti][tj][i].goLeft = 1;
            global[ti][tj][i].goRight = 1;
        }

        BFS(si, sj, dir);

        printf("%s\n", name);
        if(flag){
            for(i=0;i<4;i++)
                if(pre[ti][tj][i].from!=-1) break;
            printAns(ti, tj, i);
            if(cnt%10!=0) printf("\n");
        }
        else printf("  No Solution Possible\n");

    }
    return 0;
}
