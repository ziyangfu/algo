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
    
    
    // 39.组合总和
/**
 * @brief 找出数组中所有可以使数字和为target的组合
 * @param candidates 无重复元素的整数数组
 * @param target 目标和
 * @return 所有和为target的不同组合
 * 可以重复选择元素
 */
std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target) {
    if (candidates.empty()) {
        return {};
    }
    std::vector<std::vector<int>> result;
    std::vector<int> path;
    // 排序更方便剪枝
    std::sort(candidates.begin(), candidates.end());
    auto backtrack = [&](int startIndex, int remaining) -> void {
        // 终止条件：剩余的和为0
        if (remaining == 0) {
            result.push_back(path);
            return;
        }
        // 剪枝：如果剩余值小于0，直接返回
        if (remaining < 0) {
            return;
        }
         // 从startIndex开始遍历，避免重复组合
        for (int i = startIndex; i < candidates.size(); i++) {
            if (candidates[i] > remaining) {
                // continue;  // 未排序
                break;  // 已排序
            }
            path.push_back(candidates[i]);
            // 递归时传递更新后的剩余值，startIndex保持i允许重复使用当前元素
            backtrack(i, remaining - candidates[i]);
            path.pop_back();
        }
        
    };
    backtrack(0, target);
    return result;
}

// 40.组合总和II
// 特性	        39题（组合总和）	40题（组合总和II）
// 元素使用次数	        无限次	    每个元素只能用一次
// 数组特点	        无重复元素	    可能有重复元素
// 重复处理	        不需要特别处理	    需要去重
// 递归参数	    backtrack(i, ...)	backtrack(i+1, ...)
/**
 * @brief 找出数组中所有可以使数字和为target的组合（每个数字只能用一次，结果不能重复）
 * @param candidates 可能包含重复元素的整数数组
 * @param target 目标和
 * @return 所有和为target的不同组合（不包含重复组合）
 * candidates 中的每个数字在每个组合中只能使用一次
 * 数组里面的数字，是可能重复的
 */

// 这个问题不能事先排序去重
    // // 1. 排序 (Sort): 将所有重复的元素相邻放置
    // std::sort(candidates.begin(), candidates.end());
    // // 2. 唯一化 (Unique): 
    // // std::unique 将不重复的元素移到容器的前部，并返回一个迭代器，
    // // 指向新逻辑末尾的下一个位置（即第一个重复元素的起始位置）。
    // auto last = std::unique(candidates.begin(), candidates.end());
    // // 3. 擦除 (Erase): 
    // // 移除从 last 迭代器到容器实际末尾之间的所有元素。
    // candidates.erase(last, candidates.end());
// 它只是数组不能重复，例如candidates = [3, 3, 3]，target = 6, 
// {[3, 3]}, 然后去重后，candidates 变成 [3]，只能找到组合 [3]，无法找到 [3, 3]
std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target) {
    if (candidates.empty()) {
        return {};
    }
    
    std::vector<std::vector<int>> result;
    std::vector<int> path;
    std::sort(candidates.begin(), candidates.end());
    auto backtrack = [&](int startIndex, int remaining) -> void {
        if (remaining == 0)
        {
            result.push_back(path);
            return;
        }

        if (remaining < 0) {
            return;
        }

        for (int i = startIndex; i < candidates.size(); i++) {
            // 剪枝：如果当前值已经大于剩余值，后面的也不用看了,因为数组已排序
            if (candidates[i] > remaining) {
                break;
            }
            // 剪枝 2: 关键的去重逻辑
            // 如果当前元素 (candidates[i]) 与前一个元素 (candidates[i-1]) 相同，
            // 且前一个元素在当前层已经被处理过 (i > startIndex)，则跳过。
            // 确保 i > startIndex 是为了避免跳过第一个重复项。
            if (i > startIndex && candidates[i] == candidates[i - 1]) {
                continue;
            }

            path.push_back(candidates[i]);
            // 递归：下一层级从 i + 1 开始，确保每个数字只用一次
            backtrack(i + 1, remaining - candidates[i]);
            path.pop_back();
        }
         
    };

    backtrack(0, target);
    return result;
}
// 131.分割回文串
// 回文串：正读和反读都相同的字符串
// 一个字符串，任意切割，割成的所有子串，都是回文串，那么，这种切割方式就是正确的

// 判断子串是否是回文串的方法：
// 1. 双指针法，左右向中间，判断是否回文串
// 2. 翻转法，将子串翻转，是否与源串相等
// 3. 动态规划

