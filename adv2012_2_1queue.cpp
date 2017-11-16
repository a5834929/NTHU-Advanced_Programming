#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<deque>
using namespace std;
deque<int> Q;

int choose(int c, int k){
    int off, left=k-1, x;
    while(left){
        off = c%left;
        if(off==0) off=left;
        off--;
        while(off--){
            x = Q.front();
            Q.pop_front();
            Q.push_back(x);
        }
        if(left>1 && Q.front()==13) return 1;
        Q.pop_front();
        left--;
    }
    return 0;
}

int main(){
    int N, i, k, cycle;
    int ans[101];

    for(N=13;N<=100;N++){
        Q.clear();
        for(i=2;i<=N;i++)
            Q.push_back(i);
        cycle = 1;
        while(choose(cycle, N)){
            Q.clear();
            for(i=2;i<=N;i++)
                Q.push_back(i);
            cycle++;
        }
        ans[N]=cycle;
    }
    while(scanf("%d", &N)!=EOF && N){
        printf("%d\n", ans[N]);
    }

    return 0;
}
