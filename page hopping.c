#include<stdio.h>
#include<string.h>
int adj[110][110], T=1;
int exist[110];
double ans;

int min(int a, int b){
    return (a<b)?a:b;
}
int max(int a, int b){
    return (a>b)?a:b;
}

void initialize(){
    ans = 0;
    memset(adj, 0, sizeof(adj));
    memset(exist, 0, sizeof(exist));
}

void FLOYDWARSHALL(int a, int b){
    int i, j, k;
    for(k=a;k<=b;k++)
        for(i=a;i<=b;i++)
            for(j=a;j<=b;j++)
                if(i!=j && adj[i][k]*adj[k][j]){
                    if(adj[i][j]) adj[i][j] = min(adj[i][j], adj[i][k]+adj[k][j]);
                    else adj[i][j] = adj[i][k]+adj[k][j];
                }
}

int main(){
    int p1, p2, n;
    int i, j, a, b;

    while(scanf("%d%d", &p1, &p2)!=EOF && p1*p2){
        initialize();
        n = 0, a = 101, b = 0;
        adj[p1][p2] = 1;
        exist[p1] = exist[p2] = 1;
        a = min(a, min(p1, p2));
        b = max(b, max(p1, p2));
        while(scanf("%d%d", &p1, &p2)!=EOF && p1*p2){
            adj[p1][p2] = 1;
            exist[p1] = exist[p2] = 1;
            a = min(a, min(p1, p2));
            b = max(b, max(p1, p2));
        }
        FLOYDWARSHALL(a, b);
        for(i=a;i<=b;i++) for(j=a;j<=b;j++) ans+=adj[i][j];
        for(i=1;i<=100;i++) n+=exist[i];
        printf("Case %d: average length between pages = %.3lf clicks\n", T++, ans/(n*(n-1)));
    }

    return 0;
}
