// ============================================================
// MODULE 09 | C++ OOP → Full Object-Oriented Programming
// ============================================================
// DESCRIPTION:
//   Comprehensive coverage of all OOP principles in C++:
//   Classes, Constructors & Destructors, Encapsulation,
//   Inheritance, Polymorphism, Abstraction, Virtual Functions,
//   Method Overloading & Overriding, and Interfaces (pure abstract).
//
// COMPILE & RUN:
//   g++ -std=c++17 -lm 01_oop.cpp -o out && ./out
//
// FOUR PILLARS OF OOP:
//   1. Encapsulation  : bundling data + methods; hiding internals
//   2. Inheritance    : deriving new classes from existing ones
//   3. Polymorphism   : one interface, many implementations
//   4. Abstraction    : hiding complexity behind a simple interface
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

// ============================================================
// SECTION 1: CONSTRUCTORS & DESTRUCTORS
// ============================================================

class Box {
    double l, w, h;
public:
    // Default constructor — called when no arguments are provided
    Box() : l(1), w(1), h(1) {
        cout << "  Box() default constructor\n";
    }

    // Parameterised constructor — called with specific values
    Box(double l, double w, double h) : l(l), w(w), h(h) {
        cout << "  Box(" << l << "," << w << "," << h << ") parameterised\n";
    }

    // Copy constructor — called when one object is initialised from another
    Box(const Box& other) : l(other.l), w(other.w), h(other.h) {
        cout << "  Box copy constructor\n";
    }

    // Destructor — called when the object goes out of scope or is deleted
    ~Box() {
        cout << "  Box(" << l << "," << w << "," << h << ") destroyed\n";
    }

    double volume() const { return l * w * h; }

    // Operator overloading: + adds two boxes
    Box operator+(const Box& b) const {
        return Box(l + b.l, w + b.w, h + b.h);
    }

    void print() const {
        printf("  Box: %.1f × %.1f × %.1f  Vol=%.1f\n", l, w, h, volume());
    }
};

// ============================================================
// SECTION 2: ENCAPSULATION — BankAccount
// ============================================================
// Private data + public interface = encapsulation.
// Never expose raw data. Always use getters/setters for control.

class BankAccount {
    string owner;
    double balance;         // private — cannot be accessed directly
    int    transactionCount;

public:
    // Constructor: initialises account
    BankAccount(const string& owner, double initialBalance)
        : owner(owner), balance(initialBalance), transactionCount(0) {}

    // Getters (read-only access)
    double getBalance()      const { return balance; }
    string getOwner()        const { return owner; }
    int    getTransactions() const { return transactionCount; }

    // Mutators with validation
    void deposit(double amount) {
        if (amount <= 0) { cout << "  ERROR: deposit amount must be positive\n"; return; }
        balance += amount;
        transactionCount++;
        printf("  Deposited ₹%.2f  |  New balance: ₹%.2f\n", amount, balance);
    }

    bool withdraw(double amount) {
        if (amount <= 0) { cout << "  ERROR: amount must be positive\n"; return false; }
        if (amount > balance) { cout << "  ERROR: Insufficient funds\n"; return false; }
        balance -= amount;
        transactionCount++;
        printf("  Withdrew  ₹%.2f  |  New balance: ₹%.2f\n", amount, balance);
        return true;
    }

    void printStatement() const {
        printf("  Owner: %-12s | Balance: ₹%10.2f | Txns: %d\n",
               owner.c_str(), balance, transactionCount);
    }
};

// ============================================================
// SECTION 3: ABSTRACTION + POLYMORPHISM — Shape Hierarchy
// ============================================================
// Abstract class: has at least one PURE VIRTUAL function (= 0).
// Cannot instantiate an abstract class directly.
// Subclasses MUST override all pure virtual methods.

class Shape {
protected:
    string color;

public:
    explicit Shape(const string& c = "white") : color(c) {}
    virtual ~Shape() = default;   // virtual destructor — REQUIRED for polymorphism

    // Pure virtual → makes Shape abstract (interface contract)
    virtual double area()      const = 0;
    virtual double perimeter() const = 0;
    virtual void   draw()      const = 0;

    // Concrete method shared by all shapes
    void describe() const {
        printf("  %-12s | color=%-8s | area=%8.2f | perimeter=%.2f\n",
               typeid(*this).name(), color.c_str(), area(), perimeter());
    }
};

class Circle : public Shape {
    double radius;
public:
    Circle(double r, const string& c = "red") : Shape(c), radius(r) {}

    double area()      const override { return M_PI * radius * radius; }
    double perimeter() const override { return 2 * M_PI * radius; }
    void   draw()      const override {
        cout << "  Drawing circle with radius=" << radius << "\n";
    }
};

class Rectangle : public Shape {
    double len, wid;
public:
    Rectangle(double l, double w, const string& c = "blue")
        : Shape(c), len(l), wid(w) {}

    double area()      const override { return len * wid; }
    double perimeter() const override { return 2 * (len + wid); }
    void   draw()      const override {
        cout << "  Drawing rectangle " << len << " × " << wid << "\n";
    }
};

