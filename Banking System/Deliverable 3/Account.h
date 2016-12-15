//
// Created by bendu on 2015-10-08.
//


//Includes
#include <string>

using namespace std;

class Account {

public:

	int id, ownerId;      //Variables to store id and owner's id
	int type;               //Variable to represent type of account. 1 = chequings, 2 = savings, 3 = credit card
	double balance;         //Variable to store current balance of this account
	float rate;             //Variable to hold the interest rate on the account

	//Constructors
	Account(int type, int id, int owner, float rate) {
		this->type = type;
		this->id = id;
		this->ownerId = owner;
		this->rate = rate;
		this->balance = 0;
	}
	Account() { id = -1; }	//default constructor, creates account with id -1 which indicates a null account

	//Other methods
	void deposit(double d);	//Deposit function
	void withdraw(double d);//Withdraw function
	bool transfer(Account* a, double d); //transfer function

	string summarize(); //Method to summarize an account

};

