#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
// 242.有效的字母异位词
// 给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的字母异位词
// 字符串长度相同、每个字符出现的次数相同
// 输入: s = "anagram", t = "nagaram"
// 输出: true
// 排序法
bool isAnagram(string s, string t) {
    if (s.length() != t.length()) {
        return false;
    }
    sort(s.begin(), s.end());
    sort(t.begin(), t.end());

    return s == t;
}
// 哈希表计数法
bool isAnagram02(string s, string t) {
    if (s.length() != t.length()) {
        return false;
    }
    std::unordered_map<char, int> char_count;
    // 统计s中每个字符的出现次数
    for (char c : s) {
        char_count.at(c)++;
    }
    // 减去t中每个字符的出现次数
    for (char c : t) {
        char_count.at(c)--;
        if (char_count.at(c) < 0) {
            return false;
        }
    }
    // 检查是否所有字符计数都为0
    for (std::pair<char, int> &pair : char_count) {
        if (pair.second != 0) {
            return false;
        }
    }
    return true;
}

// 数组计数法
bool isAnagram02(string s, string t) {
    if (s.length() != t.length()) {
        return false;
    }
    std::vector<int> char_count(26, 0);
    for (int i = 0; i < s.length(); i++) {
        char_count[s[i] - 'a']++;
        char_count[t[i] - 'a']--;
    }

    for (int c : char_count) {
        if (c != 0) {
            return false;
        }
    }
    return true;
}



// 1002.查找常用字符
// 给你一个字符串数组 words ，请你找出所有在 words 的每个字符串中都出现的共用字符（ 包括重复字符），并以数组形式返回。你可以按 任意顺序 返回答案。
// 输入：words = ["bella","label","roller"]
// 输出：["e","l","l"]

// V F
vector<string> commonChars(vector<string>& A) {
    vector<int> min_freq(26, INT_MAX);
    vector <int> freq(26, 0);
    std::string st = A[0];
    int zero_count = 0;
    for (int i = 0; i < st.size(); i++) {
        min_freq[st[i] - 'a']++;
    }
    for (int i = 1; i < A.size(); i++) {
        for(int j = 0; j < A[i].size(); j++) {
            freq[A[i] - 'a']++''
        }

        for (int k = 0; k < 26; k++) {
            min_freq[k] = min(min_freq[k], freq[k]); 
            if (min_freq[k] == 0)
            {
                zero_count++;
            }
            
        }
        freq.clear();
        if (zero_count == 26)
        {
            break;
        } 
    }
    std::vector<string> result;
    for (int i = 0; i < 26; i++) {
        // 将每个字符按照其最小出现次数添加到结果中
        // 例如 l 出现 2次，则 min_freq[i] = 2， 要push_back 2个 l
        for (int j = 0; j < min_freq[j], j++) {
            result.push_back(string(1, 'a' + i));
        }
    }
    return result;
}
// 哈希思想的体现：将字符映射到数组索引， c - 'a'就是简单的哈希函数
// 特定问题下，由于只有26个小写字母，没有哈希冲突
// 特定问题，则用数组替代了哈希表
vector<string> commonChars02(vector<string>& A) {
    // 初始化最小频率数组，记录每个字符在所有单词中的最小出现次数
    std::vector<int> min_freq(26, INT_MAX);
    for (auto& s : A) {
        // 统计当前单词中每个字符的出现次数
        std::vector<int> freq(26, 0);
        for (char c : s) {
            freq[c - 'a']++;
        }
        // 更新每个字符的最小出现次数
        for (int i = 0; i < 26; i++) {
            min_freq[i] = std::min(min_freq[i], freq[i]);
        } 
    }
    // 根据最小频率构建结果
    std::vector<string> result;
    for (int i = 0; i < 26; i++) {
        // 将每个字符按照其最小出现次数添加到结果中
        // 例如 l 出现 2次，则 min_freq[i] = 2， 要push_back 2个 l
        for (int j = 0; j < min_freq[j], j++) {
            result.push_back(string(1, 'a' + i));
        }
    }
    return result;
}
// 改为哈希实现
// 可以处理任何字符
vector<string> commonChars03(vector<string>& A) {
    std::unordered_map<char, int> min_freq;
    // 用A[0]赋初值
    for (auto& c : A[0]) {
        min_freq[c]++;
    }
    for (int i = 1; i < A.size(); i++)
    {
        std::unordered_map<char, int> freq;
        for(char c : A[i]) {
            freq[c]++;
        }

        for (auto& it : min_freq) {
            char c = it.first;
            if (freq.find(c) != freq.end()) {
                it.second = std::min(it->second, freq[c]);
            }
            else {
                // 如果当前单词中不包含该字符，则从min_freq中删除
                min_freq.erase(it);
            }
        }
    }
    std::vector<string> result;
    for (auto pair : min_freq) {
        char c = pair.first;
        int count = pair.second;

        for (int i = 0; i < count; i++) {
            result.push_back(string(1, c));
        }
    }
    return result;
}