class Triangle : public Shape {
    double a, b, c_side;   // three sides
public:
    Triangle(double a, double b, double c, const string& color = "green")
        : Shape(color), a(a), b(b), c_side(c) {}

    double perimeter() const override { return a + b + c_side; }
    double area() const override {
        // Heron's formula: s = (a+b+c)/2; area = sqrt(s(s-a)(s-b)(s-c))
        double s = perimeter() / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c_side));
    }
    void draw() const override {
        cout << "  Drawing triangle with sides " << a << "," << b << "," << c_side << "\n";
    }
};

// ============================================================
// SECTION 4: INHERITANCE — Animal Hierarchy
// ============================================================
// Single inheritance: Dog and Cat both inherit from Animal.
// Multi-level inheritance chain: Animal → Pet → Dog

class Animal {
protected:
    string name;
    int    age;

public:
    Animal(const string& n, int a) : name(n), age(a) {}
    virtual ~Animal() = default;

    // Virtual method: CAN be overridden (but doesn't have to be)
    virtual void makeSound() const { cout << "  " << name << ": ...\n"; }

    void display() const {
        cout << "  " << name << " (age=" << age << ")\n";
    }
    string getName() const { return name; }
};

class Dog : public Animal {
    string breed;
public:
    Dog(const string& n, int a, const string& b)
        : Animal(n, a), breed(b) {}

    void makeSound() const override {   // Method OVERRIDING
        cout << "  " << name << " [" << breed << "] says: Woof!\n";
    }
    void fetch() const {
        cout << "  " << name << " fetches the ball!\n";
    }
};

class Cat : public Animal {
public:
    Cat(const string& n, int a) : Animal(n, a) {}
    void makeSound() const override {
        cout << "  " << name << " says: Meow!\n";
    }
};

// ============================================================
// SECTION 5: METHOD OVERLOADING (Compile-time Polymorphism)
// ============================================================
class Calculator {
public:
    // Same name, different signature — compiler picks by argument type
    int    add(int a, int b)             { return a + b; }
    double add(double a, double b)       { return a + b; }
    int    add(int a, int b, int c)      { return a + b + c; }
    string add(string a, const string& b) { return a + b; }   // concatenate
};

// ============================================================
// MAIN
// ============================================================
int main() {

    // --- Constructors & Destructors ---
    cout << "=== CONSTRUCTORS & DESTRUCTORS ===" << endl;
    {
        Box b1;             // default
        Box b2(3, 4, 5);    // parameterised
        Box b3 = b2;        // copy
        b1.print();  b2.print();
        Box b4 = b2 + b3;   // operator+
        b4.print();
    }   // all boxes destroyed here — destructors fire in REVERSE order

    // --- Encapsulation ---
    cout << "\n=== ENCAPSULATION (BankAccount) ===" << endl;
    BankAccount acc("Deepak", 10000.0);
    acc.printStatement();
    acc.deposit(5000);
    acc.withdraw(3000);
    acc.withdraw(20000);   // edge case: insufficient funds
    acc.deposit(-500);     // edge case: negative deposit
    acc.printStatement();

    // --- Abstraction & Polymorphism ---
    cout << "\n=== ABSTRACTION & POLYMORPHISM (Shapes) ===" << endl;
    vector<Shape*> shapes = {
        new Circle(5, "red"),
        new Rectangle(4, 6, "blue"),
        new Triangle(3, 4, 5, "green")
    };

    for (auto* s : shapes) {
        s->draw();
        s->describe();
    }
    // Cleanup — virtual destructor ensures correct derived destructor is called
    for (auto* s : shapes) delete s;

    // --- Inheritance ---
    cout << "\n=== INHERITANCE (Animals) ===" << endl;
    vector<Animal*> animals = {
        new Animal("Lion", 8),
        new Dog("Max", 3, "Labrador"),
        new Cat("Luna", 2)
    };

    cout << "Virtual dispatch (makeSound):\n";
    for (auto* a : animals) a->makeSound();   // calls correct subclass version

    // Safe downcast with dynamic_cast
    if (Dog* d = dynamic_cast<Dog*>(animals[1])) {
        d->fetch();   // only Dogs can fetch
    }
    for (auto* a : animals) delete a;

    // --- Method Overloading ---
    cout << "\n=== METHOD OVERLOADING ===" << endl;
    Calculator calc;
    cout << "  add(5, 3)          = " << calc.add(5, 3)           << "\n";   // int
    cout << "  add(2.5, 3.1)      = " << calc.add(2.5, 3.1)       << "\n";   // double
    cout << "  add(1, 2, 3)       = " << calc.add(1, 2, 3)         << "\n";   // int×3
    cout << "  add(\"Hello\",\" World\") = " << calc.add("Hello", " World") << "\n"; // string

    return 0;
}
// ============================================================
// OOP SUMMARY TABLE:
//   Concept         | Mechanism in C++
//   Encapsulation   | private members + public getters/setters
//   Inheritance     : class Derived : public Base
//   Polymorphism    : virtual functions + base class pointers
//   Abstraction     : pure virtual functions = 0 (abstract class)
//   Overloading     : same name, different signature (compile-time)
//   Overriding      : override keyword in derived class (runtime)
// ============================================================
