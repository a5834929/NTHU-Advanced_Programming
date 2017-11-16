#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
char map[110][110];

void DFS(int row, int col, int N){
    map[row][col] = '.';
    if(row+1<=N-1 && (map[row+1][col]=='x' || map[row+1][col]=='@')) DFS(row+1, col, N);
    if(col+1<=N-1 && (map[row][col+1]=='x' || map[row][col+1]=='@')) DFS(row, col+1, N);
    return;
}

int main(){
    int I, T, N, i, j;
    int cnt;

    scanf("%d", &T);
    for(I=1;I<=T;I++){
        cnt = 0;
        scanf("%d", &N);
        for(i=0;i<N;i++)
            scanf("%s", map[i]);
        for(i=0;i<N;i++){
            for(j=0;j<N;j++){
                if(map[i][j]=='x'){
                    DFS(i, j, N);
                    cnt++;
                }
            }
        }
        printf("Case %d: %d\n", I, cnt);
    }

    return 0;
}
