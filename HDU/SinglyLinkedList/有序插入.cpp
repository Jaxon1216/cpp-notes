//https://acm.hdu.edu.cn/submit.php?pid=2019

#include <iostream>
#include <stdexcept>

using namespace std;
#define eleType int

// 链表节点结构体
struct ListNode {
    eleType data;
    ListNode* next;
    ListNode(eleType x) : data(x), next(NULL) {}
};

// 单向链表类
class LinkedList {
private:
    ListNode* head;
    int size;

public:

    LinkedList() : head(NULL), size(0) {}    // 链表构造函数
    ~LinkedList();
    void insert(int i, eleType value);       // 在链表的第 i 个位置，插入一个值为 value 的结点
    void remove(int i);                      // 删除链表第 i 个位置的结点    
    ListNode* find(eleType value);           // 查找链表中值为 value 的结点
    ListNode* get(int i);                    // 获取链表中第 i 个位置的结点
    void update(int i, eleType value);       // 修改链表中第 i 个位置的结点的值为 value
    void print();    
	void append(eleType value);
	void ascinsert(eleType value);
};

LinkedList::~LinkedList() {
    ListNode* curr = head;
    while (curr != NULL) {
        ListNode* temp = curr;
        curr = curr->next;
        delete temp;
    }
}

void LinkedList::insert(int i, eleType value) {
    if (i < 0 || i > size) {
        throw std::out_of_range("Invalid position");
    }
    ListNode* newNode = new ListNode(value);
    if (i == 0) {
        // 在表头插入
        newNode->next = head;
        head = newNode;
    }
    else {
        ListNode* curr = head;
        for (int j = 0; j < i - 1; j++) {
            curr = curr->next;
        }
        // 在第 i 个位置插入
        newNode->next = curr->next;
        curr->next = newNode;
    }
    size++;
}

void LinkedList::remove(int i) {
    if (i < 0 || i >= size) {
        throw std::out_of_range("Invalid position");
    }
    if (i == 0) {
        // 删除表头结点
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
    else {
        ListNode* curr = head;
        for (int j = 0; j < i - 1; j++) {
            curr = curr->next;
        }
        // 删除第 i 个结点
        ListNode* temp = curr->next;
        curr->next = temp->next;
        delete temp;
    }
    size--;
}

ListNode* LinkedList::find(eleType value) {
    ListNode* curr = head;
    while (curr != NULL && curr->data != value) {
        curr = curr->next;
    }
    return curr;
}

ListNode* LinkedList::get(int i) {
    if (i < 0 || i >= size) {
        throw std::out_of_range("Invalid position");
    }
    ListNode* curr = head;
    for (int j = 0; j < i; j++) {
        curr = curr->next;
    }
    return curr;
}

void LinkedList::update(int i, eleType value) {
    if (i < 0 || i >= size) {
        throw std::out_of_range("Invalid position");
    }
    get(i)->data = value;
}

void LinkedList::print() {
    ListNode* curr = head;
    while (curr != NULL) {
        std::cout << curr->data << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}

void LinkedList::append(eleType value){
	insert(size,value);//不是size（）？？？因为 size 是成员变量，不是成员函数,第18行；
}

void LinkedList::ascinsert(eleType value){
	if(size == 0){
		insert(0,value);
		return ;
	}
	ListNode* curr = head;
	for(int i = 0;i < size; i++){
		if(value <= curr->data){
			insert(i,value);
			return;//?
		}
		curr = curr->next;
	}
	insert(size,value);
}
int main(){
	int n,x;
	
	while(cin >> n >> x){
		if(!n&&!x) break;
		LinkedList l;
		while(n--){
			int a;
			cin >> a;
			l.append(a);
		}
		l.ascinsert(x);
		l.print();
	}
	return 0;
}
		
			
			
			
			
			
			
			
			
