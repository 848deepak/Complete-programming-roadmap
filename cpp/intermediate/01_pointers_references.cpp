// ============================================================
// MODULE 07 | C++ INTERMEDIATE → Pointers & References
// ============================================================
// DESCRIPTION:
//   Covers raw pointers, pointer arithmetic, references, dynamic
//   memory allocation (new/delete), pointer-to-function, smart
//   pointers (unique_ptr, shared_ptr), and nullptr safety.
//
// COMPILE & RUN:
//   g++ -std=c++17 01_pointers_references.cpp -o out && ./out
//
// KEY CONCEPTS:
//   Pointer   : variable that stores a MEMORY ADDRESS
//   Reference : alias (alternative name) for an existing variable
//   Smart ptr : RAII wrapper — auto-deletes when out of scope
//
// COMPLEXITY ANALYSIS:
//   Time  : O(1) for all pointer/reference operations
//   Space : O(1) for stack; O(n) for heap allocations
// ============================================================

#include <iostream>
#include <memory>    // unique_ptr, shared_ptr, make_unique, make_shared
#include <string>
using namespace std;

// ============================================================
// DEMO CLASS for Smart Pointer Lifecycle
// ============================================================
class Resource {
    string name;
public:
    /** Constructor: runs when object is created */
    explicit Resource(const string& n) : name(n) {
        cout << "  [+] Resource(\"" << name << "\") created\n";
    }
    /** Destructor: runs when object goes out of scope or is deleted */
    ~Resource() {
        cout << "  [-] Resource(\"" << name << "\") destroyed\n";
    }
    void use() const { cout << "  [*] Using: " << name << "\n"; }
};

// ============================================================
// SWAP: Pointer vs Reference
// ============================================================

/**
 * Swap using POINTERS: caller passes addresses (&a, &b).
 * The function dereferences (*a, *b) to access actual values.
 */
void swapPtr(int* a, int* b) {
    int temp = *a;   // dereference: read value at address
    *a = *b;
    *b = temp;
}

/**
 * Swap using REFERENCES: caller passes variables directly.
 * The function works on the original variables transparently.
 * Preferred in C++ — cleaner syntax, no nullptr risk.
 */
