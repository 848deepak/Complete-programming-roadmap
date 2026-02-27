/*
Topic: Data Structures and Algorithms
Learning Goal: Understand this concept with a runnable example.
Approach: Read main() first, then helper function(s), then modify sample input.
Time Complexity: Analyze the core operation in this file while practicing.
Space Complexity: Check recursion/auxiliary data structure usage.
How to Run: Compile and run this file; verify output shown in terminal.
Practice Task: Change inputs and test at least 3 edge cases.
*/

class ZeroOneKnapsack {
    static int knapsack(int[] weight, int[] value, int capacity) {
        int n = weight.length;
        int[][] dp = new int[n + 1][capacity + 1];

        for (int i = 1; i <= n; i++) {
            for (int currentCapacity = 0; currentCapacity <= capacity; currentCapacity++) {
                dp[i][currentCapacity] = dp[i - 1][currentCapacity];
                if (weight[i - 1] <= currentCapacity) {
                    dp[i][currentCapacity] = Math.max(
                        dp[i][currentCapacity],
                        value[i - 1] + dp[i - 1][currentCapacity - weight[i - 1]]
                    );
                }
            }
        }
        return dp[n][capacity];
    }

    public static void main(String[] args) {
        int[] weight = {1, 3, 4, 5};
        int[] value = {1, 4, 5, 7};
        int capacity = 7;

        System.out.println("Max knapsack value: " + knapsack(weight, value, capacity));
    }
}

/*
Sample Output:
Max knapsack value: 9
*/
