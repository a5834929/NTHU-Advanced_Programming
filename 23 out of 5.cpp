#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
int num[5], done, vis[5];

void DFS(int ind, int sum){
    int i;
    if(ind==5){
        if(sum==23) done = 1;
        return;
    }
    for(i=0;i<5;i++){
        if(!vis[i]){
            vis[i] = 1;
            DFS(ind+1, sum*num[i]);
            DFS(ind+1, sum+num[i]);
            DFS(ind+1, sum-num[i]);
            vis[i] = 0;
        }
    }
}

int main(){
    int i;

    while(scanf("%d", &num[0])!=EOF){
        done = 0;
        for(i=1;i<5;i++)
            scanf("%d", &num[i]);
        if(num[0]+num[1]+num[2]+num[3]+num[4]==0) break;
        for(i=0;i<5;i++){
            memset(vis, 0, sizeof(vis));
            vis[i] = 1;
            DFS(1, num[i]);
            if(done)break;
        }
        if(done) printf("Possible\n");
        else printf("Impossible\n");
    }

    return 0;
}
