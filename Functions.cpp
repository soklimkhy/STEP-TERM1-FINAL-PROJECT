#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <iomanip>
using namespace std;

struct User {
    char username[50];
    char password[50];
    int accountNumber;
};
struct Transaction {
    int transactionID;
    double amount;
    bool isDeposit;
};
// Function to add a transaction record to the file
void addTransactionRecord(int transactionID, double amount, bool isDeposit) {
    Transaction transactionRecord;
    transactionRecord.transactionID = transactionID;
    transactionRecord.amount = amount;
    transactionRecord.isDeposit = isDeposit;

    ofstream outFile("transaction.dat", ios::app | ios::binary);
    if (!outFile) {
        cout << "Error opening file for writing transaction record." << endl;
        return;
    }

    outFile.write(reinterpret_cast<char*>(&transactionRecord), sizeof(Transaction));
    outFile.close();
}



// Function to generate a random 4-digit account ID
int generateAccountID() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1000, 9999);
    return dist(gen);
}
// Function to register a new user
void registerUser() {
    
    User newUser;
    cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo" << endl;
    cout << "                                     Enter a username: ";
    cin >> newUser.username;

    // Validate password length
    while (true) {
        cout << "                       Enter a password (at least 8 characters): ";
        cin >> newUser.password;
        if (strlen(newUser.password) >= 8) {
            break; // Password is valid
        } else {
            cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo" << endl;
            cout << "" << endl;
            cout << "                             [ Password must be at least 8 characters ]" << endl;
            cout << "" << endl;
            cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo" << endl;
        }
    }

    // Generate a random 4-digit account ID
    int accountNumber = generateAccountID(); // Declare accountNumber here
    newUser.accountNumber = accountNumber; // Assign the generated accountNumber

    ofstream outFile("project.dat", ios::app | ios::binary);
    if (!outFile) {
        cout << "Error opening file for writing." << endl;
        return;
    }
    outFile.write(reinterpret_cast<char*>(&newUser), sizeof(User));
    outFile.close();
    cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo" << endl;
    cout << "                                                                               " << endl;
    cout << "                                     Registration successful!" << endl;
    cout << "                                     Your account ID is: " << newUser.accountNumber << endl;
    cout << "                                                                               " << endl;
    
}

// Function to authenticate a user
bool authenticateUser() {
    User inputUser;
    cout<<"                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo"<<endl;
    cout << "                                     Enter your username: ";
    cin >> inputUser.username;
    cout << "                                     Enter your password: ";
    cin >> inputUser.password;

    ifstream inFile("project.dat", ios::binary);
    if (!inFile) {
        cout << "                                   Error opening file for reading." << endl;
        return false;
    }

    User storedUser;
    while (inFile.read(reinterpret_cast<char*>(&storedUser), sizeof(User))) {
        if (strcmp(storedUser.username, inputUser.username) == 0 && strcmp(storedUser.password, inputUser.password) == 0) {
            inFile.close();
            return true; // Authentication successful
        }
    }

    inFile.close();
    return false; // Authentication failed
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Global variable to store the user's current money balance
double currentBalance = 0.0;
int generateTransactionID() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(100000, 999999);
    return dist(gen);
}
// Function to display the current wallet balance
void displayWalletBalance() {
    cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo                        " << endl;
    cout << "                       o                                                  o                        " << endl;
    cout << "                       o                Wallet Information                o                        " << endl;
    cout << "                       o                                                  o                        " << endl;
    cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo                        " << endl;
    cout << "                                       Current Balance: $" << currentBalance << "                                       " << endl;
}

