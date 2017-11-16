#include<cstdio>
#include<cstring>
#include<vector>
#include<deque>
#include<algorithm>
using namespace std;
typedef struct P{
    int to, weight;
}POINT;
POINT point;
vector<POINT> V[110];
int village, castle, road;
int limit, time;
int adj[110][110];
int dis[110][12];
int inQ[110][12];
deque<pair<int, int> > Q;

void initialize(){
    int i;
    for(i=0;i<110;i++)V[i].clear();
    Q.clear();
    memset(adj, 0, sizeof(adj));
    memset(dis, -1, sizeof(dis));
    memset(inQ, 0, sizeof(inQ));
}
void FloydWarshall(){
    int i, j, k;
    for(k=1;k<=village;k++)
        for(i=1;i<=village+castle;i++)
            for(j=1;j<=village+castle;j++)
                if(adj[i][k]*adj[k][j] && adj[i][k]+adj[k][j]<=limit && i!=j){
                    if(adj[i][j]!=0) adj[i][j]= min(adj[i][j], adj[i][k]+adj[k][j]);
                    else adj[i][j]=adj[i][k]+adj[k][j];
                }
}

void SPFA(){
    int i, p, t = 0;
    int np;
    p = village+castle;
    inQ[p][t] = 1;
    dis[p][t] = 0;
    Q.push_back(make_pair(p, t));
    while(!Q.empty()){
        p = Q.front().first;
        t = Q.front().second;
        Q.pop_front(), inQ[p][t] = 0;
        for(i=0;i<V[p].size();i++){
            np = V[p][i].to;
            if(dis[p][t]+V[p][i].weight<dis[np][t] || dis[np][t]==-1){
                dis[np][t] = dis[p][t]+V[p][i].weight;
                if(!inQ[np][t]){
                    Q.push_back(make_pair(np, t));
                    inQ[np][t] = 1;
                }
            }
        }
        for(i=1;i<=village+castle;i++){
            if(adj[p][i] && t<time){
                if(dis[p][t]<dis[i][t+1] || dis[i][t+1]==-1){
                    dis[i][t+1] = dis[p][t];
                    if(!inQ[i][t+1]){
                        Q.push_back(make_pair(i, t+1));
                        inQ[i][t+1] = 1;
                    }
                }
            }
        }
    }
}

int main(){
    int T, i, ans;
    int from , to, wei;


    scanf("%d", &T);
    while(T--){
        initialize();
        scanf("%d%d%d%d%d", &village, &castle, &road, &limit, &time);
        for(i=0;i<road;i++){
            scanf("%d%d%d", &from, &to, &wei);
            point.to = to, point.weight = wei;
            V[from].push_back(point);
            point.to = from;
            V[to].push_back(point);
            if(wei<=limit) adj[from][to] = adj[to][from] = wei;
        }
        FloydWarshall();
        SPFA();
        ans = 2147483647;
        for(i=0;i<=time;i++)
            if(dis[1][i]!=-1 && ans>dis[1][i])
                ans = dis[1][i];
        printf("%d\n", ans);
    }

    return 0;
}
