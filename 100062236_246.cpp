#include<cstdio>
#include<cstring>
#include<deque>
#include<map>
using namespace std;

deque<int> card[8], curState;
map<deque<int>, int> stateMap;
int deal, result, emp[8];

void Init(){
    int i;
    for(i=0;i<8;i++)card[i].clear();
    stateMap.clear();
    deal=0;
    result=-1;
    memset(emp, 0, sizeof(emp));
}

void setState(){
    stateMap.insert(pair<deque<int>,int>(curState, 1));
}

void dealCard(int cur){
    deal++;
    card[cur].push_back(card[0].front());
    card[0].pop_front();
}

int checkSum(int cur){
    int sum=0;
    if(card[cur].size()<3){
        return 0;
    }
    sum = card[cur].front()+card[cur].at(1)+card[cur].back();
    if(sum==10 || sum==20 || sum==30){
        card[0].push_back(card[cur].front()), card[cur].pop_front();
        card[0].push_back(card[cur].front()), card[cur].pop_front();
        card[0].push_back(card[cur].back()), card[cur].pop_back();
        if(card[cur].size()==0)emp[cur]=1;
        return 1;
    }
    sum = card[cur].front()+card[cur].at(card[cur].size()-2)+card[cur].back();
    if(sum==10 || sum==20 || sum==30){
        card[0].push_back(card[cur].front()), card[cur].pop_front();
        card[0].push_back(card[cur].at(card[cur].size()-2));
        card[0].push_back(card[cur].back()), card[cur].pop_back();
        card[cur].pop_back();
        if(card[cur].size()==0)emp[cur]=1;
        return 1;
    }
    sum = card[cur].at(card[cur].size()-3)+card[cur].at(card[cur].size()-2)+card[cur].back();
    if(sum==10 || sum==20 || sum==30){
        card[0].push_back(card[cur].at(card[cur].size()-3));
        card[0].push_back(card[cur].at(card[cur].size()-2));
        card[0].push_back(card[cur].back()), card[cur].pop_back();
        card[cur].pop_back();
        card[cur].pop_back();
        if(card[cur].size()==0)emp[cur]=1;
        return 1;
    }
    return 0;
}

int checkState(){
    int i, j;
    curState.clear();
    for(i=0;i<8;i++){
        for(j=0;j<card[i].size();j++)
            curState.push_back(card[i].at(j));
        curState.push_back(card[i].size());
    }
    if(stateMap.find(curState)!=stateMap.end()) return 1;
    return 0;
}

int checkResult(){
    int i;
    if(card[0].size()==0)return 2;
    for(i=1;i<8;i++)
        if(card[i].size())return 0;
    return 1;
}

int main(){
    int i, x;

    while(scanf("%d", &x)!=EOF && x){
        Init();
        card[0].push_back(x);
        for(i=1;i<52;i++){
            scanf("%d", &x);
            card[0].push_back(x);
        }
        i=1;
        while(1){
            dealCard(i);
            while(checkSum(i));
            if(checkState()){
                result=0;
                break;
            }
            setState();
            result = checkResult();
            if(result) break;
            i++, i%=8;
            if(i==0)i=1;
            while(emp[i]){
                i++, i%=8;
                if(i==0)i=1;
            }
        }
        if(result==1)printf("Win : %d\n", deal);
        else if(result==2)printf("Loss: %d\n", deal);
        else if(result==0)printf("Draw: %d\n", deal);
    }
    return 0;
}
