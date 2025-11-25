# 滑动窗口
## 定长模版：我们要计算所有长度恰好为 k 的子串中，最多可以包含多少个元音字母。
```cpp
class Solution {
public:
    int maxVowels(string s, int k) {
        //思路：右侧进入，更新答案，左侧离开,
        //初始化右侧 开始循环
        //右侧指针可以从0开始判断元音
        //左侧根据长度来的 i - k + 1,注意小于0 的情况；
        //更新答案
        //删左侧
        int ans = 0, v = 0;
        for(int i = 0; i < s.size(); i++){
            if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u') v++;

            int left = i - k + 1;
            if(left < 0) continue;

            ans = max(ans,v);

            if (s[left] == 'a' || s[left] == 'e' || s[left] == 'i' || s[left] == 'o' || s[left] == 'u') v--;

        }
        return ans;
    }
};
```

## [最大平均数](https://leetcode.cn/problems/maximum-average-subarray-i/description/)


myans:
```cpp
class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        //思路：通过循环遍历，循环i作为右侧点r，l ，不满足就继续+，满足就取最大，最后减掉左边;可以先求出和再平均；
        double tmp = 0, ans = -10000000;
        for(int i = 0; i < nums.size(); i++){
            tmp += nums[i];
            //tmp /= (double)k;
            int l = i - k + 1;
            if(l < 0) continue;
            ans = max(ans,tmp);
            tmp -= nums[l];
        }
        return ans / k;
    }
};
```
做题时遇到了以下问题：
- 当nums里面的数据为负，取max得到0;
- 写完代码一定要在脑海里模拟
根据gpt的建议，作如下修改，使得不需要定义极小值
```cpp
double tmp = 0;
for (int i = 0; i < k; i++) tmp += nums[i];
//初始化tmp和ans
double ans = tmp / k;
```

- 记住以下常量
```cpp
//求最大
int:        INT_MIN（或-2e9）
long long:  LLONG_MIN（或-1e18）
double:     -1e18（或 -inf）
//求最小
int:        INT_MAX
long long:  LLONG_MAX
double:     1e18（或 +inf）
```
对于inf，在leetcode无法添加库，所以用`double ans = -std::numeric_limits<double>::infinity();`

## [半径为k的子数组平均值](https://leetcode.cn/problems/k-radius-subarray-averages/)
- vector初始化为-1技巧
### 看懂报错
```text
Line 9: Char 17: runtime error: signed integer overflow: 2147475255 + 94243 cannot be represented in type 'int' (solution.cpp)
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior prog_joined.cpp:18:17
```
题目给的数据范围：
```text
n == nums.length
1 <= n <= 10^5
0 <= nums[i] <= 10^5
0 <= k <= 10^5
```
- 窗口大小（window_size）:
`window_size = 2 * k + 1`
- 最大情况下：
`k = 1e5   →   window_size = 200001`
- tmp 是窗口内的和：
tmp = sum(nums[l ... r])
- 最坏情况下的 tmp：
`200001 * 100000 = 2.00001 × 10^{10}   （2e10）`
- int 的上限是：
`2.147 × 10^9`

## [几乎唯一子数组最大和](https://leetcode.cn/problems/maximum-sum-of-almost-unique-subarray/description/)
>给定整数数组 `nums` 及正整数 `m`、`k`（`1 <= m <= k <= nums.length`），求长度为 `k` 且至少含 `m` 个不同元素的子数组的最大和，无此类子数组则返回 `0`。
- 此题又涉及到哈希表！
```cpp
class Solution {
public:
    long long maxSum(vector<int>& nums, int m, int k) {
        //不知道怎么判断子数组至少有m个互不相同的元素，查了一下用unordered_map，这个是互异，无序的
        //窗口先写好，然后判断的时候，用。size（）
        int ans = 0, tmp = 0;
        unordered_map<int,int> cnt;
        for(int i = 0; i < nums.size(); i++){
            tmp += nums[i];
            cnt[nums[i]]++;

            int l = i - k + 1;
            if(l < 0) continue;
            if(cnt.size() >= m) ans = max(ans,tmp);

            tmp -= nums[l];
            cnt[nums[l]]--;

        }
        return ans;
    }
};
```
这里测试样例都过了，提交错误，在脑海里模拟了一下，又想到之前查map的时候看到了一眼说要减大小，猜测是`cnt[nums[l]]--;`的问题，没有 删掉`键`。
- 使用下面代码删掉键就可以了:
```cpp
if(cnt[nums[l]]==0) cnt.erase(nums[l]);
```
不过又出现了越界，int 改成 long long;

