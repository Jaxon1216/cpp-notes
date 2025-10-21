#include<iostream>
using namespace std;
int main(){
    int n,k;
    vector<int> people;
    vector<int> result;
    int cnt=0,pos=0;
    cin >> n >> k;
    for(int i = 0; i < n; i++) people.push_back(i+1);

    while(!people.empty()){
        cnt++;
        if(cnt == k){
            result.push_back(people[pos]);
            people.erase(people.begin()+pos);//删除当前位置的人，注意写法
            cnt = 0;
        }
        else{ //没报到k
            pos++;
            if(pos >=people.size()) pos = 0;
        }
    }

    for(int i = 0; i < result.size(); i++){
        cout << result[i];
        if(i != result.size() - 1) cout << " ";
    }
    return 0;
}