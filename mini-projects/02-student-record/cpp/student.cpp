/*
 * Student Record Management System — C++
 * Concepts: Encapsulation, File I/O, Sorting, Searching
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

class Student {
    int rollNo;
    string name;
    double gpa;
public:
    Student() : rollNo(0), gpa(0) {}
    Student(int roll, string name, double gpa) : rollNo(roll), name(name), gpa(gpa) {}

    int getRoll() const    { return rollNo; }
    string getName() const { return name; }
    double getGPA() const  { return gpa; }
    void setGPA(double g)  { if (g >= 0 && g <= 4.0) gpa = g; }
    void setName(string n) { name = n; }

    void display() const {
        cout << "| " << setw(6) << rollNo << " | " << setw(20) << left << name 
             << " | " << fixed << setprecision(2) << setw(5) << gpa << " |\n";
    }

    // File I/O
    void saveToFile(ofstream& f) const { f << rollNo << "," << name << "," << gpa << "\n"; }
    static Student loadFromFile(const string& line) {
        int roll; string name; double gpa;
        size_t p1 = line.find(','), p2 = line.rfind(',');
        roll = stoi(line.substr(0, p1));
        name = line.substr(p1+1, p2-p1-1);
        gpa = stod(line.substr(p2+1));
        return Student(roll, name, gpa);
    }
};

class RecordManager {
    vector<Student> records;
    string filename = "students.csv";

    int findByRoll(int roll) {
        for (int i = 0; i < (int)records.size(); i++)
            if (records[i].getRoll() == roll) return i;
        return -1;
    }

public:
    void addStudent(int roll, const string& name, double gpa) {
        if (findByRoll(roll) != -1) { cout << "❌ Roll number exists.\n"; return; }
        records.emplace_back(roll, name, gpa);
        cout << "✅ Added: " << name << "\n";
    }

    void removeStudent(int roll) {
        int idx = findByRoll(roll);
        if (idx == -1) { cout << "❌ Not found.\n"; return; }
        cout << "✅ Removed: " << records[idx].getName() << "\n";
        records.erase(records.begin() + idx);
    }

    void updateGPA(int roll, double newGPA) {
        int idx = findByRoll(roll);
        if (idx == -1) { cout << "❌ Not found.\n"; return; }
        records[idx].setGPA(newGPA);
        cout << "✅ Updated GPA for " << records[idx].getName() << "\n";
    }

    void searchByName(const string& query) {
        cout << "\n🔍 Results:\n";
        for (auto& s : records)
            if (s.getName().find(query) != string::npos) s.display();
    }

    void sortByGPA() {
        sort(records.begin(), records.end(), [](auto& a, auto& b){ return a.getGPA() > b.getGPA(); });
        cout << "✅ Sorted by GPA (descending).\n";
    }

    void sortByName() {
        sort(records.begin(), records.end(), [](auto& a, auto& b){ return a.getName() < b.getName(); });
        cout << "✅ Sorted by name.\n";
    }

    void displayAll() {
        cout << "\n📋 Student Records (" << records.size() << " students):\n";
        cout << "+--------+----------------------+-------+\n";
        cout << "|  Roll  | Name                 |  GPA  |\n";
        cout << "+--------+----------------------+-------+\n";
        for (auto& s : records) s.display();
        cout << "+--------+----------------------+-------+\n";
        // Statistics
        if (!records.empty()) {
            double avg = 0; for (auto& s : records) avg += s.getGPA();
            avg /= records.size();
            cout << "Average GPA: " << fixed << setprecision(2) << avg << "\n";
        }
    }

    void saveToFile() {
        ofstream f(filename);
        for (auto& s : records) s.saveToFile(f);
        cout << "✅ Saved to " << filename << "\n";
    }

    void loadFromFile() {
        ifstream f(filename);
        if (!f) { cout << "No saved file found.\n"; return; }
        records.clear();
        string line;
        while (getline(f, line)) records.push_back(Student::loadFromFile(line));
        cout << "✅ Loaded " << records.size() << " records.\n";
    }
};

int main() {
    RecordManager mgr;
    mgr.addStudent(101, "Alice Johnson", 3.8);
    mgr.addStudent(102, "Bob Smith", 3.5);
    mgr.addStudent(103, "Charlie Brown", 3.9);
    mgr.addStudent(104, "Diana Prince", 3.7);

    int choice;
    do {
        cout << "\n===== Student Records =====\n"
             << "1. Display  2. Add  3. Remove  4. Search  5. Sort by GPA  6. Save  7. Load  0. Exit\n"
             << "Choice: ";
        cin >> choice; cin.ignore();
        switch (choice) {
            case 1: mgr.displayAll(); break;
            case 2: { int r; string n; double g;
                cout << "Roll: "; cin >> r; cin.ignore();
                cout << "Name: "; getline(cin, n);
                cout << "GPA: "; cin >> g;
                mgr.addStudent(r, n, g); break; }
            case 3: { int r; cout << "Roll: "; cin >> r; mgr.removeStudent(r); break; }
            case 4: { string q; cout << "Name: "; getline(cin, q); mgr.searchByName(q); break; }
            case 5: mgr.sortByGPA(); mgr.displayAll(); break;
            case 6: mgr.saveToFile(); break;
            case 7: mgr.loadFromFile(); break;
        }
    } while (choice != 0);
    return 0;
}
