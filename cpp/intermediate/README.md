# C++ Intermediate

> **Folder:** `cpp/intermediate/` | **Level:** Intermediate  
> **Files:** `01_pointers_references.cpp` · `02_exception_handling.cpp` · `03_file_handling.cpp` · `04_stl.cpp` · `05_structures.cpp`

---

## 1. Introduction

This module bridges the gap between basic C++ and full OOP. It covers the features that make C++ powerful and often tricky: manual memory management with pointers, safe exception handling, file I/O, the entire Standard Template Library, and user-defined aggregate types (structs). These topics are heavily tested in interviews and essential for writing production-quality C++ code.

> **Compile any file:**
> ```bash
> g++ -std=c++17 <filename>.cpp -o out && ./out
> ```

---

## 2. Core Concepts

### 2.1 Pointers & References (`01_pointers_references.cpp`)

#### What is a Pointer?
A **pointer** is a variable that stores a **memory address**. It does NOT store a value — it stores where a value lives.

```cpp
int x = 42;
int* ptr = &x;   // ptr holds the ADDRESS of x

cout << *ptr;    // dereference: read value at that address → 42
*ptr = 99;       // modify x through the pointer
```

#### Pointer Arithmetic
When you increment a pointer, it moves by `sizeof(element)` bytes — not by 1 byte:
```cpp
int arr[] = {10, 20, 30, 40, 50};
int* p = arr;           // points to arr[0]
*(p + 2);               // accesses arr[2] = 30
```

#### References
A **reference** is an alias — an alternative name for an existing variable. Key rules:
- Must be initialized at declaration
- Cannot be re-bound to a different variable after initialization
- No null reference (unlike pointers)

```cpp
int val = 10;
int& ref = val;   // ref IS val — same memory location
ref = 50;         // val is now 50
&val == &ref;     // true — same address
```

#### Pointer vs Reference: When to Use

| | Pointer | Reference |
|--|---------|-----------|
| Can be null | Yes (`nullptr`) | No |
| Rebindable | Yes | No |
| Syntax | `*` dereference, `->` member | Transparent — same as original |
| Use case | Ownership, nullable, reallocation | Function params, aliases |
| Preferred in | C-style APIs, dynamic memory | C++ functions, return values |

#### Pointer-to-Function
```cpp
int (*op)(int, int);   // declare function pointer: (int,int)→int
op = add;              // point to function 'add'
op(3, 4);              // call through pointer → 7
op = mul;              // reassign to 'mul'
```

#### Dynamic Memory: `new` / `delete`
```cpp
int* dyn = new int(777);   // heap allocation
delete dyn;                // MUST free — else memory leak
dyn = nullptr;             // prevent dangling pointer

int* arr = new int[5];     // dynamic array
delete[] arr;              // note: delete[] for arrays
arr = nullptr;
```

#### Smart Pointers (C++11) — RAII Wrappers
Smart pointers automatically free memory when they go out of scope:

| Smart Pointer | Ownership | Copyable | When to Use |
|---------------|-----------|----------|-------------|
| `unique_ptr` | Exclusive (one owner) | No (only movable) | Default choice — sole ownership |
| `shared_ptr` | Shared (reference counted) | Yes | Multiple owners needed |
| `weak_ptr` | Non-owning observer | Yes | Break circular references |

```cpp
auto uptr = make_unique<Resource>("File");   // created
uptr->use();
// automatically deleted when uptr goes out of scope

auto sp1 = make_shared<Resource>("DB");
auto sp2 = sp1;                              // use_count = 2
// destroyed when ALL shared_ptrs go out of scope
```

#### `nullptr` (C++11)
Always prefer `nullptr` over `NULL` or `0`:
```cpp
int* p = nullptr;
if (p != nullptr) { *p; }  // safe — always check before dereferencing
```
`nullptr` is type-safe — `NULL` is just `0` and can cause ambiguous overloads.

---

### 2.2 Exception Handling (`02_exception_handling.cpp`)

#### Basic Mechanism
```
try { /* code that might throw */ }
catch (const ExceptionType& e) { /* handle */ }
throw ExceptionObject;   /* signal error */
```

