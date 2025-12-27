## day1:作用域，垃圾回收，闭包，变量和函数提升，箭头函数，解构，forEach，filter


##### 块级作用域（ES6）

```js
if (true) {
  let y = 20
}
```

* `let / const` 支持
* `var` 不支持

### 二、垃圾回收（Garbage Collection）

#### 1. GC 的核心原则

* **引用计数 / 可达性**
* 变量只要还能被访问，就不会被回收

#### 2. 常见触发场景

```js
function fn() {
  let obj = {}
}
fn()
```

* `obj` 无外部引用 → 可回收

#### 3. 内存泄漏常见原因

* 全局变量
* 闭包中保存无用数据
* 未清理的定时器 / 事件

---

### 三、闭包（Closure）

#### 1. 定义

* **函数 + 定义时的作用域**
* 即使外层函数执行结束，内部仍能访问外层变量

#### 2. 基本示例

```js
function outer() {
  let count = 0
  return function () {
    count++
    return count
  }
}
```

#### 3. 特点

* 延长变量生命周期
* 既强大，也容易导致内存泄漏

---

### 四、变量与函数提升（Hoisting）

#### 1. 函数提升

```js
fn()
function fn() {}
```

* 函数声明整体提升

#### 2. 变量提升（var）

```js
console.log(a) // undefined
var a = 10
```

* 只提升声明，不提升赋值

#### 3. let / const

```js
console.log(b) // 报错
let b = 20
```

* 存在暂时性死区（TDZ）

---

### 五、箭头函数（Arrow Function）

#### 1. 基本语法

```js
const fn = (a, b) => a + b
```

#### 2. 核心特点

* 没有自己的 `this`
* 没有 `arguments`
* 不能作为构造函数

#### 3. this 对比

```js
function fn() {
  console.log(this)
}

const arrow = () => {
  console.log(this)
}
```

---

### 六、arguments 对象

#### 1. 什么是 arguments

* 函数内部的**类数组对象**
* 保存所有传入的参数

#### 2. 使用示例

```js
function sum() {
  let total = 0
  for (let i = 0; i < arguments.length; i++) {
    total += arguments[i]
  }
  return total
}
```

#### 3. 注意事项

* **箭头函数没有 arguments**
* ES6 推荐使用 **剩余参数**

```js
function sum(...args) {
  return args.reduce((a, b) => a + b, 0)
}
```

---

### 七、解构赋值（Destructuring）

#### 1. 对象解构

```js
const { name, price } = item
```

#### 2. 数组解构

```js
const [a, b] = [1, 2]
```

#### 3. 常见用法

```js
const { price = 0 } = item
```

---

### 八、forEach

#### 1. 定义

* 用于遍历数组
* **不返回新数组**

#### 2. 用法

```js
arr.forEach(item => {
  console.log(item)
})
```

#### 3. 特点

* 无法 `break / return`
* 适合执行副作用操作

---

### 九、map

#### 1. 定义

* 对数组每一项进行映射
* **返回新数组**

#### 2. 用法

```js
const prices = arr.map(item => item.price)
```

---

### 十、forEach vs map（高频对比）

| 对比点     | forEach | map  |
| ------- | ------- | ---- |
| 返回值     | 无       | 新数组  |
| 是否可链式   | 否       | 是    |
| 使用场景    | 遍历 / 渲染 | 数据转换 |
| 是否修改原数组 | 否       | 否    |

---

### 十一、filter

#### 1. 定义

* 按条件筛选数组

#### 2. 用法

```js
const res = arr.filter(item => item.price > 100)
```

#### 3. 特点

* 返回新数组
* 不影响原数组

---

### 十二、数组方法总结（面试速记）

| 方法      | 用途 | 是否返回新数组 |
| ------- | -- | ------- |
| forEach | 遍历 | 否       |
| map     | 映射 | 是       |
| filter  | 筛选 | 是       |
| reduce  | 累积 | 是       |

---


下面我**完全按「项目模块」的视角**，把你今天学到的所有知识点**嵌入到这个模态框项目的真实结构中讲解**。
你可以把它当成：**“这是一个小组件项目，每一块在项目里承担什么职责，用到了哪些 JS 核心能力”**。

---

## 项目模块总览（先有全局认知）

这个项目本质是一个 **Modal 消息提示组件**，可以拆成 5 个模块：

1. **组件初始化模块（构造函数 + new）**
2. **DOM 构建模块（基本包装类型 + 字符串方法）**
3. **组件行为模块（原型方法 + this）**
4. **事件交互模块（箭头函数 + 查找判断）**
5. **数据与集合处理模块（数组方法 / Object 方法 / reduce 思想）**

下面逐模块拆解。

---

