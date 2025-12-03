## 目录
- [HDU 基础题](#hdu-基础题)
- [Leetcode 字符串操作](#leetcode-字符串操作)

## HDU 基础题

### [HDU 2030. 汉字统计](https://acm.hdu.edu.cn/showproblem.php?pid=2030)

## 题意

统计给定文本文件中汉字的个数。
- 输入：输入文件首先包含一个整数n，表示测试实例的个数，然后是n段文本
- 输出：对于每一段文本，输出其中的汉字的个数，每个测试实例的输出占一行

## 思路

- 用char数组存储，注意忽略换行符，汉字机内码特征小于0，占两个字节，计数的时候，i++跳过一个字节。
- 汉字机内码：为了与ASCII码兼容（不冲突），规定组成汉字的两个字节的最高位都必须是1。

## 代码

```cpp
cin.ignore();//<iostream>里
//or
getchar();//<cstdio>里

// gets编译错误
char s[500];
gets(s);//c11之后就被删了
// 改成c风格
cin.getline(s,500);
// 或者直接string库的
getline(cin,s);
```

### [HDU 2026. 首字母变大写](https://acm.hdu.edu.cn/showproblem.php?pid=2026)

## 题意

输入一个英文句子，将每个单词的第一个字母改成大写字母。

## 思路

- cin.getline输入，判断字母前面是空格，是就变大写，变大写-'a'+'A'；
- 检查 `'\0'`（空字符）而不是空格,空格是` `;
- 或者`s[i] = toupper(s[i])`,这个在`<cctype>`

### [HDU 2025. 查找最大元素](https://acm.hdu.edu.cn/showproblem.php?pid=2025) <Badge type="tip" text="已解决" />

## 题意

对于输入的每个字符串，查找其中的最大字母，在该字母后面插入字符串“(max)”。

## 思路

- 直接模拟不行么？

## Leetcode 字符串操作

### [1812. 判断国际象棋棋盘中一个格子的颜色](https://leetcode.cn/problems/determine-color-of-a-chessboard-square/description/)

## 题意

给你一个坐标 `coordinates`，它是一个字符串，表示国际象棋棋盘中一个格子的坐标。如果所给格子的颜色是白色，返回 `true`；如果是黑色，返回 `false`。
- `coordinates` 是长度为 2 的字符串，第一个字符是字母（'a'-'h'），第二个字符是数字（'1'-'8'）
- 下标之和为奇数 -> 白色

## 思路

- 观察下标与白色格子的特征关系（下标之和为奇数），纵方向就是减去字符1，横坐标减去字符a；
- 运算符优先级，检查括号

### [LCR 122. 路径加密](https://leetcode.cn/problems/ti-huan-kong-ge-lcof/)

## 题意

假定一段路径记作字符串 `path`，其中以 "." 作为分隔符。现需将路径加密，加密方法为将 `path` 中的分隔符替换为空格 " "，请返回加密后的字符串。

## 思路

- 跟算法书上的例题差不多，可以边输入边输出，如果不是字母就else；
- 单引号表示单个字符，双引号表示字符串

### [1876. 长度为三且各字符不同的子字符串](https://leetcode.cn/problems/substrings-of-size-three-with-distinct-characters/description/)

## 题意

如果一个字符串不含有任何重复字符，我们称这个字符串为**好字符串**。给你一个字符串 `s`，请你返回 `s` 中长度为 **3** 的**好子字符串**的数量。注意，如果相同的好子字符串出现多次，每一次都应该被记入答案之中。

## 思路

- 截取长度，判断是否有重复，计数器计数，注意边界。
- `s.size()-2` 当字符串小于3时，会变成一个很大的无符号数（因为 `size()`返回的是 `size_t`类型）。

## 代码

```cpp
for(int i = 0; i < s.size()-2; i++) // 错误写法，若size<2会溢出
```

### [2011. 执行操作后的变量值](https://leetcode.cn/problems/final-value-of-variable-after-performing-operations/description/) <Badge type="tip" text="已解决" />

## 题意

存在一种仅支持 4 种操作和 1 个变量 X 的编程语言：
- ++X 和 X++ 使变量 X 的值 加 1
- --X 和 X-- 使变量 X 的值 减 1
最初，X 的值是 0

## 思路

- 直接模拟即可
- 两个不同操作得出一样的结果用`||`;

### [1108. IP 地址无效化](https://leetcode.cn/problems/defanging-an-ip-address/description/)

## 题意

给你一个有效的 IPv4 地址 `address`，返回这个 IP 地址的无效化版本。所谓无效化 IP 地址，其实就是用 `"[.]"` 代替了每个 `"."`。

## 思路

- 不能直接替换，类型不匹配，`address[i]`是`char`类型，`'[.]'` 是字符串。
- 解决方案是`string`一个新串。

## 代码

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

### [2315. 统计星号](https://leetcode.cn/problems/count-asterisks/description/) <Badge type="tip" text="已解决" />

## 题意

给你一个字符串 s ，每 两个 连续竖线 '|' 为 一对 。换言之，第一个和第二个 '|' 为一对，第三个和第四个 '|' 为一对，以此类推。

请你返回 不在 竖线对之间，s 中 '*' 的数目。

## 思路

- 两个竖线为一对，之前书上有类似的，创建一个标志变量加上！

### [1221. 分割平衡字符串](https://leetcode.cn/problems/split-a-string-in-balanced-strings/description/) <Badge type="tip" text="已解决" />

## 题意

平衡字符串 中，'L' 和 'R' 字符的数量是相同的。

给你一个平衡字符串 s，请你将它分割成尽可能多的 平衡字符串 。

返回可以通过分割得到的平衡字符串的 最大数量 。

## 思路

- 最开始想用两数统计次数，相等就输出然后再重置，又想到二元关系，用加一减一估计更好。

### [LCR 182. 动态口令](https://leetcode.cn/problems/zuo-xuan-zhuan-zi-fu-chuan-lcof/description/)

## 题意

某公司门禁密码使用动态口令技术。初始密码为字符串 `password`，密码更新均遵循以下步骤：设定一个正整数目标值 `target`；将 `password` 前 `target` 个字符按原顺序移动至字符串末尾。请返回更新后的密码字符串。

## 思路

- 算法书上有个题包含了此题的思想，[环状字符串最小字典序](https://blog.csdn.net/2401_88544423/article/details/154158761?spm=1001.2014.3001.5501)

## 代码

```cpp
string result;
int len = password.size();
for(int i = 0; i < len; i++)
    result += password[(i+target)%len];
```

### [2114. 句子中的最多单词数](https://leetcode.cn/problems/maximum-number-of-words-found-in-sentences/) <Badge type="tip" text="已解决" />

## 题意

一个 句子 由一些 单词 以及它们之间的单个空格组成，句子的开头和结尾不会有多余空格。

给你一个字符串数组 sentences ，其中 sentences[i] 表示单个句子。

请你返回单个句子里 单词的 最大数目 。

## 思路

- 最开始cnt为0，遍历，跟每个句子的temp比较,聪明的我发现单词数就是空格加1；

### [1684. 统计一致字符串的数目](https://leetcode.cn/problems/count-the-number-of-consistent-strings/description/) <Badge type="warning" text="未解决" />

## 题意

给你一个由不同字符组成的字符串 `allowed` 和一个字符串数组 `words`。如果一个字符串的每一个字符都在 `allowed` 中，就称这个字符串是**一致字符串**。请你返回 `words` 数组中**一致字符串**的数目。

## 思路

- **set**: 创建一个名为 allowedSet 的集合，它包含了 allowed 字符串中的所有字符。
- **bool数组**: 创建一个bool数组标记 allowed 字符。
- **遍历**: 暴力检查每个字符是否在 allowed 中。

## 代码

```cpp
// Set 方法
class Solution {
public:
    int countConsistentStrings(string allowed, vector<string>& words) {
        unordered_set<char> allowedSet(allowed.begin(), allowed.end());
        int count = 0;
        
        for (const string& word : words) {
            bool consistent = true;
            for (char c : word) {
                if (allowedSet.find(c) == allowedSet.end()) {
                    consistent = false;
                    break;
                }
            }
            if (consistent) count++;
        }
        return count;
    }
};

// Bool 数组
class Solution {
public:
    int countConsistentStrings(string allowed, vector<string>& words) {
        bool allowedChars[26] = {false};
        for (char c : allowed) allowedChars[c - 'a'] = true;
        
        int count = 0;
        for (const string& word : words) {
            bool consistent = true;
            for (char c : word) {
                if (!allowedChars[c - 'a']) {
                    consistent = false;
                    break;
                }
            }
            if (consistent) count++;
        }
        return count;
    }
};
```
