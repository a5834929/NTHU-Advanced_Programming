#include<stdio.h>
#include<string.h>
char map[200][200];

int main(){
    int I, N, i, j, len;
    int now, up, low;
    char str[60];

    scanf("%d", &N);
    for(I=1;I<=N;I++){
        for(i=0;i<200;i++)
            for(j=0;j<200;j++)map[i][j] = ' ';
        scanf("%s", str);
        len = strlen(str);
        now = 100;
        up = 0; low = 1000;
        for(i=0;i<len;i++){
            if(str[i]=='R')
                map[now--][i+1] = '/';
            else if(str[i]=='F'){
                now++;
                map[now][i+1] = '\\';
            }
            else map[now][i+1] = '_';
            up = (up>now)?up:now;
            low = (low<now)?low:now;
        }
        printf("Case #%d:\n", I);
        for(i=low;i<=up+1;i++){
            for(j=199;j>=0;j--)
                if(map[i][j]!=' ')break;
            if(j>0){
                printf("|");
                map[i][j+1] = '\0';
                printf("%s", map[i]);
                printf("\n");
            }
        }
        printf("+-");
        for(i=0;i<=len;i++)printf("-");
        printf("\n\n");
    }
    return 0;
}
