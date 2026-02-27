/*
Topic: Data Structures and Algorithms
Learning Goal: Understand this concept with a runnable example.
Approach: Read main() first, then helper function(s), then modify sample input.
Time Complexity: Analyze the core operation in this file while practicing.
Space Complexity: Check recursion/auxiliary data structure usage.
How to Run: Compile and run this file; verify output shown in terminal.
Practice Task: Change inputs and test at least 3 edge cases.
*/

import java.util.Arrays;

class ArrayInsert {
    public static void main(String[] args) {
        int[] arr = {1, 2, 3, 4, 5};
        int position = 2;
        int value = 99;

        int[] result = new int[arr.length + 1];
        for (int i = 0, j = 0; i < result.length; i++) {
            if (i == position) {
                result[i] = value;
            } else {
                result[i] = arr[j++];
            }
        }

        System.out.println(Arrays.toString(result));
    }
}