void swapRef(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// ============================================================
// POINTER-TO-FUNCTION
// ============================================================
// A function pointer stores the address of a function.
// Syntax: returnType (*name)(paramTypes)

int add(int x, int y) { return x + y; }
int mul(int x, int y) { return x * y; }

/**
 * Applies a binary operation using a function pointer.
 * @param func  Pointer to a function (int, int) → int
 */
int applyOp(int (*func)(int, int), int x, int y) {
    return func(x, y);   // call through the pointer
}

// ============================================================
// MAIN
// ============================================================
int main() {

    // ================================================================
    // SECTION 1: POINTER BASICS
    // ================================================================
    cout << "=== POINTER BASICS ===" << endl;

    int x = 42;
    int* ptr = &x;         // ptr holds the ADDRESS of x

    cout << "x       = " << x    << "\n";         // value: 42
    cout << "&x      = " << &x   << "\n";         // address of x
    cout << "ptr     = " << ptr  << "\n";         // same address
    cout << "*ptr    = " << *ptr << "\n";         // dereference: value at that address (42)

    *ptr = 99;             // modify x through the pointer
    cout << "After *ptr=99, x = " << x << "\n";  // 99

    // ================================================================
    // SECTION 2: POINTER ARITHMETIC
    // ================================================================
    // When you increment a pointer, it moves by sizeof(element) bytes.
    // ptr + 1 moves to the NEXT int, not just the next byte.
    // ----------------------------------------------------------------
    cout << "\n=== POINTER ARITHMETIC ===" << endl;

    int arr[] = {10, 20, 30, 40, 50};
    int* p = arr;          // points to arr[0]

    cout << "Array elements using pointer arithmetic:\n";
    for (int i = 0; i < 5; i++) {
        cout << "  *(p+" << i << ") = " << *(p + i) << "\n";
    }

    // ================================================================
    // SECTION 3: REFERENCES
    // ================================================================
    // A reference MUST be initialized when declared.
    // It cannot be re-assigned to refer to a different variable.
    // ----------------------------------------------------------------
    cout << "\n=== REFERENCES ===" << endl;

    int val = 10;
    int& ref = val;    // ref is now an alias for val

    cout << "val = " << val << ",  ref = " << ref << "\n";
    ref = 50;          // modifying ref modifies val
    cout << "After ref=50, val = " << val << "\n";    // 50
    cout << "Same address? " << (&val == &ref ? "yes" : "no") << "\n"; // yes

    // ================================================================
    // SECTION 4: SWAP DEMO — Pointer vs Reference
    // ================================================================
    cout << "\n=== SWAP DEMO ===" << endl;

    int a = 5, b = 9;
    cout << "Original: a=" << a << " b=" << b << "\n";

    swapPtr(&a, &b);     // pass addresses
    cout << "swapPtr:  a=" << a << " b=" << b << "\n";

    swapRef(a, b);       // pass variables directly
    cout << "swapRef:  a=" << a << " b=" << b << "\n";

    // ================================================================
    // SECTION 5: DYNAMIC MEMORY (new / delete)
    // ================================================================
    // 'new' allocates on the HEAP — persists until explicily deleted.
    // 'delete' returns memory to the OS. Forgetting → memory leak!
    // Always set the pointer to nullptr after deleting.
    // ----------------------------------------------------------------
    cout << "\n=== DYNAMIC MEMORY ===" << endl;

    // Single value
    int* dyn = new int(777);
    cout << "Dynamic int: " << *dyn << "\n";
    delete dyn;           // free memory
    dyn = nullptr;        // prevent dangling pointer

    // Dynamic array
    int size = 5;
    int* dynArr = new int[size];
    for (int i = 0; i < size; i++) dynArr[i] = i * 10;
    cout << "Dynamic array: ";
    for (int i = 0; i < size; i++) cout << dynArr[i] << " ";
    cout << "\n";
    delete[] dynArr;      // note: delete[] for arrays, not delete
    dynArr = nullptr;

    // ================================================================
    // SECTION 6: SMART POINTERS (C++11)
    // ================================================================
    // Smart pointers AUTOMATICALLY manage memory — no manual delete needed.
    // They follow RAII: Resource Acquisition Is Initialization.
    // ----------------------------------------------------------------
    cout << "\n=== SMART POINTERS ===" << endl;

    // --- unique_ptr: SOLE owner — cannot be copied, only moved ---
    cout << "\nunique_ptr (exclusive ownership):\n";
    {
        auto uptr = make_unique<Resource>("File");   // allocated
        uptr->use();
        // Resource is automatically deleted when uptr goes out of scope
    }  // ← destructor fires here

    // --- shared_ptr: SHARED ownership — reference counted ---
    cout << "\nshared_ptr (shared ownership):\n";
    auto sp1 = make_shared<Resource>("Database");
    cout << "  use_count after sp1 = " << sp1.use_count() << "\n";    // 1
    {
        auto sp2 = sp1;    // sp2 shares ownership with sp1
        cout << "  use_count after sp2 = " << sp1.use_count() << "\n"; // 2
    }   // sp2 goes out of scope — count decreases to 1
    cout << "  use_count after sp2 destroyed = " << sp1.use_count() << "\n"; // 1
    // Resource destroyed when sp1 goes out of scope at end of main

    // ================================================================
    // SECTION 7: POINTER-TO-FUNCTION
    // ================================================================
    cout << "\n=== FUNCTION POINTERS ===" << endl;

    int (*op)(int, int);   // declare a function pointer

    op = add;              // point to 'add'
    cout << "applyOp(add, 3, 4) = " << applyOp(op, 3, 4) << "\n";   // 7

    op = mul;              // reassign to 'mul'
    cout << "applyOp(mul, 3, 4) = " << applyOp(op, 3, 4) << "\n";   // 12

    // ================================================================
    // SECTION 8: nullptr (C++11 — safer than NULL)
    // ================================================================
    cout << "\n=== nullptr ===" << endl;

    int* nullPtr = nullptr;
    cout << "nullPtr is null: " << (nullPtr == nullptr ? "yes" : "no") << "\n";

    // Always check before dereferencing a pointer!
    if (nullPtr != nullptr) {
        cout << *nullPtr;   // safe — won't execute
    } else {
        cout << "Safe guard: pointer is null, skipping dereference\n";
    }

    return 0;
}
// ============================================================
// COMMON MISTAKES TO AVOID:
//   1. Dereferencing nullptr        → segfault
//   2. Forgetting delete/delete[]   → memory leak
//   3. double-free (delete twice)   → undefined behavior
//   4. Dangling pointer (using after delete) → undefined behavior
// BEST PRACTICE: Use smart pointers (unique_ptr/shared_ptr) always.
// ============================================================
