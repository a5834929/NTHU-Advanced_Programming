#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;

int adj[30][30], in[30], out[30];
int vis[30], alph[30], euler;

void initialize(){
    euler = 1;
    memset(adj, 0, sizeof(adj));
    memset(in, 0, sizeof(in));
    memset(out, 0, sizeof(out));
    memset(vis, 0, sizeof(vis));
    memset(alph, 0, sizeof(alph));
}

void DFS(int src){
    int i;
    vis[src] = 1;
    for(i=0;i<26;i++)
        if(adj[src][i] && !vis[i])
            DFS(i);
    return;
}

void checkConnection(int src){
    int i;
    if(euler)DFS(src);
    for(i=0;i<26;i++){
        if(alph[i] && !vis[i]){
            euler = 0;
            break;
        }
    }
}

int main(){
    int N, W, i;
    int len, s, src, tar;
    int srccnt, tarcnt;
    char str[1010];

    scanf("%d", &N);
    while(N--){
        initialize();
        memset(alph, 0, sizeof(alph));
        srccnt = tarcnt = 0;
        scanf("%d", &W);
        for(i=0;i<W;i++){
            scanf("%s", str);
            len = strlen(str);
            adj[str[0]-'a'][str[len-1]-'a']++;
            in[str[len-1]-'a']++;
            out[str[0]-'a']++;
            alph[str[0]-'a'] = alph[str[len-1]-'a'] = 1;
        }

        for(i=0;i<26;i++){
            if(alph[i]) s = i;
            if(out[i]-in[i]==1){
                src = i;
                srccnt++;
                if(srccnt>1){
                    euler = 0;
                    break;
                }
            }
            else if(in[i]-out[i]){
                tar = i;
                tarcnt++;
                if(tarcnt>1){
                    euler = 0;
                    break;
                }
            }
            else if(out[i]!=in[i]) euler = 0;
        }
        if(!(srccnt==0 && tarcnt==0) && !(srccnt==1 && tarcnt==1)) euler=0;
        if(srccnt==0) src = s;

        if(euler)checkConnection(src);
        if(euler!=1) printf("The door cannot be opened.\n");
        else printf("Ordering is possible.\n");
    }

    return 0;
}
