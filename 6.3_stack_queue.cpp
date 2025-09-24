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
// �����ٵĽⷨ��
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
 * �����һ����������ϵͳ����ϵͳ��Ҫͨ��һ��������ģ��˿�ͨ�����ﳵ�Ľ�����̣���Ҫʵ�ֵĹ����У�

get_max()����ȡ������Ʒ�е���߼۸��������Ϊ�գ��򷵻� -1
add(value)�����۸�Ϊ value ����Ʒ�����������Ʒ���е�β��
remove()���Ƴ���һ�����������Ʒ�۸��������Ϊ�գ��򷵻� -1
ע�⣬Ϊ��֤��ϵͳ��ת��Ч�ԣ����Ϻ����ľ�̯ʱ�临�ӶȾ�Ϊ O(1)

?

ʾ�� 1��

����: 
["Checkout","add","add","get_max","remove","get_max"]
[[],[4],[7],[],[],[]]

���: [null,null,null,7,4,7]
ʾ�� 2��

����: 
["Checkout","remove","get_max"]
[[],[],[]]

���: [null,-1,-1]

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