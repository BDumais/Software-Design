//
// Created by bendu on 2015-10-08.
//

//Includes
#include "User.h"
#include <string>
#include <sstream>

using namespace std;

//Method to display accounts held by a user
string User::display_accounts(){
	stringstream ss; //Create a stringstream object

	if (accounts[0].id >= 0)	//If a valid account is found in the array, create a string for it
		ss << "Chequings account " << accounts[0].id << ", Balance: " << accounts[0].balance << "\n";
	if (accounts[1].id >= 0)
		ss << "Savings account " << accounts[1].id << ", Balance: " << accounts[1].balance << "\n";
	if (accounts[2].id >= 0)
		ss << "Credit Card number " << accounts[2].id << ", Balance " << accounts[2].balance << "\n";

	return ss.str(); //Return the string
}

//Method to list account as selectable options
string User::list_accounts() {
	stringstream ss;	//Create stringstream objet

	if (accounts[0].id >= 0)	//Check each account in the array to see if it exists
		ss << "a) Chequings account " << accounts[0].id << ", Balance: " << accounts[0].balance << "\n"; //If it does, add it to the list of options
	if (accounts[1].id >= 0)
		ss << "b) Savings account " << accounts[1].id << ", Balance: " << accounts[1].balance << "\n";
	if (accounts[2].id >= 0)
		ss << "c) Credit Card number " << accounts[2].id << ", Balance " << accounts[2].balance << "\n";

	return ss.str(); //Return the string

}

//Method to summarize a user into a string
string User::summarize() {

	stringstream ss;	//Create string stream

	ss << name << " , id " << id << ", SSN " << ssn;	//Add in ID and SSN

	if (type == 1)	//Add type of user
		ss << ", Customer";
	else if (type == 2)
		ss << ", Manager";
	else
		ss << ", System Maintenance";

	ss << "\n\n" << display_accounts();	//Display accounts

	return ss.str(); //return string

}