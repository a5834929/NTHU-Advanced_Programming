#include<stdio.h>
#include<string.h>

long long int a[300], b[300], c[600];
char A[300], B[300];

int main(){
    int i, j, alen, blen, carry;

    while(scanf("%s%s", A, B)!=EOF){
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        memset(c, 0, sizeof(c));
        alen=strlen(A), blen=strlen(B);
        for(i=0;i<alen;i++) a[i]=A[alen-1-i]-'0';
        for(i=0;i<blen;i++) b[i]=B[blen-1-i]-'0';
        for(i=0;i<alen;i++)
            for(j=0;j<blen;j++)
                c[i+j] += a[i]*b[j];
        carry=0;
        for(i=0;i<=alen+blen;i++){
            c[i]+=carry;
            carry=c[i]/10;
            c[i]%=10;
        }
        for(i=alen+blen+1;i>=0;i--)if(c[i])break;
        if(i==-1)printf("0");
        else for(;i>=0;i--)printf("%lld", c[i]);
        printf("\n");
    }
    return 0;
}
