#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define INF 2147483647
using namespace std;
int T=1, adj[101][101];

void initialize(){
    int i, j;
    for(i=1;i<101;i++)
        for(j=1;j<101;j++)
            adj[i][j] = INF;
}

void FLOYDWARSHALL(int n){
    int i, j, k;
    for(k=1;k<=n;k++){
        for(i=1;i<=n;i++){
            for(j=1;j<=n;j++){
                if(i!=j){
                    adj[i][j] = min(adj[i][j], max(adj[i][k], adj[k][j]));
                }
            }
        }
    }
}

int main(){
    int i;
    int node, edge, t;
    int n1, n2, decibel;

    scanf("%d%d%d", &node, &edge, &t);
    while(1){
        initialize();
        for(i=0;i<edge;i++){
            scanf("%d%d%d", &n1, &n2, &decibel);
            adj[n1][n2] = adj[n2][n1] = decibel;
        }
        FLOYDWARSHALL(node);
        printf("Case #%d\n", T++);
        for(i=0;i<t;i++){
            scanf("%d%d", &n1, &n2);
            if(adj[n1][n2]<INF)printf("%d\n", adj[n1][n2]);
            else printf("no path\n");
        }

        scanf("%d%d%d", &node, &edge, &t);
        if(node==0 && edge==0 && t==0) break;
        else printf("\n");
    }
    return 0;
}
