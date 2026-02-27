# C++ Advanced

> **Folder:** `cpp/advanced/` | **Level:** Advanced  
> **Files:** `01_advanced.cpp` · `modern-cpp-features.md`

---

## 1. Introduction

This module covers the features that distinguish **modern C++ (C++11/14/17)** from classical C++. These topics make C++ safer, faster, and more expressive: generic programming with templates, zero-cost move semantics, type-safe alternatives to raw pointers and unions, compile-time computation with `constexpr`, and native multithreading. These are the features that appear in production codebases and advanced interviews.

> **Compile:**
> ```bash
> g++ -std=c++17 -pthread 01_advanced.cpp -o out && ./out
> ```

---

## 2. Core Concepts

### 2.1 Function Templates

Templates let you write **type-generic** code. The compiler generates type-specific versions at **compile time** — zero runtime overhead.

```cpp
template<typename T>
T getMax(T a, T b) { return (a > b) ? a : b; }

getMax(3, 7);                          // T = int
getMax(3.14, 2.71);                    // T = double
getMax(string("cat"), string("bat"));  // T = string
```

The compiler **instantiates** a separate version for each type used. If `T` doesn't support the required operations (`>` here), it's a **compile-time error**.

#### Container Template
```cpp
template<typename Container>
void printContainer(const string& label, const Container& c) {
    for (const auto& x : c) cout << x << " ";
}
// Works for vector, list, set, array — anything with begin()/end()
```

#### Variadic Templates (C++11)
Accept any number of arguments of any type:
```cpp
template<typename T>
T sumAll(T v) { return v; }   // base case: single arg

template<typename T, typename... Args>
T sumAll(T first, Args... rest) { return first + sumAll(rest...); }

sumAll(1, 2, 3, 4, 5);     // → 15
sumAll(1.5, 2.5, 3.0);     // → 7.0
```

---

### 2.2 Class Templates

Define a generic class parametrized over a type:

```cpp
template<typename T>
class Stack {
    vector<T> data_;
public:
    void push(T val)      { data_.push_back(move(val)); }
    T    pop()            { T v = move(data_.back()); data_.pop_back(); return v; }
    const T& peek() const { return data_.back(); }
    bool empty() const    { return data_.empty(); }
    int  size()  const    { return (int)data_.size(); }
};

Stack<int>    intStack;     // works for int
Stack<string> strStack;     // works for string
```

Key implementation details:
- Uses `move()` inside `push` and `pop` to avoid unnecessary copies.
- Throws `underflow_error` on pop/peek from empty stack.
- Supports range-based for via `begin()`/`end()`.

---

### 2.3 Move Semantics (C++11)

#### l-values vs r-values
- **l-value:** Has a name and a persistent address (can appear on the left of `=`)
- **r-value:** Temporary, no name, no persistent address (e.g., `42`, `string("hello")`, return-value of a function)

#### Why Move Matters
Copying a large buffer is **O(n)** — allocates new memory and copies each element. **Moving** is **O(1)** — it just transfers the pointer:

```cpp
// Copy constructor: O(n) — full deep copy
Buffer(const Buffer& other) : data_(new int[other.size_]) {
    copy(other.data_, other.data_ + other.size_, data_);
}

// Move constructor: O(1) — steal the pointer
Buffer(Buffer&& other) noexcept : data_(other.data_), size_(other.size_) {
    other.data_ = nullptr;  // leave source in valid-but-empty state
    other.size_ = 0;
}
```

```cpp
Buffer b1(5, "src");
Buffer b2 = b1;           // COPY — allocates new array (O(n))
Buffer b3 = move(b1);     // MOVE — transfers pointer (O(1)); b1 is now empty
```

**`std::move()`** is a cast — it converts an l-value to an r-value reference `(&&)`, enabling the move constructor/assignment to be chosen.

#### Rule of Five
If you write any of destructor, copy-ctor, copy-assign — also write move-ctor and move-assign:
- Destructor, Copy constructor, Copy assignment operator
- Move constructor, Move assignment operator

Or use **Rule of Zero** — let RAII wrappers (`vector`, `string`, `unique_ptr`) handle everything automatically.

---

### 2.4 Smart Pointers (Deep Dive)

| Smart Pointer | Ownership | Copies | Use When |
|---------------|-----------|--------|----------|
| `unique_ptr` | Exclusive sole owner | No (movable only) | Default — one clear owner |
| `shared_ptr` | Shared, ref-counted | Yes | Multiple owners needed |
| `weak_ptr` | Non-owning observer | Yes | Break circular `shared_ptr` references |

