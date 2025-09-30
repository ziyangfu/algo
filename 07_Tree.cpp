// 二叉树的遍历
// BFS，层序遍历
// // DFS，深度优先遍历，前序，中序，后序
// * [144.二叉树的前序遍历](https://leetcode.cn/problems/binary-tree-preorder-traversal/)
// * [145.二叉树的后序遍历](https://leetcode.cn/problems/binary-tree-postorder-traversal/)
// * [94.二叉树的中序遍历](https://leetcode.cn/problems/binary-tree-inorder-traversal/)



//  三个核心问题，递归函数参数及返回值，递归函数的功能，递归的终止条件
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
}
// 144 前序遍历，递归法
void preTraversal(TreeNode* root, vector<int>& res) {
    if (root == nullptr) {
        return;
    }
    res.push_back(root->val, res);
    preTraversal(root->left, res);
    preTraversal(root->right);
}

vector<int> preorderTraversal(TreeNode* root) {
    vector<int> res;
    preTraversal(root, res);
    return res;
}
// 144 迭代法
vector<int> preorderTraversal01(TreeNode* root) {
    vector<int> res;
    std::stack<TreeNode*> st;
    if (root == nullptr) {
        return res;
    }
    st.push(root);

    while (!st.empty()) {
        TreeNode* node = st.top();      // 中
        st.pop();

        res.push_back(node->val);
        if (node->right != nullptr) st.push(node->right); // 右
        if (node->left != nullptr) st.push(node->left); // 左
    }

    return res;
}


// 94 中序遍历，递归法
void inTraversal(TreeNode* root, vector<int>& res) {
    if (root == nullptr) {
        return;
    }
    inTraversal(root->left, res);
    res.push_back(root->val, res);
    inTraversal(root->right);
}
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> res;
    inTraversal(root, res);
    return res;
}
// 94 迭代法
// 核心：要访问的节点与要处理写入vector的节点，不一致，而前序节点是一致的。
// 因此需要先用栈把节点都保存下来
vector<int> inorderTraversal02(TreeNode* root) {
    vector<int> res;
    stack<TreeNode*> st;

    TreeNode* cur = root;

    while (cur != nullptr || !st.empty()) {
        if (cur != nullptr) { // 指针一直到最底层的叶子节点
            st.push(cur);       // 将要访问的节点入栈 
            cur = cur->left;    // 左
        }
        else {
            cur = st.top();     // 栈顶节点出栈
            st.pop();
            res.push_back(cur->val); // 中
            cur = cur->right;       // 右
        }
    }
    
    return res;
}
// 145 后序遍历，递归法
void postTraversal(TreeNode* root, vector<int>& res) {
    if (root == nullptr) {
        return;
    }
    postTraversal(root->left, res);
    postTraversal(root->right, res);
    res.push_back(root->val);
}
vector<int> postorderTraversal(TreeNode* root) {
    vector<int> res;
    postTraversal(root, res);
    return res;
}
// 后序遍历，迭代法
// 核心：前序遍历，中左右，后序遍历，左右中
// 因此先调整前序遍历代码修改为，中右左，然后反转变为左右中
vector<int> postorderTraversal02(TreeNode* root) {
    vector<int> res;
    std::stack<int> st;
    if (root == nullptr) return res;

    while (!st.empty()) {
        TreeNode* node = st.top();
        node.top();
        res.push_back(node.val);
        if (node.left != nullptr) {// 相对于前序遍历，这更改一下入栈顺序 （空节点不入栈）
            st.push(node.left);
        }
        if (node.right != nullptr) {
            st.push(node.right);
        }
    }
    std::reverse(res.begin(), res.end());
    return res;
}
// 102.二叉树的层序遍历
// 层序遍历
// 核心，使用队列
vector<vector<int>> levelOrder(TreeNode* root) {
    std::queue<TreeNode*> que;
    if (root != nullptr) {
        que.push(root);
    }
    vector<vector<int>> result;

    while (que.empty() == false) {
        int size = que.size();
        vector<int> vec;
        // 这里一定要使用固定大小size，不要使用que.size()，因为que.size是不断变化的
        for (int i = 0; i < size; i++) {
            // 遍历当前层的每个节点
            TreeNode* node = que.front();
            que.pop();
            vec.push_back(node->val);
            // 把下一层的所有节点放入队列
            if (node->left != nullptr) {
                que.push(node->left);
            }
            if (node->right != nullptr) {
                que.push(node->right);
            }
        }
        result.push_back(vec);
    }
    return result;
}
// 107.二叉树的层次遍历II
// 先正常层序遍历，再反转结果：
    // 按照102题的方法实现层序遍历
    // 最后将结果vector进行反转
