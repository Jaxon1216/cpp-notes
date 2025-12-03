// 给定一个非负索引 rowIndex，返回「杨辉三角」的第 rowIndex 行。
// 在「杨辉三角」中，
// 示例 1:
// 输入: rowIndex = 3
// 输出: [1,3,3,1]

// 1 0 0 0 0
// 1 1 0 0 0
// 1 2 1 0 0
// 1 3 3 1 0
// 1 4 6 4 1

class Solution {
    public:
        vector<int> getRow(int rowIndex) {
            int y[34][34];
            for(int i = 0; i <= rowIndex; i++){
                for(int j = 0; j <= i ; j++) {
                    if(j==0||j==i) y[i][j] = 1;
                    else y[i][j] = y[i-1][j-1]+y[i-1][j];
                }
            }
            vector<int>ans;
            for(int i = 0; i <= rowIndex; i++) ans.push_back(y[rowIndex][i]);
            return ans;
        }
};
