// ============================================================
// MODULE | C++ ADVANCED → Templates, Move Semantics, RAII,
//          Lambdas, Smart Pointers, std::optional/variant,
//          constexpr, Threading, Design Patterns
// ============================================================
// DESCRIPTION:
//   A comprehensive tour of modern C++ (C++14/17/20) advanced
//   features. Each section is independently runnable.
//
// COMPILE & RUN:
//   g++ -std=c++17 -pthread 01_advanced.cpp -o out && ./out
//
// SAMPLE OUTPUT:
//   === TEMPLATES ===
//   getMax(3,7)=7  getMax(cat,bat)=cat
//   ...
// ============================================================

#include <iostream>
#include <vector>
#include <string>
#include <memory>       // unique_ptr, shared_ptr, weak_ptr
#include <functional>   // std::function
#include <optional>     // std::optional
#include <variant>      // std::variant
#include <algorithm>
#include <numeric>
#include <thread>
#include <mutex>
#include <future>
#include <type_traits>  // std::is_integral_v
using namespace std;

// ============================================================
// SECTION 1: FUNCTION TEMPLATES
// ============================================================
// Templates generate type-specific code at compile time.
// 'typename T' is a placeholder for any type.
// ------------------------------------------------------------ 

/**
 * Returns the larger of two values.
 * Works for ANY type that supports operator>.
 *
 * Time: O(1)  |  Space: O(1)
 */
template<typename T>
T getMax(T a, T b) {
    return (a > b) ? a : b;
}

/**
 * Prints all elements of any container.
 * Uses two template params: Container type and value type.
 *
 * Time: O(n)  |  Space: O(1)
 */
template<typename Container>
void printContainer(const string& label, const Container& c) {
    cout << label << ": [ ";
    for (const auto& x : c) cout << x << " ";
    cout << "]\n";
}

/**
 * Variadic template: recursively sums any number of arguments.
 * Base case: single argument.
 * Recursive case: first + sum of rest.
 *
 * Time: O(n)  |  Space: O(n stack frames)
 */
template<typename T>
T sumAll(T v) { return v; }  // base case

template<typename T, typename... Args>
T sumAll(T first, Args... rest) { return first + sumAll(rest...); }

// ============================================================
// SECTION 2: CLASS TEMPLATES
// ============================================================

/**
 * Generic typed Stack (LIFO) using a vector internally.
 * Demonstrates class template with member functions.
 *
 * Time: push/pop/peek all O(1)
 * Space: O(n)
 */
template<typename T>
class Stack {
    vector<T> data_;

public:
    void push(T val) {
        data_.push_back(move(val));   // move avoids unnecessary copy
    }

    T pop() {
        if (data_.empty())
            throw underflow_error("Stack::pop() on empty stack");
        T val = move(data_.back());
        data_.pop_back();
        return val;
    }

    const T& peek() const {
        if (data_.empty()) throw underflow_error("Stack::peek() on empty stack");
        return data_.back();
    }

    bool empty() const { return data_.empty(); }
    int  size()  const { return (int)data_.size(); }

    // Range-based for support
    auto begin() { return data_.begin(); }
    auto end()   { return data_.end(); }
};

// ============================================================
// SECTION 3: MOVE SEMANTICS (C++11)
// ============================================================
// l-value: has a name/address (can appear on left of =)
// r-value: temporary, no persistent identity (appears only on right)
//
// Copy   : creates a full copy of data      → O(n)
// Move   : transfers ownership of resource  → O(1)
// std::move() casts an l-value to r-value reference (&&)
// ------------------------------------------------------------ 

class Buffer {
    int*   data_;
    size_t size_;
    string name_;

public:
    // Constructor: allocate
    Buffer(size_t sz, const string& name)
        : data_(new int[sz]), size_(sz), name_(name) {
        fill(data_, data_ + sz, 0);
        cout << "  Buffer(" << name_ << ", sz=" << sz << ") — CONSTRUCTED\n";
    }

