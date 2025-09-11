# 算法专题目录
- [斐波那契应用](#斐波那契应用)
- [进制转换算法](#进制转换算法)
  - [基本转换原理](#基本转换原理)
  - [链表应用实现](#链表应用实现)
- [快慢指针技巧](#快慢指针技巧)
  - [倒数第K个节点](#倒数第k个节点)
  - [链表中点问题](#链表中点问题)

---

## 斐波那契应用
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

---

## 进制转换算法
### 基本转换原理
**通用转换规则**：
1. N进制转十进制：  
   `加权求和法`：每位数字×N^(位数-1)  
   ``` 
   例：1A₍₁₆₎ = 1×16¹ + 10×16⁰ = 26
   ```

2. 十进制转N进制：  
   `除N取余法`：反复除N记录余数，逆序排列  
   ```
   例：13 → 1101：13/2余1 → 6/2余0 → 3/2余1 → 1/2余1
   ```

### 链表应用实现
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

---

## 快慢指针技巧
### 倒数第K个节点
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

### 链表中点问题
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
