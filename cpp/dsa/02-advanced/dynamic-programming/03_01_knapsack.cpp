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
using namespace std;

int knapsack(const vector<int>& weight, const vector<int>& value, int capacity) {
    int n = weight.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int currentCapacity = 0; currentCapacity <= capacity; currentCapacity++) {
            dp[i][currentCapacity] = dp[i - 1][currentCapacity];
            if (weight[i - 1] <= currentCapacity) {
                dp[i][currentCapacity] = max(
                    dp[i][currentCapacity],
                    value[i - 1] + dp[i - 1][currentCapacity - weight[i - 1]]
                );
            }
        }
    }
    return dp[n][capacity];
}

int main() {
    vector<int> weight = {1, 3, 4, 5};
    vector<int> value = {1, 4, 5, 7};
    int capacity = 7;

    cout << "Max knapsack value: " << knapsack(weight, value, capacity) << endl;
    return 0;
}

/*
Sample Output:
Max knapsack value: 9
*/