// Function to deposit money into the wallet with a random transaction ID
void depositMoney() {
    double amount;
    cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo                        " << endl;
    cout << "                       o                                                  o                        " << endl;
    cout << "                       o                Depositing Money                  o                        " << endl;
    cout << "                       o                                                  o                        " << endl;
    cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo                        " << endl;
    cout << "                                       Current Balance: $" << currentBalance << "                  " << endl;
    cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo                        " << endl;
    cout << "                                 Enter the amount to deposit: $";
    cin >> amount;
    
    

    if (amount <= 0) {
        cout << "                    Invalid amount. Please enter a positive value for deposit." << endl;
        return;
    }
    
    int transactionID = generateTransactionID(); // Generate a random transaction ID

    addTransactionRecord(transactionID, amount, true);
    currentBalance += amount;
    cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo                        " << endl;
    cout << "                                                                                                   " << endl;
    cout << "                                        Deposit successful!                                        " << endl;
    cout << "                                                                                                   " << endl;
    cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo                        " << endl;
    cout << "                                      Transaction ID: " << transactionID                             << endl;
    cout << "                                      Current balance: $" << currentBalance                          << endl;
    
}

// Function to withdraw money from the wallet with a random transaction ID
void withdrawMoney() {
    double amount;
    cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo                        " << endl;
    cout << "                       o                                                  o                        " << endl;
    cout << "                       o                Withdrawing Money                 o                        " << endl;
    cout << "                       o                                                  o                        " << endl;
    cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo                        " << endl;
    cout << "                                     Current Balance: $" << currentBalance << "                                       " << endl;
    cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo                        " << endl;
    cout << "                                 Enter the amount to withdraw: $";
    cin >> amount;

    if (amount <= 0 || amount > currentBalance) {
        cout << "                    Invalid amount. Please enter a valid amount for withdrawal." << endl;
        cout << "                       Or It may caused by your wallet is 0$ or not enough.  " << endl;
        cout << "                                                                                                   " << endl;
        return;
    }
    int transactionID = generateTransactionID(); // Generate a random transaction ID
    addTransactionRecord(transactionID, amount, false);
    currentBalance -= amount;
    cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo                        " << endl;
    cout << "                                                                                                   " << endl;
    cout << "                                    Withdrawal successful!                                         " << endl;
    cout << "                                                                                                   " << endl;
    cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo                        " << endl;
    cout << "                                     Transaction ID: " << transactionID                              << endl;
    cout << "                                     Current balance: $" << currentBalance                           << endl;
    
}