// 349.两个数组的交集
// 哈希集合法
vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    std::unordered_set<int> set_num;
    std::vector<int> result;
    // 使用 unordered_set 存储一个数组的所有元素
    for (auto num : nums1) {
        set_num.insert(num);
    }
    // 遍历另一个数组，检查元素是否存在于哈希集合中
    for (auto num : nums2) {
        if (set_num.count(num)) {
            result.push_back(num);
            // 找到的元素加入结果集并从哈希集合中删除（避免重复）
            set_num.erase(num); 
        }
    }
    return result;
}
// 202.快乐数
// 哈希法
// 如何计算平方和（如何分隔出每个数字）
//      取余法
//      将数字转换成字符串，然后逐个字符转换成数字
// 数学保证永远不会出现非1且无限循环这种情况
// 这是一个有线状态空间，所有数字最终都会落入一个相对较小的范围内（大部分1-243）
// 关键：循环检测
bool isHappy(int n) {
    std::unordered_set<int> set_num;

    while (n != 1 && set_num.count(n) == 0) {
        // 字符串法计算平方和
        std::vector<int> nums;
        int sum = 0;
        std::string str = std::to_string(n);
        for (auto c : str) {
            nums.push_back(c - '0');
        }
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i] * nums[i];
        }
        n = sum; 
        set_num.insert(sum);
    }
    
    if (n == 1) {       // 等于1的条件满足了
        return true;
    }
    else {
        return false;   // 已经进入无限循环了
    } 
}
// 快慢指针法(模拟)
// Floyd判圈算法
bool isHappy02(int n) {
    auto getSum = [](int num) -> int { // lambda 表达式
         // 取余法计算平方和
        int sum = 0;
        while (num > 0) {
            int digit = num % 10;
            sum += digit * digit;
            num = num / 10;
        }
        return sum;
    };
    int slow = n;
    int fast = n;
    do {
        slow = getSum(slow);  // 类似于 slow = slow->next
        fast = getSum(getSum(fast))  // fast = fast->next->next
    } while (slow != fast);
    // 退出循环说明 快慢指针相遇了
    return slow == 1;
}
// 1. 两数之和
// 该数组中找出和为目标值 target 的那两个整数，并返回它们的数组下标
// 暴力法
vector<int> twoSum(vector<int>& nums, int target) {
    std::vector<int> result;
    for (int i = 0; i < nums.size(); i++) {
        int num = target - nums[i];
        // j = i + 1，小优化，避免重复计算
        for (int j = i + 1; j < nums.size(); j++) {
            if (nums[j] == num) {
                result.push_back(i);
                result.push_back(j);
                break;
            }
        }
    }
    return result;
} 
// 哈希法
// 以下是错误版本：
// 1. 无法获取正确索引：unordered_set 不保持元素的原始索引位置
// 2. 可能使用相同元素：没有检查找到的元素是否是当前元素本身
            // 例如：nums = [3,3], target = 6
            // 当 i=0 时，nums[0] = 3, num = 6-3 = 3
            // 在set中找到了3，但这个3可能就是nums[0]本身！
