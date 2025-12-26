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


