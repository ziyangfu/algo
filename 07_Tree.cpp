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

// 222.完全二叉树的节点个数
// 可以通过遍历计算节点数
// 先序遍历

void preorder(TreeNode* root, int& count) {
    if (root == nullptr) {
        return;
    }
    count++;
    preorder(root->left, count);
    preorder(root->right, count);
}
int countNodes(TreeNode* root) {
    int count {0};
    preorder(root, count);
    return count;
}

// 层序遍历
int countNodes(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }
    int count {0};

    std::queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        count++;
        if (node->left != nullptr) {
            q.push(node->left);
        }
        if (node->right != nullptr) {
            q.push(node->right);
        }
    }
    return count;
}
// 完全二叉树优化



// 平衡二叉树：左右子树高度差不能超过1，且左右子树都是平衡二叉树
// 110.判断是否是平衡二叉树
// 自顶向下递归，节点重复计算，效率低（n^2）

// 计算树的深度
int getDepth(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }
    return 1 + std::max(getDepth(root->left), getDepth(root->right));
}

bool isBalanced(TreeNode* root) {
、  if (root == nullptr) {
        return true;
    }
    int leftDepth = getDepth(root->left);
    int rightDepth = getDepth(root->right);

    return std::abs(leftDepth - rightDepth) <= 1 && 
            isBalanced(root->left) && 
            isBalanced(root->right);

}
// 方案2：自底向上递归，效率更高
// 辅助函数：计算树的高度，并同时检查是否平衡
// 如果不平衡，返回 -1；如果平衡，返回当前子树的高度
int getHeightAndCheckBalanced(TreeNode* root) {
    // 基本情况：空节点是平衡的，高度为 0
    if (root == nullptr) {
        return 0;
    }
    // 递归计算左子树的高度并检查平衡性
    int leftHeight = getHeightAndCheckBalanced(root->left);
    // 如果左子树不平衡，则整个树也不平衡
    if (leftHeight == -1) {
        return -1;
    }
    // 递归计算右子树的高度并检查平衡性
    int rightHeight = getHeightAndCheckBalanced(root->right);
    if (rightHeight == -1) {
        return -1;
    }
    // 检查当前节点左右子树的高度差是否超过 1
    if (std::abs(leftHeight - rightHeight) > 1) {
        return -1;
    }
    // 如果当前节点及其子树都平衡，返回当前子树的高度
    // 当前节点的高度是其左右子树最大高度加 1
    return 1 + std::max(leftHeight, rightHeight);
}
bool isBalanced02(TreeNode* root) {
    // 如果辅助函数返回 -1，说明树不平衡，否则平衡
    return getHeightAndCheckBalanced(root) != -1;
}

// 257. 二叉树的所有路径问题
// 方法一：使用深度优先搜索，递归实现
// 注意： 入参中的path是值传递，而不是引用传递，
//      在递归中，每次递归调用都会创建一个新的字符串对象，而不是修改传入的参数。
//      这很重要，不然右子树会带有左子树的路径
void dfs(TreeNode* root, std::string path, 
                    std::vector<std::string>& paths) {
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

vector<string> binaryTreePaths(TreeNode* root) {
    std::vector<std::string> paths;
    if (root == nullptr) {
        return paths;
    }
    std::string path;
    dfs(root, path, paths);
    return paths;
}
// 方法2: 引用传递 + 手动回溯
// 注意，这里的传参path是引用传递
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

vector<string> binaryTreePaths02(TreeNode* root) {
    std::vector<std::string> paths;
    if (root == nullptr) {
        return paths;
    }
    std::string path;
    dfs_with_backtracking(root, path, paths);
    return paths;
}
// 404.左叶子之和
// 分析，什么是左叶子节点
// 左叶子：父节点的左节点，且是叶子（左右子节点都为nullptr）
// 前序遍历
void dfs_left_leaf(TreeNode* root, int& sum) {
    if (root == nullptr) {
        return;
    }
    // 父节点的左节点 && 是叶子节点
    if (root->left != nullptr && 
        root->left->left == nullptr && root->left->right == nullptr) {
            sum += root->left->val;
    }
    dfs_left_leaf(root->left, sum);
    dfs_left_leaf(root->right, sum);
}

int sumOfLeftLeaves(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }
    int sum {0};

    dfs_left_leaf(root, sum);
    return sum;
}
// 513.找树左下角的值
// 分析：什么是最深层最左边的节点
// 叶子节点：左右子节点都为nullptr
// 找到所有的最左边的节点，从中挑出一个最深的节点
int findBottomLeftValue(TreeNode* root) {
    if (root == nullptr)
    {
        return 0;
    }
    std::queue<TreeNode*> q;
    std::vector<std::vector<int> > all_values;
    q.push(root);
    while(!q.empty()) {
        std::vector<int> level_values;
        int size = q.size();
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();
            level_values.push_back(node->val);
            if (node->left != nullptr) {
                q.push(node->left);
            }
            if (node->right != nullptr) {
                q.push(node->right);
            }
        }
        all_values.push_back(level_values);
    }
    // 最后一层的第一个值，就是最深处最左边的值
    return all_values.back().front();
}
// 优化版本，并不需要记录每层的所有节点，只需要记录最左边的节点即可
int findBottomLeftValue02(TreeNode* root) {
    if (root == nullptr)
    {
        return 0;
    }
    std::queue<TreeNode*> q;
    int leftmost_value = root->val;
    while(!q.empty()) {
        std::vector<int> level_values;
        int size = q.size();
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();
            // 记录当前层的第一个节点值
            if (i == 0) {
                leftmost_value = node->val;
            }
            if (node->left != nullptr) {
                q.push(node->left);
            }
            if (node->right != nullptr) {
                q.push(node->right);
            }
        }
    }
    return leftmost_value;
}
// 还可以使用DFS深度优先搜索
// 使用DFS解决这个问题的核心思想是：在遍历过程中记录当前深度，当访问到更深的节点时更新结果
int findBottomLeftValue03(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }
    int maxDepth = -1;
    int leftmostValue = 0;
    dfsfindBottomLeftValue03(root, 0, maxDepth, leftmostValue);
    return leftmostValue;
}

