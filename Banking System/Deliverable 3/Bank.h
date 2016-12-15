//
// Created by bendu on 2015-10-10.
// Class to contain and handle data for the bank system
//

//Includes
#include "User.h"
#include "Account.h"
#include <vector>

//Namespace
using namespace std;

class Bank {

	std::vector<User> user_list;		//Storage vector for users
	std::vector<Account> account_list;	//Storage vector for accounts

public:

	//Constructor
	Bank() {}

	int next_user_id = 1000;		//Counter for next available ID for users, used to ensure no duplicates
	int next_account_id = 100;		//Count for account IDs

	//Methods to return user or account based on ID
	User get_user(int id);			//Method to get a user by ID
	Account get_account(int id);	//Method to get a user by ID

	//Methods to add accounts or users
	void add_user(User u) { user_list.push_back(u); next_user_id++; }			//Method to add a user
	void add_account(Account a, User* u) { account_list.push_back(a); u->accounts[a.type - 1] = a; next_account_id++; }	//Method to add an account
	void add_account(Account a) { account_list.push_back(a); next_account_id++; }	//Overloaded, takes only account (used in population)

	//Methods to remove users or accounts
	bool remove_user(int id);
	bool remove_account(int id);

	//Methods that return summaries of accounts or users
	string list_all_users();
	string list_managers();
	string list_all_accounts();

	void compound_accounts();	//Function to update balances based on interest
	void populate();			//Populates bank system with data

};
