//增删改查
#include<iostream>
using namespace std;

#define eletype int 
//便于修改：如果以后想把元素类型从 int 改为 double，只需要改一行

struct Sequentiallist{
    eletype *elements;
    // elements 是一个指针，将来会指向一个数组
    //指向动态数组的指针，存储实际数据 //指针就是存储内存地址的变量，它指向内存中的某个位置。

    int size; 
    int capacity; 
    //size ≤ capacity，当size达到capacity时需要扩容
};

void initializelist(Sequentiallist *list, int capacity){
    list->elements = new eletype[capacity];
    //当我们要访问指针指向的结构体成员时，用 ->
    //如果 list 是普通变量（不是指针），就用 .

    list->size = 0;
    list->capacity = capacity;
}

void destroylist(Sequentiallist *list){
    delete[] list->elements;
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
        
        eletype *newelements = new eletype[newcapacity];
        for(int i = 0; i < list->size; i++)
            newelements[i] = list->elements[i];
        delete[] list->elements;
        list->elements = newelements;
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