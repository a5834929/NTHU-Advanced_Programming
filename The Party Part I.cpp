#include<cstdio>
#include<cstring>
#include<vector>
#include<deque>
using namespace std;
vector<int> V[100010];
deque<int> Q;
int dis[100010], inQ[100010];

void initialize(){
    int i;
    for(i=0;i<100010;i++) V[i].clear();
    Q.clear();
    memset(dis, -1, sizeof(dis));
    memset(inQ, 0, sizeof(inQ));
}

void SPFA(){
    int i, now, next;
    dis[0] = 0;
    Q.push_back(0);
    inQ[0] = 1;

    while(!Q.empty()){
        now = Q.front(), Q.pop_front();
        inQ[now] = 0;
        for(i=0;i<V[now].size();i++){
            next = V[now][i];
            if(dis[now]+1<dis[next] || dis[next]==-1){
                dis[next] = dis[now]+1;
                if(inQ[next]==0){
                    Q.push_back(next);
                    inQ[next] = 1;
                }
            }
        }
    }
}

int main(){
    int T, i, j, p, r, x, y;

    scanf("%d", &T);
    while(T--){
        initialize();
        scanf("%d%d", &p, &r);
        for(i=0;i<r;i++){
            scanf("%d%d", &x, &y);
            V[x].push_back(y);
            V[y].push_back(x);
        }
        SPFA();
        for(i=1;i<p;i++){
            if(dis[i]!=-1) printf("%d\n", dis[i]);
            else printf("INF\n");
        }
        if(T>0) printf("\n");
    }

    return 0;
}
