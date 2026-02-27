# C++ Object-Oriented Programming (OOP)

> **Folder:** `cpp/oops/` | **Level:** Intermediate → Advanced  
> **Files:** `01_oop.cpp`

---

## 1. Introduction

Object-Oriented Programming (OOP) is a programming paradigm built around the concept of **objects** — entities that bundle related data (attributes) and behaviour (methods) together. C++ is a multi-paradigm language with first-class OOP support built on four foundational pillars: **Encapsulation, Inheritance, Polymorphism, and Abstraction**.

This module implements all four pillars through real, working examples: a `Box` class (constructors), `BankAccount` (encapsulation), a `Shape` hierarchy (abstraction + polymorphism), and an `Animal` hierarchy (inheritance + virtual dispatch).

---

## 2. Core Concepts

### 2.1 Classes and Objects
A **class** is a blueprint that defines data (member variables) and behaviour (member functions). An **object** is an instance of a class created from that blueprint.

```cpp
class BankAccount {
    // --- data (attributes) ---
    string owner;
    double balance;      // private by default in class

public:
    // --- behaviour (methods) ---
    void deposit(double amount);
    bool withdraw(double amount);
};

BankAccount acc("Deepak", 10000): // object (instance)
```

**`struct` vs `class`:** The only technical difference is the **default access**: `struct` defaults to `public`, `class` defaults to `private`. By convention, use `struct` for plain data and `class` for encapsulated objects with logic.

---

### 2.2 Constructors & Destructors

| Constructor Type | When Called | Syntax |
|-----------------|-------------|--------|
| Default | No arguments provided | `Box()` |
| Parameterised | Called with specific values | `Box(double l, double w, double h)` |
| Copy | Initialised from another object | `Box(const Box& other)` |
| Move (C++11) | Initialised from temporary r-value | `Box(Box&& other) noexcept` |
| Destructor | Object goes out of scope or `delete` | `~Box()` |

```cpp
Box b1;             // default constructor
Box b2(3, 4, 5);    // parameterised constructor
Box b3 = b2;        // copy constructor
```

**Initialiser List** — Preferred way to initialise members (runs before the constructor body):
```cpp
Box(double l, double w, double h) : l(l), w(w), h(h) {
    // body runs AFTER members are initialised
}
```

**Destructor call order:** Destructors fire in **reverse** order of construction when objects go out of scope.

---

### 2.3 Encapsulation (`BankAccount`)
**Encapsulation** = bundling data + methods + restricting direct access to internal state.

```cpp
class BankAccount {
    double balance;    // PRIVATE — cannot be accessed directly from outside
public:
    double getBalance() const { return balance; }   // read-only getter

    void deposit(double amount) {
        if (amount <= 0) { cout << "ERROR"; return; }  // validation gating
        balance += amount;
    }

    bool withdraw(double amount) {
        if (amount > balance) { cout << "Insufficient"; return false; }
        balance -= amount;
        return true;
    }
};
```

**Benefits:** Data integrity (invalid states prevented), flexibility (implementation can change without breaking callers), testability (controlled interface).

---

### 2.4 Abstraction — Abstract Classes & Pure Virtual Functions

An **abstract class** has at least one **pure virtual function** (`= 0`). It cannot be instantiated directly — it defines a **contract** that subclasses must fulfill:

```cpp
class Shape {
public:
    virtual ~Shape() = default;   // REQUIRED virtual destructor for polymorphism

    virtual double area()      const = 0;   // pure virtual — must override
    virtual double perimeter() const = 0;
    virtual void   draw()      const = 0;

    void describe() const { ... }  // concrete shared method — no override needed
};
```

- `= 0` makes the function **pure virtual** → class becomes abstract.
- Derived classes **must** override all pure virtual functions, or they also become abstract.

```cpp
class Circle : public Shape {
    double radius;
public:
    double area()      const override { return M_PI * radius * radius; }
    double perimeter() const override { return 2 * M_PI * radius; }
    void   draw()      const override { cout << "Drawing circle\n"; }
};
```

---

### 2.5 Inheritance

**Inheritance** allows a new class (derived/child) to reuse and extend the behaviour of an existing class (base/parent):

```cpp
class Animal {
protected:
    string name;
    int age;
public:
    virtual void makeSound() const { cout << name << ": ...\n"; }
};

class Dog : public Animal {   // Dog IS-A Animal
    string breed;
public:
    void makeSound() const override { cout << name << ": Woof!\n"; }
    void fetch() const { cout << name << " fetches!\n"; }
};
```

