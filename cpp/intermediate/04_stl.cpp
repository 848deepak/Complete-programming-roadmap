// ============================================================
// MODULE | C++ INTERMEDIATE → Standard Template Library (STL)
// ============================================================
// DESCRIPTION:
//   Complete guide to the most important STL containers and
//   algorithms: vector, list, stack, queue, map, unordered_map,
//   set, priority_queue, sort with custom comparator, and
//   common algorithms (find, count, accumulate, etc.)
//
// COMPILE & RUN:
//   g++ -std=c++17 04_stl.cpp -o out && ./out
//
// STL TABLE:
//   Container        | Underlying DS    | Access  | Insert  | Delete
//   --------------- -+------------------+---------+---------+-------
//   vector           | Dynamic array    | O(1)    | O(1)*   | O(n)
//   list             | Doubly LL        | O(n)    | O(1)    | O(1)
//   stack            | deque (default)  | O(1)    | O(1)    | O(1)
//   queue            | deque (default)  | O(1)    | O(1)    | O(1)
//   map              | Red-Black tree   | O(log n)| O(log n)| O(log n)
//   unordered_map    | Hash table       | O(1)*   | O(1)*   | O(1)*
//   set              | Red-Black tree   | O(log n)| O(log n)| O(log n)
//   priority_queue   | Binary heap      | O(1)    | O(log n)| O(log n)
//   (* amortized)
// ============================================================

#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>    // sort, find, count, reverse, min_element, etc.
#include <numeric>      // accumulate, iota
#include <string>
#include <functional>   // greater<T>
using namespace std;

// ============================================================
// HELPER: Print any iterable container
// ============================================================
template<typename Container>
void printAll(const string& label, const Container& c) {
    cout << label << ": [ ";
    for (const auto& x : c) cout << x << " ";
    cout << "]\n";
}

// ============================================================
// SECTION 1: std::vector
// ============================================================
// Dynamic array. Best for random access and push_back.
// Resizes automatically (doubles capacity when full).
// ------------------------------------------------------------ 
void demonstrateVector() {
    cout << "\n=== std::vector ===" << endl;

    vector<int> v;              // empty vector, size=0, capacity=0
    v.reserve(10);              // pre-allocate space to avoid reallocations

    // Push elements
    for (int i = 1; i <= 6; i++) v.push_back(i * 10);
    printAll("initial", v);     // [10 20 30 40 50 60]

    // Access — O(1)
    cout << "v[0]=" << v[0] << "  v.front()=" << v.front() << "  v.back()=" << v.back() << "\n";

    // Insert at position (O(n) — shifts elements)
    v.insert(v.begin() + 2, 99);   // insert 99 at index 2
    printAll("after insert(idx=2, 99)", v);

    // Erase at position (O(n) — shifts elements)
    v.erase(v.begin() + 2);        // remove element at index 2
    printAll("after erase(idx=2)", v);

    // pop_back — O(1)
    v.pop_back();
    printAll("after pop_back", v);

    // Sort (can sort in-place)
    vector<int> unsorted = {5, 3, 8, 1, 9, 2};
    sort(unsorted.begin(), unsorted.end());              // ascending
    printAll("sorted ascending", unsorted);

    sort(unsorted.begin(), unsorted.end(), greater<int>()); // descending
    printAll("sorted descending", unsorted);

    // Custom sort: sort pairs by second element
    vector<pair<string,int>> people = {{"Alice",30},{"Bob",25},{"Carol",35}};
    sort(people.begin(), people.end(),
        [](const auto& a, const auto& b){ return a.second < b.second; });
    cout << "Sorted by age: ";
    for (auto& [name, age] : people) cout << name << "(" << age << ") ";
    cout << "\n";

    // Size & capacity
    cout << "size=" << v.size() << "  capacity=" << v.capacity() << "\n";
}

// ============================================================
// SECTION 2: std::list (Doubly Linked List)
// ============================================================
// O(1) insert/delete anywhere when you have an iterator.
// No random access — no operator[].
// ------------------------------------------------------------ 
void demonstrateList() {
    cout << "\n=== std::list ===" << endl;

    list<int> lst = {10, 20, 30, 40, 50};
    printAll("initial", lst);

    lst.push_front(5);        // O(1) prepend
    lst.push_back(60);        // O(1) append
    printAll("after push_front(5) + push_back(60)", lst);

    lst.remove(30);           // O(n) remove all elements with value 30
    printAll("after remove(30)", lst);

    lst.sort();               // O(n log n) — mergesort, stable
    printAll("after sort", lst);

    lst.reverse();            // O(n) — reverses in-place
    printAll("after reverse", lst);
}

