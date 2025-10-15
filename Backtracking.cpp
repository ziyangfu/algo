// 回溯算法
// 77.组合
// 77.组合优化， 剪枝优化
std::vector<std::vector<int>> result;
void backtracking(int n, int k, int startIndex, std::vector<int> &path) {
    // 1. 终止条件 (Base Case): 已经选择了 k 个数
    if (path.size() == k) {
        result.push_back(path);
        return;
    }
    // 2. 搜索与剪枝优化：
        // i <= n: 原始搜索上限
        // n - (k - path.size()) + 1: 剪枝优化后的搜索上限 
        // 含义：从 i 到 n 中剩余的元素个数 (n - i + 1) 必须 >= 还需要选择的元素个数 (k - path.size())
        // n−i+1≥k−path.size()
    // for (int i = startIndex; i <= n; i++)
    for (int i=startIndex; i <= n - (k - path.size()) + 1; i++) {
        path.push_back(i);
        // 递归：下一层级从 i + 1 开始搜索
        backtracking(n, k, i + 1, path);
        // 撤销选择（回溯）：回退到上一状态，尝试选择下一个数字 i+1
        path.pop_back();
    }
}

/**
 * @brief 找出所有从 1 到 n 中选择 k 个数组成的组合。
 * @param n 整数范围的上界（从 1 到 n）。
 * @param k 需要选择的元素个数。
 * @return 所有组合的列表。
 */
std::vector<std::vector<int>> combine(int n, int k) {
    result.clear(); // 确保结果集为空
    std::vector<int> path; // 记录单次组合的路径
    backtracking(n, k, 1, path);  // 从 1 开始搜索
    return result; 
}

// 216.组合总和III
// 找出所有由 k 个数字组成的、且这些数字满足以下条件的组合：
// 数字的取值范围在 1 到 9 之间（包含 1 和 9）
// 组合中的所有数字都必须是唯一的
// 组合中的数字之和等于一个给定的目标数 n
/**
 * @brief 找出所有由 k 个不同数字组成的组合，使得它们的和为 n。
 *        数字只能是 1~9，且每个数字只能用一次。
 * 
 * @param k 需要选择的不同数字的个数。
 * @param n 目标和。
 * @return 所有符合条件的组合列表。
 */

std::vector<std::vector<int>> combinationSum3(int k, int n) {
    std::vector<std::vector<int>> result;
    std::vector<int> path;

    auto backtrack = [&](int start, int remainingK, int remainingSum) -> void {
        // 终止条件：已经选择了k个数字
        if (remainingK == 0) {
            // 如果和也正好为n，则找到一个有效组合
            if (remainingSum == 0) {
                result.push_back(path);
            }
            return;
        }
        // 剪枝：如果剩余和已经小于0，或者剩余数字不够，直接返回
        // 假设 start = 3，那么从3到9的数字包括：3, 4, 5, 6, 7, 8, 9
        // 9 - 3 == 6； 个数是7个
        if (remainingSum < 0 || remainingK > 9 - start + 1) {
            return;
        }
        // 从start开始遍历数字1-9
        for (int i = start; i <= 9; i++) {
            // 剪枝：如果当前数字已经大于剩余和，后面的也不用看了
            if (i > remainingSum) {
                break;
            }
            path.push_back(i);
            backtrack(i + 1, remainingK - 1, remainingSum - i);
            path.pop_back();
        }
    };
    backtrack(1, k, n);
    return result;
}
// 17.电话号码的字母组合
/**
 * @brief 根据输入的数字字符串，返回所有可能的字母组合
 * @param digits 包含数字2-9的字符串
 * @return 所有可能的字母组合
 */
std::vector<std::string> letterCombinations(const std::string& digits) {
    std::vector<std::string> result;
    if (digits.empty()) {
        return result;
    }
    // 定义一个map，用于将数字映射为对应的字母
    std::vector<std::string> mapping = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

    // // 解析数字字符串
    // std::vector<std::string> strs;
    // for (auto c : digits) {
    //     int i = c - '0';
    //     strs.push_back(mapping[i]);
    // }
    // int k = strs.size();

    //  问题转变为： 从path的K个元素中，选择一个字母，会有多少中组合

    // std::vector<char> path;
    auto backtrack = [&](int index) -> void{
        // // 终止条件：已经处理完所有数字
        if (digits.size() == index) {
            result.push_back(path);
            return;
        }
        // 获取当前数字对应的字母
        int digit = digits[index] - '0';
        std::string letters = mapping[digit];
        // 遍历当前数字对应的所有字母
        for (char letter : letters) {
            path.push_back(letter); // 选择
            backtrack(index + 1);   // 递归处理下一个数字
            path.pop_back();        // 撤销选择（回溯）
        }
    };
    backtrack(0);
    return result;

}
