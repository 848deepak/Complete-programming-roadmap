// ============================================================
// DSA | Java → Trees: Binary Tree, BST, Traversals, Balance
// ============================================================
// DESCRIPTION:
//   - Binary Tree: all traversals (in/pre/post/level-order)
//   - Binary Search Tree: insert, search, delete, validate
//   - Tree properties: height, diameter, balanced check
//   - Level order, zigzag, left/right view
//   - Lowest Common Ancestor (LCA)
//
// COMPILE & RUN:
//   javac Trees.java && java Trees
// ============================================================

import java.util.*;

public class Trees {

    // ============================================================
    // TREE NODE
    // ============================================================
    static class TreeNode {
        int val;
        TreeNode left, right;

        TreeNode(int v) {
            val = v;
        }
    }

    // Build binary tree from level-order array (-1 = null)
    static TreeNode build(int[] vals) {
        if (vals == null || vals.length == 0 || vals[0] == -1)
            return null;
        TreeNode root = new TreeNode(vals[0]);
        Queue<TreeNode> q = new LinkedList<>();
        q.offer(root);
        int i = 1;
        while (!q.isEmpty() && i < vals.length) {
            TreeNode node = q.poll();
            if (i < vals.length && vals[i] != -1) {
                node.left = new TreeNode(vals[i]);
                q.offer(node.left);
            }
            i++;
            if (i < vals.length && vals[i] != -1) {
                node.right = new TreeNode(vals[i]);
                q.offer(node.right);
            }
            i++;
        }
        return root;
    }

    // ============================================================
    // SECTION 1: TRAVERSALS
    // ============================================================

    // Inorder: Left → Root → Right (gives sorted order for BST)
    static List<Integer> inorder(TreeNode root) {
        List<Integer> res = new ArrayList<>();
        inorderHelper(root, res);
        return res;
    }

    static void inorderHelper(TreeNode node, List<Integer> res) {
        if (node == null)
            return;
        inorderHelper(node.left, res);
        res.add(node.val);
        inorderHelper(node.right, res);
    }

    // Preorder: Root → Left → Right
    static List<Integer> preorder(TreeNode root) {
        List<Integer> res = new ArrayList<>();
        preorderHelper(root, res);
        return res;
    }

    static void preorderHelper(TreeNode node, List<Integer> res) {
        if (node == null)
            return;
        res.add(node.val);
        preorderHelper(node.left, res);
        preorderHelper(node.right, res);
    }

    // Iterative inorder using Stack — O(n) time, O(h) space
    static List<Integer> inorderIterative(TreeNode root) {
        List<Integer> res = new ArrayList<>();
        Deque<TreeNode> stk = new ArrayDeque<>();
        TreeNode curr = root;
        while (curr != null || !stk.isEmpty()) {
            while (curr != null) {
                stk.push(curr);
                curr = curr.left;
            }
            curr = stk.pop();
            res.add(curr.val);
            curr = curr.right;
        }
        return res;
    }