```cpp
// unique_ptr — transferred with move, not copy
auto up = make_unique<Resource>("FileHandle");
auto up2 = move(up);   // up is now nullptr; up2 owns the Resource

// shared_ptr — reference-counted
auto sp1 = make_shared<Resource>("DB");   // use_count = 1
{
    auto sp2 = sp1;    // use_count = 2
}                      // sp2 destroyed; use_count = 1
// Resource destroyed when sp1 goes out of scope

// weak_ptr — breaks cycles, doesn't affect ref count
weak_ptr<Resource> wp = sp1;
sp1.reset();           // Resource destroyed; wp.expired() → true
if (auto locked = wp.lock()) { locked->use(); }  // safe check
```

---

### 2.5 Lambdas (Advanced)

Lambda = anonymous, inline function object. Captures local variables from enclosing scope.

#### Capture Modes

| Syntax | Meaning |
|--------|---------|
| `[]` | Capture nothing |
| `[=]` | Capture all used variables by value (copy) |
| `[&]` | Capture all used variables by reference |
| `[x]` | Capture `x` by value |
| `[&x]` | Capture `x` by reference |
| `[x, &y]` | x by value, y by reference |

```cpp
int factor = 3;
auto scale  = [factor](int x) { return x * factor; };   // capture by value
auto addRef = [&factor](int x) { return x + factor; };  // capture by reference

// mutable lambda: can modify captured-by-value variables (local copy only)
auto inc = [factor]() mutable { return ++factor; };  // outer factor unchanged

// Higher-order function: lambda as argument
auto applyTwice = [](function<int(int)> f, int x) { return f(f(x)); };
applyTwice([](int x){ return x*x; }, 3);   // → 81

// Lambda with STL algorithm
sort(v.begin(), v.end(), [](int a, int b){ return a > b; }); // descending sort
```

---

### 2.6 `std::optional` (C++17)

Represents a value that **may or may not be present**. Replaces returning magic values (`-1`, `nullptr`, `""`) or bool out-parameters.

```cpp
optional<double> safeSqrt(double x) {
    if (x < 0) return nullopt;   // no value
    return sqrt(x);              // has value
}

auto r = safeSqrt(-1.0);
r.has_value();     // false
r.value();         // throws std::bad_optional_access if empty!
r.value_or(0.0);  // safe fallback: returns 0.0 if empty

// Optional as function return (find-like APIs)
optional<string> findUser(int id) {
    if (id == 42) return "Deepak";
    return nullopt;
}
findUser(99).value_or("Not found");   // → "Not found"
```

---

### 2.7 `std::variant` (C++17) — Type-Safe Union

Holds **one value of one of several types** at a time, chosen at runtime. Replaces the unsafe C-style `union`.

```cpp
using JsonValue = variant<int, double, string, bool>;

JsonValue v = 42;          // holds int
v = string("hello");       // now holds string (old value replaced)

holds_alternative<string>(v);     // true
get<string>(v);                   // "hello"
get<int>(v);                      // throws std::bad_variant_access!
get_if<string>(&v);               // returns pointer, or nullptr if wrong type

// std::visit — applies a visitor to the active type (no manual if-else)
visit([](const auto& val) { cout << val; }, v);
```

---

### 2.8 `constexpr` — Compile-Time Computation

`constexpr` functions and variables are evaluated at **compile time** when their inputs are compile-time constants — **zero runtime overhead**:

```cpp
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}
constexpr double square(double x) { return x * x; }

// Evaluated at compile time (embedded in binary as constant)
constexpr int f5 = factorial(5);   // 120
constexpr double s3 = square(3.0); // 9.0

// Also works at runtime (with non-constexpr inputs)
int n = getUserInput();
factorial(n);   // evaluated at runtime
```

`constexpr` is also used for physical constants, lookup tables (`constexpr` arrays), and template parameters that require compile-time values.

---

### 2.9 Multithreading (C++11)

#### `std::thread`
```cpp
void task(int n, int id) { /* ... */ }

thread t1(task, 500, 1);  // spawn thread
thread t2(task, 500, 2);
t1.join();   // wait for t1 to finish
t2.join();
```

