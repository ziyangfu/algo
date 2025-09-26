// 232.用栈实现队列
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
// 225.用队列实现栈
// 使用1个队列实现
// 也可以用2个队列实现，关键在push中：
    // void push(int x) {
    //     // 将新元素添加到空队列q2
    //     q2.push(x);
        
    //     // 将q1中的所有元素移动到q2
    //     while (!q1.empty()) {
    //         q2.push(q1.front());
    //         q1.pop();
    //     }
        
    //     // 交换两个队列，使q1始终保持栈的顺序
    //     std::swap(q1, q2);
    // }

class MyStack {
private:
    std::queue<int> q; 
public:
    MyStack() {
        
    }
    void push(int x) {
        int size = q.size();
        q.push(x);
        // 将之前的所有元素重新排列到新元素后面
        for (int i = 0; i < size; i++) {
            q.push(q.front());
            q.pop();
        }

    }

    int top() {
        return q.front();

    }

    void pop() {
        int top = q.front();
        q.pop();
        return top;

    }

    bool empty() {
        return q.empty();
    }

};
// 20.有效的括号
// 经典的栈的解决思路
bool isValid(string s) {
    std::stack<char> st;

    char top = st.top();

    for (c : s) {
        // 遇到左括号时，将对应的右括号入栈，方便后面比对
        if (c == '(') { st.push(')');}
        else if (c == '[') { st.push(']');}
        else if (c == '{') { st.push('}');}
         // 遇到右括号时，检查是否与栈顶元素匹配
        else {
            // 如果栈为空或者不匹配，则无效
            if (st.empty() || c != st.top()) {
                return false;
            }
            st.pop();  // 匹配成功，弹出栈顶元素
        }
    }
    return st.empty(); // 最后检查栈是否为空，空则说明所有括号都匹配
}
// 1047.删除字符串中的所有相邻重复项
//消消乐游戏
string removeDuplicates(string s) {
    std::string newStr;
    std::stack<char> st;
    for (char c : s) {
        if (st.empty() || c != st.top()) {
            st.push(c);
        }
        else {
            st.pop();
        }
    }
    // 从栈中取出字符，并拼接成新的字符串
    while (!st.empty()) {
        newStr += st.top();
        st.pop();
    }
    // 反转字符串，从栈中拿出来的，是反的
    std::reverse(newStr.begin(), newStr.end());
    return newStr;
}
// 直接使用 std::string 作为栈来避免反转操作
string removeDuplicates(string s) {
    string result;
    for (char c : s) {
        if (result.empty() || c != result.back()) {
            result.push_back(c);
        } else {
            result.pop_back();
        }
    }
    return result;
}
// 150.逆波兰表达式求值
// tokens = ["4","13","5","/","+"] 
// (4 + (13 / 5)) = 6
int evalRPN(vector<string>& tokens) {
    std::stack<int> st;
    
    for (auto c : tokens) {
        if (c == "+" || c == "-" || c == "*" || c == "/") {
            int c1 = st.top();
            st.pop();
            int c2 = st.top();
            st.pop();
            int sum;
            switch (c) {
                case "+":
                    sum = c2 + c1;
                    break;
                case "-":
                    sum = c2 - c1;
                    break;
                case "*":
                    sum = c2 * c1;
                    break;
                case "/":
                    sum = c2 / c1;
                    break;
            }
            st.push(sum);
        }
        else {
            st.push(stoi(c));
        }
    }

    return st.top();
}
// 239.滑动窗口最大值
// 暴力法
// 优先队列（堆) — 最起码掌握这种
// 单调队列解法
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    std::vector<int> result;
    auto start = 0;
    auto end = k - 1;
    // 处理第一个窗口
    if (nums.empty() || k == 0) return result;


    while (end < nums.size()) {
        // 每次只移动一位，说明上一次的最大值，只要不是划出的那一位，就可以复用
        // 优化：如果消失的不是最大值，那么可以复用
        // nums[end]：新加入的值
        // result.back()：上一次的最大值，还在区间中
        if (!result.empty() && result.back() != nums[start - 1]) {
            result.push_back(max(result.back(), nums[end]));
        }
        else {
            // 区间最大值逻辑
            int max = INT_MIN;
            for(auto i = start; i <= end; i++) {
                if (max < nums[i]) {
                    max = nums[i];
                }
            }
            result.push_back(max);
        }
        start++;
        end++;
    }
    return result;
}
// 单调队列解法
// 不好理解
vector<int> maxSlidingWindow01(vector<int>& nums, int k) {
    std::vector<int> result;
    std::deque<int> dq; // 存储数组下标，保持对应值单调递减

    for (int i = 0; i < nums.size(); i++) {
        // 移除超出窗口范围的元素
        if (!dp.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }
        // 维护单调递减队列
        while(!dq.empty() && nums[dq.back()] < nums[i]) {
            dp.pop_back();
        }

        dp.push_back(i);
        // 当窗口大小达到k时，开始记录结果
        if (i >= k -1) {
            result.push_back(nums[dp.front()]);

        }
 
    }
    return result;
}