void dfsfindBottomLeftValue03(TreeNode* node, int currentDepth, int& maxDepth, int& leftmostValue) {
    if (node == nullptr) {
        return;
    }
    
    // 如果当前深度大于已记录的最大深度，说明找到了更深的层
    // 由于我们先遍历左子树，所以第一次到达新深度时记录的一定是该层最左边的节点
    if (currentDepth > maxDepth) {
        maxDepth = currentDepth;
        leftmostValue = node->val;
    }
    
    // 先遍历左子树，再遍历右子树
    dfsfindBottomLeftValue03(node->left, currentDepth + 1, maxDepth, leftmostValue);
    dfsfindBottomLeftValue03(node->right, currentDepth + 1, maxDepth, leftmostValue);
}

// 112.路径总和
bool dfs_path_sum(TreeNode* root, int targetSum, int pathSum) {
    if (root == nullptr)
    {
        return false;
    }
    // 更新当前路径和
    pathSum += root->val;
    // 如果是叶子节点，检查路径和是否等于目标值
    if (root->left == nullptr && root->right == nullptr) {
        if (pathSum + root->val == targetSum) {
            return true;
        }
    }
    // 递归检查左右子树
    bool leftHasPathSum = dfs_path_sum(root->left, targetSum, pathSum);
    bool rightHasPathSum = dfs_path_sum(root->right, targetSum, pathSum);  
    return leftHasPathSum || rightHasPathSum;           
}
bool hasPathSum(TreeNode* root, int targetSum) {
    if (root == nullptr)
    {
        return false;
    }
    int pathSum {0};
    return dfs_path_sum(root, targetSum, pathSum);
}

// 更简洁的实现，可以在原函数中实现的
bool hasPathSum02(TreeNode* root, int targetSum) {
    if (root == nullptr) {
        return false;
    }
    
    // 如果是叶子节点，直接比较值
    if (root->left == nullptr && root->right == nullptr) {
        return root->val == targetSum;
    }
    
    // 递归检查左右子树，目标值减去当前节点值
    return hasPathSum(root->left, targetSum - root->val) || 
           hasPathSum(root->right, targetSum - root->val);
}

// 106.构造二叉树
// 给定两个整数数组 inorder 和 postorder，其中 inorder 是二叉树的中序遍历，postorder 是同一棵树的后序遍历，请你构造并返回这颗二叉树
// 核心思想：借助后序确定根节点，借助中序确定左右子树
std::unordered_map<int, int> inorder_map; // 值到中序索引的映射
int postorder_index;    // 后序遍历的当前索引

