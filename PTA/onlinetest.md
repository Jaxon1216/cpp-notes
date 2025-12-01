





- 超时代码
```cpp
//根据互异性，唯一性，可以用unorderedmap，
//但是每次访问都要开一个map？
//sort一下？ 哦 multimap，可以有重复的键，还是不行，
//这个不就是子鼠组么，写个函数模拟一下吧
#include<bits/stdc++.h>
using namespace std;
int getans(vector<int> &v, int a , int b){
    map<int,int> tmp;
    for(int i = a - 1; i < b; i++) tmp[v[i]]++;

    if(tmp.size() == 1) return -1;
    else return (next(tmp.begin())->first);
}
int main(){
    int n,k;
    cin >> n >> k;
    vector<int> v;
    while(n--){
        int m;
        cin>>m;
        v.push_back(m);
    }
    int m,j;
    while(k--&& cin >>m >> j){
        cout << getans(v,m,j) << endl;
    }
    return 0;
}
```