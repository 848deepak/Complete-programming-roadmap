# 🌐 Graph Traversal Template

## When to Use
- **BFS:** Shortest path (unweighted), level-order, minimum steps
- **DFS:** Explore all paths, cycle detection, topological sort, connected components
- **Grid problems** are just graphs where cells are nodes

## How to Recognize
Keywords: *shortest path*, *connected*, *reachable*, *islands*, *levels*, *topological order*, *cycle*.

## Common Mistakes
1. **Forgetting visited array** → infinite loops
2. **Marking visited too late** → same node added to queue multiple times
3. **Using DFS for shortest path** → only BFS guarantees shortest in unweighted graphs
4. **Grid boundary checks** → check `0 <= r < rows && 0 <= c < cols` before accessing

---

## Template — BFS (Queue)

```cpp
// C++ — BFS Template (Graph)
vector<int> bfs(int start, vector<vector<int>>& adj, int n) {
    vector<bool> visited(n, false);
    queue<int> q;
    vector<int> order;
    
    visited[start] = true;
    q.push(start);
    
    while (!q.empty()) {
        int node = q.front(); q.pop();
        order.push_back(node);
        
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;  // Mark BEFORE pushing
                q.push(neighbor);
            }
        }
    }
    return order;
}

// BFS — Shortest Path (unweighted)
int shortestPath(int src, int dest, vector<vector<int>>& adj, int n) {
    vector<int> dist(n, -1);
    queue<int> q;
    dist[src] = 0; q.push(src);
    
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == dest) return dist[u];
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return -1;  // Unreachable
}
```

```java
// Java — BFS
public static int shortestPath(int src, int dest, List<List<Integer>> adj, int n) {
    int[] dist = new int[n]; Arrays.fill(dist, -1);
    Queue<Integer> q = new LinkedList<>();
    dist[src] = 0; q.add(src);
    while (!q.isEmpty()) {
        int u = q.poll();
        if (u == dest) return dist[u];
        for (int v : adj.get(u)) {
            if (dist[v] == -1) { dist[v] = dist[u] + 1; q.add(v); }
        }
    }
    return -1;
}
```

## Template — DFS (Recursive)

```cpp
// C++ — DFS Template
void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited) {
    visited[node] = true;
    // Process node here
    
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, adj, visited);
        }
    }
}
```

## Template — DFS (Iterative with Stack)

```cpp
void dfsIterative(int start, vector<vector<int>>& adj, int n) {
    vector<bool> visited(n, false);
    stack<int> st;
    st.push(start);
    
    while (!st.empty()) {
        int node = st.top(); st.pop();
        if (visited[node]) continue;
        visited[node] = true;
        // Process node here
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) st.push(neighbor);
        }
    }
}
```

## Template — Grid BFS (4-directional)

```cpp
// C++ — Grid BFS
int bfsGrid(vector<vector<int>>& grid, int sr, int sc, int tr, int tc) {
    int rows = grid.size(), cols = grid[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    queue<tuple<int,int,int>> q;  // row, col, distance
    
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    
    visited[sr][sc] = true;
    q.push({sr, sc, 0});
    
    while (!q.empty()) {
        auto [r, c, dist] = q.front(); q.pop();
        if (r == tr && c == tc) return dist;
        
        for (int d = 0; d < 4; d++) {
            int nr = r + dx[d], nc = c + dy[d];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols 
                && !visited[nr][nc] && grid[nr][nc] == 0) {
                visited[nr][nc] = true;
                q.push({nr, nc, dist + 1});
            }
        }
    }
    return -1;
}
```

```java
public static int bfsGrid(int[][] grid, int sr, int sc, int tr, int tc) {
    int rows = grid.length, cols = grid[0].length;
    boolean[][] visited = new boolean[rows][cols];
    int[][] dirs = {{0,1},{0,-1},{1,0},{-1,0}};
    Queue<int[]> q = new LinkedList<>();
    visited[sr][sc] = true; q.add(new int[]{sr, sc, 0});
    while (!q.isEmpty()) {
        int[] p = q.poll();
        if (p[0]==tr && p[1]==tc) return p[2];
        for (int[] d : dirs) {
            int nr=p[0]+d[0], nc=p[1]+d[1];
            if (nr>=0&&nr<rows&&nc>=0&&nc<cols&&!visited[nr][nc]&&grid[nr][nc]==0) {
                visited[nr][nc]=true; q.add(new int[]{nr,nc,p[2]+1});
            }
        }
    }
    return -1;
}
```

---

## Example Problems

### 1. Number of Islands
**Pattern:** DFS/BFS on grid. For each unvisited '1', start DFS to mark entire island.

### 2. Word Ladder (Shortest Transformation)
**Pattern:** BFS. Each word is a node. Edge exists if words differ by 1 letter.

### 3. Course Schedule (Topological Sort)
**Pattern:** Build directed graph from prerequisites. BFS (Kahn's) or DFS with cycle detection.

---

## BFS vs DFS Decision Guide

| Use Case | BFS | DFS |
|----------|-----|-----|
| Shortest path (unweighted) | ✅ | ❌ |
| Explore all paths | ❌ | ✅ |
| Level-order traversal | ✅ | ❌ |
| Cycle detection | ✅ | ✅ |
| Topological sort | ✅ (Kahn's) | ✅ (finish time) |
| Connected components | Either | Either |
| Memory efficiency | O(width) | O(depth) |