#### Standard Exception Hierarchy
```
std::exception
├── std::logic_error
│   ├── std::invalid_argument   (bad function argument)
│   ├── std::domain_error       (math domain error)
│   ├── std::length_error       (exceeds max length)
│   └── std::out_of_range       (index out of range)
└── std::runtime_error
    ├── std::range_error
    ├── std::overflow_error
    └── std::underflow_error
```

**Always catch by `const` reference** to avoid slicing and unnecessary copying:
```cpp
catch (const std::out_of_range& e) { cout << e.what(); }
catch (const std::exception& e)    { /* catches all above */ }
catch (...)                        { /* catch-all — last resort */ }
```

#### Catch Order Rule
**Most specific → Least specific.** C++ uses the first matching `catch`:
```cpp
catch (const invalid_argument& e) { ... }  // most specific
catch (const runtime_error& e)    { ... }
catch (const exception& e)        { ... }  // least specific
catch (...)                       { ... }  // absolute catch-all
```

#### Custom Exceptions
Inherit from `std::runtime_error` for custom exceptions with a message:
```cpp
class NegativeAmountException : public runtime_error {
    double amount_;
public:
    explicit NegativeAmountException(double amt)
        : runtime_error("Amount cannot be negative: " + to_string(amt))
        , amount_(amt) {}
    double amount() const { return amount_; }
};
```

#### Re-throwing
Use bare `throw;` (not `throw e;`) to re-throw — preserves the original exception type:
```cpp
catch (const exception& e) {
    log(e.what());
    throw;   // re-throws original, not a copy (preserves type)
}
```

#### `noexcept`
Declares a function will never throw. If it does, `std::terminate()` is called:
```cpp
int safeAdd(int a, int b) noexcept { return a + b; }
```
Use `noexcept` on: destructors, move constructors/assignment, and pure utility functions.

#### RAII — Exception Safety
**RAII (Resource Acquisition Is Initialization):** Destructors always run — even when an exception is thrown. This guarantees cleanup:
```cpp
class FileGuard {
    ~FileGuard() { /* always runs, even on exception */ close(file_); }
};

try {
    FileGuard guard("report.txt");    // file opened
    throw runtime_error("Disk full"); // exception thrown
    // FileGuard destructor fires here BEFORE catch — file closed safely
} catch (...) { ... }
```
Smart pointers (`unique_ptr`, `shared_ptr`) are the standard RAII tool for memory.

---

### 2.3 File Handling (`03_file_handling.cpp`)

#### Stream Types

| Class | Direction | Default Mode |
|-------|-----------|-------------|
| `ifstream` | Input (read) | `ios::in` |
| `ofstream` | Output (write) | `ios::out` (truncates) |
| `fstream` | Both read + write | Must specify |

#### Open Mode Flags

| Flag | Meaning |
|------|---------|
| `ios::in` | Read mode |
| `ios::out` | Write mode (truncates existing content) |
| `ios::app` | Append mode (never truncates) |
| `ios::binary` | Binary mode (no newline conversion) |
| `ios::ate` | Start at end of file on open |

#### Text File Operations
```cpp
// Write
ofstream outFile("demo.txt");
if (!outFile.is_open()) throw runtime_error("cannot open");
outFile << "Hello\n";
outFile.close();

// Read line by line
ifstream inFile("demo.txt");
string line;
while (getline(inFile, line)) { /* process line */ }

// Append
ofstream appFile("demo.txt", ios::app);
appFile << "new line\n";
```

#### Stream State Flags
```cpp
f.good()   // no errors at all
f.eof()    // end-of-file reached
f.fail()   // logical I/O failure (e.g. parse error)
f.bad()    // hardware-level read/write failure
```
Always check `!f` or `!f.is_open()` after opening.

#### CSV Parsing
```cpp
while (getline(file, line)) {
    stringstream ss(line);
    string token;
    getline(ss, token, ',');  s.name = token;
    getline(ss, token, ',');  s.age  = stoi(token);
    getline(ss, token, ',');  s.gpa  = stod(token);
}
```

