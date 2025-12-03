## [汉字统计](https://acm.hdu.edu.cn/showproblem.php?pid=2030)
### 题意
- **题目描述**：统计给定文本文件中汉字的个数
- **输入**：输入文件首先包含一个整数n，表示测试实例的个数，然后是n段文本
- **输出**：对于每一段文本，输出其中的汉字的个数，每个测试实例的输出占一行
- **示例**：
  - 输入："WaHaHa! WaHaHa! 今年过节不说话要说只说普通话WaHaHa! WaHaHa!" → 输出：14
  - 输入："马上就要期末考试了Are you ready?" → 输出：9

> 思路：用char数组存储，注意忽略换行符，汉字机内码特征小于0，占两个字节，计数的时候，i++跳过一个字节

- ASCII字符： 最高位（第8位）为0。例如，字母 A 的ASCII码是 01000001（十六进制0x41）。
- 汉字机内码： 为了与ASCII码兼容（不冲突），规定组成汉字的两个字节的最高位都必须是1。
为什么这么做？
- 当计算机读取一个字节时，如果发现其最高位是0，就把它当作一个ASCII字符处理；如果发现是1，就知道它（连同下一个字节）是一个双字节字符（如汉字）的一部分。这样就实现了中英文混合文本的无冲突存储
- 忽略换行符
```cpp
cin.ignore();//<iostream>里
//or
getchar();//<cstdio>里
```
- gets编译错误
```cpp
char s[500];
gets(s);//c11之后就被删了
```
改成c风格`cin.getline(s,500)`或者直接string库的`getline(cin,s)`;

## [字母变大写](https://acm.hdu.edu.cn/showproblem.php?pid=2026)
### 题意
- **题目描述**：输入一个英文句子，将每个单词的第一个字母改成大写字母
- **输入**：输入数据包含多个测试实例，每个测试实例是一个长度不超过100的英文句子，占一行
- **输出**：请输出按照要求改写后的英文句子
- **示例**：
  - 输入："i like acm" → 输出："I Like Acm"
  - 输入："i want to get an accepted" → 输出："I Want To Get An Accepted"

> 思路：cin.getline输入，判断字母前面是空格，是就变大写，变大写-'a'+'A'；
- strlen在`<cstring>`库
- 检查 `'\0'`（空字符）而不是空格,空格是` `;
- 或者`s[i] = toupper(s[i])`,这个在`<cctype>`

### [找最大元素](https://acm.hdu.edu.cn/showproblem.php?pid=2025) <Badge type="tip" text="已解决" />
>思路：直接模拟就行

## [判断棋盘颜色](https://leetcode.cn/problems/determine-color-of-a-chessboard-square/description/)
### 题意
- **题目描述**：给你一个坐标 `coordinates`，它是一个字符串，表示国际象棋棋盘中一个格子的坐标。如果所给格子的颜色是白色，返回 `true`；如果是黑色，返回 `false`
- **输入**：`coordinates` 是长度为 2 的字符串，第一个字符是字母（'a'-'h'），第二个字符是数字（'1'-'8'）
- **输出**：布尔值（白色返回 `true`，黑色返回 `false`）
- **示例**：
  - 输入：coordinates = "a1" → 输出：false（黑色）
  - 输入：coordinates = "h3" → 输出：true（白色）
  - 输入：coordinates = "c7" → 输出：false（黑色）

>观察下标与白色格子的特征关系（下标之和为奇数），纵方向就是减去字符1，横坐标减去字符a；
- 运算符优先级，检查括号

## [换字符](https://leetcode.cn/problems/ti-huan-kong-ge-lcof/)
### 题意
- **题目描述**：假定一段路径记作字符串 `path`，其中以 "." 作为分隔符。现需将路径加密，加密方法为将 `path` 中的分隔符替换为空格 " "，请返回加密后的字符串
- **输入**：`path` 是一个字符串，0 <= path.length <= 10000
- **输出**：返回替换后的字符串
- **示例**：
  - 输入：path = "a.aef.qerf.bb" → 输出："a aef qerf bb"

> 跟算法书上的例题差不多，可以边输入边输出，如果不是字母就else；
- 单引号表示单个字符，双引号表示字符串