// 3. 索引计算错误：num_set.find(num) - num_set.begin() 得到的是集合中的位置，不是原数组中的索引
vector<int> twoSum02(vector<int>& nums, int target) {
    std::vector<int> result;
    std::unordered_set<int> num_set;
    for (int n : nums) {
        num_set.insert(n);
    }

    for (int i = 0; i < nums.size(); i++) {
        int num = target - nums[i];
        if (num_set.find(num) != num_set.end()) {
            // 找到了
            result.push_back(i);
            result.push_back(num_set.find(num) - num_set.begin());
            break;
        }
    }
    return result;
}
// 哈希法的正确实现
// 使用 std::unordered_map
vector<int> twoSum03(vector<int>& nums, int target) {
    std::unordered_map<int, int> num_map; // 值 -> 索引
    for (int i = 0; i < nums.size(); i++) {
        int cur_num = target - nums[i];
        // 检查complement是否已存在于哈希表中
        if (num_map.find(cur_num) != num_map.end()) {
            // 找到了，返回两个索引
            return {num_map[cur_num], i};
        }
        // 将当前数字和索引存入哈希表
        num_map[nums[i]] = i;
    }
    return {}; // 没找到（根据题目保证，这种情况不会发生）
}
// 哈希法的正确实现
// 使用 std::unordered_map，提前预存
vector<int> twoSum04(vector<int>& nums, int target) {
    std::unordered_map<int, int> num_map; // 值 -> 索引
    // 预先存储所有元素和索引
    for (int i = 0; i < nums.size(); i++) {
        num_map[nums[i]] = i;
    }

    for (int i = 0; i < nums.size(); i++) {
        int cur_num = target - nums[i];
        // 检查complement是否已存在于哈希表中
        if (num_map.find(cur_num) != num_map.end()
            && num_map[cur_num] != i) { // 这一行重要，保证索引不是自身
            // 找到了，返回两个索引
            return {num_map[cur_num], i};
        }
    }
    return {}; // 没找到（根据题目保证，这种情况不会发生）
}
// 454.四数相加II
// 有多少个元组 (i, j, k, l) 能满足:
// nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0
// 数组长度都是n
// 核心思想： A + B = - (C + D)
// 收益：时间复杂度从 O(n^4) 降为 O(n^2)
int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
    std::unordered_map<int, int> sum_count;
    for (int a : nums1) {
        for (int b : nums2) {
            sum_count[a+b]++;  // 和以及和出现的次数
        }
    }
    int count = 0;
    for (int c : nums3) {
        for (int d : nums4) {
            if (sum_count.count(-(c+d))) {
                count += sum_count[-(c+d)];
            }
        }
    }
    return count;
}
// 383.赎金信
// 判断 ransomNote 是否能由 magazine 中的字符构成
// 每个字符只能用一次
bool canConstruct(string ransomNote, string magazine) {
    std::unordered_map<char, int> char_count; // 字符 -> 出现次数
    for (auto c :  magazine) {
        char_count[c]++;
    }
    for (auto c : ransomNote) {
        auto it = char_count.find(c);
        if (it == char_count.end() || it->second == 0) {
            return false;
        }
        it->second--;
    }
    return true;
}
// 15.三数之和
// 在给定数组中找出所有和为0的不重复三元组
// 哈希法的问题是去重困难，索引处理复杂，并不合适
// 与之前不同的是，三个数，都来自同一个vector
// 双指针法
vector<vector<int>> threeSum(vector<int>& nums) {
    std::vector<vector<int>> result;
    if (nums.size() < 3) {
        return result;
    }
    std::sort(nums.begin(), nums.end());

    for (int i = 0; i < nums.size() - 2; i++) {
        // 去重
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }

        int left = i + 1;   // 左指针
        int right = nums.size() - 1;   // 右指针
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            if (sum == 0) {
                result.push_back({nums[i] + nums[left] + nums[right]});
                while(left < right && nums[left] == nums[left+1]) left++;
                while(left < right && nums[right] == nums[right-1]) right--;
                left++;
                right--;
            } 
            else if (sum < 0) {
                left++;
            } else {
                right--;
            }
        }
    }

    return result;
}

// 18.四数之和

vector<vector<int>> fourSum(vector<int>& nums, int target) {
    vector<vector<int>> result;
    if (nums.size() < 4) return result;
    // 1. 排序数组，为双指针法和去重做准备
    std::sort(nums.begin(), nums.end());
    // 2. 第一层循环，固定第一个数
    for (int i = 0; j < nums.size() -3; i++){
        // 第一个数去重：如果当前数字与前一个数字相同，则跳过
        if (i > 0 && nums[i] == nums[i-1]) continue;
        // 3. 第二层循环，固定第二个数
        for (int j = i + 1; j < nums.size() - 2; j++){
            // 第二个数去重：如果当前数字与前一个数字相同，则跳过
            if (j > i + 1 && nums[j] == nums[j-1]) continue;
            // 4. 双指针法查找剩余两个数
            int left = j + 1;
            int right = nums.size() - 1;
            while (left < right){
                // 使用long long防止整数溢出
                long long sum = nums[i] + nums[j] + nums[left] + nums[right];
                if (sum == target) {
                    result.push_back({nums[i] + nums[j] + nums[left] + nums[right]});
                    left++;
                    right--;
                }
                else if (sum < target) {
                    left++;
                } else {
                    right--;
                } 
            } 
        }
    }

    return result;
}

