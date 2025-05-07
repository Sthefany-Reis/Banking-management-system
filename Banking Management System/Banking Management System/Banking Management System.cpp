// Banking Management System.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <iomanip>
#include <fstream>
#include <windows.h>
#include <string>
#include <sstream>
#include <vector>
using namespace std;
const char currency = char(156); //£


void heading() {
	//function to display heading
	cout << "\t\t\t\t\t*****************************************\n";
	cout << "\t\t\t\t\t*     | BANKING MANAGEMENT SYSTEM |     *\n";
	cout << "\t\t\t\t\t*****************************************\n";
}


struct Account {
	//struct to store account data
	string id;
	string name;
	string balance;
};

Account fileLine(const string& line) {
	//function to convert file line to accounts
	stringstream ss(line);
	string id, name, balance;
	getline(ss, id, ',');
	getline(ss, name, ',');
	getline(ss, balance, ',');
	return { id, name, balance };
}


vector<Account> readAccounts() {
	//function to read accounts from the file
	vector<Account> accounts;
	//vector to store accounts
	ifstream file("account.csv");
	string line;
	bool isHeader = true;
	// Flag to skip header line
	while (getline(file, line)) {
		if (isHeader) {
			isHeader = false;
			continue;
		}
		accounts.push_back(fileLine(line));
		// Convert each line to an Account object and add to the vector
	}

	return accounts;
	// Return the vector of accounts

}

void saveAccounts(const vector<Account>& accounts) {
	//function to save accounts to file
	ofstream file("account.csv");
	file << "ID,Name,Balance\n";
	for (const auto& a : accounts) {
		file << a.id << "," << a.name << "," << a.balance << "\n";

	}
}


void appendAccount(const Account& a) {
	//function to append each account to the file
	ifstream check("account.csv");
	// Check if file exists

	if (!check.is_open()) {
		// If file doesn't exist, create it
		ofstream createFile("account.csv");
		createFile.close();
	}


	bool newFile = !check.good();
	// Check if file exists by attempting to open it
	check.close();

	ofstream file("account.csv", ios::app);

	if (newFile) {
		// If file didn't exist, create it and add header
		file << "ID,Name,Balance\n";
	}

	file << a.id << "," << a.name << "," << a.balance << "\n";
	// Append the new account to the file
}


void displayAccounts() {
	//function to display accounts
	vector<Account> accounts = readAccounts();
	cout << "\t\t\t\t\t*           | All Accounts |            *\n";
	cout << "\t\t\t\t\t*****************************************\n";
	for (const auto& a : accounts) {
		// Loop through each account and display its details
		cout << "\t\t\t\t\t* ID: " << a.id << ", Name: " << a.name << ", Balance: " << currency << setprecision(2) << fixed << a.balance << "\n";
	}
	cout << "\t\t\t\t\t*****************************************\n";
	cout << "\t\t\t\t\t* Press any key to continue...\n";
	cin.ignore();
	cin.get(); // Wait for user input

}


