# 🧠 C++ Memory Management — Interview Questions

> Memory management is what separates C++ from most other languages. Interviewers use it to gauge your understanding of low-level systems.

---

## 1. Stack vs Heap Memory

| Feature | Stack | Heap |
|---------|-------|------|
| Allocation | Automatic (LIFO) | Manual (`new`/`malloc`) |
| Speed | Very fast | Slower (OS manages) |
| Size | Limited (~1-8 MB) | Large (limited by RAM) |
| Lifetime | Function scope | Until `delete`/`free` |
| Fragmentation | None | Can fragment |

```cpp
void example() {
    int x = 10;              // Stack — auto-destroyed at function end
    int* p = new int(20);    // Heap — lives until delete
    delete p;                // Must manually free!
}
```

### ⚠️ Trap
> "Where are static variables stored?" → Neither stack nor heap. They're in the **data segment** (initialized) or **BSS segment** (uninitialized). They persist for program lifetime.

---

## 2. Memory Leaks

### What
Heap memory allocated but never freed. Program slowly consumes more and more RAM.

### Classic Causes
```cpp
void leak() {
    int* p = new int[100];
    return;  // ❌ Never deleted — LEAK!
}

void leak2() {
    int* p = new int(5);
    p = new int(10);  // ❌ Lost pointer to first allocation — LEAK!
}

void leak3() {
    int* p = new int(5);
    throw runtime_error("oops");  // ❌ Exception before delete — LEAK!
    delete p;
}
```

### 📌 Interview Tip
> Fix: Use **RAII** (Resource Acquisition Is Initialization) — wrap resources in objects whose destructors release them. This is the principle behind smart pointers.

---

## 3. Smart Pointers (C++11+)

### `unique_ptr` — Exclusive ownership
```cpp
unique_ptr<int> p = make_unique<int>(42);
// No copy allowed, only move
unique_ptr<int> q = move(p);  // p is now nullptr
// Automatically deleted when q goes out of scope
```

### `shared_ptr` — Shared ownership (reference counted)
```cpp
shared_ptr<int> p = make_shared<int>(42);
shared_ptr<int> q = p;  // ref count = 2
// Deleted when last shared_ptr is destroyed (ref count hits 0)
```

### `weak_ptr` — Non-owning reference (breaks cycles)
```cpp
shared_ptr<Node> a = make_shared<Node>();
shared_ptr<Node> b = make_shared<Node>();
a->next = b;
b->next = a;  // ❌ Circular reference — MEMORY LEAK!
// Fix: make one pointer weak
b->next = weak_ptr<Node>(a);  // Doesn't increase ref count
```

### ⚠️ Trap
> "When would you use `shared_ptr`?" → Only when true shared ownership is needed (multiple owners). If there's one clear owner, use `unique_ptr` (cheaper, no ref counting overhead).

---

## 4. Dangling Pointers

```cpp
int* createDangling() {
    int x = 42;
    return &x;  // ❌ x is destroyed, pointer is DANGLING
}

int* p = new int(5);
delete p;
cout << *p;  // ❌ UNDEFINED BEHAVIOR — p is dangling
p = nullptr; // ✅ Always nullify after delete
```

### 📌 Interview Tip
> After `delete`, always set pointer to `nullptr`. Better yet, use smart pointers so you never manually delete.

---

## 5. `new` / `delete` vs `malloc` / `free`

| Feature | `new`/`delete` | `malloc`/`free` |
|---------|---------------|----------------|
| Language | C++ | C (also works in C++) |
| Calls constructor | ✅ Yes | ❌ No |
| Returns | Typed pointer | `void*` (needs cast) |
| On failure | Throws `bad_alloc` | Returns `NULL` |
| Array version | `new[]`/`delete[]` | N/A |

### ⚠️ Trap
> Never mix them! `new` + `free` or `malloc` + `delete` = undefined behavior.
> Always use `delete[]` for arrays, not `delete`.

---

## 6. Rule of Three / Five / Zero

| Rule | When | What to Implement |
|------|------|------------------|
| **Rule of Three** | Custom destructor needed | Destructor + Copy Constructor + Copy Assignment |
| **Rule of Five** (C++11) | + Move semantics | + Move Constructor + Move Assignment |
| **Rule of Zero** | Use smart pointers | Let compiler generate everything |

### 📌 Interview Tip
> In modern C++, always strive for **Rule of Zero** — use `unique_ptr`/`shared_ptr` and let the compiler handle resource management. Only write custom destructors if you absolutely must.
