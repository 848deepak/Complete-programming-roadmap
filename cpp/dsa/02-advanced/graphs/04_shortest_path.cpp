// ============================================================
// DSA | C++ → Graphs: Shortest Path — Dijkstra & Bellman-Ford
// ============================================================
// DESCRIPTION:
//   Finding shortest paths in weighted graphs.
//
//   DIJKSTRA: Works on non-negative weighted graphs.
//             Greedy: always extends shortest known path.
//             Time: O((V+E) log V) with priority queue.
//
//   BELLMAN-FORD: Works on graphs with negative weights.
//                 Detects negative weight cycles.
//                 Time: O(V * E).
//
// COMPILE & RUN:
//   g++ -std=c++17 04_shortest_path.cpp -o out && ./out
// ============================================================

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <string>
using namespace std;

using Graph = vector<vector<pair<int,int>>>;   // adjacency list: {neighbor, weight}

// ============================================================
// HELPER: Print distances from source
// ============================================================
void printDist(const string& algo, const vector<int>& dist, int src) {
    cout << "  " << algo << " from vertex " << src << ":\n";
    for (int i = 0; i < (int)dist.size(); i++) {
        cout << "    " << src << " → " << i << " : ";
        if (dist[i] == INT_MAX) cout << "∞\n";
        else                    cout << dist[i] << "\n";
    }
}

// ============================================================
// SECTION 1: DIJKSTRA'S ALGORITHM
// ============================================================
// IDEA:
//   - Maintain a min-heap of (distance, vertex) pairs.
//   - Always process the vertex with the shortest known distance.
//   - For each neighbor, update distance if new path is shorter.
//
// REQUIREMENT: Non-negative edge weights.
// Negative weights break the greedy assumption (a later path
// might be shorter but we've already finalized the node).
//
// Time: O((V+E) log V)  |  Space: O(V)
// ------------------------------------------------------------ 

/**
 * Returns shortest distances from `src` to all vertices.
 * dist[v] = INT_MAX if v is unreachable.
 *
 * @param adj  Adjacency list: adj[u] = {(v, weight)}
 * @param V    Number of vertices
 * @param src  Source vertex
 */
vector<int> dijkstra(const Graph& adj, int V, int src) {
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    // Min-heap: (distance, vertex)
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> minHeap;
    minHeap.push({0, src});

    while (!minHeap.empty()) {
        auto [d, u] = minHeap.top();
        minHeap.pop();

        if (d > dist[u]) continue;   // outdated entry — skip (lazy deletion)

        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;   // found shorter path to v
                minHeap.push({dist[v], v});
            }
        }
    }

    return dist;
}

/**
 * Dijkstra with path reconstruction.
 * Returns {distances, parent array}.
 * Trace parent[] backward from destination to recover path.
 */
pair<vector<int>, vector<int>> dijkstraWithPath(const Graph& adj, int V, int src) {
    vector<int> dist(V, INT_MAX);
    vector<int> parent(V, -1);
    dist[src] = 0;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> minHeap;
    minHeap.push({0, src});

    while (!minHeap.empty()) {
        auto [d, u] = minHeap.top(); minHeap.pop();
        if (d > dist[u]) continue;

        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v]   = dist[u] + w;
                parent[v] = u;           // record how we got to v
                minHeap.push({dist[v], v});
            }
        }
    }

    return {dist, parent};
}

void printPath(int src, int dest, const vector<int>& parent) {
    if (parent[dest] == -1 && dest != src) {
        cout << "  No path from " << src << " to " << dest << "\n";
        return;
    }
    vector<int> path;
    for (int v = dest; v != -1; v = parent[v]) path.push_back(v);
    reverse(path.begin(), path.end());
    cout << "  Path " << src << "→" << dest << ": ";
    for (int i = 0; i < (int)path.size(); i++)
        cout << path[i] << (i+1 < (int)path.size() ? " → " : "");
    cout << "  (cost=" << -1 << ")\n";
}

// ============================================================
// SECTION 2: BELLMAN-FORD ALGORITHM
// ============================================================
// IDEA:
//   Relax ALL edges (V-1) times.
//   After V-1 relaxations, shortest paths are finalized IF
//   no negative cycles exist.
//   Do one more pass: if any edge can still be relaxed → negative cycle!
//
// WORKS WITH: Negative weights (but NOT negative cycles).
//
// Time: O(V * E)  |  Space: O(V)
// ------------------------------------------------------------ 

struct Edge {
    int u, v, w;   // u → v with weight w
};

/**
 * Bellman-Ford shortest path from `src`.
 *
 * @param edges  All edges of the graph
 * @param V      Number of vertices
 * @param src    Source vertex
 * @return       {distances, hasNegCycle}
 */