#### Binary File I/O
```cpp
// Write struct to binary
ofstream f("data.bin", ios::binary);
f.write(reinterpret_cast<const char*>(&record), sizeof(Record));

// Read struct from binary
ifstream f("data.bin", ios::binary);
f.read(reinterpret_cast<char*>(&record), sizeof(Record));
```

#### Get File Size
```cpp
ifstream f(filename, ios::binary | ios::ate);  // open, seek to end
long size = (long)f.tellg();                   // position = size
```

---

### 2.4 STL — Standard Template Library (`04_stl.cpp`)

#### Container Complexity Overview

| Container | Underlying DS | Access | Insert | Erase | Ordered? | Unique? |
|-----------|--------------|--------|--------|-------|----------|---------|
| `vector` | Dynamic array | O(1) | O(1)* | O(n) | Yes (by index) | No |
| `list` | Doubly linked list | O(n) | O(1) | O(1) | Yes (by order) | No |
| `stack` | deque adapter | O(1) top | O(1) | O(1) | LIFO | No |
| `queue` | deque adapter | O(1) front | O(1) | O(1) | FIFO | No |
| `map` | Red-Black tree | O(log n) | O(log n) | O(log n) | Yes (by key) | Keys yes |
| `unordered_map` | Hash table | O(1)* | O(1)* | O(1)* | No | Keys yes |
| `set` | Red-Black tree | O(log n) | O(log n) | O(log n) | Yes | Yes |
| `unordered_set` | Hash table | O(1)* | O(1)* | O(1)* | No | Yes |
| `priority_queue` | Binary heap | O(1) top | O(log n) | O(log n) | Heap | No |

> `*` = amortized

#### `std::vector`
```cpp
vector<int> v;
v.reserve(10);           // pre-allocate to avoid reallocations
v.push_back(42);         // O(1) amortized
v.insert(v.begin()+2, 99); // O(n) — shifts elements right
v.erase(v.begin()+2);    // O(n) — shifts elements left
v.pop_back();            // O(1)
sort(v.begin(), v.end()); // in-place sort — O(n log n)

// Custom sort with lambda
sort(v.begin(), v.end(), [](int a, int b){ return a > b; }); // descending
```

#### `std::list`
```cpp
list<int> lst = {10, 20, 30};
lst.push_front(5);    // O(1) prepend
lst.push_back(40);    // O(1) append
lst.remove(20);       // O(n) — removes ALL occurrences of 20
lst.sort();           // O(n log n) stable mergesort
lst.reverse();        // O(n) in-place
// No random access — use iterators
```

#### `std::stack` and `std::queue`
```cpp
// Stack — LIFO
stack<string> stk;
stk.push("A"); stk.push("B");
stk.top();   // peek — "B"
stk.pop();   // remove top

// Queue — FIFO
queue<int> q;
q.push(10); q.push(20);
q.front();  // peek front — 10
q.back();   // peek back — 20
q.pop();    // remove from front
```

#### `std::map` vs `std::unordered_map`
```cpp
// map: sorted keys, O(log n) ops
map<string, int> freq;
freq["the"]++;          // inserts with default 0 if missing
freq.find("the");       // O(log n) — returns iterator or end()
freq.count("the");      // returns 1 if exists, 0 if not
freq.erase("the");      // O(log n)
// Iteration is SORTED by key

// unordered_map: O(1) avg, unsorted
unordered_map<int, string> idMap;
idMap[101] = "Alice";   // O(1) avg insert
idMap.count(101);       // O(1) avg lookup
// Iteration order is NOT guaranteed
```

#### `std::set` and `std::unordered_set`
```cpp
set<int> s = {5,3,8,1,9,3,5};  // {1,3,5,8,9} — sorted, no duplicates
s.insert(4);    // O(log n), ignored if already exists
s.count(8);     // 1 if present, 0 if not — O(log n)
s.erase(8);     // O(log n)

unordered_set<string> visited;
visited.insert("url.com");       // O(1) avg
visited.count("url.com");        // O(1) avg — use for dedup or visited tracking
```

