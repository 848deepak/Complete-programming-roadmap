 // ============================================================
// MODULE | C++ INTERMEDIATE → Exception Handling
// ============================================================
// DESCRIPTION:
//   Comprehensive guide to C++ exception handling:
//   try-catch-throw, exception hierarchy, custom exceptions,
//   nested try, noexcept, RAII for exception safety.
//
// COMPILE & RUN:
//   g++ -std=c++17 02_exception_handling.cpp -o out && ./out
//
// SAMPLE OUTPUT:
//   === BASIC TRY-CATCH ===
//   Caught: Division by zero!
//   === EXCEPTION HIERARCHY ===
//   Caught std::runtime_error: File not found: config.txt
//   ...
//
// COMPLEXITY:
//   Throwing an exception: O(1) (stack unwinding adds overhead)
//   Catching an exception: O(depth of call stack)
// ============================================================

#include <iostream>
#include <stdexcept>    // std::runtime_error, std::invalid_argument, std::out_of_range
#include <string>
#include <vector>
#include <memory>       // std::unique_ptr (RAII demo)
#include <fstream>
using namespace std;

// ============================================================
// SECTION 1: BASIC try-catch-throw
// ============================================================
// try   : wraps code that might throw
// catch : handles a specific exception type
// throw : signals an error condition to the caller
// ------------------------------------------------------------ 

/**
 * Safe integer division — throws std::invalid_argument if divisor is 0.
 *
 * @param a  Dividend
 * @param b  Divisor (must not be 0)
 * @return   a / b
 *
 * Time: O(1)  |  Space: O(1)
 * Edge case: b == 0 → throws
 */
double safeDivide(double a, double b) {
    if (b == 0)
        throw invalid_argument("Division by zero! Divisor cannot be 0.");
    return a / b;
}

// ============================================================
// SECTION 2: STANDARD EXCEPTION HIERARCHY
// ============================================================
//
//  std::exception
//  ├── std::logic_error
//  │   ├── std::invalid_argument   ← bad function argument
//  │   ├── std::domain_error       ← math domain error
//  │   ├── std::length_error       ← exceeds permitted length
//  │   └── std::out_of_range       ← index/value out of range
//  └── std::runtime_error
//      ├── std::range_error        ← computed value out of range
//      ├── std::overflow_error     ← arithmetic overflow
//      └── std::underflow_error    ← arithmetic underflow
//
// Rule: Catch by CONST REFERENCE to avoid slicing and copying.
// ------------------------------------------------------------ 

void demonstrateStdExceptions() {
    cout << "\n=== STANDARD EXCEPTION HIERARCHY ===" << endl;

    // --- std::out_of_range ---
    try {
        vector<int> v = {1, 2, 3};
        cout << v.at(10) << endl;   // .at() does bounds checking & throws
    }
    catch (const out_of_range& e) {
        cout << "out_of_range: " << e.what() << "\n";
    }

    // --- std::invalid_argument ---
    try {
        int x = stoi("abc");   // cannot convert non-numeric string
        (void)x;
    }
    catch (const invalid_argument& e) {
        cout << "invalid_argument: " << e.what() << "\n";
    }

    // --- std::runtime_error ---
    try {
        throw runtime_error("File not found: config.txt");
    }
    catch (const runtime_error& e) {
        cout << "runtime_error: " << e.what() << "\n";
    }

    // --- Catch base class std::exception (catches any above) ---
    try {
        throw overflow_error("Arithmetic overflow in computation");
    }
    catch (const exception& e) {
        // Polymorphic catch — e.what() calls the correct derived what()
        cout << "std::exception (base): " << e.what() << "\n";
    }
}

// ============================================================
// SECTION 3: CUSTOM EXCEPTIONS
// ============================================================
// Inherit from std::exception or std::runtime_error.
// Override what() to provide a meaningful message.
// ------------------------------------------------------------ 

/**
 * Custom exception representing a negative-value error in financial ops.
 */
class NegativeAmountException : public runtime_error {
    double amount_;   // the invalid value that caused the exception
public:
    explicit NegativeAmountException(double amt)
        : runtime_error("Amount cannot be negative: " + to_string(amt))
        , amount_(amt) {}

    double amount() const { return amount_; }   // extra accessor
};

