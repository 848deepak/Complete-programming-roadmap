# 📚 Library Management System

## Problem Statement
Build a console-based Library Management System that allows librarians to manage books and members, issue books, return books, and search the catalog.

## Features
- Add/remove books to catalog
- Register/remove members
- Issue & return books with due date tracking
- Search books by title, author, or ISBN
- Display all books and their availability
- Track overdue books

## Folder Structure
```
01-library-management/
├── README.md
├── cpp/
│   └── library.cpp
└── java/
    └── Library.java
```

## OOPs Principles Used

| Principle | How It's Applied |
|-----------|-----------------|
| **Encapsulation** | Book/Member data is private, accessed via getters/setters |
| **Inheritance** | `ReferenceBook` and `RegularBook` extend `Book` base class |
| **Polymorphism** | `displayInfo()` behaves differently for different book types |
| **Abstraction** | `Library` class hides internal data structure from user |

## Design Explanation

```
                    ┌──────────┐
                    │  Library  │  (manages collections)
                    └─────┬────┘
              ┌───────────┼───────────┐
        ┌─────┴─────┐  ┌─┴──────┐  ┌─┴────────┐
        │   Book     │  │ Member │  │ Transaction│
        │ (abstract) │  └────────┘  └───────────┘
        └─────┬──────┘
     ┌────────┼──────────┐
┌────┴─────┐  ┌──────────┴───┐
│RegularBook│  │ReferenceBook │
│(can issue)│  │(library only)│
└──────────┘  └──────────────┘
```
