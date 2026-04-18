#include <iostream>
#include <fstream>
using namespace std;

class BankAccount {
    int accNo;
    string name;
    float balance;

public:
    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accNo;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    void showAccount() {
        cout << "\nAccount No: " << accNo;
        cout << "\nName: " << name;
        cout << "\nBalance: " << balance << endl;
    }

    void deposit() {
        float amt;
        cout << "Enter amount to deposit: ";
        cin >> amt;
        balance += amt;
    }

    void withdraw() {
        float amt;
        cout << "Enter amount to withdraw: ";
        cin >> amt;
        if (amt > balance)
            cout << "Insufficient balance!\n";
        else
            balance -= amt;
    }

    int getAccNo() {
        return accNo;
    }
};

// Create account
void createAccount() {
    BankAccount acc;
    ofstream file("bank.dat", ios::binary | ios::app);

    acc.createAccount();
    file.write((char*)&acc, sizeof(acc));

    file.close();
    cout << "Account created successfully!\n";
}

// Display all accounts
void displayAll() {
    BankAccount acc;
    ifstream file("bank.dat", ios::binary);

    while (file.read((char*)&acc, sizeof(acc))) {
        acc.showAccount();
        cout << "-------------------\n";
    }

    file.close();
}

// Deposit / Withdraw
void updateAccount(int accNo, int type) {
    BankAccount acc;
    fstream file("bank.dat", ios::binary | ios::in | ios::out);
    bool found = false;

    while (file.read((char*)&acc, sizeof(acc))) {
        if (acc.getAccNo() == accNo) {
            acc.showAccount();

            if (type == 1)
                acc.deposit();
            else
                acc.withdraw();

            int pos = -1 * sizeof(acc);
            file.seekp(pos, ios::cur);
            file.write((char*)&acc, sizeof(acc));

            cout << "Updated successfully!\n";
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "Account not found!\n";
}

// Search account
void searchAccount(int accNo) {
    BankAccount acc;
    ifstream file("bank.dat", ios::binary);
    bool found = false;

    while (file.read((char*)&acc, sizeof(acc))) {
        if (acc.getAccNo() == accNo) {
            acc.showAccount();
            found = true;
        }
    }

    file.close();

    if (!found)
        cout << "Account not found!\n";
}

int main() {
    int choice, accNo;

    do {
        cout << "\n===== BANK MENU =====\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Display All\n";
        cout << "5. Search Account\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                createAccount();
                break;

            case 2:
                cout << "Enter Account No: ";
                cin >> accNo;
                updateAccount(accNo, 1);
                break;

            case 3:
                cout << "Enter Account No: ";
                cin >> accNo;
                updateAccount(accNo, 2);
                break;

            case 4:
                displayAll();
                break;

            case 5:
                cout << "Enter Account No: ";
                cin >> accNo;
                searchAccount(accNo);
                break;

            case 6:
                cout << "Thank you!\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}