void newAccount() {
	//function to add new accounts
	vector<Account> accounts = readAccounts();
	Account a;
	string id;
	cout << "\t\t\t\t\t*            | New Account |            *\n";
	cout << "\t\t\t\t\t*****************************************\n";
	cout << "\t\t\t\t\t* Please Enter The Account ID: ";
	cin.ignore(); // Clear newline
	getline(cin, id);

	bool exists = false;
	// Flag to check if account is found

	for (auto& a : accounts) {
		// Check if the account ID already exists
		if (a.id == id) {
			exists = true;
			break;
		}
	}
	if (exists) {
		// If exists, display a message and return
		cout << "\t\t\t\t\t*****************************************\n";
		cout << "\t\t\t\t\t* Account ID Already Exists.            *\n";
		cout << "\t\t\t\t\t* Please Enter A Different ID.          *\n";
		cout << "\t\t\t\t\t*****************************************\n";
		Sleep(2000); //timer
		system("cls");
		// Clear the screen and show the heading again
		heading();
		return newAccount();
	}
	else {
		// If doesn't, proceed to create a new account
		a.id = id;
		// Set the ID for the new account
		cout << "\t\t\t\t\t* Please Enter Account Holder's Name: ";
		getline(cin, a.name);
		cout << "\t\t\t\t\t* Please Enter Initial Balance: " << currency << setprecision(2) << fixed;
		getline(cin, a.balance);
		appendAccount(a);
		// Append the new account to the file
		cout << "\t\t\t\t\t*****************************************\n";
		cout << "\t\t\t\t\t*   | Account Created Successfully |    *\n";
		cout << "\t\t\t\t\t*****************************************\n";
		cout << "\t\t\t\t\t* Account Details:                      *\n";
		cout << "\t\t\t\t\t* Account ID: " << a.id << "\n";
		cout << "\t\t\t\t\t* Account Holder's Name: " << a.name << "\n";
		cout << "\t\t\t\t\t* Initial Balance: " << currency << setprecision(2) << fixed << a.balance << "\n";
		cout << "\t\t\t\t\t*****************************************\n";

		Sleep(2000); //timer
	}
}


void editAccount() {
	//function to edit existing accounts
	vector<Account> accounts = readAccounts();
	Account a;
	string id, name;
	cout << "\t\t\t\t\t*           | Edit Account |            *\n";
	cout << "\t\t\t\t\t*****************************************\n";
	cout << "\t\t\t\t\t* Please Enter The Account ID To Edit: ";
	cin.ignore(); // Clear newline
	getline(cin, id);

	bool exists = false;
	// Flag to check if account exists

	for (auto& a : accounts) {
		// Loop through accounts

		if (a.id == id) {
			exists = true;
			system("cls");
			heading();
			cout << "\t\t\t\t\t*****************************************\n";
			cout << "\t\t\t\t\t*           | Account Found |           *\n";
			cout << "\t\t\t\t\t*****************************************\n";
			cout << "\t\t\t\t\t   ID: " << a.id << ",   Name: " << a.name << ",  Balance: " << currency << setprecision(2) << fixed << a.balance << "\n";
			cout << "\t\t\t\t\t*****************************************\n";
			cout << "\t\t\t\t\t* Please Enter New Name: ";
			getline(cin, a.name);
			cout << "\t\t\t\t\t* Please Enter New Balance: " << currency << setprecision(2) << fixed;
			getline(cin, a.balance);
			if (exists) {
				// If exists save the updated accounts
				saveAccounts(accounts);
				cout << "\t\t\t\t\t*****************************************\n";
				cout << "\t\t\t\t\t* Account Updated Successfully.\n";
				cout << "\t\t\t\t\t*****************************************\n";
				cout << "\t\t\t\t\t* Account Details:                      *\n";
				cout << "\t\t\t\t\t* Account ID: " << a.id << "\n";
				cout << "\t\t\t\t\t* Account Holder's Name: " << a.name << "\n";
				cout << "\t\t\t\t\t* Updated Balance: " << currency << setprecision(2) << fixed << a.balance << "\n";
				cout << "\t\t\t\t\t*****************************************\n";
				cout << "\t\t\t\t\t* Press any key to continue...\n";
				cin.ignore();
				cin.get(); // Wait for user input
				cout << "\t\t\t\t\t*****************************************\n";
				system("cls");
			}
			else {
				// If doesnt exist
				cout << "\t\t\t\t\t*****************************************\n";
				cout << "\t\t\t\t\t* Account ID Not Found.\n";
				cout << "\t\t\t\t\t* Please Enter A Valid ID.              *\n";
				cout << "\t\t\t\t\t*****************************************\n";
				Sleep(2000); //timer
				system("cls");
				heading();
				return editAccount();
			}
			break;
		}
	}


}