/**
 * Custom exception for failed database connections.
 */
class DatabaseException : public runtime_error {
    string host_;
    int    port_;
public:
    DatabaseException(const string& host, int port, const string& reason)
        : runtime_error("DB connection failed [" + host + ":" + to_string(port) + "] — " + reason)
        , host_(host), port_(port) {}

    string host() const { return host_; }
    int    port() const { return port_; }
};

void demonstrateCustomExceptions() {
    cout << "\n=== CUSTOM EXCEPTIONS ===" << endl;

    // NegativeAmountException
    try {
        double deposit = -500.0;
        if (deposit < 0) throw NegativeAmountException(deposit);
    }
    catch (const NegativeAmountException& e) {
        cout << "Caught NegativeAmountException: " << e.what() << "\n";
        cout << "  Invalid amount was: " << e.amount() << "\n";
    }

    // DatabaseException
    try {
        throw DatabaseException("db.example.com", 5432, "Connection refused");
    }
    catch (const DatabaseException& e) {
        cout << "Caught DatabaseException: " << e.what() << "\n";
        cout << "  Host=" << e.host() << "  Port=" << e.port() << "\n";
    }
}

// ============================================================
// SECTION 4: MULTIPLE CATCH BLOCKS + CATCH-ALL
// ============================================================
// Always order catches from MOST SPECIFIC to LEAST SPECIFIC.
// catch(...) catches everything — use as last resort.
// ------------------------------------------------------------ 

void tryCatchOrder(int scenario) {
    try {
        if (scenario == 1) throw invalid_argument("bad input");
        if (scenario == 2) throw runtime_error("runtime failure");
        if (scenario == 3) throw 42;            // non-exception type!
        if (scenario == 4) throw string("oops");
    }
    catch (const invalid_argument& e) {
        cout << "  [invalid_argument] " << e.what() << "\n";
    }
    catch (const runtime_error& e) {
        cout << "  [runtime_error] " << e.what() << "\n";
    }
    catch (const exception& e) {
        cout << "  [exception base] " << e.what() << "\n";
    }
    catch (int code) {
        cout << "  [int exception] code=" << code << "\n";
    }
    catch (...) {
        cout << "  [catch-all] Unknown exception type\n";
    }
}

void demonstrateMultipleCatch() {
    cout << "\n=== MULTIPLE CATCH BLOCKS ===" << endl;
    for (int i = 1; i <= 4; i++) {
        cout << "Scenario " << i << ": ";
        tryCatchOrder(i);
    }
}

// ============================================================
// SECTION 5: NESTED TRY-CATCH + RE-THROWING
// ============================================================
// Re-throw with `throw;` (no argument) preserves the original exception.
// Use when you want to log locally but let the caller handle it.
// ------------------------------------------------------------ 

void innerFunction() {
    throw runtime_error("Something went wrong in innerFunction");
}

void outerFunction() {
    try {
        innerFunction();
    }
    catch (const exception& e) {
        cout << "  outerFunction caught: " << e.what() << " — re-throwing...\n";
        throw;   // re-throw original exception; don't use throw e (would slice!)
    }
}

void demonstrateRethrow() {
    cout << "\n=== NESTED TRY + RE-THROW ===" << endl;
    try {
        outerFunction();
    }
    catch (const exception& e) {
        cout << "  main caught after re-throw: " << e.what() << "\n";
    }
}

// ============================================================
// SECTION 6: noexcept SPECIFIER
// ============================================================
// noexcept: declares that a function NEVER throws.
// If it does throw anyway, std::terminate() is called immediately.
// Use noexcept for destructors, move constructors, and leaf utilities.
// ------------------------------------------------------------ 

int safeAdd(int a, int b) noexcept {
    return a + b;   // guaranteed to never throw
}

// noexcept(condition): conditionally noexcept
template<typename T>
T getValue(const vector<T>& v, size_t i) noexcept(false) {
    return v.at(i);   // CAN throw out_of_range
}

void demonstrateNoexcept() {
    cout << "\n=== noexcept ===" << endl;
    cout << "safeAdd(3,4) = " << safeAdd(3, 4) << "\n";
    cout << "noexcept(safeAdd(0,0)) = " << boolalpha << noexcept(safeAdd(0,0)) << "\n";
}

