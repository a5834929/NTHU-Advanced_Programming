#include<cstdio>
#include<cstring>
#include<iostream>
#include<iomanip>
#include<vector>
#include<deque>
using namespace std;
int T=1, dis[550], inQ[550];
int d1, d2, flag;
double ans1, ans2, tmp;
typedef struct E{
    int to, weight;
}EDGE;
EDGE edge;
vector<EDGE> V[550];
deque<int> Q;

void initial(){
    int i;
    for(i=0;i<=500;i++) V[i].clear();
    Q.clear();
    memset(dis, -1, sizeof(dis));
    memset(inQ, 0, sizeof(inQ));
    ans1=ans2=tmp=0;d1=d2=flag=1;
}

void SPFA(){
    int i, now, next, wei;
    Q.push_back(1);
    inQ[1] = 1;
    dis[1] = 0;
    while(!Q.empty()){
        now = Q.front();Q.pop_front();
        inQ[now] = 0;
        for(i=0;i<V[now].size();i++){
            next = V[now][i].to;
            wei = V[now][i].weight;
            if(dis[now]+wei < dis[next] || dis[next]==-1){
                dis[next] = dis[now]+wei;
                if(!inQ[next]){
                    Q.push_back(next);
                    inQ[next]=1;
                }
            }
        }
    }
}

int main(){
    int i, n, m;
    int x, y, prev;

    while(scanf("%d%d", &n, &m)!=EOF && n){
        initial();
        for(i=1;i<=m;i++){
            scanf("%d%d%d", &x, &y, &edge.weight);
            edge.to = y;
            V[x].push_back(edge);
            edge.to = x;
            V[y].push_back(edge);
        }
        SPFA();
        ans1 = ans2 = dis[1];
        for(i=2;i<=n;i++){
            if(dis[i]>ans1){
                d1 = i;
                ans1 = (double)dis[i]/1.0;
            }
        }

        for(i=0;i<V[d1].size();i++){
            prev = V[d1][i].to;
            if(dis[d1]-V[d1][i].weight!=dis[prev]){
                tmp = (double)(dis[d1]+V[d1][i].weight-dis[prev])/2.0+dis[prev];
                if(tmp>ans2){
                    flag = 2;
                    d2 = prev;
                    ans2 = tmp;
                }
            }
        }

        printf("System #%d\n", T++);
        if(flag==1)
            cout<<"The last domino falls after "<<fixed<<setprecision(1)<<ans1<<" seconds, at key domino "<<d1<<".\n\n";
        else if(flag==2)
            cout<<"The last domino falls after "<<ans2<<" seconds, between key dominoes "<<((d1<d2)?d1:d2)<<" and "<<((d1>d2)?d1:d2)<<".\n\n";
    }
    return 0;
}