std::vector<std::vector<std::string>> partition(std::string s) {
    if (s.empty()) {
        return {};
    }
    std::vector<std::vector<std::string>> result;
    std::vector<std::string> path;
    // 双指针法判断
    auto isPalindrome = [](std::string str, int left, int right) -> bool{
        while (left <= right) {
            if (str[left] != str[right]) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }

    auto backtrack = [&](int startIndex) -> void {
        // 终止条件，字符串全部分割结束
        // 当起始索引到达字符串末尾时，表示已经完成一个完整的分割方案
        // 前面每切一次，都判断是否是回文串，因此，等到结束，这个path，肯定是一个有效方案
        if (startIndex == s.size()) {
            result.push_back(path);
            return;
        } 
        for (int i = startIndex; i < s.size(); i++) {
            // 切割一个子串为 [startIndex, i]
            if (!isPalindrome(s, startIndex, i)) {
                // 选择：如果是回文串，将其加入当前路径
                std::string str = s.substr(startIndex, i - startIndex + 1);
                path.push_back(str);
                // 递归：从当前子串的下一个位置 (i + 1) 开始继续分割
                backtrack(i + 1);
                // 撤销选择（回溯）：移除当前子串，尝试下一个切割点
                path.pop_back();
            }
            else {
                // 如果不是回文串，则这个切割点无效，直接跳过
                continue;
            }
        }
    };

    backtrack(0);
    return result; 
}
// 动态规划法优化，DP 优化能将 O(N^2) 的回文检查时间降到 O(1)
/**
 * @brief 分割回文串 - 使用预处理优化的版本
 * @param s 输入字符串
 * @return 所有可能的分割方案
 */
std::vector<std::vector<std::string>> partition02(std::string s) {
    if (s.empty()) {
        return {};
    }
    
    int n = s.length();
    
    // 预处理：使用动态规划计算所有子串是否为回文串
    // dp[i][j] 表示 s[i...j] 是否为回文串
    std::vector<std::vector<bool>> dp(n, std::vector<bool>(n, false));
    
    // 单个字符都是回文串
    for (int i = 0; i < n; i++) {
        dp[i][i] = true;
    }
    
    // 从长度为2的子串开始判断
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if (s[i] == s[j]) {
                if (len == 2) {
                    dp[i][j] = true;
                } else {
                    dp[i][j] = dp[i + 1][j - 1];
                }
            }
        }
    }
    
    std::vector<std::vector<std::string>> result;
    std::vector<std::string> path;
    
    // 回溯函数
    std::function<void(int)> backtrack = [&](int startIndex) {
        // 终止条件
        if (startIndex >= s.length()) {
            result.push_back(path);
            return;
        }
        
        // 尝试不同的分割点
        for (int i = startIndex; i < s.length(); i++) {
            // 使用预处理结果快速判断是否为回文串
            if (dp[startIndex][i]) {
                path.push_back(s.substr(startIndex, i - startIndex + 1));
                backtrack(i + 1);
                path.pop_back();
            }
        }
    };
    
    backtrack(0);
    return result;
}
// 93.复原IP地址
/**
 * @brief 给定一个数字字符串 s，将其复原为所有可能有效的 IP 地址。
 * @param s 输入的数字字符串。
 * @return 所有可能的有效 IP 地址的列表。
 * 有效的 IP 地址 必须由四个整数组成，每个整数位于 0 到 255 之间，并且由点 . 分隔
 * 有效的 IP 地址不能包含任何前导零，除非该数字本身就是 0; (即01是不对的，但0，10这些是可以的)
 */
