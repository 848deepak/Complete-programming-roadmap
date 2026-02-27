/*
 * Library Management System — Java Implementation
 * 
 * OOPs: Inheritance, Polymorphism, Encapsulation, Abstraction
 * DSA:  HashMap, ArrayList, Stream API for search
 */

import java.util.*;

// ===================== Book Hierarchy =====================

abstract class Book {
    private String isbn, title, author;
    private boolean available = true;

    public Book(String isbn, String title, String author) {
        this.isbn = isbn;
        this.title = title;
        this.author = author;
    }

    // Getters (Encapsulation)
    public String getISBN() {
        return isbn;
    }

    public String getTitle() {
        return title;
    }

    public String getAuthor() {
        return author;
    }

    public boolean isAvailable() {
        return available;
    }

    public void setAvailable(boolean v) {
        available = v;
    }

    // Abstract methods (Abstraction + Polymorphism)
    public abstract String getType();

    public abstract boolean canBeIssued();

    public void displayInfo() {
        System.out.printf("[%s] %s by %s (ISBN: %s) — %s%n",
                getType(), title, author, isbn, available ? "Available" : "Issued");
    }
}

class RegularBook extends Book {
    public RegularBook(String isbn, String title, String author) {
        super(isbn, title, author);
    }

    public String getType() {
        return "Regular";
    }

    public boolean canBeIssued() {
        return isAvailable();
    }
}

class ReferenceBook extends Book {
    public ReferenceBook(String isbn, String title, String author) {
        super(isbn, title, author);
    }

    public String getType() {
        return "Reference";
    }

    public boolean canBeIssued() {
        return false;
    }

    @Override
    public void displayInfo() {
        super.displayInfo();
        System.out.println("  ⚠️ Reference books cannot be issued");
    }
}

// ===================== Member =====================

class Member {
    private String id, name;
    private List<String> issuedBooks = new ArrayList<>();

    public Member(String id, String name) {
        this.id = id;
        this.name = name;
    }

    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public List<String> getIssuedBooks() {
        return issuedBooks;
    }

    public void issueBook(String isbn) {
        issuedBooks.add(isbn);
    }

    public void returnBook(String isbn) {
        issuedBooks.remove(isbn);
    }

    public void displayInfo() {
        System.out.printf("Member: %s (ID: %s) — %d books issued%n", name, id, issuedBooks.size());
    }
}

// ===================== Library =====================

class LibrarySystem {
    private Map<String, Book> books = new HashMap<>();
    private Map<String, Member> members = new HashMap<>();

    public void addBook(Book book) {
        if (books.containsKey(book.getISBN())) {
            System.out.println("❌ Book already exists.");
            return;
        }
        books.put(book.getISBN(), book);
        System.out.println("✅ Added: " + book.getTitle());
    }

    public void registerMember(String id, String name) {
        if (members.containsKey(id)) {
            System.out.println("❌ ID exists.");
            return;
        }
        members.put(id, new Member(id, name));
        System.out.println("✅ Registered: " + name);
    }

    public void issueBook(String memberId, String isbn) {
        Member m = members.get(memberId);
        Book b = books.get(isbn);
        if (m == null) {
            System.out.println("❌ Member not found.");
            return;
        }
        if (b == null) {
            System.out.println("❌ Book not found.");
            return;
        }
        if (!b.canBeIssued()) {
            System.out.println("❌ Cannot issue.");
            return;
        }
        b.setAvailable(false);
        m.issueBook(isbn);
        System.out.println("✅ Issued '" + b.getTitle() + "' to " + m.getName());
    }

    public void returnBook(String memberId, String isbn) {
        Member m = members.get(memberId);
        Book b = books.get(isbn);
        if (m == null || b == null) {
            System.out.println("❌ Invalid.");
            return;
        }
        b.setAvailable(true);
        m.returnBook(isbn);
        System.out.println("✅ Returned: " + b.getTitle());
    }

    public void searchByTitle(String query) {
        System.out.println("\n🔍 Results for '" + query + "':");
        books.values().stream()
                .filter(b -> b.getTitle().toLowerCase().contains(query.toLowerCase()))
                .forEach(Book::displayInfo);
    }

    public void displayAll() {
        books.values().forEach(Book::displayInfo);
    }

    public void displayMembers() {
        members.values().forEach(Member::displayInfo);
    }
}

// ===================== Main =====================

public class Library {
    public static void main(String[] args) {
        LibrarySystem lib = new LibrarySystem();
        lib.addBook(new RegularBook("978-0-13-468599-1", "The C++ Programming Language", "Stroustrup"));
        lib.addBook(new RegularBook("978-0-596-00712-6", "Head First Design Patterns", "Freeman"));
        lib.addBook(new ReferenceBook("978-0-201-63361-0", "Design Patterns (GoF)", "Gang of Four"));
        lib.registerMember("M001", "Alice");
        lib.registerMember("M002", "Bob");

        Scanner sc = new Scanner(System.in);
        int choice;
        do {
            System.out.println("\n===== Library Management =====");
            System.out.println("1. Display Books  2. Search  3. Issue  4. Return  5. Members  0. Exit");
            System.out.print("Choice: ");
            choice = sc.nextInt();
            sc.nextLine();
            switch (choice) {
                case 1 -> lib.displayAll();
                case 2 -> {
                    System.out.print("Query: ");
                    lib.searchByTitle(sc.nextLine());
                }
                case 3 -> {
                    System.out.print("Member ID: ");
                    String m = sc.nextLine();
                    System.out.print("ISBN: ");
                    lib.issueBook(m, sc.nextLine());
                }
                case 4 -> {
                    System.out.print("Member ID: ");
                    String m = sc.nextLine();
                    System.out.print("ISBN: ");
                    lib.returnBook(m, sc.nextLine());
                }
                case 5 -> lib.displayMembers();
            }
        } while (choice != 0);
        System.out.println("Goodbye!");
    }
}
