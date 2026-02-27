// ============================================================
// DSA | C++ → Hashing: HashMap, HashSet, Collision Handling
// ============================================================
// DESCRIPTION:
//   Explains hash tables with:
//   - unordered_map (hash map)
//   - unordered_set (hash set)
//   - Custom hash functions
//   - Collision handling: chaining vs open addressing
//   - Classic interview problems solved with hashing
//
// COMPILE & RUN:
//   g++ -std=c++17 01_hashmap_hashset.cpp -o out && ./out
//
// COMPLEXITY:
//   unordered_map insert/find/erase : O(1) average, O(n) worst
//   unordered_set insert/count/erase: O(1) average, O(n) worst
// ============================================================

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <map>           // for ordered comparison
#include <vector>
#include <string>
#include <algorithm>
#include <list>         // for chaining collision demo
using namespace std;

// ============================================================
// SECTION 1: HASHMAP (unordered_map) BASICS
// ============================================================
// unordered_map<K, V>: stores key-value pairs.
// hash(key) → bucket index → O(1) average access.
// Keys must be hashable (built-in types are by default).
// ------------------------------------------------------------ 

void demoHashMap() {
    cout << "=== HASHMAP (unordered_map) ===" << "\n";

    unordered_map<string, int> freq;

    // Insert / update — O(1) avg
    string sentence = "the cat sat on the mat the cat";
    for (auto word : {"the","cat","sat","on","the","mat","the","cat"})
        freq[word]++;  // operator[] creates entry with 0 if missing

    // Iterate (order NOT guaranteed)
    cout << "Word frequencies:\n";
    for (const auto& [word, count] : freq)
        cout << "  " << word << " → " << count << "\n";

    // find — O(1) avg; safer than operator[] (doesn't insert)
    auto it = freq.find("cat");
    if (it != freq.end())
        cout << "  find('cat') = " << it->second << "\n";

    // contains — C++20: freq.contains("sat")
    cout << "  count('sat'): " << freq.count("sat") << "\n";   // 1 or 0

    // erase
    freq.erase("on");
    cout << "  After erase('on'), size=" << freq.size() << "\n";

    // Load factor and rehashing
    cout << "  load_factor=" << freq.load_factor()
         << "  bucket_count=" << freq.bucket_count() << "\n";

    // Map from int to string
    unordered_map<int, string> idToName = {{1,"Alice"},{2,"Bob"},{3,"Carol"}};
    idToName[4] = "Dave";
    for (const auto& [id, name] : idToName)
        cout << "  " << id << " → " << name << "\n";
}

// ============================================================
// SECTION 2: HASHSET (unordered_set) BASICS
// ============================================================
// unordered_set<K>: stores unique keys only. No values.
// Use when you need:  "have I seen this before?"
// ------------------------------------------------------------ 

void demoHashSet() {
    cout << "\n=== HASHSET (unordered_set) ===" << "\n";

    unordered_set<int> seen;
    vector<int> nums = {4, 1, 2, 1, 3, 4, 2, 5};

    cout << "Unique elements: ";
    for (int x : nums) {
        if (!seen.count(x)) {    // O(1) membership check
            cout << x << " ";
            seen.insert(x);      // O(1) insert
        }
    }
    cout << "\n";

    cout << "  contains 3? " << (seen.count(3) ? "yes" : "no") << "\n";
    seen.erase(3);
    cout << "  after erase(3), contains 3? " << (seen.count(3) ? "yes" : "no") << "\n";
    cout << "  set size: " << seen.size() << "\n";
}

// ============================================================
// SECTION 3: CUSTOM HASH FUNCTION
// ============================================================
// For custom types as keys, define a hash struct.
// ------------------------------------------------------------ 

struct Point { int x, y; };

// Custom hash for Point (XOR combine x and y hashes)
struct PointHash {
    size_t operator()(const Point& p) const {
        return hash<int>()(p.x) ^ (hash<int>()(p.y) << 16);
    }
};

struct PointEqual {
    bool operator()(const Point& a, const Point& b) const {
        return a.x == b.x && a.y == b.y;
    }
};

void demoCustomHash() {
    cout << "\n=== CUSTOM HASH FUNCTION ===" << "\n";

    unordered_set<Point, PointHash, PointEqual> points;
    points.insert({1, 2});
    points.insert({3, 4});
    points.insert({1, 2});   // duplicate — ignored

    cout << "  Unique points: " << points.size() << "\n";   // 2

    unordered_map<Point, string, PointHash, PointEqual> labels;
    labels[{0, 0}] = "origin";
    labels[{1, 0}] = "x-axis";
    cout << "  (0,0) → " << labels[{0,0}] << "\n";
}

// ============================================================
// SECTION 4: COLLISION HANDLING — CHAINING (conceptual demo)
// ============================================================
// Chaining: each bucket is a linked list.
// Multiple keys that hash to same index form a chain.
// Load factor = n/m (n=keys, m=buckets).
// Low load factor → fewer collisions → closer to O(1).
// ------------------------------------------------------------ 

class ChainHashMap {
    static const int BUCKET_COUNT = 7;
    list<pair<int,string>> table_[BUCKET_COUNT];   // each bucket = linked list

    int hash(int key) const { return key % BUCKET_COUNT; }

public:
    void insert(int key, const string& val) {
        int idx = hash(key);
        for (auto& [k, v] : table_[idx]) {
            if (k == key) { v = val; return; }  // update existing
        }
        table_[idx].push_back({key, val});       // add new
    }