TreeNode* buildTreeHelper(vector<int>& inorder, vector<int>& postorder,
                          int inorder_start, int inorder_end) {
    // 递归终止条件
    if (inorder_start > inorder_end) {
        return nullptr;
    }
    // 后序遍历的最后一个元素，是当前子树的根节点
    int root_val = postorder[postorder_index];
    postorder_index--; 
    TreeNode* root = new TreeNode(root_val);      
    // 在中序遍历中找到根节点的位置
    int root_index = inorder_map[root_val];
    // 递归构造右子树 （注意：先构造右子树，因为后序遍历是左->右->根）
    // 在右子树的递归中，构建完成左右的右子树，自然，下一个待处理的根是左子树根节点
    // 因此先右再左，顺序不能反，从后往前看，后续遍历是，根，右，左
    root->right = buildTreeHelper(inorder, postorder, root_index+1, inorder_end);
    // 递归构造左子树
    root->left = buildTreeHelper(inorder, postorder, inorder_start, root_index - 1);

    return root;

}

TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    // 构建中序遍历中值到索引的映射，用于快速查找根节点位置
    for (int i = 0; i < inorder.size(); i++) {
        inorder_map[inorder[i]] = i;
    }
    postorder_index = postorder.size() - 1;

    return buildTreeHelper(inorder, postorder, 0, inorder.size() - 1);
}


// 只给前序遍历、中序遍历、后续遍历或者层序遍历中的一个，一般来说，是无法构建唯一二叉树的
// 如果是完满或完全二叉树，任何一种遍历序列，都可以唯一确定一棵树。例如：
// 根据层序遍历构造完全二叉树
TreeNode* buildCompleteBinaryTree(vector<int>& levelOrder) {
    if (levelOrder.empty()) return nullptr;
    
    vector<TreeNode*> nodes;
    // 创建所有节点
    for (int val : levelOrder) {
        nodes.push_back(new TreeNode(val));
    }
    
    // 连接父子节点
    for (int i = 0; i < nodes.size(); i++) {
        int leftChildIdx = 2 * i + 1;
        int rightChildIdx = 2 * i + 2;
        
        if (leftChildIdx < nodes.size()) {
            nodes[i]->left = nodes[leftChildIdx];
        }
        if (rightChildIdx < nodes.size()) {
            nodes[i]->right = nodes[rightChildIdx];
        }
    }
    
    return nodes[0];
}

// 如果是二叉搜索树，仅凭前序、后序或层序遍历就可以唯一构造
// 注意，中序遍历是不行的
// 根据BST的前序遍历构造BST
TreeNode* buildBSTFromPreorder(vector<int>& preorder) {
    if (preorder.empty()) return nullptr;
    
    TreeNode* root = new TreeNode(preorder[0]);
    
    for (int i = 1; i < preorder.size(); i++) {
        insertIntoBST(root, preorder[i]);
    }
    
    return root;
}

void insertIntoBST(TreeNode* root, int val) {
    if (val < root->val) {
        if (root->left == nullptr) {
            root->left = new TreeNode(val);
        } else {
            insertIntoBST(root->left, val);
        }
    } else {
        if (root->right == nullptr) {
            root->right = new TreeNode(val);
        } else {
            insertIntoBST(root->right, val);
        }
    }
}
// 654.最大二叉树
// 类似中序 + 后序构建二叉树，把后序节点，换成数组中的最大值
TreeNode* constructMaximumBinaryTreeHelper(const std::vector<int>& nums, int start, int end) {
    if (start > end) {
        return nullptr;
    }
    // 找到区间最大值及最大值的索引
    int maxIndex = start;
    int maxValue = nums[start];
    for (int i = start + 1; i <= end; i++) {
        if (nums[i] > maxValue) {
            maxValue = nums[i];
            maxIndex = i;
        }
    }
    TreeNode* root = new TreeNode(nums[maxIndex]);

    root->left = constructMaximumBinaryTreeHelper(nums, start, maxValue - 1);
    root->right = constructMaximumBinaryTreeHelper(nums, maxValue + 1, end);

    return root;
} 

TreeNode* constructMaximumBinaryTree(const std::vector<int>& nums) {
    if (nums.empty()) {
        return nullptr;
    }
    return constructMaximumBinaryTreeHelper(nums, 0, nums.size() - 1);
}

