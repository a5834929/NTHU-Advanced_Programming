#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<deque>
#include<algorithm>
#define inf 2147483647
using namespace std;
typedef struct N{
    int a, b, c;
}NODE;
deque<NODE> Q;
int pour[220][220];
int best[220];
int A, B, C, D, total, ans;

void initialize(){
    Q.clear();
    total = ans = 0;
    for(int i=0;i<=A;i++)
        for(int j=0;j<=B;j++)
            pour[i][j]=inf;
    for(int i=0;i<201;i++)best[i]=inf;
}

void checkAndEnque(NODE n, int newPour){
    if(newPour<pour[n.a][n.b]){
        pour[n.a][n.b] = newPour;
        best[n.a] = min(best[n.a], newPour);
        best[n.b] = min(best[n.b], newPour);
        best[n.c] = min(best[n.c], newPour);
        total = newPour;
        Q.push_back(n);
    }
    return;
}

void BFS(){
    NODE n, now;
    int remain;
    n.a = n.b = 0, n.c = C;
    pour[0][0] = 0;
    best[0] = best[C] = 0;
    Q.push_back(n);
    while(!Q.empty()){
        now = Q.front(); Q.pop_front();
        // C->A
        remain = min(now.c+now.a, A) - now.a;
        if(remain>0){
            n.a = now.a+remain;
            n.b = now.b;
            n.c = now.c-remain;
            checkAndEnque(n, pour[now.a][now.b]+remain);
        }
        // C->B
        remain = min(now.c+now.b, B) - now.b;
        if(remain>0){
            n.a = now.a;
            n.b = now.b+remain;
            n.c = now.c-remain;
            checkAndEnque(n, pour[now.a][now.b]+remain);
        }
        // B->A
        remain = min(now.b+now.a, A) - now.a;
        if(remain>0){
            n.a = now.a+remain;
            n.b = now.b-remain;
            n.c = now.c;
            checkAndEnque(n, pour[now.a][now.b]+remain);
        }
        // B->C
        remain = min(now.b+now.c, C) - now.c;
        if(remain>0){
            n.a = now.a;
            n.b = now.b-remain;
            n.c = now.c+remain;
            checkAndEnque(n, pour[now.a][now.b]+remain);
        }
        // A->B
        remain = min(now.a+now.b, B) - now.b;
        if(remain>0){
            n.a = now.a-remain;
            n.b = now.b+remain;
            n.c = now.c;
            checkAndEnque(n, pour[now.a][now.b]+remain);
        }
        // A->C
        remain = min(now.a+now.c, C) - now.c;
        if(remain>0){
            n.a = now.a-remain;
            n.b = now.b;
            n.c = now.c+remain;
            checkAndEnque(n, pour[now.a][now.b]+remain);
        }
    }
}

int main(){
    int T, d;

    scanf("%d", &T);
    while(T--){
        scanf("%d%d%d%d", &A, &B, &C, &D);
        initialize();
        BFS();
        if(best[D]<inf) d = D;
        else for(d=D;d>=0;d--)
                if(best[d]<inf) break;
        printf("%d %d\n", best[d], d);
    }
    return 0;
}
