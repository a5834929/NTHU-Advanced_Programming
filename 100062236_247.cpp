#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<map>
using namespace std;
struct STR{
    char name[30];
    bool operator < (const STR &p)const{
        return strcmp(name, p.name)<0;
    }
};
STR str1, str2;
map<STR, int> M;
int adj[30][30], flag[30];
char names[30][30];

int main(){
    int t = 1, n, m, i, j, k;

    scanf("%d%d", &n, &m);
    while(1){
        M.clear(); n = 0;
        memset(adj, 0, sizeof(adj));
        memset(names, 0, sizeof(names));
        for(i=0;i<m;i++){
            scanf("%s%s", str1.name, str2.name);
            if(M.find(str1)==M.end()){
                M.insert(pair<STR, int>(str1, n));
                strcpy(names[n], str1.name);
                n++;
            }
            if(M.find(str2)==M.end()){
                M.insert(pair<STR, int>(str2, n));
                strcpy(names[n], str2.name);
                n++;
            }
            adj[M[str1]][M[str2]] = 1;
        }
        for(k=0;k<n;k++)
            for(i=0;i<n;i++)
                for(j=0;j<n;j++)
                    if(adj[i][k] && adj[k][j])
                        adj[i][j]=1;
        printf("Calling circles for data set %d:\n", t++);
        for(i=0;i<n;i++)flag[i] = 1;
        for(i=0;i<n;i++){
            if(flag[i]==1){
                flag[i] = 0;
                printf("%s", names[i]);
                for(j=i+1;j<n;j++){
                    if(adj[i][j]==1 && adj[j][i]==1){
                        flag[j] = 0;
                        printf(", %s", names[j]);
                    }
                }
                printf("\n");
            }
        }
        scanf("%d%d", &n, &m);
        if(n!=0 && m!=0)printf("\n");
        else break;
    }
    return 0;
}
