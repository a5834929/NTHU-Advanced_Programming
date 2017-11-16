#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cctype>
using namespace std;
char map[600][600];
int t = 1, x, y, cnt, n;
typedef struct A{
    char ch;
    int num;
}ANS;
ANS ans[600];

int cmp(const void*p, const void*q){
    ANS a=*(ANS*)p, b=*(ANS*)q;
    if(a.num>b.num) return -1;
    else if(a.num<b.num)return 1;
    else return (a.ch<b.ch)?-1:1;
}

void DFS(char hole, int row, int col){
    map[row][col] = '.';
    cnt++;
    if(row+1<x && map[row+1][col]==hole) DFS(hole, row+1, col);
    if(row-1>=0 && map[row-1][col]==hole) DFS(hole, row-1, col);
    if(col+1<y && map[row][col+1]==hole) DFS(hole, row, col+1);
    if(col-1>=0 && map[row][col-1]==hole) DFS(hole, row, col-1);
    ans[n].ch = hole;
    ans[n].num = (cnt>ans[n].num)?cnt:ans[n].num;
}

int main(){
    int i, j;

    while(scanf("%d%d", &x, &y)!=EOF && x*y){
        memset(ans, 0, sizeof(ans));
        n = 0;
        for(i=0;i<x;i++)
            scanf("%s", map[i]);
        for(i=0;i<x;i++){
            for(j=0;j<y;j++){
                if(isalpha(map[i][j])){
                    cnt = 0;
                    DFS(map[i][j], i, j);
                    n++;
                }
            }
        }
        qsort(ans, n, sizeof(ANS), cmp);
        printf("Problem %d:\n", t++);
        for(i=0;i<n;i++){
            if(ans[i].num==0) break;
            printf("%c %d\n", ans[i].ch, ans[i].num);
        }
    }

    return 0;
}

