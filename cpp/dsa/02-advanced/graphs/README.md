# C++ Data Structures & Algorithms: Graphs

> **Folder:** `cpp/dsa/02-advanced/graphs/` | **Level:** Advanced  
> **Files:** `01_graph_bfs.cpp` · `02_graph_dfs.cpp` · `03_dijkstra_shortest_path.cpp` · `04_shortest_path.cpp` · `05_minimum_spanning_tree.cpp`

---

## 1. Introduction

A Graph is a versatile, non-linear data structure consisting of **Vertices (Nodes)** connected by **Edges**. They model vast ranges of real-world networks: social connections, internet routing, road maps, and dependencies. 

> **Compile any file:**
> ```bash
> g++ -std=c++17 <filename>.cpp -o out && ./out
> ```

---

## 2. Core Graph Concepts

### 2.1 Terminology
- **Directed / Undirected:** Edges have a direction (one-way street) or are bidirectional (two-way street).
- **Weighted / Unweighted:** Edges carry a cost (e.g., shortest path calculations).
- **Cyclic / Acyclic:** Path exists where a node can reach itself again.
- **Tree vs. Graph:** A Tree is merely a connected, strictly acyclic undirected graph.

### 2.2 Representation Methods
- **Adjacency Matrix:** A 2D array `matrix[V][V]`. Cell `[i][j]` is `1` (or the weight) if an edge exists from `i` to `j`. Pros: Fast edge lookup `O(1)`. Cons: Spatially inefficient `O(V²)` if the graph is sparse.
- **Adjacency List:** An array/vector of lists. Index `i` holds a list of all nodes connected to `i`. Pros: Spatially efficient `O(V + E)`. Cons: Slower edge lookup `O(V)`. Preferred for most algorithms.

---

## 3. Core Traversal Algorithms

### 3.1 Breadth-First Search (BFS) (`01_graph_bfs.cpp`)
- **Mechanism:** Explores nodes layer-by-layer moving outwards from the root. Uses a **Queue**. Level `n` nodes are explored before Level `n+1`.
- **Primary Use Case:** Finding the shortest path in an **unweighted** graph. Finding all connected components.
- **Complexity:** Time: `O(V + E)` Space: `O(V)`

### 3.2 Depth-First Search (DFS) (`02_graph_dfs.cpp`)
- **Mechanism:** Explores as deeply as possible along a single branch before backtracking. Typically implemented via **Recursion** (using the Call Stack) or explicitly using a Stack.
- **Primary Use Case:** Topological sorting, detecting cycles, exploring mazes/grids.
- **Complexity:** Time: `O(V + E)` Space: `O(V)`

---

## 4. Advanced Graph Algorithms

### 4.1 Dijkstra's Shortest Path (`03` & `04`)
Finds the shortest path from a starting node to all other nodes in a **weighted** graph (weights must be non-negative).
- **Mechanism:** Maintains a priority queue (min-heap) of (distance, vertex) pairs. Always pulls the node with the shortest current known distance, marks it "settled", and "relaxes" (updates) the distances to its adjacent neighbors.
- **Complexity:** `O(E log V)` time using an Adjacency List + Min-Heap. 

### 4.2 Minimum Spanning Tree (MST) (`05_minimum_spanning_tree.cpp`)
Connects all the vertices together without any cycles, using the minimum possible total edge weight.
- **Prim's Algorithm Example:** Grows the MST edge by edge from a starting node, greedily selecting the cheapest edge that connects the existing tree to a new, unvisited node. (Often uses a Priority Queue).
- **Kruskal's Algorithm (Alt Idea):** Sort all edges by weight, greedily pick the cheapest edge that doesn't form a cycle (checked via a Disjoint Set / Union-Find structure).

---

## 5. Typical Patterns / Interview Problems

| Pattern | Classic Examples | Recommended Approach |
|---------|------------------|----------------------|
| **Matrix/Grid Problems** | Number of Islands, Max Area of Island, Word Search | Treat 2D grid as a graph. Use DFS or BFS. Check bounds carefully. |
| **Shortest Path (Unweighted)** | Word Ladder, Knight Constraints | **BFS**. First time a node is reached is guaranteed the shortest path. |
| **Shortest Path (Weighted)** | Network Delay Time, Minimum Cost Path | **Dijkstra** (Positive weights) or **Bellman-Ford** (Negative weights allowed). |
| **Dependencies / Ordering** | Course Schedule, Alien Dictionary | **Topological Sort** (Kahn's algorithm using In-Degrees or DFS). |
| **Connected Components** | Number of Provinces | **Union-Find (Disjoint Set)** or simple DFS/BFS loops counting disconnected groups. |

---

## 6. Common Pitfalls

- **Infinite Loops:** Not marking nodes as "visited". Graphs contain cycles! Always maintain a `visited` array or set.
- **Edge Direction:** Treating a directed graph as undirected when populating the Adjacency List (`adj[u].push_back(v)` vs `adj[u].push_back(v); adj[v].push_back(u);`).
- **Dijkstra Negative Edge Warning:** Dijkstra's Algorithm will fail if the graph contains negative weight edges.
- **Out of Bounds (Grids):** When treating 2D matrices as graphs (up/down/left/right), failing to check `0 <= row < R && 0 <= col < C` before exploring the neighbor.

---

> **The End:** This completes the DSA C++ module section!
