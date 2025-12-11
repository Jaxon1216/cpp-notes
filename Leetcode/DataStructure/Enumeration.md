# 枚举右，维护左

对于**双变量问题**，例如“两数之和” $a_i + a_j = t$，可以**枚举右边**的 $a_j$，将其转化为**单变量问题**：在 $a_j$ 左边查找是否存在 $a_i = t - a_j$。这种查找可以通过**哈希表**来高效实现。

我把这个技巧叫做：**枚举右，维护左**。

对于暴力解法，一般是 枚举 - 枚举+判断；
而本专题则是        枚举 - 查找

相比暴力做法，哈希表多消耗了内存空间，但减少了运行时间，这就是「空间换时间」。

问：是什么原因导致了这两种算法的快慢？

答：我用「获取了多少信息」来解释。

暴力做法每次拿两个数出来相加，和 target 比较，那么花费 O(1) 的时间，只获取了 O(1) 的信息。

而哈希表做法，每次查询都能知道 O(n) 个数中是否有 target−nums[j]，那么花费 O(1) 的时间，就获取了 O(n) 的信息。

---
## [两数之和](https://leetcode.cn/problems/two-sum/description/) <Badge type="tip" text="已解决" />
给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。
你可以假设每种输入只会对应一个答案，并且你不能使用两次相同的元素。
你可以按任意顺序返回答案。
示例 1：
输入：nums = [2,7,11,15], target = 9
输出：[0,1]
解释：因为 nums[0] + nums[1] == 9 ，返回 [0, 1] 。
- 维护左的关键————map的更新和find函数；

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> idx; // 创建一个空哈希表
        for (int j = 0; ; j++) { // 枚举 j
            // 在左边找 nums[i]，满足 nums[i]+nums[j]=target
            auto it = idx.find(target - nums[j]);
            if (it != idx.end()) { // 找到了
                return {it->second, j}; // 返回两个数的下标,注意是迭代器的first和second。
            }
            idx[nums[j]] = j; // 保存 nums[j] 和 j
        }
    }
};
```

## [好数对](https://leetcode.cn/problems/number-of-good-pairs/description/)<Badge type="tip" text="多思考" />
给你一个整数数组 nums 。

如果一组数字 (i,j) 满足 nums[i] == nums[j] 且 i < j ，就可以认为这是一组 好数对 。

返回好数对的数目。

- 特征1:j之前的每个数字出现的频次需要记录
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

## [配对问题](https://leetcode.cn/problems/largest-positive-integer-that-exists-with-its-negative/description/)<Badge type="tip" text="常复习" />
给你一个 不包含 任何零的整数数组 nums ，找出自身与对应的负数都在数组中存在的最大正整数 k 。

返回正整数 k ，如果不存在这样的整数，返回 -1 。
示例 1：
输入：nums = [-1,2,-3,3]
输出：3
解释：3 是数组中唯一一个满足题目要求的 k 
- 特征：检查存在
- 特征：配对问题，，如果用map把负数变成正数，会导致信息丢失；
- O（1）查找
立刻想到set
```cpp
class Solution {
public:
    int findMaxK(vector<int>& nums) {
        unordered_set<int> s(nums.begin(), nums.end());
        int ans = -1;
        for (int num : nums) {
            if (num > 0 && s.count(-num)) {
                ans = max(ans, num);
            }
        }
        return ans;
    }
};
```

## [买股票最佳时机](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/)<Badge type="tip" text="学优化" />
- 特征：遍历+查询
```cpp
class Solution {
public:
    //我的时间复杂度是nlogn
    /*
     //特征：左侧最好有顺序，不能当天买卖，map
    //遍历，更新答案，set存储
    int ans = 0;
    set<int> st;
    for(int j = 0; j < prices.size(); j++){
        if(!st.empty()) {
        auto it = st.begin();
        ans = max(ans,prices[j]- *it);
        }
        st.insert(prices[j]);
    }
    return ans;
    */
//先更新答案再维护最小值，可以保证遍历到的数字在最小值之后；
    int maxProfit(vector<int>& prices) {
        int ans = 0;
        int min_price = prices[0];
        for (int p : prices) {
            ans = max(ans, p - min_price);
            min_price = min(min_price, p);
        }
        return ans;
    }
};
```


## [](https://leetcode.cn/problems/maximum-distance-in-arrays/description/)<Badge type="tip" text="常复习" />
给定 m 个数组，每个数组都已经按照升序排好序了。

现在你需要从两个不同的数组中选择两个整数（每个数组选一个）并且计算它们的距离。两个整数 a 和 b 之间的距离定义为它们差的绝对值 |a-b| 。
- 特征：当前的最值受到之前的最值的影响，所以需要维护左边
- 掌握：二元数组的遍历，贪心思想
- Max函数
- 假如这个二元数组的每个行数组没有顺序排列怎么办？
```cpp
for (auto &row : arrays) {
    sort(row.begin(), row.end());
}
```
我的错误答案
```cpp
class Solution {
public:
    int maxDistance(vector<vector<int>>& arrays) {
        //特征：二维，遍历时需维护前面的
        //初始化mintmp，maxtmp，
        // for遍历，ans = 当前最大 - 历史最小，or abs（当前最小 - 历史最大），更新历史
        int ans = 0,mintmp = arrays[0].front(),maxtmp = arrays[0].back();
        for(auto& v : arrays){
            ans = max(abs(v.front()-maxtmp),v.back()-mintmp,ans);
            maxtmp = max(maxtmp,v.back());
            mintmp = min(mintmp,v.front());
        }
        return ans;
    }
};
/usr/lib/gcc/x86_64-linux-gnu/14/../../../../include/c++/14/bits/stl_algobase.h:306:11: error: called object type 'int' is not a function or function 
```
第一点（两选一）默认的取max只能两个数比较
```text
① 两两取 max（最常见）
ans = max(ans, max(abs(v.front()-maxtmp), v.back()-mintmp));
② 用 initializer_list 版本（C++11+）
这个更简洁：
ans = max({ans, abs(v.front()-maxtmp), v.back()-mintmp});
```
第二点，更新逻辑可能会让第一组的值变成答案
```cpp
    for (int i = 1; i < arrays.size(); i++) {
```