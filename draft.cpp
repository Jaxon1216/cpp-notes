#include <iostream>
#include <stdexcept>

using namespace std;

template<typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(T d) : data(d), next(NULL) {}
    };

    Node* front;
    Node* rear;
    int size;

public:
    Queue() : front(NULL), rear(NULL), size(0) {}
    ~Queue();
    void enqueue(T element);
    T dequeue();
    T getFront() const;
    int getSize() const;
};

template<typename T>
Queue<T>::~Queue() {
    while (front) {
        Node* temp = front;
        front = front->next;
        delete temp;
    }
}

template<typename T>
void Queue<T>::enqueue(T element) {
    if (rear == NULL) {
        rear = new Node(element);
        front = rear;
    }
    else {
        rear->next = new Node(element);
        rear = rear->next;
    }
    size++;
}

template<typename T>
T Queue<T>::dequeue() {
    if (front == NULL) {
        throw std::underflow_error("Queue is empty");
    }
    T element = front->data;
    Node* temp = front;
    front = front->next;
    delete temp;
    size--;
    if (size == 0) rear = NULL;
    return element;
}

template<typename T>
T Queue<T>::getFront() const {
    if (front == NULL) {
        throw std::underflow_error("Queue is empty");
    }
    return front->data;
}

template<typename T>
int Queue<T>::getSize() const {
    return size;
}

int main() {
    Queue<int> q1,q2;
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		for(int i = 1; i <= n; i++) q1.enqueue(i);
		while(q1.getSize() > 3){
			int cnt = 0;
			//筛选报1的到2队
			while(q1.getSize()){ //最终会排空，之前还一直理解不了，还以为执行完会有元素
				int v = q1.dequeue();
				cnt++;
				if(cnt % 2 == 1) q2.enqueue(v);
			}
			//考虑q2特殊情况
			if(q2.getSize() <= 3) {
				while(q2.getSize()) q1.enqueue(q2.dequeue());
				break;
			}
			
			cnt = 0;
			while(q2.getSize()){
				int v = q2.dequeue();
				cnt++;
				if(cnt%3 == 1||cnt%3 == 2) q1.enqueue(v);
			}
		
			int flag = 0;
			while(q1.getSize()){
				if(flag) cout <<' ';
				cout << q1.dequeue() ;
				flag++;
			}	
			cout << endl;
		}
	}
	return 0;
}