## [字符查重](https://leetcode.cn/problems/substrings-of-size-three-with-distinct-characters/description/)
### 题意
- **题目描述**：如果一个字符串不含有任何重复字符，我们称这个字符串为**好字符串**。给你一个字符串 `s`，请你返回 `s` 中长度为 **3** 的**好子字符串**的数量。注意，如果相同的好子字符串出现多次，每一次都应该被记入答案之中
- **输入**：`s` 是一个字符串，1 <= s.length <= 100，只包含小写英文字母
- **输出**：返回长度为 3 的好子字符串的数量
- **示例**：
  - 输入：s = "xyzzaz" → 输出：1（只有 "xyz" 是好子字符串）
  - 输入：s = "aababcabc" → 输出：4（"abc"，"bca"，"cab"，"abc"）

>截取长度，判断是否有重复，计数器计数，注意边界。
```cpp
for(int i = 0; i < s.size()-2; i++)
```
题目说`1 <= s.length <= 100`，在看有个`s.size()-2`,当字符串小于3时，会变成一个很大的无符号数（因为 `size()`返回的是 `size_t`类型，是无符号整数

### [字符串操作](https://leetcode.cn/problems/final-value-of-variable-after-performing-operations/description/) <Badge type="tip" text="已解决" />
>直接模拟即可
- 两个不同操作得出一样的结果用`||`;

## [字符串与字符之间的替换](https://leetcode.cn/problems/defanging-an-ip-address/description/)
### 题意
- **题目描述**：给你一个有效的 IPv4 地址 `address`，返回这个 IP 地址的无效化版本。所谓无效化 IP 地址，其实就是用 `"[.]"` 代替了每个 `"."`
- **输入**：`address` 是一个有效的 IPv4 地址
- **输出**：返回无效化后的字符串
- **示例**：
  - 输入：address = "1.1.1.1" → 输出："1[.]1[.]1[.]1"
  - 输入：address = "255.100.50.0" → 输出："255[.]100[.]50[.]0"

>不能直接替换
```cpp
for(int i = 0; i < address.size()-1; i++)
                if(address[i] == '.') address[i] = '[.]';
```
- 类型不匹配，`address[i]`是`char`类型，只能存储单个字符
`'[.]'` 是一个字符串字面量，包含3个字符：`'['`,` '.'`,` ']'`
- 字符串的长度变化，但是没有额外的空间分配新的内存
- 解决方案是`string`一个新串
```cpp
string defangIPaddr(string address) {
        string result;
        for (char c : address) {
            if (c == '.')result += "[.]";
            else result += c;
        }
        return result;
    }
```

### [一对](https://leetcode.cn/problems/count-asterisks/description/) <Badge type="tip" text="已解决" />
>两个竖线为一对，之前书上有类似的，创建一个标志变量加上！

### [判断两符号数量相等，先A后B，相等为一组](https://leetcode.cn/problems/split-a-string-in-balanced-strings/description/) <Badge type="tip" text="已解决" />
>思路: 最开始想用两数统计次数，相等就输出然后再重置，又想到二元关系，用加一减一估计更好。

## [动态口令](https://leetcode.cn/problems/zuo-xuan-zhuan-zi-fu-chuan-lcof/description/)
### 题意
- **题目描述**：某公司门禁密码使用动态口令技术。初始密码为字符串 `password`，密码更新均遵循以下步骤：设定一个正整数目标值 `target`；将 `password` 前 `target` 个字符按原顺序移动至字符串末尾。请返回更新后的密码字符串
- **输入**：`password` 是一个字符串，`target` 是正整数，1 <= target < password.length <= 10000
- **输出**：返回更新后的字符串
- **示例**：
  - 输入：password = "s3cur1tyC0d3", target = 4 → 输出："r1tyC0d3s3cu"
  - 输入：password = "lrloseumgh", target = 6 → 输出："umghlrlose"