    string* find(int key) {
        int idx = hash(key);
        for (auto& [k, v] : table_[idx])
            if (k == key) return &v;
        return nullptr;
    }

    void printAll() const {
        cout << "  ChainHashMap buckets:\n";
        for (int i = 0; i < BUCKET_COUNT; i++) {
            if (!table_[i].empty()) {
                cout << "    [" << i << "]: ";
                for (const auto& [k, v] : table_[i])
                    cout << "(" << k << "," << v << ") ";
                cout << "\n";
            }
        }
    }
};

void demoChaining() {
    cout << "\n=== CHAINING (collision handling) ===" << "\n";
    ChainHashMap hm;
    // Keys 7 and 14 both hash to bucket 0 (7%7=0, 14%7=0) — collision!
    hm.insert(1,  "one");
    hm.insert(7,  "seven");
    hm.insert(14, "fourteen");   // collision with 7
    hm.insert(3,  "three");
    hm.insert(10, "ten");        // collision with 3
    hm.printAll();

    auto val = hm.find(14);
    cout << "  find(14): " << (val ? *val : "not found") << "\n";
    val = hm.find(99);
    cout << "  find(99): " << (val ? *val : "not found") << "\n";
}

// ============================================================
// SECTION 5: CLASSIC INTERVIEW PROBLEMS
// ============================================================

/** P1: Two Sum — find indices i,j where arr[i]+arr[j]==target. O(n) */
pair<int,int> twoSum(const vector<int>& arr, int target) {
    unordered_map<int,int> seen;  // value → index
    for (int i = 0; i < (int)arr.size(); i++) {
        int complement = target - arr[i];
        if (seen.count(complement)) return {seen[complement], i};
        seen[arr[i]] = i;
    }
    return {-1, -1};
}

/** P2: Longest consecutive sequence — O(n) */
int longestConsecutive(const vector<int>& nums) {
    unordered_set<int> s(nums.begin(), nums.end());
    int best = 0;
    for (int n : s) {
        if (!s.count(n - 1)) {          // n is the start of a sequence
            int curr = n, len = 1;
            while (s.count(curr + 1))  { curr++; len++; }
            best = max(best, len);
        }
    }
    return best;
}

/** P3: Group anagrams — O(n * L log L) */
vector<vector<string>> groupAnagrams(const vector<string>& words) {
    unordered_map<string, vector<string>> groups;
    for (const auto& w : words) {
        string key = w;
        sort(key.begin(), key.end());  // canonical sorted form
        groups[key].push_back(w);
    }
    vector<vector<string>> result;
    for (auto& [k, v] : groups) result.push_back(v);
    return result;
}

/** P4: Subarray sum equals k — O(n) using prefix sum + hash map */
int subarraySumK(const vector<int>& arr, int k) {
    unordered_map<int,int> prefixFreq;
    prefixFreq[0] = 1;     // empty prefix
    int sum = 0, count = 0;
    for (int x : arr) {
        sum += x;
        count += prefixFreq[sum - k];  // subarrays ending here with sum=k
        prefixFreq[sum]++;
    }
    return count;
}

// ============================================================
// MAIN
// ============================================================
int main() {
    demoHashMap();
    demoHashSet();
    demoCustomHash();
    demoChaining();

    cout << "\n=== INTERVIEW PROBLEMS ===" << "\n";

    // Two Sum
    vector<int> arr = {2, 7, 11, 15};
    auto [i, j] = twoSum(arr, 9);
    cout << "TwoSum([2,7,11,15], 9): indices [" << i << "," << j << "] → "
         << arr[i] << "+" << arr[j] << "=9\n";

    // Longest Consecutive
    vector<int> nums = {100, 4, 200, 1, 3, 2};
    cout << "Longest consecutive [100,4,200,1,3,2]: " << longestConsecutive(nums) << "\n";  // 4

    // Group Anagrams
    vector<string> words = {"eat","tea","tan","ate","nat","bat"};
    auto groups = groupAnagrams(words);
    cout << "Group anagrams:\n";
    for (auto& g : groups) {
        cout << "  [";
        for (int k = 0; k < (int)g.size(); k++) cout << g[k] << (k+1<(int)g.size()?",":"");
        cout << "]\n";
    }

    // Subarray Sum K
    vector<int> arr2 = {1, 1, 1};
    cout << "Subarray sum=2 in [1,1,1]: " << subarraySumK(arr2, 2) << "\n";  // 2

    vector<int> arr3 = {1, 2, 3, -1, 1, 4};
    cout << "Subarray sum=5 in [1,2,3,-1,1,4]: " << subarraySumK(arr3, 5) << "\n";  // 3

    return 0;
}

// ============================================================
// COMPLEXITY SUMMARY
//   unordered_map insert/find  : O(1) avg, O(n) worst (many collisions)
//   unordered_set insert/count : O(1) avg
//   Chaining (worst case)      : O(n) — all keys in one bucket
//   TwoSum                     : O(n)
//   LongestConsecutive         : O(n)
//   GroupAnagrams              : O(n * L log L) — L = avg word length
//   SubarraySumK               : O(n)
//
// CHAINING vs OPEN ADDRESSING:
//   Chaining        : uses linked list per bucket, handles high load factor
//   Open Addressing : uses same array, probes for empty slot on collision
//                     (Linear Probe, Quadratic Probe, Double Hashing)
// ============================================================
