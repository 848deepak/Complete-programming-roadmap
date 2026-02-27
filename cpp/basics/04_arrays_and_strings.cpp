// ============================================================
// C++ | Basics → Arrays & Strings
// ============================================================
// DESCRIPTION:
//   - C-style arrays vs std::array vs std::vector
//   - Common array operations
//   - C-style strings vs std::string
//   - String methods and manipulation
//   - String conversion, searching, splitting
//
// COMPILE & RUN:
//   g++ -std=c++17 04_arrays_and_strings.cpp -o out && ./out
// ============================================================

#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <sstream>   // stringstream — for splitting and conversion
#include <algorithm> // sort, reverse, find
#include <cctype>    // tolower, toupper, isdigit, isalpha
using namespace std;

// ============================================================
// SECTION 1: C-STYLE ARRAYS
// ============================================================

void demoRawArrays() {
    cout << "=== C-STYLE ARRAYS ===" << "\n";

    // Fixed-size on stack — size must be constant at compile time
    int arr[5] = {10, 20, 30, 40, 50};

    // Traverse
    cout << "  Elements: ";
    for (int i = 0; i < 5; i++) cout << arr[i] << " ";
    cout << "\n";

    // Range-based for loop (C++11+)
    cout << "  Range-for: ";
    for (int x : arr) cout << x << " ";
    cout << "\n";

    // 2D array
    int matrix[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    cout << "  2D matrix:\n";
    for (auto& row : matrix) {
        cout << "    ";
        for (int v : row) cout << v << " ";
        cout << "\n";
    }
}

// ============================================================
// SECTION 2: STD::ARRAY (fixed-size, bounds-safe)
// ============================================================

void demoStdArray() {
    cout << "\n=== STD::ARRAY ===" << "\n";

    array<int, 5> arr = {5, 3, 1, 4, 2};
    cout << "  Before sort: ";
    for (int x : arr) cout << x << " ";
    cout << "\n";

    sort(arr.begin(), arr.end());
    cout << "  After sort:  ";
    for (int x : arr) cout << x << " ";
    cout << "\n";

    cout << "  size=" << arr.size()
         << "  front=" << arr.front()
         << "  back=" << arr.back() << "\n";
}

// ============================================================
// SECTION 3: STD::VECTOR (dynamic array — preferred in C++)
// ============================================================

void demoVector() {
    cout << "\n=== STD::VECTOR ===" << "\n";

    vector<int> v = {1, 2, 3};
    v.push_back(4);
    v.push_back(5);

    cout << "  After push_back(4,5): ";
    for (int x : v) cout << x << " ";
    cout << "  size=" << v.size() << " capacity=" << v.capacity() << "\n";

    v.pop_back();
    cout << "  After pop_back: size=" << v.size() << "\n";

    // insert at position 1
    v.insert(v.begin() + 1, 99);
    cout << "  After insert(99 at idx 1): ";
    for (int x : v) cout << x << " ";
    cout << "\n";

    // erase element at index 2
    v.erase(v.begin() + 2);
    cout << "  After erase(idx 2): ";
    for (int x : v) cout << x << " ";
    cout << "\n";

    cout << "  v[0]=" << v[0] << "  v.at(1)=" << v.at(1) << "\n";
    cout << "  empty? " << boolalpha << v.empty() << "\n";

    // 2D vector
    vector<vector<int>> mat(3, vector<int>(3, 0));
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            mat[i][j] = i * 3 + j + 1;
    cout << "  2D vector:\n";
    for (auto& row : mat) {
        cout << "    ";
        for (int v : row) cout << v << " ";
        cout << "\n";
    }
}

// ============================================================
// SECTION 4: C-STYLE STRINGS vs std::string
// ============================================================

void demoStrings() {
    cout << "\n=== STRINGS ===" << "\n";

    // C-style string (null-terminated char array) — AVOID in modern C++
    const char* cStr = "Hello, C!";
    cout << "  C-style: " << cStr << "  len=" << strlen(cStr) << "\n";

    // std::string — preferred
    string s = "Hello, World!";
    cout << "  std::string: " << s << "\n";
    cout << "  length: " << s.length() << "  size: " << s.size() << "\n";

    // Access characters
    cout << "  s[0]=" << s[0] << "  s.at(7)=" << s.at(7) << "\n";
    cout << "  front=" << s.front() << "  back=" << s.back() << "\n";

    // Concatenation
    string greeting = "Hello";
    greeting += ", Alice";          // += operator
    greeting.append("!");
    cout << "  Concatenated: " << greeting << "\n";

    // Substring
    cout << "  substr(0,5): " << s.substr(0, 5) << "\n";    // "Hello"
    cout << "  substr(7):   " << s.substr(7) << "\n";        // "World!"

    // Find
    size_t pos = s.find("World");
    cout << "  find('World'): pos=" << pos << "\n";
    cout << "  find('xyz'):   pos=" << (s.find("xyz") == string::npos ? -1 : (int)s.find("xyz")) << "\n";

    // Replace
    string r = s;
    r.replace(7, 5, "C++");
    cout << "  After replace: " << r << "\n";

    // Compare
    string a = "apple", b = "banana";
    cout << "  a < b: " << (a < b) << "\n";          // lexicographic comparison
    cout << "  a == a: " << (a == a) << "\n";
    cout << "  compare: " << a.compare(b) << "\n";   // <0 means a < b

    // Reverse
    string rev = s;
    reverse(rev.begin(), rev.end());
    cout << "  Reversed: " << rev << "\n";

    // Case conversion
    string upper = "hello";
    for (char& c : upper) c = toupper(c);
    cout << "  To upper: " << upper << "\n";

    string lower = "WORLD";
    for (char& c : lower) c = tolower(c);
    cout << "  To lower: " << lower << "\n";
}

// ============================================================
// SECTION 5: STRING — TYPE CONVERSION
// ============================================================

void demoConversions() {
    cout << "\n=== STRING CONVERSIONS ===" << "\n";

    // int/double → string
    int    num   = 42;
    double pi    = 3.14159;
    string sNum  = to_string(num);
    string sPi   = to_string(pi);
    cout << "  to_string(42):       " << sNum << "\n";
    cout << "  to_string(3.14159):  " << sPi  << "\n";

    // string → int/double
    string s1 = "123", s2 = "3.14";
    cout << "  stoi(\"123\"):   " << stoi(s1)   << "\n";
    cout << "  stod(\"3.14\"):  " << stod(s2)   << "\n";
    cout << "  stol(\"1234\"): " << stol("1234") << "\n";

    // stringstream — versatile parsing
    string csv = "Alice,30,Engineer";
    stringstream ss(csv);
    string token;
    cout << "  CSV parse: ";
    while (getline(ss, token, ',')) cout << "[" << token << "] ";
    cout << "\n";
}

// ============================================================
// SECTION 6: COMMON STRING ALGORITHMS
// ============================================================

bool isPalindrome(const string& s) {
    int l = 0, r = (int)s.size() - 1;
    while (l < r) {
        if (s[l] != s[r]) return false;
        l++; r--;
    }
    return true;
}

int countVowels(const string& s) {
    int cnt = 0;
    for (char c : s) {
        char lower = tolower(c);
        if (lower=='a'||lower=='e'||lower=='i'||lower=='o'||lower=='u') cnt++;
    }
    return cnt;
}

string reverseWords(const string& s) {
    vector<string> words;
    stringstream ss(s);
    string word;
    while (ss >> word) words.push_back(word);
    reverse(words.begin(), words.end());
    string result;
    for (int i = 0; i < (int)words.size(); i++) {
        result += words[i];
        if (i + 1 < (int)words.size()) result += " ";
    }
    return result;
}

void demoAlgorithms() {
    cout << "\n=== STRING ALGORITHMS ===" << "\n";
    cout << "  isPalindrome(\"racecar\"): " << boolalpha << isPalindrome("racecar") << "\n";
    cout << "  isPalindrome(\"hello\"):   " << isPalindrome("hello") << "\n";
    cout << "  countVowels(\"Hello\"): "    << countVowels("Hello") << "\n";
    cout << "  reverseWords(\"the sky is blue\"): " << reverseWords("the sky is blue") << "\n";

    // Anagram check (sort both strings)
    string a = "listen", b = "silent";
    string sa = a, sb = b;
    sort(sa.begin(), sa.end()); sort(sb.begin(), sb.end());
    cout << "  anagram(\"listen\",\"silent\"): " << (sa == sb) << "\n";
}

// ============================================================
// MAIN
// ============================================================
int main() {
    demoRawArrays();
    demoStdArray();
    demoVector();
    demoStrings();
    demoConversions();
    demoAlgorithms();
    return 0;
}
