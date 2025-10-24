// 动态规划

// 什么是动态规划？
// 动态规划（Dynamic Programming，简称 DP）是一种通过将复杂问题分解成更小的、重叠的子问题，并存储这些子问题的解以避免重复计算，从而高效地解决问题的算法设计方法。简单来说，它是一种“以空间换时间”的策略。

// 核心思想：
// 动态规划的核心思想可以概括为两个字：“最优性” 和 “重叠子问题”。

// 最优性原理（Principle of Optimality）：
// 一个问题的最优解包含了其子问题的最优解。换句话说，如果你有一个问题的最优解，那么这个最优解中涉及到的所有子问题也都必须是其各自最优解。
// 举例： 寻找从城市 A 到城市 C 的最短路径。如果最短路径经过城市 B，那么 A 到 B 的路径一定是从 A 到 B 的最短路径，B 到 C 的路径也一定是从 B 到 C 的最短路径。如果 A 到 B 的路径不是最短的，那么整体路径就不是最短的。
// 重叠子问题（Overlapping Subproblems）：
// 在解决一个复杂问题时，会遇到许多相同的子问题。如果不对这些子问题进行记忆（存储），那么它们会被反复计算，导致效率低下。动态规划通过存储已计算的子问题答案，避免了这种重复计算。
// 举例： 计算斐波那契数列 F(n) = F(n-1) + F(n-2)。在计算 F(5) 时，需要 F(4) 和 F(3)。计算 F(4) 又需要 F(3) 和 F(2)。你会发现 F(3) 被计算了两次。动态规划就是把 F(3) 的结果存起来，第二次直接用即可。
// 动态规划的构成要素：
// 一个可以应用动态规划的问题，通常需要具备以下两个关键特征：

// 最优子结构（Optimal Substructure）：
// 这与最优性原理紧密相关。问题的最优解可以由其子问题的最优解组合而成。
// 重叠子问题（Overlapping Subproblems）：
// 在问题的求解过程中，会反复遇到相同的子问题。
// 动态规划的解题步骤：
// 通常，解决一个动态规划问题可以遵循以下步骤：

// 确定状态（Define the State）：
// 这是最关键的一步。你需要定义一个或多个状态变量，用来表示问题的子问题的解。
// 状态的定义应该能够涵盖所有需要解决的子问题，并且能够通过组合子问题的解来得到最终问题的解。
// 状态通常用一个数组、矩阵或更复杂的结构来表示。
// 确定状态转移方程（Define the Recurrence Relation）：
// 状态转移方程描述了如何从一个或多个较小的子问题的状态推导出当前子问题的状态。
// 它反映了问题之间的依赖关系。
// 通常，这是用数学公式来表示的。
// 确定边界条件（Define the Base Cases）：
// 边界条件是递归的终止条件，也是动态规划的起点。
// 它们是那些可以直接求解的、最简单的子问题。
// 例如，对于斐波那契数列，F(0) = 0 和 F(1) = 1 就是边界条件。
// 确定计算顺序（Determine the Order of Computation）：
// 根据状态转移方程，需要确定计算子问题的顺序，以确保在计算当前子问题时，其所需的更小子问题的解已经计算并存储。
// 通常有两种计算方法：
// 自顶向下（Top-Down）带备忘录（Memoization）： 采用递归的方式，如果子问题的解还没有计算，则递归计算；否则，直接返回已存储的解。
// 自底向上（Bottom-Up）迭代（Tabulation）： 按照从小到大的顺序，从边界条件开始，迭代地计算所有子问题的解，直到计算出最终问题的解。
// 求解最终问题（Solve the Final Problem）：
// 根据边界条件和状态转移方程，通过迭代或递归计算，最终得到原问题的解。
// 动态规划的两种实现方式：
// 自顶向下（Top-Down）带备忘录（Memoization）：
// 特点： 使用递归实现，通过一个数据结构（如哈希表或数组）来存储已经计算过的子问题的解。当需要某个子问题的解时，先检查它是否已经计算过，如果计算过则直接返回，否则就计算并存储。
// 优点： 直观，容易理解，只计算实际需要的子问题。
// 缺点： 递归深度可能导致栈溢出，函数调用开销相对较大。
// 伪代码示例（斐波那契数列）：


// memo = {} // 备忘录

// function fibonacci(n):
//     if n in memo:
//         return memo[n]
//     if n <= 1:
//         return n
//     result = fibonacci(n-1) + fibonacci(n-2)
//     memo[n] = result
//     return result

