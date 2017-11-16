#include<cstdio>
#include<cstdlib>
#include<cstring>

typedef struct R{
    int prev, ind, next;
}REG;
REG region[101];

int choose(int c, int N){
    int now = 1, off;
    int left = N-1, i;
    REG tmp;
    while(left){
        off = c%left;
        if(off==0) off=left;
        off--;
        tmp = region[now];
        while(off--) tmp = region[tmp.next];
        if(left>1 && tmp.ind==12) return 1;
        region[tmp.next].prev = tmp.prev;
        region[tmp.prev].next = tmp.next;
        now = tmp.next;
        left--;
    }
    return 0;
}

int main(){
    int N, i, k;
    int cycle, ans[101];

    for(k=13;k<=100;k++){
        memset(region, 0, sizeof(region));
        for(i=1;i<k;i++){
            region[i].ind = i;
            region[i].prev = (i-1<1)?k-1:i-1;
            region[i].next = (i+1>k-1)?1:i+1;
        }
        cycle = 1;
        while(choose(cycle, k)){
            for(i=1;i<k;i++){
                region[i].ind = i;
                region[i].prev = (i-1<1)?k-1:i-1;
                region[i].next = (i+1>k-1)?1:i+1;
            }
            cycle++;
        }
        ans[k]=cycle;
    }

    while(scanf("%d", &N)!=EOF && N){
        printf("%d\n", ans[N]);
    }

    return 0;
}
