#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;

int board[5][5];
int result[5][5] = {
    {1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1},
    {0, 0,-1, 1, 1},
    {0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0}
};

int move[8][2] = {
    {1, 2},
    {2, 1},
    {2, -1},
    {1,-2},
    {-1, -2},
    {-2, -1},
    {-2, 1},
    {-1, 2}
};

int ans;

void initialize(){
    memset(board, 0, sizeof(board));
    ans = 12;
}

int check(){
    int i, j;
    for(i=0;i<5;i++)
        for(j=0;j<5;j++)
            if(board[i][j]!=result[i][j])
                return 0;
    return 1;
}

void DFS(int row, int col, int step){
    int i, nextRow, nextCol;
    if(step>10)return;
    if(check()){
        ans = (ans<step)?ans:step;
        return;
    }

    for(i=0;i<8;i++){
        nextRow = row+move[i][0];
        nextCol = col+move[i][1];
        if(nextRow>=0 && nextRow<5 && nextCol>=0 && nextCol<5){
            board[row][col] = board[nextRow][nextCol];
            board[nextRow][nextCol] = -1;
            DFS(nextRow, nextCol, step+1);
            board[nextRow][nextCol] = board[row][col];
            board[row][col] = -1;
        }
    }
}

int main(){
    int T, i, j, row, col;
    char c;

    scanf("%d%*c", &T);
    while(T--){
        initialize();
        for(i=0;i<5;i++){
            for(j=0;j<5;j++){
                if(j<4) scanf("%c", &c);
                else scanf("%c%*c", &c);
                if(c==' '){
                    row = i, col = j;
                    board[i][j] = -1;
                }
                else board[i][j] = c-'0';
            }
        }
        DFS(row, col, 0);

        if(ans>10) printf("Unsolvable in less than 11 move(s).\n");
        else printf("Solvable in %d move(s).\n", ans);
    }
    return 0;
}
