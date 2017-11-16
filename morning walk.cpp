#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<vector>
using namespace std;
vector<int> V[210];
int deg[210], euler;
int vis[210], edge[210][210];

void initialize(){
    int i;
    for(i=0;i<210;i++) V[i].clear();
    euler = 1;
    memset(deg, 0, sizeof(deg));
    memset(vis, 0, sizeof(vis));
    memset(edge, 0, sizeof(edge));
}

void DFS(int src){
    int i, next;

    vis[src] = 1;
    for(i=0;i<V[src].size();i++){
        next = V[src][i];
        if(!vis[next]){
            deg[next]--;
            deg[src]--;
            DFS(next);
        }
    }
}

void checkConnection(int src, int N){
    int i;
    DFS(src);
    for(i=0;i<N;i++){
        if(!vis[i]){
            euler = 0;
            break;
        }
    }
}

int main(){
    int N, R, i;
    int c1, c2;

    while(scanf("%d%d", &N, &R)!=EOF){
        initialize();
        for(i=0;i<R;i++){
            scanf("%d%d", &c1, &c2);
            V[c1].push_back(c2);
            V[c2].push_back(c1);
            deg[c1]++;
            deg[c2]++;
        }
        for(i=0;i<N;i++){
            if(deg[i]%2){
                euler = 0;
                break;
            }
        }

        if(euler) checkConnection(0, N);
        if(euler) printf("Possible\n");
        else printf("Not Possible\n");
    }

    return 0;
}
