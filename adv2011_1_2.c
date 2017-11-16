#include<stdio.h>
#include<string.h>
#include<math.h>

typedef struct P{
    int a, b;
}PRIME;
PRIME primes[100003];
char isPrime[18500000];

void PrimeTable(){
    int i, j;
    memset(isPrime, 1, sizeof(isPrime));
    memset(primes, 0, sizeof(primes));
    isPrime[0]=isPrime[1]=0;
    for(i=2;i<=4500;i++)
        if(isPrime[i])
            for(j=i*i;j<=18409201;j+=i)
                isPrime[j]=0;
}

int main(){
    int i, j=0;
    PrimeTable();
    for(i=3;i<=18409199;i+=2){
        if(isPrime[i]*isPrime[i+2]){
            primes[j].a=i;
            primes[j++].b=i+2;
        }
    }
    while(scanf("%d", &i)!=EOF){
        printf("(%d, %d)\n", primes[i-1].a, primes[i-1].b);
    }
    return 0;
}
