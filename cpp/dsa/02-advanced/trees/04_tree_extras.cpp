// ============================================================
// DSA | C++ → Trees: Level Order, Diameter, Balanced Check
// ============================================================
// DESCRIPTION:
//   Additional tree operations:
//   - Level Order Traversal (BFS on tree)
//   - Diameter of Binary Tree
//   - Check if Binary Tree is Balanced
//   - Left/Right View of Binary Tree
//   - Zigzag (Spiral) Level Order
//
// COMPILE & RUN:
//   g++ -std=c++17 04_tree_extras.cpp -o out && ./out
// ============================================================

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// ============================================================
// NODE STRUCTURE
// ============================================================

struct TreeNode {
    int       val;
    TreeNode* left;
    TreeNode* right;
    explicit TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

// ============================================================
// HELPER: Build tree from vector (level-order, -1 = null)
// ============================================================
TreeNode* buildTree(const vector<int>& vals) {
    if (vals.empty() || vals[0] == -1) return nullptr;
    TreeNode* root = new TreeNode(vals[0]);
    queue<TreeNode*> q;
    q.push(root);
    int i = 1;
    while (!q.empty() && i < (int)vals.size()) {
        TreeNode* node = q.front(); q.pop();
        if (i < (int)vals.size() && vals[i] != -1) {
            node->left = new TreeNode(vals[i]);
            q.push(node->left);
        }
        i++;
        if (i < (int)vals.size() && vals[i] != -1) {
            node->right = new TreeNode(vals[i]);
            q.push(node->right);
        }
        i++;
    }
    return root;
}

// ============================================================
// SECTION 1: LEVEL ORDER TRAVERSAL (BFS)
// ============================================================
// Use a queue. Process one level at a time.
// Return elements level by level as a 2D vector.
//
// Time: O(n)  |  Space: O(w) where w = max width of tree
// ------------------------------------------------------------ 

/**
 * Returns elements of tree grouped by level.
 * [ [root], [level1 left, level1 right], ... ]
 */
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = (int)q.size();   // how many nodes are in current level
        vector<int> level;

        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = q.front(); q.pop();
            level.push_back(node->val);

            if (node->left)  q.push(node->left);    // enqueue children for next level
            if (node->right) q.push(node->right);
        }

        result.push_back(level);
    }

    return result;
}

// ============================================================
// SECTION 2: ZIGZAG (SPIRAL) LEVEL ORDER
// ============================================================
// Like level order but alternate direction per level.
// Left-to-right on even levels, right-to-left on odd levels.
//
// Time: O(n)  |  Space: O(w)
// ------------------------------------------------------------ 

vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;

    queue<TreeNode*> q;
    q.push(root);
    bool leftToRight = true;

    while (!q.empty()) {
        int n = (int)q.size();
        vector<int> level(n);

        for (int i = 0; i < n; i++) {
            TreeNode* node = q.front(); q.pop();
            int idx = leftToRight ? i : n - 1 - i;   // direction determines index
            level[idx] = node->val;
            if (node->left)  q.push(node->left);
            if (node->right) q.push(node->right);
        }

        result.push_back(level);
        leftToRight = !leftToRight;   // flip direction
    }

    return result;
}

// ============================================================
// SECTION 3: LEFT VIEW & RIGHT VIEW
// ============================================================
// Left view  = first node at each level
// Right view = last node at each level
// ------------------------------------------------------------ 