#### `std::priority_queue`
```cpp
// Max heap (default)
priority_queue<int> maxPQ;
maxPQ.push(5); maxPQ.top(); // 5

// Min heap
priority_queue<int, vector<int>, greater<int>> minPQ;

// Custom comparator
auto cmp = [](pair<int,string> a, pair<int,string> b){ return a.first > b.first; };
priority_queue<pair<int,string>, vector<pair<int,string>>, decltype(cmp)> pq(cmp);
```

#### `<algorithm>` Utilities

| Function | Description | Complexity |
|----------|-------------|------------|
| `sort(b,e)` | Sort range | O(n log n) |
| `reverse(b,e)` | Reverse range in-place | O(n) |
| `find(b,e,val)` | Linear search | O(n) |
| `count(b,e,val)` | Count occurrences | O(n) |
| `count_if(b,e,pred)` | Count matching predicate | O(n) |
| `accumulate(b,e,init)` | Sum (or fold) | O(n) |
| `min_element(b,e)` | Pointer to minimum | O(n) |
| `max_element(b,e)` | Pointer to maximum | O(n) |
| `binary_search(b,e,val)` | Check if sorted range has val | O(log n) |
| `lower_bound(b,e,val)` | First element ≥ val | O(log n) |
| `upper_bound(b,e,val)` | First element > val | O(log n) |
| `unique(b,e)` | Remove consecutive duplicates | O(n) |
| `iota(b,e,start)` | Fill with incrementing values | O(n) |

---

### 2.5 Structures (`05_structures.cpp`)

#### What is a `struct`?
A `struct` groups multiple related variables (members) under one name. All members are **public by default**.

```cpp
struct Point {
    double x;
    double y;
};
Point p1 = {3.0, 4.0};   // aggregate initialization
```

#### Pointer to Struct — `->` Operator
```cpp
Point* ptr = new Point{6.0, 8.0};
ptr->x;        // shorthand for (*ptr).x
(*ptr).y;      // equivalent, less readable
delete ptr;
```

#### Nested Structs
```cpp
struct Address { string city; int pincode; };
struct Student {
    int     rollNo;
    string  name;
    Address addr;      // nested struct
};
Student s1 = {101, "Deepak", {"Delhi", 110001}};
s1.addr.city;          // access nested member
```

#### Struct with Member Functions (C++)
Unlike C, C++ structs can have constructors and methods:
```cpp
struct Rectangle {
    double length, width;
    Rectangle(double l, double w) : length(l), width(w) {}
    double area()      const { return length * width; }
    double perimeter() const { return 2 * (length + width); }
    void scale(double f)    { length *= f; width *= f; }
};
```

#### `typedef` and `using`
```cpp
// C-style typedef
typedef struct { int id; float salary; } Employee;

// Modern C++ equivalent
using Employee = struct { int id; float salary; };
```

#### `struct` vs `class`
| | `struct` | `class` |
|--|----------|---------|
| Default access | `public` | `private` |
| Everything else | Identical | Identical |
| Convention | Plain data containers | Encapsulated objects with logic |

---

## 3. Internal Working

### Stack Unwinding (Exception Handling)
When an exception is thrown, C++ **unwinds** the call stack — destroying local objects (calling destructors) in reverse order of construction. This is why RAII works: destructors are guaranteed to run before the `catch` block.

### `vector` Capacity Growth
A `vector` doubles its capacity when full (`push_back` triggers a reallocation). This gives **amortized O(1)** for `push_back`. Use `v.reserve(n)` to pre-allocate and avoid reallocations.

### Hash Tables (`unordered_map`/`unordered_set`)
- Average O(1) operations depend on a good hash function.
- Worst case is O(n) when many keys collide in the same bucket.
- Do not use `unordered_map` when key ordering matters.

### Memory Layout of a Struct
Struct members are laid in memory in declaration order. Padding bytes may be added between members for alignment:
```cpp
struct { char c; int n; };  // 1 byte for c + 3 bytes padding + 4 bytes for n = 8 bytes total
```

---

## 4. Operations & Techniques

### Choosing the Right Container