// ============================================================
// SECTION 3: std::stack (LIFO) & std::queue (FIFO)
// ============================================================
void demonstrateStackQueue() {
    cout << "\n=== std::stack (LIFO) ===" << endl;

    stack<string> stk;
    stk.push("first");
    stk.push("second");
    stk.push("third");

    cout << "stack size=" << stk.size() << "  top=" << stk.top() << "\n";
    while (!stk.empty()) {
        cout << "pop: " << stk.top() << "\n";
        stk.pop();
    }

    cout << "\n=== std::queue (FIFO) ===" << endl;

    queue<int> q;
    for (int i = 1; i <= 5; i++) q.push(i * 10);
    cout << "queue size=" << q.size() << "  front=" << q.front() << "  back=" << q.back() << "\n";

    while (!q.empty()) {
        cout << "dequeue: " << q.front() << "\n";
        q.pop();    // removes from front
    }
}

// ============================================================
// SECTION 4: std::map (Ordered Key-Value Store)
// ============================================================
// Internally a Red-Black tree. Keys are SORTED automatically.
// Use when you need ORDERED iteration over keys.
// ------------------------------------------------------------ 
void demonstrateMap() {
    cout << "\n=== std::map ===" << endl;

    map<string, int> wordCount;

    // Insert / update — O(log n)
    string text = "the cat sat on the mat the cat";
    for (const string& w : {"the","cat","sat","on","the","mat","the","cat"}) {
        wordCount[w]++;     // operator[] inserts with default value (0) if key missing
    }

    // Ordered iteration (sorted by key alphabetically)
    cout << "Word frequencies (sorted by key):\n";
    for (const auto& [word, count] : wordCount) {
        cout << "  " << word << " → " << count << "\n";
    }

    // find — O(log n), safer than operator[]
    auto it = wordCount.find("cat");
    if (it != wordCount.end())
        cout << "Found 'cat': " << it->second << " times\n";
    else
        cout << "'cat' not found\n";

    // erase
    wordCount.erase("sat");
    cout << "After erase('sat'), size=" << wordCount.size() << "\n";

    // count — O(log n) — returns 1 if key exists, 0 otherwise
    cout << "contains 'on': " << (wordCount.count("on") ? "yes" : "no") << "\n";
}

// ============================================================
// SECTION 5: std::unordered_map (Hash Map)
// ============================================================
// Average O(1) for insert/find/erase.
// Keys are NOT sorted — use when order doesn't matter.
// Worst case O(n) if too many hash collisions.
// ------------------------------------------------------------ 
void demonstrateUnorderedMap() {
    cout << "\n=== std::unordered_map ===" << endl;

    unordered_map<int, string> idToName = {
        {101, "Alice"},
        {202, "Bob"},
        {303, "Carol"}
    };

    // O(1) average lookup
    if (idToName.count(202)) {
        cout << "ID 202 → " << idToName[202] << "\n";
    }

    idToName[404] = "Dave";                   // insert new key
    idToName.erase(101);                      // erase by key
    cout << "After insert+erase, size=" << idToName.size() << "\n";

    // Iterate (order is NOT guaranteed)
    for (const auto& [id, name] : idToName)
        cout << "  " << id << " → " << name << "\n";
}

// ============================================================
// SECTION 6: std::set & std::unordered_set
// ============================================================
// set: Sorted unique elements (Red-Black tree)
// unordered_set: Unique elements in hash table, O(1) avg ops
// ------------------------------------------------------------ 
void demonstrateSet() {
    cout << "\n=== std::set ===" << endl;

    set<int> s = {5, 3, 8, 1, 9, 3, 5};   // duplicates ignored!
    printAll("set (unique + sorted)", s);   // {1,3,5,8,9}

    s.insert(4);
    s.insert(3);    // ignored — already exists
    printAll("after insert(4), insert(3 dup)", s);

    cout << "contains 8: " << (s.count(8) ? "yes" : "no") << "\n";
    s.erase(8);
    cout << "after erase(8): ";
    for (int x : s) cout << x << " ";
    cout << "\n";

    // unordered_set
    cout << "\n=== std::unordered_set ===" << endl;
    unordered_set<string> visited;
    for (auto& url : {"a.com","b.com","a.com","c.com"}) {
        if (!visited.count(url)) {
            visited.insert(url);
            cout << "Visiting: " << url << "\n";
        } else {
            cout << "Already visited: " << url << "\n";
        }
    }
}

