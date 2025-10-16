#include <vector>
#include <string>
#include <iostream>

class Solution {
private:
    std::vector<std::vector<std::string>> result; // 存储所有有效的分割方案
    std::vector<std::string> path;               // 存储当前路径（一种分割方案）

    /**
     * @brief 检查子串是否为回文串
     * @param s 原始字符串
     * @param left 子串起始索引
     * @param right 子串结束索引
     * @return 如果子串是回文串，返回 true
     */
    bool isPalindrome(const std::string& s, int left, int right) {
        while (left < right) {
            if (s[left] != s[right]) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }

    /**
     * @brief 回溯函数
     * @param s 原始字符串
     * @param startIndex 当前层级开始处理的字符索引
     */
    void backtracking(const std::string& s, int startIndex) {
        // 1. 终止条件 (Base Case)
        // 当起始索引到达字符串末尾时，表示已经完成一个完整的分割方案
        if (startIndex == s.length()) {
            result.push_back(path);
            return;
        }

        // 2. 遍历切割点
        // i 是当前分割子串的结束索引
        for (int i = startIndex; i < s.length(); ++i) {
            // 切割子串为 s[startIndex..i]
            
            // 检查：判断当前子串是否为回文串
            if (isPalindrome(s, startIndex, i)) {
                
                // 选择：如果是回文串，将其加入当前路径
                std::string sub = s.substr(startIndex, i - startIndex + 1);
                path.push_back(sub);
                
                // 递归：从当前子串的下一个位置 (i + 1) 开始继续分割
                backtracking(s, i + 1);
                
                // 撤销选择（回溯）：移除当前子串，尝试下一个切割点
                path.pop_back();
                
            } else {
                // 如果不是回文串，则这个切割点无效，直接跳过
                continue; 
            }
        }
    }

public:
    std::vector<std::vector<std::string>> partition(std::string s) {
        result.clear();
        path.clear();
        
        backtracking(s, 0); // 从字符串的第一个字符（索引 0）开始分割
        
        return result;
    }
};


// 示例用法（在 main 函数中）
int main() {
    Solution sol;
    std::string s1 = "aabccbcc";
    auto result1 = sol.partition(s1);
    std::cout << "{ "  << std::endl;
    for (auto& path : result1) {
        std::cout << "[ ";
        for (auto& str : path) {
            std::cout << str << ", ";
        }
        std::cout << "] ";
        std::cout << std::endl;
    }
    std::cout << "} "  << std::endl;

    // 输出: [["a","a","b"], ["aa","b"]]

    std::string s2 = "a";
    auto result2 = sol.partition(s2);
    // 输出: [["a"]]
    
    return 0;
}

