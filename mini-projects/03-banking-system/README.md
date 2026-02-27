# 🏦 Banking System Simulation

## Problem Statement
Simulate a banking system with multiple account types, transactions, and exception handling.

## Features
- Multiple account types (Savings, Current, Fixed Deposit)
- Deposit, Withdraw, Transfer with validation
- Interest calculation (different rates per account type)
- Transaction history
- Exception handling for insufficient funds, invalid amounts

## OOPs Principles
| Principle | Application |
|-----------|------------|
| **Polymorphism** | `calculateInterest()` differs per account type |
| **Inheritance** | `SavingsAccount`, `CurrentAccount` extend `Account` |
| **Exception Handling** | Custom `InsufficientFundsException` |
| **Encapsulation** | Balance is private, modified only through validated methods |
