#include<stdio.h>

int M, K, ans[600];
long long int page[600];

long long int check(long long int mid){
    int i, cut=0;
    long long int sum=0, maxsum=0;
    for(i=M-1;i>=0;i--){
        if((i<K-cut-1 || sum+page[i]>mid) && cut<K-1){
            ans[i]=1;
            maxsum=(sum>maxsum)?sum:maxsum;
            sum=page[i];
            cut++;
        }
        else sum+=page[i];
    }
    return (sum>maxsum)?sum:maxsum;
}

int main(){
    int T, i;
    long long int upper, lower, mid, result;

    scanf("%d", &T);
    while(T--){
        scanf("%d%d", &M, &K);
        upper=0;
        for(i=0;i<M;i++){
            scanf("%lld", &page[i]);
            upper+=page[i];
        }
        lower=upper/K;
        while(lower<upper){
            mid=(lower+upper)/2;
            for(i=0;i<M;i++) ans[i]=0;
            result=check(mid);
            if(result>mid) lower=mid+1;
            else upper=mid;
        }
        for(i=0;i<M;i++) ans[i]=0;
        check(upper);
        for(i=0;i<M;i++){
            printf("%lld%c", page[i], (i<M-1)?' ':'\n');
            if(ans[i]) printf("/ ");
        }
    }
    return 0;
}
