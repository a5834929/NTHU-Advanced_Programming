#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
using namespace std;

vector<int> adlist[30010];
int T, N, M, num;
int vis[30010];

void DFS(int ind){
    int i;
    vis[ind]=1;
    for(i=0;i<adlist[ind].size();i++){
        if(!vis[adlist[ind][i]]){
            num++;
            DFS(adlist[ind][i]);
        }
    }
}

int main(){
    int i, j;
    int x, y;
    int max;

    scanf("%d", &T);

    while(T--){
        scanf("%d%d", &N, &M);
        memset(vis, 0, sizeof(vis));
        num=max=0;
        for(i=0;i<N;i++) adlist[i].clear();
        for(i=0;i<M;i++){
            scanf("%d%d", &x, &y);
            adlist[x].push_back(y);
            adlist[y].push_back(x);
        }
        for(i=0;i<N;i++){
            num=0;
            if(!vis[i]){
                num++;
                DFS(i);
            }
            max=(num>max)?num:max;
        }
        printf("%d\n", max);
    }
    return 0;
}