void deleteAccount() {
	//function to delete existing accounts
	vector<Account> accounts = readAccounts();
	string id;
	cout << "\t\t\t\t\t*           | Delete Account |          *\n";
	cout << "\t\t\t\t\t*****************************************\n";
	cout << "\t\t\t\t\t* Please Enter The Account ID To Delete: ";
	cin.ignore(); // Clear newline
	getline(cin, id);

	bool exists = false;
	// Flag to check if account exists
	for (auto& a : accounts) {
		// Loop through accounts 
		if (a.id == id) {
			exists = true;
			system("cls");
			heading();
			cout << "\t\t\t\t\t*****************************************\n";
			cout << "\t\t\t\t\t*           | Account Found |           *\n";
			cout << "\t\t\t\t\t*****************************************\n";
			cout << "\t\t\t\t\t*  ID: " << a.id << ",   Name: " << a.name << ",  Balance: " << currency << setprecision(2) << fixed << a.balance << "\n";
			cout << "\t\t\t\t\t*****************************************\n";
			cout << "\t\t\t\t\t* Are You Sure You Want To Delete This Account? (Y/N): ";
			string confirm;
			getline(cin, confirm);
			if (confirm == "Y" || confirm == "y") {
				// If confirmed, delete the account
				accounts.erase(remove_if(accounts.begin(), accounts.end(),
					[&](Account a) { return a.id == id; }), accounts.end());
				// Remove the account 
				saveAccounts(accounts);
				// Save the updated accounts
				cout << "\t\t\t\t\t*****************************************\n";
				cout << "\t\t\t\t\t*   | Account Deleted Successfully |    *\n";
				cout << "\t\t\t\t\t*****************************************\n";
				break;
			}
			else {
				// If not confirmed
				cout << "\t\t\t\t\t*****************************************\n";
				cout << "\t\t\t\t\t*     | Account Deletion Cancelled |    *\n";
				cout << "\t\t\t\t\t*****************************************\n";
				Sleep(2000); //timer
				system("cls");
				heading();
				return deleteAccount();
			}
			break;
		}
		// If ID doesnt exist, set exists to false
		else {
			exists = false;
		}

	}
	if (!exists) {
		// If ID doesn't exist
		cout << "\t\t\t\t\t*****************************************\n";
		cout << "\t\t\t\t\t*           | Account Not Found |       *\n";
		cout << "\t\t\t\t\t*****************************************\n";
		cout << "\t\t\t\t\t* Account ID Not Found.                 *\n";
		cout << "\t\t\t\t\t* Please Enter A Valid ID.              *\n";
		cout << "\t\t\t\t\t*****************************************\n";
		Sleep(2000); //timer
		system("cls");
		heading();
		return deleteAccount();
	}
}

