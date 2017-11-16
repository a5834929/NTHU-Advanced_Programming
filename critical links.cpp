#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<vector>
using namespace std;
vector<int> V[100];
int used[100][100];
int vis[100];
int X, Y;
typedef struct L{
    int a, b;
}LINK;
LINK link[20000];

void initialize(){
    int i;
    for(i=0;i<100;i++) V[i].clear();
    memset(vis, 0, sizeof(vis));
    memset(link, 0, sizeof(link));
    memset(used, 0, sizeof(used));
}

int edgeExist(int i, int j){
    return !((i==X && j==Y) || (i==Y && j==X));
}

void findComponent(int ind, int subNo){
    int i;
    vis[ind] = 1;
    for(i=0;i<V[ind].size();i++)
        if(!vis[V[ind][i]]) findComponent(V[ind][i], subNo);
    return;
}

void DFS(int ind, int subNo){
    int i;
    vis[ind] = 1;
    for(i=0;i<V[ind].size();i++)
        if(!vis[V[ind][i]] && edgeExist(ind, V[ind][i]))
            DFS(V[ind][i], subNo);
    return;
}

int main(){
    int S, i, j, k, x, n, m;
    int server, edge, subNo;

    while(scanf("%d", &S)!=EOF){
        initialize(); m = 0;
        for(i=0;i<S;i++){
            scanf("%d", &server);
            scanf("%*c%*c%d%*c", &edge);
            for(j=0;j<edge;j++){
                scanf("%d", &x);
                V[server].push_back(x);
            }
        }
        subNo = 0;
        for(i=0;i<S;i++)
            if(!vis[i]) findComponent(i, subNo++);

        for(i=0;i<S;i++){
            for(j=0;j<V[i].size();j++){
                n = 0;
                memset(vis, 0, sizeof(vis));
                if(i!=V[i][j] && !used[i][V[i][j]] && !used[V[i][j]][i]){
                    X = i;
                    Y = V[i][j];
                    used[i][V[i][j]] = used[V[i][j]][i] = 1;
                    for(k=0;k<S;k++)
                        if(!vis[k]) DFS(k, n++);
                    if(n>subNo){
                        link[m].a = X;
                        link[m++].b = Y;
                    }
                }
            }
        }
        printf("%d critical links\n", m);
        for(i=0;i<m;i++){
            printf("%d - %d\n", link[i].a, link[i].b);
        }
        printf("\n");

    }

    return 0;
}
