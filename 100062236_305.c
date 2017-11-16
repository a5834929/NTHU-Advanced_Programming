#include<stdio.h>

typedef struct P{
    int prev, ind, next;
}PPL;

PPL ppl[30];

int choose(int c, int K){
    int now=0, kill=c%(2*K);
    int left=2*K, i;
    PPL tmp;
    if(kill==0)kill=2*K;
    while(left>K){
        tmp = ppl[now];
        for(i=1;i<kill;i++)
            tmp = ppl[tmp.next];
        if(tmp.ind<K)return 1;
        ppl[ppl[tmp.ind].prev].next = ppl[tmp.ind].next;
        ppl[ppl[tmp.ind].next].prev = ppl[tmp.ind].prev;
        now=ppl[tmp.ind].next;
        left--;
        kill = c%left;
        if(kill==0)kill=left;
    }
    return 0;
}

int main(){
    int i, k, K, cycle;
    int ans[14];

    for(k=1;k<=13;k++){
        for(i=0;i<2*k;i++){
            ppl[i].ind = i;
            ppl[i].prev=(i-1<0)?2*k-1:i-1;
            ppl[i].next=(i+1>2*k-1)?0:i+1;
        }
        cycle=1;
        while(choose(cycle, k)){
            for(i=0;i<2*k;i++){
                ppl[i].ind = i;
                ppl[i].prev=(i-1<0)?2*k-1:i-1;
                ppl[i].next=(i+1>2*k-1)?0:i+1;
            }
            cycle++;
        }
        ans[k]=cycle;
    }

    while(scanf("%d", &K)!=EOF && K){
        printf("%d\n", ans[K]);
    }
    return 0;
}
