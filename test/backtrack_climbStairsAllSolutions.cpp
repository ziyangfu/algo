// 算法解释：
// 回溯算法原理：

// 通过递归尝试每一种可能的选择（爬1步或2步）
// 当做出一个选择后，递归处理剩余的台阶
// 在递归返回后撤销当前选择（回溯），尝试其他可能性
// 关键步骤：

// 选择：在每一步选择爬1个或2个台阶
// 约束：不能超过总台阶数
// 目标：当剩余台阶数为0时，记录当前路径
// 回溯：撤销当前选择，尝试其他分支
// 时间和空间复杂度：

// 时间复杂度：O(2^n)，因为每个台阶都有两种选择
// 空间复杂度：O(n)，递归栈的最大深度为n
// 优化建议：

// 对于较大的n值，方案数量会急剧增长，可能需要考虑限制输出数量
// 可以添加参数限制最大输出方案数


#include <vector>
#include <iostream>

class Solution {
public:
    /**
     * @brief 获取爬楼梯的所有可能方案
     * 
     * @param n 需要爬的台阶数
     * @return 所有可能的爬楼梯方案列表
     */
    std::vector<std::vector<int>> climbStairsAllSolutions(int n) {
        std::vector<std::vector<int>> result;
        std::vector<int> path;
        
        backtrack(n, path, result);
        
        return result;
    }
    
private:
    /**
     * @brief 回溯算法生成所有可能的方案
     * 
     * @param remaining 剩余需要爬的台阶数
     * @param path 当前路径（已选择的步数）
     * @param result 存储所有可能方案的结果集
     */
    void backtrack(int remaining, std::vector<int>& path, 
                   std::vector<std::vector<int>>& result) {
        // 基础情况：如果剩余台阶数为0，说明找到一种有效方案
        if (remaining == 0) {
            result.push_back(path);
            return;
        }
        
        // 尝试爬1个台阶
        if (remaining >= 1) {
            path.push_back(1);
            backtrack(remaining - 1, path, result);
            path.pop_back(); // 回溯
        }
        
        // 尝试爬2个台阶
        if (remaining >= 2) {
            path.push_back(2);
            backtrack(remaining - 2, path, result);
            path.pop_back(); // 回溯
        }
    }
    
public:
    /**
     * @brief 打印所有可能的爬楼梯方案
     * 
     * @param n 需要爬的台阶数
     */
    void printAllSolutions(int n) {
        auto solutions = climbStairsAllSolutions(n);
        
        std::cout << "爬" << n << "阶楼梯的所有方案 (" 
                  << solutions.size() << "种):\n";
                  
        for (size_t i = 0; i < solutions.size(); i++) {
            std::cout << "方案" << (i + 1) << ": ";
            for (size_t j = 0; j < solutions[i].size(); j++) {
                std::cout << solutions[i][j];
                if (j < solutions[i].size() - 1) {
                    std::cout << " + ";
                }
            }
            std::cout << "\n";
        }
    }
};

int main() {
    Solution solution;
    
    // 打印n=5的所有方案
    solution.printAllSolutions(5);
    
    return 0;
}
