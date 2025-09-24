#include <iostream>
#include <vector>
#include <cassert>

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// 测试目标函数
ListNode* removeElements(ListNode* head, int val) {
    if (head == nullptr) return nullptr;
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

// 创建链表的辅助函数
ListNode* createList(const std::vector<int>& values) {
    if (values.empty()) return nullptr;
    
    ListNode* head = new ListNode(values[0]);
    ListNode* current = head;
    
    for (size_t i = 1; i < values.size(); ++i) {
        current->next = new ListNode(values[i]);
        current = current->next;
    }
    
    return head;
}

// 将链表转换为vector的辅助函数
std::vector<int> listToVector(ListNode* head) {
    std::vector<int> result;
    ListNode* current = head;
    
    while (current != nullptr) {
        result.push_back(current->val);
        ListNode* temp = current;
        current = current->next;
        delete temp; // 清理内存
    }
    
    return result;
}

// 打印链表的辅助函数
void printList(ListNode* head) {
    ListNode* current = head;
    while (current != nullptr) {
        std::cout << current->val;
        if (current->next != nullptr) {
            std::cout << " -> ";
        }
        current = current->next;
    }
    std::cout << std::endl;
}

int main() {
    // 测试用例1: [1,2,6,3,4,5,6], val = 6
    // 预期输出: [1,2,3,4,5]
    std::cout << "Test case 1:" << std::endl;
    std::vector<int> input1 = {1, 2, 6, 3, 4, 5, 6};
    ListNode* head1 = createList(input1);
    std::cout << "Input: ";
    printList(head1);
    
    ListNode* result1 = removeElements(head1, 6);
    std::cout << "Output: ";
    printList(result1);
    std::cout << std::endl;
    
    // 测试用例2: 空链表
    std::cout << "Test case 2 (empty list):" << std::endl;
    ListNode* head2 = nullptr;
    ListNode* result2 = removeElements(head2, 1);
    std::cout << "Input: nullptr" << std::endl;
    std::cout << "Output: ";
    printList(result2);
    std::cout << std::endl;
    
    // 测试用例3: 所有元素都需要删除
    std::cout << "Test case 3 (all elements to be removed):" << std::endl;
    std::vector<int> input3 = {7, 7, 7, 7};
    ListNode* head3 = createList(input3);
    std::cout << "Input: ";
    printList(head3);
    
    ListNode* result3 = removeElements(head3, 7);
    std::cout << "Output: ";
    printList(result3);
    
    return 0;
}
