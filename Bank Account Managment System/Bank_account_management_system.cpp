#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <windows.h>

using namespace std;

// Define the Account class
class Account {
private:
    string AccountNo, Password;
    int Balance;

public:
    Account() : AccountNo(""), Password(""), Balance(0) {}

    // Setters
    void setAccountNo(string id) { AccountNo = id; }
    void setPassword(string password) { Password = password; }
    void setBalance(int balance) { Balance = balance; }

    // Getters
   string getAccountNo() const { return AccountNo; }  // Must be const
    string getPassword() const { return Password; }    // Must be const
    int getBalance() const { return Balance; }
};

// Function to save account details to a file
void saveAccountToFile(const Account &account) {
    ofstream outFile("accounts.txt", ios::app); // Open file in append mode
    if (outFile.is_open()) {
        // Write account details to the file
        outFile << account.getAccountNo() << " " 
                << account.getPassword() << " " 
                << account.getBalance() << endl;

        cout << "Account details saved successfully." << endl; // Confirmation message
        outFile.close();
    } else {
        cout << "Error: Unable to open file for saving account." << endl;
    }
}


// Function to load accounts from file into a map
unordered_map<string, Account> loadAccountsFromFile() {
    unordered_map<string, Account> accounts;
    ifstream inFile("accounts.txt");
    if (inFile.is_open()) {
        string accountNo, password;
        int balance;
        while (inFile >> accountNo >> password >> balance) {
            Account account;
            account.setAccountNo(accountNo);
            account.setPassword(password);
            account.setBalance(balance);
            accounts[accountNo] = account;
        }
        inFile.close();
    }
    return accounts;
}

// Function to save all accounts back to the file
void saveAllAccountsToFile(const unordered_map<string, Account> &accounts) {
    ofstream outFile("accounts.txt", ios::trunc);
    if (outFile.is_open()) {
        for (const auto &entry : accounts) {
            outFile << entry.second.getAccountNo() << " " << entry.second.getPassword() << " " << entry.second.getBalance() << endl;
        }
        outFile.close();
    } else {
        cout << "Error: Unable to save accounts to file." << endl;
    }
}

// Function to open a new account
void Open_Account() {
    system("cls");
    string id, password;
    cout << "\t Enter Account No.: ";
    cin >> id;

    cout << "\t Enter A Strong Password: ";
    cin >> password;

    Account user;
    user.setAccountNo(id);
    user.setPassword(password);
    user.setBalance(0);

    saveAccountToFile(user);

    cout << "\t Account Created Successfully!" << endl;
    Sleep(3000);
}

// Function to add cash to an account
void Add_Cash() {
    system("cls");
    string id;
    int cash;
    cout << "\t Enter Account No.: ";
    cin >> id;

    unordered_map<string, Account> accounts = loadAccountsFromFile();
    if (accounts.find(id) != accounts.end()) {
        cout << "\t Enter cash to add: ";
        cin >> cash;

        accounts[id].setBalance(accounts[id].getBalance() + cash);
        saveAllAccountsToFile(accounts);

        cout << "\t Cash Added Successfully! New Balance: " << accounts[id].getBalance() << endl;
    } else {
        cout << "\t Account Not Found!" << endl;
    }
    Sleep(3000);
}

// Function to withdraw cash from an account
void Withdraw() {
    system("cls");
    string id, password;
    int cash;
    cout << "\t Enter Account No.: ";
    cin >> id;

    cout << "\t Enter Password: ";
    cin >> password;

    unordered_map<string, Account> accounts = loadAccountsFromFile();
    if (accounts.find(id) != accounts.end() && accounts[id].getPassword() == password) {
        cout << "\t Enter Amount to Withdraw: ";
        cin >> cash;

        if (accounts[id].getBalance() >= cash) {
            accounts[id].setBalance(accounts[id].getBalance() - cash);
            saveAllAccountsToFile(accounts);

            cout << "\t Withdrawal Successful! Remaining Balance: " << accounts[id].getBalance() << endl;
        } else {
            cout << "\t Insufficient Balance!" << endl;
        }
    } else {
        cout << "\t Invalid Account No. or Password!" << endl;
    }
    Sleep(3000);
}

// Main function
int main() {
    Account user;

    bool exit = false;
    while (!exit) {
        system("cls");
        int choice;
        cout << "\t Welcome To Bank Account Management System " << endl;
        cout << "\t******" << endl;
        cout << "\t 1. Open New Account" << endl;
        cout << "\t 2. Add Cash" << endl;
        cout << "\t 3. Withdraw Cash" << endl;
        cout << "\t 4. Exit" << endl;
        cout << "\t Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            Open_Account();
            break;
        case 2:
            Add_Cash();
            break;
        case 3:
            Withdraw();
            break;
        case 4:
            system("cls");
            exit = true;
            cout << "\t Thank You for Using Our System!" << endl;
            Sleep(2000);
            break;
        default:
            cout << "\t Invalid Choice! Try Again." << endl;
            Sleep(2000);
        }
    }

    return 0;
}