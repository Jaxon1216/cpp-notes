//增删改查
#include<iostream>
using namespace std;

#define eletype int 
//便于修改：如果以后想把元素类型从 int 改为 double，只需要改一行

struct Sequentiallist{
    /* =====================【要点1｜显眼说明】===================== 
       elements 的类型是 eletype*，它是“指针变量”，本身只存地址，不是数组。
       之所以能写 elements[i]，是因为第19行 new 之后，它会指向一段
       “连续的 eletype 元素内存”，下标运算只是“指针 + 偏移”的语法糖。
       区别提醒：
       - sizeof(elements) 得到的是指针大小（通常8字节），不是数组大小；
       - 指针可以被重新赋值（指向别处），数组名在作用域内不可被重新赋值。
       ========================================================= */
    eletype *elements;

    int size; 
    int capacity; 
    //size ≤ capacity，当size达到capacity时需要扩容
};

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

void destroylist(Sequentiallist *list){
    // 【要点4】delete[] 释放的是 elements 当前指向的“数组内存”，不是指针变量本身
    delete[] list->elements;
    list->elements = nullptr; // 置空，避免悬空指针被误用
    list->size = 0;
    list->capacity = 0;
}

int size(Sequentiallist *list){
    return list->size;
}

int isempty(Sequentiallist *list){
    return list->size == 0;
}

void insert(Sequentiallist *list, int index, eletype element){
    if(index < 0 || index > list->size) throw std::invalid_argument("invalid index");
    //throw 抛出异常，用throw更加优雅，健壮，安全。

    if(list->size == list->capacity){
        int newcapacity = list->capacity * 2;
        //如果当前容量不够，则扩容
        
        /* =====================【要点3｜显眼说明｜扩容三步】=====================
           1) 先申请“新数组内存”（一排新的连续柜子）
           2) 再把“旧数组里的数据”逐个搬过去（拷贝内容）
           3) 最后把 elements 这个“指针标签”改贴到新数组（改指向，不拷贝内容）
           解释：newelements 与 list->elements 都是 eletype*，类型相同，只是指向不同内存。
           - 下方 for 循环：拷贝的是“内容”
           - list->elements = newelements;：只是“改指向”，完全不搬内容
           （等价写法：可用 std::copy 或 std::memcpy 来替代手写 for）
           ================================================================ */
        eletype *newelements = new eletype[newcapacity]; // 1) 申请新内存
        for(int i = 0; i < list->size; i++)              // 2) 拷贝旧内容到新内存
            newelements[i] = list->elements[i];
        delete[] list->elements;                          // 释放旧内存（不是删指针变量）
        list->elements = newelements;                     // 3) 改指向到新内存
        list->capacity = newcapacity;
    }

    for(int i = list->size; i > index; i--)
        list->elements[i] = list->elements[i-1];
    list->elements[index] = element;
    list->size++;
}

void deleteElement(Sequentiallist *list, int index){
    if(index < 0 || index >= list->size) throw std::invalid_argument("invalid index");
    for(int i = index; i < list->size - 1; i++)
        list->elements[i] = list->elements[i+1];
    list->size--;
}

int findElement(Sequentiallist *list, eletype element){
    for(int i = 0; i < list->size; i++)
        if(list->elements[i] == element) return i;
    return -1;
}

eletype getElement(Sequentiallist *list, int index){
    if(index < 0 || index >= list->size) throw std::invalid_argument("invalid index");
    return list->elements[index];
}

eletype updateElement(Sequentiallist *list, int index, eletype value){
    if(index < 0 || index >= list->size) throw std::invalid_argument("invalid index");
    list->elements[index] = value;
}
/*
int main(){
    Sequentiallist list;
    initializelist(&list, 10);
    //初始化顺序表，容量为10
    for(int i = 0; i < 10; i++) insert(&list, i, i*10 );
    //插入10个元素，值为0到90
    cout << size(&list) << endl;
    //输出顺序表长度，10
    cout << isempty(&list) << endl;
    //输出顺序表是否为空，0
    for(int i = 0; i < 10; i++) cout << getElement(&list, i) << " ";
    cout << endl;
    //输出顺序表，0到90，顺序表为0，10，20，30，40，50，60，70，80，90
    deleteElement(&list, 5);
    //删除第6个元素，50，顺序表为0，10，20，30，40，60，70，80，90
    updateElement(&list, 1, 1314);
    //更新第2个元素，1314，顺序表为0，1314，20，30，40，60，70，80，90
    for(int i = 0; i < 9; i++) cout << getElement(&list, i) << " ";
    cout << endl;
    int index = findElement(&list, 20);
    //查找20，返回2
    updateElement(&list, index, 520);
    //更新20，520，顺序表为0，1314，520，30，40，60，70，80，90
    destroylist(&list);
    return 0;
}
*/

/*
=====================【总结与常见疑问｜显眼整理】=====================

Q1：为什么 main 里要写 initializelist(&list, 10)？
- 形参是 Sequentiallist*，需要“对象地址”。main 里有对象 `Sequentiallist list;`，
  所以要传 `&list`（取地址，类型刚好是 Sequentiallist*）。

Q2：以后凡是“操作指针指向的对象”，都要加 & 吗？
- 不。仅当“形参类型是指针 T*，而你手里是一个对象 T”时，才需要写 `&obj`。
  小抄：
  - 你有对象 T obj，函数要 T*        → 传 &obj
  - 你已有指针 T* p，函数要 T*         → 直接传 p（不要再 &）
  - 函数要引用 T&                     → 直接传 obj（不用 &）
  - 函数要值 T（拷贝）                 → 直接传 obj（函数内改动不影响外部）

Q3：为什么在 insert 等函数里不写成 &elements？
- 因为 `elements` 的类型已经是 `eletype*`（指向元素的指针），正是我们需要的。
- `&elements` 的类型会变成 `eletype**`（指向“指针变量本身”的地址），
  这既不是数组起始地址，也不是我们要用来下标访问的类型，反而会出错。
- 例如扩容时：
    newelements[i] = list->elements[i];
  两边都是 `eletype` 的值拷贝，`list->elements` 和 `newelements` 都是 `eletype*`，不需要再取地址。

Q4：再帮你捋顺几种访问方式（便于一眼记忆）
- 结构体指针访问成员：`ptr->member`
- 结构体对象访问成员：`obj.member`
- 动态数组（指针指向一段连续元素）：`ptr[i]` 等同于 `*(ptr + i)`
- 何时取地址 `&`：当函数要 T* 而你手上是 T；或你真的需要得到某个变量本身所在的地址。

小例子：
  Sequentiallist list;                 // 对象
  initializelist(&list, 10);           // 形参是 Sequentiallist*，所以取地址传入
  Sequentiallist* p = &list;           // p 已经是指针
  insert(p, 0, 42);                    // 形参是 Sequentiallist*，直接传 p，不要再加 &

====================================================================
*/