std::vector<std::string> restoreIpAddresses(std::string s) {
    std::vector<std::string> result;
    std::vector<std::string> path;

    auto isValid = [](std::string str) -> bool {
        // 空的，或者 长度超过 3，不符合
        if (str.empty() || str.size() > 3) {
            return false;
        }
        // 0 开头，长度超过1，不符合
        if (str[0] == '0' && str.size() > 1) {
            return false;
        }
        // 转换为数字，判断是否大于 255
        int num = std::stoi(str);
        if (num > 255) {
            return false;
        }
        return true;
    };
    //  依旧是分隔字符串，判断子串是否有效
    auto backtrack = [&](int startIndex) -> void { 
        if (path.size() == 4) {
            std::string ip = path[0] + "." + path[1] + "." + path[2] + "." + path[3];
            result.push_back(ip);
            return;
        }

        for (int i = startIndex; i < s.size(); i++) {
            std::string str = s.substr(startIndex, i - startIndex + 1);
            if (isValid(str)) {
                path.push_back(str);
                backtrack(i + 1);
                path.pop_back();
            }
            else {
                continue;
            }
        }
    };

    backtrack(0);
    return result; 
}
// 带剪枝的优化方案
std::vector<std::string> restoreIpAddresses02(std::string s) {
    std::vector<std::string> result;
    std::vector<std::string> path;

    auto isValid = [](std::string str) -> bool {
        // 空的，或者 长度超过 3，不符合
        if (str.empty() || str.size() > 3) {
            return false;
        }
        // 0 开头，长度超过1，不符合
        if (str[0] == '0' && str.size() > 1) {
            return false;
        }
        // 转换为数字，判断是否大于 255
        int num = std::stoi(str);
        if (num > 255) {
            return false;
        }
        return true;
    };
    //  依旧是分隔字符串，判断子串是否有效
    auto backtrack = [&](int startIndex) -> void { 
        if (path.size() == 4) {
            // 终止条件：如果切了 4 段，且用完了所有字符
            if (startIndex == s.size()) {
                // 拼接IP，加入结果
                std::string ip = path[0] + "." + path[1] + "." + path[2] + "." + path[3];
                result.push_back(ip);
            }
            // 如果 path.size() == 4 但 startIndex != s.size()，
            // 说明字符串没用完，这是无效方案，直接返回。
            return;
        }
        // 早期剪枝 (优化)：
        // 1. 最长：剩余的字符 (s.size() - startIndex) 必须 <= 剩下的段数 (4 - path.size()) * 3
        // 2. 最短：剩余的字符 (s.size() - startIndex) 必须 >= 剩下的段数 (4 - path.size()) * 1
        // 如果不满足，就没有继续搜索的必要了。
        int remaining_segments = 4 - path.size();
        int remaining_length = s.size() - startIndex;

        if (remaining_length < remaining_segments ||
            remaining_length > remaining_segments * 3) {
            // 剪枝：剩余的段数 * 3 < 剩余的长度，则不可能找到有效的 IP 地址
            return;
        }

        for (int i = startIndex; i < s.size()  && i < startIndex + 3; i++) {
            std::string str = s.substr(startIndex, i - startIndex + 1);
            if (isValid(str)) {
                path.push_back(str);
                backtrack(i + 1);
                path.pop_back();
            }
            else {
                // 因为是从 i=startIndex 开始，str 逐渐变长，
            // 如果长度 1 或 2 的子串有效，而长度 3 的子串无效（例如 > 255），
            // 那么 continue 是正确的。
            // 但如果 str 无效的原因是前导 0 或 > 255，那么再长的 str 也会无效。
            // 简单的 continue 是可以的，但更优的做法是利用 isValid 的特性。
            
            // 优化：如果 i=startIndex，且当前子串就是 '0'，下一个 i=startIndex+1 就会导致前导 0 无效。
            // 如果 str 在长度 < 3 时就已经无效（例如 '300' > 255），可以直接 break。
            // 但你的 isValid 设计得很好，它可以自然处理这些情况。
            
            // 如果当前子串 str 已经无效，因为 i 是递增的，下一个 i 得到的子串会更长。
            // 例如 s="256..."，当 i=startIndex+2 时 str="256"，无效。
            // 下一个 i=startIndex+3 会超出长度 3 限制，所以不需要 continue/break。
            
            // 但是，如果 str 无效是因为数值太大（>255），我们应该 break。
            if (std::stoi(str) > 255) { 
                break; // 如果数值超过 255，那么继续增长长度一定超过 255，直接终止循环
            }
            // 否则，如果是因为前导零等其他原因导致无效，可以继续（例如 s="01..."，'0'有效，'01'无效，但 i=startIndex+2 就不再是前导0了，虽然此时长度已经>3）
            continue; // 维持原样，继续判断下一个 i
            }
        }
    };

    backtrack(0);
    return result; 
}
/**
 * @brief 给定一个不含重复元素的整数数组 nums，返回所有可能的子集（幂集）。
 * @param nums 输入的整数数组。
 * @return 所有子集的列表。
 */
std::vector<std::vector<int>> subsets(std::vector<int>& nums) {
    if (nums.empty()) {
        return {{}};
    }
    std::vector<std::vector<int>> result;
    std::vector<int> path;
    // 错误实现，漏空集，漏子集
    // auto backtrack = [&](int startIndex) ->void {
    //     if (startIndex == nums.size()) {
    //         return;
    //     }
    //     for (int i = startIndex; i < nums.size(); i++) {
    //         // 获得一个子区间（nums[startIndex] 到 nums[i]）
    //         // 这种方案只能获得连续的集合，对于不连续的子集，遗漏
    //         for (int j = startIndex; j <= i; j++) {
    //             path.push_back(nums[j]);
    //         }
    //         result.push_back(path);
    //         backtrack(i + 1);
    //         path.pop_back();
    //     }
    // }
    auto backtrack = [&](int startIndex) ->void {
        // 1. 收集结果：每一步的 path 都是一个有效的子集
        result.push_back(path);
        // 2. 终止条件：当 startIndex 等于数组大小时，本轮搜索结束
        if (startIndex == nums.size()) {
            return;
        }
        // 3. 遍历选择：从 startIndex 开始遍历，避免重复的组合（例如 [1, 2] 和 [2, 1]）
        for (int i = startIndex; i < nums.size(); i++) {
            // 选择：将当前元素 nums[i] 加入路径
            path.push_back(nums[i]);
            // 递归：从 i 的下一个元素开始继续构建子集
            backtrack(i + 1);
            // 撤销选择（回溯）：将 nums[i] 弹出，恢复路径，以便尝试下一个选择 i+1
            path.pop_back();
        }
    };
    backtrack(0);
    return result; 
}


}
