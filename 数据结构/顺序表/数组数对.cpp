// 给你一个下标从 0 开始的整数数组 nums 。在一步操作中，你可以执行以下步骤：
// 从 nums 选出 两个 相等的 整数
// 从 nums 中移除这两个整数，形成一个 数对
// 请你在 nums 上多次执行此操作直到无法继续执行。
// 返回一个下标从 0 开始、长度为 2 的整数数组 answer 作为答案，其中 answer[0] 是形成的数对数目，answer[1] 是对 nums 尽可能执行上述操作后剩下的整数数目。
// 示例 1：
// 输入：nums = [1,3,2,1,3,2,2]
// 输出：[3,1]
// 解释：
// nums[0] 和 nums[3] 形成一个数对，并从 nums 中移除，nums = [3,2,3,2,2] 。
// nums[0] 和 nums[2] 形成一个数对，并从 nums 中移除，nums = [2,2,2] 。
// nums[0] 和 nums[1] 形成一个数对，并从 nums 中移除，nums = [2] 。
// 无法形成更多数对。总共形成 3 个数对，nums 中剩下 1 个数字。

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