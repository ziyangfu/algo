
// 344.反转字符串
void reverseString(vector<char>& s) {
    int left = 0;
    int right = s.size() - 1;

    while(left < right) {
        std::swap(s[left], s[right]);
        left++;
        right--;
    }
}
// 541.反转字符串II
// 效率差的个人实现版本
string reverseStr(string s, int k) {
    std::string newStr;
    auto reverse = [](std::string& str) {
        int left = 0;
        int right = str.size() - 1;
        while (left < right) {
            std::swap(str.at(left), str.at(right));
            left++;
            right--;
        }
    };

    for (size_t i = 0; i < s.size(); i += 2 * k) {
        // 对2K的处理，转换1K的逻辑
        std::string sk1;
        std::string sk2;
        
        // 边界处理， all < k or 剩余 < k
        if (s.size() <= i + k) {
            // substr的第二个参数是len
            sk1 = s.substr(i, s.size() - i); 
            reverse(sk1);
            newStr += sk1;
        }
        //   k < all or 剩余 < 2k 
        else if (s.size() < i + 2 * k) {
            std::string sk1 = s.substr(i, k);
            reverse(sk1);
            std::string sk2 = s.substr(i + k, s.size() - i - k);
            newStr += sk1;
            newStr += sk2;
        }
        else {
            std::string sk1 = s.substr(i, k);
            reverse(sk1);
            std::string sk2 = s.substr(i + k, k);
            newStr += sk1;
            newStr += sk2;
        }
    }
    return newStr;
}
// 效率高的版本
// 关键：只需要找到需要转换的区间即可
// 只需要判别 size 与 k 哪个大
string reverseStr02(string s, int k) {
    for (int i = 0; i < s.size(); i+=2*k) {
        // 获得要转换的长度
        int len = std::min(k, static_cast<int>(s.size() - i));
        // algorithm中的转换算法
        std::reverse(s.begin() + i, s.begin() + i + len);
    }
    return s;
}

// 给定一个字符串 s，它包含小写字母和数字字符，请编写一个函数，将字符串中的字母字符保持不变，而将每个数字字符替换为number
// 将字符串中的数字字符替换为对应的英文单词
// 字符串：替换数字
// 卡码网，可以考虑不申请新的string，原地挪移修改
string replaceDigits(string s) {
    std::string newStr;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            newStr += "number";
        }
        else {
            newStr += s[i];

        }
    }
    return newStr;
}

// 151.翻转字符串里的单词
// 太多复杂，且存在部分错误
string reverseWords(string s) {
    std::string newStr;
    // 处理多余空格
    s = s.insert(0, 1, 's');  // 前插一个字符，排除前面有空格
    s = s + 'e'; // 尾插一个字符，排除后面有空格
    //std::cout << "s: " << s << std::endl;
    // 此时所有情况都变为中间有空格
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ' ') {
            newStr += " ";
            while (s[i] == ' ') {
                i++;
            }
            i--;
        }
        else {
            newStr += s[i];
        }
    }
    // 对类似 s hello world e 的处理
    int start = 0;
    int len = 0;
    if (newStr[1] == ' ') {
    	start = 2;
    }
    else {
    	start = 1;
    }
    if (newStr[newStr.size() - 2] == ' ') {
    	len = newStr.size() - start - 2;
    }
    else {
    	len = newStr.size() - start - 1;
    }
    

    newStr = newStr.substr(start, len); // 去掉头尾2字符
    std::cout << "new str: " << newStr << std::endl;
    // 全部翻转
    std::reverse(newStr.begin(), newStr.end());
    // 遍历单词，翻转单词
    for(int i = 0; i < newStr.size(); i++) {
        int first = i; // 单词的起始位置
        while(newStr[i] != ' ' && i < newStr.size()) {
            i++;
        }
        std::reverse(newStr.begin() +first, newStr.begin() +i);
    }
    return newStr;
}

string reverseWords01(string s) {
    std::string newStr;

    int start = 0;
    int end = s.size() - 1;
    // 指向第一个非空字符
    while (start <= end && s[start] == ' ') start++;
    // 找到最后一个非空字符
    while (end <= start && s[end] == ' ') end--;

    for (int i = start; i <= end; i++) {
        if (s[i] == ' ') {
            newStr += " ";
            while (i < end && s[i] == ' ') i++;
            // 因为后面for循环还会++，所以要补偿一下，不然就跳过了
            i--;
        }
        else {
            newStr += s[i];
        }
    }
    // 2. 反转整个字符串
    std::reverse(newStr.begin(), newStr.end());
    // 3. 反转每个单词
    int wordStart = 0;
    for (int i = 0; i < newStr.size(); i++) {
        if (i == newStr.size() || newStr[i] == ' ') {
            std::reverse(newStr.begin() + wordStart, newStr.begin() + i);
            wordStart = i + 1;
        }
    }
    return newStr;

}
// 更简洁的实现
string reverseWords02(string s) {
    // 提取所有单词
    vector<string> words;
    string word = "";
    
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != ' ') {
            word += s[i];
        } else {
            if (!word.empty()) {
                words.push_back(word);
                word = "";
            }
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }
    
    // 反转单词顺序并组合
    string result = "";
    for (int i = words.size() - 1; i >= 0; i--) {
        result += words[i];
        if (i > 0) result += " ";
    }
    
    return result;
}

// 字符串：右旋字符串
// 字符串：右旋字符串（三次反转法）
string reverseLeftWords(string s, int n) {
    // 1. 反转整个字符串
    reverse(s.begin(), s.end());
    // 2. 反转前s.length-n个字符
    reverse(s.begin(), s.begin() + s.length() - n);
    // 3. 反转后n个字符
    reverse(s.begin() + s.length() - n, s.end());
    return s;
}

// 帮你把KMP算法学个通透 
// 28. 实现 strStr()
// 459.重复的子字符串
