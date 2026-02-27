// ============================================================
// MODULE | C++ INTERMEDIATE → File Handling
// ============================================================
// DESCRIPTION:
//   Complete guide to C++ file I/O using <fstream>:
//   Text read/write, append, getline, binary files, error
//   checking, and structured CSV parsing.
//
// COMPILE & RUN:
//   g++ -std=c++17 03_file_handling.cpp -o out && ./out
//
// SAMPLE OUTPUT:
//   === WRITE TEXT FILE ===
//   Written to output.txt
//   === READ TEXT FILE ===
//   Line 1: Hello, World!
//   ...
//
// COMPLEXITY:
//   Read/write n bytes: O(n)
//   Sequential line scan: O(L) where L = number of lines
// ============================================================

#include <iostream>
#include <fstream>      // ifstream, ofstream, fstream
#include <sstream>      // stringstream (for CSV parsing)
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

// ============================================================
// SECTION 1: WRITE A TEXT FILE (ofstream)
// ============================================================
// ofstream opens a file for OUTPUT (writing).
// Default behaviour: creates file if not found, OVERWRITES if exists.
// ios::app flag → APPEND to existing content instead of overwriting.
// ------------------------------------------------------------ 

/**
 * Writes multiple lines to a text file.
 *
 * @param filename  Path to file
 * @param lines     Lines to write
 * @throws runtime_error if file cannot be opened
 *
 * Time: O(n)  |  Space: O(1)
 */
void writeTextFile(const string& filename, const vector<string>& lines) {
    ofstream outFile(filename);             // open for writing (creates/overwrites)

    if (!outFile.is_open()) {              // ALWAYS check if file opened successfully
        throw runtime_error("Cannot open file for writing: " + filename);
    }

    for (const auto& line : lines) {
        outFile << line << "\n";           // write each line followed by newline
    }
    outFile.close();                       // explicitly close (also done by destructor)
    cout << "Written " << lines.size() << " lines to \"" << filename << "\"\n";
}

// ============================================================
// SECTION 2: READ A TEXT FILE (ifstream)
// ============================================================

/**
 * Reads all lines from a text file into a vector.
 *
 * @param filename  Path to file
 * @return          Vector of strings, one per line
 * @throws runtime_error if file cannot be opened
 *
 * Time: O(L)  |  Space: O(L) where L = number of lines
 */
vector<string> readTextFile(const string& filename) {
    ifstream inFile(filename);             // open for reading

    if (!inFile) {                         // implicit bool conversion checks open state
        throw runtime_error("Cannot open file for reading: " + filename);
    }

    vector<string> lines;
    string line;

    // getline reads one line at a time (stops at '\n', discards delimiter)
    while (getline(inFile, line)) {
        lines.push_back(line);
    }

    return lines;
}

// ============================================================
// SECTION 3: APPEND TO A TEXT FILE (ios::app)
// ============================================================

/**
 * Appends a single line to an existing (or new) text file.
 *
 * @param filename  Path to file
 * @param newLine   Text to append
 *
 * Time: O(1) amortized  |  Space: O(1)
 */
void appendLine(const string& filename, const string& newLine) {
    ofstream outFile(filename, ios::app);  // ios::app = append mode, keeps existing content

    if (!outFile) {
        throw runtime_error("Cannot open file for appending: " + filename);
    }
    outFile << newLine << "\n";
    cout << "Appended: \"" << newLine << "\" to \"" << filename << "\"\n";
}

// ============================================================
// SECTION 4: fstream — BOTH READ AND WRITE ON SAME OBJECT
// ============================================================
// fstream opens a file for both input and output simultaneously.
// Use seekg / seekp to move read/write positions.
// ------------------------------------------------------------ 

/**
 * Counts the number of words in a text file using fstream.
 *
 * @param filename  Path to file
 * @return          Word count
 *
 * Time: O(W * avg_word_length)  |  Space: O(1)
 */
int countWords(const string& filename) {
    fstream f(filename, ios::in);          // open for reading with fstream

    if (!f) throw runtime_error("Cannot open: " + filename);

    string word;
    int count = 0;
    while (f >> word) count++;            // operator>> splits on whitespace
    return count;
}

// ============================================================
// SECTION 5: CSV PARSING
// ============================================================
// Real-world pattern: parse comma-separated values line by line.
// ------------------------------------------------------------ 

struct Student {
    string name;
    int    age;
    double gpa;
};

/**
 * Writes a CSV file with student records.
 * Format: name,age,gpa
 *
 * Time: O(n)  |  Space: O(1)
 */
void writeCSV(const string& filename, const vector<Student>& students) {
    ofstream f(filename);
    if (!f) throw runtime_error("Cannot write CSV: " + filename);

    f << "name,age,gpa\n";               // header row
    for (const auto& s : students) {
        f << s.name << "," << s.age << "," << s.gpa << "\n";
    }
    cout << "CSV written: " << filename << " (" << students.size() << " records)\n";
}

/**
 * Reads and parses a CSV file into a vector of Student structs.
 * Skips the header row.
 *
 * Time: O(n)  |  Space: O(n)
 */
vector<Student> readCSV(const string& filename) {
    ifstream f(filename);
    if (!f) throw runtime_error("Cannot read CSV: " + filename);

    vector<Student> result;
    string line;
    getline(f, line);                    // skip header row

    while (getline(f, line)) {
        stringstream ss(line);           // wrap line in a stream for tokenising
        string tok;
        Student s;

        getline(ss, tok, ',');  s.name = tok;          // read until comma
        getline(ss, tok, ',');  s.age  = stoi(tok);    // convert token to int
        getline(ss, tok, ',');  s.gpa  = stod(tok);    // convert token to double

        result.push_back(s);
    }
    return result;
}

