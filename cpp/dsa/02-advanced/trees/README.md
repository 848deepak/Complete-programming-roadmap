# C++ Data Structures & Algorithms: Trees

> **Folder:** `cpp/dsa/02-advanced/trees/` | **Level:** Advanced  
> **Files:** `01_binary_tree_traversal.cpp` · `02_bst_insert_search.cpp` · `03_tree_height.cpp` · `04_tree_extras.cpp`

---

## 1. Introduction

A Tree is a non-linear, hierarchical data structure composed of nodes connected by edges. The topmost node is the **root**, and nodes with no children are **leaves**. Trees are crucial for representing hierarchical data (file systems, HTML DOM), optimizing search operations, and parsing expressions.

> **Compile any file:**
> ```bash
> g++ -std=c++17 <filename>.cpp -o out && ./out
> ```

---

## 2. Types of Trees Covered

### 2.1 Binary Tree (`01` to `04`)
Each node has at most two children (left and right child).

### 2.2 Binary Search Tree (BST) (`02_bst_insert_search.cpp`)
A Binary Tree with strict ordering properties:
- The left subtree of a node contains only nodes with values **less than** the node's value.
- The right subtree of a node contains only nodes with values **greater than** the node's value.
- Both left and right subtrees must also be BSTs.
- **Advantage:** Allows for highly efficient searching, insertion, and deletion (O(log n) on average).

---

## 3. Core Algorithms

### 3.1 Tree Traversals (`01_binary_tree_traversal.cpp`)
Methods for visiting every node in the tree exactly once.
- **Pre-order (Root, Left, Right):** Used for creating a copy of a tree or prefix expression parsing.
- **In-order (Left, Root, Right):** In a BST, an in-order traversal yields the nodes in **sorted (ascending) order**.
- **Post-order (Left, Right, Root):** Used for deleting a tree (delete children before the parent) or postfix expression parsing.
- **Level-order (BFS):** Visits nodes level by level, left to right. Requires a **Queue**.

### 3.2 BST Operations (`02_bst_insert_search.cpp`)
- **Search:** Compare target with current node. If smaller, go left. If larger, go right. (O(log n) avg, O(n) worst if skewed).
- **Insert:** Traverse using search logic until a `nullptr` is hit, attach the new node there. (O(log n) avg).

### 3.3 Tree Metrics (`03_tree_height.cpp` & `04_tree_extras.cpp`)
- **Height / Max Depth:** The number of edges on the longest path from the root to a leaf. Computed recursively as `1 + max(height(left), height(right))`.
- **Size / Count:** Total number of nodes globally. Computed recursively as `1 + count(left) + count(right)`.
- **Diameter:** The length of the longest path between *any* two nodes in the tree. (Does not necessarily pass through the root).

---

## 4. Recursion vs. Iteration

Trees are inherently recursive structures.
- **Recursion:** Usually results in clean, localized code (DFS). The implicit call stack handles the state. Risk: Stack Overflow for enormously deep skewed trees.
- **Iteration:** Uses explicit auxiliary data structures:
  - **Stacks:** Used for iterative DFS (Pre/In/Post order).
  - **Queues:** Used for BFS (Level-order).

---

## 5. Time & Space Complexity

### Tree Operations
| Operation | BST (Average) | BST (Worst - Skewed) | Balanced BST (AVL/Red-Black) |
|-----------|---------------|-----------------------|------------------------------|
| Search | O(log n) | O(n) | O(log n) |
| Insert | O(log n) | O(n) | O(log n) |
| Delete | O(log n) | O(n) | O(log n) |

### Traversals / Algorithms
| Algorithm | Time complexity | Extra Space |
|-----------|------------------|-------------|
| DFS Traversals (Pre, In, Post) | O(n) | O(h) call stack (h = height) |
| BFS / Level-Order | O(n) | O(w) queue (w = max width) |
| Find Height/Diameter | O(n) | O(h) call stack |

---

## 6. Interview Relevance

Trees are highly visual. A key skill is translating tree diagrams into concise recursive functions.

| Problem Pattern | Classic Examples |
|-----------------|------------------|
| **Recursive DFS** | Maximum Depth, Invert Binary Tree, Symmetric Tree, Lowest Common Ancestor (LCA), Path Sum |
| **Level-Order BFS** | Binary Tree Level Order Traversal, Binary Tree Right Side View, Zigzag Level Traversal |
| **BST Properties** | Validate Binary Search Tree, Convert Sorted Array to BST, Kth Smallest Element in BST |
| **Advanced DFS** | Diameter of Binary Tree, Serialize and Deserialize Binary Tree |

---

> **Next Steps:** Proceed to `graphs/`. A Tree is simply a restricted, special type of Graph (a connected, acyclic undirected graph).
