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
题意：找出有多少种以下情况：i < j < k,并且对应的值。。。。满足相关条件。

- 我还是只会暴力O(n^3)复杂度，学一下[前缀和](https://oiwiki.com/basic/prefix-sum/)
前缀和定义为：\( S_i = \sum_{j=1}^{i} a_j \)

递推关系式为：
- \( S_0 = 0 \)
- \( S_i = S_{i-1} + a_i \)

计算区间 \([l, r]\) 的和，只需用前缀和相减：
- \( S([l, r]) = S_r - S_{l-1} \)

通过 \(O(n)\) 时间预处理前缀和数组，可以将单次区间和查询的复杂度降至 \(O(1)\)。
```cpp
class Solution {
public:
    int countGoodTriplets(vector<int>& arr, int a, int b, int c) {
        int n = arr.size(), mx = ranges::max(arr);
        vector<int> count(mx+ 1, 0); //表示值v出现次数
        // prefix[v] 表示值 ≤ v 的元素个数
        vector<int> prefix(mx + 2, 0);
        int ans = 0;

        for (int j = 0; j < n; j++) {
            // 对于每个 j，枚举所有 k > j
            for (int k = j + 1; k < n; k++) {
                // 先检查 |arr[j] - arr[k]| ≤ b
                if (abs(arr[j] - arr[k]) <= b) {
                    // 确定 i 的取值范围
                    int left = max({arr[j] - a, arr[k] - c, 0});
                    int right = min({arr[j] + a, arr[k] + c, mx});
                    
                    // 如果范围有效，计算范围内有多少个元素
                    if (left <= right) {
                        // prefix[right+1] - prefix[left] 就是值在 [left, right] 内的元素个数
                        ans += prefix[right + 1] - prefix[left];
                    }
                }
            }
            
            // 处理完当前 j 的所有 k 后，把 arr[j] 加入统计
            // 这样保证后续的 j 能看到当前 j 的元素
            count[arr[j]]++;
            
            // 更新前缀和数组
            prefix[0] = 0;
            for (int v = 1; v <= mx + 1; v++) {
                prefix[v] = prefix[v - 1] + count[v - 1];
            }
        }
        
        return ans;
    }            
};

```
更新时机
在 j 循环中，先处理所有 k > j
然后才把 arr[j] 加入计数
这样保证处理 (j, k) 时，统计的是 j 之前的元素

## [各位数字和](https://leetcode.cn/problems/add-digits/description/?envType=study-plan-v2&envId=primers-list)
>题意: 给定一个非负整数 num，反复将各个位上的数字相加，直到结果为一位数。返回这个结果。
- 还是只会用循环，来看看O（1）做法：
比如 num = 678，计算过程为：

```
678 → 6 + 7 + 8 = 21 → 2 + 1 = 3
```

思考：从 678 到 21，减少了多少？  
计算如下：

```
678 - 21
= (600 + 70 + 8) - (6 + 7 + 8)
= (600 - 6) + (70 - 7) + (8 - 8)
= 6 × (100 - 1) + 7 × (10 - 1)
= 6 × 99 + 7 × 9
```

因为 99 和 9 都是 9 的倍数，所以每次减少的总是 9 的倍数。

从 21 到 3 也是同理，减少量为 9 的倍数。

因此，不断地将 num 各位相加，相当于不断减去 9 的倍数，直到变为一位数。  
这其实和「余数」的概念很接近：

- 从 num 不断地减去 9，直到结果小于 9，这个结果就是 `num % 9` 的值。

特殊情况：
- 如果 num == 0，结果就是 0；
- 如果 num 是 9 的倍数（且 num > 0），最终会得到 9；

所以可以总结为：

- 如果 num == 0，返回 0；
- 如果 num % 9 == 0，返回 9；
- 否则返回 num % 9。

则可以直接用公式：
```
(num - 1) % 9 + 1
```

## [2的幂](https://leetcode.cn/problems/power-of-two/description/?envType=study-plan-v2&envId=primers-list)
题意：
给你一个整数 n，请你判断该整数是否是 2 的幂次方。如果是，返回 true ；否则，返回 false 。
如果存在一个整数 x 使得 n == 2x ，则认为 n 是 2 的幂次方
- 我用循环，当n很大的时候，超时，找数学规律，没找出来。
- 位运算

如果 n 是 2 的幂，那么它的二进制形式非常特殊：最左侧是 1，其余全为 0，例如：
（除2取余）
- 4 = 100₂
- 8 = 1000₂
- 16 = 10000₂

（下文二进制省略下标）

如果 n 是 2 的幂，`n-1` 的二进制会将最高位的 1 变为 0，其余位变为 1，因此 `n & (n-1)` 一定等于 0。

**示例：**
```
n = 8      // 1000
n-1 = 7    // 0111
8 & 7 = 0
```

反之，如果 n 不是 2 的幂，n 的二进制中至少有两个 1，此时 n-1 不会影响最高位的 1，所以 `n & (n-1)` 一定不为 0。

**示例：**
```
n = 9      // 1001
n-1 = 8    // 1000
9 & 8 = 1000 ≠ 0
```

**结论**：

- 当 n > 0 且 `n & (n-1) == 0`，n 是 2 的幂；
- 否则，n 不是 2 的幂（n≤0 也不是）。

> 注：`n & (n-1)` 的技巧还可以用来快速去除 n 的二进制表示中的最低位 1。

```cpp
class Solution {
public:
    bool isPowerOfTwo(int n) {
        return n > 0 && (n & (n - 1)) == 0;
        //注意这个括号，优先级：算术 > 移位 > 关系 > 相等 > 位运算 > 逻辑 > 赋值
    }
};
```

## [3的幂](https://leetcode.cn/problems/power-of-three/description/?envType=study-plan-v2&envId=primers-list)
> 找3的几次方等于n
- 我的想法
    - 已知 $2^{31} \approx 2.1 \times 10^9$，$\log_{10}2 \approx 0.3$，$\log_{10}3 \approx 0.4771$，$\log_{10}7 \approx 0.8451$
    - 要求 $3^x = n \leq 2^{31}$，即 $3^x < 2 \times 10^9$，大约 $x$ 最大约等于20，保险起见可以枚举到30
    - 不能用 pow 函数，只能用循环实现
```cpp
class Solution {
public:
    bool isPowerOfThree(int n) {
        if (n <= 0) return false;
        
        long long power = 1;  // 使用 long long 防止溢出
        for (int i = 0; i <= 20; i++) {
            if (power == n) return true;
            if (power > n) break;  // 提前退出
            power *= 3;
        }
        return false;
    }
};
```

- 数论优雅版：
```cpp
class Solution {
public:
    bool isPowerOfThree(int n) {
        if (n <= 0) return false;
        
        while (n % 3 == 0) {
            n /= 3;
        }
        return n == 1;
    }
};
```

- 递归版：
```cpp
class Solution {
public:
    bool isPowerOfThree(int n) {
        if (n <= 0) return false;
        if (n == 1) return true;
        if (n % 3 != 0) return false;
        return isPowerOfThree(n / 3);
    }
};
```

- 整数限制法（可以推广到任何素数次幂）：
```cpp
class Solution {
public:
    bool isPowerOfThree(int n) {
        //计算出大概是20左右，可以测试输出，刚好报错的那个数前面就是了
        // 在 32 位有符号整数范围内，最大的 3 的幂是 3^19 = 1162261467
        // 如果 n 是 3 的幂，那么 1162261467 一定能被 n 整除
        return n > 0 && 1162261467 % n == 0;
    }
};
```

## [丑数](https://leetcode.cn/problems/ugly-number/description/?envType=study-plan-v2&envId=primers-list)

丑数 就是只包含质因数 2、3 和 5 的 正 整数。

>我的思路是：
   ```cpp
    class Solution {
    public:
        bool isUgly(int n) {
            //只包含2，3，5，，也就是只能被他们中的数整除，写循环，如果不是他们整除就false
            if(n == 1) return true;
            for(int i = 2; i*i < n; i++){
                if(n % i ==0){
                    if(n / i !=2 && n/i !=3 &&n/i!=5)return false;
                    else return true;
                }
            }
            return false;
        }
    };
    ```
错误的点就是无法处理多个相同质因数，比如8；我想的时候已经默认只分解成两位数相乘了
- 位运算优化
首先，如果 `n ≤ 0`，不符合题目正整数的要求，返回 `false`。
接下来，依次去掉 `n` 中的因子 `3`，也就是不断地把 `n` 除以 `3`，直到 `n` 不是 `3` 的倍数为止。
同理，再去掉 `n` 中的因子 `5`，就是不断地把 `n` 除以 `5`，直到 `n` 不是 `5` 的倍数为止。
最后只剩下因子 `2`，即判断 `n` 是否为 `2` 的某次幂。
```cpp
class Solution {
public:
    bool isUgly(int n) {
        if (n <= 0) {
            return false;
        }
        while (n % 3 == 0) {
            n /= 3;
        }
        while (n % 5 == 0) {
            n /= 5;
        }

        while(n % 2 == 0) n/=2;
        if(n == 1) return true;
        return false;
        //或者这三行直接写成return (n & (n - 1)) == 0;
    }
};
```

## [转置矩阵](https://leetcode.cn/problems/transpose-matrix/?envType=study-plan-v2&envId=primers-list)

> 太生疏了，错误好多；

- 二元数组计算行和列 
- 赋值or push_back();
- 错误：
```cpp
class Solution {
public:
    vector<vector<int>> transpose(vector<vector<int>>& matrix) {
        //二维数组 新建矩阵 换过去
        vector<vector<int>> ans;
        int m = matrix.size();
        for(int i = 0; i < m; i++){
            int n = matrix[i].size();
            for(int j = 0; j < n; j++){
                ans.push_back(matrix[j][i]);
            }
        }
        return ans;
    }
};
```

- right:
```cpp
class Solution {
public:
    vector<vector<int>> transpose(vector<vector<int>>& matrix) {
        int m = matrix.size();         // 行
        int n = matrix[0].size();      // 列

        vector<vector<int>> ans(n, vector<int>(m)); // n x m

        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                ans[j][i] = matrix[i][j];
            }
        }
        return ans;
    }
};
```
or
```cpp
class Solution {
public:
    vector<vector<int>> transpose(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();

        vector<vector<int>> ans(n, vector<int>());

        for (int j = 0; j < n; j++) {
            for (int i = 0; i < m; i++) {
                ans[j].push_back(matrix[i][j]);
            }
        }

        return ans;
    }
};
```

## [分割字符串](https://leetcode.cn/problems/maximum-score-after-splitting-a-string/?envType=study-plan-v2&envId=primers-list)
- 前缀和
- s.size() 位置是尾元素后面一位
我的O（n^2
```cpp
class Solution {
public:
    int maxScore(string s) {
        int ans = 0;
        for(int i = 0; i < s.size() - 1; i++){  // i从0到size()-2
            int tmp = 0;
            // 计算左子串中'0'的数量
            for(int j = 0; j <= i; j++) 
                if(s[j]=='0') tmp++;
            // 计算右子串中'1'的数量  
            for(int j = i + 1; j < s.size(); j++)  // j从i+1到size()-1
                if(s[j] == '1') tmp++;
            
            if(tmp > ans) ans = tmp;
        }
        return ans;
    }
};
```
前缀和O(n)复杂度
```cpp
class Solution {
public:
    int maxScore(string s) {
        int n = s.size();
        
        // 方法1：前缀和数组（清晰易懂）
        vector<int> prefixZero(n, 0);  // 前缀0的个数
        vector<int> prefixOne(n, 0);   // 前缀1的个数
        
        // 构建前缀和数组
        for(int i = 0; i < n; i++) {
            if(i == 0) {
                if(s[i] == '0') {
                    prefixZero[0] = 1;
                    prefixOne[0] = 0;
                } else {
                    prefixZero[0] = 0;
                    prefixOne[0] = 1;
                }
            } else {
                prefixZero[i] = prefixZero[i-1] + (s[i] == '0' ? 1 : 0);
                prefixOne[i] = prefixOne[i-1] + (s[i] == '1' ? 1 : 0);
            }
        }
        
        int totalOnes = prefixOne[n-1];
        int ans = 0;
        
        for(int i = 0; i < n - 1; i++) {
            // 左子串0的个数：prefixZero[i]
            // 右子串1的个数：totalOnes - prefixOne[i]
            int score = prefixZero[i] + (totalOnes - prefixOne[i]);
            ans = max(ans, score);
        }
        
        return ans;
    }
};
```


## [统计元音字符串](https://leetcode.cn/problems/count-the-number-of-vowel-strings-in-range/description/?envType=study-plan-v2&envId=primers-list)
> 题意：给定一个下标从 0 开始的字符串数组 words 和两个整数 left、right。

> 如果一个字符串以元音字母开头且以元音字母结尾（元音为 'a', 'e', 'i', 'o', 'u'），则称其为元音字符串。

> 返回在闭区间 [left, right] 内，words[i] 为元音字符串的数量。

- 我的屎山
```cpp
class Solution {
public:
    bool isyuan(string &s){
        int a = s.size() - 1;
        if((s[0] == 'a'||s[0] == 'e'||s[0] == 'i'||s[0] == 'o'||s[0] == 'u')&&(s[a] == 'a'||s[a] == 'e'||s[a] == 'i'||s[a] == 'o'||s[a] == 'u'))
         return true;
        return false;
    }
    int vowelStrings(vector<string>& words, int left, int right) {
        //思路：计数器，判断函数，
        int cnt = 0;
        for(int i = left; i <= right; i++){
            if(isyuan(words[i])) cnt++;
        }
        return cnt;
    }
};
```
- 灵神优雅版：
```cpp
//思路：
class Solution {
public:
    int vowelStrings(vector<string>& words, int left, int right) {
        const string vowel = "aeiou";
        int ans = 0;
        for (int i = left; i <= right; i++) {
            string& s = words[i];
            ans += vowel.find(s[0]) != string::npos &&
                   vowel.find(s.back()) != string::npos;
                   //充分利用string的迭代器
        }
        return ans;
    }
};
```
## [二分](https://leetcode.cn/problems/peak-index-in-a-mountain-array/?envType=study-plan-v2&envId=primers-list)
```cpp
class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int l = 0, r = arr.size() - 1;
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (arr[mid] < arr[mid + 1]) {  // 上升阶段
                l = mid + 1;
            } else {                        // 下降阶段
                r = mid;
            }
        }
        return l; // 或 r，二者相等
    }
};
- `int mid = l + (r - l) / 2` 为什么这样写？
可能见过更直观的写法：
```cpp
int mid = (l + r) / 2;
```

但是，这样写存在整数溢出风险。

---

**(l + r) / 2 可能溢出吗？**

是的！

假如：
- l = 2_000_000_000
- r = 2_000_000_005

那么：
- l + r = 4_000_000_005

而 `int` 最大值大约是 2147483647（约 2e9），所以 l + r 会溢出，导致 mid 计算错误。

---

**推导过程（直观理解）：**

我们想求位于 l 和 r 中间的中点 mid：

- 距离：`(r - l)`
- 中点：`mid = l + (r - l) / 2`

这样计算，与 `(l + r) / 2` 完全等价，但***可以避免溢出***。

---