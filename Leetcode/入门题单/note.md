## `vector` 初始化误区

```cpp
// ❌ 错误：空vector不能直接用[]赋值
vector<double> vec;
vec[0] = 3.14;  // 运行时错误！

// ✅ 方法1: 指定大小
vector<double> vec(5);
vec[0] = 3.14;  // 正确

// ✅ 方法2: push_back
vector<double> vec;
vec.push_back(3.14);  // 正确

// ✅ 方法3: 初始化列表
vector<double> vec = {3.14, 2.71};  // 正确
```

## [输出2和n的最小公倍数](https://leetcode.cn/problems/smallest-even-multiple/solutions/1831561/yi-xing-gong-shi-by-endlesscheng-ixss/?envType=study-plan-v2&envId=primers-list)
>我就直接用循环模拟了

- 我居然没想到，n为奇答案就是2*n，n为偶答案就是n；但是这个优雅的写法我还是写不出来哈
```cpp
class Solution {
public:
    int smallestEvenMultiple(int n) {
        return (n % 2 + 1) * n;
    }
};
```

## 位运算符
在 C++ 中，有三个主要的位运算符，我来详细解释一下：

三个主要位运算符：

### 1. **按位与 (AND)** - `&`
```cpp
int a = 5;    // 二进制: 0101
int b = 3;    // 二进制: 0011
int result = a & b;  // 结果: 0001 (十进制 1)
```

### 2. **按位或 (OR)** - `|`
```cpp
int a = 5;    // 二进制: 0101
int b = 3;    // 二进制: 0011
int result = a | b;  // 结果: 0111 (十进制 7)
```

### 3. **按位异或 (XOR)** - `^`
```cpp
int a = 5;    // 二进制: 0101
int b = 3;    // 二进制: 0011
int result = a ^ b;  // 结果: 0110 (十进制 6)
```

## 位运算的简单应用：

```cpp
// 检查奇偶性
bool isEven = (num & 1) == 0;  // 与1进行AND运算

// 乘以2的幂次
int multiplyBy8 = num << 3;    // 左移3位相当于乘以8

// 除以2的幂次
int divideBy4 = num >> 2;      // 右移2位相当于除以4
```

## [统计好数对](https://leetcode.cn/problems/number-of-good-pairs/description/?envType=study-plan-v2&envId=primers-list)
题意
统计满足 `i<j` 且 `nums[i]=nums[j]` 的数对个数

- 我的思路直接是二重循环。。O(n^2)复杂度
- 哈希表，O（n）复杂度
```cpp
class Solution {
public:
    int numIdenticalPairs(vector<int>& nums) {
        int ans = 0;
        unordered_map<int, int> cnt;
        for (int x : nums) { // x = nums[j]
            // 此时 cnt[x] 表示之前遍历过的 x 的个数，加到 ans 中
            // 如果先执行 cnt[x]++，再执行 ans += cnt[x]，就把 i=j 这种情况也统计进来了，算出的答案会偏大
            ans += cnt[x];
            cnt[x]++;
        }
        return ans;
    }
};
```
注意到：
当 cnt[x] 中的 x 第一次出现时：
会自动创建键 x
值会被初始化为 0（对于 int 类型）


## [统计好三元数组](https://leetcode.cn/problems/count-good-triplets/description/?envType=study-plan-v2&envId=primers-list)
题意：找出有多少种以下情况：i < j < k,并且arr[i]。。。。满足相关条件

- 我还是只会暴力O(n^3)复杂度，学一下灵神的前缀和