>思路：算法书上有个题包含了此题的思想，[环状字符串最小字典序](https://blog.csdn.net/2401_88544423/article/details/154158761?spm=1001.2014.3001.5501)
```cpp
string result;
int len = password.size();
for(int i = 0; i < len; i++)
    result += password[(i+target)%len];
```

### [统计vector中的string句子中的单词个数](https://leetcode.cn/problems/maximum-number-of-words-found-in-sentences/) <Badge type="tip" text="已解决" />
>思路：最开始cnt为0，遍历，跟每个句子的temp比较,聪明的我发现单词数就是空格加1；

### [字符串的比较](https://leetcode.cn/problems/count-the-number-of-consistent-strings/description/) <Badge type="warning" text="未解决" />
### 题意
- **题目描述**：给你一个由不同字符组成的字符串 `allowed` 和一个字符串数组 `words`。如果一个字符串的每一个字符都在 `allowed` 中，就称这个字符串是**一致字符串**。请你返回 `words` 数组中**一致字符串**的数目
- **输入**：`allowed` 是由不同字符组成的字符串（1 <= allowed.length <= 26），`words` 是字符串数组（1 <= words.length <= 10^4，1 <= words[i].length <= 10），只包含小写英文字母
- **输出**：返回一致字符串的数目
- **示例**：
  - 输入：allowed = "ab", words = ["ad","bd","aaab","baa","badab"] → 输出：2（"aaab" 和 "baa"）
  - 输入：allowed = "abc", words = ["a","b","c","ab","ac","bc","abc"] → 输出：7（所有字符串都是一致的）
  - 输入：allowed = "cad", words = ["cc","acd","b","ba","bac","bad","ac","d"] → 输出：4（"cc"，"acd"，"ac"，"d"）

>思路：要计数就得有计数器，至于比较，新写一个函数并且新开一个字符数组？试试
>很遗憾，做不出来，参考以下
#### set
```cpp
class Solution {
public:
    class Solution {
public:
    int countConsistentStrings(string allowed, vector<string>& words) {
        unordered_set<char> allowedSet(allowed.begin(), allowed.end());
        //创建一个名为 allowedSet 的集合，它包含了 allowed 字符串中的所有字符。
        //allowed.begin() 和 allowed.end() 表示整个字符串的范围
        //集合会自动去除重复字符（如果有的话）
        //集合的作用是快速判断某个字符是否存在

        //find()是集合的一个方法，用于在集合中查找指定的元素：
        //如果找到了元素 c，返回一个指向该元素的迭代器
        //如果没找到元素 c，返回 allowedSet.end()
        //end()返回一个特殊的迭代器，它不指向任何实际元素，而是指向集合的"末尾之后"的位置。可以把它理解为"无效位置"或"结束标志"。

        int count = 0;
        
        for (const string& word : words) {
            bool consistent = true;
            // 直接遍历单词的每个字符
            for (char c : word) {
                if (allowedSet.find(c) == allowedSet.end()) {
                    //相等就说明没找到
                    consistent = false;
                    break;
                }
            }
            
            if (consistent) {
                count++;
            }
        }
        
        return count;
    }
};

```
#### bool数组
```cpp
class Solution {
public:
    int countConsistentStrings(string allowed, vector<string>& words) {
        bool allowedChars[26] = {false};
        
        // 标记allowed中的字符
        for (char c : allowed) {
            allowedChars[c - 'a'] = true;
        }
        
        int count = 0;
        
        for (const string& word : words) {
            bool consistent = true;
            
            // 检查单词中的每个字符
            for (char c : word) {
                if (!allowedChars[c - 'a']) {
                    consistent = false;
                    break;
                }
            }
            
            if (consistent) {
                count++;
            }
        }
        
        return count;
    }
};
```
### 遍历

```cpp
for (每个单词) {
    for (单词中的每个字符) {
        检查这个字符是否在allowed中
    }
    如果所有字符都在allowed中，计数加1
}
```

```cpp
class Solution {
public:
    int countConsistentStrings(string allowed, vector<string>& words) {
        int count = 0;
        
        for (const string& word : words) {
            //每个单词
            bool consistent = true;
            //是否合法
            for (char c : word) {
                // 在allowed中查找当前字符
                bool found = false;
                for (char a : allowed) {
                    if (a == c) {
                        found = true;
                        break;
                        //注意是a在变换，a找到了就不用换allowed的其他字符了
                    }
                }
                
                if (!found) {
                    consistent = false;
                    //只要一个单词没找到，直接退出循环标记false
                    break;
                }
            }
            
            if (consistent) {
                count++;
            }
        }
        
        return count;
    }
};
```