// ============================================================
// SECTION 6: BINARY FILE I/O
// ============================================================
// Binary mode (ios::binary): writes raw bytes, no text conversions.
// Useful for: custom data formats, images, serialisation.
// write() / read() operate on raw memory (reinterpret_cast required).
// ------------------------------------------------------------ 

struct Record {
    int    id;
    double value;
    char   tag[8];   // fixed-size char array (easier to binary-serialize)
};

/**
 * Writes an array of Record structs to a binary file.
 *
 * Time: O(n)  |  Space: O(1)
 */
void writeBinary(const string& filename, const vector<Record>& records) {
    ofstream f(filename, ios::binary);
    if (!f) throw runtime_error("Cannot open binary file for writing: " + filename);

    int n = (int)records.size();
    f.write(reinterpret_cast<const char*>(&n), sizeof(n));   // write count first

    for (const auto& r : records) {
        f.write(reinterpret_cast<const char*>(&r), sizeof(Record));
    }
    cout << "Binary: wrote " << n << " Record(s) to " << filename << "\n";
}

/**
 * Reads Record structs from a binary file.
 *
 * Time: O(n)  |  Space: O(n)
 */
vector<Record> readBinary(const string& filename) {
    ifstream f(filename, ios::binary);
    if (!f) throw runtime_error("Cannot open binary file for reading: " + filename);

    int n = 0;
    f.read(reinterpret_cast<char*>(&n), sizeof(n));          // read count

    vector<Record> records(n);
    for (auto& r : records) {
        f.read(reinterpret_cast<char*>(&r), sizeof(Record)); // read each struct
    }
    return records;
}

// ============================================================
// SECTION 7: FILE SIZE & ERROR STATE FLAGS
// ============================================================
/**
 * Returns the size of a file in bytes using seekg.
 *
 * Time: O(1)  |  Space: O(1)
 */
long getFileSize(const string& filename) {
    ifstream f(filename, ios::binary | ios::ate);  // ios::ate = start at end
    if (!f) throw runtime_error("Cannot open: " + filename);
    return (long)f.tellg();                        // position = file size
}

// ============================================================
// MAIN
// ============================================================
int main() {
    const string textFile   = "/tmp/demo.txt";
    const string csvFile    = "/tmp/students.csv";
    const string binaryFile = "/tmp/records.bin";

    // --- 1: Write text file ---
    cout << "=== WRITE TEXT FILE ===" << endl;
    writeTextFile(textFile, {
        "Hello, World!",
        "C++ File Handling",
        "Line three with numbers: 42 3.14",
        "The quick brown fox"
    });

    // --- 2: Read text file ---
    cout << "\n=== READ TEXT FILE ===" << endl;
    auto lines = readTextFile(textFile);
    for (int i = 0; i < (int)lines.size(); i++)
        cout << "Line " << i + 1 << ": " << lines[i] << "\n";

    // --- 3: Append ---
    cout << "\n=== APPEND TO FILE ===" << endl;
    appendLine(textFile, "Appended line!");
    cout << "File now has " << readTextFile(textFile).size() << " lines.\n";

    // --- 4: Word count ---
    cout << "\n=== WORD COUNT (fstream) ===" << endl;
    cout << "Words in file: " << countWords(textFile) << "\n";

    // --- 5: File size ---
    cout << "\n=== FILE SIZE ===" << endl;
    cout << "Size of \"" << textFile << "\": " << getFileSize(textFile) << " bytes\n";

    // --- 6: CSV ---
    cout << "\n=== CSV WRITE ===" << endl;
    vector<Student> students = {
        {"Alice", 20, 3.9},
        {"Bob",   22, 3.5},
        {"Carol", 21, 3.7}
    };
    writeCSV(csvFile, students);

    cout << "\n=== CSV READ ===" << endl;
    auto loaded = readCSV(csvFile);
    cout << left;
    cout << "Name         Age   GPA\n";
    cout << "-------------------------\n";
    for (const auto& s : loaded)
        printf("%-12s  %2d   %.1f\n", s.name.c_str(), s.age, s.gpa);

    // --- 7: Binary ---
    cout << "\n=== BINARY FILE ===" << endl;
    vector<Record> recs = {
        {101, 3.14, "alpha"},
        {202, 2.71, "beta"},
        {303, 1.41, "gamma"}
    };
    writeBinary(binaryFile, recs);

    auto recs2 = readBinary(binaryFile);
    cout << "Binary: read " << recs2.size() << " record(s):\n";
    for (const auto& r : recs2)
        printf("  id=%-4d  value=%.2f  tag=%s\n", r.id, r.value, r.tag);

    // --- 8: Error handling ---
    cout << "\n=== ERROR HANDLING ===" << endl;
    try {
        readTextFile("/nonexistent/path/file.txt");
    }
    catch (const runtime_error& e) {
        cout << "Caught: " << e.what() << "\n";
    }

    return 0;
}

// ============================================================
// COMPLEXITY ANALYSIS
//   Text write n lines : O(n)
//   Text read  n lines : O(n)
//   CSV parse  n rows  : O(n)
//   Binary write n recs: O(n)
//   File size query    : O(1)
//
// KEY FLAGS:
//   ios::in     — read mode     (ifstream default)
//   ios::out    — write mode    (ofstream default, truncates)
//   ios::app    — append mode   (never truncates)
//   ios::binary — binary mode   (no newline translation)
//   ios::ate    — seek to end on open
//
// STREAM STATE FLAGS:
//   f.good()    — no errors
//   f.eof()     — end-of-file reached
//   f.fail()    — logical I/O failure
//   f.bad()     — read/write failure (hardware level)
// ============================================================
