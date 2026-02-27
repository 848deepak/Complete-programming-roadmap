// ============================================================
// DSA | C++ → Arrays: Two Pointer Technique
// ============================================================
// DESCRIPTION:
//   The Two Pointer technique uses two indices that move toward
//   or away from each other to solve problems without nested loops.
//   Reduces O(n²) brute force to O(n) in many cases.
//
// CLASSIC APPLICATIONS:
//   - Pair with given sum in sorted array
//   - Remove duplicates from sorted array
//   - Container with most water
//   - 3Sum / 4Sum
//   - Palindrome check
//   - Trapping rain water
//
// COMPILE & RUN:
//   g++ -std=c++17 07_two_pointer.cpp -o out && ./out
//
// SAMPLE OUTPUT:
//   Pair with sum 9: (2, 7) at indices (1, 4)
// ============================================================

#include <iostream>
#include <vector>
#include <algorithm>    // sort
#include <string>
using namespace std;

// ============================================================
// SECTION 1: PAIR WITH GIVEN SUM (sorted array)
// ============================================================
// Approach: left pointer at start, right at end.
//   If sum too small → move left pointer right (increase sum)
//   If sum too large → move right pointer left (decrease sum)
//
// Time: O(n)  |  Space: O(1)  [O(n log n) if sorting needed]
// ------------------------------------------------------------ 

/**
 * Finds a pair in SORTED arr with sum == target.
 * Returns indices {l, r} or {-1,-1} if not found.
 */
pair<int,int> twoSum_sorted(const vector<int>& arr, int target) {
    int left  = 0;
    int right = (int)arr.size() - 1;

    while (left < right) {
        int sum = arr[left] + arr[right];

        if      (sum == target) return {left, right};   // found
        else if (sum  < target) left++;                 // need larger sum
        else                    right--;                // need smaller sum
    }

    return {-1, -1};  // no pair found
}

// ============================================================
// SECTION 2: REMOVE DUPLICATES FROM SORTED ARRAY
// ============================================================
// Two pointers: slow (write) and fast (read).
// Slow marks the last unique position; fast scans ahead.
//
// Time: O(n)  |  Space: O(1) — in-place
// ------------------------------------------------------------ 

/**
 * Removes duplicates from sorted arr in-place.
 * Returns the new length (unique elements).
 *
 * Example: [1,1,2,3,3,4] → [1,2,3,4] with new length 4
 */
int removeDuplicatesSorted(vector<int>& arr) {
    if (arr.empty()) return 0;

    int slow = 0;   // slow points to the last unique element written

    for (int fast = 1; fast < (int)arr.size(); fast++) {
        if (arr[fast] != arr[slow]) {     // new unique value found
            slow++;
            arr[slow] = arr[fast];        // write it next to previous unique
        }
        // else: fast saw a duplicate — skip it
    }

    return slow + 1;   // length of unique section
}

// ============================================================
// SECTION 3: CONTAINER WITH MOST WATER
// ============================================================
// Given heights[i], find i,j (i < j) maximising (j-i)*min(h[i],h[j]).
// Two pointers: always move the pointer with the SHORTER line.
// Moving the taller one can only decrease or maintain the area.
//
// Time: O(n)  |  Space: O(1)
// ------------------------------------------------------------ 

/**
 * Returns the maximum water that can be trapped between two walls.
 *
 * @param heights  Array of wall heights
 * @return         Maximum area
 */
int maxWaterContainer(const vector<int>& heights) {
    int left  = 0;
    int right = (int)heights.size() - 1;
    int maxArea = 0;

    while (left < right) {
        // Width × height of the shorter wall
        int area = (right - left) * min(heights[left], heights[right]);
        maxArea  = max(maxArea, area);

        // Move the pointer with the shorter wall inward
        if (heights[left] < heights[right]) left++;
        else                                right--;
    }

    return maxArea;
}

// ============================================================
// SECTION 4: TRAPPING RAIN WATER
// ============================================================
// Water trapped at i = min(maxLeft[i], maxRight[i]) - height[i]
// Two-pointer approach avoids building prefix-max arrays.
//
// Time: O(n)  |  Space: O(1)
// ------------------------------------------------------------ 

/**
 * Computes the total water trapped after raining.
 *
 * @param heights  Elevation map (heights of bars)
 * @return         Total units of water trapped
 *
 * Example: heights=[0,1,0,2,1,0,1,3,2,1,2,1] → 6
 */
int trapRainWater(const vector<int>& heights) {
    int left = 0, right = (int)heights.size() - 1;
    int maxLeft = 0, maxRight = 0;
    int water = 0;

    while (left <= right) {
        if (heights[left] <= heights[right]) {
            // The constraining wall is on the right (maxRight >= maxLeft)
            if (heights[left] >= maxLeft)
                maxLeft = heights[left];    // update left max
            else
                water += maxLeft - heights[left];  // water at left position
            left++;
        } else {
            if (heights[right] >= maxRight)
                maxRight = heights[right];  // update right max
            else
                water += maxRight - heights[right]; // water at right position
            right--;
        }
    }

    return water;
}

