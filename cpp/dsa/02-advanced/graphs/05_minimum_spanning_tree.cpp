// ============================================================
// DSA | C++ → Graphs: Minimum Spanning Tree — Kruskal & Prim
// ============================================================
// DESCRIPTION:
//   A Minimum Spanning Tree (MST) connects all V vertices with
//   the minimum total edge weight using exactly V-1 edges.
//
//   KRUSKAL'S: Sort edges by weight; add edge if it doesn't form cycle.
//              Uses Union-Find (Disjoint Set Union) data structure.
//              Best for sparse graphs: O(E log E).
//
//   PRIM'S:    Greedy; grow MST one vertex at a time by always
//              choosing the cheapest edge to a non-MST vertex.
//              Best for dense graphs: O((V+E) log V).
//
// COMPILE & RUN:
//   g++ -std=c++17 05_minimum_spanning_tree.cpp -o out && ./out
// ============================================================

#include <iostream>
#include <vector>
#include <algorithm>    // sort
#include <queue>        // priority_queue (Prim's)
#include <numeric>      // iota
using namespace std;

// ============================================================
// UNION-FIND (Disjoint Set Union) — needed by Kruskal's
// ============================================================
// Two operations:
//   find(x)   : returns root of x's component
//   unify(x,y): merges the components of x and y
//
// Optimisations:
//   Path Compression : flatten tree during find
//   Union by Rank    : always attach shorter tree under taller
//
// Time: nearly O(1) per operation (inverse Ackermann)
// ------------------------------------------------------------ 

class UnionFind {
    vector<int> parent_, rank_;
public:
    explicit UnionFind(int n) : parent_(n), rank_(n, 0) {
        iota(parent_.begin(), parent_.end(), 0);   // parent[i] = i
    }

    /**
     * Find root of x with path compression.
     * Flattens the tree: every node on the path points directly to root.
     */
    int find(int x) {
        if (parent_[x] != x) parent_[x] = find(parent_[x]);   // path compression
        return parent_[x];
    }

    /**
     * Unite the sets of x and y.
     * Returns false if x and y are already in the same set (would form cycle).
     */
    bool unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return false;   // same component → cycle

        // Union by rank: attach smaller rank tree under higher rank
        if      (rank_[rx] < rank_[ry]) parent_[rx] = ry;
        else if (rank_[rx] > rank_[ry]) parent_[ry] = rx;
        else {
            parent_[ry] = rx;
            rank_[rx]++;
        }
        return true;
    }

    bool connected(int x, int y) { return find(x) == find(y); }
};

// ============================================================
// SECTION 1: KRUSKAL'S ALGORITHM
// ============================================================
// STEPS:
//   1. Sort all edges by weight (ascending).
//   2. For each edge (u, v, w):
//      - If u and v are in different components → add edge to MST, unite them.
//      - Else → skip (would form a cycle).
//   3. Stop when MST has V-1 edges.
//
// Time: O(E log E) for sorting  |  Space: O(V + E)
// ------------------------------------------------------------ 

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const { return w < other.w; }
};

/**
 * Computes MST using Kruskal's algorithm.
 *
 * @param edges  All edges (undirected, may contain duplicates with different weights)
 * @param V      Number of vertices (0..V-1)
 * @return       {MST edges, total MST weight}, or {edges=empty, weight=-1} if no MST
 */
pair<vector<Edge>, int> kruskal(vector<Edge> edges, int V) {
    sort(edges.begin(), edges.end());   // Step 1: sort by weight

    UnionFind uf(V);
    vector<Edge> mst;
    int totalWeight = 0;

    for (const auto& e : edges) {
        if (uf.unite(e.u, e.v)) {     // Step 2: add if no cycle formed
            mst.push_back(e);
            totalWeight += e.w;
            if ((int)mst.size() == V - 1) break;  // MST complete
        }
    }

    // If MST doesn't have V-1 edges, graph is disconnected
    if ((int)mst.size() < V - 1) return {{}, -1};
    return {mst, totalWeight};
}

// ============================================================
// SECTION 2: PRIM'S ALGORITHM
// ============================================================
// STEPS:
//   1. Start from any vertex (say vertex 0).
//   2. Use a min-heap keyed on edge weight.
//   3. Mark vertex as visited; add all its edges to heap.
//   4. Extract minimum weight edge; if destination unvisited:
//      - Add edge to MST; mark destination visited.
//      - Add its edges to heap.
//   5. Repeat until all vertices visited.
//
// Time: O((V + E) log V)  |  Space: O(V + E)
// ------------------------------------------------------------ 

using WGraph = vector<vector<pair<int,int>>>;   // adj[u] = {(v, weight)}

/**
 * Computes MST using Prim's algorithm.
 *
 * @param adj  Adjacency list (undirected graph)
 * @param V    Number of vertices
 * @return     {MST edge list, total MST weight}
 */
