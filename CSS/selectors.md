# CSS选择器全面解析

## 一、基本选择器（必须掌握的4种）

### 1. **元素选择器**
```css
/* 选择所有指定元素 */
p { color: red; }          /* 所有p标签 */
div { background: blue; }  /* 所有div标签 */
table { border: 1px solid; }
```

### 2. **类选择器（最常用）**
```html
<div class="box active">内容</div>
```
```css
.box { width: 100px; }      /* 选择class="box"的元素 */
.active { color: green; }   /* 选择class="active"的元素 */
```

### 3. **ID选择器**
```html
<div id="header">头部</div>
```
```css
#header { height: 60px; }  /* 选择id="header"的元素 */
```

### 4. **通用选择器**
```css
* { margin: 0; padding: 0; }  /* 选择所有元素 */
```

## 二、组合选择器（重点掌握）

### 1. **后代选择器（空格）**
```css
/* 选择div内部的所有p元素（不限层级） */
div p { color: blue; }

/* 你的代码中使用了这个 */
table tr { height: 40px; }  /* 选择table内的所有tr */
```

### 2. **子元素选择器（>）**
```css
/* 只选择div的直接子元素p */
div > p { color: red; }

/* 对比：后代 vs 子元素 */
<div>
  <p>这个会被选中（直接子元素）</p>
  <section>
    <p>这个不会被选中（不是直接子元素）</p>
  </section>
</div>
```

### 3. **相邻兄弟选择器（+）**
```css
/* 选择紧接在h1后面的第一个p元素 */
h1 + p { font-weight: bold; }

/* 例子 */
<h1>标题</h1>
<p>这个p会被选中</p>
<p>这个p不会被选中</p>
```

### 4. **通用兄弟选择器（~）**
```css
/* 选择h1后面的所有兄弟p元素 */
h1 ~ p { color: gray; }

/* 例子 */
<h1>标题</h1>
<div>中间内容</div>
<p>这个p会被选中</p>
<p>这个p也会被选中</p>
```

## 三、属性选择器

```css
/* 1. 选择有特定属性的元素 */
a[href] { color: blue; }

/* 2. 选择属性值等于特定值的元素 */
input[type="text"] { border: 1px solid; }

/* 3. 选择属性值包含特定字符串的元素 */
a[href*="baidu"] { color: red; }  /* href包含"baidu" */

/* 4. 选择属性值以特定字符串开头的元素 */
a[href^="https"] { color: green; }  /* href以"https"开头 */

/* 5. 选择属性值以特定字符串结尾的元素 */
a[href$=".pdf"] { color: purple; }  /* href以".pdf"结尾 */
```

## 四、伪类选择器（状态选择器）

### 1. **结构伪类（你不太明白的部分）**

```css
/* :nth-child 系列 */
li:nth-child(1) { color: red; }      /* 第1个li */
li:nth-child(2) { color: blue; }     /* 第2个li */
li:nth-child(odd) { background: #f0f0f0; }    /* 奇数项 */
li:nth-child(even) { background: #e0e0e0; }   /* 偶数项 */
li:nth-child(3n) { color: green; }           /* 每第3个（3,6,9...） */
li:nth-child(3n+1) { color: orange; }        /* 3n+1（1,4,7,10...） */

/* 简写形式 */
li:first-child { color: red; }       /* 等同于 :nth-child(1) */
li:last-child { color: blue; }       /* 选择最后一个 */
li:only-child { color: green; }      /* 当它是唯一子元素时 */

/* :nth-of-type 系列 */
/* 区别：:nth-child计数所有兄弟元素，:nth-of-type只计数同类型 */
<div>
  <p>第一个p</p>        <!-- p:nth-child(1) 匹配 -->
  <span>span元素</span>
  <p>第二个p</p>        <!-- p:nth-child(3) 匹配，但p:nth-of-type(2)匹配 -->
</div>
```

### 2. **动态伪类**
```css
a:link { color: blue; }         /* 未访问的链接 */
a:visited { color: purple; }    /* 已访问的链接 */
a:hover { background: yellow; } /* 鼠标悬停 */
a:active { color: red; }        /* 激活/点击时 */
input:focus { border-color: blue; } /* 获得焦点时 */
```

### 3. **表单相关伪类**
```css
input:checked { background: green; }     /* 被选中的复选框/单选按钮 */
input:disabled { opacity: 0.5; }         /* 禁用的表单元素 */
input:required { border-color: red; }    /* 必填字段 */
```

## 五、伪元素选择器