// Function to manage the wallet
void Wallet() {
    char walletChoice;
    do {
        displayWalletBalance();
        cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo                        " << endl;
        cout << "                       o                1. Deposit Money                  o                        " << endl;
        cout << "                       o                2. Withdraw Money                 o                        " << endl;
        cout << "                       o                3. Back                           o                        " << endl;
        cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo                        " << endl;
        cout << "                                    Choose numbers from 1-3: ";
        cin >> walletChoice;

        switch (walletChoice) {
            case '1':
                depositMoney();
                break;
            case '2':
                withdrawMoney();
                break;
            case '3':
                break;
            default:
                cout << "                         Invalid choice. Please choose a number from 1-3." << endl;
        }
    } while (walletChoice != '3');
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function to display user profile
void displayProfile(const char* username) {
    ifstream inFile("project.dat", ios::binary);

    if (!inFile) {
        cout << "Error opening file for reading." << endl;
        return;
    }

    User currentUser;
    bool found = false;

    while (inFile.read(reinterpret_cast<char*>(&currentUser), sizeof(User))) {
        if (strcmp(currentUser.username, username) == 0) {
            found = true;
            break;
        }
    }

    inFile.close();

    if (found) {
        cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo                        " << endl;
        cout << "" << endl;
        cout << "                                     User Profile Information                                      " << endl;
        cout << "" << endl;
        cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo                        " << endl;
        cout << "                                        Username: " << currentUser.username << "                                        " << endl;
        cout << "                                        Account ID: " << currentUser.accountNumber << "                                   " << endl;
        cout << "                                        Password: " << currentUser.password << "                                        " << endl;
    } else {
        cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo                        " << endl;
        cout << "" << endl;
        cout << "                        [ Profile not found. Please check your username. ]" << endl;
        cout << "" << endl;
        
    }
}
// Function to display user profile information
void displayProfile(const char* username, int accountNumber, const char* password) {
    cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo    " << endl;
    cout << "                                                                               " << endl;
    cout << "                                   User Profile Information                    " << endl;
    cout << "                                                                               " << endl;
    cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo" << endl;
    cout << "                       o              Username: " << username << "                  o" << endl;
    cout << "                       o              Wallet Number: " << accountNumber << "             o" << endl;
    cout << "                       o              Password: " << password << "                  o" << endl;
    cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo" << endl;
}

// Function to display the profile for the authenticated user
void displayAuthenticatedUserProfile(const User& user) {
    displayProfile(user.username, user.accountNumber, user.password);
}
// Function to manage user profile
void Profile() {
    char username[50];
    cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo                        " << endl;
    cout << "                                Enter your username to confirm: ";
    cin >> username;

    displayProfile(username);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function to display transaction history and search for a specific transaction
void TransactionsHistory() {
    cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo                        " << endl;
    cout << "                                                                               " << endl;
    cout << "                                       Transaction History                     " << endl;
    cout << "                                                                               " << endl;
    cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo" << endl;

    ifstream inFile("transaction.dat", ios::binary);
    if (!inFile) {
        cout << "Error opening file for reading." << endl;
        return;
    }

    Transaction currentTransaction;
    bool found = false;

    while (inFile.read(reinterpret_cast<char*>(&currentTransaction), sizeof(Transaction))) {
        cout << "                                      Transaction ID: " << currentTransaction.transactionID << "                   " << endl;
        if (currentTransaction.isDeposit) {
            cout << "                                     Deposit Amount: $" << fixed << setprecision(2) << currentTransaction.amount << "                " << endl;
        } else {
            cout << "                                    Withdrawal Amount: $" << fixed << setprecision(2) << currentTransaction.amount << "             " << endl;
        }
        cout << "                       o--------------------------------------------------o" << endl;
    }

    inFile.close();

    cout << "                    Search Transaction ID or Press any key to go back: ";
    int targetTransactionID;
    cin >> targetTransactionID;

    // Reopen the file to search for the specific transaction
    ifstream searchFile("transaction.dat", ios::binary);
    if (!searchFile) {
        cout << "Error opening file for reading." << endl;
        return;
    }

    while (searchFile.read(reinterpret_cast<char*>(&currentTransaction), sizeof(Transaction))) {
        if (currentTransaction.transactionID == targetTransactionID) {
            found = true;
            cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo" << endl;
            cout << "                                                                               " << endl;
            cout << "                                       Transaction Searched                     " << endl;
            cout << "                                                                               " << endl;
            cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo" << endl;
            cout << "                                      Transaction ID: " << currentTransaction.transactionID << "                    " << endl;
            if (currentTransaction.isDeposit) {
                cout << "                                     Deposit Amount: $" << fixed << setprecision(2) << currentTransaction.amount << "               " << endl;
            } else {
                cout << "                                    Withdrawal Amount: $" << fixed << setprecision(2) << currentTransaction.amount << "             " << endl;
            }

            
        }
    }

    searchFile.close();

    if (!found) {
        cout << "                                         [Return back menu]                                                                  " << endl;
        return;
    }
    cin.ignore(); // Clear the input buffer
    cin.get();    // Wait for user input (any key)
    return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function to compare transactions for sorting in ascending order
bool compareAscending(const Transaction& a, const Transaction& b) {
    return a.transactionID < b.transactionID;
}

// Function to compare transactions for sorting in descending order
bool compareDescending(const Transaction& a, const Transaction& b) {
    return a.transactionID > b.transactionID;
}

void SortTransactions() {
    ifstream inFile("transaction.dat", ios::binary);

    if (!inFile) {
        cout << "Error opening file for reading." << endl;
        return;
    }

    Transaction currentTransaction;
    Transaction transactions[100]; // Assuming a maximum of 100 transactions

    int transactionCount = 0;
    while (inFile.read(reinterpret_cast<char*>(&currentTransaction), sizeof(Transaction))) {
        transactions[transactionCount] = currentTransaction;
        transactionCount++;
    }

    inFile.close();

    char sortOrder;
    cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo                        " << endl;
    cout << "                                                                               " << endl;
    cout << "                                        Sort Transactions                              " << endl;
    cout << "                                                                               " << endl;
    cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo" << endl;
    cout << "                                       Choose sorting order:                               " << endl;
    cout << "                                          1. Ascending                                      " << endl;
    cout << "                                          2. Descending                                     " << endl;
    cout << "                       o--------------------------------------------------o" << endl;
    cout << "                                   Enter your choice (1 or 2): ";
    cin >> sortOrder;

    if (sortOrder != '1' && sortOrder != '2') {
        cout << "                                                                               " << endl;
        cout << "                               Invalid choice. Please choose 1 or 2." << endl;
        return;
    }

    // Sort the transactions based on user choice
    if (sortOrder == '1') {
        for (int i = 0; i < transactionCount - 1; i++) {
            for (int j = 0; j < transactionCount - i - 1; j++) {
                if (compareAscending(transactions[j], transactions[j + 1])) {
                    // Swap transactions[j] and transactions[j + 1]
                    Transaction temp = transactions[j];
                    transactions[j] = transactions[j + 1];
                    transactions[j + 1] = temp;
                }
            }
        }
    } else {
        for (int i = 0; i < transactionCount - 1; i++) {
            for (int j = 0; j < transactionCount - i - 1; j++) {
                if (compareDescending(transactions[j], transactions[j + 1])) {
                    // Swap transactions[j] and transactions[j + 1]
                    Transaction temp = transactions[j];
                    transactions[j] = transactions[j + 1];
                    transactions[j + 1] = temp;
                }
            }
        }
    }

    // Display the sorted transactions
    cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo" << endl;
    cout << "                                                                               " << endl;
    cout << "                                         Sorted Transactions                              " << endl;
    cout << "                                                                               " << endl;
    cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo" << endl;
    for (int i = 0; i < transactionCount; i++) {
        cout << "                                      Transaction ID: " << transactions[i].transactionID << "                    " << endl;
        if (transactions[i].isDeposit) {
            cout << "                                      Deposit Amount: $" << fixed << setprecision(2) << transactions[i].amount << "               " << endl;
        } else {
            cout << "                                     Withdrawal Amount: $" << fixed << setprecision(2) << transactions[i].amount << "             " << endl;
        }
        cout << "                       o--------------------------------------------------o" << endl;
    }


}


////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function to delete a transaction record by ID
void DeleteTransactionsByID(int targetTransactionID) {
    ifstream inFile("transaction.dat", ios::binary);
    if (!inFile) {
        cout << "Error opening file for reading." << endl;
        return;
    }

    ofstream outFile("temp.dat", ios::binary);
    if (!outFile) {
        cout << "Error opening temporary file for writing." << endl;
        return;
    }

    Transaction currentTransaction;

    bool found = false;
    while (inFile.read(reinterpret_cast<char*>(&currentTransaction), sizeof(Transaction))) {
        if (currentTransaction.transactionID == targetTransactionID) {
            found = true;
            continue; // Skip the transaction to delete
        }
        outFile.write(reinterpret_cast<const char*>(&currentTransaction), sizeof(Transaction));
    }

    inFile.close();
    outFile.close();

    if (found) {
        if (remove("transaction.dat") != 0) {
            cout << "Error deleting the original transaction file." << endl;
            return;
        }

        if (rename("temp.dat", "transaction.dat") != 0) {
            cout << "Error renaming the temporary file." << endl;
            return;
        }

        cout << "                                Transaction with ID " << targetTransactionID << " has been deleted." << endl;
    } else { 
        cout << "                                Transaction with ID " << targetTransactionID << " not found." << endl;
        remove("temp.dat"); // Delete the temporary file
    }
}