// ============================================================
// SECTION 5: THREE-SUM (find all unique triplets with sum 0)
// ============================================================
// Sort → fix one element → two-pointer scan on the rest.
//
// Time: O(n²)  |  Space: O(1) extra (excluding result)
// ------------------------------------------------------------ 

/**
 * Finds all unique triplets in arr that sum to zero.
 * Duplicate triplets are skipped.
 */
vector<vector<int>> threeSum(vector<int> arr) {
    sort(arr.begin(), arr.end());
    vector<vector<int>> result;
    int n = (int)arr.size();

    for (int i = 0; i < n - 2; i++) {
        if (i > 0 && arr[i] == arr[i-1]) continue;   // skip duplicate 'i' values

        int left  = i + 1;
        int right = n - 1;

        while (left < right) {
            int sum = arr[i] + arr[left] + arr[right];

            if (sum == 0) {
                result.push_back({arr[i], arr[left], arr[right]});
                while (left < right && arr[left]  == arr[left+1])  left++;   // skip dups
                while (left < right && arr[right] == arr[right-1]) right--;  // skip dups
                left++;
                right--;
            } else if (sum < 0) {
                left++;
            } else {
                right--;
            }
        }
    }

    return result;
}

// ============================================================
// SECTION 6: PALINDROME CHECK (string)
// ============================================================
// Two pointers meet in the middle comparing characters.
//
// Time: O(n)  |  Space: O(1)
// ------------------------------------------------------------ 

/**
 * Returns true if s is a palindrome (ignoring case, non-alphanumeric).
 */
bool isPalindrome(const string& s) {
    int left = 0, right = (int)s.size() - 1;

    while (left < right) {
        // Skip non-alphanumeric characters
        while (left < right && !isalnum(s[left]))  left++;
        while (left < right && !isalnum(s[right])) right--;

        if (tolower(s[left]) != tolower(s[right])) return false;

        left++;
        right--;
    }
    return true;
}

// ============================================================
// MAIN
// ============================================================
int main() {

    // --- Two Sum ---
    cout << "=== TWO SUM (sorted array) ===" << "\n";
    vector<int> arr = {1, 2, 3, 4, 6, 8, 9};
    auto [l, r] = twoSum_sorted(arr, 10);
    if (l != -1)
        cout << "Pair summing to 10: " << arr[l] << " + " << arr[r]
             << " at indices (" << l << ", " << r << ")\n";

    auto [l2, r2] = twoSum_sorted(arr, 99);
    cout << "Pair summing to 99: " << (l2 == -1 ? "not found" : "found") << "\n";

    // --- Remove Duplicates ---
    cout << "\n=== REMOVE DUPLICATES (sorted) ===" << "\n";
    vector<int> dup = {1, 1, 2, 3, 3, 3, 4, 5, 5};
    int newLen = removeDuplicatesSorted(dup);
    cout << "After dedup, length=" << newLen << ": ";
    for (int i = 0; i < newLen; i++) cout << dup[i] << " ";
    cout << "\n";

    // --- Water Container ---
    cout << "\n=== CONTAINER WITH MOST WATER ===" << "\n";
    vector<int> walls = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    cout << "heights=[1,8,6,2,5,4,8,3,7]\n";
    cout << "Max water: " << maxWaterContainer(walls) << "\n";  // 49

    // --- Trapping Rain Water ---
    cout << "\n=== TRAPPING RAIN WATER ===" << "\n";
    vector<int> elev = {0,1,0,2,1,0,1,3,2,1,2,1};
    cout << "heights=[0,1,0,2,1,0,1,3,2,1,2,1]\n";
    cout << "Water trapped: " << trapRainWater(elev) << " units\n";  // 6

    // --- Three Sum ---
    cout << "\n=== THREE SUM (sum == 0) ===" << "\n";
    vector<int> nums = {-1, 0, 1, 2, -1, -4};
    auto triplets = threeSum(nums);
    cout << "Input: [-1,0,1,2,-1,-4]\n";
    for (auto& t : triplets)
        cout << "  [" << t[0] << ", " << t[1] << ", " << t[2] << "]\n";

    // --- Palindrome ---
    cout << "\n=== PALINDROME ===" << "\n";
    vector<string> tests = {"racecar", "hello", "A man a plan a canal Panama", "Was it a car or a cat I saw"};
    for (auto& s : tests)
        cout << "\"" << s << "\" → " << (isPalindrome(s) ? "palindrome" : "not palindrome") << "\n";

    return 0;
}

// ============================================================
// COMPLEXITY SUMMARY
//   twoSum_sorted        : O(n) time, O(1) space
//   removeDuplicates     : O(n) time, O(1) space
//   maxWaterContainer    : O(n) time, O(1) space
//   trapRainWater        : O(n) time, O(1) space (vs O(n) with prefix arrays)
//   threeSum             : O(n²) time, O(1) extra space
//   isPalindrome         : O(n) time, O(1) space
// ============================================================