    // Copy constructor: deep copy — O(n)
    Buffer(const Buffer& other)
        : data_(new int[other.size_]), size_(other.size_), name_(other.name_ + "_copy") {
        copy(other.data_, other.data_ + other.size_, data_);
        cout << "  Buffer(" << name_ << ") — COPY CONSTRUCTED\n";
    }

    // Move constructor: steal resource — O(1)
    Buffer(Buffer&& other) noexcept
        : data_(other.data_), size_(other.size_), name_(move(other.name_)) {
        other.data_ = nullptr;     // leave source in a valid but empty state
        other.size_ = 0;
        name_ += "_moved";
        cout << "  Buffer(" << name_ << ") — MOVE CONSTRUCTED (O(1))\n";
    }

    // Destructor: release
    ~Buffer() {
        if (data_) {
            delete[] data_;
            cout << "  Buffer(" << name_ << ") — DESTROYED\n";
        } else {
            cout << "  Buffer(moved-from) — DESTROYED (no-op)\n";
        }
    }

    size_t size() const { return size_; }
    string name() const { return name_; }
};

// ============================================================
// SECTION 4: SMART POINTERS
// ============================================================
// unique_ptr : sole owner, cannot be copied, only moved. O(1) overhead.
// shared_ptr : reference-counted ownership. ~O(1) overhead.
// weak_ptr   : non-owning observer of a shared_ptr (breaks cycles).
// ------------------------------------------------------------ 

class Resource {
    string name_;
public:
    explicit Resource(const string& n) : name_(n) {
        cout << "  Resource(\"" << n << "\") acquired\n";
    }
    ~Resource() {
        cout << "  Resource(\"" << name_ << "\") released\n";
    }
    void use() const { cout << "  Using " << name_ << "\n"; }
};

void demonstrateSmartPointers() {
    cout << "\n=== SMART POINTERS ===" << endl;

    // --- unique_ptr --- (sole owner)
    cout << "-- unique_ptr --\n";
    {
        auto up = make_unique<Resource>("FileHandle");   // acquired
        up->use();
        // transfer ownership — move only!
        auto up2 = move(up);
        if (!up) cout << "  up is now nullptr (ownership transferred)\n";
        up2->use();
    }   // up2 goes out of scope → destructor fires automatically

    // --- shared_ptr ---
    cout << "\n-- shared_ptr --\n";
    shared_ptr<Resource> sp1;
    {
        sp1 = make_shared<Resource>("DBConnection");
        cout << "  use_count=" << sp1.use_count() << "\n";   // 1
        {
            auto sp2 = sp1;    // shared ownership; ref count → 2
            cout << "  use_count=" << sp1.use_count() << "\n";
        }
        cout << "  use_count after inner scope=" << sp1.use_count() << "\n";   // back to 1
    }
    // sp1 still alive here (use_count=1)

    // --- weak_ptr (breaking circular references) ---
    cout << "\n-- weak_ptr --\n";
    auto sp = make_shared<Resource>("CacheEntry");
    weak_ptr<Resource> wp = sp;
    cout << "  weak_ptr expired? " << boolalpha << wp.expired() << "\n";  // false
    sp.reset();   // release the shared_ptr
    cout << "  After sp.reset(), weak_ptr expired? " << wp.expired() << "\n";  // true
}

// ============================================================
// SECTION 5: LAMBDAS
// ============================================================
// Lambda = anonymous inline function object.
// Capture:  []   → capture nothing
//           [=]  → capture all by value (copy)
//           [&]  → capture all by reference
//           [x, &y] → x by value, y by reference
// ------------------------------------------------------------ 
void demonstrateLambdas() {
    cout << "\n=== LAMBDAS ===" << endl;

    // Basic lambda
    auto square = [](int x) { return x * x; };
    cout << "square(7) = " << square(7) << "\n";

    // Capture by value
    int factor = 3;
    auto scaleByFactor = [factor](int x) { return x * factor; };
    cout << "scale(5) with factor=3: " << scaleByFactor(5) << "\n";

    // Capture by reference (modifies outer variable)
    int callCount = 0;
    auto increment = [&callCount]() { callCount++; };
    increment(); increment(); increment();
    cout << "callCount after 3 increments: " << callCount << "\n";

    // Higher-order function: pass lambda as argument
    auto applyTwice = [](function<int(int)> f, int x) { return f(f(x)); };
    cout << "applyTwice(square, 3) = " << applyTwice(square, 3) << "\n";  // 81

    // Lambda used with STL algorithm
    vector<int> nums = {5, 3, 8, 1, 9, 2, 7};
    sort(nums.begin(), nums.end(), [](int a, int b){ return a > b; }); // descending
    cout << "sorted descending: ";
    for (int n : nums) cout << n << " ";
    cout << "\n";

    // Mutable lambda (can modify captured-by-value variables)
    int counter = 0;
    auto inc = [counter]() mutable { return ++counter; };  // counter is local copy
    cout << "mutable lambda: " << inc() << " " << inc() << " " << inc() << "\n";
    cout << "outer counter unchanged: " << counter << "\n";
}