void manageBalance() {
	//function to manage balance
	vector<Account> accounts = readAccounts();
	string id, choice;
	cout << "\t\t\t\t\t*           | Manage Balance |          *\n";
	cout << "\t\t\t\t\t*****************************************\n";
	cout << "\t\t\t\t\t* 1. Deposit Money                      *\n";
	cout << "\t\t\t\t\t* 2. Withdraw Money                     *\n";
	cout << "\t\t\t\t\t*****************************************\n";
	cout << "\t\t\t\t\t* Please Enter Your Choice: ";
	cin >> choice;
	cin.ignore(); // Clear newline
	if (choice == "1") {
		// Deposit money
		cout << "\t\t\t\t\t* Please Enter The Account ID: ";
		getline(cin, id);
		bool exists = false;
		// Flag to check if account exists
		for (auto& a : accounts) {
			// Loop through accounts to find the ID
			if (a.id == id) {
				exists = true;
				system("cls");
				heading();
				cout << "\t\t\t\t\t*****************************************\n";
				cout << "\t\t\t\t\t*           | Account Found |           *\n";
				cout << "\t\t\t\t\t*****************************************\n";
				cout << "\t\t\t\t\t*  ID: " << a.id << ",   Name: " << a.name << ",  Balance: " << currency << setprecision(2) << fixed << a.balance << "\n";
				cout << "\t\t\t\t\t*****************************************\n";
				cout << "\t\t\t\t\t* Please Enter Amount To Deposit: " << currency << setprecision(2) << fixed;
				string amount;
				getline(cin, amount);
				a.balance = to_string(stod(a.balance) + stod(amount));
				saveAccounts(accounts);
				// Save the updated accounts 
				cout << "\t\t\t\t\t*****************************************\n";
				cout << "\t\t\t\t\t*   | Amount Deposited Successfully |   *\n";
				cout << "\t\t\t\t\t*****************************************\n";
				cout << "\t\t\t\t\t* Account Details:                      *\n";
				cout << "\t\t\t\t\t* Account ID: " << a.id << "\n";
				cout << "\t\t\t\t\t* Account Holder's Name: " << a.name << "\n";
				cout << "\t\t\t\t\t* Updated Balance: " << currency << setprecision(2) << fixed << a.balance << "\n";
				cout << "\t\t\t\t\t*****************************************\n";
				break;
			}
		}
		if (!exists) {
			// If account ID doesn't exist
			cout << "\t\t\t\t\t*****************************************\n";
			cout << "\t\t\t\t\t*           | Account Not Found |       *\n";
			cout << "\t\t\t\t\t*****************************************\n";
			cout << "\t\t\t\t\t* Account ID Not Found.                 *\n";
			cout << "\t\t\t\t\t* Please Enter A Valid ID.              *\n";
			cout << "\t\t\t\t\t*****************************************\n";
			Sleep(2000); //timer
			system("cls");
			heading();
			return manageBalance();
		}
	}
	else if (choice == "2") {
		// Withdraw money
		cout << "\t\t\t\t\t* Please Enter The Account ID: ";
		getline(cin, id);
		bool exists = false;
		for (auto& a : accounts) {
			// Loop through accounts to find the ID
			if (a.id == id) {
				exists = true;
				system("cls");
				heading();
				cout << "\t\t\t\t\t*****************************************\n";
				cout << "\t\t\t\t\t*           | Account Found |           *\n";
				cout << "\t\t\t\t\t*****************************************\n";
				cout << "\t\t\t\t\t*  ID: " << a.id << ",   Name: " << a.name << ",  Balance: " << currency << setprecision(2) << fixed << a.balance << "\n";
				cout << "\t\t\t\t\t*****************************************\n";
				cout << "\t\t\t\t\t* Please Enter Amount To Withdraw: " << currency << setprecision(2) << fixed;
				string amount;
				getline(cin, amount);
				if (stod(a.balance) >= stod(amount)) {
					// If sufficient balance
					a.balance = to_string(stod(a.balance) - stod(amount));
					saveAccounts(accounts);
					// Save the updated accounts 
					cout << "\t\t\t\t\t*****************************************\n";
					cout << "\t\t\t\t\t*   | Amount Withdrawn Successfully |   *\n";
					cout << "\t\t\t\t\t*****************************************\n";
					cout << "\t\t\t\t\t* Account Details:                      *\n";
					cout << "\t\t\t\t\t* Account ID: " << a.id << "\n";
					cout << "\t\t\t\t\t* Account Holder's Name: " << a.name << "\n";
					cout << "\t\t\t\t\t* Updated Balance: " << currency << setprecision(2) << fixed << a.balance << "\n";
					cout << "\t\t\t\t\t*****************************************\n";
					break;
				}
				else {
					// If insufficient balance
					cout << "\t\t\t\t\t*****************************************\n";
					cout << "\t\t\t\t\t*        | Insufficient Balance |       *\n";
					cout << "\t\t\t\t\t*****************************************\n";
					cout << "\t\t\t\t\t* Insufficient Balance.                 *\n";
					cout << "\t\t\t\t\t* Please Enter A Valid Amount.          *\n";
					cout << "\t\t\t\t\t*****************************************\n";
					Sleep(2000); //timer
					system("cls");
					heading();
					return manageBalance();
				}
				break;
			}
		}
		if (!exists) {
			// If account ID doesnt exist
			cout << "\t\t\t\t\t*****************************************\n";
			cout << "\t\t\t\t\t*           | Account Not Found |       *\n";
			cout << "\t\t\t\t\t*****************************************\n";
			cout << "\t\t\t\t\t* Account ID Not Found.                 *\n";
			cout << "\t\t\t\t\t* Please Enter A Valid ID.              *\n";
			cout << "\t\t\t\t\t*****************************************\n";
			Sleep(2000); //timer
			system("cls");
			heading();
			return manageBalance();

		}
	}
	else {
		// If invalid choice
		cout << "\t\t\t\t\t*****************************************\n";
		cout << "\t\t\t\t\t*           | Invalid Option |          *\n";
		cout << "\t\t\t\t\t*****************************************\n";
		cout << "\t\t\t\t\t* Invalid Option.                       *\n";
		cout << "\t\t\t\t\t* Please Enter A Valid Option.          *\n";
		cout << "\t\t\t\t\t*****************************************\n";
		cout << "\t\t\t\t\t* Please Enter 1 or 2.                  *\n";
		cout << "\t\t\t\t\t*****************************************\n";
		Sleep(2000); //timer
		system("cls");
		heading();
		return manageBalance();

	}
}