// 617.合并两个二叉树
TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
    // 合并规则：
    // 1. 如果 root1 和 root2 都为空，则返回 nullptr。
    // 2. 如果 root1 为空，root2 不为空，则返回 root2。
    // 3. 如果 root1 不为空，root2 为空，则返回 root1。
    // 4. 如果 root1 和 root2 都不为空：
    //    a. 创建一个新的 TreeNode，其值为 root1->val + root2->val。
    //    b. 递归地合并它们的左子树，并将结果赋给新节点的左子节点。
    //    c. 递归地合并它们的右子树，并将结果赋给新节点的右子节点。
    //    d. 返回新节点。
    if (root1 == nullptr && root2 == nullptr) {
        return nullptr;
    }
    if (root1 == nullptr) {
        return root2;
    }
    if (root2 == nullptr) {
        return root1;
    }
    // root1 与 root2 都不空的情况
    // 先创建一个根节点
    TreeNode* merged = new TreeNode(root1->val + root2->val);
    merged->left = mergeTrees(root1->left, root2->left);
    merged->right = mergeTrees(root1->right, root2->right);
    return merged;
}

// 700.二叉搜索树登场，0700.二叉搜索树中的搜索
// 首先可以使用最基本的二叉树遍历来搜索，不利用二叉搜索树的性质
TreeNode* searchBST(TreeNode* root, int val) {
    if (root == nullptr) {
        return nullptr;
    }
    if (root->val == val) {
        return root;
    }
    TreeNode* left = searchBST(root->left, val);
    if (left != nullptr) {
        return left;
    }
    TreeNode* right = searchBST(root->right, val);
    return right;
}
// 使用二叉搜索树特性
// 二叉搜索树的特性是，左子树的值小于根节点，右子树值大于根节点，递归
TreeNode* searchBST02(TreeNode* root, int val) {
    if (root == nullptr) {
        return nullptr;
    }
    if (val == root->val) {
        return root;
    }
    if (val < root->val) {
        return searchBST(root->left, val);
    }
    else {
        return searchBST(root->left, val);
    }
}
// 迭代形式
TreeNode* searchBST_Iterative(TreeNode* root, int val) {
    while (root != nullptr) {
        if (val == root->val) {
            return root;
        }
        else if (val < root->val) {
            root = root->left; // 目标值较小，向左走
        }
        else {
            root = root->right; // 目标值较大，向右走
        }
    }
    return nullptr;
}
// 98.验证二叉搜索树
// 判断一个给定的二叉树是否是一个有效的二叉搜索树（Binary Search Tree, BST）
// 1. 左低右高 2. 递归同样成立 3. 值唯一
// 存在的问题：1. 空指针解引用，如果root是叶子节点，则root->left和root->right会解引用空指针
//           2. 二叉搜索树是左子树的所有节点，都要小于根节点，右子树所有节点都要大于根节点，
//              注意，是所有，下面的时候，只是左子节点小于根节点，当然不对 
bool isValidBST_error(TreeNode* root) {
    if (root == nullptr) {
        return true;
    }
    // 遍历所有的节点，对每一个节点
    if ((root->left->val < root->val) == false) {
        return false;
    };
    if ((root->right->val > root->val) == false) {
        return false;
    };
    bool leftB = isValidBST(root->left);
    bool rightB = isValidBST(root->right); 
    return leftB && rightB;
}
// 正确的实现
bool isValidBSTHelper(TreeNode* root, long minVal, long maxVal  ) { 
    if (root == nullptr) {
        return true; // 空树是有效的 BST
    }
    // 检查当前节点的值是否在允许的范围内
        // 注意：这里使用 long 来避免 int 溢出，以防 minVal 或 maxVal 是 int 的最小值或最大值
    if (root->val <= minVal || root->val >= maxVal) {
        return false;
    }
    // 递归检查左子树：左子树的所有值必须在 minVal 和 node->val 之间
    // 递归检查右子树：右子树的所有值必须在 node->val 和 maxVal 之间
    bool leftB = isValidBSTHelper(root->left, minVal, root->val);
    bool rightB = isValidBSTHelper(root->right, root->val, maxVal);
    return leftB && rightB;
}
bool isValidBST(TreeNode* root) {
    // 初始调用时，最小值设为负无穷，最大值设为正无穷
    // 使用 long long 以确保可以处理 int 范围内的所有值，包括 INT_MIN 和 INT_MAX
    return isValidBSTHelper(root, LONG_MIN, LONG_MAX);

}
// 还有一个特点，二叉搜索树的中序遍历，是一个单调递增的序列
// 因此可以中序遍历，得到一个序列，然后查看这个序列，是否是单调递增的
void inOrderHelper(TreeNode* root, std::vector<int>& vec) { 
    if (root == nullptr) {
        return;
    }
    inOrderHelper(root->left, vec);
    vec.push_back(root->val);
    inOrderHelper(root->right, vec);
}
bool isValidBST_02(TreeNode* root) {
    std::vector<int> vec;
    inOrderHelper(root, vec);
    for (int i = 0; i < vec.size() - 1; i++) {
        if (vec[i + 1] - vec[i] <= 0) { // 有重复值也是不符合要求的
            return false;
        }
    }
    return true;
}
// 530.搜索树的最小绝对差
// 任意两个不同节点之间值的绝对差的最小值
// 通过前面的inOrder遍历，得到一个有序的序列
int getMinimumDifference(TreeNode* root) {
    std::vector<int> vec;
    int min = INT_MAX;
    inOrderHelper(root, vec);
    for (int i = 0; i < vec.size() - 1; i++) {
        min = std::min(min, vec[i + 1] - vec[i]);
    }
    return min;
}

