#include<stdio.h>
#include<string.h>
#include<math.h>

int prime[32000], plen=0;
char isPrime[32000];

void PrimeTable(void){
    int i, j;
    memset(isPrime, 1, sizeof(isPrime));
    isPrime[0]=isPrime[1]=0;

    int range=(int)(sqrt(1000000000)+0.001);

    for(i=2;i<=range;i++)
        if(isPrime[i]==1)
            for(j=i*i;j<=range;j+=i)
                isPrime[j]=0;
    for(i=2;i<=range;i++)
        if(isPrime[i]==1)
            prime[plen++]=i;
}

int main(){
    int N, L, U, i, j;
    int range;
    int x, ans, tmp, max, count;

    scanf("%d", &N);
    PrimeTable();
    while(N--){
        scanf("%d%d", &L, &U);
        range=(int)(sqrt(U)+0.001);
        max=ans=0;
        for(i=L;i<=U;i++){
            tmp=1;
            x=i;
            for(j=0;j<plen && prime[j]<=range+5;j++){
                count=1;
                while(x%prime[j]==0){
                    count++;
                    x/=prime[j];
                }
                tmp*=count;
            }
            if(tmp>max){
                ans=i;
                max=tmp;
            }
        }
        printf("Between %d and %d, %d has a maximum of %d divisors.\n", L, U, ans, max);
    }
    return 0;
}
