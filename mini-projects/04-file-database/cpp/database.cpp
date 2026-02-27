/*
 * Console File Database — C++
 * Concepts: Hashing, File I/O, CRUD, Custom Data Structure
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <functional>
#include <iomanip>
using namespace std;

struct Record {
    string key, value;
};

class HashDatabase {
    static const int BUCKET_COUNT = 16;
    list<Record> buckets[BUCKET_COUNT];
    string filename = "database.dat";

    int hashKey(const string& key) const {
        return hash<string>{}(key) % BUCKET_COUNT;
    }

    list<Record>::iterator findInBucket(int idx, const string& key) {
        for (auto it = buckets[idx].begin(); it != buckets[idx].end(); ++it)
            if (it->key == key) return it;
        return buckets[idx].end();
    }

public:
    void insert(const string& key, const string& value) {
        int idx = hashKey(key);
        auto it = findInBucket(idx, key);
        if (it != buckets[idx].end()) {
            it->value = value; // Update existing
            cout << "✅ Updated: " << key << "\n";
        } else {
            buckets[idx].push_back({key, value});
            cout << "✅ Inserted: " << key << "\n";
        }
    }

    string get(const string& key) {
        int idx = hashKey(key);
        auto it = findInBucket(idx, key);
        if (it == buckets[idx].end()) return "❌ Key not found";
        return it->value;
    }

    bool remove(const string& key) {
        int idx = hashKey(key);
        auto it = findInBucket(idx, key);
        if (it == buckets[idx].end()) return false;
        buckets[idx].erase(it);
        return true;
    }

    void displayAll() {
        cout << "\n📦 Database Contents:\n";
        cout << "+------------------+----------------------------------+\n";
        cout << "| Key              | Value                            |\n";
        cout << "+------------------+----------------------------------+\n";
        int total = 0;
        for (int i = 0; i < BUCKET_COUNT; i++)
            for (auto& r : buckets[i]) {
                cout << "| " << setw(16) << left << r.key << " | "
                     << setw(32) << left << r.value << " |\n";
                total++;
            }
        cout << "+------------------+----------------------------------+\n";
        cout << "Total records: " << total << "\n";
    }

    void displayStats() {
        cout << "\n📊 Hash Table Statistics:\n";
        int total = 0, maxChain = 0, nonEmpty = 0;
        for (int i = 0; i < BUCKET_COUNT; i++) {
            int sz = buckets[i].size();
            total += sz;
            maxChain = max(maxChain, sz);
            if (sz > 0) nonEmpty++;
        }
        cout << "  Buckets: " << BUCKET_COUNT << "\n";
        cout << "  Records: " << total << "\n";
        cout << "  Load Factor: " << fixed << setprecision(2) << (double)total/BUCKET_COUNT << "\n";
        cout << "  Max Chain Length: " << maxChain << "\n";
        cout << "  Non-empty Buckets: " << nonEmpty << "/" << BUCKET_COUNT << "\n";
    }

    void saveToFile() {
        ofstream f(filename);
        for (int i = 0; i < BUCKET_COUNT; i++)
            for (auto& r : buckets[i])
                f << r.key << "|" << r.value << "\n";
        cout << "✅ Saved to " << filename << "\n";
    }

    void loadFromFile() {
        ifstream f(filename);
        if (!f) { cout << "No saved data found.\n"; return; }
        string line;
        int count = 0;
        while (getline(f, line)) {
            size_t sep = line.find('|');
            if (sep != string::npos) {
                insert(line.substr(0, sep), line.substr(sep+1));
                count++;
            }
        }
        cout << "✅ Loaded " << count << " records.\n";
    }
};

int main() {
    HashDatabase db;
    db.insert("name", "Alice Johnson");
    db.insert("email", "alice@example.com");
    db.insert("age", "28");
    db.insert("city", "San Francisco");
    db.insert("role", "Software Engineer");

    int choice;
    do {
        cout << "\n===== File Database =====\n"
             << "1. Insert  2. Get  3. Delete  4. Display All  5. Stats  6. Save  7. Load  0. Exit\n"
             << "Choice: ";
        cin >> choice; cin.ignore();
        switch (choice) {
            case 1: { string k, v; cout << "Key: "; getline(cin, k);
                     cout << "Value: "; getline(cin, v); db.insert(k, v); break; }
            case 2: { string k; cout << "Key: "; getline(cin, k);
                     cout << "→ " << db.get(k) << "\n"; break; }
            case 3: { string k; cout << "Key: "; getline(cin, k);
                     cout << (db.remove(k) ? "✅ Deleted" : "❌ Not found") << "\n"; break; }
            case 4: db.displayAll(); break;
            case 5: db.displayStats(); break;
            case 6: db.saveToFile(); break;
            case 7: db.loadFromFile(); break;
        }
    } while (choice != 0);
    return 0;
}
