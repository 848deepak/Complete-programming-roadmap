// ============================================================
// DSA | Java → Graphs: BFS, DFS, Shortest Path, Cycle Detection
// ============================================================
// DESCRIPTION:
//   Complete graph algorithms in Java:
//   - Graph representation (adjacency list)
//   - BFS: shortest path in unweighted graph
//   - DFS: connected components, topological sort
//   - Cycle detection (directed and undirected)
//   - Dijkstra's shortest path
//   - Union-Find for MST (Kruskal's)
//
// COMPILE & RUN:
//   javac Graphs.java && java Graphs
// ============================================================

import java.util.*;

public class Graphs {

    // ============================================================
    // GRAPH REPRESENTATION
    // ============================================================
    static class Graph {
        int V;
        List<List<Integer>> adj; // unweighted adjacency list
        List<List<int[]>> wAdj; // weighted: {neighbor, weight}

        Graph(int v) {
            V = v;
            adj = new ArrayList<>();
            wAdj = new ArrayList<>();
            for (int i = 0; i < V; i++) {
                adj.add(new ArrayList<>());
                wAdj.add(new ArrayList<>());
            }
        }

        void addEdge(int u, int v) {
            adj.get(u).add(v);
        }

        void addUndirectedEdge(int u, int v) {
            adj.get(u).add(v);
            adj.get(v).add(u);
        }

        void addWeightedEdge(int u, int v, int w) {
            wAdj.get(u).add(new int[] { v, w });
        }

        void addUndirectedWeightedEdge(int u, int v, int w) {
            wAdj.get(u).add(new int[] { v, w });
            wAdj.get(v).add(new int[] { u, w });
        }
    }

    // ============================================================
    // SECTION 1: BFS — Shortest Path (unweighted)
    // ============================================================
    // Time: O(V + E) | Space: O(V)

