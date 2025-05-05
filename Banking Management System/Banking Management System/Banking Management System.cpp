// Banking Management System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <windows.h>

void showBalance(double balance);
double deposit();
double withdraw(double balance);
const char currency = char(156); //£

int main() {
    double balance = 0;
    int choice = 0;


    do {
        //choices menu
        std::cout << "**********************\n";
        std::cout << "Enter your choice:\n";
        std::cout << "**********************\n";
        std::cout << "1. show balance\n";
        std::cout << "2. deposit money\n";
        std::cout << "3. withdraw money\n";
        std::cout << "4. exit\n";
        std::cin >> choice;


        system("CLS");
        //clear screen
        Sleep(1000);
        //timer

        std::cin.clear();
        fflush(stdin);
        //clear input buffer so it do not keep rolling

        switch (choice) {
            //testing different cases for the menu choice
        case 1: showBalance(balance);
            break;
        case 2: balance += deposit();
            showBalance(balance);
            break;
        case 3: balance -= withdraw(balance);
            break;
        case 4: std::cout << "Thanks for visiting!\n";
            break;
        default:std::cout << "Invalid Choice!\n";
        }
    } while (choice != 4);
    return 0;
}
void showBalance(double balance) {
    std::cout << "Your balance is: " << currency << std::setprecision(2) << std::fixed << balance << "\n";
    Sleep(1000);
    system("CLS");
    //clear screen

}

double deposit() {
    double amount = 0;
    std::cout << "Enter the amount to be deposited: " << currency;
    std::cin >> amount;

    if (amount > 0) {
        return amount;
    }
    else {
        std::cout << "That amount is invalid!\n";
        return 0;
    }
}

double withdraw(double balance) {
    double amount = 0;
    std::cout << "Enter the amount to be withdrawn: \n";
    std::cin >> amount;

    if (amount > balance) {
        std::cout << "Insufficient funds\n";
        return 0;
    }
    else if (amount < 0) {
        std::cout << "That is not a valid amount\n";
        return 0;
    }
    return amount;
}
// This program is a simple banking management system that allows users to check their balance, deposit money, and withdraw money.
// Program execution ends here