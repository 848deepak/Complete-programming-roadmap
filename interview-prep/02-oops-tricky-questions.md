# 🧱 OOPs Tricky Interview Questions

> Concepts interviewers love to test — especially the subtle differences students get wrong.

---

## 1. Abstraction vs Encapsulation

### Concept
- **Abstraction:** Hiding *complexity* — showing only relevant interface (abstract classes, interfaces)
- **Encapsulation:** Hiding *data* — bundling data + methods, restricting direct access (private fields + getters)

### 📌 Interview Tip
> "Abstraction is about WHAT an object does. Encapsulation is about HOW it hides its internals."

### Example
```cpp
// Encapsulation: private data + public interface
class BankAccount {
    double balance;  // private — hidden
public:
    void deposit(double amt) { if (amt > 0) balance += amt; }
    double getBalance() { return balance; }
};

// Abstraction: hiding complexity behind interface
class Shape {
public:
    virtual double area() = 0;  // User doesn't know HOW area is computed
};
```

### ⚠️ Trap
> Students say they're the same thing. They're related but distinct. Encapsulation is a mechanism; abstraction is a concept.

---

## 2. Virtual Functions & VTable

### Key Question: "What happens when you call a virtual function?"

```cpp
class Base {
public:
    virtual void show() { cout << "Base\n"; }
};
class Derived : public Base {
public:
    void show() override { cout << "Derived\n"; }
};

Base* ptr = new Derived();
ptr->show();  // Output: "Derived" — resolved at RUNTIME via vtable
```

### 📌 Interview Tip
> Every class with virtual functions has a **vtable** (table of function pointers). Each object has a **vptr** pointing to its class's vtable. This is how runtime polymorphism works.

### ⚠️ Trap
> "Can constructors be virtual?" → **NO** (object type must be known at construction). "Can destructors be virtual?" → **YES, and they SHOULD BE** in base classes with virtual functions.

---

## 3. Diamond Problem (Multiple Inheritance)

```cpp
class A { public: void show() { cout << "A\n"; } };
class B : public A {};
class C : public A {};
class D : public B, public C {};  // Diamond! D has TWO copies of A

D d;
// d.show();  // ❌ AMBIGUOUS — which A::show()?

// Fix: Virtual inheritance
class B : virtual public A {};
class C : virtual public A {};
class D : public B, public C {};  // Now ONE copy of A
```

### 📌 Interview Tip
> Java avoids this by not allowing multiple class inheritance (only interfaces). C++ uses virtual inheritance.

---

## 4. Abstract Class vs Interface

| Feature | Abstract Class | Interface (Java) |
|---------|---------------|------------------|
| Methods | Can have both abstract and concrete | All abstract (pre-Java 8) |
| Variables | Can have state (fields) | Only constants |
| Constructors | Yes | No |
| Inheritance | Single | Multiple |
| Use when | Sharing code among related classes | Defining a contract |

### ⚠️ Trap
> "When to use which?" → Use abstract class when classes share **behavior**. Use interface when unrelated classes need the **same capability**.

---

## 5. Shallow Copy vs Deep Copy

```cpp
class MyClass {
    int* data;
public:
    MyClass(int val) { data = new int(val); }
    
    // Shallow copy (DEFAULT) — both objects point to SAME memory
    // If one deletes it, the other has a dangling pointer!
    
    // Deep copy — allocate new memory
    MyClass(const MyClass& other) {
        data = new int(*other.data);  // New allocation
    }
};
```

### 📌 Interview Tip
> Always implement the **Rule of Three** in C++: if you need a custom destructor, you also need a custom copy constructor and copy assignment operator.

---

## 6. SOLID Principles (Quick Reference)

| Principle | Meaning | Violation Example |
|-----------|---------|------------------|
| **S** — Single Responsibility | One class = one reason to change | `User` class that handles DB + email |
| **O** — Open/Closed | Open for extension, closed for modification | Adding features by modifying existing code |
| **L** — Liskov Substitution | Subclass must be substitutable for base | `Square extends Rectangle` breaks setWidth |
| **I** — Interface Segregation | Don't force unused interfaces | `Worker` interface with both `work()` and `eat()` |
| **D** — Dependency Inversion | Depend on abstractions, not concretions | Hardcoding `MySQLDB` instead of `Database` interface |

### ⚠️ Trap
> Liskov Substitution is the most tricky. `Square IS-A Rectangle` mathematically, but in code, if `setWidth` doesn't also `setHeight`, it violates LSP.

---

## 7. Static vs Dynamic Binding

| | Static (Early) Binding | Dynamic (Late) Binding |
|--|---|---|
| **When** | Compile time | Runtime |
| **How** | Function overloading, non-virtual | Virtual functions, vtable |
| **Speed** | Faster (no lookup) | Slightly slower (vtable lookup) |

```cpp
Base* p = new Derived();
p->nonVirtual();  // Static binding → Base::nonVirtual()
p->virtualFunc(); // Dynamic binding → Derived::virtualFunc()
```
