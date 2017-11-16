#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<deque>
#include<vector>
using namespace std;

typedef struct E{
    int to, num;
}EDGE;

EDGE edge;
int deg[50];
int eNum, pNum;
int vis[2000], ans[2000];
deque<int> S;
vector<EDGE> V[2000];

bool cmp(const EDGE&p, const EDGE&q){
    if(p.num<q.num)return true;
    return false;
}

void findCircuit(int from){
    int i, next, street;

    if(!deg[from]){
        S.push_back(from);
        return;
    }
    for(i=0;i<V[from].size();i++){
        next = V[from][i].to;
        street = V[from][i].num;
        if(!vis[street]){
            vis[street] = 1;
            deg[from]--;deg[next]--;
            findCircuit(next);
        }
    }
    S.push_back(from);
}

void Initial(){
    int i;
    memset(deg, 0, sizeof(deg));
    S.clear();
    for(i=1;i<50;i++)
        V[i].clear();
}

int main(){
    int x, y, z, i;
    int first;
    int noEuler, src, des;

    while(scanf("%d%d", &x, &y)!=EOF && x*y){
        eNum=pNum=noEuler=first=0;
        Initial();
        while(x*y){
            scanf("%d", &z);
            if(!first)first=(x<y)?x:y;
            vis[z] = 0;
            edge.num = z;
            edge.to = y;
            V[x].push_back(edge);
            edge.to = x;
            V[y].push_back(edge);

            pNum = (pNum>x)?pNum:x;
            pNum = (pNum>y)?pNum:y;
            eNum = (eNum>z)?eNum:z;
            deg[x]++;
            deg[y]++;
            scanf("%d%d", &x, &y);
        }
        for(i=1;i<=pNum;i++){
            if(deg[i]%2){
                noEuler = 1;
                break;
            }
            sort(V[i].begin(), V[i].end(), cmp);
        }

        if(noEuler)printf("Round trip does not exist.\n\n");
        else{
            findCircuit(first);
            src = S.back();S.pop_back();
            while(!S.empty()){
                des = S.back();S.pop_back();
                for(i=0;i<V[src].size();i++){
                    if(V[src][i].to==des && vis[V[src][i].num]){
                        printf("%d%c", V[src][i].num, S.size()?' ':'\n');
                        vis[V[src][i].num] = 0;
                        break;
                    }
                }
                src = des;
            }
            printf("\n");
        }
    }
    return 0;
}
