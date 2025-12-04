# 二分查找
## 模版题
题意：
给你一个按照非递减顺序排列的整数数组 nums，和一个目标值 target。请你找出给定目标值在数组中的开始位置和结束位置。
如果数组中不存在目标值 target，返回 [-1, -1]。
你必须设计并实现时间复杂度为 O(log n) 的算法解决此问题。
```cpp
class Solution {
    // lower_bound 返回最小的满足 nums[i] >= target 的下标 i
    // 如果数组为空，或者所有数都 < target，则返回 nums.size()
    // 要求 nums 是非递减的，即 nums[i] <= nums[i + 1]
    int lower_bound(vector<int>& nums, int target) {
        int left = 0, right = (int) nums.size() - 1; // 闭区间 [left, right],注意这个-1
        while (left <= right) { // 区间不为空
            int mid = left + (right - left) / 2;
            if (nums[mid] >= target) {
                right = mid - 1; // 范围缩小到 [left, mid-1]
            } else {
                left = mid + 1; // 范围缩小到 [mid+1, right]
            }
        }
        // 循环结束后 left = right+1
        // 此时 nums[left-1] < target 而 nums[left] = nums[right+1] >= target
        // 所以 left 就是第一个 >= target 的元素下标
        return left;
    }

    // 示例：在数组 [1, 3, 3, 5, 7, 9] 中查找第一个 >= 5 的位置
    // 索引：          0  1  2  3  4  5
    // 数组：         [1, 3, 3, 5, 7, 9]   target = 5
    //
    // 初始状态：
    //                 ↓              ↓
    //                [1, 3, 3, 5, 7, 9]
    //                 L              R
    //                left=0, right=5
    // 循环结束：
    //                       ↓  ↓↓
    //                [1, 3, 3, 5, 7, 9]
    //                       R  LM
    //                left=3, right=2 (left > right，退出循环)
    //
    // 返回 left = 3，即第一个 >= 5 的元素下标为 3
    }

public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int start = lower_bound(nums, target);
        if (start == nums.size() || nums[start] != target) {
            return {-1, -1}; // nums 中没有 target
        }
        // 如果 start 存在，那么 end 必定存在
        int end = lower_bound(nums, target + 1) - 1;
        return {start, end};
    }
};
```

| 需求                          | 写法                                | 如果不存在    |
|------------------------------|-------------------------------------|---------------|
| ≥x 的第一个元素的下标        | lowerBound(nums, x)                  | 结果为 n      |
| >x 的第一个元素的下标        | lowerBound(nums, x+1)                | 结果为 n      |
| <x 的最后一个元素的下标      | lowerBound(nums, x) − 1              | 结果为 -1     |
| ≤x 的最后一个元素的下标      | lowerBound(nums, x+1) − 1            | 结果为 -1     |

- 当查找 **≥x** 或 **>x** 时，如果不存在，left 会一直右移直到超出数组，返回 **n**
- 当查找 **<x** 或 **≤x** 时，如果不存在，lowerBound 返回 0，减 1 后得到 **-1**


## [咒语和药水](https://leetcode.cn/problems/successful-pairs-of-spells-and-potions/solutions/1595712/by-endlesscheng-1kbp/) <Badge type="tip" text="未解决" />
