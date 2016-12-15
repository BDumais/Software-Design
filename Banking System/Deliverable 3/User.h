//
// Created by bendu on 2015-10-08.
// Class to represent a user of the bank system
//

//Includes
#include <string>
#include "Account.h"

class User {
public:
	string name; //Strings to store information about user
	int id, pin, ssn, type;           //Integers to store account data
	Account accounts[3];        //Array of accounts to represent a user's owned accounts

	//Basic Constructor
	User(string name, int id, int pin, int ssn, int type) {
		this->name = name;
		this->id = id;
		this->pin = pin;
		this->ssn = ssn;
		this->type = type;
	}
	//Default constructor
	User() { id = -1; } //Assign id of -1, which will be taken as an invalid account id

	//Other methods to display information about user
	string display_accounts();
	string list_accounts();
	string summarize();
};