// ============================================================
// SECTION 7: std::priority_queue
// ============================================================
// Binary heap. By default: MAX heap (largest element at top).
// priority_queue<T, vector<T>, greater<T>> → MIN heap.
// ------------------------------------------------------------ 
void demonstratePriorityQueue() {
    cout << "\n=== std::priority_queue ===" << endl;

    // Max heap (default)
    priority_queue<int> maxHeap;
    for (int x : {4, 1, 7, 3, 9, 2}) maxHeap.push(x);
    cout << "Max heap — top (max): " << maxHeap.top() << "\n";
    cout << "Popping: ";
    while (!maxHeap.empty()) {
        cout << maxHeap.top() << " ";
        maxHeap.pop();
    }
    cout << "\n";

    // Min heap
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (int x : {4, 1, 7, 3, 9, 2}) minHeap.push(x);
    cout << "Min heap — top (min): " << minHeap.top() << "\n";
    cout << "Popping: ";
    while (!minHeap.empty()) {
        cout << minHeap.top() << " ";
        minHeap.pop();
    }
    cout << "\n";

    // Custom comparator with pairs: sort by second element (min priority)
    using P = pair<int,string>;
    auto cmp = [](const P& a, const P& b){ return a.first > b.first; }; // min-heap on first
    priority_queue<P, vector<P>, decltype(cmp)> taskQueue(cmp);
    taskQueue.push({3, "medium priority"});
    taskQueue.push({1, "high priority"});
    taskQueue.push({5, "low priority"});
    cout << "Task queue (by priority):\n";
    while (!taskQueue.empty()) {
        auto [pri, task] = taskQueue.top(); taskQueue.pop();
        cout << "  priority=" << pri << " → " << task << "\n";
    }
}

// ============================================================
// SECTION 8: <algorithm> UTILITIES
// ============================================================
void demonstrateAlgorithms() {
    cout << "\n=== <algorithm> UTILITIES ===" << endl;

    vector<int> v = {5, 3, 8, 1, 9, 2, 7, 4, 6};

    // accumulate — sum all elements — O(n)
    int total = accumulate(v.begin(), v.end(), 0);
    cout << "sum = " << total << "\n";

    // min_element / max_element — O(n)
    cout << "min = " << *min_element(v.begin(), v.end()) << "\n";
    cout << "max = " << *max_element(v.begin(), v.end()) << "\n";

    // find — O(n) linear search
    auto it = find(v.begin(), v.end(), 8);
    cout << "find(8): " << (it != v.end() ? "found at index "+to_string(it-v.begin()) : "not found") << "\n";

    // count — O(n) count occurrences
    vector<int> v2 = {1, 2, 2, 3, 2, 4};
    cout << "count(2) in {1,2,2,3,2,4}: " << count(v2.begin(), v2.end(), 2) << "\n";

    // count_if — O(n) count elements matching predicate
    int evens = count_if(v.begin(), v.end(), [](int x){ return x % 2 == 0; });
    cout << "count even numbers: " << evens << "\n";

    // reverse — O(n)
    vector<int> rv = {1, 2, 3, 4, 5};
    reverse(rv.begin(), rv.end());
    printAll("reversed", rv);

    // binary_search + lower_bound (requires sorted input) — O(log n)
    vector<int> sorted = {1, 3, 5, 7, 9, 11};
    cout << "binary_search(7): " << (binary_search(sorted.begin(), sorted.end(), 7) ? "found" : "not found") << "\n";
    auto lb = lower_bound(sorted.begin(), sorted.end(), 6);  // first element >= 6
    cout << "lower_bound(6) points to: " << *lb << "\n";

    // unique — removes CONSECUTIVE duplicates (sort first!) — O(n)
    vector<int> dup = {1, 1, 2, 3, 3, 3, 4, 5, 5};
    auto newEnd = unique(dup.begin(), dup.end());
    dup.erase(newEnd, dup.end());       // erase "garbage" at end
    printAll("unique (deduplicated)", dup);

    // fill + iota
    vector<int> filled(5);
    iota(filled.begin(), filled.end(), 1);  // fill with 1,2,3,4,5
    printAll("iota (1..5)", filled);
}

// ============================================================
// MAIN
// ============================================================
int main() {
    demonstrateVector();
    demonstrateList();
    demonstrateStackQueue();
    demonstrateMap();
    demonstrateUnorderedMap();
    demonstrateSet();
    demonstratePriorityQueue();
    demonstrateAlgorithms();
    return 0;
}

// ============================================================
// COMPLEXITY SUMMARY
//   vector     : access O(1), push_back O(1) amortized, insert/erase O(n)
//   list       : access O(n), insert/erase at iter O(1)
//   map        : all key ops O(log n), ordered iteration
//   unordered_map : all key ops O(1) avg, O(n) worst
//   set        : all ops O(log n), ordered, unique
//   prio_queue : top O(1), push/pop O(log n)
//   sort       : O(n log n) average (introsort)
//   find       : O(n), binary_search O(log n) on sorted range
// ============================================================
