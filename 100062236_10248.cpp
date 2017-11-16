#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<deque>
using namespace std;
int adj[10][10];
int out[10], in[10];
int num[10];
deque<int> Q;

void initialize(){
    Q.clear();
    memset(adj, 0, sizeof(adj));
    memset(out, 0, sizeof(out));
    memset(in, 0, sizeof(in));
    memset(num, -1, sizeof(num));
}

void DFS(int src){
    int i;
    num[src] = 1;
    if(out[src]==0){
        for(i=0;i<10;i++)
            if(out[i]>in[i])
                break;
        if(i!=10)DFS(i);
        Q.push_back(src);
        return;
    }
    for(i=0;i<10;i++){
        if(adj[src][i]){
            adj[src][i]--;
            out[src]--;
            in[i]--;
            DFS(i);
        }
    }
    Q.push_back(src);
}

int main(){
    int i, m, n;
    int src, src1;

    while(scanf("%d%d", &m, &n)!=EOF){
        initialize();
        src = src1 = -1;
        for(i=m;i<=n;i++){
            if(i>=10){
                adj[i/10][i%10]++;
                out[i/10]++;
                in[i%10]++;
            }
            else num[i] = 0;
        }

        for(i=1;i<10;i++){
            if(out[i]>in[i]){
                src = i;
                break;
            }
            if(src1==-1 && out[i]==in[i] && out[i])
                src1 = i;
        }
        if(src==-1) src = src1;
        if(src!=-1) DFS(src);
        while(!Q.empty()){
            printf("%d", Q.back());
            Q.pop_back();
        }
        for(i=0;i<10;i++)
            if(num[i]==0) printf("%d", i);
        printf("\n");
    }
    return 0;
}