#### Access Specifiers in Inheritance

| Base member | `public` inheritance | `protected` inheritance | `private` inheritance |
|-------------|---------------------|------------------------|----------------------|
| `public` | `public` | `protected` | `private` |
| `protected` | `protected` | `protected` | `private` |
| `private` | Not accessible | Not accessible | Not accessible |

#### Types of Inheritance (C++)
- **Single:** `class Dog : public Animal`
- **Multi-level:** `Animal → Pet → Dog`
- **Multiple:** `class FlyingFish : public Fish, public Bird`
- **Hierarchical:** Multiple classes inherit from the same base

---

### 2.6 Polymorphism

**Polymorphism** = "many forms" — one interface operating on different types.

#### Runtime Polymorphism (Virtual Functions)
```cpp
vector<Animal*> animals = { new Animal("Lion"), new Dog("Max"), new Cat("Luna") };

for (auto* a : animals) a->makeSound();   // calls the CORRECT override at runtime
// Lion: ...   Max: Woof!   Luna: Meow!
```
The correct function is selected at runtime via the **vtable** (virtual dispatch table).

**Rules:**
- Base class must declare the function as `virtual`.
- Derived class overrides with `override` keyword (optional but strongly recommended).
- Always declare virtual destructor in the base class if using polymorphism.

#### Compile-Time Polymorphism (Function Overloading)
```cpp
class Calculator {
public:
    int    add(int a, int b)        { return a + b; }
    double add(double a, double b)  { return a + b; }
    int    add(int a, int b, int c) { return a + b + c; }
    string add(string a, const string& b) { return a + b; }  // concatenate
};
```
Resolved by the compiler based on argument types at compile time. Zero runtime overhead.

#### `dynamic_cast` — Safe Downcast
```cpp
Animal* a = new Dog("Max");
if (Dog* d = dynamic_cast<Dog*>(a)) {   // returns nullptr if cast fails
    d->fetch();   // only Dogs can fetch
}
```

#### Operator Overloading
```cpp
Box operator+(const Box& b) const {
    return Box(l + b.l, w + b.w, h + b.h);
}
Box b4 = b2 + b3;   // calls operator+ naturally
```

---

## 3. Internal Working

### Virtual Table (vtable)
Every class with at least one `virtual` function has a hidden **vtable** — a table of function pointers. Each object has a hidden **vptr** (vtable pointer) pointing to its class's vtable. When `makeSound()` is called through a base pointer, the vptr redirects to the correct derived function at runtime.

```
Animal*  →  [vptr] → Animal's vtable  → Animal::makeSound
Dog*     →  [vptr] → Dog's vtable     → Dog::makeSound
```

**Cost:** One pointer per object + one virtual dispatch per call (negligible in practice).

### Object Memory Layout
```
class Animal {
    string name;    // 32 bytes (string object)
    int age;        // 4 bytes
    [vptr]          // 8 bytes (added by compiler if virtual exists)
};
```

### Why Virtual Destructor is Mandatory
```cpp
Animal* a = new Dog("Max");
delete a;   // Without virtual destructor: only ~Animal() called → Dog resources leaked!
            // With virtual destructor: ~Dog() called first, then ~Animal() — correct!
```

---

## 4. Operations & Techniques

### The Rule of Three / Five / Zero

If a class manages a resource (heap memory, file handle, mutex):
- **Rule of Three:** If you define any of destructor, copy constructor, or copy assignment — define all three.
- **Rule of Five (C++11):** Add move constructor and move assignment.
- **Rule of Zero:** If you use RAII wrappers (smart pointers, `string`, `vector`), you need none of the above — the compiler-generated versions work correctly.

### Polymorphic Container Pattern
```cpp
// Store any Shape subtype through a base pointer
vector<Shape*> shapes = { new Circle(5), new Rectangle(4,6), new Triangle(3,4,5) };
for (auto* s : shapes) {
    s->draw();      // polymorphic dispatch
    s->describe();  // shared concrete method
}
for (auto* s : shapes) delete s;  // don't forget to free!
// Or use: vector<unique_ptr<Shape>> shapes; — auto-freed, no delete needed
```

---

## 5. Time & Space Complexity Table

