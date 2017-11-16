#include<stdio.h>
#include<string.h>
#include<math.h>

char isPrime[1000005];

void PrimeTable(){
    int i, j;
    memset(isPrime, 1, sizeof(isPrime));
    isPrime[0]=isPrime[1]=0;
    for(i=2;i<=1000;i++)
        if(isPrime[i])
            for(j=i*i;j<=1000000;j+=i)isPrime[j]=0;
}

int main(){
    int digit[10], num, tmp, len, i, j;

    PrimeTable();

    while(scanf("%d", &num)!=EOF){
        len=0;
        tmp=num;
        if(!isPrime[num])printf("%d is not prime.\n", num);
        else{
            while(tmp>0){
                digit[len++]=tmp%10;
                tmp/=10;
            }
            for(i=len-1, j=1;i>=0;i--, j*=10)
                tmp+=digit[i]*j;
            if(isPrime[num]*isPrime[tmp] && num!=tmp)
                printf("%d is emirp.\n", num);
            else printf("%d is prime.\n", num);
        }
    }
    return 0;
}
