//
// Created by bendu on 2015-10-08.
//

//Includes
#include "Account.h"
#include <string>
#include <sstream>

//Namespace
using namespace std;

//Method to add an amount from the account
void Account::deposit(double d)
{
    if (type == 3)		//If account is a credit card, subtract the amount from owed balance
        balance -= d;
    else
        balance += d;	//Otherwise add balance
}

//Methods to detract an amount from the account
void Account::withdraw(double d)
{
        balance -= d;
}

//Method to move balance between two accounts
bool Account::transfer(Account* a, double d)
{
    //Check to see if account has sufficient funds
    if (d > balance)
        return false; //Throw error
	else {
		a->deposit(d);     //Add amount to target account
		this->withdraw(d);       //Remove amount from target account
	}

	return true;
}

//Method to summarize an account into a string
string Account::summarize() {

	stringstream ss;	//create string stream

	if (type == 1)	//Add type of account to string
		ss << "Chequings account ";
	if (type == 2)
		ss << "Savings account ";
	else
		ss << "Credit card ";

	//Add in rest of account information to string
	ss << id << ", Owner " << ownerId << ", balance of " << balance;

	//Return string
	return ss.str();
}