/*
Topic: Data Structures and Algorithms
Learning Goal: Understand this concept with a runnable example.
Approach: Read main() first, then helper function(s), then modify sample input.
Time Complexity: Analyze the core operation in this file while practicing.
Space Complexity: Check recursion/auxiliary data structure usage.
How to Run: Compile and run this file; verify output shown in terminal.
Practice Task: Change inputs and test at least 3 edge cases.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

vector<int> dijkstra(int start, const vector<vector<pair<int, int>>>& graph) {
    int n = graph.size();
    vector<int> distance(n, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;

    distance[start] = 0;
    minHeap.push({0, start});

    while (!minHeap.empty()) {
        auto [currentDistance, node] = minHeap.top();
        minHeap.pop();

        if (currentDistance > distance[node]) continue;

        for (const auto& [neighbor, weight] : graph[node]) {
            if (distance[node] + weight < distance[neighbor]) {
                distance[neighbor] = distance[node] + weight;
                minHeap.push({distance[neighbor], neighbor});
            }
        }
    }
    return distance;
}

int main() {
    vector<vector<pair<int, int>>> graph(5);
    graph[0] = {{1, 2}, {2, 4}};
    graph[1] = {{2, 1}, {3, 7}};
    graph[2] = {{4, 3}};
    graph[3] = {{4, 1}};

    vector<int> distance = dijkstra(0, graph);
    cout << "Shortest distance from node 0 to node 4: " << distance[4] << endl;
    return 0;
}

/*
Sample Output:
Shortest distance from node 0 to node 4: 6
*/
