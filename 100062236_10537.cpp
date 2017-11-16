#include<cstdio>
#include<cstring>
#include<cctype>
#include<deque>
using namespace std;
int caseNum = 1;
int roadMap[52][52];
int inQ[52], from[52];
long long int dis[52];
deque<int> Q;

void initialize(){
    Q.clear();
    memset(roadMap, 0, sizeof(roadMap));
    memset(dis, -1, sizeof(dis));
    memset(inQ, 0, sizeof(inQ));
    memset(from, -1, sizeof(from));
}

int calIndex(char ch){
    if(isupper(ch)) return ch-'A';
    return ch-'a'+26;
}

long long int calCost(long long int cost){
    long long int a, b, tmp;
    tmp = cost%19;
    a = (19-tmp)%19;
    b = (cost+a)/19;
    return 20*b-a;
}

void SPFA(int src, long long int deliver){
    int i, now, next;
    long long int newDeliver;
    dis[src] = deliver;
    inQ[src] = 1;
    Q.push_back(src);
    while(!Q.empty()){
        now = Q.back();Q.pop_back();
        inQ[now] = 0;
        for(i=0;i<52;i++){
            next = i;
            if(roadMap[now][next]){
                if(now<26) newDeliver = calCost(dis[now]);
                else newDeliver = dis[now]+1;
                if(newDeliver<dis[next] || dis[next]==-1){
                    dis[next] = newDeliver;
                    from[next] = now;
                    if(!inQ[next]){
                        inQ[next] = 1;
                        Q.push_back(next);
                    }
                }
                else if(newDeliver==dis[next])
                    from[next] = (from[next]<now)?from[next]:now;
            }
        }
    }
}

int main(){
    int i, j, road, src, tar;
    long long int deliver;
    char s1[2], s2[2];

    while(scanf("%d", &road)!=EOF && road!=-1){
        initialize();
        deliver = src = tar = 0;
        while(road--){
            scanf("%s%s", s1, s2);
            i = calIndex(s1[0]);
            j = calIndex(s2[0]);
            roadMap[i][j] = roadMap[j][i] = 1;
        }
        scanf("%lld %s%s", &deliver, s1, s2);
        src = calIndex(s1[0]);
        tar = calIndex(s2[0]);

        SPFA(tar, deliver);

        printf("Case %d:\n", caseNum++);
        printf("%lld\n", dis[src]);
        printf("%c", (src<26)?(src+'A'):(src+'a'-26));
        while(from[src]!=-1){
            printf("-%c", (from[src]<26)?(from[src]+'A'):(from[src]+'a'-26));
            src = from[src];
        }
        printf("\n");
    }
    return 0;
}
