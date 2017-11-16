#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int W, B[60], prul[60][30], profit[60][30], pmax[60];
int buy[60][30], buyn[60], sum[1000], tmp[1000];

int cmp(const void*p, const void*q){
    int a=*(int *)p, b=*(int *)q;
    return  a-b;
}

int SORT(int len){
    int i, len2=1;
    qsort(tmp, len, sizeof(int), cmp);
    sum[0]=tmp[0];
    for(i=1;i<len;i++){
        if(tmp[i]!=tmp[i-1] && len2<10)
            sum[len2++]=tmp[i];
    }
    return len2;
}

void initial(void){
    memset(B, 0, sizeof(int));
    memset(prul, 0, sizeof(int));
    memset(profit, 0, sizeof(int));
    memset(buyn, 0, sizeof(int));
    memset(buy, 0, sizeof(int));
    memset(sum, 0, sizeof(int));
    memset(tmp, 0, sizeof(int));
}

int main(){
    int i, j, k, total=0, nzero[60];
    int sumn, tmpn, nzeron, ansmax;

    scanf("%d", &W);
    while(W){
        ansmax=0;
        initial();
        for(i=1;i<=W;i++){
            buyn[i]=0;
            scanf("%d", &B[i]);
            pmax[i]=0;
            nzero[i]=0;

            for(j=1;j<=B[i];j++){
                scanf("%d", &prul[i][j]);
                profit[i][j]=profit[i][j-1]+(10-prul[i][j]);
                pmax[i]=(pmax[i]>profit[i][j])?pmax[i]:profit[i][j];
                pmax[i]=(pmax[i]>0)?pmax[i]:0;
            }
        }
        nzeron=0;
        for(i=1;i<=W;i++){
            for(j=0;j<=B[i];j++)
                if(profit[i][j]==pmax[i])
                    buy[i][buyn[i]++]=j;
            if(buyn[i]!=0)  nzero[nzeron++]=i;
            ansmax+=pmax[i];
        }

        if(nzeron>1){
            tmpn=0;
            for(i=0;i<buyn[nzero[0]];i++)
                for(j=0;j<buyn[nzero[1]];j++)
                    tmp[tmpn++]=buy[nzero[0]][i]+buy[nzero[1]][j];
            sumn=SORT(tmpn);
            i=2;
            while(i<nzeron){
                tmpn=0;
                for(j=0;j<sumn;j++)
                    for(k=0;k<buyn[nzero[i]];k++)
                        tmp[tmpn++]=sum[j]+buy[nzero[i]][k];
                sumn=SORT(tmpn);
                i++;
            }
        }
        total++;
        printf("Workyards %d\n", total);
        printf("Maximum profit is %d.\n", ansmax);
        printf("Number of pruls to buy:");
        ansmax=0;
        if(nzeron==1) for(i=0;i<buyn[nzero[0]];i++) printf(" %d", buy[nzero[0]][i]);
        else for(i=0;i<sumn && i<10;i++) printf(" %d", sum[i]);
        printf("\n");
        if(scanf("%d", &W)!=EOF && W) printf("\n");
        else break;
    }
    return 0;
}
