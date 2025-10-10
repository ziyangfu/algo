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

