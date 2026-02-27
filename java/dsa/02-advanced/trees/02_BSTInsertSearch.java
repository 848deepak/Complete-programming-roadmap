/*
Topic: Data Structures and Algorithms
Learning Goal: Understand this concept with a runnable example.
Approach: Read main() first, then helper function(s), then modify sample input.
Time Complexity: Analyze the core operation in this file while practicing.
Space Complexity: Check recursion/auxiliary data structure usage.
How to Run: Compile and run this file; verify output shown in terminal.
Practice Task: Change inputs and test at least 3 edge cases.
*/

class BSTInsertSearch {
    static class Node {
        int data;
        Node left;
        Node right;

        Node(int data) {
            this.data = data;
        }
    }

    static Node insert(Node root, int value) {
        if (root == null) return new Node(value);
        if (value < root.data) root.left = insert(root.left, value);
        else root.right = insert(root.right, value);
        return root;
    }

    static boolean search(Node root, int target) {
        if (root == null) return false;
        if (root.data == target) return true;
        if (target < root.data) return search(root.left, target);
        return search(root.right, target);
    }

    public static void main(String[] args) {
        Node root = null;
        int[] values = {50, 30, 70, 20, 40, 60, 80};
        for (int value : values) root = insert(root, value);

        int target = 60;
        System.out.println("Search " + target + ": " + (search(root, target) ? "Found" : "Not Found"));
    }
}

/*
Sample Output:
Search 60: Found
*/
