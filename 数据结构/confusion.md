# 顺序表
[顺序表源码](https://github.com/Jaxon1216/cpp-notes/blob/main/%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/%E9%A1%BA%E5%BA%8F%E8%A1%A8/Sqlisttmp.cpp)
## 宏定义
```cpp
#define eletype int 
//便于修改：如果以后想把元素类型从 int 改为 double，只需要改一行
```
## 申请空间
```cpp
void initializelist(Sequentiallist *list, int capacity){
    list->elements = new eletype[capacity];
    /* =====================【要点2｜显眼说明】===================== 
       在堆上申请了 “capacity 个 eletype 的连续内存”，并把“首地址”赋给 elements。
       注意：像 int 这类内置类型，new[] 默认不清零；若需清零可写 new eletype[capacity]();
       访问指针指向的结构体成员用 ->；若 list 是对象本身（非指针）则用 .
       ========================================================= */

    list->size = 0;
    list->capacity = capacity;
}
```

## 释放内存
```cpp

void destroylist(Sequentiallist *list){
    // 【要点4】delete[] 释放的是 elements 当前指向的“数组内存”，不是指针变量本身
    delete[] list->elements;
    list->elements = nullptr; // 置空，避免悬空指针被误用
    list->size = 0;
    list->capacity = 0;
}
```



## 总结与常见疑问

#### Q1：为什么 main 里要写 initializelist(&list, 10)？
- 形参是 `Sequentiallist*`，需要“对象地址”。main 里有对象 `Sequentiallist list;`，
  所以要传 `&list`（取地址，类型刚好是 `Sequentiallist*`）。

#### Q2：以后凡是“操作指针指向的对象”，都要加 `&` 吗？
- 不。仅当“形参类型是指针 `T*`，而你手里是一个对象 `T`”时，才需要写 `&obj`。
  小抄：
  - 你有对象 `T obj`，函数要 `T*`        → 传 `&obj`
  - 你已有指针 `T* p`，函数要 `T*`         → 直接传 `p`（不要再 `&`）
  - 函数要引用 `T&`                     → 直接传 `obj`（不用 `&`）
  - 函数要值 `T`（拷贝）                 → 直接传 `obj`（函数内改动不影响外部）

#### Q3：为什么在 `insert` 等函数里不写成 `&elements`？
- 因为 `elements` 的类型已经是 `eletype*`（指向元素的指针），正是我们需要的。
- `&elements` 的类型会变成 `eletype**`（指向“指针变量本身”的地址），
  这既不是数组起始地址，也不是我们要用来下标访问的类型，反而会出错。
- 例如扩容时：
    newelements[i] = list->elements[i];
  两边都是 `eletype` 的值拷贝，`list->elements` 和 `newelements` 都是 `eletype*`，不需要再取地址。

#### Q4：再帮你捋顺几种访问方式（便于一眼记忆）
- 结构体指针访问成员：`ptr->member`
- 结构体对象访问成员：`obj.member`
- 动态数组（指针指向一段连续元素）：`ptr[i]` 等同于 `*(ptr + i)`
- 何时取地址 `&`：当函数要 T* 而你手上是 T；或你真的需要得到某个变量本身所在的地址。

小例子：
```cpp
Sequentiallist list;                 // 对象
initializelist(&list, 10);           // 形参是 Sequentiallist*，所以取地址传入
Sequentiallist* p = &list;           // p 已经是指针
insert(p, 0, 42);                    // 形参是 Sequentiallist*，直接传 p，不要再加 &
```

# 单向链表
[单向链表源码](https://github.com/Jaxon1216/cpp-notes/blob/main/%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/%E5%8D%95%E5%90%91%E9%93%BE%E8%A1%A8/%E6%BA%90%E7%A0%81.cpp)

## 节点与构造函数（初始化列表）
```cpp
struct ListNode {
    eleType data;
    ListNode* next;
    // 推荐写法：使用构造函数初始化列表，next 初始化为 nullptr
    ListNode(eleType x) : data(x), next(nullptr) {}
};
```

## 总结与常见疑问（单向链表）

#### Q1：参数名为什么常写成 `x`？
- 只是习惯用法/占位符，表示“传入的值”。你可以改为任何更语义化的名字，如 `value`、`val`、`dataIn`。
- 核心点：构造函数通过“初始化列表”把形参的值用于初始化成员：`data(x)`。

#### Q2：构造函数初始化列表的语法是什么？
- 语法：`ClassName(params) : member1(init1), member2{init2} { /* body */ }`
- `:` 后面是以逗号分隔的“成员初始化器”。可以用圆括号 `()` 或花括号 `{}` 初始化，推荐优先使用 `{}` 的一致初始化。
- 示例：
```cpp
ListNode(eleType value) : data{value}, next{nullptr} {}
```

#### Q3：初始化列表 vs 构造函数体内赋值，有什么区别？
- 初始化列表：直接“构造”成员，效率更高，且某些成员只能这样初始化。
- 构造函数体内赋值：先默认构造/零初始化成员，再进行赋值；对自定义类型相当于“先构造后赋值”，多一步。
- 对于 `const` 成员、引用成员、或成员类型没有默认构造函数的场景，必须使用初始化列表。

#### Q4：成员的实际初始化顺序按什么来？
- 按“成员在类中声明的顺序”，而不是初始化列表里书写的顺序。
```cpp
struct A {
    int a;
    int b;
    A() : b(2), a(1) {} // 实际顺序仍是先 a 后 b（按声明顺序）
};
```
- 建议让初始化列表的书写顺序与成员声明顺序一致，避免潜在的行为差异与编译器告警。

#### Q5：哪些场景必须或强烈建议使用初始化列表？
- 必须：`const` 成员、引用成员、成员类型没有默认构造函数。
- 强烈建议：大型对象或自定义类型（减少一次“构造后赋值”），以及需要为指针/句柄设定明确初值（如 `nullptr`）。

#### Q6：`NULL` 和 `nullptr` 有何区别？本处该用哪个？
- `nullptr` 是 C++11 引入的空指针字面量，类型安全，优先使用。
- 建议：`next(nullptr)` 而不是 `next(NULL)`。

#### Q7：与“成员内默认值”如何配合？
```cpp
struct ListNode {
    eleType data{};          // 成员内默认值（统一初始化）
    ListNode* next{nullptr}; // 成员内默认值
    ListNode(eleType value) : data{value} {} // 显式初始化 data，next 走其默认值
};
```
- 规则：当构造函数未在初始化列表中显式初始化某成员时，成员内默认值生效；一旦显式初始化，就以初始化列表为准。

# 串
## 关于 `数据结构/串/源码.cpp` 的关键点（0基础版）
- 1) 第一行：`#define _CRT_SECURE_NO_WARNINGS`
  - 作用：在 MSVC 编译器里关闭“使用不安全 C 函数”的警告，例如 `strcpy`、`strcat`。
  - 好处：示例代码可直接编译运行；实际项目建议改用更安全的变体（如 `strcpy_s`）。

- 2) 第14行 vs 第15行构造函数
  - 第14行 `String(const char* s)`：从 C 风格字符串构造对象（形如字面量 "abc"）。
  - 第15行 `String(const String& s)`：拷贝构造，从同类对象拷贝生成新对象。
  - 区别在于参数类型与用途不同：一个接收 `const char*`，一个接收 `const String&`。

- 3) 第25行友元函数与第92-94行
  - 友元声明：`friend ostream& operator<<(ostream& out, const String& s);`
  - 含义：允许该非成员函数访问 `String` 的私有成员（例如 `s.str`）。
  - 第92-94行实现展示了它如何直接访问 `s.str` 并返回 `ostream&` 以支持链式 `<<`。

- 4) 本文件用到的 `<cstring>` 内容
  - `strlen`：计算 C 字符串长度（不含终止符 `\0`）。
  - `strcpy`：把源 C 字符串拷贝到目标缓冲区。
  - `strcmp`：按字典序比较两个 C 字符串，相等返回 0。
  - `strcat`：把源 C 字符串追加到目标字符串末尾。

- 5) 第61行的 `this`
  - `this` 是指向“当前对象”的指针，类型为 `String*`。
  - 用法：`if (this != &s)` 用来判断是否自我赋值（同一对象），避免先 `delete[]` 自己的数据导致错误。

- 6) 第67行的 `*this`
  - `*this` 是“当前对象本身”的引用（把指针解引用后得到对象）。
  - 返回 `*this`（类型 `String&`）可支持链式赋值：`a = b = c;`。