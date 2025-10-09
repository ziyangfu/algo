#include <iostream>
#include <cassert>
#include <stack>

// 假设 MyQueue 类已经定义（如你提供的实现）
class MyQueue {
private:
    std::stack<int> inStack;
    std::stack<int> outStack;

public:
    /** Initialize your data structure here. */
    MyQueue() {
        
    }

    void in2out() { 
        if (outStack.empty()) {
            while(!inStack.empty()) {
                outStack.push(inStack.top());
                inStack.pop();
            }
        }
    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        // 恢复回来
        while(!outStack.empty()) {
            inStack.push(outStack.top());
            outStack.pop();
        }
        inStack.push(x);
        
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        // 弹出最前面那个
        in2out(); // 换栈，调转栈内顺序
        int front = outStack.top();
        outStack.pop();
        return front;
    }
    
    /** Get the front element. */
    int front() {
        // 获取最前面的元素
        in2out(); // 换栈，调转栈内顺序
        return outStack.top();
    }

    int back() {
        // 恢复回来
        while(!outStack.empty()) {
            inStack.push(outStack.top());
            outStack.pop();
        }
        return inStack.top();

    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        // 判空
        return inStack.empty() && outStack.empty();
    }
};


int main() {
    MyQueue queue;
    
    // 测试空队列
    assert(queue.empty() == true);
    std::cout << "测试1: 空队列检查通过" << std::endl;
    
    // 测试 push 操作
    queue.push(1);
    queue.push(2);
    queue.push(3);
    assert(queue.empty() == false);
    std::cout << "测试2: push操作后队列非空检查通过" << std::endl;
    
    // 测试 front 操作
    assert(queue.front() == 1);
    std::cout << "测试3: front元素检查通过，值为 " << queue.front() << std::endl;
    
    // 测试 back 操作
    assert(queue.back() == 3);
    std::cout << "测试4: back元素检查通过，值为 " << queue.back() << std::endl;
    
    // 测试 pop 操作
    assert(queue.pop() == 1);
    std::cout << "测试5: 第一次pop操作通过，弹出值为 " << 1 << std::endl;
    
    // 再次检查 front 和 back
    assert(queue.front() == 2);
    std::cout << "测试6: pop后front元素检查通过，值为 " << queue.front() << std::endl;
    
    assert(queue.back() == 3);
    std::cout << "测试7: pop后back元素检查通过，值为 " << queue.back() << std::endl;
    
    // 继续 pop
    assert(queue.pop() == 2);
    std::cout << "测试8: 第二次pop操作通过，弹出值为 " << 2 << std::endl;
    
    // 添加新元素后再测试
    queue.push(4);
    queue.push(5);
    assert(queue.front() == 3);
    std::cout << "测试9: push新元素后front元素检查通过，值为 " << queue.front() << std::endl;
    
    assert(queue.back() == 5);
    std::cout << "测试10: push新元素后back元素检查通过，值为 " << queue.back() << std::endl;
    
    // 继续 pop 所有元素
    assert(queue.pop() == 3);
    assert(queue.pop() == 4);
    assert(queue.pop() == 5);
    std::cout << "测试11: 连续pop操作通过" << std::endl;
    
    // 检查队列是否为空
    assert(queue.empty() == true);
    std::cout << "测试12: 所有元素pop后队列为空检查通过" << std::endl;
    
    // 测试交替 push/pop 操作（你提到的场景）
    queue.push(10);
    queue.push(20);
    assert(queue.pop() == 10);
    queue.push(30);
    assert(queue.front() == 20);
    assert(queue.back() == 30);
    assert(queue.pop() == 20);
    assert(queue.pop() == 30);
    assert(queue.empty() == true);
    std::cout << "测试13: 交替push/pop操作场景测试通过" << std::endl;
    
    std::cout << "\n所有测试通过！队列实现正确。" << std::endl;
    
    return 0;
}
