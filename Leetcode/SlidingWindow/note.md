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

### [最大平均数](https://leetcode.cn/problems/maximum-average-subarray-i/description/) <Badge type="tip" text="已解决" />


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

### [半径为k的子数组平均值](https://leetcode.cn/problems/k-radius-subarray-averages/) <Badge type="tip" text="已解决" />
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

### [几乎唯一子数组最大和](https://leetcode.cn/problems/maximum-sum-of-almost-unique-subarray/description/) <Badge type="tip" text="已解决" />
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


### [长度为k的子数组最大和](https://leetcode.cn/problems/maximum-sum-of-distinct-subarrays-with-length-k/description/) <Badge type="tip" text="已解决" />
最大子数组元素和，要求子数组元素互异；
- 一是`unordered_map.count(val)`辨析
- `.size()` can count the number of elements because of the `uniqueness of map`

```cpp
class Solution {
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        //思路：注意数据类型，滑动窗口，进i，更新答案，出l，注意边界
        //子数组中的所有元素 各不相同 。还是不熟悉map，搞一个无序map，利用互异性(元素各不相同），size函数，count函数erase函数
        long long ans = 0,  tmp = 0;
        unordered_map<int, int> cnt;

        for(int i = 0; i < nums.size(); i++){
            tmp += nums[i];
            cnt[nums[i]]++;
            int l = i - k + 1;
            if(l < 0) continue;
            if(cnt.size() == k)
                ans = max(ans,tmp); //ans > tmp ? ans : tmp;
            tmp -= nums[l];
            cnt[nums[l]]--;
            if(cnt[nums[l]] == 0)
                cnt.erase(nums[l]);
        }
        return ans;
    }
};
```

### [可获得最大点数](https://leetcode.cn/problems/maximum-points-you-can-obtain-from-cards/description/) <Badge type="tip" text="已解决" />
可以从左开始拿，从右边开始拿，拿到定长为k的数目的卡片，返回卡片点数可能的最大之和；痛点在于左右两边

- C++17引入的 `reduce`函数 快速计算窗口和
- 最多，想到对立面最少，转化为定长滑动窗口
- 需要意识到，左右两边都可以随机拿一张，可以想到所有的可能有哪些 
左边0个 右边k个
左边1个 右边k-1个

反面计算
```cpp
class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        //两边最大，中间最小，从0滑到n - k，最后答案要用总和减一下，另外考虑特殊情况
        //当全部都是一样的元素的时候，同上
        int ans = 1e9, tmp = 0, j = cardPoints.size() - k;
        if(j == 0) return reduce(cardPoints.begin(),cardPoints.end());
        for(int i = 0; i < cardPoints.size();i++){
            tmp += cardPoints[i];

            int l = i - j + 1;
            if(l < 0) continue;
            ans = min(ans,tmp);

            tmp -= cardPoints[l];

        }
        return reduce(cardPoints.begin(),cardPoints.end()) - ans;
    }
};
```
正面计算
```cpp
class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int s = reduce(cardPoints.begin(), cardPoints.begin() + k);
        int ans = s;
        for (int i = 1; i <= k; i++) {
            s += cardPoints[cardPoints.size() - i] - cardPoints[k - i];
            ans = max(ans, s);
        }
        return ans;
    }
};
```

## 不定长滑动窗口

### [无重复字符的最长子串](https://leetcode.cn/problems/longest-substring-without-repeating-characters/description/) <Badge type="warning" text="未解决" />
- 需要熟练运用map，重复想到set或map，连续子串想到窗口
- 要注意这些：
    - 一是连续性，abca，滑动到第二个a，删除最左边的就行
    - 二是注意这个while可以让指针连续移动，直到重复字符那里
    - 三是复杂度O（n），虽然嵌套了 while，但每个字符最多被 left 和 right 各访问一次
```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.length(), ans = 0, left = 0;
        unordered_map<char, int> cnt; // 维护从下标 left 到下标 right 的字符
        for (int right = 0; right < n; right++) {
            char c = s[right];
            cnt[c]++;
            while (cnt[c] > 1) { // 窗口内有重复字母
            //注意，这里不是用count，直接用value就行了
                cnt[s[left]]--; // 移除窗口左端点字母
                left++; // 缩小窗口
            }
            ans = max(ans, right - left + 1); // 更新窗口长度最大值
        }
        return ans;
    }
};
```

### [删掉一个元素以后全为1的最长子数组](https://leetcode.cn/problems/longest-subarray-of-1s-after-deleting-one-element/) <Badge type="tip" text="已解决" />
给你一个二进制数组 nums ，你需要从中删掉一个元素。
请你在删掉元素的结果数组中，返回最长的且只包含 1 的非空子数组的长度。
如果不存在这样的子数组，请返回 0 。

