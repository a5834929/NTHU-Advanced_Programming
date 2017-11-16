#include<stdio.h>
#include<stdlib.h>

typedef struct P{
    int sum, a, b;
}PAIR;
PAIR pairs[1000005];

int cmp(const void*P, const void*Q){
    PAIR p=*(PAIR*)P, q=*(PAIR*)Q;
    return p.sum-q.sum;
}

int MAX(int a, int b){
    return (a>b)?a:b;
}

int main(){
    int N, Y, i, j, k, l;
    int arr[1005];
    int U, L, M, ans, flag;

    while(scanf("%d", &N)!=EOF && N){
        for(i=0;i<N;i++)
            scanf("%d", &arr[i]);
        k=0;
        for(i=0;i<N;i++){
            for(j=0;j<N;j++){
                if(i!=j){
                    pairs[k].sum=arr[i]+arr[j];
                    pairs[k].a=arr[i];
                    pairs[k].b=arr[j];
                    k++;
                }
            }
        }
        qsort(pairs, k, sizeof(PAIR), cmp);
        flag=0;
        ans=-2147483648;
        for(i=0;i<N;i++){
            for(j=0;j<N;j++){
                if(i!=j){
                    Y=arr[i]-arr[j];
                    U=k-1;
                    L=0;
                    while(U>L){
                        M=(U+L)/2;
                        if(Y>pairs[M].sum)L=M+1;
                        else if(Y<pairs[M].sum)U=M-1;
                        else{
                            for(l=M;pairs[l].sum==Y;l++){
                                if(arr[i]!=pairs[l].a && arr[i]!= pairs[l].b && arr[j]!=pairs[l].a && arr[j]!= pairs[l].b){
                                    flag=1;
                                    ans=MAX(ans, arr[i]);
                                }
                            }
                            for(l=M;pairs[l].sum==Y;l--){
                                if(arr[i]!=pairs[l].a && arr[i]!= pairs[l].b && arr[j]!=pairs[l].a && arr[j]!= pairs[l].b){
                                    flag=1;
                                    ans=MAX(ans, arr[i]);
                                }
                            }
                            break;
                        }
                    }
                }
            }
        }
        if(flag)printf("%d\n", ans);
        else printf("no solution\n");
    }
    return 0;
}
