//
// Created by bendu on 2015-10-10.
//

//Includes
#include "Bank.h"
#include <sstream>

//Method to find a user based on an id
User Bank::get_user(int id) {
	for (User u : user_list) {	//Loop through all users
		if (u.id == id)			//If current user's id matches the parameter, return that user
			return u;
	}

	return User();			//Otherwise return a blank User
}

//Method to remove a user based on an id
bool Bank::remove_user(int id) {

	vector<User>::iterator it;	//Iterator for list

	for (it = user_list.begin(); it < user_list.end(); it++) {	//Loop through elements in the array
		if (it->id == id) {	//If element at current position matches the input ID
			user_list.erase(it);	//Erase the element at the current position
			return true;	//return true
		}
	}

	return false; //If no match was found, return false
}


//Method to find and return an account based on id
Account Bank::get_account(int id) {

	for (Account a : account_list) {	//Loop through all accounts
		if (a.id == id)					//If the IDs match, return current account
			return a;
	}

	return Account();		//If not found, return a blank account
}

//Method to remove a user based on an id
bool Bank::remove_account(int id) {

	vector<Account>::iterator it;	//Iterator for list

	for (it = account_list.begin(); it < account_list.end(); it++) {	//Loop through elements in the array
		if (it->id == id) {	//If element at current position matches the input ID
			account_list.erase(it);	//Erase the element at the current position
			return true;	//return true
		}
	}

	return false; //If no match was found, return false
}


//Method to list all users in the bank database
string Bank::list_all_users() {
	stringstream ss;
	int num_accounts;

	for (User u : user_list) {	//Loop through each user
		num_accounts = 0;
		ss << u.name << ", "; //Add user name

		if (u.type == 1)	//Append type of user to string
			ss << "Customer";
		else if (u.type == 2)
			ss << "Manager";
		else
			ss << "System Maintenance";

		ss << ", ID " << u.id << ", SSN " << u.ssn;	//Summarize user info
		for (Account a : u.accounts) {	//Loop through accounts and add to num_accounts each valid account
			if (a.id >= 0)
				num_accounts++;
		}
		ss << ", " << num_accounts << " accounts\n"; //Add to string and start new line
	}

	return ss.str(); //Return the entire string

}

//Method to list all managers in the bank database
string Bank::list_managers() {
	stringstream ss;

	for (User u : user_list) {	//Loop through each user
		if (u.type == 2)
			ss << u.name << "\n";
	}

	return ss.str(); //Return the entire string

}

//Method to display all accounts in the system
string Bank::list_all_accounts() {
	stringstream ss;

	for (Account a : account_list) {	//Loop through all accounts
		if (a.type == 1)	//display type of account
			ss << "Chequings Account ";
		else if (a.type == 2)
			ss << "Savings Account ";
		else
			ss << "Credit Card ";

		//Append rest of account info to string
		ss << a.id << ", Owner " << a.ownerId << ", Rate " << a.rate << ", Balance " << a.balance << "\n";
	}

	return ss.str(); //return the string
}

//Method to compound interest in all accounts
void Bank::compound_accounts() {

	vector<Account>::iterator it;	//Initialize iterator

	for (it = account_list.begin(); it < account_list.end(); it++)	//Loop through array
		it->balance *= (1 + it->rate);	//Multiply balance of each account by 1 + rate

}


//Populate bank with users + accounts
void Bank::populate() {

	/*
	// After wrestling with serialization and reading from csv files, I found it was better to populate data
	// Manually. This unfortunately means that data is not persistant
	*/

	//Create Managers
	User u1("Frank", 1000, 1234, 111222333, 2);
	User u2("Jess", 1001, 4321, 111222334, 2);
	User u3("Dave", 1002, 1111, 111222335, 2);

	//Create Customers
	User u4("Sue", 1003, 2222, 111222333, 1);
	User u5("Lisa", 1004, 3333, 111222334, 1);
	User u6("Cameron", 1005, 4444, 111222335, 1);
	User u7("Steve", 1006, 5555, 111222333, 1);
	User u8("Jason", 1007, 6666, 111222334, 1);
	User u9("Linda", 1008, 7777, 111222335, 1);

	//Create System Maintenance
	User u10("Mike", 1009, 1212, 321654987, 3);


	//Create Chequings accounts for all customers
	Account a1(1, 1000, 1003, 0.05);
	Account a2(1, 1001, 1004, 0.05);
	Account a3(1, 1002, 1005, 0.05);
	Account a4(1, 1003, 1006, 0.05);
	Account a5(1, 1004, 1007, 0.05);
	Account a6(1, 1005, 1008, 0.05);

	//Create Savings accounts
	Account a7(2, 1006, 1004, 0.1);
	Account a8(2, 1007, 1006, 0.1);
	Account a9(2, 1008, 1008, 0.1);

	//Create Credit Card accounts
	Account a10(3, 1009, 1003, 0.05);
	Account a11(3, 1010, 1004, 0.05);
	Account a12(3, 1011, 1005, 0.05);

	//Set balance for first customer (Sue) for testing purposes
	a1.balance = 1200;
	a7.balance = 10000;
	a10.balance = 250;

	//Assign accounts to owners
	u4.accounts[0] = a1;
	u5.accounts[0] = a2;
	u6.accounts[0] = a3;
	u7.accounts[0] = a4;
	u8.accounts[0] = a5;
	u9.accounts[0] = a6;

	u4.accounts[1] = a7;
	u6.accounts[1] = a8;
	u8.accounts[1] = a9;

	u4.accounts[2] = a10;
	u5.accounts[2] = a11;
	u6.accounts[2] = a12;

	//Add accounts to list
	add_account(a1);
	add_account(a2);
	add_account(a3);
	add_account(a4);
	add_account(a5);
	add_account(a6);
	add_account(a7);
	add_account(a8);
	add_account(a9);
	add_account(a10);
	add_account(a11);
	add_account(a12);

	//Add users to list
	add_user(u1);
	add_user(u2);
	add_user(u3);
	add_user(u4);
	add_user(u5);
	add_user(u6);
	add_user(u7);
	add_user(u8);
	add_user(u9);
	add_user(u10);
	
}