#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
int board[8][8], able[100][8], tmp[8];
int column[8], left[15], right[15];
int aNum = 0, ans;

void initialize(){
    memset(tmp, 0, sizeof(tmp));
    memset(column, 0, sizeof(column));
    memset(left, 0, sizeof(left));
    memset(right, 0, sizeof(right));
}

void DFS(int row){
    int i, col;
    int lt, rt;
    if(row==8){
        for(i=0;i<8;i++)
            able[aNum][i] = tmp[i];
        aNum++;
        return;
    }

    for(col=0;col<8;col++){
        lt = (col-row)+7;
        rt = col+row;
        if(!column[col] && !left[lt] && !right[rt]){
            column[col] = left[lt] = right[rt] = 1;
            tmp[row] = col;
            DFS(row+1);
            column[col] = left[lt] = right[rt] = 0;
        }
    }
}

int main(){
    int k, i, j, sum;

    initialize();
    DFS(0);

    scanf("%d", &k);
    while(k--){
        ans = -1;
        for(i=0;i<8;i++)
            for(j=0;j<8;j++)
                scanf("%d", &board[i][j]);

        for(i=0;i<aNum;i++){
            sum = 0;
            for(j=0;j<8;j++)
                sum += board[j][able[i][j]];
            ans = max(ans, sum);
        }
        printf("%5d\n", ans);
    }
    return 0;
}