#### `std::mutex` and `lock_guard`
Prevent **data races** (concurrent access to shared data):
```cpp
mutex mtx;
int sharedCounter = 0;

void increment(int n) {
    for (int i = 0; i < n; i++) {
        lock_guard<mutex> lock(mtx);  // RAII lock — auto-released on scope exit
        sharedCounter++;
    }
}

// Without mutex: sharedCounter < 1000 (race condition)
// With mutex:    sharedCounter == 1000 always
```

#### `std::async` and `std::future`
Task-based concurrency — cleaner than raw threads:
```cpp
auto fut1 = async(launch::async, computeHeavy, 100);  // runs on new thread
auto fut2 = async(launch::async, computeHeavy, 200);

// Do other work here while async tasks run...

int r1 = fut1.get();  // blocks until result ready
int r2 = fut2.get();
```

---

## 3. Internal Working

### Template Instantiation
The compiler creates a separate function/class for each unique type combination used. This is called **template instantiation**. If `getMax<int>` and `getMax<double>` are used, two separate functions exist in the binary. This is the "cost" of templates — larger binary, but zero runtime overhead.

### Move Semantics Under the Hood
`Buffer b3 = move(b1)`:
1. `std::move(b1)` casts `b1` to `Buffer&&` (r-value reference).
2. The compiler selects the move constructor.
3. Move constructor copies the raw pointer (O(1)) and nulls the source.
4. No heap allocation. No element copying.

### `optional` Memory Layout
`optional<T>` stores a `bool` flag + aligned storage for `T`. When empty, the storage is uninitialized. Size ≈ `sizeof(T) + 1` byte (with potential padding).

### `variant` Memory Layout
`variant<int, double, string>` holds a **type index** + aligned storage large enough for the largest type (`string` here). Only one type is ever "active" at a time.

---

## 4. Operations & Techniques

### When to Use Each Feature

| Feature | When to Use |
|---------|-------------|
| Function template | Same algorithm for multiple types |
| Class template | Generic data structure (Stack, Queue, Pair) |
| `move()` | Transferring ownership of containers, buffers, file handles |
| `unique_ptr` | Single-owner resource (the default choice) |
| `shared_ptr` | Shared ownership (caches, observer patterns) |
| `weak_ptr` | Non-owning references, break circular dependencies |
| Lambda | Short inline callbacks, STL predicates, capturing local state |
| `optional` | Functions that may not return a value |
| `variant` | Type-safe sum type (JSON values, error/value union) |
| `constexpr` | Compile-time constants, lookup tables, size computations |
| `thread` + `mutex` | CPU-bound parallel tasks |
| `async` + `future` | Asynchronous tasks with a return value |

---

## 5. Time & Space Complexity Table

| Feature | Time | Space | Notes |
|---------|------|-------|-------|
| Template function call | O(same as non-template) | O(1) | Instantiated at compile time |
| Move constructor | O(1) | O(1) | Pointer transfer only |
| Copy constructor | O(n) | O(n) | Full deep copy |
| `unique_ptr` ops | O(1) | O(1) | Zero overhead over raw pointer |
| `shared_ptr` copy | O(1) | O(1) | Atomic ref count increment |
| Lambda capture (by value) | O(captured size) | O(captured size) | Copies at creation |
| `optional` access | O(1) | O(sizeof T + 1) | — |
| `variant` visit | O(1) | O(sizeof largest type) | — |
| `constexpr` evaluation | O(0) runtime | O(0) runtime | Compile-time constant |
| `thread` creation | O(OS overhead) | O(stack size) | Typical ~1ms |
| `mutex` lock/unlock | O(1) | O(1) | ~20-100 ns |
| `async` task launch | O(thread creation) | O(stack + result) | — |

---

## 6. Common Mistakes

### Templates
- **Putting template definitions in a `.cpp` file** → linker errors. Template definitions must be in the **header** (or same file as usage).
- **Forgetting to handle empty variadic pack** → infinite recursion or compile error. Always add a base case.

### Move Semantics
- **Accessing a moved-from object** → undefined behavior. The moved-from object is in a "valid but unspecified state".
- **`move` on a `const` object** → silently falls back to copy (no move for `const`).
- **Forgetting `noexcept` on move constructors** → STL containers won't use move (falls back to copy for exception safety).

### Smart Pointers
- **`shared_ptr` circular reference** → both objects keep each other alive → memory leak. Break with `weak_ptr`.
- **Using `shared_ptr` when `unique_ptr` would do** → unnecessary ref-count overhead.
- **`make_shared` vs `shared_ptr(new T)`** → prefer `make_shared` (single allocation for object + control block).

