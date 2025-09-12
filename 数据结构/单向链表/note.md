# 单向链表知识总结

## 目录
- [1. 链表遍历](#1-链表遍历)
  - [1.1 斐波那契应用](#11-斐波那契应用)
  - [1.2 进制转换算法](#12-进制转换算法)
  - [1.3 快慢指针技巧](#13-快慢指针技巧)
- [2. 链表删除](#2-链表删除)
  - [2.1 哑节点技巧](#21-哑节点技巧)
  - [2.2 值覆盖删除](#22-值覆盖删除)
  - [2.3 前驱指针删除](#23-前驱指针删除)
  - [2.4 倒数第N个节点删除](#24-倒数第n个节点删除)
- [3. 链表插入](#3-链表插入)
  - [3.1 哈希表去重构建](#31-哈希表去重构建)
- [4. 链表的递归和迭代](#4-链表的递归和迭代)
  - [4.1 递归实现](#41-递归实现)
  - [4.2 迭代实现](#42-迭代实现)
  - [4.3 递归详解](#43-递归详解)

---

## 1. 链表遍历

### 1.1 斐波那契应用

**题目链接**：  
[杭电OJ 2041 - 超级楼梯](https://acm.hdu.edu.cn/submit.php?pid=2041)

**算法解析**：  
设`f(M)`为从第1级到第M级的走法数，递推公式为：

```math
f(M) = f(M-1) + f(M-2)
```

**递推关系解释**：  
- 最后一步可能从M-1级跨1级
- 或从M-2级跨2级
- 边界条件：f(1)=1, f(2)=1

### 1.2 进制转换算法

#### 基本转换原理

**通用转换规则**：

1. **N进制转十进制**：  
   `加权求和法`：每位数字×N^(位数-1)  
   ```
   例：1A₍₁₆₎ = 1×16¹ + 10×16⁰ = 26
   ```

2. **十进制转N进制**：  
   `除N取余法`：反复除N记录余数，逆序排列  
   ```
   例：13 → 1101：13/2余1 → 6/2余0 → 3/2余1 → 1/2余1
   ```

#### 链表应用实现

**题目链接**：  
[LeetCode 1290 - 二进制链表转整数](https://leetcode.cn/problems/convert-binary-number-in-a-linked-list-to-integer/description/)

**算法实现**：  
```cpp
int getDecimalValue(ListNode* head) {
    int sum = 0;
    while(head) {
        sum = sum*2 + head->val;  // 核心算法
        head = head->next;
    }
    return sum;
}
```

**算法解析**：  
链表 1 → 0 → 1 的处理流程：
```
处理1：sum = 0×2 + 1 = 1  // 相当于1×2²的初始值
处理0：sum = 1×2 + 0 = 2  // 相当于(1×2 + 0)×2¹
处理1：sum = 2×2 + 1 = 5  // 最终结果1×2² + 0×2¹ + 1×2⁰
```

### 1.3 快慢指针技巧

#### 倒数第K个节点

**题目链接**：  
[LeetCode 面试题 02.02 - 返回倒数第k个节点](https://leetcode.cn/problems/kth-node-from-end-of-list-lcci/description/)

**算法实现**：
```cpp
int kthToLast(ListNode* head, int k) {
    ListNode *fast = head, *slow = head;
    while(k--) fast = fast->next;  // 快指针先走k步
    
    while(fast) {  // 同步移动直到末尾
        fast = fast->next;
        slow = slow->next;
    }
    return slow->val;
}
```

#### 链表中点问题

**题目链接**：  
[LeetCode 876 - 链表的中间结点](https://leetcode.cn/problems/middle-of-the-linked-list/)

**算法实现**：
```cpp
ListNode* middleNode(ListNode* head) {
    ListNode *fast = head, *slow = head;
    while(fast && fast->next) {
        fast = fast->next->next;  // 快指针每次走两步
        slow = slow->next;        // 慢指针每次走一步
    }
    return slow;
}
```

**算法特点**：  
- 快指针速度是慢指针2倍
- 当快指针到达末尾时，慢指针正好在中点
- 时间复杂度：O(n)，空间复杂度：O(1)

---

## 2. 链表删除

### 2.1 哑节点技巧

**题目链接**：  
[删除指定元素](https://leetcode.cn/problems/remove-linked-list-elements/description/)

#### 问题分析
删除链表中所有值为给定值 val 的节点，需处理多种情况：
- 普通节点删除
- 头节点可能被删除
- 连续多个节点需要删除
- 空链表或所有节点都需删除

#### 解题思路
使用 **哑节点 (dummy node)** 技巧简化头节点删除的处理：
- 创建哑节点作为辅助头节点，其 next 指向原链表头
- 使用前驱指针 pre 遍历链表，检查下一个节点是否需要删除
- 若需删除则跳过该节点，否则移动前驱指针

#### 代码实现
```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* newhead = new ListNode();
        newhead->next = head;
        ListNode* pre = newhead;
        while(pre->next){
            if(pre->next->val==val){
                    pre->next = pre->next->next;
            }
            else{
                pre = pre->next;
            }
        }
        return newhead->next;
    }
};
```

#### 复杂度分析
- **时间复杂度**：O(n)，需遍历链表一次
- **空间复杂度**：O(1)，仅使用常数额外空间

#### 关键点
- 哑节点解决了头节点可能被删除的边界问题
- 前驱指针 pre 使删除操作更简单，无需额外记录前一个节点
- 统一的处理逻辑适用于所有节点，包括连续多个需删除的节点

### 2.2 值覆盖删除

**题目链接**：  
[删除节点值](https://leetcode.cn/problems/delete-node-in-a-linked-list/)

```cpp
class Solution {
public:
    void deleteNode(ListNode* node) {
        node->val = node->next->val;
        node->next = node->next->next;
    }
};
```

### 2.3 前驱指针删除

**题目链接**：  
[删除重复元素](https://leetcode.cn/problems/remove-duplicates-from-sorted-list/submissions/662037181/)

```cpp
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        //一般对于删除的问题都要定义前驱？？
        //首先一定是返回head，然后定义curr和前驱，然后开始遍历
        ListNode* curr = head;
        ListNode* pre = NULL;
        while(curr){
            while(pre&&pre->val == curr->val){ //用while可以删除连续的,注意pre也不能为空
                pre->next = curr->next;
                curr = pre->next;
                if(!curr) break;
            }
            //删完之后继续遍历
            if(!curr) break;
            pre = curr;
            curr = curr->next;//看到这个操作就要想到是否为空
        }
        return head;
    }
};
```

### 2.4 倒数第N个节点删除

**题目链接**：  
[删除链表的倒数第 N 个结点](https://leetcode.cn/problems/remove-nth-node-from-end-of-list/)

```cpp
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* fast = head;
        ListNode* slow = head;
        ListNode* pre = NULL;
        while(n--){
            fast = fast->next;
        }
        while(fast){
            fast = fast->next;
            pre = slow;
            slow = slow->next;
        }
        if(!pre) return head->next; //别忘了考虑删除掉第一个元素
        pre->next = slow->next;
        return head;
    }
};
```

---

## 3. 链表插入

### 3.1 哈希表去重构建

**题目链接**：  
[移除重复节点](https://leetcode.cn/problems/remove-duplicate-node-lcci/)

```cpp
class Solution {
public:
    ListNode* removeDuplicateNodes(ListNode* head) {
        //一定要注意这里！！
        if(head == NULL) return NULL;//没有的话会产生空指针访问错误
        ListNode* tmp = head;
        ListNode* pre = head;
        ListNode* curr = head->next;
        bool hash[20001] = {0};
        hash[head->val] = 1;
        while(curr){
            if(!hash[curr->val]){
                hash[curr->val] = 1;
                tmp->next = curr;
                tmp = tmp->next;
            }
            pre = curr;
            curr = curr->next;
        }
        tmp->next = NULL;
        return head;
    }
};
```

---

## 4. 链表的递归和迭代

### 4.1 递归实现

#### 数组链表结合
**题目链接**：  
[从尾到头打印链表](https://leetcode.cn/problems/cong-wei-dao-tou-da-yin-lian-biao-lcof/submissions/662069306/)

```cpp
vector<int> reverseBookList(ListNode* head) {
    vector<int> ans;
    while(head){
        ans.push_back(head->val);
        head = head->next;
    }
    int l = 0, r = ans.size()-1;
    while(l < r){
        int temp = ans[l];
        ans[l] = ans[r];
        ans[r] = temp;
        l++;
        r--;
    }
    return ans;
}
```

#### 递归链表反转
**题目链接**：  
[递进行链表反转](https://leetcode.cn/problems/UHnkqh/)

```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(head == NULL || head->next == NULL) return head;
        ListNode* newhead = reverseList(head->next);//看成整体就行了
        head->next->next = head;
        head->next = NULL;
        return newhead;
    }
};
```

#### 递归删除元素
**题目链接**：  
[从链表中移除节点](https://leetcode.cn/problems/remove-nodes-from-linked-list/description/)

```cpp
class Solution {
public:
    ListNode* removeNodes(ListNode* head) {
        if(head == NULL) return head;
        head->next = removeNodes(head->next);
        if(head->next == NULL) return head;
        if(head->val < head->next->val) return head->next;
        return head;
    }
};
```

#### 链表翻倍
**题目链接**：  
[链表中数字翻倍](https://leetcode.cn/problems/double-a-number-represented-as-a-linked-list/description/)

```cpp
class Solution {
    void dodouble(ListNode* head, int *cap){
        if(head == NULL){
            *cap = 0;
            return;
        }
        int val;
        dodouble(head->next, &val);
        head->val = head->val*2 + val;
        *cap = head->val / 10;
        head->val %= 10;
    }
public:
    ListNode* doubleIt(ListNode* head) {
        int val;
        dodouble(head,&val);
        return val==0 ? head : new ListNode(val,head);
    }
};
```

### 4.2 迭代实现

#### 迭代链表反转
**题目链接**：  
[反转链表](https://leetcode.cn/problems/reverse-linked-list/description/)

```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* pre = NULL;
        ListNode* curr = head;
        while(curr){
            ListNode* next = curr->next;
            curr->next = pre;//箭头方向
//下面两行先写出来：往后移动
            pre = curr;
            curr = next;
        }
        return pre;
    }
};
```

### 4.3 递归详解

#### 递归的核心概念
递归就是**函数调用自己**，但每次调用时处理的是**更小的问题**，直到达到**基础情况**（递归终止条件）。

#### 链表反转的递归过程详解

以链表 `1→2→3→4→NULL` 为例：

##### 第1步：理解递归终止条件
```cpp
if(head == NULL || head->next == NULL) return head;
```
- 当链表为空或只有一个节点时，不需要反转，直接返回

##### 第2步：递归调用过程

```
原始链表: 1→2→3→4→NULL

调用栈（从上到下）:
┌─────────────────────────────────┐
│ reverseList(1)                  │ ← 最外层调用
│ 调用 reverseList(2)             │
├─────────────────────────────────┤
│ reverseList(2)                  │
│ 调用 reverseList(3)             │
├─────────────────────────────────┤
│ reverseList(3)                  │
│ 调用 reverseList(4)             │
├─────────────────────────────────┤
│ reverseList(4)                  │ ← 基础情况，直接返回4
└─────────────────────────────────┘
```

##### 第3步：递归返回过程

**第1次调用：`reverseList(1)`**
- `head = 1`, `head->next = 2`
- 不满足终止条件，继续递归
- 调用 `reverseList(2)` 并等待结果

**第2次调用：`reverseList(2)`**
- `head = 2`, `head->next = 3`
- 不满足终止条件，继续递归
- 调用 `reverseList(3)` 并等待结果

**第3次调用：`reverseList(3)`**
- `head = 3`, `head->next = 4`
- 不满足终止条件，继续递归
- 调用 `reverseList(4)` 并等待结果

**第4次调用：`reverseList(4)`**
- `head = 4`, `head->next = NULL`
- **满足终止条件！** 直接返回 `4`

##### 第4步：递归返回和反转操作

现在开始**从内向外**返回并执行反转：

**从 `reverseList(4)` 返回：**
- 返回 `4`（单个节点，无需反转）

**回到 `reverseList(3)`：**
```cpp
ListNode* newhead = reverseList(head->next); // newhead = 4
head->next->next = head;  // 4->next = 3，形成 4→3
head->next = NULL;        // 3->next = NULL
return newhead;           // 返回 4
```
现在链表变成：`4→3→NULL`

**回到 `reverseList(2)`：**
```cpp
ListNode* newhead = reverseList(head->next); // newhead = 4
head->next->next = head;  // 3->next = 2，形成 4→3→2
head->next = NULL;        // 2->next = NULL
return newhead;           // 返回 4
```
现在链表变成：`4→3→2→NULL`

**回到 `reverseList(1)`：**
```cpp
ListNode* newhead = reverseList(head->next); // newhead = 4
head->next->next = head;  // 2->next = 1，形成 4→3→2→1
head->next = NULL;        // 1->next = NULL
return newhead;           // 返回 4
```
最终结果：`4→3→2→1→NULL`