// ============================================================
// SECTION 6: std::optional (C++17)
// ============================================================
// Represents a value that may or may not be present.
// Better than returning -1, nullptr, or using a bool out-param.
// ------------------------------------------------------------ 
optional<double> safeSqrt(double x) {
    if (x < 0) return nullopt;         // no value
    return sqrt(x);                    // has value
}

optional<string> findUser(int id) {
    if (id == 42) return "Deepak";
    return nullopt;
}

void demonstrateOptional() {
    cout << "\n=== std::optional ===" << endl;

    for (double v : {4.0, -1.0, 9.0}) {
        auto result = safeSqrt(v);
        if (result.has_value())
            cout << "sqrt(" << v << ") = " << result.value() << "\n";
        else
            cout << "sqrt(" << v << ") = undefined (negative input)\n";
    }

    // value_or provides a fallback default
    auto user = findUser(99);
    cout << "User: " << user.value_or("Not found") << "\n";

    auto admin = findUser(42);
    cout << "Admin: " << admin.value_or("Not found") << "\n";
}

// ============================================================
// SECTION 7: std::variant (C++17) — Type-Safe Union
// ============================================================
// Holds one value of several possible types at a time.
// Replaces unsafe C-style unions.
// std::visit applies a visitor function to the active type.
// ------------------------------------------------------------ 
using JsonValue = variant<int, double, string, bool>;

void printJson(const JsonValue& v) {
    visit([](const auto& val) {
        cout << "  type=" << typeid(val).name() << "  value=" << boolalpha << val << "\n";
    }, v);
}

void demonstrateVariant() {
    cout << "\n=== std::variant ===" << endl;

    vector<JsonValue> values = {42, 3.14, string("hello"), true};

    for (const auto& jv : values) {
        printJson(jv);
    }

    // holds_alternative and get
    JsonValue v = string("world");
    if (holds_alternative<string>(v)) {
        cout << "  variant holds string: " << get<string>(v) << "\n";
    }
}

// ============================================================
// SECTION 8: constexpr (Compile-Time Computation)
// ============================================================
// constexpr functions and variables are evaluated at compile time.
// Zero runtime overhead for constant inputs.
// ------------------------------------------------------------ 
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

constexpr double square(double x) { return x * x; }

void demonstrateConstexpr() {
    cout << "\n=== constexpr ===" << endl;

    // Both evaluated at COMPILE TIME — no runtime cost
    constexpr int  f5  = factorial(5);    // 120
    constexpr double s3 = square(3.0);    // 9.0

    cout << "factorial(5) [compile-time] = " << f5  << "\n";
    cout << "square(3.0)  [compile-time] = " << s3  << "\n";

    // Works at runtime too (with non-constexpr input)
    int n; cout << "Enter n for factorial: ";
    if (!(cin >> n)) n = 6;   // fallback if no stdin available
    cout << "factorial(" << n << ") [runtime] = " << factorial(n) << "\n";
}

// ============================================================
// SECTION 9: MULTITHREADING (C++11)
// ============================================================
// std::thread    : create OS-level threads
// std::mutex     : mutual exclusion (prevents data races)
// lock_guard     : RAII mutex lock (auto-releases on scope exit)
// std::async/future : task-based concurrency
// ------------------------------------------------------------ 
mutex globalMtx;
int   sharedCounter = 0;

