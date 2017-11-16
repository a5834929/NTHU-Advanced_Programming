#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct S{
    char seq[60];
    int sum, ind;
}STR;
STR dna[150];

int cmp(const void*q, const void*p){
    STR a=*(STR*)q, b=*(STR*)p;
    if(a.sum<b.sum)return -1;
    else if(a.sum>b.sum)return 1;
    if(a.ind<b.ind)return -1;
    else return 1;
}

int main(){
    int N, n, m, i, j;
    int A, C, G, T;
    char str[60];
    scanf("%d", &N);
    while(N--){
        memset(dna, 0, sizeof(dna));
        scanf("%d%d", &n, &m);
        for(i=0;i<m;i++){
            scanf("%s", str);
            A=C=G=T=0;
            for(j=0;j<n;j++){
                if(str[j]=='A')A++;
                else if(str[j]=='C')C++;
                else if(str[j]=='G')G++;
            }
            strcpy(dna[i].seq, str);
            dna[i].ind=i;
            for(j=0;j<n;j++){
                if(str[j]=='T') dna[i].sum+=(A+C+G);
                else if(str[j]=='G'){
                    dna[i].sum+=(A+C);
                    G--;
                }
                else if(str[j]=='C'){
                    dna[i].sum+=A;
                    C--;
                }
                else if(str[j]=='A')A--;
            }
        }
        qsort(dna, m, sizeof(STR), cmp);
        for(i=0;i<m;i++)
            printf("%s\n", dna[i].seq);
        if(N>0)printf("\n");
    }
    return 0;
}
