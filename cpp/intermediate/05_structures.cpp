// ============================================================
// MODULE 08 | C++ INTERMEDIATE → Structures
// ============================================================
// DESCRIPTION:
//   Covers struct (user-defined aggregate type), nested structs,
//   typedef, pointer to struct, struct vs class, and array of structs.
//   Structures are the foundation of custom data types in C.
//
// COMPILE & RUN:
//   g++ -std=c++17 05_structures.cpp -o out && ./out
//
// KEY CONCEPTS:
//   struct   : Groups multiple related variables under one name
//   typedef  : Creates an alias for a type name
//   ->       : Dereference + access member via pointer ((*ptr).member shorthand)
//
// COMPLEXITY:
//   Time  : O(1) per struct operation; O(n) for array operations
//   Space : O(n) for an array of n structs
// ============================================================

#include <iostream>
#include <string>
#include <algorithm>   // sort
using namespace std;

// ============================================================
// BASIC STRUCT: Point
// ============================================================
// All members are PUBLIC by default in a struct.

struct Point {
    double x;   // x-coordinate
    double y;   // y-coordinate
};

/**
 * Computes Euclidean distance between two points.
 * Formula: sqrt((x2-x1)² + (y2-y1)²)
 */
double distance(const Point& a, const Point& b) {
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    return sqrt(dx * dx + dy * dy);
}

// ============================================================
// NESTED STRUCT: Student with Address
// ============================================================
// One struct can contain another as a member.

struct Address {
    string city;
    string state;
    int    pincode;
};

struct Student {
    int     rollNo;
    string  name;
    double  gpa;
    Address addr;   // nested struct
};

/**
 * Displays a Student's details to stdout.
 */
void displayStudent(const Student& s) {
    cout << "  Roll: " << s.rollNo
         << "  Name: " << s.name
         << "  GPA: "  << s.gpa
         << "  City: " << s.addr.city
         << "\n";
}

// ============================================================
// TYPEDEF: Create a cleaner alias
// ============================================================
// Traditional C-style typedef; C++ also supports 'using'.

typedef struct {
    int   id;
    float salary;
    char  grade;   // 'A', 'B', or 'C'
} Employee;

// Equivalent modern C++ style:
// using Employee = struct { ... };

// ============================================================
// STRUCT WITH MEMBER FUNCTIONS (closer to a class)
// ============================================================
// Structs in C++ CAN have member functions, constructors, etc.

struct Rectangle {
    double length;
    double width;

    // Constructor: initialises members directly
    Rectangle(double l, double w) : length(l), width(w) {}

    /** Returns area of the rectangle. */
    double area()      const { return length * width; }

    /** Returns perimeter of the rectangle. */
    double perimeter() const { return 2 * (length + width); }

    /**
     * Scales the rectangle by a factor.
     * @param factor  Multiplier applied to both dimensions
     */
    void scale(double factor) {
        length *= factor;
        width  *= factor;
    }
};

// ============================================================
// MAIN
// ============================================================
int main() {

    // ================================================================
    // SECTION 1: BASIC STRUCT — POINT
    // ================================================================
    cout << "=== POINT STRUCT ===" << endl;

    Point p1 = {3.0, 4.0};   // aggregate initialization
    Point p2 = {0.0, 0.0};   // origin

    cout << "p1 = (" << p1.x << ", " << p1.y << ")\n";
    cout << "p2 = (" << p2.x << ", " << p2.y << ")\n";
    cout << "Distance(p1, p2) = " << distance(p1, p2) << "\n";  // 5.0

    // ================================================================
    // SECTION 2: POINTER TO STRUCT
    // ================================================================
    // Use '->' to access members through a pointer (shorthand for (*ptr).member)
    // ----------------------------------------------------------------
    cout << "\n=== POINTER TO STRUCT ===" << endl;

    Point* pPtr = new Point{6.0, 8.0};     // allocate on heap
    cout << "Via pointer ->  x=" << pPtr->x << " y=" << pPtr->y << "\n";
    cout << "Via (*ptr).     x=" << (*pPtr).x << "\n";   // equivalent, less readable
    cout << "Distance from origin = " << distance(*pPtr, {0, 0}) << "\n";  // 10.0
    delete pPtr;    // free heap memory
    pPtr = nullptr;

    // ================================================================
    // SECTION 3: NESTED STRUCT — STUDENT
    // ================================================================
    cout << "\n=== NESTED STRUCT (Student) ===" << endl;

    Student s1 = {101, "Deepak",  8.9, {"Delhi",   "Delhi", 110001}};
    Student s2 = {102, "Anjali",  9.2, {"Mumbai",  "MH",    400001}};
    Student s3 = {103, "Rohan",   7.5, {"Chennai", "TN",    600001}};

    Student students[] = {s1, s2, s3};
    int count = 3;

    cout << "All students:\n";
    for (int i = 0; i < count; i++) displayStudent(students[i]);

    // Sort students by GPA in descending order
    sort(students, students + count, [](const Student& a, const Student& b) {
        return a.gpa > b.gpa;    // descending
    });

    cout << "\nSorted by GPA (descending):\n";
    for (int i = 0; i < count; i++) displayStudent(students[i]);

    // ================================================================
    // SECTION 4: TYPEDEF STRUCT
    // ================================================================
    cout << "\n=== TYPEDEF (Employee) ===" << endl;

    Employee emp1 = {1001, 55000.0f, 'A'};
    Employee emp2 = {1002, 42000.0f, 'B'};

    // Print using positional access
    printf("  Emp %d | Salary %.2f | Grade %c\n", emp1.id, emp1.salary, emp1.grade);
    printf("  Emp %d | Salary %.2f | Grade %c\n", emp2.id, emp2.salary, emp2.grade);

    // ================================================================
    // SECTION 5: STRUCT WITH MEMBER FUNCTIONS
    // ================================================================
    cout << "\n=== STRUCT WITH METHODS (Rectangle) ===" << endl;

    Rectangle rect(4.0, 6.0);
    cout << "  " << rect.length << " × " << rect.width << "\n";
    cout << "  Area      = " << rect.area()      << "\n";   // 24
    cout << "  Perimeter = " << rect.perimeter() << "\n";   // 20

    rect.scale(2.0);   // double the dimensions
    cout << "After scale(2):\n";
    cout << "  " << rect.length << " × " << rect.width << "\n";  // 8 × 12
    cout << "  Area      = " << rect.area() << "\n";   // 96

    // ================================================================
    // SECTION 6: STRUCT vs CLASS
    // ================================================================
    cout << "\n=== STRUCT vs CLASS ===" << endl;
    cout << "  struct: all members are PUBLIC by default\n";
    cout << "  class:  all members are PRIVATE by default\n";
    cout << "  Both support constructors, methods, inheritance, etc.\n";
    cout << "  Convention: use struct for plain data, class for encapsulated objects.\n";

    return 0;
}
// ============================================================
// KEY TAKEAWAYS:
//   1. Use struct for grouping related plain data (e.g., Point, Address)
//   2. Use -> to access members via a pointer
//   3. Structs CAN have constructors and member functions in C++
//   4. 'typedef struct' is a C-style pattern; 'using' is the modern C++ way
// ============================================================