// 更优方案
// 优化空间复杂度
// 我们可以不必显式地存储整个有序序列。在进行中序遍历的过程中，我们只需要记录 
// 前一个被访问的节点（previous node） 的值，然后将当前节点的值与前一个节点的值
// 进行比较即可。这样就可以将空间复杂度从 O(N) 优化到 O(1)（如果不考虑递归栈空间的话）。
// 下面是优化后的实现思路：
// 在遍历函数中维护一个指向前一个节点的指针 prev。
// 同样进行中序遍历（左 -> 根 -> 右）。
// 在处理根节点时：
//      检查 prev 是否为 nullptr。如果不是，说明我们已经访问过一个节点了。
//      计算当前节点 root->val 与前一个节点 prev->val 的差值，并更新全局的最小差值。
//      将 prev 更新为当前节点
void inOrderTraversal(TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    // 1. 遍历左子树
    inOrderTraversal(root->left);

    // 2. 处理当前节点
    if (prevNode != nullptr) {
        // 如果前一个节点存在，计算差值并更新最小值
        minDiff = std::min(minDiff, root->val - prevNode->val);
    }
    // 更新前一个节点为当前节点
    prevNode = root;

    // 3. 遍历右子树
    inOrderTraversal(root->right);
}
int getMinimumDifference02(TreeNode* root) {
    inOrderTraversal(root);
    return minDiff;
}
// 501.二叉搜索树中的众数
// 含重复值的 二叉搜索树（BST） 的根节点 root，
// 找出并返回其中的 众数（即出现频率最高的元素

// 哈希表法
void findModeHelper(TreeNode* root, std::unordered_map<int, int>& map) { 
    if (root == nullptr) {
        return;
    }
    map[root->val]++;
    findModeHelper(root->left, map);
    findModeHelper(root->right, map);
}
// O(N)
std::vector<int> findMode(TreeNode* root) {
    std::vector<int> vec;
    int max = 0;
    std::unordered_map<int, int> map; // 值， 频率
    findModeHelper(root, map);
    
    for (auto it = map.begin(); it != map.end(); it++) {
        if (it->second > max) {
            max = it->second;
        }
    }
    for (auto it = map.begin(); it != map.end(); it++) {
        if (it->second == max) {
            vec.push_back(it->first);
        }
    }
    return vec;
}

std::vector<int> result;    // 存储众数
int maxCount = 0;           // 全局最高频率
int currentCount = 0;       // 当前元素的频率
int preVal = INT_MIN;// 上一个访问的节点值 (INT_MIN 确保第一个元素能被正确初始化)

void inOrderTraversal(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    inOrderTraversal(root->left);
    // 2. 处理根节点（关键逻辑）
    // 统计频率
    if (root->val == prevVal) {
        currentCount++;
    }
    else {
        // 遇到了一个新的值， 重置频率
        preVal = root->val;
        currentCount = 1;
    }

    // 更新结果集
    if (currentCount > maxCount) {
        maxCount = currentCount; // 找到新的最高频率
        result.clear(); // 清空旧的众数
        result.push_back(root->val); 
    }
    else if (currentCount == maxCount) {
        result.push_back(root->val); // 当前值也是众数
    }

    inOrderTraversal(root->right); 
}
// 236.公共祖先问题
// 非递减数组法
std::vector<int> findMode02(TreeNode* root) {
    inorderTraversal(root);
    return result;
}
// 自低向上递归
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == nullptr) {
        return nullptr;
    }
    // 命中目标，等待另一个目标从另一侧子树或上层节点返回
    if (root == p || root == q) {
        return root;
    }

    TreeNode* leftT = lowestCommonAncestor(root->left, p, q);  // 左子树
    TreeNode* rightT = lowestCommonAncestor(root->right, p, q); // 右子树
    // 后序，此时根节点的左右子树都遍历完了，注意，后序遍历是自下而上的
    // 4. 汇总结果并判断 LCA
    //  p 和 q 分布在 root 的两侧，那么 root 就是 LCA。
    if (leftT != nullptr && rightT != nullptr) {
        return root; // p，q分别在左右子树中，则当前节点是公共祖先节点
    }
    // 左侧非空，右侧为空
    // p 和 q 都在左子树中，或者 p 或 q 就是 left 返回的节点，LCA 在左边。
    // 将 left (即找到的节点或 LCA) 继续向上传递。
    if (leftT != nullptr) {
        return leftT;
    }
    // 情况 C：左侧为空，右侧非空
    // p 和 q 都在右子树中，LCA 在右边。
    // 将 right (即找到的节点或 LCA) 继续向上传递。
    if (rightT != nullptr) {
        return rightT;
    }
    // 情况 D：左右皆空 ( left == nullptr && right == nullptr )
    // 当前子树中没有 p 或 q，返回空。
    return nullptr; 
}
// 思路，如果p，q分别在某节点的左子树或右子树中，则说明当前节点是公共祖先节点

