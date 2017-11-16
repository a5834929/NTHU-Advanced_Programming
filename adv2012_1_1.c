#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct A{
    int num, index, order;
}ARRAY;

ARRAY arr[1000010];
int count[1000010], temp[1000010];

int cmp(const void*q, const void*p){
    ARRAY a=*(ARRAY*)q, b=*(ARRAY*)p;
    if(a.num<b.num)return -1;
    else if(a.num>b.num)return 1;
    if(a.order<b.order)return -1;
    else return 1;
}

int main(){
    int N, Q, k, v, i;
    int L, U, M;

    while(scanf("%d%d", &N, &Q)!=EOF){
        memset(arr, 0, sizeof(arr));
        memset(count, 0, sizeof(count));
        for(i=0;i<N;i++){
            scanf("%d", &arr[i].num);
            temp[i]=arr[i].num;
            arr[i].index=i+1;
            count[arr[i].num]++;
            arr[i].order=count[arr[i].num];
        }
        qsort(arr, N, sizeof(ARRAY), cmp);
        while(Q--){
            scanf("%d%d", &k, &v);
            if(k>count[v]) printf("0\n");
            else{
                L=0;
                U=N-1;
                while(L<U){
                    M=(U+L)/2;
                    if(arr[M].num>v)U=M-1;
                    else if(arr[M].num<v)L=M+1;
                    else break;
                }
                M=(L+U)/2;
                i=arr[M].order-k;
                printf("%d\n", arr[M-i].index);
            }
        }
    }
    return 0;
}
