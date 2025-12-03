//1.求奇数乘积,有多行，每行第一个数是n，后面是n个数。
//先做顺序表，再遍历，判断，做乘积
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

int main(){
    int n;
    while(cin >> n){
        Sequentiallist l;
        initializelist(&l,n);
        for(int i = 0; i < n; i++) {
            int x;
            cin >> x;
            insert(&l,i,x);
        }
        int pro = 1;
        for(int i = 0; i < n; i++){
            if(getElement(&l,i) % 2 == 1) pro *= getElement(&l,i);
        }
        cout << pro << endl;
        destroylist(&l);
    }
    return 0;

}
//比较快的
int a[1000];
int main(){
    int n;
    while(cin >> n){

        for(int i = 0; i < n; i++) {
            int x;
            cin >> x;
            a[i] = x;
        }
        int pro = 1;
        for(int i = 0; i < n; i++){
            if(a[i] % 2 == 1) pro *= a[i];
        }
        cout << pro << endl;
    }
    return 0;

}
//模版思维，比赛可以打印带进去，细节不易出错。