// ============================================================
// SECTION 7: RAII — Exception Safety via Destructors
// ============================================================
// RAII = Resource Acquisition Is Initialization
// The destructor is GUARANTEED to run even when an exception is thrown.
// This ensures resources (memory, file handles, locks) are never leaked.
// ------------------------------------------------------------ 

class FileGuard {
    string filename_;
public:
    explicit FileGuard(const string& filename) : filename_(filename) {
        cout << "  FileGuard: acquired \"" << filename_ << "\"\n";
    }
    ~FileGuard() {
        // Destructor runs even when exception is thrown in the guarded scope.
        cout << "  FileGuard: released \"" << filename_ << "\" (destructor)\n";
    }
};

void demonstrateRAII() {
    cout << "\n=== RAII — Exception-Safe Resource Management ===" << endl;
    try {
        FileGuard guard("report.txt");        // resource acquired
        cout << "  Processing file...\n";
        throw runtime_error("Disk full!");    // exception thrown mid-processing
        cout << "  This line is never reached.\n";
    }
    catch (const exception& e) {
        // The FileGuard destructor ran BEFORE this catch block
        cout << "  Caught: " << e.what() << "\n";
    }
    // Result: file handle released cleanly regardless of exception
}

// ============================================================
// SECTION 8: EXCEPTION IN CONSTRUCTOR + unique_ptr SAFETY
// ============================================================

class NetworkSocket {
    string address_;
public:
    explicit NetworkSocket(const string& addr) : address_(addr) {
        cout << "  Socket: connecting to " << addr << "\n";
        if (addr.empty())
            throw invalid_argument("Socket address cannot be empty");
        cout << "  Socket: connected!\n";
    }
    ~NetworkSocket() {
        cout << "  Socket: disconnected from " << address_ << "\n";
    }
    void send(const string& msg) { cout << "  Socket: sent \"" << msg << "\"\n"; }
};

void demonstrateUniquePtr() {
    cout << "\n=== unique_ptr + Exception Safety ===" << endl;

    // Good: non-empty address
    try {
        auto sock = make_unique<NetworkSocket>("192.168.1.1:8080");
        sock->send("Hello!");
        // sock destructor called here — socket disconnected cleanly
    }
    catch (const exception& e) {
        cout << "  Error: " << e.what() << "\n";
    }

    // Bad: empty address → constructor throws
    try {
        auto sock = make_unique<NetworkSocket>("");   // throws
        // unique_ptr is never assigned; no memory leak
    }
    catch (const exception& e) {
        cout << "  Error: " << e.what() << "\n";
    }
}

// ============================================================
// MAIN
// ============================================================
int main() {

    // 1. Basic try-catch
    cout << "=== BASIC TRY-CATCH ===" << endl;
    try {
        cout << "10 / 2 = " << safeDivide(10, 2) << "\n";
        cout << "5  / 0 = " << safeDivide(5, 0) << "\n";   // throws
    }
    catch (const invalid_argument& e) {
        cout << "Caught: " << e.what() << "\n";
    }

    // 2. Standard exception hierarchy
    demonstrateStdExceptions();

    // 3. Custom exceptions
    demonstrateCustomExceptions();

    // 4. Multiple catch blocks
    demonstrateMultipleCatch();

    // 5. Nested try + re-throw
    demonstrateRethrow();

    // 6. noexcept
    demonstrateNoexcept();

    // 7. RAII
    demonstrateRAII();

    // 8. unique_ptr exception safety
    demonstrateUniquePtr();

    return 0;
}

// ============================================================
// COMPLEXITY ANALYSIS
//   Throw   : O(1) — stack unwinding proportional to call depth
//   Catch   : O(d) where d = call stack depth at throw point
//   RAII    : O(1) — destructor cost is fixed per object
//
// BEST PRACTICES:
//   ✔ Always catch by const reference: catch(const exception& e)
//   ✔ Order catch blocks most-specific to least-specific
//   ✔ Use noexcept on destructors and move constructors
//   ✔ Prefer RAII (unique_ptr, lock_guard) over manual cleanup
//   ✔ Never throw from a destructor (leads to std::terminate)
//   ✗ Avoid catch(...)  except as a last-resort safety net
//   ✗ Never silently swallow exceptions in an empty catch block
// ============================================================