最长的子数组 - 不定长滑动窗口
用样例模拟了一下，发现： 删掉一个元素 - map中的 0 键对应的值 只能为1

那么问题转化为： 只含一个0的最长滑动窗口长度减去1，，，做的时候发现答案也可以是value（1）

```cpp
class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        //不定长滑动窗口，问题可以转化为，只含1个0的最长滑动窗口的值减去1
        //int，int型的map，
        int l = 0, ans  = 0;
        unordered_map<int,int> mp;
        for(int i = 0; i < nums.size(); i++){
            mp[nums[i]]++;

            while(mp[0] > 1){
                mp[nums[l]]--;
                l++;
            }
            
            ans = max(ans,mp[1]);
        }
        return mp[0] == 0 ? ans - 1 : ans;

    }
};
```

### [使数组平衡的最少移除数目](https://leetcode.cn/problems/minimum-removals-to-balance-array/description/) <Badge type="tip" text="已解决" />
给你一个整数数组 nums 和一个整数 k。
如果一个数组的 最大 元素的值 至多 是其 最小 元素的 k 倍，则该数组被称为是 平衡 的。
你可以从 nums 中移除 任意 数量的元素，但不能使其变为 空 数组。

返回为了使剩余数组平衡，需要移除的元素的 最小 数量。

注意：大小为 1 的数组被认为是平衡的，因为其最大值和最小值相等，且条件总是成立。
```cpp
class Solution {
public:
    int minRemoval(vector<int>& nums, int k) {
        //子数组，这个窗口是不断减小的可以先排序吧，排序之后，样例通过
        //好吧，错误，没有考虑到可以移除最小值
        //好吧，解答错误，其实也可以移除左边再右边，那么思路应该是
        //逆向思路，排好序，求符合条件的最长子数组，一旦不符合条件，左指针右移动，更新答案，
        //返回长度减去最长的子数组长度
        sort(nums.begin(),nums.end());
        int n = nums.size(),l = 0,res = 0;

        for(int i = 0; i < n; i++){
            while(nums[i] > nums[l]*(long long)k){
                l++;
            }
            res = max(res,i - l + 1);
        }
        return n - res;
    }
};
```

### [尽可能使字符串相等](https://leetcode.cn/problems/get-equal-substrings-within-budget/description/) <Badge type="warning" text="未解决" />
给两个长度相同的字符串，s 和 t。

将 s 中的第 i 个字符变到 t 中的第 i 个字符需要 |s[i] - t[i]| 的开销（开销可能为 0），也就是两个字符的 ASCII 码值的差的绝对值。

用于变更字符串的最大预算是 maxCost。在转化字符串时，总开销应当小于等于该预算，这也意味着字符串的转化可能是不完全的。

如果你可以将 s 的子字符串转化为它在 t 中对应的子字符串，则返回可以转化的最大长度。

如果 s 中没有子字符串可以转化成 t 中对应的子字符串，则返回 0。

### [水果成篮](https://leetcode.cn/problems/fruit-into-baskets/description/) <Badge type="tip" text="已解决" />
你正在探访一家农场，农场从左到右种植了一排果树。这些树用一个整数数组 fruits 表示，其中 fruits[i] 是第 i 棵树上的水果 种类 。

你想要尽可能多地收集水果。然而，农场的主人设定了一些严格的规矩，你必须按照要求采摘水果：

你只有 两个 篮子，并且每个篮子只能装 单一类型 的水果。每个篮子能够装的水果总量没有限制。
你可以选择任意一棵树开始采摘，你必须从 每棵 树（包括开始采摘的树）上 恰好摘一个水果 。采摘的水果应当符合篮子中的水果类型。每采摘一次，你将会向右移动到下一棵树，并继续采摘。
一旦你走到某棵树前，但水果不符合篮子的水果类型，那么就必须停止采摘。
给你一个整数数组 fruits ，返回你可以收集的水果的 最大 数目。

```cpp
class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        //两个篮子，试试用map的size函数吧，
        //进入map，当size>=3 左边删，左边出
        //ans = max....
        //不定长
        int l = 0, ans = 0;
        unordered_map<int,int> mp;
        for(int i = 0; i < fruits.size(); i++){
            mp[fruits[i]]++;
            while(mp.size() > 2){
                mp[fruits[l]]--;
                if(mp[fruits[l]] == 0) mp.erase(fruits[l]);
                l++;
            }
            ans = max(ans, i - l + 1);

        }
        return ans;
    }
};
```
