// 0704
// [left, right]
// 二分查找
int search(std::vector<int>& nums, int target) {
    int left = 0; 
    int right = nums.size() - 1;  // 最后一个元素的索引
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target) {
            left = mid + 1;
        }
        else if (nums[mid] > target) {
            right = mid - 1;
        }
        else {
            return mid;
        }
    }

}

// 0027
// 首尾指针
int removeElements01(std::vector<int>& nums, int val) {
    int EndIndex = nums.size();
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] == val) {
            nums[i] = nums[EndIndex - 1]; // 将最后一个元素移动到当前位置
            EndIndex--;
            i--;
        }
    }
    return EndIndex;
}

// 0027 快慢双指针法 
int removeElements(std::vector<int>& nums, int val) {
    int FastIndex = 0;
    int SlowIndex = 0;
    for (FastIndex; FastIndex < nums.size(); FastIndex++) {
        if (nums[FastIndex] != val) {
            nums[SlowIndex] = nums[FastIndex];
            SlowIndex++;
        } 
    }
}

// 977
std::vector<int> sortedSquares(std::vector<int>& nums) {
    std::vector<int> result(nums.size());
    int FirstIndex = 0;
    int LastIndex = nums.size() - 1;
    int Index = nums.size() - 1;
    while (FirstIndex <= LastIndex)
    {
        int SqFirst = nums[FirstIndex] * nums[FirstIndex];
        int SqLast = nums[LastIndex] * nums[LastIndex];
        if (SqFirst < SqLast) {
            result[Index] = SqLast;
            LastIndex--;
            Index--;
        }
        else {
            result[Index] = SqFirst;
            FirstIndex++;
            Index--;
        }
    }
    return result;
}

// 209
// 滑动窗口，右边扩展窗口，左边缩小窗口
int minSubArrayLen(int target, std::vector<int>& nums) {
    int result = INT32_MAX;
    int sum = 0;
    int left = 0;
    int right = 0;
    for (right; right < nums.size(); right++) {
        sum += nums[right];
        while (sum >= target) {
            result = std::min(result, right - left + 1);
            sum -= nums[left];
            left++;
        }
    }
    return result == INT32_MAX ? 0 : result;

}
// 209暴力法
int minSubArrayLen2(int s, std::vector<int>& nums) {
    int result = INT32_MAX; // 最终的结果
    int sum = 0; // 子序列的数值之和
    int subLength = 0; // 子序列的长度
    for (int i = 0; i < nums.size(); i++) { // 设置子序列起点为i
        sum = 0;
        for (int j = i; j < nums.size(); j++) { // 设置子序列终止位置为j
            sum += nums[j];
            if (sum >= s) { // 一旦发现子序列和超过了s，更新result
                subLength = j - i + 1; // 取子序列的长度
                result = result < subLength ? result : subLength;
                break; // 因为我们是找符合条件最短的子序列，所以一旦符合条件就break
            }
        }
    }
    // 如果result没有被赋值的话，就返回0，说明没有符合条件的子序列
    return result == INT32_MAX ? 0 : result;
}

