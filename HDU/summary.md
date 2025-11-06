# HUD page11
### 小问题
- 注意题目要求输入`实数`，那就double，注意匹配`%lf`
- c语言中`sqrt`在`math.h`
- `pi*r*r*r*4/3`从左到右，如果4/3放在最前面就错，除非加个`(double)4/3`
- 对于`YYYY/MM/DD`这种的输入可以用`scanf("%d/%d/%d", &year, &month, &day)`
- 闰年二月29天一般28天
- c语言没有bool类型已经true和false，可以用int ，以及 1，0:`int isleapyear(int n){ifxxxreturn 1 else return 0}`

之前都是似懂非懂，现在来总结一下：
  - 区别能体现：涉及立刻赋值，立刻打印，数组索引，return， 条件判断
  - 一样效果：循环，单独写一行，函数调用`fun（xxx）`；
- 样例通过，提交不过，很有可能就是有些变量在`多次读取数据的while`外边;

| 数据类型 | 输入(scanf) | 输出(printf) |
|---------|------------|------------|
| int | %d（Decimal	十进制整数） | %d |
| long long | %lld | %lld |
| double | %lf | %f 或 %lf |
| float | %f | %f |
- 注意`“之间空格”`,
- [平方和立方和](https://acm.hdu.edu.cn/showproblem.php?pid=2007)
    > 题目要是只说给你两个整数，那就要注意他们两个的大小关系，你做循环从小到大，那么就可以`if(a > b){int t = a; a = b; b = t;};`
    > 平方和，立方和，注意数据类型大小。循环里面涉及到立方转类型（long long）


### [ASCII sort](https://acm.hdu.edu.cn/showproblem.php?pid=2000)
```c
#include<stdio.h>
int main() {
    char i,j,k;

    while(scanf("%c%c%c ",&i,&j,&k) == 3){ //读取这里有过问题
        if(i > j){char t; t = i; i = j; j = t; }//比较这里有过问题，'i'
        if(i > k){char t; t = i; i = k; k = t; }
        if(j > k){char t; t = j; j = k; k = t; }
        printf("%c %c %c\n",i,j,k);
    }
    return 0;
}
```
- `scanf`中所有基本类型变量都需要`&`，只有数组名不需要
```c
char str[100];
scanf("%s", str); // ✓ 数组名本身就是地址，不需要&
```
- 注意区分变量 vs 字符常量
- 读取要是有换行，在这引号前面加个空格