// 优先队列（堆）解决滑动窗口最大值问题
vector<int> maxSlidingWindow02(vector<int>& nums, int k) {
    vector<int> result;
    // 使用优先队列存储pair<值, 索引>
    // 默认是最大堆，按照pair的第一个元素（值）进行排序
    priority_queue<pair<int, int>> pq;
    
    for (int i = 0; i < nums.size(); i++) {
        // 将当前元素加入堆中
        pq.push({nums[i], i});
        
        // 当窗口大小达到k时开始处理
        if (i >= k - 1) {
            // 移除堆中超出窗口范围的元素
            // 堆顶元素的索引如果小于当前窗口的起始位置，则需要移除
            while (!pq.empty() && pq.top().second <= i - k) {
                pq.pop();
            }
            
            // 堆顶元素就是当前窗口的最大值
            result.push_back(pq.top().first);
        }
    }
    return result;
}

vector<int> topKFrequent(vector<int>& nums, int k) {
    std::vector<int> result;
    std::priority_queue<std::pair<int, int>> pq;  // (频率, 数字) 的最大堆
    std::unordered_map<int, int> map;

    // hash 记录 数字与出现次数
    for (auto num : nums)
    {
        map[num]++;
    }

    // 创建大顶堆
    for (auto it = map.begin(); it != map.end(); it++) {
        pq.push(std::make_pair(it->second, it->first));
    }
    // pop出k个数字，写入结果数组
    for (int i = 0; i < k; i++) {
        result.push_back(pq.top().second);
        pq.pop();
    }
    return result;
}
// 用最小堆，把频率最少的数字pop出来
vector<int> topKFrequent02(vector<int>& nums, int k) {
    vector<int> result;
    // 使用最小堆，保持堆大小为k
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    unordered_map<int, int> freqMap;

    // 统计频率
    for (auto num : nums) {
        freqMap[num]++;
    }

    // 维护大小为k的最小堆
    for (auto it = freqMap.begin(); it != freqMap.end(); it++) {
        pq.push(make_pair(it->second, it->first));
        if (pq.size() > k) {
            pq.pop();  // 移除频率最小的元素
        }
    }
    
    // 取出结果（因为是最小堆，需要反转）
    while (!pq.empty()) {
        result.push_back(pq.top().second);
        pq.pop();
    }
    
    // 反转结果以获得正确顺序
    reverse(result.begin(), result.end());
    return result;
}



















/**
https://leetcode.cn/leetbook/read/illustration-of-algorithm/7f6f91/
*/
#include <stack>

class Solution {
public:
    bool validateBookSequences(vector<int>& putIn, vector<int>& takeOut) {
        std::stack<int> stk_;
        int i = 0;
        for (auto num : putIn) {
          stk_.push(num);
          while (!stk_.empty() && stk_.top() == takeOut[i]){
                stk_.pop();
                i++;
            }
        }
        return stk_.empty();
    }
};

// --------------------------------------------------------------------------------
#include <vector>
#include <algorithm>
using namespace std;
    
class Solution {
public:
    vector<int> maxAltitude(vector<int>& heights, int limit) {
        vector<int> result{};
        int i = 0;
        if (heights.empty())
        {
            return result;
        }
        
        while(i < heights.size() + 1 - limit) {
            vector<int> tmp(heights.begin() + i , heights.begin() + i + limit);
            result.push_back(getMax(tmp));
            i++;
        }
        return result;

    }
    int getMax(vector<int>& sub) {
        std::make_heap(sub.begin(), sub.end());
        return sub.front();
    }
};
// žü¿ìËÙµÄœâ·š£º
class Solution {
public:
    vector<int> maxAltitude(vector<int>& heights, int limit) {
        int k = limit;
        vector<int> nums = heights;

        int n = nums.size();
        deque<int> dq;
        vector<int> ans;
        for (int i = 0; i < n; i ++ ) {
            if (dq.size() && dq.front() < i - k + 1) 
                dq.pop_front();
            while (dq.size() && nums[dq.back()] <= nums[i]) dq.pop_back();
            dq.push_back(i);
            if (i - k + 1 >= 0) 
                ans.push_back(nums[dq.front()]);
        }
        return ans;
    }

};


*/
#include <queue>
#include <deque>
class Checkout {
private:
    std::queue<int> q;
    //std::stack<int> stk;
    std::deque<int> deq;
public:
    Checkout() {

    }
    
    int get_max() {
        if (!q.empty())
        {
            return stk.top();
        }
        else {
            return -1;
        }
    }
    
    void add(int value) {
        q.push(value);
        if (stk.empty() || stk.top() < value)
        {
            stk.push(value);
        }
    }
    
    int remove() {
        int top = -1;
        if (!q.empty())
        {
            top = q.front();
            if(top == stk.top()){
                stk.pop();
            }
            q.pop();
        }
        return top;
    }
};

/**
 * Your Checkout object will be instantiated and called as such:
 * Checkout* obj = new Checkout();
 * int param_1 = obj->get_max();
 * obj->add(value);
 * int param_3 = obj->remove();
 */