// 235.搜索树的最近公共祖先
// 特别在于二叉搜索树，利用BST特性剪枝
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == nullptr) {
        return nullptr;
    }
    // p、q都比root小，所以pq都在左边
    if (p->val < root->val && q->val < root->val) {
        return lowestCommonAncestor(root->left, p, q);
    }
    // p、q都比root大, 所以pq都在右边
    if (p->val > root->val && q->val > root->val) {
        return lowestCommonAncestor(root->right, p, q);
    }
    // p在左边，q在右边，或者 p在右边，q在左边
    // 此时 root 就是 p 和 q 的最近公共祖先
    // 怎么理解最近？自底向上，最先达标的，肯定是最近
    if (p->val < root->val && q->val > root->val) {
        return root;
    }
}
// 701.搜索树中的插入操作
// 插入值到二叉搜索树的合适位置
TreeNode* insertIntoBST(TreeNode* root, int val) {
    // 1. 基线条件：找到插入位置
    // 如果 root 为空，说明我们已经到达了树的边缘，这里就是新节点的位置
    // 它返回后，要么会挂在root->left，要么就挂在root->right
    if (root == nullptr) {
        return new TreeNode(val);
    }
    // 严格来说，不存在相同的值
    if (val < root->val) {
        // 如果 val 小于当前节点值，则应该插入到左子树
        // 关键：将左子树递归调用的返回值赋值给 root->left
        // 这样，如果左子树返回一个新节点（即基线条件被触发），
        // 那么这个新节点就会被正确地链接到 root 上。
        root->left = insertIntoBST(root->left, val);
    }
    if (val > root->val) {
        root->right = insertIntoBST(root->right, val);
    }
    // 3. 返回当前节点
    // 在返回路径上，每个节点都保持不变（结构可能因左右子树的更改而改变）
    return root; // 占位符
}
// 迭代法
TreeNode* insertIntoBST_Iterative(TreeNode* root, int val) {
    TreeNode* newNode = new TreeNode(val);

    // 特殊情况：树为空
    if (root == nullptr) {
        return newNode;
    }

    TreeNode* current = root;
    TreeNode* parent = nullptr;

    // 1. 寻找插入位置（循环直到 current 为 nullptr）
    while (current != nullptr) {
        parent = current; // 记录当前节点作为父节点
        
        if (val < current->val) {
            current = current->left;
        } else if (val > current->val) {
            current = current->right;
        } 
        // 同样假设 val 不会等于现有值
    }

    // 2. 插入新节点（连接到 parent）
    if (val < parent->val) {
        parent->left = newNode;
    } else { // val > parent->val
        parent->right = newNode;
    }

    // 3. 返回原始根节点
    return root;
}
// 450.搜索树中的删除操作
// 删除二叉搜索树的节点
// 删除了节点后，需要保持搜索树的特性，这需要一定的重构

