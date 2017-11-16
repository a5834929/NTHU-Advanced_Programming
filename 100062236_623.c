#include<stdio.h>
#include<string.h>

int tmp[3000];

typedef struct N{
    int ans[3000];
    int len;
}NUM;
NUM fact[1005];

int main(){
    int N, i, j, carry;
    memset(tmp, 0, sizeof(int));
    memset(fact, 0, sizeof(NUM));

    fact[0].len=fact[1].len=fact[2].len=1;
    fact[0].ans[0]=fact[1].ans[0]=1;
    fact[2].ans[0]=2;

    for(i=3;i<=1000;i++){
        for(j=0;j<fact[i-1].len;j++)
            fact[i].ans[j]=fact[i-1].ans[j]*i;
        fact[i].len=j;
        carry=0;
        for(j=0;j<fact[i].len+3;j++){
            fact[i].ans[j]+=carry;
            carry=fact[i].ans[j]/10;
            fact[i].ans[j]%=10;
        }
        for(j=fact[i].len+5;j>=0;j--)
            if(fact[i].ans[j]!=0){
                fact[i].len=j+1;
                break;
            }
    }

    while(scanf("%d", &N)!=EOF){
        printf("%d!\n", N);
        for(i=fact[N].len-1;i>=0;i--)
            printf("%d", fact[N].ans[i]);
        printf("\n");
    }
    return 0;
}
