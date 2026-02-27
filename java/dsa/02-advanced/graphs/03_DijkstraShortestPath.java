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

class DijkstraShortestPath {
    static class Edge {
        int to;
        int weight;

        Edge(int to, int weight) {
            this.to = to;
            this.weight = weight;
        }
    }

    static int[] dijkstra(int start, List<List<Edge>> graph) {
        int n = graph.size();
        int[] distance = new int[n];
        Arrays.fill(distance, Integer.MAX_VALUE);
        distance[start] = 0;

        PriorityQueue<int[]> minHeap = new PriorityQueue<>(Comparator.comparingInt(a -> a[0]));
        minHeap.offer(new int[]{0, start});

        while (!minHeap.isEmpty()) {
            int[] current = minHeap.poll();
            int currentDistance = current[0];
            int node = current[1];

            if (currentDistance > distance[node]) continue;

            for (Edge edge : graph.get(node)) {
                int next = edge.to;
                int newDistance = distance[node] + edge.weight;
                if (newDistance < distance[next]) {
                    distance[next] = newDistance;
                    minHeap.offer(new int[]{newDistance, next});
                }
            }
        }
        return distance;
    }

    public static void main(String[] args) {
        List<List<Edge>> graph = new ArrayList<>();
        for (int i = 0; i < 5; i++) graph.add(new ArrayList<>());

        graph.get(0).add(new Edge(1, 2));
        graph.get(0).add(new Edge(2, 4));
        graph.get(1).add(new Edge(2, 1));
        graph.get(1).add(new Edge(3, 7));
        graph.get(2).add(new Edge(4, 3));
        graph.get(3).add(new Edge(4, 1));

        int[] distance = dijkstra(0, graph);
        System.out.println("Shortest distance from node 0 to node 4: " + distance[4]);
    }
}

/*
Sample Output:
Shortest distance from node 0 to node 4: 6
*/
