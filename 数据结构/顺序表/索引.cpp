// 小A 和 小B 在玩猜数字游戏。小B 每次从 1, 2, 3 中随机选择一个数字，小A 也从 1, 2, 3 中选择一个数字进行猜测。他们一共进行三次这个游戏。请返回 小A 猜对了几次？

// 输入的guess数组记录了 小A 每次的猜测，answer数组记录了 小B 每次的选择。guess和answer的长度都等于3。

// 示例
// 输入：guess = [1,2,3], answer = [1,2,3]
// 输出：3
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