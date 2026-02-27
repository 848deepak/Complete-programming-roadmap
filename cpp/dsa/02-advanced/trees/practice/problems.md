# 🌳 Trees — Practice Problems

> **Topic:** Binary Trees, BST | **Level:** Easy → Hard

---

| # | Problem | Difficulty | Pattern |
|---|---------|-----------|---------|
| 1 | [Level Order Traversal](#1-level-order) | 🟢 Easy | BFS |
| 2 | [Max Depth of Binary Tree](#2-max-depth) | 🟢 Easy | DFS |
| 3 | [Check if BST](#3-validate-bst) | 🟢 Easy | Inorder / Range |
| 4 | [Symmetric Tree](#4-symmetric-tree) | 🟢 Easy | Mirror DFS |
| 5 | [Invert Binary Tree](#5-invert-tree) | 🟢 Easy | DFS |
| 6 | [Lowest Common Ancestor](#6-lca) | 🟡 Medium | Recursive DFS |
| 7 | [Diameter of Binary Tree](#7-diameter) | 🟡 Medium | DFS + Height |
| 8 | [Zigzag Level Order Traversal](#8-zigzag) | 🟡 Medium | BFS + Flag |
| 9 | [Construct Tree from Inorder+Preorder](#9-construct-tree) | 🟡 Medium | Divide & Conquer |
| 10 | [Kth Smallest in BST](#10-kth-smallest) | 🟡 Medium | Inorder Traversal |
| 11 | [Serialize & Deserialize Binary Tree](#11-serialize) | 🔴 Hard | BFS/DFS |
| 12 | [Max Path Sum](#12-max-path-sum) | 🔴 Hard | DFS + Global Max |
| 13 | [Vertical Order Traversal](#13-vertical-order) | 🔴 Hard | BFS + Column Map |

---

## Node Structure
```cpp
struct TreeNode { int val; TreeNode *left, *right; TreeNode(int x):val(x),left(nullptr),right(nullptr){} };
```
```java
class TreeNode { int val; TreeNode left, right; TreeNode(int x){val=x;} }
```

---

## 🟢 EASY PROBLEMS

### 1. Level Order Traversal
```cpp
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> res; if (!root) return res;
    queue<TreeNode*> q; q.push(root);
    while (!q.empty()) {
        int sz = q.size(); vector<int> level;
        while (sz--) { auto n=q.front();q.pop(); level.push_back(n->val); if(n->left)q.push(n->left); if(n->right)q.push(n->right); }
        res.push_back(level);
    }
    return res;
}
```
```java
public static List<List<Integer>> levelOrder(TreeNode root) {
    List<List<Integer>> res = new ArrayList<>(); if (root==null) return res;
    Queue<TreeNode> q = new LinkedList<>(); q.add(root);
    while (!q.isEmpty()) {
        int sz=q.size(); List<Integer> level=new ArrayList<>();
        while(sz-->0){TreeNode n=q.poll();level.add(n.val);if(n.left!=null)q.add(n.left);if(n.right!=null)q.add(n.right);}
        res.add(level);
    }
    return res;
}
```
**O(n) time, O(n) space.**

---

### 2. Max Depth of Binary Tree
```cpp
int maxDepth(TreeNode* root) { return root ? 1+max(maxDepth(root->left),maxDepth(root->right)) : 0; }
```
```java
public static int maxDepth(TreeNode root) { return root==null?0:1+Math.max(maxDepth(root.left),maxDepth(root.right)); }
```

---

### 3. Validate BST
**Approach:** Pass min/max range. Each node must be within (min, max).

```cpp
bool isValid(TreeNode* n, long lo, long hi) {
    if (!n) return true;
    if (n->val<=lo || n->val>=hi) return false;
    return isValid(n->left,lo,n->val) && isValid(n->right,n->val,hi);
}
bool isValidBST(TreeNode* root) { return isValid(root,LONG_MIN,LONG_MAX); }
```
```java
static boolean isValid(TreeNode n, long lo, long hi) {
    if(n==null) return true;
    if(n.val<=lo||n.val>=hi) return false;
    return isValid(n.left,lo,n.val)&&isValid(n.right,n.val,hi);
}
```

---

### 4. Symmetric Tree
```cpp
bool isMirror(TreeNode* a, TreeNode* b) {
    if (!a&&!b) return true; if (!a||!b) return false;
    return a->val==b->val && isMirror(a->left,b->right) && isMirror(a->right,b->left);
}
bool isSymmetric(TreeNode* root) { return !root || isMirror(root->left,root->right); }
```
```java
static boolean isMirror(TreeNode a, TreeNode b) {
    if(a==null&&b==null)return true; if(a==null||b==null)return false;
    return a.val==b.val&&isMirror(a.left,b.right)&&isMirror(a.right,b.left);
}
```

---

### 5. Invert Binary Tree
```cpp
TreeNode* invertTree(TreeNode* root) {
    if (!root) return nullptr;
    swap(root->left, root->right);
    invertTree(root->left); invertTree(root->right);
    return root;
}
```
```java
public static TreeNode invertTree(TreeNode root) {
    if(root==null)return null;
    TreeNode t=root.left; root.left=root.right; root.right=t;
    invertTree(root.left); invertTree(root.right);
    return root;
}
```

---

## 🟡 MEDIUM PROBLEMS

### 6. Lowest Common Ancestor
**Problem:** Find LCA of two nodes p and q in a binary tree.

```cpp
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || root==p || root==q) return root;
    TreeNode* L = lowestCommonAncestor(root->left,p,q);
    TreeNode* R = lowestCommonAncestor(root->right,p,q);
    if (L && R) return root;  // p and q in different subtrees
    return L ? L : R;
}
```
```java
public static TreeNode lca(TreeNode root, TreeNode p, TreeNode q) {
    if(root==null||root==p||root==q) return root;
    TreeNode L=lca(root.left,p,q), R=lca(root.right,p,q);
    return (L!=null&&R!=null)?root:(L!=null?L:R);
}
```
**O(n) time.**

---

### 7. Diameter of Binary Tree
**Problem:** Longest path between any two nodes (number of edges).
**Approach:** At each node, diameter through it = leftHeight + rightHeight. Track global max.

```cpp
int diameterHelper(TreeNode* root, int& maxDia) {
    if (!root) return 0;
    int L = diameterHelper(root->left, maxDia);
    int R = diameterHelper(root->right, maxDia);
    maxDia = max(maxDia, L+R);
    return 1+max(L,R);
}
int diameterOfBinaryTree(TreeNode* root) { int d=0; diameterHelper(root,d); return d; }
```
```java
static int maxDia;
static int height(TreeNode root) {
    if(root==null) return 0;
    int L=height(root.left), R=height(root.right);
    maxDia=Math.max(maxDia,L+R); return 1+Math.max(L,R);
}
public static int diameter(TreeNode root) { maxDia=0; height(root); return maxDia; }
```

---

### 8. Zigzag Level Order
**Problem:** Level order but alternate left-to-right and right-to-left.

```cpp
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> res; if (!root) return res;
    queue<TreeNode*> q; q.push(root); bool leftToRight = true;
    while (!q.empty()) {
        int sz = q.size(); vector<int> level(sz);
        for (int i=0;i<sz;i++) {
            auto n=q.front();q.pop();
            int idx = leftToRight ? i : sz-1-i;
            level[idx] = n->val;
            if(n->left) q.push(n->left); if(n->right) q.push(n->right);
        }
        res.push_back(level); leftToRight = !leftToRight;
    }
    return res;
}
```

---

### 9. Construct Tree from Inorder + Preorder
**Approach:** First element of preorder is root. Find it in inorder to split left/right subtrees.

```cpp
TreeNode* build(vector<int>& pre, int& idx, vector<int>& in, int lo, int hi, unordered_map<int,int>& inMap) {
    if (lo>hi) return nullptr;
    TreeNode* root = new TreeNode(pre[idx++]);
    int mid = inMap[root->val];
    root->left = build(pre,idx,in,lo,mid-1,inMap);
    root->right = build(pre,idx,in,mid+1,hi,inMap);
    return root;
}
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    unordered_map<int,int> inMap;
    for (int i=0;i<(int)inorder.size();i++) inMap[inorder[i]]=i;
    int idx=0; return build(preorder,idx,inorder,0,inorder.size()-1,inMap);
}
```
**O(n) time with hash map.**

---

### 10. Kth Smallest in BST
**Approach:** Inorder traversal gives sorted order. Return kth element.

```cpp
int kthSmallest(TreeNode* root, int k) {
    stack<TreeNode*> st; TreeNode* curr = root;
    while (curr || !st.empty()) {
        while (curr) { st.push(curr); curr=curr->left; }
        curr = st.top(); st.pop();
        if (--k == 0) return curr->val;
        curr = curr->right;
    }
    return -1;
}
```
```java
public static int kthSmallest(TreeNode root, int k) {
    Deque<TreeNode> st = new ArrayDeque<>(); TreeNode curr=root;
    while(curr!=null||!st.isEmpty()){
        while(curr!=null){st.push(curr);curr=curr.left;}
        curr=st.pop(); if(--k==0) return curr.val; curr=curr.right;
    }
    return -1;
}
```

---

## 🔴 HARD PROBLEMS

### 11. Serialize & Deserialize Binary Tree
**Problem:** Convert tree to string and back.
**Approach:** Preorder with null markers.

```cpp
string serialize(TreeNode* root) {
    if (!root) return "#";
    return to_string(root->val)+","+serialize(root->left)+","+serialize(root->right);
}
TreeNode* deserializeHelper(queue<string>& q) {
    string s = q.front(); q.pop();
    if (s=="#") return nullptr;
    TreeNode* n = new TreeNode(stoi(s));
    n->left = deserializeHelper(q); n->right = deserializeHelper(q);
    return n;
}
TreeNode* deserialize(string data) {
    queue<string> q; stringstream ss(data); string item;
    while (getline(ss,item,',')) q.push(item);
    return deserializeHelper(q);
}
```

---

### 12. Max Path Sum
**Problem:** Find max sum path (any node to any node, not necessarily through root).
**Approach:** DFS. At each node, max contribution = node.val + max(left, right, 0). Update global with node + left + right.

```cpp
int maxPathSumHelper(TreeNode* root, int& globalMax) {
    if (!root) return 0;
    int L = max(0, maxPathSumHelper(root->left, globalMax));
    int R = max(0, maxPathSumHelper(root->right, globalMax));
    globalMax = max(globalMax, root->val + L + R);
    return root->val + max(L, R);
}
int maxPathSum(TreeNode* root) { int g=INT_MIN; maxPathSumHelper(root,g); return g; }
```
```java
static int globalMax;
static int helper(TreeNode root) {
    if(root==null)return 0;
    int L=Math.max(0,helper(root.left)), R=Math.max(0,helper(root.right));
    globalMax=Math.max(globalMax,root.val+L+R);
    return root.val+Math.max(L,R);
}
public static int maxPathSum(TreeNode root) { globalMax=Integer.MIN_VALUE; helper(root); return globalMax; }
```
**O(n).**

---

### 13. Vertical Order Traversal
**Problem:** Group nodes by vertical column. Nodes at same position sorted by value.
**Approach:** BFS with column tracking. Use TreeMap for sorted columns.

```cpp
vector<vector<int>> verticalTraversal(TreeNode* root) {
    map<int, vector<pair<int,int>>> cols; // col → [(row, val)]
    queue<tuple<TreeNode*,int,int>> q; q.push({root,0,0});
    while (!q.empty()) {
        auto [node,row,col]=q.front(); q.pop();
        cols[col].push_back({row, node->val});
        if (node->left) q.push({node->left,row+1,col-1});
        if (node->right) q.push({node->right,row+1,col+1});
    }
    vector<vector<int>> res;
    for (auto& [c, entries] : cols) {
        sort(entries.begin(), entries.end());
        vector<int> column;
        for (auto& [r,v] : entries) column.push_back(v);
        res.push_back(column);
    }
    return res;
}
```
**O(n log n).**

---

## 🗺️ Pattern Summary

| Pattern | Problems |
|---------|----------|
| BFS Level Order | Level Order, Zigzag, Vertical |
| DFS + Height | Max Depth, Diameter, Max Path Sum |
| Range Validation | Validate BST |
| Mirror DFS | Symmetric Tree |
| Divide & Conquer | Construct Tree |
| Inorder Traversal | Kth Smallest in BST |
| Serialization | Serialize/Deserialize |
