/*
 * Banking System — C++ Implementation
 * Concepts: Polymorphism, Inheritance, Exception Handling, Encapsulation
 */
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <unordered_map>
using namespace std;

// Custom Exception
class InsufficientFundsException : public runtime_error {
public:
    InsufficientFundsException(double requested, double available)
        : runtime_error("Insufficient funds: requested $" + to_string(requested)
                        + ", available $" + to_string(available)) {}
};

// Transaction record
struct Transaction {
    string type, description;
    double amount;
    void display() const {
        cout << "  " << setw(10) << left << type << " $" << fixed << setprecision(2) << amount
             << "  " << description << "\n";
    }
};

// ===================== Account Hierarchy =====================

class Account {
protected:
    string accountNo, ownerName;
    double balance;
    vector<Transaction> history;

public:
    Account(string accNo, string owner, double balance)
        : accountNo(accNo), ownerName(owner), balance(balance) {}
    virtual ~Account() = default;

    string getAccountNo() const { return accountNo; }
    string getOwner() const     { return ownerName; }
    double getBalance() const   { return balance; }

    void deposit(double amount) {
        if (amount <= 0) throw invalid_argument("Deposit amount must be positive.");
        balance += amount;
        history.push_back({"DEPOSIT", "Cash deposit", amount});
        cout << "✅ Deposited $" << fixed << setprecision(2) << amount << "\n";
    }

    virtual void withdraw(double amount) {
        if (amount <= 0) throw invalid_argument("Withdrawal amount must be positive.");
        if (amount > balance) throw InsufficientFundsException(amount, balance);
        balance -= amount;
        history.push_back({"WITHDRAW", "Cash withdrawal", amount});
        cout << "✅ Withdrew $" << fixed << setprecision(2) << amount << "\n";
    }

    // Polymorphism — each account type has different interest
    virtual double calculateInterest() const = 0;
    virtual string getType() const = 0;

    void displayInfo() const {
        cout << "[" << getType() << "] " << accountNo << " — " << ownerName
             << " — Balance: $" << fixed << setprecision(2) << balance << "\n";
    }

    void showHistory() const {
        cout << "\n📜 Transaction History for " << accountNo << ":\n";
        for (auto& t : history) t.display();
    }
};

class SavingsAccount : public Account {
    double interestRate = 0.04; // 4%
public:
    using Account::Account;
    string getType() const override { return "Savings"; }
    double calculateInterest() const override { return balance * interestRate; }
    void withdraw(double amount) override {
        if (balance - amount < 500) {
            cout << "⚠️ Minimum balance $500 required in Savings account.\n";
            throw InsufficientFundsException(amount, balance - 500);
        }
        Account::withdraw(amount);
    }
};

class CurrentAccount : public Account {
    double overdraftLimit = 1000;
public:
    using Account::Account;
    string getType() const override { return "Current"; }
    double calculateInterest() const override { return 0; } // No interest
    void withdraw(double amount) override {
        if (amount > balance + overdraftLimit)
            throw InsufficientFundsException(amount, balance + overdraftLimit);
        balance -= amount;
        history.push_back({"WITHDRAW", "Cash withdrawal", amount});
        if (balance < 0) cout << "⚠️ Overdraft used. Balance: $" << balance << "\n";
        else cout << "✅ Withdrew $" << amount << "\n";
    }
};

class FixedDeposit : public Account {
    int termMonths;
    double interestRate = 0.07; // 7%
public:
    FixedDeposit(string acc, string owner, double bal, int months)
        : Account(acc, owner, bal), termMonths(months) {}
    string getType() const override { return "FD"; }
    double calculateInterest() const override { return balance * interestRate * termMonths / 12; }
    void withdraw(double amount) override {
        cout << "⚠️ Penalty of 1% applied for early FD withdrawal.\n";
        double penalty = amount * 0.01;
        Account::withdraw(amount + penalty);
    }
};

// ===================== Bank =====================

class Bank {
    unordered_map<string, Account*> accounts;
public:
    ~Bank() { for (auto& [k,v] : accounts) delete v; }

    void addAccount(Account* acc) {
        accounts[acc->getAccountNo()] = acc;
        cout << "✅ Account created: " << acc->getAccountNo() << "\n";
    }

    void transfer(const string& from, const string& to, double amount) {
        if (!accounts.count(from) || !accounts.count(to)) {
            cout << "❌ Invalid account number.\n"; return;
        }
        try {
            accounts[from]->withdraw(amount);
            accounts[to]->deposit(amount);
            cout << "✅ Transferred $" << amount << " from " << from << " to " << to << "\n";
        } catch (exception& e) {
            cout << "❌ Transfer failed: " << e.what() << "\n";
        }
    }

    void displayAll() {
        cout << "\n🏦 All Accounts:\n";
        for (auto& [id, acc] : accounts) {
            acc->displayInfo();
            cout << "   Annual Interest: $" << fixed << setprecision(2)
                 << acc->calculateInterest() << "\n";
        }
    }

    Account* getAccount(const string& accNo) {
        return accounts.count(accNo) ? accounts[accNo] : nullptr;
    }
};

// ===================== Main =====================

int main() {
    Bank bank;
    bank.addAccount(new SavingsAccount("SAV001", "Alice", 5000));
    bank.addAccount(new CurrentAccount("CUR001", "Bob", 3000));
    bank.addAccount(new FixedDeposit("FD001", "Charlie", 10000, 12));

    bank.displayAll();

    // Demo transactions
    cout << "\n--- Demo Transactions ---\n";
    try {
        Account* alice = bank.getAccount("SAV001");
        alice->deposit(1000);
        alice->withdraw(500);
        alice->showHistory();

        bank.transfer("SAV001", "CUR001", 2000);

        // This will throw
        alice->withdraw(100000);
    } catch (exception& e) {
        cout << "❌ Error: " << e.what() << "\n";
    }

    bank.displayAll();
    return 0;
}
