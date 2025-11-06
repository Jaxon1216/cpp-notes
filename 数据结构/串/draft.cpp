class Solution {
    public:
        string dynamicPassword(string password, int target) {
            string result;
            int len = password.size();
            for(int i = 0; i < len; i++){
                result += password[(i+target)%len];
            }
            return result;
        }
    };