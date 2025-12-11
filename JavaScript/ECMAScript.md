ECMAScript（简称 ES，全称European Computer Manufacturers Association”（欧洲计算机制造商协会）
）是 JavaScript 的官方语言标准，由 ECMA International 组织制定。从经典的 ES5 到划时代的 ES6，再到每年更新的 ES2024，它定义了语法、核心 API 和语言特性。浏览器和 Node.js 中的 JavaScript 都是其实现。了解 ECMAScript，就是理解现代 JavaScript 发展的核心脉络。

---
# 黑马学习总结

## day1
- document.write,alert,console.log
- prompt读取的默认是string
- 代表数字的变量前面加+号转成num
- ${变量}
- typeof x
- 转数字Number,parseInt,parseFloat;
    在cpp中，是(目标数据类型),在js里放在一样的位置去掉括就行
- String,toString

## day2
- 模板字符串``支持代码中直接换行，单引号''需要\n才能换行。
- `==`,`===`后者要求数据类型也相等,注意!==才表示不等于；判断语句（if/switch/循环）中都用 ===（全等），永远避免使用 ==。在js中尽量忘记==的存在；
- 断点调试：开发者工具-source-选择file
- 前增后增差异（cpp已经总结过，搬过来）
**两者的差异，在以下场景会显现：**
//js，cpp，Java等等
- 立即赋值（`let x = a++`）
- 立即打印或参与运算（`console.log(a++)`）
- 作为数组索引（`arr[i++]`）
- 在 `return` 语句中
- 在条件判断里（`while(i++ < 5)`）

**两者的效果，在以下场景完全相同：**
- 在循环的增量部分单独使用（`for(...; ...; i++)`）
- 单独写一整行（`i++;`）
- 作为不关心其返回值的函数参数（`func(i++)`）


## day3
1. 数组的增删改查，push,unshift,pop,shift,splice
2. flex布局的一些容器还是不太熟
- 外层 .box：水平排列柱子
- 内层 .box div：每个柱子内部垂直排列文字
    - flex-direction: column 改变主轴方向为垂直方向
    - 默认 row（水平），改为 column 后：
    - 主轴：从上到下
    - 交叉轴：从左到右
    - 这样内部的 span 和 h4 就能垂直排列
    - justify-content: space-between 现在主轴是垂直的，所以控制垂直分布
    - space-between：顶部文字和底部文字分别贴边，中间空间均匀分布
- justify-content: space-around;    /* 重点：主轴对齐方式 */
    - space-around：每个项目两侧的间隔相等
    - flex-start：左对齐（默认）
    - flex-end：右对齐
    - center：居中
    - space-between：两端对齐，项目间隔相等
    - space-evenly：均匀分布，所有间隔相等
- align-items: flex-end;           /* 重点：交叉轴对齐方式 */
    - flex-end：底部对齐
    - 这里是让柱子从底部开始向上生长
    - stretch：拉伸填满容器高度（默认）
    - flex-start：顶部对齐
    - center：垂直居中
    - baseline：基线对齐