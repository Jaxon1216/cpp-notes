## 目录
- [进制转换](#进制转换)
- [栈的应用](#栈的应用)
- [单调栈](#单调栈)

## 进制转换

### [HDU 2051. 进制转换-转2](http://acm.hdu.edu.cn/showproblem.php?pid=2051)

## 题意

输入一个十进制数N，将它转换成二进制数输出。

## 思路

- 十进制转二进制需要除2取余，余数序列需要逆序输出；
- 利用栈的特性，将余数依次入栈，然后出栈输出即可得到正确的二进制序列；

## 代码

```cpp
int main() {
	int n;
	while(cin>>n){
    	Stack<int> st;
		while(n){
			st.push(n % 2);
			n /= 2;
		}
		while(st.getSize()) cout << st.pop();
			cout << endl;
		}
    	return 0;
	}
```

### [HDU 2031. 进制转换-转任意](http://acm.hdu.edu.cn/showproblem.php?pid=2031)

## 题意

输入一个十进制数N，将它转换成R进制数输出。

## 思路

- 任意进制转换需要处理负数标记和大于9的数字用字母表示；
- 先处理负数符号，然后按目标进制除法取余入栈，出栈时对大于等于10的数字转换为字母A-F；

## 代码

```cpp
int main() {
	int a,b;
	while(cin >> a >> b){
		Stack<int> stk;
        //考虑特殊情况
		if(a < 0){      
			cout<<"-";
			a = - a;
		}
		while(a){
			stk.push(a % b);
			a /= b;
		}
		while(stk.getSize()){
			int x = stk.pop();
			if(x >= 10) printf("%c", 'A' + x - 10);
			else printf("%d", x);
		}
		cout<<endl;
	}
	return 0;
}
```

## 栈的应用

### [LCR 027. 回文链表](https://leetcode.cn/problems/aMhZSa/) <Badge type="tip" text="已解决" />

## 题意

给定一个链表的头节点 head ，请判断其是否为回文链表。

如果一个链表是回文，那么链表节点序列从前往后看和从后往前看是相同的。

## 思路

- 回文需要正反两个方向比较，链表只能单向遍历，需要借助数据结构实现逆序；
- 第一次遍历将所有节点入栈，第二次遍历同时从头和栈顶(尾)开始比较值，不相等即非回文；

## 代码

```cpp
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        stack<ListNode*> stk;
        ListNode* tmp = head;
        while(tmp){
            stk.push(tmp);
            tmp = tmp->next;
        }
        while(head){
            if(head->val != stk.top()->val) return false;
            stk.pop();
            head = head->next;
        }
        return true;

    }
};
```

### [1614. 括号的最大嵌套深度](https://leetcode.cn/problems/maximum-nesting-depth-of-the-parentheses/) <Badge type="tip" text="已解决" />

## 题意

给你一个 有效括号字符串 s，返回该字符串的 s 嵌套深度。

## 思路

- 括号的嵌套深度等价于栈的最大深度，但不需要真正使用栈；
- 用计数器模拟栈深度，遇到左括号深度+1并更新最大值，遇到右括号深度-1；

## 代码

```cpp
class Solution {
public:
    int maxDepth(string s) {
        int tmp=0, top =0;
        for(int i = 0; i < s.size(); i++){
            if(s[i] == '('){
                top++;
                tmp = max(tmp,top);
            }
            else if(s[i] == ')') top--;
        }
    return tmp;
    }
};
```

### [20. 有效的括号](https://leetcode.cn/problems/valid-parentheses/) <Badge type="tip" text="已解决" />

## 题意

给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。

## 思路

- 括号匹配经典栈应用，左括号入栈，右括号匹配栈顶，需要处理空栈和不匹配情况；
- 遇到左括号直接入栈，遇到右括号检查栈是否为空和是否与栈顶匹配，最后检查栈是否为空；

## 代码

```cpp
class Solution {
    bool isleft(char c){
        return c == '(' ||c == '[' || c=='{';
    }
    bool ismatch(char l, char r){
        return l == '(' && r == ')' || l == '[' && r ==']' || l == '{' && r == '}';
    }
public:
    bool isValid(string s) {
        stack<char> stk;
        for(int i = 0; i < s.size(); i++){
            if(isleft(s[i])) stk.push(s[i]);
            else{
                if(stk.empty()) return false;
                if(!ismatch(stk.top(),s[i])) return false;
                stk.pop();//注意这行代码的位置和作用
            }

        }
        return stk.empty();//这里
    }
};
```

## 单调栈

### [739. 每日温度](https://leetcode.cn/problems/daily-temperatures/) <Badge type="tip" text="已解决" />

## 题意

给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer ，其中 answer[i] 是指对于第 i 天，下一个更高温度出现在几天后。如果气温在这之后都不会升高，请在该位置用 0 来代替。

## 思路

- 寻找下一个更大元素的经典单调栈问题，栈中存储下标而非值；
- 维护单调递减栈存储下标，遇到更大温度时弹出栈中较小元素并计算距离，当前元素入栈；

## 代码

```cpp
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> stk;
        vector<int> ans;
        for(int i = 0; i < temperatures.size(); i++) ans.push_back(0);
        for(int i = 0; i < temperatures.size(); i++){
            while(stk.size()&&temperatures[stk.back()] < temperatures[i]){
                ans[stk.back()] = i - stk.back();
                stk.pop_back();
            }
            stk.push_back(i);
        }
        return ans;
    }
};
/*
考虑极端情况
1 2 3 4 5 6 
1 1 1 1 1 0

6 5 4 3 2 1
0 0 0 0 0 0 

在考虑普通情况
1 2 3 4 6 8 
*/
```

### [2487. 从链表中移除节点](https://leetcode.cn/problems/remove-nodes-from-linked-list/description/) <Badge type="tip" text="已解决" />

## 题意

给你一个链表的头节点 head 。

移除每个右侧有一个更大数值的节点。

## 思路

- 删除想到前驱，但是单调不增栈，需要头节点极大；遍历链表需要curr；
- 哑节点入栈（不是整个链表入了），比较，小于curr就弹出，节点整理好后处理指针；
- 单项链表也做过这道（递归）
- 既然可以用递归，那就一定可以用栈；深搜和栈联系起来广搜和队列联系起来；

## 代码

```cpp
class Solution {
public:
    ListNode* removeNodes(ListNode* head) {
        ListNode* dummy = new ListNode(1000001,head);
        ListNode* curr = head;
        vector<ListNode*> stk;
        stk.push_back(dummy);
        while(curr){
            while(stk.back()->val < curr->val) stk.pop_back();//连续弹栈，把if改成while
            stk.push_back(curr);
            curr = curr->next;
        }
        for(int i = 0; i < stk.size()-1; i++) stk[i]->next = stk[i+1];//没有这个减一会报错；
        return dummy->next;
    }
};
```
