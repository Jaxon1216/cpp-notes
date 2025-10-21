## PTA 十月刷题

- **目录**:
  - [题目：约瑟夫环](#题目约瑟夫环)

---

### 题目：约瑟夫环

- **简介**: 经典约瑟夫环问题。输入 `n` 和 `k`，按照报数 `k` 出局，记录每一轮出局顺序。
- 暴力
```cpp
#include<iostream>
#include<vector>
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
//当最后一个人出局时：
// people 删除最后一个元素后变成空数组
// 但代码继续执行 if (index >= people.size())
// people.size() 返回 0，index 可能是任何值
// 程序不会立即崩溃，但逻辑错误
        if(people.size() == 0) break;
        if(pos >= people.size()) pos = 0;
        }

        else{ //没报到k
            pos++;
            if(pos >= people.size()) pos = 0;
        }
    }

    for(int i = 0; i < result.size(); i++){
        cout << result[i];
        if(i != result.size() - 1) cout << " ";
        else cout << endl;
    }
    return 0; 
}
```
- 数学方法
```cpp
//引入数学方法，解决约瑟夫环问题
// 基础情况：
// 当 n=1 时：f(1, k) = 0（只有一个人，他肯定是幸存者）
// 递推关系：
// 第一轮出局的位置是：(k-1) % n
// 剩下 n-1 个人，重新编号：
// 原来的 (k % n) 号变成新的 0 号
// 原来的 (k+1) % n 号变成新的 1 号
// ...
// 所以：f(n, k) = (f(n-1, k) + k) % n

    int pos = 0;  // 当前位置（从0开始编号）
    
    for (int i = n; i >= 1; i--) {
        // 计算当前轮出局的人的位置
        pos = (pos + k - 1) % i;
        
        // 将位置转换为实际编号（从1开始）
        result.push_back(pos + 1);
        
        // 注意：这里我们不需要实际删除，因为数学上已经处理了
    }
    
```