void incrementTask(int increments, int threadId) {
    for (int i = 0; i < increments; i++) {
        lock_guard<mutex> lock(globalMtx);   // RAII lock — auto-released
        sharedCounter++;
    }
    // Note: printing without mutex here would cause garbled output
}

int computeHeavy(int n) {
    int result = 0;
    for (int i = 1; i <= n; i++) result += i;   // simulate heavy work
    return result;
}

void demonstrateThreading() {
    cout << "\n=== MULTITHREADING ===" << endl;

    sharedCounter = 0;

    // Spawn two threads that both increment the shared counter
    thread t1(incrementTask, 500, 1);
    thread t2(incrementTask, 500, 2);

    t1.join();   // wait for t1 to complete
    t2.join();   // wait for t2 to complete

    // Without the mutex, sharedCounter could be < 1000 due to data race.
    // With mutex, result is always exactly 1000.
    cout << "sharedCounter (expected 1000) = " << sharedCounter << "\n";

    // std::async + std::future (fire-and-forget async task)
    auto fut1 = async(launch::async, computeHeavy, 100);   // runs on new thread
    auto fut2 = async(launch::async, computeHeavy, 200);

    // Do other work while async tasks run...
    cout << "Async tasks running...\n";

    int r1 = fut1.get();   // blocks until result is ready
    int r2 = fut2.get();
    cout << "sum(1..100) = " << r1 << "  sum(1..200) = " << r2 << "\n";
}

// ============================================================
// MAIN
// ============================================================
int main() {

    cout << "=== FUNCTION TEMPLATES ===" << endl;
    cout << "getMax(3,7)             = " << getMax(3, 7)                    << "\n";
    cout << "getMax(3.14, 2.71)      = " << getMax(3.14, 2.71)              << "\n";
    cout << "getMax(\"cat\",\"bat\")= " << getMax(string("cat"),string("bat")) << "\n";

    cout << "\n=== CLASS TEMPLATE (Stack<T>) ===" << endl;
    Stack<int> intStack;
    for (int x : {10,20,30,40}) intStack.push(x);
    cout << "size=" << intStack.size() << "  peek=" << intStack.peek() << "\n";
    cout << "popping: ";
    while (!intStack.empty()) cout << intStack.pop() << " ";
    cout << "\n";

    cout << "\n=== VARIADIC TEMPLATE ===" << endl;
    cout << "sumAll(1,2,3,4,5)   = " << sumAll(1,2,3,4,5)       << "\n";
    cout << "sumAll(1.5,2.5,3.0) = " << sumAll(1.5,2.5,3.0)     << "\n";

    cout << "\n=== MOVE SEMANTICS ===" << endl;
    {
        Buffer b1(5, "src");
        Buffer b2 = b1;           // COPY — allocates new memory
        Buffer b3 = move(b1);     // MOVE — transfers pointer (O(1))
        cout << "b2.name()=" << b2.name() << "  b3.name()=" << b3.name() << "\n";
    }   // destructors fire here in reverse order

    demonstrateSmartPointers();
    demonstrateLambdas();
    demonstrateOptional();
    demonstrateVariant();
    demonstrateConstexpr();
    demonstrateThreading();

    return 0;
}

// ============================================================
// COMPLEXITY & KEY CONCEPTS
//   Templates     : zero-cost abstraction (compile-time)
//   Move semantics: O(1) vs O(n) for copy
//   unique_ptr    : zero overhead vs raw pointer
//   shared_ptr    : ~2× overhead (atomic ref count)
//   optional/variant: small overhead (tag byte)
//   constexpr     : zero runtime cost for const inputs
//   mutex/lock    : ~20–100 ns overhead per lock (OS-dependent)
//
// MODERN C++ RULES OF ZERO / FIVE:
//   If a class manages a resource, define ALL of:
//     destructor, copy-ctor, copy-assign, move-ctor, move-assign
//   Or use RAII wrappers (smart pointers) for automatic management.
// ============================================================
