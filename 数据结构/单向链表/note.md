
---

## 链表遍历

### [超级楼梯](https://acm.hdu.edu.cn/submit.php?pid=2041)
- hint: 走楼梯问题本质是斐波那契数列，每次可以走1步或2步，当前状态由前两个状态决定；
- 思路: 设f(M)为到达第M级的走法数，最后一步要么从M-1级走1步，要么从M-2级走2步，递推公式f(M)=f(M-1)+f(M-2)；

```math
f(M) = f(M-1) + f(M-2)
```

**递推关系解释**：  
- 最后一步可能从M-1级跨1级
- 或从M-2级跨2级
- 边界条件：f(1)=1, f(2)=1


#### 进制转换原理

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


### [二进制链表转整数](https://leetcode.cn/problems/convert-binary-number-in-a-linked-list-to-integer/description/)
- hint: 二进制转十进制需要从高位到低位累加，每遍历一个节点相当于左移一位再加当前位；
- 思路: 遍历链表，每次将累积结果乘2(左移)再加上当前节点值，模拟二进制转十进制的加权求和过程；
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


### [返回倒数第k个节点](https://leetcode.cn/problems/kth-node-from-end-of-list-lcci/description/)
- hint: 倒数第k个节点可以用快慢指针解决，让快指针先走k步形成窗口；
- 思路: 快指针先走k步，然后快慢指针同步移动，当快指针到达末尾时慢指针正好指向倒数第k个节点；
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


### [链表的中间结点](https://leetcode.cn/problems/middle-of-the-linked-list/)
- hint: 快慢指针经典应用，快指针速度是慢指针的2倍，当快指针到达末尾时慢指针正好在中点；
- 思路: 快指针每次走2步，慢指针每次走1步，利用速度差找到中间位置，需注意快指针的边界条件；
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

## 链表删除

### [删除指定元素](https://leetcode.cn/problems/remove-linked-list-elements/description/)
- hint: 删除操作需要前驱指针，头节点删除是特殊情况，哑节点可以统一处理；
- 思路: 创建哑节点指向原链表头，用前驱指针遍历，检查下一个节点是否需要删除，需要则跳过，否则移动前驱指针；

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

### [删除节点值](https://leetcode.cn/problems/delete-node-in-a-linked-list/)
- hint: 只给出要删除的节点指针，无法获取前驱，需要巧妙地将下一个节点的值覆盖当前节点；
- 思路: 将下一个节点的值复制到当前节点，然后删除下一个节点，等效于删除当前节点；
```cpp
class Solution {
public:
    void deleteNode(ListNode* node) {
        node->val = node->next->val;
        node->next = node->next->next;
    }
};
```

  
### [删除重复元素](https://leetcode.cn/problems/remove-duplicates-from-sorted-list/submissions/662037181/)

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

### [删除链表的倒数第 N 个结点](https://leetcode.cn/problems/remove-nth-node-from-end-of-list/)

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

## 链表插入
 
### [移除重复节点](https://leetcode.cn/problems/remove-duplicate-node-lcci/)
- 哈希表去重
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

## 链表的递归和迭代
 
### [从尾到头打印链表](https://leetcode.cn/problems/cong-wei-dao-tou-da-yin-lian-biao-lcof/submissions/662069306/)

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
  
### [递进行链表反转](https://leetcode.cn/problems/UHnkqh/)

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

### [从链表中移除节点](https://leetcode.cn/problems/remove-nodes-from-linked-list/description/)

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

  
### [链表中数字翻倍](https://leetcode.cn/problems/double-a-number-represented-as-a-linked-list/description/)

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
 
### [反转链表](https://leetcode.cn/problems/reverse-linked-list/description/)
- 迭代
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

### 递归详解

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