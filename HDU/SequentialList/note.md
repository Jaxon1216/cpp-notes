## 目录
- [顺序表模版](#顺序表模版)
- [HDU 基础题](#hdu-基础题)
- [Leetcode 数组操作](#leetcode-数组操作)

## 顺序表模版

### [顺序表实现](Sqlisttmp.cpp)

## 思路
- `elements` 的类型是 `eletype*`，它是“指针变量”，本身只存地址，不是数组。
- `new` 申请内存，`delete[]` 释放内存。
- 扩容机制：申请新内存 -> 拷贝旧数据 -> 释放旧内存 -> 指向新内存。

## 代码

```cpp
//增删改查
#include<iostream>
using namespace std;

#define eletype int 
//便于修改：如果以后想把元素类型从 int 改为 double，只需要改一行

struct Sequentiallist{
    /* =====================【要点1｜显眼说明】===================== 
       elements 的类型是 eletype*，它是“指针变量”，本身只存地址，不是数组。
       之所以能写 elements[i]，是因为第19行 new 之后，它会指向一段
       “连续的 eletype 元素内存”，下标运算只是“指针 + 偏移”的语法糖。
       区别提醒：
       - sizeof(elements) 得到的是指针大小（通常8字节），不是数组大小；
       - 指针可以被重新赋值（指向别处），数组名在作用域内不可被重新赋值。
       ========================================================= */
    eletype *elements;

    int size; 
    int capacity; 
    //size ≤ capacity，当size达到capacity时需要扩容
};

void initializelist(Sequentiallist *list, int capacity){
    list->elements = new eletype[capacity];
    /* =====================【要点2｜显眼说明】===================== 
       在堆上申请了 “capacity 个 eletype 的连续内存”，并把“首地址”赋给 elements。
       注意：像 int 这类内置类型，new[] 默认不清零；若需清零可写 new eletype[capacity]();
       访问指针指向的结构体成员用 ->；若 list 是对象本身（非指针）则用 .
       ========================================================= */

    list->size = 0;
    list->capacity = capacity;
}

void destroylist(Sequentiallist *list){
    // 【要点4】delete[] 释放的是 elements 当前指向的“数组内存”，不是指针变量本身
    delete[] list->elements;
    list->elements = nullptr; // 置空，避免悬空指针被误用
    list->size = 0;
    list->capacity = 0;
}

int size(Sequentiallist *list){
    return list->size;
}

int isempty(Sequentiallist *list){
    return list->size == 0;
}

void insert(Sequentiallist *list, int index, eletype element){
    if(index < 0 || index > list->size) throw std::invalid_argument("invalid index");
    //throw 抛出异常，用throw更加优雅，健壮，安全。

    if(list->size == list->capacity){
        int newcapacity = list->capacity * 2;
        //如果当前容量不够，则扩容
        
        /* =====================【要点3｜显眼说明｜扩容三步】=====================
           1) 先申请“新数组内存”（一排新的连续柜子）
           2) 再把“旧数组里的数据”逐个搬过去（拷贝内容）
           3) 最后把 elements 这个“指针标签”改贴到新数组（改指向，不拷贝内容）
           解释：newelements 与 list->elements 都是 eletype*，类型相同，只是指向不同内存。
           - 下方 for 循环：拷贝的是“内容”
           - list->elements = newelements;：只是“改指向”，完全不搬内容
           （等价写法：可用 std::copy 或 std::memcpy 来替代手写 for）
           ================================================================ */
        eletype *newelements = new eletype[newcapacity]; // 1) 申请新内存
        for(int i = 0; i < list->size; i++)              // 2) 拷贝旧内容到新内存
            newelements[i] = list->elements[i];
        delete[] list->elements;                          // 释放旧内存（不是删指针变量）
        list->elements = newelements;                     // 3) 改指向到新内存
        list->capacity = newcapacity;
    }

    for(int i = list->size; i > index; i--)
        list->elements[i] = list->elements[i-1];
    list->elements[index] = element;
    list->size++;
}

void deleteElement(Sequentiallist *list, int index){
    if(index < 0 || index >= list->size) throw std::invalid_argument("invalid index");
    for(int i = index; i < list->size - 1; i++)
        list->elements[i] = list->elements[i+1];
    list->size--;
}

int findElement(Sequentiallist *list, eletype element){
    for(int i = 0; i < list->size; i++)
        if(list->elements[i] == element) return i;
    return -1;
}

eletype getElement(Sequentiallist *list, int index){
    if(index < 0 || index >= list->size) throw std::invalid_argument("invalid index");
    return list->elements[index];
}

eletype updateElement(Sequentiallist *list, int index, eletype value){
    if(index < 0 || index >= list->size) throw std::invalid_argument("invalid index");
    list->elements[index] = value;
}
```

## HDU 基础题

### [HDU 2006. 求奇数的乘积](http://acm.hdu.edu.cn/showproblem.php?pid=2006)

## 题意

给你n个整数，求他们中所有奇数的乘积。

## 思路

- 顺序表实现，遍历判断 `x % 2 == 1`，累乘。

## 代码

```cpp
//比较快的
int a[1000];
int main(){
    int n;
    while(cin >> n){

        for(int i = 0; i < n; i++) {
            int x;
            cin >> x;
            a[i] = x;
        }
        int pro = 1;
        for(int i = 0; i < n; i++){
            if(a[i] % 2 == 1) pro *= a[i];
        }
        cout << pro << endl;
    }
    return 0;

}
//模版思维，比赛可以打印带进去，细节不易出错。
```

### [HDU 2008. 数值统计](http://acm.hdu.edu.cn/showproblem.php?pid=2008)

## 题意

统计给定的n个数中，负数、零和正数的个数。

## 思路

- 遍历统计，注意浮点数比较。

## 代码

```cpp
int main(){
    int n;
    while(cin >> n && n != 0){//不能是0个数
        Sequentiallist l;
        initializelist(&l,n);
        for(int i = 0; i < n; i++) {
            double x;
            cin >> x;
            insert(&l,i,x);
        }
        int neg = 0, zero = 0, pos = 0;
        for(int i = 0; i < n; i++){
            if(getElement(&l,i) < 0) neg++;
            else if(getElement(&l,i) == 0) zero++;
            else pos++;
        }
        cout << neg << " " << zero << " " << pos << endl;
        destroylist(&l);
    }
    return 0;
}
```

### [HDU 2014. 青年歌手大奖赛_评委会打分](http://acm.hdu.edu.cn/showproblem.php?pid=2014)

## 题意

得分规则为去掉一个最高分和一个最低分，然后计算平均得分。

## 思路

- 遍历找 max 和 min，求和 `sum`，最后 `(sum - max - min) / (n - 2)`。
- `iomanip` 控制输出精度 `fixed << setprecision(2)`。

## 代码

```cpp
int main(){
    int n;
    while(cin >> n && n != 0){//不能是0个数
        Sequentiallist l;
        initializelist(&l,n);
        for(int i = 0; i < n; i++) {
            double x;
            cin >> x;
            insert(&l,i,x);
        }
        double sum = 0, max = -1e9, min = 1e9;
        for(int i = 0; i < n; i++){
            double a = getElement(&l,i);
            sum += a;
            if(a > max) max = a;
            if(a < min) min = a;
        }
        cout << fixed << setprecision(2) << (sum - max - min) / (n - 2) << endl;
        destroylist(&l);
    }
    return 0;
}
```

## Leetcode 数组操作

### [2859. 计算 K 置位下标对应元素的和](https://leetcode.cn/problems/sum-of-values-at-indices-with-k-set-bits/description/) <Badge type="tip" text="已解决" />

## 题意

给你一个下标从 0 开始的整数数组 nums 和一个整数 k 。
请你用整数形式返回 nums 中的特定元素之 和 ，这些特定元素满足：其对应下标的二进制表示中恰存在 k 个置位。

## 思路

- `__builtin_popcount(index)` 计算二进制中 1 的个数。

## 代码

```cpp
class Solution {
    public:
        int sumIndicesWithKSetBits(vector<int>& nums, int k) {
            int result = 0;
            for (int index = 0; index < (int)nums.size(); ++index) {
                if (__builtin_popcount(index) == k) {
                    result += nums[index];
                }
            }
            return result;
        }
};
```

### [3158. 求出出现两次数字的 XOR 值](https://leetcode.cn/problems/find-the-xor-of-numbers-which-appear-twice/description/) <Badge type="tip" text="已解决" />

## 题意

给你一个数组 nums ，数组中的数字 要么 出现一次，要么 出现两次。
请你返回数组中所有出现两次数字的按位 XOR 值，如果没有数字出现过两次，返回 0 。

## 思路

- 用位集 visited 记录“是否出现过”。第 i 位代表数值 i。
- 若 `(visited & (1<<x))` 非 0，说明 x 之前已出现，现在是第二次 => `ans ^= x`。
- 否则首次出现 => `visited |= (1<<x)`。
- 注意 `1LL << x` 防止溢出。

## 代码

```cpp
class Solution {
    public:
        int xorOperation(vector<int>& nums) {
            int ans = 0;
            long long visited = 0 ;
            for(int i = 0; i < nums.size(); i++){
                if(visited & ((long long)1<<nums[i])){
                    ans ^= nums[i];
                }
                else visited |= ((long long)1<<nums[i]);// ｜ 有1则1
            }
            return ans;
        }
    }; 
```

### [2341. 数组能形成多少数对](https://leetcode.cn/problems/maximum-number-of-pairs-in-array/description/) <Badge type="tip" text="已解决" />

## 题意

从 nums 选出 两个 相等的 整数，从 nums 中移除这两个整数，形成一个 数对。
返回一个下标从 0 开始、长度为 2 的整数数组 answer 作为答案，其中 answer[0] 是形成的数对数目，answer[1] 是对 nums 尽可能执行上述操作后剩下的整数数目。

## 思路

- 暴力法：双重循环查找匹配，用 bool 数组标记已使用的元素。
- 更好的方法：哈希表计数，`cnt / 2` 是对数，`cnt % 2` 是剩余。

## 代码

```cpp
class Solution {
    public:
        vector<int> numberOfPairs(vector<int>& nums) {
            bool a[100] = {0};
            int cnt = 0;
            for(int i = 0 ; i < nums.size(); i++){
                for(int j = 0; j < i ;j++){
                    if(a[j]) continue;
                    if(nums[i]==nums[j]){
                        a[j]= a[i] = 1 ;
                        cnt++;
                        break;
                    }
                }
                
            }

            return {cnt,nums.size()-2*cnt};
        }
};
```

### [119. 杨辉三角 II](https://leetcode.cn/problems/pascals-triangle-ii/description/) <Badge type="tip" text="已解决" />

## 题意

给定一个非负索引 rowIndex，返回「杨辉三角」的第 rowIndex 行。

## 思路

- 二维数组模拟：`y[i][j] = y[i-1][j-1] + y[i-1][j]`。
- 滚动数组优化（一维数组从后往前更新）。

## 代码

```cpp
class Solution {
    public:
        vector<int> getRow(int rowIndex) {
            int y[34][34];
            for(int i = 0; i <= rowIndex; i++){
                for(int j = 0; j <= i ; j++) {
                    if(j==0||j==i) y[i][j] = 1;
                    else y[i][j] = y[i-1][j-1]+y[i-1][j];
                }
            }
            vector<int>ans;
            for(int i = 0; i <= rowIndex; i++) ans.push_back(y[rowIndex][i]);
            return ans;
        }
};
```

### [LCP 01. 猜数字](https://leetcode.cn/problems/guess-numbers/description/) <Badge type="tip" text="已解决" />

## 题意

小A 和 小B 在玩猜数字游戏。小B 每次从 1, 2, 3 中随机选择一个数字，小A 也从 1, 2, 3 中选择一个数字进行猜测。他们一共进行三次这个游戏。请返回 小A 猜对了几次？

## 思路

- 遍历比较 `guess[i] == answer[i]`。

## 代码

```cpp
class Solution {
    public:
        int game(vector<int>& guess, vector<int>& answer) {//标记
            int cnt = 0;
            for(int i = 0; i < 3; i++){
                if(guess[i] == answer[i]) cnt++;
            }
            return cnt;
        }
};
```

### [27. 移除元素](https://leetcode.cn/problems/remove-element/description/) <Badge type="tip" text="已解决" />

## 题意

给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素。元素的顺序可能发生改变。然后返回 nums 中与 val 不同的元素的数量。

## 思路

- 双指针：左指针指向待处理位置，右指针指向待检查元素。
- 或者双向指针：左边找等于val的，右边找不等于val的，交换。

## 代码

```cpp
class Solution {
    public:
        int removeElement(vector<int>& nums, int val) {
            int l=0, r=nums.size()-1;
            while(l <= r){
                if(nums[l] == val){
                    int tmp = nums[l];
                    nums[l] = nums[r];
                    nums[r] = tmp;
                    r--;
                }
                else l++;
            }
            return l;
        }
    };
```