// 辅助函数：查找右子树中的最小节点（即后继节点）
TreeNode* findMin(TreeNode* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}
TreeNode* deleteNode(TreeNode* root, int key) {
    if (root == nullptr) {
        return nullptr; // 键不存在或到达叶子节点
    }
     // 1. 查找目标节点 (递归向下)
    if (key < root->val) {
        // 目标在左子树，并将左子树的返回值（可能的新根）链接回来
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->val) {
        // 目标在右子树
        root->right = deleteNode(root->right, key);
    }
     // 2. 找到了目标节点 (key == root->val)
    else {
        // 情况 A & B: 0 或 1 个子节点
        // 如果只有一边，那就左节点挂载左边，右节点挂在右边，能保持BST特性
        if (root->left == nullptr) {
            // 包括了 0 个子节点（都为 nullptr）和只有右子节点的情况
            TreeNode* temp = root->right;
            delete root;
            return temp;  // 返回右子节点作为新的根，如果左右都空，那返回的也是nullptr
        }
        else if (root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;
            return temp; // 返回左子节点作为新的根
        }
        // 情况 C: 两个子节点
        else {
            // 找到右子树中的最小节点 (后继节点)
            TreeNode* temp = findMin(root->right);
            // a. 用后继节点的值覆盖当前节点的值
            root->val = temp->val;
            // b. 递归地删除后继节点（现在后继节点变成了“待删除”节点，它最多只有一个右子节点）
            // 这是关键步骤，它利用了情况 A/B 的逻辑来简化删除
            root->right = deleteNode(root->right, temp->val);
        }
    }
    return root;
}
/**
删除有两个子节点的二叉搜索树（BST）节点（情况 C）是 BST 删除操作中最复杂的部分，但其背后的逻辑是为了维护 BST 的核心有序性。

核心问题：维护 BST 有序性
当一个节点 N（有两个子节点）被删除后，必须用另一个节点 S 来填补 N 的位置，同时 S 必须满足以下条件：
    S 必须大于 N 原来左子树中的所有值。
    S 必须小于 N 原来右子树中的所有值。

只有两个节点符合这个要求：
    后继节点 (In-order Successor)： 右子树中最小的那个节点。
    前驱节点 (In-order Predecessor)： 左子树中最大的那个节点。

最常见的做法是使用后继节点 S 来替代被删除节点 N。

替代节点（后继节点）的特点
后继节点 S 有两个关键特点，使得用它来替代 N 变得可行且高效：

有序性保证： S 是右子树中最小的，所以它天然大于左子树的所有节点，也小于右子树中除了 S 之外的所有节点。用 S 替换 N 后，BST 的有序性得到完美维护。

简单删除： 由于 S 是其子树（即 N 的右子树）中的最小节点，这意味着 S 最多只有一个子节点——右子节点。它不可能有左子节点（否则它就不是最小的了）。

步骤详解（以使用后继节点为例）
假设要删除的节点是 N。

步骤 1: 找到后继节点 S
后继节点 S 位于 N 的右子树中，沿着左侧链一直向下走：

S=findMin(N→right)
步骤 2: 替换值，而不是替换节点本身
为了简化父节点的指针操作，我们不直接将 S 移动到 N 的位置。而是采取一个巧妙的技巧：

N→val=S→val
现在，节点 N 的值已经被更新为 S 的值。从外部看，N 已经完成了它的使命。但是，现在树中出现了两个值为 S.val 的节点（一个在 N 的位置，一个在 S 的原位置）。

步骤 3: 递归删除后继节点 S
由于我们已经用 S 的值填充了 N 的位置，现在 S 的原始位置必须被删除。

因为 S 最多只有一个右子节点（如上面所分析），所以删除 S 的操作现在简化为情况 B（删除一个只有 0 个或 1 个子节点的节点）。

N→right=deleteNode(N→right,S→val)
在递归调用中：

deleteNode 函数会找到 S。

由于 S 没有左子节点，它会进入情况 B 的逻辑，用 S 的右子节点（如果有）来替换 S 的位置，然后将该子节点返回给 N→right。

这样，两个难题就分步解决了：

维护有序性（通过值替换）。

简化删除操作（将删除两个子节点的难题转化为删除一个零或一个子节点的简单问题）。

总结图示
假设我们删除节点 50：

原始状态：

      (50) <-- N
     /    \
   (30)   (70)
         /   \
       (60)  (80) <-- S (后继节点,指的是60)
Step 1 & 2：替换值
S=60。用 60 替换 50 的值。

      (60) <-- N (值被 S 覆盖)
     /    \
   (30)   (70)
         /   \
       (60)  (80) <-- S (现在是冗余的,指的是60)
Step 3：删除 S（递归调用）
递归删除右子树中的 60，60 只有右子节点（80）。删除操作将 80 返回给 70 的左指针。

最终状态：

      (60) <-- 最终的 LCA
     /    \
   (30)   (70)
             \
             (80)
通过这种方法，BST 的有序性得以完美保持
*/
// 669.修剪二叉搜索树
TreeNode* trimBST(TreeNode* root, int low, int high) {
    // 基线条件：如果当前节点为空，直接返回空
    if (root == nullptr) {
        return nullptr;
    }
     // 情况 1: 节点值大于 high (需要删除 root 及其右子树)
    if (root->val > high) {
        // LCA 必然在左子树。直接返回对左子树的修剪结果。
        // 原来的 root 和右子树都被丢弃。
        return trimBST(root->left, low, high);
    }
    // 情况 2: 节点值小于 low (需要删除 root 及其左子树)
    if (root->val < low) {
        // LCA 必然在右子树。直接返回对右子树的修剪结果。
        // 原来的 root 和左子树都被丢弃。
        return trimBST(root->right, low, high);
    }
    // 情况 3: 节点值在 [low, high] 范围内 (保留 root)
    // 递归修剪左右子树，并将返回的新根连接到 root 上

    // 保留 root
    // 递归修剪 root 的左子树，将返回的新根连接到 root->left
    // 递归修剪 root 的右子树，将返回的新根连接到 root->right
    // 返回 root 作为当前子树的新根
    root->left = trimBST(root->left, low, high);
    root->right = trimBST(root->right, low, high);

    return root;
}
// 108.将有序数组转换为二叉搜索树
/**
 * @brief 辅助递归函数，用于构建BST
 * @param nums 升序数组
 * @param left 当前子数组的起始索引
 * @param right 当前子数组的结束索引
 * @return 构建好的子树的根节点
 */