| Operation | Time | Space | Notes |
|-----------|------|-------|-------|
| Object construction | O(1) | O(members) | Initialiser list is faster |
| Member access | O(1) | O(1) | Direct offset from base address |
| Virtual function call | O(1) | O(1) | One extra pointer dereference (vtable) |
| `dynamic_cast` | O(1) to O(hierarchy depth) | O(1) | RTTI traversal |
| Function overload resolution | O(1) | O(1) | Compile-time — no runtime cost |
| Operator overloading | Same as equivalent function | Same | No overhead |
| Destructor chain (depth d) | O(d) | O(1) | Unwinds inheritance chain |

---

## 6. Common Mistakes

- **Forgetting `virtual` destructor in base class** → derived class destructors not called → resource leaks when using polymorphism.
- **Object slicing:** `Animal a = *dog_ptr;` — copies only the `Animal` part; the `Dog` members are sliced off. Always use pointers or references for polymorphism.
- **Using `override` incorrectly** — if the signature doesn't match the base virtual function, it creates a new function instead of overriding. `override` keyword catches this at compile time.
- **Not initialising members in initialiser list** — members of class/struct types are default-constructed then copy-assigned (wasteful). Use initialiser list to construct directly.
- **Calling virtual functions from constructors** — the vtable isn't fully set up yet; the base version is called, not the derived.
- **Forgetting `const` on getters** — `getBalance()` without `const` can't be called on a `const BankAccount`.
- **Deleting through base pointer without virtual destructor** → undefined behavior.

---

## 7. Interview Relevance

| Topic | Common Questions |
|-------|-----------------|
| Four pillars | "Explain encapsulation with an example. What is abstraction?" |
| Virtual functions | "What is a vtable? When is a destructor called?" |
| Virtual destructor | "Why must a polymorphic base class destructor be virtual?" |
| Pure virtual | "What is an abstract class? Can you instantiate it?" |
| Overloading vs Overriding | "What is the difference? Which happens at compile time vs runtime?" |
| `dynamic_cast` | "When would you use `dynamic_cast`? What does it return if it fails?" |
| Constructor types | "What is a copy constructor? When is it called?" |
| Object slicing | "What is object slicing and how do you prevent it?" |
| `override` keyword | "What does the `override` keyword do? Is it mandatory?" |
| Rule of Three/Five | "What is the Rule of Three? When do you need a custom destructor?" |

---

## 8. Best Practices (C++ Specific)

```cpp
// ✅ Always declare virtual destructor in polymorphic base classes
virtual ~Shape() = default;

// ✅ Use override keyword — catches signature mismatches at compile time
double area() const override { ... }

// ✅ Use initialiser lists in constructors
BankAccount(string owner, double bal) : owner_(owner), balance_(bal) {}

// ✅ Use const on methods that don't modify state
double getBalance() const { return balance_; }

// ✅ Prefer smart pointers for polymorphic containers
vector<unique_ptr<Shape>> shapes;
shapes.push_back(make_unique<Circle>(5, "red"));
// No manual delete needed

// ✅ Mark classes not meant to be subclassed as `final`
class Singleton final { ... };

// ✅ Mark virtual functions that should not be further overridden as `final`
void draw() const override final { ... }
```

---

## 9. Summary

```
cpp/oops/ — What's Covered (01_oop.cpp)
├── Constructors: default, parameterised, copy + initialiser list
├── Destructors: lifecycle, reverse-order destruction, virtual destructor
├── Operator Overloading: Box::operator+
├── Encapsulation: BankAccount — private data + validated public interface
├── Abstraction: Shape abstract class with pure virtual area/perimeter/draw
├── Polymorphism (Runtime): Shape* pointing to Circle/Rectangle/Triangle
│                           — virtual dispatch via vtable
├── Polymorphism (Compile-time): Calculator method overloading
├── Inheritance: Animal → Dog/Cat — single inheritance
├── Method Overriding: Dog::makeSound overrides Animal::makeSound
└── dynamic_cast: safe downcast from Animal* → Dog*
```

**Key OOP Principles in Code:**

| Pillar | C++ Mechanism | Example in Code |
|--------|---------------|-----------------|
| Encapsulation | `private` members + public interface | `BankAccount` |
| Abstraction | Pure virtual functions (`= 0`) | `Shape` class |
| Inheritance | `class Derived : public Base` | `Dog : Animal` |
| Polymorphism | `virtual` + base class pointer/reference | `vector<Shape*>` |

---

> **Next Steps:** Head to `cpp/advanced/` for templates, move semantics, `std::optional`, `std::variant`, `constexpr`, and multithreading.
