#include<cstdio>
#include<cstring>
int t = 1, row, column;
int panel[5][5], mask[9][2], m;
int state[5][5], path[30], minCnt;
int ans[30], found;

void initialize(){
    m = found = 0;
    minCnt = 2147483647;
    memset(panel, 0, sizeof(panel));
    memset(mask, 0, sizeof(mask));
    memset(state, 0, sizeof(state));
    memset(path, 0, sizeof(path));
    memset(ans, 0, sizeof(ans));
}

int checkPanel(){
    int i, j;
    for(i=0;i<row;i++)
        for(j=0;j<column;j++)
            if(panel[i][j]==0)
                return 0;

    found = 1;
    return 1;
}

int Bound(int r){
    int j;
    for(j = 0;j<column;j++)
        if(panel[r-2][j] == 0)
            return 1;
    return 0;
}

void changePanel(int r, int c){
    int i, pr, pc;
    for(i=0;i<m;i++){
        pr = r+mask[i][0];
        pc = c+mask[i][1];
        if(pr>=0 && pr<row && pc>=0 && pc<column)
            panel[pr][pc] = 1-panel[pr][pc];
    }
}

void DFS(int r, int c, int cnt){
    int i;
    if(c==column){
        r++, c = 0;
    }
    if(r==row){
        if(minCnt>cnt && checkPanel()==1){
            minCnt = cnt;
            for(i=0;i<cnt;i++)
                ans[i] = path[i];
        }
        return;
    }
    if(r>=2 && Bound(r)) return;

    state[r][c] = 0;
    DFS(r, c+1, cnt);

    state[r][c] = 1;
    changePanel(r, c);
    path[cnt] = r*column+c+1;
    DFS(r, c+1, cnt+1);

    changePanel(r, c);
    state[r][c] = 0;
}

int main(){
    int i, j;
    char ch[5];

    while(scanf("%d%d", &row, &column)!=EOF && row*column){
        initialize();
        for(i=0;i<3;i++){
            scanf("%s", ch);
            for(j=0;j<3;j++){
                if(ch[j]=='*'){
                    mask[m][0] = i-1;
                    mask[m++][1] = j-1;
                }
            }
        }
        DFS(0, 0, 0);
        printf("Case #%d\n", t++);
        if(found){
            printf("%d", ans[0]);
            for(i=1;i<minCnt;i++)
                printf(" %d", ans[i]);
            printf("\n");
        }
        else printf("Impossible.\n");
    }

    return 0;
}
