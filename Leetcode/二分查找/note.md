# 二分查找
## 模版题
```cpp
class Solution {
    // lower_bound 返回最小的满足 nums[i] >= target 的下标 i
    // 如果数组为空，或者所有数都 < target，则返回 nums.size()
    // 要求 nums 是非递减的，即 nums[i] <= nums[i + 1]
    int lower_bound(vector<int>& nums, int target) {
        int left = 0, right = (int) nums.size() - 1; // 闭区间 [left, right]
        while (left <= right) { // 区间不为空
            // 循环不变量：
            // nums[left-1] < target
            // nums[right+1] >= target
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
    //
    // 第 1 次循环：
    //                 ↓     ↓        ↓
    //                [1, 3, 3, 5, 7, 9]
    //                 L     M        R
    //                          L‘
    //                left=0, mid=2, right=5
    //                nums[2]=3 < 5，执行 left = mid + 1
    //
    // 第 2 次循环：
    //                          ↓  ↓  ↓
    //                [1, 3, 3, 5, 7, 9]
    //                          L  M  R
    //                          R’
    //                left=3, 取中点后mid=4, right=5
    //                nums[4]=7 >= 5，执行 right = mid - 1
    //
    // 第 3 次循环：
    //                         ↓↓↓
    //                [1, 3, 3, 5, 7, 9]
    //                         LRM
    //                       R‘
    //                left=3, mid=3, right=3
    //                nums[3]=5 >= 5，执行 right = mid - 1
    //
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

### 不存在情况的解释

#### 示例 1：查找 ≥x 的第一个元素，但所有数都 < x
```
数组：[1, 3, 3, 5, 7, 9]   target = 10
索引： 0  1  2  3  4  5

初始状态：
                ↓              ↓
               [1, 3, 3, 5, 7, 9]
                L              R
               left=0, right=5

第 1 次循环：
                ↓     ↓        ↓
               [1, 3, 3, 5, 7, 9]
                L     M        R
                         L'
               left=0, mid=2, right=5
               nums[2]=3 < 10，执行 left = mid + 1

第 2 次循环：
                         ↓  ↓  ↓
               [1, 3, 3, 5, 7, 9]
                         L  M  R
                               L'
               left=3, mid=4, right=5
               nums[4]=7 < 10，执行 left = mid + 1

第 3 次循环：
                               ↓↓
               [1, 3, 3, 5, 7, 9]
                               LR
                               M
               left=5, mid=5, right=5
               nums[5]=9 < 10，执行 left = mid + 1

循环结束：
                               ↓  ↓
               [1, 3, 3, 5, 7, 9] |
                               R  L
               left=6, right=5 (left > right，退出循环)

返回 left = 6 = nums.size()
因为所有数都 < 10，所以不存在 ≥10 的元素，返回 n 表示"超出数组范围"
```

#### 示例 2：查找 <x 的最后一个元素，但所有数都 ≥ x
```
数组：[1, 3, 3, 5, 7, 9]   target = 1
索引： 0  1  2  3  4  5

查找 <1 的最后一个元素 = lowerBound(nums, 1) - 1

先执行 lowerBound(nums, 1)：

初始状态：
                ↓              ↓
               [1, 3, 3, 5, 7, 9]
                L              R
               left=0, right=5

第 1 次循环：
                ↓     ↓        ↓
               [1, 3, 3, 5, 7, 9]
                L     M        R
                R'
               left=0, mid=2, right=5
               nums[2]=3 >= 1，执行 right = mid - 1

第 2 次循环：
                ↓  ↓
               [1, 3, 3, 5, 7, 9]
                L  R
                M
               left=0, mid=0, right=1
               nums[0]=1 >= 1，执行 right = mid - 1

循环结束：
             ↓  ↓
            |[1, 3, 3, 5, 7, 9]
             R  L
            left=0, right=-1 (left > right，退出循环)

lowerBound 返回 left = 0
结果 = 0 - 1 = -1
因为所有数都 >= 1，所以不存在 <1 的元素，返回 -1 表示"不存在"
```

**总结：**
- 当查找 **≥x** 或 **>x** 时，如果不存在，left 会一直右移直到超出数组，返回 **n**
- 当查找 **<x** 或 **≤x** 时，如果不存在，lowerBound 返回 0，减 1 后得到 **-1**
