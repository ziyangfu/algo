#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

// 二叉树节点定义
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 方法一：使用深度优先搜索，递归实现
// 注意：入参中的path是值传递，而不是引用传递
void dfs(TreeNode* root, std::string path, std::vector<std::string>& paths) {
    if (root == nullptr) {
        return;
    }
    // 将当前节点添加到路径中
    path += std::to_string(root->val);
    // 如果是叶子节点，将路径添加到结果中
    if (root->left == nullptr && root->right == nullptr) {
        paths.push_back(path);
    }
    else {
        path += "->";
        dfs(root->left, path, paths);
        dfs(root->right, path, paths);
    }
}
// 方法2：引用 + 手动回溯
void dfs_with_backtracking(TreeNode* root, std::string& path, 
                    std::vector<std::string>& paths) {
    if (root == nullptr) {
        return;
    }
     // 记录当前路径长度，用于回溯
    int origin_path_size = path.size();
    // 将当前节点添加到路径中
    path += std::to_string(root->val);
    // 如果是叶子节点，将路径添加到结果中
    if (root->left == nullptr && root->right == nullptr) {
        paths.push_back(path);
    }
    else {
        // 如果不是叶子节点，添加连接符
        path += "->";
        dfs_with_backtracking(root->left, path, paths);
        dfs_with_backtracking(root->right, path, paths);
    }
    // 回溯：恢复路径到进入当前节点之前的状态
    path.resize(origin_path_size);
}

std::vector<std::string> binaryTreePaths(TreeNode* root) {
    std::vector<std::string> paths;
    if (root == nullptr) {
        return paths;
    }
    std::string path;
    //dfs(root, path, paths);
    dfs_with_backtracking(root, path, paths);
    return paths;
}

// 辅助函数：创建测试用的二叉树
TreeNode* createTestTree1() {
    // 创建树: [1,2,3,null,5]
    //     1
    //    / \
    //   2   3
    //    \
    //     5
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(5);
    return root;
}

TreeNode* createTestTree2() {
    // 创建树: [1]
    TreeNode* root = new TreeNode(1);
    return root;
}

TreeNode* createTestTree3() {
    // 创建树: [1,2,3,4,5]
    //     1
    //    / \
    //   2   3
    //  / \
    // 4   5
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    return root;
}

TreeNode* createTestTree4() {
    // 创建空树
    return nullptr;
}

// 辅助函数：释放二叉树内存
void deleteTree(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// 辅助函数：打印结果
void printResults(const std::vector<std::string>& results) {
    std::cout << "[";
    for (size_t i = 0; i < results.size(); ++i) {
        std::cout << "\"" << results[i] << "\"";
        if (i < results.size() - 1) {
            std::cout << ",";
        }
    }
    std::cout << "]" << std::endl;
}

// 辅助函数：检查结果是否正确（忽略顺序）
bool checkResults(const std::vector<std::string>& actual, const std::vector<std::string>& expected) {
    if (actual.size() != expected.size()) {
        return false;
    }
    
    std::vector<std::string> actualSorted = actual;
    std::vector<std::string> expectedSorted = expected;
    
    std::sort(actualSorted.begin(), actualSorted.end());
    std::sort(expectedSorted.begin(), expectedSorted.end());
    
    return actualSorted == expectedSorted;
}

// 测试函数
void runTests() {
    std::cout << "开始测试二叉树所有路径问题..." << std::endl;
    
    // 测试用例1: [1,2,3,null,5]
    {
        std::cout << "\n测试用例1: [1,2,3,null,5]" << std::endl;
        TreeNode* root = createTestTree1();
        std::vector<std::string> result = binaryTreePaths(root);
        std::vector<std::string> expected = {"1->2->5", "1->3"};
        
        std::cout << "期望结果: ";
        printResults(expected);
        std::cout << "实际结果: ";
        printResults(result);
        
        assert(checkResults(result, expected));
        std::cout << "测试通过!" << std::endl;
        
        deleteTree(root);
    }
    
    // 测试用例2: [1]
    {
        std::cout << "\n测试用例2: [1]" << std::endl;
        TreeNode* root = createTestTree2();
        std::vector<std::string> result = binaryTreePaths(root);
        std::vector<std::string> expected = {"1"};
        
        std::cout << "期望结果: ";
        printResults(expected);
        std::cout << "实际结果: ";
        printResults(result);
        
        assert(checkResults(result, expected));
        std::cout << "测试通过!" << std::endl;
        
        deleteTree(root);
    }
    
    // 测试用例3: [1,2,3,4,5]
    {
        std::cout << "\n测试用例3: [1,2,3,4,5]" << std::endl;
        TreeNode* root = createTestTree3();
        std::vector<std::string> result = binaryTreePaths(root);
        std::vector<std::string> expected = {"1->2->4", "1->2->5", "1->3"};
        
        std::cout << "期望结果: ";
        printResults(expected);
        std::cout << "实际结果: ";
        printResults(result);
        
        assert(checkResults(result, expected));
        std::cout << "测试通过!" << std::endl;
        
        deleteTree(root);
    }
    
    // 测试用例4: 空树
    {
        std::cout << "\n测试用例4: 空树" << std::endl;
        TreeNode* root = createTestTree4();
        std::vector<std::string> result = binaryTreePaths(root);
        std::vector<std::string> expected = {};
        
        std::cout << "期望结果: ";
        printResults(expected);
        std::cout << "实际结果: ";
        printResults(result);
        
        assert(checkResults(result, expected));
        std::cout << "测试通过!" << std::endl;
    }
    
    std::cout << "\n所有测试通过!" << std::endl;
}

int main() {
    try {
        runTests();
    } catch (const std::exception& e) {
        std::cerr << "测试过程中发生错误: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "测试过程中发生未知错误" << std::endl;
        return 1;
    }
    
    return 0;
}
