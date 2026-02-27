/*
Topic: Data Structures and Algorithms
Learning Goal: Understand this concept with a runnable example.
Approach: Read main() first, then helper function(s), then modify sample input.
Time Complexity: Analyze the core operation in this file while practicing.
Space Complexity: Check recursion/auxiliary data structure usage.
How to Run: Compile and run this file; verify output shown in terminal.
Practice Task: Change inputs and test at least 3 edge cases.
*/

import java.util.*;

class GraphDFS {
    static void dfs(int node, List<List<Integer>> graph, boolean[] visited) {
        visited[node] = true;
        System.out.print(node + " ");

        for (int neighbor : graph.get(node)) {
            if (!visited[neighbor]) dfs(neighbor, graph, visited);
        }
    }

    public static void main(String[] args) {
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < 6; i++) graph.add(new ArrayList<>());

        graph.get(0).addAll(Arrays.asList(1, 2));
        graph.get(1).addAll(Arrays.asList(0, 3, 4));
        graph.get(2).addAll(Arrays.asList(0, 5));
        graph.get(3).add(1);
        graph.get(4).add(1);
        graph.get(5).add(2);

        boolean[] visited = new boolean[graph.size()];
        System.out.print("DFS from node 0: ");
        dfs(0, graph, visited);
        System.out.println();
    }
}

/*
Sample Output:
DFS from node 0: 0 1 3 4 2 5
*/