```
Need fast random access?     → vector
Need fast front/back insert? → deque or list
Need key-value lookup?       → map (ordered) or unordered_map (faster)
Need uniqueness + order?     → set
Need uniqueness + speed?     → unordered_set
Need LIFO?                   → stack
Need FIFO?                   → queue
Need priority ordering?      → priority_queue
```

### Exception-Safe Code Pattern
```cpp
// Always: RAII over manual cleanup
auto resource = make_unique<Resource>();   // auto-freed

// Always: validate inputs and throw descriptive exceptions
double safeDivide(double a, double b) {
    if (b == 0) throw invalid_argument("Divisor cannot be zero");
    return a / b;
}
```

---

## 5. Time & Space Complexity Table

| Operation | Time | Space | File |
|-----------|------|-------|------|
| Pointer dereference | O(1) | O(1) | `01_pointers_references` |
| `new` / `delete` | O(1) amortized | O(1) | `01_pointers_references` |
| `shared_ptr` copy | O(1) | O(1) | `01_pointers_references` |
| try-catch (no throw) | O(1) | O(1) | `02_exception_handling` |
| Exception throw+catch | O(call depth) | O(stack) | `02_exception_handling` |
| Write n lines to file | O(n) | O(1) | `03_file_handling` |
| Read n lines from file | O(n) | O(n) | `03_file_handling` |
| File size query | O(1) | O(1) | `03_file_handling` |
| vector push_back | O(1) amortized | O(1) | `04_stl` |
| vector insert/erase | O(n) | O(1) | `04_stl` |
| map insert/find/erase | O(log n) | O(1) | `04_stl` |
| unordered_map ops | O(1) avg | O(1) | `04_stl` |
| priority_queue push/pop | O(log n) | O(1) | `04_stl` |
| sort (STL) | O(n log n) | O(log n) | `04_stl` |
| binary_search | O(log n) | O(1) | `04_stl` |
| Struct member access | O(1) | O(1) | `05_structures` |

---

## 6. Common Mistakes

### Pointers & Memory
- **Dereferencing `nullptr`** → segmentation fault. Always check before dereferencing.
- **Forgetting `delete[]`** for arrays (using `delete` instead) → undefined behavior.
- **Double-free** (calling `delete` twice on same pointer) → undefined behavior.
- **Dangling pointer** (using a pointer after `delete`) → undefined behavior. Set to `nullptr` after deleting.
- **Using raw pointers** when smart pointers would do → resource leaks on exceptions.

### Exception Handling
- **Catching by value** (`catch (exception e)`) causes **object slicing** — lose derived class info. Always catch by `const&`.
- **Most-specific catch after least-specific** → more specific catches are never reached.
- **Throwing from a destructor** → if already unwinding, calls `std::terminate()`.
- **Empty catch block** (`catch(...) {}`) silently ignores errors — hard to debug.
- **Using `throw e;` instead of `throw;`** to re-throw → creates a copy (loses derived type).

### File Handling
- **Not checking if file opened** → operating on a bad stream produces silent failures.
- **Not closing files** → data may not be flushed to disk (though destructor closes it).
- **Mixing `cin >>` with `getline`** → leftover newline in buffer causes `getline` to read an empty string. Fix: `cin.ignore()` before `getline`.
- **Forgetting to skip CSV header row** before parsing data rows.

### STL
- **`map::operator[]` creates a default entry** if key doesn't exist. Use `.find()` when you only want to read.
- **Invalidating iterators** by inserting into a `vector` mid-iteration.
- **`unique()` expects sorted input** — it only removes consecutive duplicates.
- **`list` has no `operator[]`** — no random access by index.
- **`priority_queue` has no `begin()`/`end()`** iterators — you can only access `.top()`.

---

## 7. Interview Relevance