vector<int> leftView(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int n = (int)q.size();
        for (int i = 0; i < n; i++) {
            TreeNode* node = q.front(); q.pop();
            if (i == 0) result.push_back(node->val);   // first node of level
            if (node->left)  q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
    return result;
}

vector<int> rightView(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int n = (int)q.size();
        for (int i = 0; i < n; i++) {
            TreeNode* node = q.front(); q.pop();
            if (i == n - 1) result.push_back(node->val);  // last node of level
            if (node->left)  q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
    return result;
}

// ============================================================
// SECTION 4: DIAMETER OF BINARY TREE
// ============================================================
// Diameter = longest path between any two nodes (may not pass root).
// For each node: candidate_diameter = height(left) + height(right)
// Use a single DFS that returns height and updates maxDiameter.
//
// Time: O(n)  |  Space: O(h) stack
// ------------------------------------------------------------ 

int diameterHelper(TreeNode* node, int& maxDiam) {
    if (!node) return 0;

    int leftH  = diameterHelper(node->left,  maxDiam);
    int rightH = diameterHelper(node->right, maxDiam);

    maxDiam = max(maxDiam, leftH + rightH);   // path through this node

    return 1 + max(leftH, rightH);   // height of this subtree
}

/**
 * Returns the diameter (longest path in number of edges) of the tree.
 */
int diameter(TreeNode* root) {
    int maxDiam = 0;
    diameterHelper(root, maxDiam);
    return maxDiam;
}

// ============================================================
// SECTION 5: BALANCED BINARY TREE CHECK
// ============================================================
// A balanced tree: for every node, |height(left) - height(right)| <= 1
// Naive: O(n²) if we recompute height at every node.
// Efficient: compute height bottom-up; return -1 for unbalanced.
//
// Time: O(n)  |  Space: O(h)
// ------------------------------------------------------------ 

/**
 * Returns height of subtree, or -1 if subtree is unbalanced.
 */
int checkBalanced(TreeNode* node) {
    if (!node) return 0;

    int leftH  = checkBalanced(node->left);
    if (leftH == -1) return -1;   // left subtree is already unbalanced

    int rightH = checkBalanced(node->right);
    if (rightH == -1) return -1;  // right subtree is already unbalanced

    if (abs(leftH - rightH) > 1) return -1;  // THIS node violates balance

    return 1 + max(leftH, rightH);
}

/**
 * Returns true if tree is height-balanced.
 */
bool isBalanced(TreeNode* root) {
    return checkBalanced(root) != -1;
}

// ============================================================
// SECTION 6: MAXIMUM PATH SUM
// ============================================================
// A path can start and end at any nodes. Find the path with max sum.
// For each node: candidate = node->val + max(0, leftGain) + max(0, rightGain)
//
// Time: O(n)  |  Space: O(h)
// ------------------------------------------------------------ 

int pathSumHelper(TreeNode* node, int& maxSum) {
    if (!node) return 0;

    int leftGain  = max(0, pathSumHelper(node->left,  maxSum));
    int rightGain = max(0, pathSumHelper(node->right, maxSum));

    maxSum = max(maxSum, node->val + leftGain + rightGain);

    return node->val + max(leftGain, rightGain);  // only one branch can be extended
}

int maxPathSum(TreeNode* root) {
    int maxSum = INT_MIN;
    pathSumHelper(root, maxSum);
    return maxSum;
}

// ============================================================
// HELPER: print 2D vector
// ============================================================
void print2D(const string& label, const vector<vector<int>>& vv) {
    cout << "  " << label << ": [";
    for (int i = 0; i < (int)vv.size(); i++) {
        cout << "[";
        for (int j = 0; j < (int)vv[i].size(); j++)
            cout << vv[i][j] << (j+1<(int)vv[i].size()?",":"");
        cout << "]" << (i+1<(int)vv.size()?",":"");
    }
    cout << "]\n";
}

void printV(const string& label, const vector<int>& v) {
    cout << "  " << label << ": [";
    for (int i = 0; i < (int)v.size(); i++) cout << v[i] << (i+1<(int)v.size()?",":"");
    cout << "]\n";
}

// ============================================================
// MAIN
// ============================================================
int main() {
    //     1
    //    / \
    //   2   3
    //  / \   \
    // 4   5   6
    TreeNode* root = buildTree({1, 2, 3, 4, 5, -1, 6});

    cout << "=== LEVEL ORDER TRAVERSAL ===" << "\n";
    print2D("Levels", levelOrder(root));   // [[1],[2,3],[4,5,6]]

    cout << "\n=== ZIGZAG LEVEL ORDER ===" << "\n";
    print2D("Zigzag", zigzagLevelOrder(root));  // [[1],[3,2],[4,5,6]]

    cout << "\n=== VIEWS ===" << "\n";
    printV("Left  view", leftView(root));     // [1,2,4]
    printV("Right view", rightView(root));    // [1,3,6]

    cout << "\n=== DIAMETER ===" << "\n";
    cout << "  Diameter of tree: " << diameter(root) << "\n";  // 4 (4-2-1-3-6)

    cout << "\n=== IS BALANCED ===" << "\n";
    cout << "  isBalanced: " << (isBalanced(root) ? "YES" : "NO") << "\n";  // YES

    // Unbalanced tree:
    //     1
    //    /
    //   2
    //  /
    // 3
    TreeNode* unbal = buildTree({1, 2, -1, 3});
    cout << "  unbalanced tree isBalanced: " << (isBalanced(unbal) ? "YES" : "NO") << "\n";  // NO

    cout << "\n=== MAX PATH SUM ===" << "\n";
    TreeNode* msTree = buildTree({-10, 9, 20, -1, -1, 15, 7});
    cout << "  maxPathSum (tree [-10,9,20,15,7]): " << maxPathSum(msTree) << "\n"; // 42

    return 0;
}

// ============================================================
// COMPLEXITY SUMMARY
//   levelOrder         : O(n) time, O(w) space — w=max level width
//   zigzagLevelOrder   : O(n) time, O(w) space
//   leftView/rightView : O(n) time, O(w) space
//   diameter           : O(n) time, O(h) space
//   isBalanced         : O(n) time, O(h) space
//   maxPathSum         : O(n) time, O(h) space
//   (h = tree height; balanced → h = O(log n))
// ============================================================
