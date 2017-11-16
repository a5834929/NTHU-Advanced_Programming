#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<algorithm>
#include<vector>
#include<deque>
using namespace std;
vector<int> V[310];
deque<int> Q;
int vis[310], pre[310], dis[310];

void initialize(){
    int i;
    for(i=0;i<303;i++) V[i].clear();
    Q.clear();
}

void BFS(int src, int des){
    int i, now, next;
    Q.push_back(src);
    vis[src] = 1;
    dis[src] = 0;
    while(!Q.empty()){
        now = Q.front(), Q.pop_front();
        for(i=0;i<V[now].size();i++){
            next = V[now][i];
            if(dis[now]+1<dis[next] || dis[next]==-1){
                dis[next] = dis[now]+1;
                pre[next] = now;
                if(!vis[next]){
                    Q.push_back(next);
                    vis[next] = 1;
                }
            }
        }
    }
}

void printAns(int ind){
    if(ind==0) return;
    printAns(pre[ind]);
    printf("%d ", ind);
}

int main(){
    int n, t, i, j, len;
    int src, des, node;
    char str[400];

    while(scanf("%d", &n)!=EOF){
        initialize();
        for(i=0;i<n;i++){
            scanf("%s", str);
            len = strlen(str);
            node = 0;
            for(j=0;j<len;j++){
                if(isdigit(str[j])){
                    node*=10;
                    node+=(str[j]-'0');
                }
                if(str[j]=='-'){
                    src = node;
                    j++;
                    node = 0;
                    break;
                }
            }
            for(;j<len;j++){
                if(isdigit(str[j])){
                    node*=10;
                    node+=(str[j]-'0');
                }
                else{
                    des = node;
                    V[src].push_back(des);
                    node = 0;
                }
            }
            if(node!=0) V[src].push_back(node);
        }

        scanf("%d", &t);
        printf("-----\n");
        for(i=0;i<t;i++){
            scanf("%d%d", &src, &des);
            memset(vis, 0, sizeof(vis));
            memset(pre, 0, sizeof(pre));
            memset(dis, -1, sizeof(dis));
            BFS(src, des);
            if(pre[des]==0)printf("connection impossible");
            else{
                printAns(pre[des]);
                printf("%d", des);
            }
            printf("\n");
        }
    }
    return 0;
}
