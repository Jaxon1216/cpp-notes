## 目录

- [链表遍历](#链表遍历)
- [链表删除](#链表删除)
- [链表插入](#链表插入)
- [链表的递归和迭代](#链表的递归和迭代)

## 链表遍历

### [HDU 2041. 超级楼梯](https://acm.hdu.edu.cn/submit.php?pid=2041)

## 题意

有一楼梯共M级，刚开始时你在第一级，若每次只能跨上一级或二级，要走上第M级，共有多少种走法？

## 思路

- 走楼梯问题本质是斐波那契数列，每次可以走1步或2步，当前状态由前两个状态决定；
- 设f(M)为到达第M级的走法数，最后一步要么从M-1级走1步，要么从M-2级走2步，递推公式f(M)=f(M-1)+f(M-2)；
- 边界条件：f(1)=1, f(2)=1

## 代码

```math
f(M) = f(M-1) + f(M-2)
```

### [1290. 二进制链表转整数](https://leetcode.cn/problems/convert-binary-number-in-a-linked-list-to-integer/description/) <Badge type="tip" text="已解决" />

## 题意

给你一个单链表的引用结点 head。链表中每个结点的值不是 0 就是 1。已知此链表是一个整数数字的二进制表示形式。

请你返回该链表所表示数字的 十进制值 。

## 思路

- 二进制转十进制需要从高位到低位累加，每遍历一个节点相当于左移一位再加当前位；
- 遍历链表，每次将累积结果乘2(左移)再加上当前节点值，模拟二进制转十进制的加权求和过程；

## 代码

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

### [面试题 02.02. 返回倒数第 k 个节点](https://leetcode.cn/problems/kth-node-from-end-of-list-lcci/description/) <Badge type="tip" text="已解决" />

## 题意

实现一种算法，找出单向链表中倒数第 k 个节点。返回该节点的值。

## 思路

- 倒数第k个节点可以用快慢指针解决，让快指针先走k步形成窗口；
- 快指针先走k步，然后快慢指针同步移动，当快指针到达末尾时慢指针正好指向倒数第k个节点；

## 代码

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

### [876. 链表的中间结点](https://leetcode.cn/problems/middle-of-the-linked-list/) <Badge type="tip" text="已解决" />

## 题意

给你单链表的头结点 head ，请你找出并返回链表的中间结点。

如果有两个中间结点，则返回第二个中间结点。

## 思路

- 快慢指针经典应用，快指针速度是慢指针的2倍，当快指针到达末尾时慢指针正好在中点；
- 快指针每次走2步，慢指针每次走1步，利用速度差找到中间位置，需注意快指针的边界条件；

## 代码

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

## 链表删除

### [203. 移除链表元素](https://leetcode.cn/problems/remove-linked-list-elements/description/) <Badge type="tip" text="已解决" />

## 题意

给你一个链表的头节点 head 和一个整数 val ，请你删除链表中所有满足 Node.val == val 的节点，并返回 新的头节点 。

## 思路

- 删除操作需要前驱指针，头节点删除是特殊情况，哑节点可以统一处理；
- 创建哑节点指向原链表头，用前驱指针遍历，检查下一个节点是否需要删除，需要则跳过，否则移动前驱指针；

## 代码

```cpp
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

### [237. 删除链表中的节点](https://leetcode.cn/problems/delete-node-in-a-linked-list/) <Badge type="tip" text="已解决" />

## 题意

有一个单链表的 head，我们想删除它其中的一个节点 node。

给你一个需要删除的节点 node 。你将 无法访问 第一个节点  head。

链表的所有值都是 唯一的，并且保证给定的节点 node 不是链表中的最后一个节点。

## 思路

- 只给出要删除的节点指针，无法获取前驱，需要巧妙地将下一个节点的值覆盖当前节点；
- 将下一个节点的值复制到当前节点，然后删除下一个节点，等效于删除当前节点；

## 代码

```cpp
class Solution {
public:
    void deleteNode(ListNode* node) {
        node->val = node->next->val;
        node->next = node->next->next;
    }
};
```

### [83. 删除排序链表中的重复元素](https://leetcode.cn/problems/remove-duplicates-from-sorted-list/submissions/662037181/) <Badge type="tip" text="已解决" />

## 题意

给定一个已排序的链表的头 head ， 删除所有重复的元素，使每个元素只出现一次 。返回 已排序的链表 。

## 思路

- 一般对于删除的问题都要定义前驱。
- 首先一定是返回head，然后定义curr和前驱，然后开始遍历。
- 用while可以删除连续的,注意pre也不能为空。

## 代码

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

### [19. 删除链表的倒数第 N 个结点](https://leetcode.cn/problems/remove-nth-node-from-end-of-list/) <Badge type="tip" text="已解决" />

## 题意

给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。

## 思路

- 双指针。
- 先让 fast 移动 n 次。
- 然后 fast 和 slow 一起移动。
- pre 记录 slow 的前驱，最后删除 slow。

## 代码

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

## 链表插入

### [面试题 02.01. 移除重复节点](https://leetcode.cn/problems/remove-duplicate-node-lcci/) <Badge type="tip" text="已解决" />

## 题意

编写代码，移除未排序链表中的重复节点。保留最开始出现的节点。

## 思路

- 哈希表去重。

## 代码

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

## 链表的递归和迭代

### [LCR 123. 图书整理 I](https://leetcode.cn/problems/cong-wei-dao-tou-da-yin-lian-biao-lcof/submissions/662069306/) <Badge type="tip" text="已解决" />

## 题意

书店店员需要再整理一种新的书架模式，该书架模式的特点是可以将书籍存放在一根长条形的链上。
现在请你写一个程序，返回一个数组，数组的元素是书籍的编号，顺序是从书架尾部到书架头部。

## 思路

- 遍历入栈（或vector），然后反转。

## 代码

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

### [LCR 024. 反转链表](https://leetcode.cn/problems/UHnkqh/) <Badge type="tip" text="已解决" />

## 题意

给定单链表的头节点 head ，请反转链表，并返回反转后的链表的头节点。

## 思路

- 递归法。

## 代码

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

### [2487. 从链表中移除节点](https://leetcode.cn/problems/remove-nodes-from-linked-list/description/) <Badge type="tip" text="已解决" />

## 题意

给你一个链表的头节点 head 。

移除每个右侧有一个更大数值的节点。

返回修改后链表的头节点 head 。

## 思路

- 递归法。
- 如果右边有比当前节点大的，返回右边的结果（当前节点被跳过）。
- 否则当前节点保留，接上右边的结果。

## 代码

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

### [2816. 翻倍以链表形式表示的数字](https://leetcode.cn/problems/double-a-number-represented-as-a-linked-list/description/) <Badge type="tip" text="已解决" />

## 题意

给你一个 非空 链表的头节点 head ，表示一个不含前导零的非负整数。

将链表 翻倍 后，返回头节点 head 。

## 思路

- 递归，从后往前处理进位。

## 代码

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

### [206. 反转链表](https://leetcode.cn/problems/reverse-linked-list/description/) <Badge type="tip" text="已解决" />

## 题意

给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。

## 思路

- 迭代法。
- 定义 pre, curr, next。

## 代码

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

## 递归详解

### 递归的核心概念
递归就是**函数调用自己**，但每次调用时处理的是**更小的问题**，直到达到**基础情况**（递归终止条件）。

### 链表反转的递归过程详解

以链表 `1→2→3→4→NULL` 为例：

#### 第1步：理解递归终止条件
```cpp
if(head == NULL || head->next == NULL) return head;
```
- 当链表为空或只有一个节点时，不需要反转，直接返回

#### 第2步：递归调用过程

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

#### 第3步：递归返回过程

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

#### 第4步：递归返回和反转操作

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