// 自底向上（Bottom-Up）迭代（Tabulation）：
// 特点： 使用循环（迭代）实现，从最简单的子问题（边界条件）开始，逐步计算出更复杂的子问题的解，直到最终问题的解。通常使用一个数组来存储所有子问题的解。
// 优点： 没有递归深度限制，通常比递归方式效率更高。
// 缺点： 需要预先确定所有需要的子问题，即使有些子问题在最终求解中不会被用到。
// 伪代码示例（斐波那契数列）：


// dp = array of size n+1
// dp[0] = 0
// dp[1] = 1
// for i from 2 to n:
//     dp[i] = dp[i-1] + dp[i-2]
// return dp[n]






// 509.斐波那契数
// 根据给定的整数 n，计算并返回斐波那契数列的第 n 项
class Solution {
public:
    /**
     * @brief 计算斐波那契数列的第 n 项。
     *
     * @param n 斐波那契数列的索引，非负整数。
     * @return 斐波那契数列的第 n 项的值。
     */
    int fib(int n) {
        if (n <= 1) {
            return n;
        }
        int a = 0, b = 1;

        for (int i = 2; i <= n; i++) {
            int temp = a + b;
            a = b;
            b = temp;
        }
        return b;
    }

};

// 70.爬楼梯
class Solution {
public:
    /**
     * @brief 计算爬楼梯的不同方法数
     * 
     * @param n 需要爬的台阶数
     * @return 到达楼顶的不同方法数
     */
    // 关键是从问题中，抽象出这个方法是斐波那契数列
    // 每次可以爬1个或2个台阶
    // 要到达第n阶，只能从第(n-1)阶走1步，或从第(n-2)阶走2步到达
    // 因此：f(n) = f(n-1) + f(n-2)
    int climbStairs(int n) {
        // 基础情况处理
        if (n <= 2) {
            return n;
        }
        // 使用动态规划，只保存前两个状态以节省空间
        int prev2 = 1; // 到达第1阶的方法数
        int prev1 = 2; // 到达第2阶的方法数
        // 从第3阶开始计算到第n阶的方法数
        for (int n = 3; n <= n; n++) {
            // 当前阶数的方法数 = 前一阶 + 前两阶的方法数
            int current = prev1 + prev2;
            prev2 = prev1;
            prev1 = current;
        }
        return prev1;
    }
};
// 746.使用最小花费爬楼梯
class Solution {
public:
    /**
     * @brief 计算爬楼梯的最小花费，可以从0，或者1台阶起步
     * 
     * @param cost 每个台阶需要支付的费用数组
     * @return 到达楼梯顶部的最小花费
     */

    // 暴力。使用回溯，计算出所有可能的方案，然后计算费用，最后去找最小值
    // 动态规划
    // 最优性原理（Principle of Optimality）：
    // 一个问题的最优解包含了其子问题的最优解。换句话说，
    // 如果你有一个问题的最优解，那么这个最优解中涉及到的所有子问题
    // 也都必须是其各自最优解

    // 如果爬到cost.size()是最低花费，说明，
    // (cost.size() -1 + to_cost) 或者(cost.size() -2 + to_cost)，这两个中的最小值，一定是最小花费
    int minCostClimbingStairs(std::vector<int>& cost) {
        int n = cost.size();
        
        // 处理边界情况
        if (n == 0) return 0;
        if (n == 1) return cost[0];
        if (n == 2) return std::min(cost[0], cost[1]);

        // dp[i] 表示到达第i个台阶的最小花费
        // 我们可以从前一个或前两个台阶到达当前台阶
        int prev2 = cost[0]; // 到达第0个台阶的最小花费
        int prev1 = cost[1]; // 到达第1个台阶的最小花费

        for (int i = 2; i < n; i++) {
            // 到达第i个台阶的最小花费 = 
            // min(到达第i-1个台阶的最小花费, 到达第i-2个台阶的最小花费) + 当前台阶费用
            int current = std::min(prev1, prev2) + cost[i];
            prev2 = prev1;
            prev1 = current;
        }
        // 最终答案是从最后一个或倒数第二个台阶到达楼梯顶部的最小花费
        // 注意：到达楼梯顶部不需要支付费用
        return std::min(prev1, prev2);
    }
};

