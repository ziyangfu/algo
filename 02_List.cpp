struct ListNode {
   int val;
   ListNode* next;
   ListNode(int x) : val(x), next(nullptr) {}
};

// 203
// 输入：head = [1,2,6,3,4,5,6], val = 6
// 输出：[1,2,3,4,5]
ListNode* removeElements(ListNode* head, int val) {
   ListNode* temp = nullptr;
   ListNode* current = nullptr;
   // 删除头结点
   while (head->next != nullptr && head->val == val)
   {
       head = head->next;
       temp = head;
       delete temp;
       temp = nullptr;
   }
   // 删除后续节点
   current = head;
   while (current != nullptr && current->next != nullptr)
   {
       if (current->next->val == val) {
           temp = current->next;
           current->next = current->next->next;
           delete temp;
       }
       else {
           current = current->next;
       }
   }
   return head;
}
// 203 虚拟头法，对于链表，添加虚拟头是一个常见的解题思路
ListNode* removeElements02(ListNode* head, int val) {
   ListNode* dummy = new ListNode(0);
   dummy->next = head;
   // 删除后续节点
   ListNode* current = head->next;
   while (current->next != nullptr)
   {
       if (current->next->val == val) {
           ListNode* temp = current->next;
           current->next = current->next->next;
           delete temp;
       }
       else {
           current = current->next;
       }
   }
   head = dummy->next;
   delete dummy;
   return head;
}

// 206 反转链表
ListNode* reverseList(ListNode* head) {
   ListNode* pre = nullptr;
   ListNode* current = head;

   while (current != nullptr) {
       // 保存下一个节点
       ListNode* next = current->next;
       // 转换一根指针
       current->next = pre;
       // 移动2个节点
       current = next;
       pre = current;
   }
   return pre;
}

// 0024
// 给定一个链表，两两交换其中相邻的节点，并返回交换后的链表
ListNode* swapPairs(ListNode* head) {
   ListNode* dummy = new ListNode(0);
   dummy->next = head;
   ListNode* current = dummy;
   while (current->next != nullptr &&
          current->next->next != nullptr) {
           ListNode* first = current->next;
           ListNode* second = current->next->next;

           first->next = second->next;
           second->next = first;
           current->next = second;

           current = first;
   }
   ListNode* newHead = dummy->next;
   delete dummy;
   return newHead;
}
// 给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点
// 关键是找到倒数第n个节点的前一个节点
// 快慢指针，滑动窗口
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    ListNode* first = dummy;
    ListNode* second = dummy;
    // 拉开2个指针的距离为n+1
    for (int i = 0; i <= n; i++) {
        first = first->next;
    }
    while (first != nullptr) {
        first = first->next;
        second = second->next;
    }
    ListNode* temp = second->next;
    second->next = second->next->next;
    delete temp;

    ListNode* newHead = dummy->next;
    delete dummy;
    return newHead;
}
// 0142
// 给定一个链表，返回链表开始入环的第一个节点。如果链表无环，则返回 null

// set容器法，空间复杂度大一些
#include <unordered_set>
ListNode *detectCycle(ListNode *head) {
    if (head == nullptr || head->next == nullptr) {
        return nullptr;
    }
    std::unordered_set<ListNode*> visited;
    ListNode* current = head;

    while (current != nullptr) {
        // 如果当前节点已访问过，说明是环的入口
        if (visited.count(current)) {
            return current;
        }
        // 记录当前节点
        visited,insert(current);
        current = current->next;
    }
    // 无环
    return nullptr;
}
// 快慢指针法 Floyd算法
// 通过数学确定：从头节点到环入口的距离等于从相遇点到环入口的距离
// 因此，把slow移动到head
ListNode *detectCycle02(ListNode *head) {
    if (head == nullptr || head->next == nullptr) {
        return nullptr;
    }
    // 第1步，检测是否有环
    ListNode* fast = head;
    ListNode* slow = head;
    while (fast != nullptr && fast->next != nullptr) {
        fast = fast->next->next;  // 2倍速度
        slow = slow->next; 
        if (fast == slow) {
            break; // 有环
        }
    }
    if (fast == nullptr || fast->next == nullptr) {
        return nullptr; // 无环
    }
    // 第2步，找到环的入口
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;

}
// 链表相交
// set法，插入一条链，另一条链搜索
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    if (headA == nullptr || headB == nullptr) {
        return nullptr;
    }
    std::unordered_set<ListNode*> visited;
    while (headA != nullptr) {
        visited.insert(headA);
        headA = headA->next;
    }
    while (headB != nullptr) {
        if (visited.count(headB)) {
            return headB;
        }
        headB = headB->next;
    }
    return nullptr;
}
// set法优化，每次插入一个headA节点，然后插入B节点前判断是否已存在
// 如果headA到nullptr，还没有找到重合点，则说明没有重合点
ListNode *getIntersectionNode02(ListNode *headA, ListNode *headB) {
    if (headA == nullptr || headB == nullptr) {
        return nullptr;
    }
    std::unordered_set<ListNode*> visited;
    while (headA != nullptr) {
        visited.insert(headA);
        if (visited.count(headB)) {
            return headB;
        }
        else {
            visited.insert(headB);
        }
        headA = headA->next;
        headB = headB->next;
    }
    return nullptr;
}
// 快慢指针法，双指针法
// 还有其他方法：长度差法，计算长度，先走差步，并行移动，直到相遇或到达nullptr
ListNode *getIntersectionNode03(ListNode *headA, ListNode *headB) {
    if (headA == nullptr || headB == nullptr) {
        return nullptr;
    }
    ListNode* pA = headA;
    ListNode* pB = headB;
    while (pA != pB) {
        pA == nullptr ? pA = headB : pA = pA->next;
        pB == nullptr ? pB = headA : pB = pB->next;
    }
    return pA;
}

// 寻找链表中点
// 快慢指针法的核心思想是利用不同速度的指针来获取链表的结构性信息
ListNode* findMiddle(ListNode* head) {
    if (head == nullptr)
    {
        return nullptr;
    }
    
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// 合并有序链表
// 将两个升序链表合并为一个新的升序链表并返回。
// 新链表是通过拼接给定的两个链表的所有节点组成的
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode* dummy = new ListNode(0);
    ListNode* current = dummy;

    while (l1 != nullptr && l2 != nullptr) {
        if (l1->val < l2->val) {
            current->next = l1;
            l1 = l1->next;
        }
        else {
            current->next = l2;
            l2 = l2->next;
        }
        current = current->next;
    }
    if (l1 == nullptr) {
        current->next = l2;
    }
    else {
        current->next = l1;
    }
    ListNode* newHead = dummy->next;
    delete dummy;
    return newHead;
}

// 链表排序：归并排序中的分治思想
