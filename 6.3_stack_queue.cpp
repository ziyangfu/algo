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
// 更快速的解法：
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
// --------------------------------------------------------------------------------
/**
 * 请设计一个自助结账系统，该系统需要通过一个队列来模拟顾客通过购物车的结算过程，需要实现的功能有：

get_max()：获取结算商品中的最高价格，如果队列为空，则返回 -1
add(value)：将价格为 value 的商品加入待结算商品队列的尾部
remove()：移除第一个待结算的商品价格，如果队列为空，则返回 -1
注意，为保证该系统运转高效性，以上函数的均摊时间复杂度均为 O(1)

?

示例 1：

输入: 
["Checkout","add","add","get_max","remove","get_max"]
[[],[4],[7],[],[],[]]

输出: [null,null,null,7,4,7]
示例 2：

输入: 
["Checkout","remove","get_max"]
[[],[],[]]

输出: [null,-1,-1]

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