// 62.不同路径
// 核心：dp[i][j] = dp[i - 1][j] + dp[i][ j - 1]
// 动态规划：当前结果由前面的结果影响
class Solution {
public:
    /**
     * 62. Unique Paths - 不同路径
     * 
     * @param m 网格行数
     * @param n 网格列数
     * @return 到达右下角的不同路径总数
     */
    int uniquePaths(int m, int n) {
        // dp[i][j] 表示从起点到位置(i,j)的路径数
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));
        // 初始化第一行和第一列为1，因为只有一种方式可以到达这些位置
        for (int i = 0; i < m; i++) {
            dp[i][0] = 1;
        }
        for (int j = 0; j < n; j++) {
            dp[0][j] = 1;
        }
        // 填充dp表
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                // 当前位置的路径数等于上方和左方位置路径数之和
                dp[i][j] = dp[i - 1][j] + dp[i][ j - 1]
            }
        }
        // 返回右下角位置的路径数
        // 数组索引是从0开始的，因此终点是 m-1 和 n-1
        return dp[m - 1][n - 1];
    }
};

// 63.不同路径II
class Solution {
public:
    /**
     * 63. Unique Paths II - 不同路径II
     * 
     * @param obstacleGrid 包含障碍物的网格，0表示可通过，1表示障碍物
     * @return 到达右下角的不同路径总数
     */
    // 设定好基本条件，明确当前与之前的状态关系
    // 如果当前点是障碍物，那个到达这个点的方法数是0，则dp[i][j]保持为0
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        // 到达dp[i][j]点的方法数
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));
        int m = obstacleGrid.size(); // 行
        int n = obstacleGrid[0].size(); // 列
        if (obstacleGrid[0][0] == 1 || obstacleGrid[m - 1][n - 1] == 1) {
            return 0;
        }

        dp[0][0] = 1;
        // 填充第一行
        for (int j = 1; j < n; j++) {
            if (obstacleGrid[0][j] == 0) {
                dp[0][j] = dp[0][j - 1];
            }
            // 如果有障碍物，则dp[0][j]保持为0
        }

        for (int i = 1; i < m; i++) {
            if (obstacleGrid[i][0] == 0) {
                dp[i][0] = dp[i - 1][0];
            }
            // 如果有障碍物，则dp[0][j]保持为0
        }
        // 填充其余位置
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (obstacleGrid[i][j] == 1) {
                    dp[i][j] = 0; // 如果有障碍物，dp[i][j]保持为0
                }
                else {
                    // 如果当前位置没有障碍物
                    dp[i][j] = dp[i][j - 1] + dp[i - 1][j];
                }
                
            }
        }
        return dp[m - 1][n - 1];
    }
};
// 343.整数拆分
class Solution {
public:
    /**
     * 343. Integer Break - 整数拆分
     * 
     * @param n 要拆分的正整数
     * @return 拆分后各部分乘积的最大值
     */
    int integerBreak(int n) {
        // dp[i] 表示数字 i 拆分后的最大乘积
         // 数组大小为 n + 1，方便直接使用索引 i.
        std::vector<int> dp(n + 1, 0);
        // 初始化基本情况
        dp[1] = 1;
        dp[2] = 1;
        for (int i = 3; i <= n; i++) {
            // 对于每个数字i，尝试所有可能的拆分点j
            for (int j = 1; j < i; j++) {
                // 比较三种情况：
                // 1. j * (i-j) - 直接拆分成两部分
                // 2. j * dp[i-j] - j不拆分，(i-j)继续拆分， (i-j)拆分的最大乘积就是dp[i-j]
                // 3. dp[i] - 保持之前的最优解

                // dp[i]加入最大值比对的原因是，会不断尝试max(j * (i - j), j * dp[i - j])
                // 这些尝试中，可能还不如之前的解，所有要把之前的解加入进来
                dp[i] = max(dp[i], max(j * (i - j), j * dp[i - j]));
            }
        }
        return dp[n];
    }
};
// 96. Unique Binary Search Trees - 不同的二叉搜索树
class Solution {
public:
    /**
     * 96. Unique Binary Search Trees - 不同的二叉搜索树
     * 
     * @param n 节点数量
     * @return 满足条件的二叉搜索树的数量
     */
    int numTrees(int n) {
        std::vector<int> dp(n + 1, 0);
        dp[0] = 1;
        dp[1] = 1;

        for (int i = 2; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                // 根节点可以是我们选择的任何一个节点 j (从 1 到 i)，
                // 所以总的 BST 数量 dp[i] 就是所有这些情况的总和
                // 所以要用 += 累加
                dp[i] += dp[j - 1] * dp[i - j];
            }
        }
        return dp[n];
    }
};