## day2:对象，数组字符串方法
### 模块一：组件初始化模块

**（new 实例化 + 构造函数）**

#### 模块职责

* 创建一个“模态框对象”
* 初始化该对象的**私有数据**
* 为后续行为方法提供状态

#### 项目中的代码

```js
function Modal(title = '', message = '') {
  this.title = title
  this.message = message
  this.modalBox = document.createElement('div')
}
```

#### 知识点落地

##### 1️⃣ 为什么要用构造函数

* 项目里会创建**多个模态框实例**
* 每个实例内容不同，但行为一致

```js
const m1 = new Modal('温馨提示', '没有删除权限')
const m2 = new Modal('友情提示', '未注册账号')
```

##### 2️⃣ `new` 在项目中的真实意义

`new Modal()` = 创建一个**独立组件实例**

* 每次 `new`：

  * 数据独立
  * DOM 独立
  * 状态不互相污染

---

### 模块二：DOM 构建模块

**（字符串方法 + 基本包装类型）**

#### 模块职责

* 生成组件内部 DOM 结构
* 用数据渲染视图

#### 项目中的代码

```js
this.modalBox.className = 'modal'
this.modalBox.innerHTML = `
  <div class="header">${this.title} <i>x</i></div>
  <div class="body">${this.message}</div>
`
```

---

#### 知识点 1：字符串是“临时对象”（基本包装类型）

```js
`${this.title}`
```

这里发生了什么：

* `this.title` 是字符串（基本类型）
* JS 自动包装为 `String` 对象
* 调用模板字符串能力
* 用完即销毁

等价理解：

```js
new String(this.title).toString()
```

---

#### 知识点 2：字符串常见方法在项目中的真实用途

| 方法       | 项目用途   |
| -------- | ------ |
| trim     | 清洗用户输入 |
| includes | 判断关键词  |
| slice    | 截断提示内容 |
| replace  | 关键词高亮  |

示例（项目增强）：

```js
this.message = message.trim().slice(0, 50)
```

---

### 模块三：组件行为模块

**（原型方法 + this 设计）**

#### 模块职责

* 定义组件“能做什么”
* 控制显示 / 销毁

---

#### 打开模块（open）

```js
Modal.prototype.open = function () {
  if (!document.querySelector('.modal')) {
    document.body.appendChild(this.modalBox)
  }
}
```

##### 为什么放在 prototype 上？

* `open` 是**行为**
* 所有模态框行为一致
* 不应该每个实例创建一份

---

#### 关闭模块（close）

```js
Modal.prototype.close = function () {
  document.body.removeChild(this.modalBox)
}
```

#### this 在模块中的含义

* `this` 始终指向 **当前组件实例**
* 不操作全局
* 保证组件封闭性

---

### 模块四：事件交互模块

**（箭头函数 + 查找判断）**

### 模块职责

* 响应用户行为
* 触发组件方法

---

#### 项目中的关键代码

```js
this.modalBox.querySelector('i').addEventListener('click', () => {
  this.close()
})
```

---

#### 知识点 1：为什么用箭头函数

* 事件回调默认 `this` 指向 DOM
* 组件方法需要 `this === Modal 实例`

箭头函数：

* 不绑定 `this`
* 直接继承外层 `this`

---

#### 知识点 2：查找 / 判断思维（find / every）

虽然项目里没直接写数组，但逻辑是一样的：

```js
if (!document.querySelector('.modal')) {
  ...
}
```

等价数组思维：

```js
modals.every(m => !m.isOpen)
```

项目意识：

> **先判断，再执行**

---

### 模块五：数据与集合处理模块

**（Object 方法 + reduce 思想）**

### 模块职责

* 管理组件配置
* 批量处理数据

---

#### Object 静态方法（配置型组件必备）

假设未来支持配置：

```js
function Modal(options) {
  const defaults = { title: '', message: '' }
  this.options = Object.assign(defaults, options)
}
```

* `Object.assign` → 合并配置
* `Object.keys` → 遍历配置项

---

#### reduce 思想在组件项目中的位置

虽然当前项目没写 `reduce`，但组件项目中非常常见：

##### 例：拼接 className

```js
const className = classes.reduce((res, cur) => {
  return res + ' ' + cur
}, '')
```

##### 本质

* 把**多个值 → 一个结果**
* 非常适合组件状态计算

---

### 项目级总结（非常重要）

这个项目表面是一个 **模态框**，本质是在练：

1. **如何用构造函数表示“组件实例”**
2. **如何用原型方法表示“组件行为”**
3. **如何用字符串 / DOM 构建视图**
4. **如何控制 this，避免组件失控**
5. **如何用数组 / 对象方法支撑扩展性**

---
