#include <iostream>
#include <fstream>
#include <cctype>
#include <random>
#include <Windows.h>
#include "Functions.cpp"
using namespace std;
int main()
{
    char choices;
    char choicesUser;
    system("Color 0B");
    cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo                        " << endl;
    cout << "                       o            FINAL-PROJECT-BY-SOKLIMKHY            o                        " << endl;
    cout << "                       o              BANK-MANAGEMENT-SYSTEM              o                        " << endl;
    cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo                        " << endl;
    cout << "                                                                                                   " << endl;
    cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
    cout << "                                                                                                   " << endl;
    cout << "                                             WELCOME                                               " << endl;
    cout << "                                                                                                   " << endl;
    cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
    cout << "                                                                                                   " << endl;
    do
    {

        cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo                        " << endl;
        cout << "                       o                    1. Login                      o                        " << endl;
        cout << "                       o                    2. Register                   o                        " << endl;
        cout << "                       o                    3. Exit                       o                        " << endl;
        cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo                        " << endl;
        cout << "                                    Choose numbers from 1-3: ";
        cin >> choices;
        switch (choices)
        {
        case '1':

            if (authenticateUser())
            {
                cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo                        " << endl;
                cout << "                                                                                                   " << endl;
                cout << "                                         Login successful!                                         " << endl;
                cout << "                                                                                                   " << endl;
                do
                {
                    cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo                   " << endl;
                    cout << "                       o      1.  Wallet                                  o                   " << endl;
                    cout << "                       o      2.  Profile                                 o                   " << endl;
                    cout << "                       o      3.  View or Search Transactions history     o                   " << endl;
                    cout << "                       o      4.  Sort transactions by ID                 o                   " << endl;
                    cout << "                       o      5.  Delete transactions by ID               o                   " << endl;
                    cout << "                       o      6.  Log out                                 o                   " << endl;
                    cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo                   " << endl;
                    cout << "                                    Choose numbers from 1-6: ";
                    cin >> choicesUser;
                    switch (choicesUser)
                    {
                    case '1':
                        Wallet();
                        break;
                    case '2':
                        Profile();
                        break;
                    case '3':
                        TransactionsHistory();
                        break;
                    case '4':
                        SortTransactions();
                        break;
                    case '5':
                        int targetTransactionID;
                        cout << "                            Enter the Transaction ID to delete: ";
                        cin >> targetTransactionID;
                        DeleteTransactionsByID(targetTransactionID);
                        break;
                    case '6':
                        break;
                    default:
                        cout << "                           Invalid choice. Please choose a number from 1-6." << endl;
                    }

                } while (choicesUser != '6');
            }
            else
            {
                cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo                        " << endl;
                cout << "                                                                                                   " << endl;
                cout << "                             Authentication failed. Please try again.                              " << endl;
                cout << "                                                                                                   " << endl;
            }
            break;

        case '2':
            registerUser();
            break;

        case '3':
            cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo                        " << endl;
            cout << "                                                                                                   " << endl;
            cout << "                                       Exiting the program.                                        " << endl;
            cout << "                                                                                                   " << endl;
            cout << "                       oxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo                        " << endl;
            break;
        }
    } while (choices != '3');

    return 0;
}
