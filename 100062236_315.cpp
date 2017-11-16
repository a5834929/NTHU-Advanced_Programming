#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
vector<int> adlist[120];
int vis[120];

void DFS(int ind, int N){
    int i;
    vis[ind]=1;
    for(i=0;i<adlist[ind].size();i++){
        if(!vis[adlist[ind][i]] && vis[adlist[ind][i]]!=-1)
            DFS(adlist[ind][i], N);
    }
}

int main(){
    int i, j, N, M, m;
    int ans, cnt;
    char c;

    while(scanf("%d", &N) && N){
        for(i=1;i<=N;i++) adlist[i].clear();
        while(scanf("%d", &M) && M){
            while(scanf("%d%c", &m, &c) && m){
                adlist[M].push_back(m);
                adlist[m].push_back(M);
                if(c=='\n')break;
            }
        }
        ans=0;
        for(i=1;i<=N;i++){
            memset(vis, 0, sizeof(vis));
            vis[i]=-1;
            DFS((i+1)%N+1, N);
            for(j=1;j<=N;j++){
                if(vis[j]==0){
                    ans++;
                    break;
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
