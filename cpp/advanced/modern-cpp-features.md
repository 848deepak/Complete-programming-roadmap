# ⚡ Modern C++ Features (C++11 → C++20)

> Essential modern C++ features every developer and interviewee must know.

---

## C++11 — The Game Changer

### 1. Auto & Range-Based For
```cpp
auto x = 42;         // int
auto pi = 3.14;      // double
auto vec = vector<int>{1, 2, 3};

// Range-based for loop
for (auto& val : vec) {
    cout << val << " ";  // No index needed
}

// With structured bindings (C++17)
map<string,int> m = {{"a",1}, {"b",2}};
for (auto& [key, val] : m) {
    cout << key << "=" << val << "\n";
}
```

### 2. Smart Pointers
```cpp
// unique_ptr — sole ownership, no copying
auto p1 = make_unique<int>(42);

// shared_ptr — reference counted
auto p2 = make_shared<int>(42);
auto p3 = p2;  // ref count = 2

// weak_ptr — breaks circular references
weak_ptr<int> wp = p2;
if (auto sp = wp.lock()) { /* use sp */ }
```

### 3. Lambda Expressions
```cpp
// Basic lambda
auto add = [](int a, int b) { return a + b; };
cout << add(3, 4);  // 7

// Capture by reference
int x = 10;
auto modify = [&x]() { x += 5; };
modify();  // x is now 15

// Used with algorithms
vector<int> v = {3, 1, 4, 1, 5};
sort(v.begin(), v.end(), [](int a, int b) { return a > b; });  // Descending

// Generic lambda (C++14)
auto print = [](auto x) { cout << x; };
```

### 4. Move Semantics & Rvalue References
```cpp
// Move instead of copy — avoids deep copy
vector<int> createBigVector() {
    vector<int> v(1000000, 42);
    return v;  // Move, not copy (RVO or move semantics)
}

// Move constructor
class MyString {
    char* data;
public:
    // Move constructor — "steals" resources
    MyString(MyString&& other) noexcept {
        data = other.data;
        other.data = nullptr;  // Leave source in valid state
    }
};

// std::move — explicitly cast to rvalue
string a = "hello";
string b = std::move(a);  // a is now empty, b owns the data
```

### 5. Initializer Lists & Uniform Initialization
```cpp
vector<int> v = {1, 2, 3, 4, 5};
map<string,int> m = {{"a",1}, {"b",2}};
pair<int,string> p = {42, "hello"};

// Uniform initialization (prevents narrowing)
int x{42};
// int y{3.14};  // ❌ Compile error — narrowing
```

---

## C++14 — Quality of Life

### Generic Lambdas
```cpp
auto add = [](auto a, auto b) { return a + b; };
add(1, 2);       // int
add(1.5, 2.5);   // double
add("a"s, "b"s); // string
```

### make_unique
```cpp
auto p = make_unique<int>(42);  // Preferred over new
```

---

## C++17 — Structured Bindings & More

### Structured Bindings
```cpp
auto [x, y] = make_pair(1, 2);
auto [key, value] = *myMap.begin();

// With tuples
auto [a, b, c] = make_tuple(1, "hello", 3.14);
```

### if with Initializer
```cpp
if (auto it = myMap.find(key); it != myMap.end()) {
    cout << it->second;
}
```

### std::optional
```cpp
optional<int> divide(int a, int b) {
    if (b == 0) return nullopt;
    return a / b;
}

if (auto result = divide(10, 3)) {
    cout << *result;
}
```

### std::string_view
```cpp
void print(string_view sv) {  // No copy!
    cout << sv;
}
print("hello");        // Works with string literals
print(myString);       // Works with std::string
```

---

## C++20 — The Future

### Concepts
```cpp
template<typename T>
concept Numeric = is_arithmetic_v<T>;

template<Numeric T>
T add(T a, T b) { return a + b; }
```

### Ranges
```cpp
#include <ranges>
vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// Filter even, transform to squares, take first 3
auto result = v | views::filter([](int n){ return n%2==0; })
                | views::transform([](int n){ return n*n; })
                | views::take(3);
// result: {4, 16, 36}
```

### Three-Way Comparison (Spaceship Operator)
```cpp
struct Point {
    int x, y;
    auto operator<=>(const Point&) const = default;
    // Generates ==, !=, <, >, <=, >= automatically!
};
```

---

## Interview Quick Reference

| Feature | Version | Key Use Case |
|---------|---------|-------------|
| `auto` | C++11 | Type deduction |
| Smart pointers | C++11 | Memory safety |
| Lambdas | C++11 | Inline functions, STL algorithms |
| Move semantics | C++11 | Performance, avoiding copies |
| Structured bindings | C++17 | Decomposing pairs/tuples |
| `optional` | C++17 | Nullable return values |
| `string_view` | C++17 | Non-owning string references |
| Concepts | C++20 | Template constraints |
| Ranges | C++20 | Composable data transformations |