### Lambdas
- **Capturing `this` or local references that outlive the lambda** → dangling reference.
- **`[=]` capturing large objects** → expensive unintended copies. Be explicit: `[x]` instead of `[=]`.

### Threading
- **Accessing shared data without a mutex** → data race → undefined behavior.
- **Forgetting `t.join()` or `t.detach()`** → program terminates (`std::terminate`) when thread object is destroyed while joinable.
- **Deadlock** → two threads each holding a lock and waiting for the other's.

---

## 7. Interview Relevance

| Topic | Common Interview Questions |
|-------|---------------------------|
| Templates | "What is template instantiation? What is a template specialization?" |
| Move semantics | "What is the difference between copy and move? When is move called automatically?" |
| `unique_ptr` vs `shared_ptr` | "What is the overhead of `shared_ptr`? Why prefer `unique_ptr`?" |
| `weak_ptr` | "What problem does `weak_ptr` solve? How do you use it safely?" |
| Lambda captures | "What is the difference between `[=]` and `[&]` capture?" |
| `optional` | "What is `std::optional`? How is it better than returning `-1`?" |
| `constexpr` | "What is the difference between `const` and `constexpr`?" |
| Threading | "What is a data race? How do you prevent it?" |
| `async` | "What is `std::future`? When would you use `std::async`?" |
| Rule of Five | "What is the Rule of Five? When do you need a custom move constructor?" |

---

## 8. Best Practices (C++ Specific)

```cpp
// ✅ Templates: put implementations in headers (or use .tpp files)
// ✅ Always mark move constructors/assignment noexcept
Buffer(Buffer&& other) noexcept { ... }

// ✅ Prefer unique_ptr, escalate to shared_ptr only when needed
auto resource = make_unique<MyClass>(args...);

// ✅ Use make_shared (single allocation)
auto sp = make_shared<MyClass>(args...);       // ✅
auto sp = shared_ptr<MyClass>(new MyClass());  // ❌ two allocations

// ✅ Prefer lambdas over std::bind (cleaner, more optimizable)
sort(v.begin(), v.end(), [](int a, int b){ return a > b; });

// ✅ Use optional for nullable returns instead of magic values
optional<string> findUser(int id);  // ✅
string findUser(int id);  // returns "" for not found — ❌ ambiguous

// ✅ Mark constexpr functions wherever they CAN be constexpr
constexpr double square(double x) { return x * x; }

// ✅ Always join or detach threads
thread t(task);
t.join();   // or t.detach() if fire-and-forget

// ✅ Prefer lock_guard / scoped_lock over manual lock/unlock (RAII)
lock_guard<mutex> lock(mtx);  // auto-released on scope exit
```

---

## 9. Summary

```
cpp/advanced/ — What's Covered (01_advanced.cpp)
├── Function Templates: getMax<T>, printContainer<C>, variadic sumAll<T,Args...>
├── Class Templates: Stack<T> with push/pop/peek, move semantics inside
├── Move Semantics: Buffer class — copy-ctor O(n) vs move-ctor O(1), std::move
├── Smart Pointers: unique_ptr ownership transfer, shared_ptr ref counting,
│                   weak_ptr cycle breaking
├── Lambdas: capture modes ([],[=],[&]), mutable, higher-order functions,
│            std::function, STL integration
├── std::optional (C++17): safeSqrt, findUser — nullable return values
├── std::variant (C++17): JsonValue — type-safe union, std::visit
├── constexpr: factorial/square computed at compile time, runtime fallback
└── Multithreading: std::thread, mutex + lock_guard (RAII), std::async + future
```

**Key Takeaways:**
- **Templates** achieve generic programming with zero runtime overhead — the compiler does the work.
- **Move semantics** make transferring large containers O(1) instead of O(n) — critical for performance.
- **`unique_ptr`** should be your default. Only use `shared_ptr` when you genuinely have multiple owners.
- **`constexpr`** moves computation to compile time — useful for lookup tables, type checks, and mathematical constants.
- **Mutexes** and **`lock_guard`** (RAII locking) are the two essentials for thread-safe code.

---

> **Previous:** `cpp/oops/` — Classes, Inheritance, Polymorphism  
> **Next:** `cpp/dsa/` — Data Structures and Algorithms
