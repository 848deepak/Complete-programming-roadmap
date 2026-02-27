/*
 * Library Management System — C++ Implementation
 * 
 * OOPs Concepts: Inheritance, Polymorphism, Encapsulation, Abstraction
 * DSA Concepts:  HashMap (unordered_map), Linear Search, Sorting
 */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <ctime>
using namespace std;

// ===================== Book Hierarchy =====================

class Book {
protected:
    string isbn, title, author;
    bool available;
public:
    Book(string isbn, string title, string author)
        : isbn(isbn), title(title), author(author), available(true) {}
    virtual ~Book() = default;

    // Getters (Encapsulation)
    string getISBN() const   { return isbn; }
    string getTitle() const  { return title; }
    string getAuthor() const { return author; }
    bool isAvailable() const { return available; }
    void setAvailable(bool v){ available = v; }

    // Polymorphism — overridden by subclasses
    virtual string getType() const = 0;
    virtual bool canBeIssued() const = 0;

    virtual void displayInfo() const {
        cout << "[" << getType() << "] " << title 
             << " by " << author << " (ISBN: " << isbn << ") — "
             << (available ? "Available" : "Issued") << "\n";
    }
};

class RegularBook : public Book {
public:
    using Book::Book;
    string getType() const override { return "Regular"; }
    bool canBeIssued() const override { return available; }
};

class ReferenceBook : public Book {
public:
    using Book::Book;
    string getType() const override { return "Reference"; }
    bool canBeIssued() const override { return false; } // Can't be issued!
    void displayInfo() const override {
        Book::displayInfo();
        if (!available) cout << "  ⚠️ Reference books cannot be issued\n";
    }
};

// ===================== Member =====================

class Member {
    string id, name;
    vector<string> issuedBooks; // ISBNs
public:
    Member(string id, string name) : id(id), name(name) {}

    string getId() const   { return id; }
    string getName() const { return name; }
    const vector<string>& getIssuedBooks() const { return issuedBooks; }

    void issueBook(const string& isbn) { issuedBooks.push_back(isbn); }
    void returnBook(const string& isbn) {
        issuedBooks.erase(
            remove(issuedBooks.begin(), issuedBooks.end(), isbn),
            issuedBooks.end()
        );
    }

    void displayInfo() const {
        cout << "Member: " << name << " (ID: " << id 
             << ") — " << issuedBooks.size() << " books issued\n";
    }
};

// ===================== Library (Abstraction) =====================

class Library {
    unordered_map<string, Book*> books;    // ISBN → Book
    unordered_map<string, Member*> members; // ID → Member

public:
    ~Library() {
        for (auto& [k, v] : books) delete v;
        for (auto& [k, v] : members) delete v;
    }

    // Book Management
    void addBook(Book* book) {
        if (books.count(book->getISBN())) {
            cout << "❌ Book with ISBN " << book->getISBN() << " already exists.\n";
            delete book;
            return;
        }
        books[book->getISBN()] = book;
        cout << "✅ Added: " << book->getTitle() << "\n";
    }

    void removeBook(const string& isbn) {
        if (!books.count(isbn)) { cout << "❌ Book not found.\n"; return; }
        cout << "✅ Removed: " << books[isbn]->getTitle() << "\n";
        delete books[isbn];
        books.erase(isbn);
    }

    // Member Management
    void registerMember(const string& id, const string& name) {
        if (members.count(id)) { cout << "❌ Member ID already exists.\n"; return; }
        members[id] = new Member(id, name);
        cout << "✅ Registered: " << name << "\n";
    }

    // Issue & Return
    void issueBook(const string& memberId, const string& isbn) {
        if (!members.count(memberId)) { cout << "❌ Member not found.\n"; return; }
        if (!books.count(isbn))       { cout << "❌ Book not found.\n"; return; }
        
        Book* book = books[isbn];
        if (!book->canBeIssued()) {
            cout << "❌ This book cannot be issued.\n";
            return;
        }
        book->setAvailable(false);
        members[memberId]->issueBook(isbn);
        cout << "✅ Issued '" << book->getTitle() << "' to " 
             << members[memberId]->getName() << "\n";
    }

    void returnBook(const string& memberId, const string& isbn) {
        if (!members.count(memberId) || !books.count(isbn)) {
            cout << "❌ Invalid member or book.\n"; return;
        }
        books[isbn]->setAvailable(true);
        members[memberId]->returnBook(isbn);
        cout << "✅ Returned: " << books[isbn]->getTitle() << "\n";
    }

    // Search (Linear search — could optimize with trie for autocomplete)
    void searchByTitle(const string& query) const {
        cout << "\n🔍 Search results for '" << query << "':\n";
        bool found = false;
        for (auto& [isbn, book] : books) {
            if (book->getTitle().find(query) != string::npos) {
                book->displayInfo();
                found = true;
            }
        }
        if (!found) cout << "  No results found.\n";
    }

    // Display all
    void displayAllBooks() const {
        cout << "\n📚 Library Catalog (" << books.size() << " books):\n";
        for (auto& [isbn, book] : books) book->displayInfo();
    }

    void displayAllMembers() const {
        cout << "\n👥 Members (" << members.size() << "):\n";
        for (auto& [id, member] : members) member->displayInfo();
    }
};

// ===================== Main Menu =====================

int main() {
    Library lib;
    
    // Seed with sample data
    lib.addBook(new RegularBook("978-0-13-468599-1", "The C++ Programming Language", "Bjarne Stroustrup"));
    lib.addBook(new RegularBook("978-0-596-00712-6", "Head First Design Patterns", "Freeman & Robson"));
    lib.addBook(new ReferenceBook("978-0-201-63361-0", "Design Patterns (GoF)", "Gang of Four"));
    lib.registerMember("M001", "Alice");
    lib.registerMember("M002", "Bob");
    
    int choice;
    do {
        cout << "\n===== Library Management System =====\n"
             << "1. Display All Books\n"
             << "2. Search by Title\n"
             << "3. Issue Book\n"
             << "4. Return Book\n"
             << "5. Add Book\n"
             << "6. Display Members\n"
             << "0. Exit\n"
             << "Choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            lib.displayAllBooks();
        } else if (choice == 2) {
            string q; cout << "Enter search query: "; getline(cin, q);
            lib.searchByTitle(q);
        } else if (choice == 3) {
            string mid, isbn;
            cout << "Member ID: "; getline(cin, mid);
            cout << "Book ISBN: "; getline(cin, isbn);
            lib.issueBook(mid, isbn);
        } else if (choice == 4) {
            string mid, isbn;
            cout << "Member ID: "; getline(cin, mid);
            cout << "Book ISBN: "; getline(cin, isbn);
            lib.returnBook(mid, isbn);
        } else if (choice == 5) {
            string isbn, title, author;
            cout << "ISBN: "; getline(cin, isbn);
            cout << "Title: "; getline(cin, title);
            cout << "Author: "; getline(cin, author);
            lib.addBook(new RegularBook(isbn, title, author));
        } else if (choice == 6) {
            lib.displayAllMembers();
        }
    } while (choice != 0);
    
    cout << "Goodbye!\n";
    return 0;
}