    // Level-order by levels: BFS
    static List<List<Integer>> levelOrder(TreeNode root) {
        List<List<Integer>> res = new ArrayList<>();
        if (root == null)
            return res;
        Queue<TreeNode> q = new LinkedList<>();
        q.offer(root);
        while (!q.isEmpty()) {
            int n = q.size();
            List<Integer> level = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                TreeNode node = q.poll();
                level.add(node.val);
                if (node.left != null)
                    q.offer(node.left);
                if (node.right != null)
                    q.offer(node.right);
            }
            res.add(level);
        }
        return res;
    }

    // Zigzag level order
    static List<List<Integer>> zigzag(TreeNode root) {
        List<List<Integer>> res = new ArrayList<>();
        if (root == null)
            return res;
        Queue<TreeNode> q = new LinkedList<>();
        q.offer(root);
        boolean ltr = true;
        while (!q.isEmpty()) {
            int n = q.size();
            Integer[] level = new Integer[n];
            for (int i = 0; i < n; i++) {
                TreeNode node = q.poll();
                level[ltr ? i : n - 1 - i] = node.val;
                if (node.left != null)
                    q.offer(node.left);
                if (node.right != null)
                    q.offer(node.right);
            }
            res.add(Arrays.asList(level));
            ltr = !ltr;
        }
        return res;
    }

    // Right view
    static List<Integer> rightView(TreeNode root) {
        List<Integer> res = new ArrayList<>();
        Queue<TreeNode> q = new LinkedList<>();
        if (root == null)
            return res;
        q.offer(root);
        while (!q.isEmpty()) {
            int n = q.size();
            for (int i = 0; i < n; i++) {
                TreeNode node = q.poll();
                if (i == n - 1)
                    res.add(node.val);
                if (node.left != null)
                    q.offer(node.left);
                if (node.right != null)
                    q.offer(node.right);
            }
        }
        return res;
    }

    // ============================================================
    // SECTION 2: TREE PROPERTIES
    // ============================================================

    static int height(TreeNode root) {
        if (root == null)
            return 0;
        return 1 + Math.max(height(root.left), height(root.right));
    }

    // Diameter: longest path (may not pass through root)
    static int diameter;

    static int diameterHelper(TreeNode node) {
        if (node == null)
            return 0;
        int l = diameterHelper(node.left), r = diameterHelper(node.right);
        diameter = Math.max(diameter, l + r);
        return 1 + Math.max(l, r);
    }

    static int diameter(TreeNode root) {
        diameter = 0;
        diameterHelper(root);
        return diameter;
    }

    // Check balanced: returns -1 if unbalanced, else height
    static int checkBalanced(TreeNode node) {
        if (node == null)
            return 0;
        int l = checkBalanced(node.left);
        if (l == -1)
            return -1;
        int r = checkBalanced(node.right);
        if (r == -1)
            return -1;
        if (Math.abs(l - r) > 1)
            return -1;
        return 1 + Math.max(l, r);
    }

    static boolean isBalanced(TreeNode root) {
        return checkBalanced(root) != -1;
    }

    // Max path sum
    static int maxPathSum;

    static int pathSumHelper(TreeNode node) {
        if (node == null)
            return 0;
        int l = Math.max(0, pathSumHelper(node.left));
        int r = Math.max(0, pathSumHelper(node.right));
        maxPathSum = Math.max(maxPathSum, node.val + l + r);
        return node.val + Math.max(l, r);
    }

    static int maxPathSum(TreeNode root) {
        maxPathSum = Integer.MIN_VALUE;
        pathSumHelper(root);
        return maxPathSum;
    }

    // ============================================================
    // SECTION 3: BINARY SEARCH TREE
    // ============================================================

    static TreeNode bstInsert(TreeNode root, int val) {
        if (root == null)
            return new TreeNode(val);
        if (val < root.val)
            root.left = bstInsert(root.left, val);
        else
            root.right = bstInsert(root.right, val);
        return root;
    }

    static boolean bstSearch(TreeNode root, int val) {
        if (root == null)
            return false;
        if (val == root.val)
            return true;
        return val < root.val ? bstSearch(root.left, val) : bstSearch(root.right, val);
    }

    // Validate BST: inorder must be strictly increasing
    static boolean validateBST(TreeNode root) {
        long prev = Long.MIN_VALUE;
        Deque<TreeNode> stk = new ArrayDeque<>();
        TreeNode curr = root;
        while (curr != null || !stk.isEmpty()) {
            while (curr != null) {
                stk.push(curr);
                curr = curr.left;
            }
            curr = stk.pop();
            if (curr.val <= prev)
                return false;
            prev = curr.val;
            curr = curr.right;
        }
        return true;
    }

    // LCA: Lowest Common Ancestor of two nodes in BST
    static TreeNode lcaBST(TreeNode root, int p, int q) {
        while (root != null) {
            if (p < root.val && q < root.val)
                root = root.left;
            else if (p > root.val && q > root.val)
                root = root.right;
            else
                return root;
        }
        return null;
    }

    // LCA for any Binary Tree (not necessarily BST)
    static TreeNode lcaTree(TreeNode root, int p, int q) {
        if (root == null || root.val == p || root.val == q)
            return root;
        TreeNode l = lcaTree(root.left, p, q);
        TreeNode r = lcaTree(root.right, p, q);
        return (l != null && r != null) ? root : (l != null ? l : r);
    }

    // ============================================================
    // MAIN
    // ============================================================
    public static void main(String[] args) {
        // 1
        // / \
        // 2 3
        // / \ \
        // 4 5 6
        TreeNode root = build(new int[] { 1, 2, 3, 4, 5, -1, 6 });

        System.out.println("=== TRAVERSALS ===");
        System.out.println("  Inorder (recursive): " + inorder(root));
        System.out.println("  Inorder (iterative): " + inorderIterative(root));
        System.out.println("  Preorder:            " + preorder(root));
        System.out.println("  Level order:         " + levelOrder(root));
        System.out.println("  Zigzag:              " + zigzag(root));
        System.out.println("  Right view:          " + rightView(root));

        System.out.println("\n=== TREE PROPERTIES ===");
        System.out.println("  Height:   " + height(root));
        System.out.println("  Diameter: " + diameter(root));
        System.out.println("  Balanced: " + isBalanced(root));
        System.out.println("  Max path sum: " + maxPathSum(build(new int[] { -10, 9, 20, -1, -1, 15, 7 })));

        System.out.println("\n=== BINARY SEARCH TREE ===");
        TreeNode bst = null;
        for (int v : new int[] { 5, 3, 7, 1, 4, 6, 8 })
            bst = bstInsert(bst, v);
        System.out.println("  BST inorder: " + inorder(bst)); // [1,3,4,5,6,7,8]
        System.out.println("  search(4): " + bstSearch(bst, 4));
        System.out.println("  search(9): " + bstSearch(bst, 9));
        System.out.println("  valid BST: " + validateBST(bst));

        TreeNode notBST = build(new int[] { 5, 1, 4, 0, 0, 3, 6 });
        System.out.println("  [5,1,4,3,6] valid BST: " + validateBST(notBST));

        System.out.println("  LCA BST(1,4): " + lcaBST(bst, 1, 4).val); // 3
        System.out.println("  LCA BST(6,8): " + lcaBST(bst, 6, 8).val); // 7
        System.out.println("  LCA tree(4,5): " + lcaTree(root, 4, 5).val); // 2
        System.out.println("  LCA tree(4,6): " + lcaTree(root, 4, 6).val); // 1
    }
}