// 使用栈辅助：
    // 在层序遍历时，将每层结果压入栈中
    // 最后从栈中弹出得到自底向上的结果
vector<vector<int>> levelOrderBottom(TreeNode* root) {
    vector<vector<int>> result = levelOrder(root);
    std::reverse(result.begin(), result.end());
    return result;
}

vector<int> rightSideView(TreeNode* root) {
    vector<vector<int>> res = levelOrder(root);
    vector<int> result;
    if (!res.empty()) {
        for (int i = 0; i < res.size(); i++) {
            result.push_back(res[i][res[i].size() - 1]);
        }
    }
    return result;
}

vector<int> rightSideView01(TreeNode* root) {
    vector<int> result;
    if (root == nullptr) return result;
    
    queue<TreeNode*> que;
    que.push(root);
    
    while (!que.empty()) {
        int levelSize = que.size();
        // 处理当前层的所有节点
        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = que.front();
            que.pop();
            
            // 如果是当前层的最后一个节点，则加入结果
            if (i == levelSize - 1) {
                result.push_back(node->val);
            }
            
            // 将下一层节点加入队列
            if (node->left) que.push(node->left);
            if (node->right) que.push(node->right);
        }
    }
    
    return result;
}

// 111.二叉树的最小深度
int minDepth(TreeNode* root) {
    std::queue<TreeNode*> que;
    int depth = 0;
    if (root != nullptr) {
        que.push(root);
    }
    
    while (!que.empty()) {
        depth++;
        int levelSize = que.size();
        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = que.front();
            que.pop();
            if (node->left == nullptr && node->right == nullptr)
            {
                return depth;
            }
            if (node->left != nullptr)
            {
                que.push(node->left);
            }
            if (node->right != nullptr)
            {
                que.push(node->right);
            }   
        }
    }
    return depth;
}

// 226.翻转二叉树
// 对每一个节点，交换左右子树
// 如果是前序遍历，则是从root开始交换
// 如果是后序遍历，则是从叶子节点开始交换
TreeNode* invertTree(TreeNode* root) {
    // 递归终止条件
    if (root == nullptr) {
        return nullptr;
    }
    std::swap(root->left, root->right)；
    invertTree(root->left);
    invertTree(root->right);

    return root;
}
// 101.对称二叉树
bool isSymmetric(TreeNode* root) {
    if (root == nullptr) {
        return true;
    }
    return compare(root->left, root->right);
}

bool compare(TreeNode* left, TreeNode* right) {
    // 递归终止条件
    // 2. 一个为空，一个不为空，则不对称
    if (left != nullptr && right == nullptr) return false;
    else if (left == nullptr && right != nullptr) return false;
    // 1. 两个节点都为空，则对称
    else if (left == nullptr && right == nullptr) return true;
    // 3. 两个节点都不为空，但值不相等，则不对称
    else if (left->val != right->val) return false;
    // 递归比较：外侧 vs 外侧，内侧 vs 内侧
    // 左子树的左 vs 右子树的右
    bool outside = compare(left->left, right->right);
    // 左子树的右 vs 右子树的左
    bool inside = compare(left->right, right->left);

    return outside && inside;

}


// 104.二叉树的最大深度
// 递归法
int maxDepth(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }
    return getDepth(root);
}