pair<vector<int>, bool> bellmanFord(const vector<Edge>& edges, int V, int src) {
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    // Relax all edges V-1 times
    for (int i = 0; i < V - 1; i++) {
        for (const auto& [u, v, w] : edges) {
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    // Check for negative cycle: if any edge can still be relaxed
    bool hasNegCycle = false;
    for (const auto& [u, v, w] : edges) {
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            hasNegCycle = true;
            break;
        }
    }

    return {dist, hasNegCycle};
}

// ============================================================
// SECTION 3: FLOYD-WARSHALL (All-Pairs Shortest Path)
// ============================================================
// Find shortest paths between ALL pairs of vertices.
// Dynamic programming: dist[i][j][k] = shortest path i→j using
// only vertices 0..k as intermediates.
//
// Time: O(V³)  |  Space: O(V²)
// Also detects negative cycles: if dist[v][v] < 0
// ------------------------------------------------------------ 

/**
 * Returns all-pairs shortest distances.
 * dist[i][j] = shortest distance from vertex i to j.
 * dist[i][j] = INF if unreachable.
 * Set adj[i][j] to edge weight (or INF if no direct edge).
 */
const int INF = 1e9;

vector<vector<int>> floydWarshall(vector<vector<int>> dist, int V) {
    for (int k = 0; k < V; k++) {               // intermediate vertex
        for (int i = 0; i < V; i++) {            // source
            for (int j = 0; j < V; j++) {        // destination
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    return dist;   // dist[i][i] < 0 indicates negative cycle reachable from i
}

// ============================================================
// MAIN
// ============================================================
int main() {

    // Graph: 5 vertices, directed weighted edges
    //  0 --(4)--> 1
    //  0 --(1)--> 2
    //  2 --(2)--> 1
    //  1 --(1)--> 3
    //  2 --(5)--> 3
    //  3 --(3)--> 4

    int V = 5;
    Graph adj(V);
    auto addEdge = [&](int u, int v, int w) { adj[u].push_back({v, w}); };
    addEdge(0, 1, 4);
    addEdge(0, 2, 1);
    addEdge(2, 1, 2);
    addEdge(1, 3, 1);
    addEdge(2, 3, 5);
    addEdge(3, 4, 3);

    // --- Dijkstra ---
    cout << "=== DIJKSTRA'S ALGORITHM ===" << "\n";
    cout << "  Graph: 0→1(4), 0→2(1), 2→1(2), 1→3(1), 2→3(5), 3→4(3)\n";
    auto dist = dijkstra(adj, V, 0);
    printDist("Dijkstra", dist, 0);

    // With path
    auto [distances, parent] = dijkstraWithPath(adj, V, 0);
    cout << "  Shortest paths:\n";
    printPath(0, 4, parent);

    // --- Bellman-Ford ---
    cout << "\n=== BELLMAN-FORD ALGORITHM ===" << "\n";
    // Same graph but as edge list (supports negative weights)
    vector<Edge> edges = {
        {0,1,4}, {0,2,1}, {2,1,2}, {1,3,1}, {2,3,5}, {3,4,3}
    };
    auto [bfDist, negCycle] = bellmanFord(edges, V, 0);
    printDist("Bellman-Ford", bfDist, 0);
    cout << "  Negative cycle: " << (negCycle ? "DETECTED" : "NONE") << "\n";

    // Negative weight edge example
    cout << "\n  --- With negative weight edge (3→1 : -6) ---\n";
    vector<Edge> negEdges = {{0,1,4},{0,2,1},{2,1,2},{1,3,1},{2,3,5},{3,4,3},{3,1,-6}};
    auto [negDist, negCyc] = bellmanFord(negEdges, V, 0);
    printDist("Bellman-Ford (neg weight)", negDist, 0);
    cout << "  Negative cycle: " << (negCyc ? "DETECTED" : "NONE") << "\n";

    // Negative CYCLE example
    cout << "\n  --- Negative cycle example (1→2→3→1 with weights 1,-1,-1) ---\n";
    vector<Edge> cycleEdges = {{0,1,1},{1,2,1},{2,3,-1},{3,1,-1}};
    auto [cycleDist, hasCyc] = bellmanFord(cycleEdges, 4, 0);
    cout << "  Negative cycle DETECTED: " << (hasCyc ? "YES" : "NO") << "\n";

    // --- Floyd-Warshall ---
    cout << "\n=== FLOYD-WARSHALL (All-Pairs) ===" << "\n";
    // 4-vertex graph with negative weight but no negative cycle
    vector<vector<int>> w = {
        {0,   3,   INF, 7},
        {8,   0,   2,   INF},
        {5,   INF, 0,   1},
        {2,   INF, INF, 0}
    };
    auto fw = floydWarshall(w, 4);
    cout << "  Shortest paths matrix:\n";
    cout << "      0    1    2    3\n";
    for (int i = 0; i < 4; i++) {
        cout << "  " << i << ": ";
        for (int j = 0; j < 4; j++) {
            if (fw[i][j] == INF) cout << "  ∞ ";
            else printf(" %3d", fw[i][j]);
        }
        cout << "\n";
    }

    return 0;
}

// ============================================================
// COMPARISON TABLE
//   Algorithm      | Weights       | Cycle  | Time         | Space
//   Dijkstra       | ≥0             | No     | O((V+E)logV) | O(V)
//   Bellman-Ford   | Any            | Detects| O(V*E)       | O(V)
//   Floyd-Warshall | Any (no neg cy)| Detects| O(V³)        | O(V²)
//
// USE WHEN:
//   Dijkstra      : non-negative weights, single source
//   Bellman-Ford  : negative weights, negative cycle detection
//   Floyd-Warshall: all-pairs shortest paths
// ============================================================