```css
/* ::before - 在元素内容前插入 */
p::before {
  content: "★ ";
  color: gold;
}

/* ::after - 在元素内容后插入 */
p::after {
  content: "。";
  color: gray;
}

/* ::first-letter - 首字母样式 */
p::first-letter {
  font-size: 2em;
  color: red;
}

/* ::first-line - 首行样式 */
p::first-line {
  font-weight: bold;
}
```

## 六、组合使用技巧

### 1. **多重选择器（逗号分隔）**
```css
/* 同时选择h1, h2, h3 */
h1, h2, h3 {
  font-family: Arial;
  color: #333;
}
```

### 2. **否定伪类（:not）**
```css
/* 选择所有不是.first的p元素 */
p:not(.first) { opacity: 0.8; }

/* 你的代码中使用了 */
tr:not(:first-child):hover { background-color: #eee; }
/* 解释：选择所有不是第一个子元素的tr，并在悬停时改变背景色 */
```

### 3. **多重伪类组合**
```css
/* 鼠标悬停在表格的奇数行上 */
tr:nth-child(odd):hover {
  background-color: yellow;
}

/* 第一个p元素且class="intro" */
p.intro:first-child {
  font-size: 1.2em;
}
```

## 七、选择器优先级（非常重要！）

### 优先级计算（从高到低）：
1. **!important**（尽量少用）
2. **内联样式**（style属性）
3. **ID选择器**（#id）
4. **类选择器/属性选择器/伪类选择器**（.class, :hover）
5. **元素选择器/伪元素选择器**（div, ::before）
6. **通用选择器/子选择器/相邻选择器**（*, >, +, ~）

### 权重计算示例：
```css
#header .nav li.active a:hover  /* 优先级：1,2,2,1 */
/* 计算：ID(1) + 类(1) + 元素(2) + 伪类(1) = ID:1, 类:2, 元素:2 */

/* vs */
div#header ul li a              /* 优先级：1,0,4 */
/* 计算：ID(1) + 元素(4) = ID:1, 元素:4 */
/* 第一个优先级更高，因为类选择器权重比元素选择器高 */
```

## 八、实战练习

### 练习1：理解你的代码
```css
/* 选择table内的第一个tr（不管它是不是第一个子元素） */
table tr:nth-child(1) {
  background-color: #ddd;
}

/* 选择所有不是第一个子元素的tr，悬停时变色 */
table tr:not(:first-child):hover {
  background-color: #eee;
}
```

### 练习2：常见的表格样式
```css
/* 斑马纹表格 */
tr:nth-child(even) {
  background-color: #f2f2f2;
}

/* 鼠标悬停效果 */
tr:hover {
  background-color: #e6f7ff;
}

/* 第一个单元格加粗 */
td:first-child {
  font-weight: bold;
}

/* 最后一列右对齐 */
td:last-child {
  text-align: right;
}
```

### 练习3：表单美化
```css
/* 必填字段用星号标记 */
input:required::after {
  content: " *";
  color: red;
}

/* 有效的输入框 */
input:valid {
  border-color: green;
}

/* 无效的输入框 */
input:invalid {
  border-color: red;
}
```

## 九、调试技巧

### 1. **在浏览器中测试**
```javascript
// 在控制台测试选择器
document.querySelectorAll('table tr:nth-child(odd)');
document.querySelector('table tr:first-child');

// 查看匹配的元素数量
console.log(document.querySelectorAll('tr').length);
```

### 2. **检查样式来源**
- 使用浏览器开发者工具
- 右键点击元素 → 检查
- 查看样式面板，看哪些规则被应用

## 十、常见错误

```css
/* 错误1：多余的空格 */
table tr :first-child  /* 选择tr内的:first-child，不是第一个tr */
table tr:first-child   /* 正确的 */

/* 错误2：不理解子元素计数 */
ul li:nth-child(2)    /* 选择ul的第二个子元素，但必须是li */

/* 错误3：优先级冲突 */
p { color: blue; }
.text { color: red; }  /* 这个会覆盖上面的，因为类选择器优先级更高 */
```

## 学习建议

1. **从简单到复杂**：先掌握基本选择器，再学组合选择器
2. **多练习**：在浏览器的开发者工具中直接测试
3. **理解原理**：搞清楚`:nth-child`和`:nth-of-type`的区别
4. **关注兼容性**：某些新选择器（如`:has()`）在旧浏览器不支持
5. **命名规范**：给类和ID起有意义的名字，便于选择器编写

记住：选择器是CSS的**核心基础**，掌握好选择器，才能写出优雅、高效的CSS代码！