| Topic | Common Questions |
|-------|-----------------|
| Pointers | "What is a dangling pointer? How do you prevent it?" |
| Smart pointers | "Difference between `unique_ptr` and `shared_ptr`? When does `shared_ptr` destroy?" |
| References | "Can you have a null reference? Can you re-bind a reference?" |
| RAII | "What is RAII? Why is it important for exception safety?" |
| Exceptions | "What is stack unwinding? What is the difference between `throw` and `throw e`?" |
| STL containers | "When would you use `map` vs `unordered_map`?" |
| vector | "How does `vector` resize? What is amortized O(1) for push_back?" |
| priority_queue | "How do you create a min-heap using `priority_queue`?" |
| File I/O | "How do you read a CSV file in C++?" |
| Struct vs class | "What is the only difference between struct and class in C++?" |

**Key points to mention:**
- Always prefer smart pointers over raw `new`/`delete`.
- `vector` is O(1) amortized for push_back, not O(1) worst case.
- `map` maintains sorted order; `unordered_map` does not.
- Exception safety levels: no-throw, basic guarantee, strong guarantee.

---

## 8. Best Practices (C++ Specific)

### Memory Management
```cpp
// ✅ Always prefer smart pointers
auto ptr = make_unique<MyClass>(args...);

// ❌ Avoid raw new/delete
MyClass* ptr = new MyClass(args...);
delete ptr;

// ✅ Use make_shared (single allocation for object + control block)
auto sp = make_shared<MyClass>(args...);
```

### STL Best Practices
```cpp
// ✅ Reserve vector capacity when size is known
v.reserve(expectedSize);

// ✅ Use emplace_back to construct in-place (avoids copy)
v.emplace_back(args...);

// ✅ Use find() for map lookup, not operator[]
if (auto it = m.find(key); it != m.end()) { use(it->second); }

// ✅ Always sort before using binary_search / unique
sort(v.begin(), v.end());
auto end = unique(v.begin(), v.end());
v.erase(end, v.end());
```

### Exception Best Practices
```cpp
// ✅ Catch by const reference
catch (const std::exception& e) { log(e.what()); }

// ✅ noexcept on destructors and move operations
~MyClass() noexcept { ... }
MyClass(MyClass&&) noexcept = default;

// ✅ Never throw from destructors
~MyClass() noexcept { try { cleanup(); } catch(...) {} }
```

### File Handling
```cpp
// ✅ Always check open status
if (!file.is_open()) throw runtime_error("cannot open " + filename);

// ✅ Files close automatically via RAII (ifstream/ofstream destructor)
{
    ifstream f("data.txt");
    // f closed automatically at end of block
}
```

---

## 9. Summary

```
cpp/intermediate/ — What's Covered
├── 01_pointers_references.cpp
│   → Raw pointers, pointer arithmetic, references, swap (ptr vs ref),
│     dynamic memory (new/delete), unique_ptr, shared_ptr, function pointers, nullptr
│
├── 02_exception_handling.cpp
│   → try-catch-throw, std::exception hierarchy, custom exceptions,
│     multiple catch blocks, catch order, re-throw, noexcept, RAII,
│     unique_ptr + exception safety
│
├── 03_file_handling.cpp
│   → ofstream/ifstream/fstream, text read/write, append (ios::app),
│     word count, file size, CSV parsing with stringstream,
│     binary file I/O (read/write structs), stream state flags
│
├── 04_stl.cpp
│   → vector, list, stack, queue, map, unordered_map, set, unordered_set,
│     priority_queue (max+min heap, custom comparator),
│     algorithm: sort, find, count, count_if, accumulate, binary_search,
│     lower_bound, unique, reverse, iota
│
└── 05_structures.cpp
    → Basic struct, pointer to struct (->), nested structs, array of structs,
      struct with member functions and constructor, typedef vs using, struct vs class
```

**Key Takeaways:**
- **Smart pointers** eliminate the most dangerous category of C++ bugs (memory leaks, dangling pointers, double-frees).
- **RAII** is the cornerstone of exception-safe C++ — destructors guarantee cleanup.
- **`map` vs `unordered_map`** is one of the most common interview decisions — choose based on whether you need ordering.
- **`vector` is the default container** — only switch to others when you have a specific reason.
- **STL algorithms + lambdas** make code expressive and correct — prefer them over hand-written loops.

---

> **Next Steps:** Head to `cpp/oops/` for classes, encapsulation, inheritance, polymorphism, and virtual functions.