void menu() {
	//function to display menu
	int choice;
	do {
		system("cls");
		heading();
		cout << "\t\t\t\t\t* Choose One Of The Following Options:  *\n";
		cout << "\t\t\t\t\t*****************************************\n";
		cout << "\t\t\t\t\t* 1. New Account                        *\n";
		cout << "\t\t\t\t\t* 2. View All Accounts                  *\n";
		cout << "\t\t\t\t\t* 3. Edit Account                       *\n";
		cout << "\t\t\t\t\t* 4. Delete Account                     *\n";
		cout << "\t\t\t\t\t* 5. Manage Balance                     *\n";
		cout << "\t\t\t\t\t* 6. Exit                               *\n";
		cout << "\t\t\t\t\t*****************************************\n";
		cout << "\t\t\t\t\t";
		cin >> choice;
		system("CLS"); //clear screen



		switch (choice) {
		case 1:  // Add a new account
			heading();
			newAccount();
			Sleep(2000); //timer
			break;

		case 2: // View all accounts
			heading();
			displayAccounts();
			Sleep(2000); //timer
			break;

		case 3: // Edit an existing account
			heading();
			editAccount();
			Sleep(2000); //timer
			break;

		case 4:  // Delete an existing account
			heading();
			deleteAccount();
			Sleep(2000); //timer
			break;

		case 5:	// Manage balance
			heading();
			manageBalance();
			Sleep(2000); //timer
			break;

		case 6: // Exit the program
			heading();
			cout << "\t\t\t\t\t*           | Exit Program |            *\n";
			cout << "\t\t\t\t\t*****************************************\n";
			cout << "\t\t\t\t\t* Thank You For Using The Banking System \n";
			cout << "\t\t\t\t\t*                                       *\n";
			cout << "\t\t\t\t\t*****************************************\n";
			Sleep(2000); //timer
			break;

		default: // Handle invalid input
			heading();
			cout << "\t\t\t\t\t*           | Invalid Option |          *\n";
			cout << "\t\t\t\t\t*****************************************\n";
			cout << "\t\t\t\t\t* Please Try Again                      *\n";
			cout << "\t\t\t\t\t*****************************************\n";
			Sleep(2000); //timer
			system("cls");
		}
	} while (choice != 6);
	// Loop until the user chooses to exit
}



int main() {
	// Main function
	system("cls");
	heading();
	menu();

	return 0;
}

// This program is a simple banking management system that allows users to check their balance, deposit money, and withdraw money.
// Program execution ends here