pair<vector<Edge>, int> prim(const WGraph& adj, int V) {
    vector<bool> inMST(V, false);
    // Min-heap: (weight, u, v)
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> minHeap;
    minHeap.push({0, 0, -1});   // weight=0, vertex=0, parent=-1 (source has no parent)

    vector<Edge> mst;
    int totalWeight = 0;

    while (!minHeap.empty()) {
        auto [w, u, parent] = minHeap.top(); minHeap.pop();

        if (inMST[u]) continue;   // already in MST, skip
        inMST[u] = true;

        if (parent != -1) {       // not the starting vertex
            mst.push_back({parent, u, w});
            totalWeight += w;
        }

        for (auto [v, ew] : adj[u]) {
            if (!inMST[v]) {
                minHeap.push({ew, v, u});   // add edge to heap
            }
        }
    }

    if ((int)mst.size() < V - 1) return {{}, -1};   // disconnected
    return {mst, totalWeight};
}

// ============================================================
// HELPER: Build weighted undirected graph (adj list + edge list)
// ============================================================
struct GraphData {
    WGraph adj;
    vector<Edge> edges;
};

GraphData buildGraph(int V, const vector<tuple<int,int,int>>& edgeList) {
    WGraph adj(V);
    vector<Edge> edges;
    for (auto [u, v, w] : edgeList) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        edges.push_back({u, v, w});
    }
    return {adj, edges};
}

// ============================================================
// MAIN
// ============================================================
int main() {
    // Classic weighted undirected graph:
    //        2
    //   0 ------- 1
    //   |  \    / |
    //   6   8  5  3
    //   |    \/   |
    //   5    4    2
    //   |    |    |
    //   3 ------- 4
    //        9

    auto [adj, edges] = buildGraph(6, {
        {0,1,2}, {0,3,6}, {1,2,3}, {1,3,8}, {1,4,5},
        {2,4,7}, {3,4,9}, {3,5,5}, {4,5,4}
    });

    cout << "Graph edges:\n";
    for (const auto& e : edges)
        cout << "  " << e.u << " -- " << e.v << " (w=" << e.w << ")\n";

    // --- Kruskal ---
    cout << "\n=== KRUSKAL'S MST ===" << "\n";
    auto [kMST, kWeight] = kruskal(edges, 6);
    if (kWeight == -1) {
        cout << "  Graph is disconnected — no MST\n";
    } else {
        cout << "  MST edges:\n";
        for (const auto& e : kMST)
            cout << "    " << e.u << " -- " << e.v << " (w=" << e.w << ")\n";
        cout << "  Total MST weight: " << kWeight << "\n";
    }

    // --- Prim ---
    cout << "\n=== PRIM'S MST ===" << "\n";
    auto [pMST, pWeight] = prim(adj, 6);
    if (pWeight == -1) {
        cout << "  Graph is disconnected — no MST\n";
    } else {
        cout << "  MST edges:\n";
        for (const auto& e : pMST)
            cout << "    " << e.u << " -- " << e.v << " (w=" << e.w << ")\n";
        cout << "  Total MST weight: " << pWeight << "\n";
    }

    // --- Union-Find demo ---
    cout << "\n=== UNION-FIND Demo ===" << "\n";
    UnionFind uf(5);
    cout << "  Initially all separate\n";
    cout << "  unite(0,1): " << (uf.unite(0,1) ? "ok" : "cycle") << "\n";
    cout << "  unite(2,3): " << (uf.unite(2,3) ? "ok" : "cycle") << "\n";
    cout << "  unite(0,2): " << (uf.unite(0,2) ? "ok" : "cycle") << "\n";
    cout << "  unite(1,3): " << (uf.unite(1,3) ? "ok (would cause cycle!) " : "cycle DETECTED") << "\n";
    cout << "  connected(0,3): " << (uf.connected(0,3) ? "yes" : "no") << "\n";
    cout << "  connected(0,4): " << (uf.connected(0,4) ? "yes" : "no") << "\n";

    // --- Edge case: disconnected graph ---
    cout << "\n=== EDGE: DISCONNECTED GRAPH ===" << "\n";
    auto [dAdj, dEdges] = buildGraph(4, {{0,1,5},{2,3,3}});   // two components
    auto [dMST, dW] = kruskal(dEdges, 4);
    cout << "  Kruskal on disconnected: " << (dW == -1 ? "no MST (correct)" : "mst found?") << "\n";

    return 0;
}

// ============================================================
// COMPARISON TABLE
//   Algorithm  | Time              | Space    | Best For
//   Kruskal    | O(E log E)        | O(V+E)   | Sparse graphs
//   Prim       | O((V+E) log V)    | O(V+E)   | Dense graphs
//   (with adj matrix Prim: O(V²)   | O(V²)    | Very dense)
//
// Both produce an MST with V-1 edges and minimum total weight.
// For same weight edges, different valid MSTs may exist.
// ============================================================
