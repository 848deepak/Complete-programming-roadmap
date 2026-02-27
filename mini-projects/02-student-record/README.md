# 🎓 Student Record Management System

## Problem Statement
Console-based system to manage student records with CRUD operations, file persistence, sorting, and search.

## Features
- Add/Update/Delete student records
- Search by name, ID, or grade
- Sort students by name, GPA, or roll number
- Save/Load records from file
- GPA calculation and statistics

## OOPs Principles Used
| Principle | Application |
|-----------|------------|
| **Encapsulation** | Student data is private with validation in setters |
| **Abstraction** | `RecordManager` hides file I/O and sorting details |
| **Composition** | `Student` has a `vector<Course>` (has-a relationship) |

## How to Run
```bash
# C++
g++ -std=c++17 -o student student.cpp && ./student

# Java
javac StudentRecord.java && java StudentRecord
```
