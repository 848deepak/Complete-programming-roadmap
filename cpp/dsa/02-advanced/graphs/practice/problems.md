# 🌐 Graphs — Practice Problems

> **Topic:** Graph Algorithms | **Level:** Easy → Hard

---

| # | Problem | Difficulty | Pattern |
|---|---------|-----------|---------|
| 1 | [BFS of Graph](#1-bfs) | 🟢 Easy | BFS |
| 2 | [DFS of Graph](#2-dfs) | 🟢 Easy | DFS |
| 3 | [Detect Cycle in Undirected Graph](#3-cycle-undirected) | 🟢 Easy | DFS/BFS |
| 4 | [Connected Components](#4-connected-components) | 🟢 Easy | DFS |
| 5 | [Flood Fill](#5-flood-fill) | 🟢 Easy | DFS/BFS |
| 6 | [Detect Cycle in Directed Graph](#6-cycle-directed) | 🟡 Medium | DFS Colors |
| 7 | [Topological Sort](#7-topological-sort) | 🟡 Medium | Kahn's / DFS |
| 8 | [Number of Islands](#8-number-of-islands) | 🟡 Medium | DFS/BFS |
| 9 | [Course Schedule](#9-course-schedule) | 🟡 Medium | Topological Sort |
| 10 | [Bipartite Check](#10-bipartite) | 🟡 Medium | BFS Coloring |
| 11 | [Dijkstra's Shortest Path](#11-dijkstra) | 🔴 Hard | Priority Queue |
| 12 | [Minimum Spanning Tree (Kruskal)](#12-mst-kruskal) | 🔴 Hard | Union-Find |
| 13 | [Strongly Connected Components](#13-scc) | 🔴 Hard | Kosaraju/Tarjan |

---

## 🟢 EASY

### 1. BFS
```cpp
vector<int> bfs(int start, vector<vector<int>>& adj, int n) {
    vector<bool> visited(n, false); queue<int> q; vector<int> order;
    visited[start]=true; q.push(start);
    while (!q.empty()) { int u=q.front();q.pop(); order.push_back(u);
        for (int v:adj[u]) if (!visited[v]) { visited[v]=true; q.push(v); }
    }
    return order;
}
```

### 2. DFS
```cpp
void dfs(int u, vector<vector<int>>& adj, vector<bool>& vis, vector<int>& order) {
    vis[u]=true; order.push_back(u);
    for (int v:adj[u]) if (!vis[v]) dfs(v,adj,vis,order);
}
```

### 3. Detect Cycle in Undirected Graph
```cpp
bool hasCycleDFS(int u, int parent, vector<vector<int>>& adj, vector<bool>& vis) {
    vis[u]=true;
    for (int v:adj[u]) { if (!vis[v]) { if (hasCycleDFS(v,u,adj,vis)) return true; } else if (v!=parent) return true; }
    return false;
}
```

### 4. Connected Components
**Count using DFS from each unvisited node.**
```cpp
int countComponents(int n, vector<vector<int>>& adj) {
    vector<bool> vis(n,false); int count=0;
    for (int i=0;i<n;i++) if (!vis[i]) { dfs(i,adj,vis); count++; }
    return count;
}
```

### 5. Flood Fill
```cpp
void floodFill(vector<vector<int>>& img, int r, int c, int newColor) {
    int old = img[r][c]; if (old==newColor) return;
    img[r][c]=newColor; int dx[]={0,0,1,-1}, dy[]={1,-1,0,0};
    for (int d=0;d<4;d++) { int nr=r+dx[d],nc=c+dy[d];
        if (nr>=0&&nr<(int)img.size()&&nc>=0&&nc<(int)img[0].size()&&img[nr][nc]==old)
            floodFill(img,nr,nc,newColor);
    }
}
```

---

## 🟡 MEDIUM

### 6. Detect Cycle in Directed Graph
**Approach:** DFS with 3 colors: WHITE (unvisited), GRAY (in current path), BLACK (done). Cycle exists if we visit a GRAY node.

```cpp
bool hasCycleDirected(int u, vector<vector<int>>& adj, vector<int>& color) {
    color[u]=1; // GRAY
    for (int v:adj[u]) { if (color[v]==1) return true; if (color[v]==0 && hasCycleDirected(v,adj,color)) return true; }
    color[u]=2; return false; // BLACK
}
```

### 7. Topological Sort (Kahn's BFS)
```cpp
vector<int> topoSort(int n, vector<vector<int>>& adj) {
    vector<int> indeg(n,0);
    for (int u=0;u<n;u++) for (int v:adj[u]) indeg[v]++;
    queue<int> q; for (int i=0;i<n;i++) if (indeg[i]==0) q.push(i);
    vector<int> order;
    while (!q.empty()) { int u=q.front();q.pop(); order.push_back(u);
        for (int v:adj[u]) if (--indeg[v]==0) q.push(v);
    }
    return order; // if order.size() < n → cycle exists
}
```
```java
public static int[] topoSort(int n, List<List<Integer>> adj) {
    int[] indeg = new int[n]; for (int u=0;u<n;u++) for (int v:adj.get(u)) indeg[v]++;
    Queue<Integer> q = new LinkedList<>(); for (int i=0;i<n;i++) if (indeg[i]==0) q.add(i);
    int[] order = new int[n]; int idx=0;
    while (!q.isEmpty()) { int u=q.poll(); order[idx++]=u; for (int v:adj.get(u)) if(--indeg[v]==0) q.add(v); }
    return order;
}
```

### 8. Number of Islands
**Problem:** Count connected components of `1`s in a 2D grid.

```cpp
int numIslands(vector<vector<char>>& grid) {
    int count=0, rows=grid.size(), cols=grid[0].size();
    for (int r=0;r<rows;r++) for (int c=0;c<cols;c++) if (grid[r][c]=='1') {
        count++; // DFS to mark island
        queue<pair<int,int>> q; q.push({r,c}); grid[r][c]='0';
        int dx[]={0,0,1,-1},dy[]={1,-1,0,0};
        while (!q.empty()) { auto [cr,cc]=q.front();q.pop();
            for (int d=0;d<4;d++) { int nr=cr+dx[d],nc=cc+dy[d];
                if (nr>=0&&nr<rows&&nc>=0&&nc<cols&&grid[nr][nc]=='1') { grid[nr][nc]='0'; q.push({nr,nc}); }
            }
        }
    }
    return count;
}
```

### 9. Course Schedule
**Problem:** Given n courses and prerequisites, check if all courses can be finished (i.e., no cycle in directed graph).
**Approach:** Topological sort. If sorted order has < n nodes → cycle exists.

```cpp
bool canFinish(int n, vector<vector<int>>& prereqs) {
    vector<vector<int>> adj(n); vector<int> indeg(n,0);
    for (auto& p:prereqs) { adj[p[1]].push_back(p[0]); indeg[p[0]]++; }
    queue<int> q; for (int i=0;i<n;i++) if (indeg[i]==0) q.push(i);
    int count=0;
    while (!q.empty()) { int u=q.front();q.pop(); count++;
        for (int v:adj[u]) if (--indeg[v]==0) q.push(v);
    }
    return count==n;
}
```

### 10. Bipartite Check
**Approach:** BFS coloring with 2 colors. If adjacent nodes have same color → not bipartite.

```cpp
bool isBipartite(vector<vector<int>>& adj, int n) {
    vector<int> color(n, -1);
    for (int i=0;i<n;i++) {
        if (color[i]!=-1) continue;
        queue<int> q; q.push(i); color[i]=0;
        while (!q.empty()) { int u=q.front();q.pop();
            for (int v:adj[u]) { if (color[v]==-1) { color[v]=1-color[u]; q.push(v); }
                else if (color[v]==color[u]) return false; }
        }
    }
    return true;
}
```

---

## 🔴 HARD

### 11. Dijkstra's Shortest Path
```cpp
vector<int> dijkstra(int src, vector<vector<pair<int,int>>>& adj, int n) {
    vector<int> dist(n, INT_MAX); dist[src]=0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    pq.push({0, src});
    while (!pq.empty()) {
        auto [d,u] = pq.top(); pq.pop();
        if (d>dist[u]) continue;
        for (auto [v,w]:adj[u]) if (dist[u]+w<dist[v]) { dist[v]=dist[u]+w; pq.push({dist[v],v}); }
    }
    return dist;
}
```
```java
public static int[] dijkstra(int src, List<List<int[]>> adj, int n) {
    int[] dist = new int[n]; Arrays.fill(dist, Integer.MAX_VALUE); dist[src]=0;
    PriorityQueue<int[]> pq = new PriorityQueue<>((a,b)->a[0]-b[0]);
    pq.offer(new int[]{0,src});
    while(!pq.isEmpty()){int[] top=pq.poll();int d=top[0],u=top[1];if(d>dist[u])continue;
        for(int[] e:adj.get(u)){int v=e[0],w=e[1];if(dist[u]+w<dist[v]){dist[v]=dist[u]+w;pq.offer(new int[]{dist[v],v});}}}
    return dist;
}
```
**O((V+E) log V).**

### 12. MST — Kruskal's Algorithm
```cpp
struct Edge { int u,v,w; };
class DSU {
    vector<int> parent, rank_;
public:
    DSU(int n):parent(n),rank_(n,0){iota(parent.begin(),parent.end(),0);}
    int find(int x){return parent[x]==x?x:parent[x]=find(parent[x]);}
    bool unite(int a, int b){a=find(a);b=find(b);if(a==b)return false;
        if(rank_[a]<rank_[b])swap(a,b);parent[b]=a;if(rank_[a]==rank_[b])rank_[a]++;return true;}
};
int kruskal(int n, vector<Edge>& edges) {
    sort(edges.begin(),edges.end(),[](auto&a,auto&b){return a.w<b.w;});
    DSU dsu(n); int cost=0, count=0;
    for (auto& e:edges) if (dsu.unite(e.u,e.v)) { cost+=e.w; if(++count==n-1) break; }
    return cost;
}
```
**O(E log E).**

### 13. Strongly Connected Components (Kosaraju's)
```cpp
void dfs1(int u, vector<vector<int>>& adj, vector<bool>& vis, stack<int>& order) {
    vis[u]=true; for (int v:adj[u]) if (!vis[v]) dfs1(v,adj,vis,order); order.push(u);
}
void dfs2(int u, vector<vector<int>>& radj, vector<bool>& vis, vector<int>& comp) {
    vis[u]=true; comp.push_back(u); for (int v:radj[u]) if (!vis[v]) dfs2(v,radj,vis,comp);
}
vector<vector<int>> kosaraju(int n, vector<vector<int>>& adj) {
    // Step 1: Fill order by finish time
    stack<int> order; vector<bool> vis(n,false);
    for (int i=0;i<n;i++) if (!vis[i]) dfs1(i,adj,vis,order);
    // Step 2: Build reverse graph
    vector<vector<int>> radj(n);
    for (int u=0;u<n;u++) for (int v:adj[u]) radj[v].push_back(u);
    // Step 3: DFS on reverse in order of finish time
    fill(vis.begin(),vis.end(),false);
    vector<vector<int>> sccs;
    while (!order.empty()) { int u=order.top(); order.pop();
        if (!vis[u]) { vector<int> comp; dfs2(u,radj,vis,comp); sccs.push_back(comp); }
    }
    return sccs;
}
```
**O(V + E).**

---

## 🗺️ Pattern Summary

| Pattern | Problems |
|---------|----------|
| BFS/DFS Traversal | BFS, DFS, Flood Fill, Islands |
| Cycle Detection | Undirected (parent), Directed (colors) |
| Topological Sort | Kahn's BFS, Course Schedule |
| Coloring | Bipartite Check |
| Shortest Path | Dijkstra |
| MST | Kruskal + Union-Find |
| SCC | Kosaraju |
