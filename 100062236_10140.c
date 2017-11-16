#include<stdio.h>
#include<string.h>
#include<math.h>
#define MAX 1000010

int plen;
char isPrime[MAX];

int PrimeTable(int L, int U){
    int i, j, diff, range;

    plen=U-L+1;
    memset(isPrime, 1, sizeof(isPrime));

    i=0;
    if(L%2) i=1;
    for(;i<=plen;i+=2) isPrime[i]=0;
    range=(int)(sqrt(U)+0.01);

    if(L<=1) isPrime[1-L]=0;
    if(L<=2) isPrime[2-L]=1;
    for(i=3;i<=range;i+=2){
        if(i>L && !isPrime[i-L]) i+=2;
        j=(L/i)*i;
        if(j<L) j+=i;
        if(j==i) j+=i;
        j-=L;
        for(;j<=plen;j+=i) isPrime[j]=0;
    }

    for(i=0;i<plen;i++) if(isPrime[i]) break;
    return i;
}

int main(){
    int L, U, i;
    int c1, c2, d1, d2;
    int pre, tmp, min, max;

    while(scanf("%d%d", &L, &U)!=EOF){
        c1=c2=d1=d2=max=0;
        min=2147483647;
        i=PrimeTable(L, U);
        pre=i;
        i++;
        while(i<plen){
            if(isPrime[i]){
                tmp=i-pre;
                if(tmp>max){
                    d1=pre;
                    d2=i;
                    max=tmp;
                }
                if(tmp<min){
                    c1=pre;
                    c2=i;
                    min=tmp;
                }
                pre=i;
            }
            i++;
        }
        if(max==0) printf("There are no adjacent primes.\n");
        else printf("%d,%d are closest, %d,%d are most distant.\n", c1+L, c2+L, d1+L, d2+L);
    }
    return 0;
}
