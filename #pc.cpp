#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<vector>
using namespace std;
int in[30], out[30], have[30];
int euler = 1, wOrder[2010];
char order[2020];
int o1, o2;
vector<int> V[30], A[30];
typedef struct W{
    char str[30];
    int done;
}WORD;
WORD word[1010];
int wordn;

int cmp(const void*p, const void*q){
    WORD a=*(WORD*)p, b=*(WORD*)q;
    if(strcmp(a.str, b.str)<0)return -1;
    else if(strcmp(a.str, b.str)>0) return 1;
    return 0;
}

void initialize(){
    int i;
    for(i=0;i<30;i++){
        V[i].clear();
        A[i].clear();
    }
    memset(in, 0, sizeof(in));
    memset(out, 0, sizeof(out));
    memset(have, 0, sizeof(have));
    memset(order, 0, sizeof(order));
    memset(wOrder, 0, sizeof(wOrder));
    o1 = o2 = wordn = 0;
}

void DFS(int src){
    int i, next;
    order[o1++] = src+'a';
    for(i=0;i<V[src].size();i++){
        next = V[src][i];
        if(in[next]){
            out[src]--;
            in[next]--;
            DFS(next);
        }
    }
}

void checkComp(int src){
    int i;
    DFS(src);
    for(i=0;i<26;i++){
        if(have[i] && (out[i] || in[i])){
            euler = 0;
            break;
        }
    }
}

int main(){
    int T, S, i, j, len;
    int src, tar, srccnt, tarcnt, _src;
    char s[30], c1, c2;

    scanf("%d", &T);
    while(T--){
        scanf("%d", &S);
        initialize();
        for(i=0;i<S;i++){
            scanf("%s", s);
            out[s[0]-'a']++;
            in[s[strlen(s)-1]-'a']++;
            V[s[0]-'a'].push_back(s[strlen(s)-1]-'a');
            have[s[0]-'a'] = have[s[strlen(s)-1]-'a'] = 1;
            word[wordn].done = 0;
            strcpy(word[wordn++].str, s);
        }
        qsort(word, wordn, sizeof(WORD), cmp);
        for(i=0;i<wordn;i++){
            /*printf("%d %s\n", i, word[i].str);*/
            A[word[i].str[0]-'a'].push_back(i);
            /*printf("%c push %d\n", word[i].str[0], i);*/
        }

        src = tar = srccnt = tarcnt = _src = 0;
        for(i=25;i>=0;i--){
            if(have[i]) _src = i;
            if(out[i]-in[i]==1){
                src = i;
                srccnt++;
                if(srccnt>1){
                    euler = 0;
                    break;
                }
            }
            else if(in[i]-out[i]==1){
                tar = i;
                tarcnt++;
                if(tarcnt>1){
                    euler = 0;
                    break;
                }
            }
            else if(out[i]!=in[i]) euler = 0;
            if(srccnt==0 && tarcnt!=0) src = _src;
        }
        if(euler)checkComp(src);
        if(euler){
            for(i=1;i<o1;i++){
                c1 = order[i-1];
                c2 = order[i];
                /*printf("c1 = %c  c2 = %c\n", c1, c2);*/
                for(j=0;j<A[c1-'a'].size();j++){
                    len = strlen(word[A[c1-'a'][j]].str);
                    if(word[A[c1-'a'][j]].str[0]==c1 && word[A[c1-'a'][j]].str[len-1]==c2 && word[A[c1-'a'][j]].done==0){
                        /*printf("target %s\n", word[A[c1-'a'][j]].str);*/
                        word[A[c1-'a'][j]].done = 1;
                        wOrder[o2++] = A[c1-'a'][j];
                        break;
                    }
                }
            }
            printf("%s", word[wOrder[0]].str);
            for(i=1;i<o2;i++)
                printf(".%s", word[wOrder[i]].str);
            printf("\n");

        }else printf("***\n");

    }
    return 0;
}
