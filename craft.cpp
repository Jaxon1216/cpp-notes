#include <iostream>
// 包含标准异常库，用于抛出和处理异常
#include <stdexcept>
using namespace std;
#define eleType int

// 链表节点结构体 - 这是链表的基本构建块
struct ListNode {
    eleType data;        // 存储节点的数据值
    ListNode* next;      // 指向下一个节点的指针（地址）
    // 构造函数：创建节点时初始化数据为x，next指针为NULL
    ListNode(eleType x) : data(x), next(NULL) {}
};

// 单向链表类 - 封装了链表的所有操作
class LinkedList {
private:
    ListNode* head;      // 头指针，指向链表的第一个节点
    int size;           // 记录链表中节点的数量

public:
    // 构造函数：创建空链表时，头指针为NULL，大小为0
    LinkedList() : head(NULL), size(0) {}
    // 析构函数：释放链表占用的所有内存
    ~LinkedList();
    // 在链表的第 i 个位置插入一个值为 value 的节点
    void insert(int i, eleType value);
    // 删除链表第 i 个位置的节点 
    void remove(int i);
    // 查找链表中值为 value 的节点，返回该节点的指针
    ListNode* find(eleType value);
    // 获取链表中第 i 个位置的节点，返回该节点的指针
    ListNode* get(int i);
    // 修改链表中第 i 个位置的节点的值为 value
    void update(int i, eleType value);
    // 打印链表中所有节点的数据
    void print();
};

// 析构函数实现：释放链表中所有节点的内存
LinkedList::~LinkedList() {
    ListNode* curr = head;    // curr指向当前要删除的节点
    // 遍历整个链表，逐个删除节点
    while (curr != NULL) {
        ListNode* temp = curr;  // 临时保存当前节点的地址
        curr = curr->next;      // curr移动到下一个节点，curr指着一个结构体
        delete temp;            // 删除之前保存的节点，释放内存
    }
}
//那我的理解是，一开始head指着第一个结构体，然后多了一个curr也指着第一个结构体，后开有一个tmp也指着第一个结构体，那就是三个，
// 但是后来curr往后移动一位，tmp指着的被删除，那head指针岂不是变成游离的？？？

//析构函数中可以"偷懒"不管head，但在其他函数中必须小心处理：
// 析构函数：对象马上就"死"了，head也会消失，所以不用管
// 普通函数：对象还"活着"，head必须正确维护，否则会出大问题
// 初始状态：
// curr ──→ ┌─────────────┐    ┌─────────────┐
//          │ ListNode    │    │ ListNode    │
//          │ data: 10    │    │ data: 20    │
//          │ next: ──────┼───→│ next: NULL  │
//          └─────────────┘    └─────────────┘

// 执行 curr = curr->next; 后：
//          ┌─────────────┐    ┌─────────────┐
//          │ ListNode    │    │ ListNode    │
//          │ data: 10    │    │ data: 20    │
//          │ next: ──────┼───→│ next: NULL  │
//          └─────────────┘    └─────────────┘
//                                    ↑
//                                curr 现在指向这里

// 插入函数实现：在指定位置插入新节点
void LinkedList::insert(int i, eleType value) {
    if (i < 0 || i > size) throw std::out_of_range("Invalid position");
    ListNode* newNode = new ListNode(value);
    
    // 如果在表头插入（第0个位置）
    if (i == 0) {
        newNode->next = head;   // 新节点的next指向原来的头节点
        head = newNode;         // 头指针指向新节点
    }
    else {
        // 在中间或末尾插入，需要先找到第i-1个节点
        ListNode* curr = head;
        // 移动到第i-1个节点的位置
        for (int j = 0; j < i - 1; j++) curr = curr->next;
        
        // 插入新节点：新节点的next指向curr的下一个节点
        newNode->next = curr->next;
        // curr的next指向新节点，完成插入
        curr->next = newNode;
    }
    // 链表长度增加1
    size++;
}

// 删除函数实现：删除指定位置的节点
void LinkedList::remove(int i) {
    if (i < 0 || i >= size) throw std::out_of_range("Invalid position");
    
    // 如果删除头节点（第0个位置）
    if (i == 0) {
        ListNode* temp = head;   // 临时保存头节点
        head = head->next;       // 头指针指向第二个节点
        delete temp;             // 删除原头节点，释放内存
    }
    else {
        // 删除中间或末尾的节点，需要先找到第i-1个节点
        ListNode* curr = head;
        // 移动到第i-1个节点的位置
        for (int j = 0; j < i - 1; j++) {
            curr = curr->next;
        }
        // temp指向要删除的节点（第i个节点）
        ListNode* temp = curr->next;
        // 跳过要删除的节点：curr直接指向temp的下一个节点
        curr->next = temp->next;
        // 删除节点，释放内存
        delete temp;
    }
    // 链表长度减少1
    size--;
}

// 查找函数实现：根据值查找节点
ListNode* LinkedList::find(eleType value) {
    ListNode* curr = head;    // 从头节点开始遍历
    // 遍历链表，直到找到匹配的值或到达链表末尾
    while (curr != NULL && curr->data != value) {
        curr = curr->next;    // 移动到下一个节点
    }
    // 返回找到的节点指针，如果没找到则返回NULL
    return curr;
}

// 获取函数实现：根据位置获取节点
ListNode* LinkedList::get(int i) {
    if (i < 0 || i >= size) throw std::out_of_range("Invalid position");
    ListNode* curr = head;    // 从头节点开始
    // 移动到第i个位置
    for (int j = 0; j < i; j++) {
        curr = curr->next;
    }
    // 返回第i个节点的指针
    return curr;
}

// 更新函数实现：修改指定位置节点的值
void LinkedList::update(int i, eleType value) {
    if (i < 0 || i >= size) throw std::out_of_range("Invalid position");
    // 获取第i个节点，然后修改其数据值
    get(i)->data = value;
}

// 打印函数实现：输出链表中所有节点的数据
void LinkedList::print() {
    ListNode* curr = head;    // 从头节点开始遍历
    // 遍历整个链表
    while (curr != NULL) {
        std::cout << curr->data << " ";  // 输出当前节点的数据
        curr = curr->next;               // 移动到下一个节点
    }
    std::cout << std::endl;              // 输出换行符
}
