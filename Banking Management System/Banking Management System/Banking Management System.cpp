// Banking Management System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <windows.h>
using namespace std;

void showBalance(double balance);
double deposit();
double withdraw(double balance);
const char currency = char(156); //£

void heading() {
    cout << "\t\t\t\t\t*****************************************\n";
    cout << "\t\t\t\t\t*     | BANKING MANAGEMENT SYSTEM |     *\n";
    cout << "\t\t\t\t\t*****************************************\n";
}


class accountData
{
    int ID;
    char name[50];
    double amount;
public:
    void newAccount();

};

void accountData::newAccount()
{
    
    system("CLS");
    heading();
    cout << "\t\t\t\t\t*            | NEW ACCOUNT |            *\n";
    cout << "\t\t\t\t\t*****************************************\n";
    ID = ID+1;        
    cout << "\t\t\t\t\tAccount No. : "<< ID <<"\n";
    cout << "\t\t\t\t\tEnter the Name of the Account holder: \n";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\t\t\t\t\tEnter The Deposit Amount: \n";
    cin >> amount;
    cout << "\t\t\t\t\tNew Account Created \n";
    Sleep(3000);
    int main();
}

void writeAccount();


int main() {
    double balance = 0;
    int choice = 0;

    do {
    //choices menu   
        system("cls");
        heading();
        cout << "\t\t\t\t\t* Choose One Of The Following Options:  *\n";   
        cout << "\t\t\t\t\t*****************************************\n";
        cout << "\t\t\t\t\t* 1. show balance                       *\n";
        cout << "\t\t\t\t\t* 2. deposit money                      *\n";
        cout << "\t\t\t\t\t* 3. withdraw money                     *\n";
        cout << "\t\t\t\t\t* 4. account                            *\n";
        cout << "\t\t\t\t\t* 5. exit                               *\n";
        cout << "\t\t\t\t\t* 6. exit                               *\n";
        cout << "\t\t\t\t\t* 7. exit                               *\n";
        cout << "\t\t\t\t\t*****************************************\n";
        cout << "\t\t\t\t\t";
        cin >> choice;

        system("CLS");
        //clear screen
        Sleep(1000);
        //timer

        cin.clear();
        fflush(stdin);
        //clear input buffer so it does not keep rolling

        switch (choice) {
        //testing different cases for the menu choice
        case 1: showBalance(balance);
            break;
        case 2: balance += deposit();
            showBalance(balance);
            break;
        case 3: balance -= withdraw(balance);
            break;
        case 4: writeAccount();
            break;        
        case 7: cout << "\t\t\t\t\tThanks for visiting!\n";
            break;
        default: cout << "\t\t\t\t\tInvalid Choice!\n";
        }
    } while (choice != 7);
    return 0;
}

void writeAccount() {
    accountData data;
    ofstream writeFile;
    writeFile.open("AccountData.dat", ios::app | ios::binary);
    data.newAccount();
    writeFile.write(reinterpret_cast<char*> (&data), sizeof(accountData));
    writeFile.close();

}

void showBalance(double balance) {
//show balance
    heading();
    cout << "\t\t\t\t\t*              | BALANCE |              *\n";
    cout << "\t\t\t\t\t*****************************************\n";
    cout << "\t\t\t\t\tYour balance is: " << currency << setprecision(2) << fixed << balance << "\n";
    Sleep(3000);
    system("CLS");
    //clear screen
}

double deposit() {
//deposit account
    heading();
    cout << "\t\t\t\t\t*              | DEPOSIT |              *\n";
    cout << "\t\t\t\t\t*****************************************\n";
    double amount = 0;
    cout << "\t\t\t\t\tEnter the amount to be deposited: " << currency;
    cin >> amount;
    Sleep(3000);
    system("CLS");

    if (amount > 0) {
        return amount;
    }
    else {
        cout << "\t\t\t\t\tThat amount is invalid!\n";
        return 0;
    }
}

double withdraw(double balance) {
//withdraw balance
    heading();
    cout << "\t\t\t\t\t*              | WITHDRAW |             *\n";
    cout << "\t\t\t\t\t*****************************************\n";
    double amount = 0;
    cout << "\t\t\t\t\tCurrent balance: " << currency << setprecision(2) << fixed << balance << "\n";
    cout << "\t\t\t\t\tEnter the amount to be withdrawn: "<<currency;
    cin >> amount;
    Sleep(3000);
    system("CLS");

    if (amount > balance) {
        cout << "\t\t\t\t\tInsufficient funds\n";
        return 0;
    }
    else if (amount < 0) {
        cout << "\t\t\t\t\tThat is not a valid amount\n";
        return 0;
    }
    return amount;
}

// This program is a simple banking management system that allows users to check their balance, deposit money, and withdraw money.
// Program execution ends here

