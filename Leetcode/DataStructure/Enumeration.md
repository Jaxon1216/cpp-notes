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