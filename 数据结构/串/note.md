## [汉字统计](https://acm.hdu.edu.cn/showproblem.php?pid=2030)
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
> 思路：cin.getline输入，判断字母前面是空格，是就变大写，变大写-‘a'+'A'；
- strlen在<cstirng>库
- 检查 `'\0'`（空字符）而不是空格,空格是` `;
- 或者`s[i] = toupper(s[i])`,这个在`<cctype>`

## [找最大元素](https://acm.hdu.edu.cn/showproblem.php?pid=2025)
>思路：直接模拟就行

## [判断棋盘颜色](https://leetcode.cn/problems/determine-color-of-a-chessboard-square/description/)
>观察下标与白色格子的特征关系（下标之和为奇数），纵方向就是减去字符1，横坐标减去字符a；
- 运算符优先级，检查括号

## [换字符](https://leetcode.cn/problems/ti-huan-kong-ge-lcof/)
> 跟算法书上的例题差不多，可以边输入边输出，如果不是字母就else；
- 单引号表示单个字符，双引号表示字符串

## [字符查重](https://leetcode.cn/problems/substrings-of-size-three-with-distinct-characters/description/)
>截取长度，判断是否有重复，计数器计数，注意边界。
```cpp
for(int i = 0; i < s.size()-2; i++)
```
题目说`1 <= s.length <= 100`，在看有个`s.size()-2`,当字符串小于3时，会变成一个很大的无符号数（因为 `size()`返回的是 `size_t`类型，是无符号整数

## [字符串操作](https://leetcode.cn/problems/final-value-of-variable-after-performing-operations/description/)
>直接模拟即可
- 两个不同操作得出一样的结果用`||`;

## [字符串与字符之间的替换](https://leetcode.cn/problems/defanging-an-ip-address/description/)]
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

## [一对](https://leetcode.cn/problems/count-asterisks/description/)
>两个竖线为一对，之前书上有类似的，创建一个标志变量加上！

## [判断两符号数量相等，先A后B，相等为一组](https://leetcode.cn/problems/split-a-string-in-balanced-strings/description/)
>思路: 最开始想用两数统计次数，相等就输出然后再重置，又想到二元关系，用加一减一估计更好。

## [动态口令](https://leetcode.cn/problems/zuo-xuan-zhuan-zi-fu-chuan-lcof/description/)
>思路：算法书上有个题包含了此题的思想，[环状字符串最小字典序](https://blog.csdn.net/2401_88544423/article/details/154158761?spm=1001.2014.3001.5501)
```cpp
string result;
int len = password.size();
for(int i = 0; i < len; i++)
    result += password[(i+target)%len];
```