    static int[] bfs(Graph g, int src) {
        int[] dist = new int[g.V];
        Arrays.fill(dist, -1);
        dist[src] = 0;
        Queue<Integer> q = new LinkedList<>();
        q.offer(src);
        while (!q.isEmpty()) {
            int u = q.poll();
            for (int v : g.adj.get(u)) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.offer(v);
                }
            }
        }
        return dist; // dist[v] = shortest hops from src to v (-1 = unreachable)
    }

    static List<Integer> bfsPath(Graph g, int src, int dest) {
        int[] parent = new int[g.V];
        Arrays.fill(parent, -1);
        boolean[] visited = new boolean[g.V];
        visited[src] = true;
        Queue<Integer> q = new LinkedList<>();
        q.offer(src);
        while (!q.isEmpty()) {
            int u = q.poll();
            if (u == dest)
                break;
            for (int v : g.adj.get(u)) {
                if (!visited[v]) {
                    visited[v] = true;
                    parent[v] = u;
                    q.offer(v);
                }
            }
        }
        if (!visited[dest])
            return new ArrayList<>(); // no path
        List<Integer> path = new ArrayList<>();
        for (int v = dest; v != -1; v = parent[v])
            path.add(0, v);
        return path;
    }

    // ============================================================
    // SECTION 2: DFS — Connected Components
    // ============================================================

    static void dfs(Graph g, int u, boolean[] visited, List<Integer> component) {
        visited[u] = true;
        component.add(u);
        for (int v : g.adj.get(u))
            if (!visited[v])
                dfs(g, v, visited, component);
    }

    static List<List<Integer>> connectedComponents(Graph g) {
        boolean[] visited = new boolean[g.V];
        List<List<Integer>> result = new ArrayList<>();
        for (int i = 0; i < g.V; i++) {
            if (!visited[i]) {
                List<Integer> comp = new ArrayList<>();
                dfs(g, i, visited, comp);
                result.add(comp);
            }
        }
        return result;
    }

    // ============================================================
    // SECTION 3: CYCLE DETECTION
    // ============================================================

    // Undirected graph: DFS with parent tracking
    static boolean hasCycleUndirected(Graph g) {
        boolean[] visited = new boolean[g.V];
        for (int i = 0; i < g.V; i++) {
            if (!visited[i] && cycleCheckUndirected(g, i, -1, visited))
                return true;
        }
        return false;
    }

    static boolean cycleCheckUndirected(Graph g, int u, int parent, boolean[] visited) {
        visited[u] = true;
        for (int v : g.adj.get(u)) {
            if (!visited[v]) {
                if (cycleCheckUndirected(g, v, u, visited))
                    return true;
            } else if (v != parent)
                return true; // back edge to non-parent
        }
        return false;
    }

    // Directed graph: DFS with recursion stack (white-gray-black colouring)
    static boolean hasCycleDirected(Graph g) {
        int[] color = new int[g.V]; // 0=white, 1=gray, 2=black
        for (int i = 0; i < g.V; i++)
            if (color[i] == 0 && dfsDirected(g, i, color))
                return true;
        return false;
    }

    static boolean dfsDirected(Graph g, int u, int[] color) {
        color[u] = 1; // gray: currently in DFS
        for (int v : g.adj.get(u)) {
            if (color[v] == 1)
                return true; // back edge to ancestor → cycle!
            if (color[v] == 0 && dfsDirected(g, v, color))
                return true;
        }
        color[u] = 2; // black: done
        return false;
    }

    // ============================================================
    // SECTION 4: TOPOLOGICAL SORT (Kahn's BFS Algorithm)
    // ============================================================
    // Only valid for Directed Acyclic Graphs (DAGs).
    // Returns empty list if cycle exists.
    // Time: O(V + E)

    static List<Integer> topologicalSort(Graph g) {
        int[] inDegree = new int[g.V];
        for (int u = 0; u < g.V; u++)
            for (int v : g.adj.get(u))
                inDegree[v]++;

        Queue<Integer> q = new LinkedList<>();
        for (int i = 0; i < g.V; i++)
            if (inDegree[i] == 0)
                q.offer(i);

        List<Integer> order = new ArrayList<>();
        while (!q.isEmpty()) {
            int u = q.poll();
            order.add(u);
            for (int v : g.adj.get(u)) {
                if (--inDegree[v] == 0)
                    q.offer(v);
            }
        }

        return order.size() == g.V ? order : new ArrayList<>(); // empty if cycle
    }

    // ============================================================
    // SECTION 5: DIJKSTRA'S ALGORITHM (Java PriorityQueue)
    // ============================================================
    // Time: O((V+E) log V)

    static int[] dijkstra(Graph g, int src) {
        int[] dist = new int[g.V];
        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[src] = 0;

        // PQ of {distance, vertex}
        PriorityQueue<int[]> pq = new PriorityQueue<>(Comparator.comparingInt(a -> a[0]));
        pq.offer(new int[] { 0, src });

        while (!pq.isEmpty()) {
            int[] curr = pq.poll();
            int d = curr[0], u = curr[1];
            if (d > dist[u])
                continue; // stale entry

            for (int[] edge : g.wAdj.get(u)) {
                int v = edge[0], w = edge[1];
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.offer(new int[] { dist[v], v });
                }
            }
        }
        return dist;
    }

    // ============================================================
    // SECTION 6: UNION-FIND + KRUSKAL'S MST
    // ============================================================
    static int[] ufParent, ufRank;

    static int find(int x) {
        if (ufParent[x] != x)
            ufParent[x] = find(ufParent[x]);
        return ufParent[x];
    }

    static boolean unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry)
            return false;
        if (ufRank[rx] < ufRank[ry])
            ufParent[rx] = ry;
        else if (ufRank[rx] > ufRank[ry])
            ufParent[ry] = rx;
        else {
            ufParent[ry] = rx;
            ufRank[rx]++;
        }
        return true;
    }

    static int kruskalMST(int V, int[][] edges) {
        Arrays.sort(edges, Comparator.comparingInt(e -> e[2]));
        ufParent = new int[V];
        ufRank = new int[V];
        for (int i = 0; i < V; i++)
            ufParent[i] = i;

        int totalWeight = 0, edgeCount = 0;
        System.out.println("  Kruskal MST edges:");
        for (int[] e : edges) {
            if (unite(e[0], e[1])) {
                System.out.println("    " + e[0] + " -- " + e[1] + " (w=" + e[2] + ")");
                totalWeight += e[2];
                if (++edgeCount == V - 1)
                    break;
            }
        }
        return totalWeight;
    }

    // ============================================================
    // MAIN
    // ============================================================
    public static void main(String[] args) {

        // --- BFS ---
        System.out.println("=== BFS — SHORTEST PATH ===");
        Graph g1 = new Graph(6);
        int[][] undirEdges = { { 0, 1 }, { 0, 2 }, { 1, 3 }, { 2, 3 }, { 3, 4 }, { 4, 5 } };
        for (int[] e : undirEdges)
            g1.addUndirectedEdge(e[0], e[1]);

        int[] dist = bfs(g1, 0);
        System.out.println("  BFS distances from 0: " + Arrays.toString(dist));
        System.out.println("  Path 0→5: " + bfsPath(g1, 0, 5));

        // --- Connected Components ---
        System.out.println("\n=== CONNECTED COMPONENTS ===");
        Graph g2 = new Graph(7);
        g2.addUndirectedEdge(0, 1);
        g2.addUndirectedEdge(1, 2);
        g2.addUndirectedEdge(3, 4);
        // 5 and 6 are isolated
        System.out.println("  Components: " + connectedComponents(g2));

        // --- Cycle Detection ---
        System.out.println("\n=== CYCLE DETECTION ===");
        Graph noCyc = new Graph(4);
        noCyc.addUndirectedEdge(0, 1);
        noCyc.addUndirectedEdge(1, 2);
        noCyc.addUndirectedEdge(2, 3);
        System.out.println("  Undirected no-cycle: " + hasCycleUndirected(noCyc));

        Graph hasCyc = new Graph(4);
        hasCyc.addUndirectedEdge(0, 1);
        hasCyc.addUndirectedEdge(1, 2);
        hasCyc.addUndirectedEdge(2, 3);
        hasCyc.addUndirectedEdge(3, 0);
        System.out.println("  Undirected with cycle: " + hasCycleUndirected(hasCyc));

        Graph dirNoCyc = new Graph(4);
        dirNoCyc.addEdge(0, 1);
        dirNoCyc.addEdge(1, 2);
        dirNoCyc.addEdge(2, 3);
        System.out.println("  Directed no-cycle: " + hasCycleDirected(dirNoCyc));

        Graph dirCyc = new Graph(4);
        dirCyc.addEdge(0, 1);
        dirCyc.addEdge(1, 2);
        dirCyc.addEdge(2, 0);
        System.out.println("  Directed with cycle: " + hasCycleDirected(dirCyc));

        // --- Topological Sort ---
        System.out.println("\n=== TOPOLOGICAL SORT ===");
        Graph dag = new Graph(6);
        dag.addEdge(5, 2);
        dag.addEdge(5, 0);
        dag.addEdge(4, 0);
        dag.addEdge(4, 1);
        dag.addEdge(2, 3);
        dag.addEdge(3, 1);
        System.out.println("  Topological order: " + topologicalSort(dag));

        // --- Dijkstra ---
        System.out.println("\n=== DIJKSTRA'S SHORTEST PATH ===");
        Graph dg = new Graph(5);
        dg.addWeightedEdge(0, 1, 4);
        dg.addWeightedEdge(0, 2, 1);
        dg.addWeightedEdge(2, 1, 2);
        dg.addWeightedEdge(1, 3, 1);
        dg.addWeightedEdge(2, 3, 5);
        dg.addWeightedEdge(3, 4, 3);
        int[] dDist = dijkstra(dg, 0);
        System.out.println("  Shortest from 0: " + Arrays.toString(dDist));

        // --- Kruskal MST ---
        System.out.println("\n=== KRUSKAL MST ===");
        int[][] mstEdges = { { 0, 1, 2 }, { 0, 3, 6 }, { 1, 2, 3 }, { 1, 3, 8 }, { 1, 4, 5 }, { 2, 4, 7 }, { 3, 4, 9 },
                { 3, 5, 5 }, { 4, 5, 4 } };
        int totalW = kruskalMST(6, mstEdges);
        System.out.println("  Total MST weight: " + totalW);
    }
}
