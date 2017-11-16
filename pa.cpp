#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
char s[103], dir;
int drop[80][80];

int main(){
    int W, H, X, Y, x, y, i;
    int len, lost;

    scanf("%d%d", &W, &H);
    memset(drop, 0, sizeof(drop));
    while(scanf("%d%d", &X, &Y)!=EOF){
        x = X, y = Y;
        scanf("%s", s);
        dir = s[0];
        lost = 0;
        scanf("%s", s);
        len = strlen(s);
        for(i=0;i<len;i++){
            if(dir=='E'){
                if(s[i]=='R')dir = 'S';
                else if(s[i]=='L') dir = 'N';
                else{
                    x++;
                    if(x>W && !drop[W][y]){
                        lost = 1;
                        x--;
                        drop[W][y] = 1;
                        break;
                    }
                    if(x>W && drop[W][y]) x--;
                }
            }
            else if(dir=='W'){
                if(s[i]=='R')dir = 'N';
                else if(s[i]=='L') dir = 'S';
                else{
                    x--;
                    if(x<0 && !drop[0][y]){
                        lost = 1;
                        x++;
                        drop[0][y] = 1;
                        break;
                    }
                    if(x<0 && drop[0][y]) x++;
                }
            }
            else if(dir=='N'){
                if(s[i]=='R')dir = 'E';
                else if(s[i]=='L') dir = 'W';
                else{
                    y++;
                    if(y>H && !drop[x][H]){
                        lost = 1;
                        y--;
                        drop[x][H] = 1;
                        break;
                    }
                    if(y>H && drop[x][H]) y--;
                }
            }
            else if(dir=='S'){
                if(s[i]=='R')dir = 'W';
                else if(s[i]=='L') dir = 'E';
                else{
                    y--;
                    if(y<0 && !drop[x][0]){
                        lost = 1;
                        y++;
                        drop[x][0] = 1;
                        break;
                    }
                    if(y<0 && drop[x][0]) y++;
                }
            }

        }
        if(lost)printf("%d %d %c LOST\n", x, y, dir);
        else printf("%d %d %c\n", x, y, dir);
    }
    return 0;
}