int getDepth(TreeNode* node) {
    if (node == nullptr) {
        return 0;
    }
    // 求左子树深度，再求右子树深度，取最大值
    int leftDepth = getDepth(node->left);
    int rightDepth = getDepth(node->right);
    return (std::max(leftDepth,rightDepth) + 1); // 左/右子树的深度，+ 中间节点数 1

}
// 迭代法 层序遍历法
int maxDepth01(TreeNode* root) {
    std::queue<TreeNode*> que;
    int depth = 0; 
    if (root != nullptr) {
        que.push(root);
    }
    while (!que.empty()) {
        depth++;
        int size = que.size();
        for (int i = 0; i < size; i++) {
            TreeNode* node = que.front();
            que.pop();
            
            if (node->left != nullptr) {
                que.push(node->left);
            }
            if (node->right != nullptr) {
                que.push(node->right);
            }
        }
    }
    return depth;
}
























// 二叉树：
// 二叉树：
// 二叉树：111.二叉树的最小深度
// 二叉树：222.完全二叉树的节点个数
// 二叉树：110.平衡二叉树
// 二叉树：257.二叉树的所有路径

// 二叉树：404.左叶子之和](./problems/0404.左叶子之和.md)
// 二叉树：513.找树左下角的值](./problems/0513.找树左下角的值.md)
// 二叉树：112.路径总和](./problems/0112.路径总和.md)
// 二叉树：106.构造二叉树](./problems/0106.从中序与后序遍历序列构造二叉树.md)
// 二叉树：654.最大二叉树](./problems/0654.最大二叉树.md)
// * [本周小结！（二叉树）](./problems/周总结/20201010二叉树周末总结.md)
// * [二叉树：617.合并两个二叉树](./problems/0617.合并二叉树.md)
// * [二叉树：700.二叉搜索树登场！](./problems/0700.二叉搜索树中的搜索.md)
// * [二叉树：98.验证二叉搜索树](./problems/0098.验证二叉搜索树.md)
// * [二叉树：530.搜索树的最小绝对差](./problems/0530.二叉搜索树的最小绝对差.md)
// * [二叉树：501.二叉搜索树中的众数](./problems/0501.二叉搜索树中的众数.md)
// * [二叉树：236.公共祖先问题](./problems/0236.二叉树的最近公共祖先.md)
// * [本周小结！（二叉树）](./problems/周总结/20201017二叉树周末总结.md)
// * [二叉树：235.搜索树的最近公共祖先](./problems/0235.二叉搜索树的最近公共祖先.md)
// * [二叉树：701.搜索树中的插入操作](./problems/0701.二叉搜索树中的插入操作.md)
// * [二叉树：450.搜索树中的删除操作](./problems/0450.删除二叉搜索树中的节点.md)
// * [二叉树：669.修剪二叉搜索树](./problems/0669.修剪二叉搜索树.md)
// * [二叉树：108.将有序数组转换为二叉搜索树](./problems/0108.将有序数组转换为二叉搜索树.md)
// * [二叉树：538.把二叉搜索树转换为累加树](./problems/0538.把二叉搜索树转换为累加树.md)




// 层序遍历系列
// [199.二叉树的右视图](https://leetcode.cn/problems/binary-tree-right-side-view/)
// [637.二叉树的层平均值](https://leetcode.cn/problems/average-of-levels-in-binary-tree/)
// [429.N叉树的层序遍历](https://leetcode.cn/problems/n-ary-tree-level-order-traversal/)
// [515.在每个树行中找最大值](https://leetcode.cn/problems/find-largest-value-in-each-tree-row/)
// [116.填充每个节点的下一个右侧节点指针](https://leetcode.cn/problems/populating-next-right-pointers-in-each-node/)
// [117.填充每个节点的下一个右侧节点指针II](https://leetcode.cn/problems/populating-next-right-pointers-in-each-node-ii/)
// [104.二叉树的最大深度](https://leetcode.cn/problems/maximum-depth-of-binary-tree/)