TreeNode* buildBST(std::vector<int>& nums, int left, int right) {
    // 1. 递归终止条件
    if (left > right) {
        return nullptr;
    }
    // 2. 找到中间元素作为根节点
    int mid = left + (right - left) / 2;
    // 3. 创建根节点
    TreeNode* root = new TreeNode(nums[mid]);
    // 4. 递归构建左右子树
    // 左子树的元素范围是 [left, mid - 1]
    root->left = buildBST(nums, left, mid - 1);
    // 右子树的元素范围是 [mid + 1, right]
    root->right = buildBST(nums, mid + 1, right);
    // 5. 返回根节点
    return root;
}

/**
 * @brief 将有序数组转换为高度平衡的二叉搜索树。
 * * @param nums 升序排列的整数数组。
 * @return 转换后的二叉搜索树的根节点指针。
 */
// 核心思想：中序遍历的逆过程，找到中间元素，作为根节点，然后递归处理左右子树
TreeNode* sortedArrayToBST(std::vector<int>& nums) {
    if (nums.empty()) {
        return nullptr;
    }
    return buildBST(nums, 0, nums.size() - 1);
}

// 538.把二叉搜索树转换为累加树
int sum = 0; // 用于存储已经访问过的更大节点值的累加和
// 反向中序遍历（右 中 左），这实际会得到一个降序序列
void traverse(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    // 1. 递归右子树 (Right)
    // 右子树所有节点的值都大于当前节点，所以应该先处理
    traverse(root->right);

    // 2. 处理当前节点 (Middle)
    // 节点的累加新值 = 节点原值 + 已经累计的更大值的和 (sum)
    int original_val = root->val;
    root->val = root->val + sum;
    // 更新累加和，将当前节点的原值也加入到 sum 中
    sum += original_val;
    // 3. 递归左子树 (Left)
    // 左子树所有节点的值都小于当前节点，在它们处理时，sum 已经包含了当前节点和所有右子树的值
    traverse(root->left);
}
/**
 * @brief 将二叉搜索树转换为累加树（Greater Sum Tree）。
 * @param root 原二叉搜索树的根节点。
 * @return 转换后的累加树的根节点。
 */
TreeNode* convertBST(TreeNode* root) {
    sum = 0;
    traverse(root);
    return root;
}



















// 层序遍历系列
// [199.二叉树的右视图](https://leetcode.cn/problems/binary-tree-right-side-view/)
// [637.二叉树的层平均值](https://leetcode.cn/problems/average-of-levels-in-binary-tree/)
// [429.N叉树的层序遍历](https://leetcode.cn/problems/n-ary-tree-level-order-traversal/)
// [515.在每个树行中找最大值](https://leetcode.cn/problems/find-largest-value-in-each-tree-row/)
// [116.填充每个节点的下一个右侧节点指针](https://leetcode.cn/problems/populating-next-right-pointers-in-each-node/)
// [117.填充每个节点的下一个右侧节点指针II](https://leetcode.cn/problems/populating-next-right-pointers-in-each-node-ii/)
// [104.二叉树的最大深度](https://leetcode.cn/problems/maximum-depth-of-binary-tree/)

