//
// Written by Ben Dumais for CS3307, Assignment 1
//

//Include statements
#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include "User.h"
#include "Account.h"
#include "Bank.h"

using namespace std;

//Constant strings for file names
const string USER_FILE = "users.csv";
const string ACCOUNT_FILE = "accounts.csv";
const string WRITE_FILE = "output.txt";
ofstream outfile;

//Function to check if each character of a string is a digit
bool is_dig(string s) {
	locale loc;	//Locale to use

	for (int i = 0; i < s.length(); i++) {	//Loop through each character
		if (!isdigit(s[i], loc)) {	//If its not a digit, return false
			return false;
		}
	}
	return true;	//return true

}

//Function to check if each character of a string is a character
bool is_char(string s) {
	locale loc;	//Locale to use

	for (int i = 0; i < s.length(); i++) {	//Loop through each character
		if (isdigit(s[i], loc)) {	//If its a digit, return false
			return false;
		}
	}
	return true;	//return true

}

//Method to clear cin
void clear_cin() {
	cin.clear();	//clear input
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Ignore that input
}

//Method to print execution trace to file
void write_trace(int id, string function) {

	//Time functionality borrowed from 
	time_t t = time(0);
	outfile << "TIME [" << t << "] User " << id << ", Function: " << function << "\n";

}

//Main function
int main() {

    int active_id;  //Variable for the active user's ID
	int int_input;	//Variable for numeric input
    string input;   //Variable for the user's input into the system

	bool is_valid = false;	//Looping variable to check input
	bool trace = true;		//Variable for trace -> on by default

	User active_user;		//Variable for current user

	Bank bank;			//The system object itself, which stores and handles the user and account
	bank.populate();	//Initialize with data from datafiles

	outfile.open(WRITE_FILE);	//Open output file for trace


	//Start label, used for branching
start:

	//Display welcome
	system("CLS");
	cout << "Welcome! Please select an option:\n\na) Log In\ne) Exit\n\n";
	cin >> input;	//Get input from user

	//Initialize loop to check if input was valid
	is_valid = false;
	while (!is_valid) {	//Loop until input is valid
		if (input.compare("a") == 0)
			is_valid = true;	//If login (a) was selected, break from loop
		else if (input.compare("e") == 0)
			goto logout;	//If exit (e) was selected, branch to logout
		else {		//Otherwise, reprompt user
			cout << "\nPlease select one of the options: ";
			clear_cin();
			cin >> input;	//Reprompt
		}
	}

	//Display login message
	system("CLS");
    cout << "Please enter your ID, or '0' to exit:\n " << endl;
    cin >> active_id;

	//Loop until valid input is found
	is_valid = false;
	while (!is_valid) {
		if (bank.get_user(active_id).id > 0 && !cin.fail()) //If a valid id was entered, break from loop
			is_valid = true;
		else if (active_id == 0) //If cancel was selected, branch back to main screen
			goto start;
		else { //Otherwise reprompt
			cout << "\nPlease enter a valid ID (Should not contain letters): "; //Reprompt user
			clear_cin();
			cin >> active_id;
		}
	}

	
	if (trace)//If trace is on, write to file
		write_trace(active_id, "get_user");

	//Set active user as the input id
	active_user = bank.get_user(active_id);

	//Confirm w/ pin
	cout << "\nPlease enter your PIN: ";

	is_valid = false;
	while (!is_valid) {	//Loop until we get the right PIN
		cin >> int_input;
		if (int_input == active_user.pin)	//If it matches, stop looping
			is_valid = true;
		else if (int_input == 0)	//If they want to cancel, exit
			goto start;
		else {	//If wrong pin, reprompt
			cout << "\nIncorrect PIN. Please try again or type '0' to cancel: ";
			clear_cin();
		}
	}

    //Get type, and depending on what type display options
    if (active_user.type == 1) {     //If user is a customer, show options for a customer

        while(input.compare("g") != 0){

			back_option_customer:	//Label for back option

            system("CLS");	//Clear screen and display main menu
            cout << "Account Summary for ";
			cout << active_user.name;
			cout << "\n\n";

			if (trace)//If trace is on, write to file
				write_trace(active_id, "display_accounts");

            cout << active_user.display_accounts();	//summarize user's accounts
            cout << "\na) Deposit\nb) Withdraw\nc) Transfer\nd) Request new account\ne) Request account closure\nf) Account information\ng) Log out";	//Display options
            cout << "\n\nPlease select an option\n";

            cin >> input;	//Get input

			//If user selects Deposit function, do the following
            if (input.compare("a") == 0) {

                system("CLS");          //Clear console screen
                Account* active_account; //Declare variable for active account
				active_account = &active_user.accounts[0]; //initialize to chequings account. This will change
                double amount;         //Declare variable for amount to deposit

                cout << "\nWhich account would you like to deposit to?\n";

				if (trace)	//If trace is on, write to file
					write_trace(active_id, "list_Accounts");

                cout << active_user.list_accounts();    //List current accounts belonging to customer
                cout << "\ne) Cancel\n";

				is_valid = false;
				//Make sure user has selected a valid option
				while (!is_valid) {	//Loop until we get proper input
					cout << "\nPlease select one of the options: ";
					cin >> input;
					if (input.compare("a") == 0 && active_user.accounts[0].id >= 0) {	//If input matches an option and a valid account was retrieved
						is_valid = true;	//stop looping
						active_account = &active_user.accounts[0];	//Set target account
					}
					else if (input.compare("b") == 0 && active_user.accounts[1].id >= 0) {
						is_valid = true;
						active_account = &active_user.accounts[1];
					}
					else if (input.compare("c") == 0 && active_user.accounts[2].id >= 0) {
						is_valid = true;
						active_account = &active_user.accounts[2];
					}
					else if (input.compare("e") == 0) {
						goto back_option_customer;
					}
				}


                //Get amount to deposit
                cout << "\n\nHow much would you like to deposit today? ";
                cin >> amount;

                //Check if input is valid
                while(cin.fail()){  //If input is not numeric, keep prompting for proper input

					if (trace)	//If trace is on, write to file
						write_trace(active_id, "clear_cin");

					clear_cin();
                    cout << "\nPlease enter a valid number: ";
                    cin >> amount;
                }

				if (trace)	//If trace is on, write to file
					write_trace(active_id, "deposit");

				//Add amount to balance of the desired account
				active_account->deposit(amount);// += amount;

            } //End of deposit

			//Withdraw Function
			else if (input.compare("b") == 0) {

				system("CLS");          //Clear console screen
				Account* active_account; //Declare variable for active account
				active_account = &active_user.accounts[0]; //initialize to chequings account. This will change
				double amount;         //Declare variable for amount to withdraw

				cout << "\nWhich account would you like to withdraw from?\n";

				if (trace)	//If trace is on, write to file
					write_trace(active_id, "list_Accounts");

				cout << active_user.list_accounts();    //List current accounts belonging to customer
				cout << "\ne) Cancel\n";

				is_valid = false;
				//Make sure user has selected a valid option
				while (!is_valid) {	//Loop until we get proper input
					cout << "\nPlease select one of the options: ";
					cin >> input;
					if (input.compare("a") == 0 && active_user.accounts[0].id >= 0) {	//If input matches an option and a valid account was retrieved
						is_valid = true;	//stop looping
						active_account = &active_user.accounts[0];	//Set target account
					}
					else if (input.compare("b") == 0 && active_user.accounts[1].id >= 0) {
						is_valid = true;
						active_account = &active_user.accounts[1];
					}
					else if (input.compare("c") == 0 && active_user.accounts[2].id >= 0) {
						cout << "You may not withdraw from a credit card. Please press enter to return ";
						getchar();
						getchar();
						goto back_option_customer;
					}
					else if (input.compare("e") == 0) {
						goto back_option_customer;
					}
				}


				//Get amount to deposit
				cout << "\n\nHow much would you like to withdraw? ";
				cin >> amount;

				//Check if input is valid
				while (cin.fail() || amount < 0) {  //If input is not numeric, keep prompting for proper input

					if (trace)	//If trace is on, write to file
						write_trace(active_id, "clear_cin");

					clear_cin();
					cout << "\nPlease enter a valid number: ";
					cin >> amount;
				}

				//Add amount to balance of the desired account
				if (amount > active_account->balance) {	//If amount is greater than balance, display error and return
					cout << "\nYou do not have sufficient funds. Please press enter to return ";
					getchar();
					getchar();
				}
				//If amount will take balance under 1000, ask user if they wish to proceed with $20 charge
				else if ((active_account->balance - amount) < 1000 && (active_account->balance >= (amount + 2))) {
					cout << "\nThis transaction will make your account balance below 1000. An extra charge of $2 will be applied if you continue";
					cout << "\n\na) Proceed\nb) Cancel\n\n";

					//Loop until they select an option (a or b)
					is_valid = false;
					while (!is_valid) {

						cin >> input; //Get input

						if (input.compare("a") == 0) {	//If they select a, stop looping and withdraw amount + 2
							is_valid = true;

							if (trace)	//If trace is on, write to file
								write_trace(active_id, "withdraw");

							active_account->withdraw(amount + 2);

						} //If they select b, return
						else if (input.compare("b") == 0)
							goto back_option_customer;

						//Otherwise, reprompt
						else
							cout << "\nPlease select an option: ";
					}

				}
				else { //If balance will not be under 1000 and amount is valid, withdraw normally

					if (trace)	//If trace is on, write to file
						write_trace(active_id, "withdraw");

					active_account->withdraw(amount);
				}

            }//End of Withdraw

			//Transfer Function
            else if (input.compare("c") == 0){

				system("CLS");          //Clear console screen
				Account* active_account; //Declare variable for active account
				Account* target_account; //Declare variable for target account
				double amount;         //Declare variable for amount to deposit

				active_account = &active_user.accounts[0]; //Initialize variables to start of accounts array
				target_account = &active_user.accounts[0];


				cout << "\nWhich account would you like to transfer from?\n";

				if (trace)	//If trace is on, write to file
					write_trace(active_id, "list_Accounts");

				cout << active_user.list_accounts();    //List current accounts belonging to customer
				cout << "\ne) Cancel\n";

				is_valid = false;
				//Make sure user has selected a valid option
				while (!is_valid) {
					cout << "\nPlease select an account to transfer from: ";
					cin >> input;
					if (input.compare("a") == 0 && active_user.accounts[0].id >= 0) {	//If input matches an option and a valid account was retrieved
						is_valid = true;	//Stop looping
						active_account = &active_user.accounts[0];	//Set active account to selected option
					}
					else if (input.compare("b") == 0 && active_user.accounts[1].id >= 0) {
						is_valid = true;
						active_account = &active_user.accounts[1];
					}
					else if (input.compare("c") == 0 && active_user.accounts[2].id >= 0) {
						cout << "\n\nYou cannot transfer funds from a Credit Card. Please press enter to return ";
						getchar();
						getchar();
						goto back_option_customer;
					}
					else if (input.compare("e") == 0) {
						goto back_option_customer;
					}
				}

				system("CLS");
				cout << "\nWhich account would you like to transfer to?\n\n";

				if (trace)	//If trace is on, write to file
					write_trace(active_id, "list_Accounts");

				cout << active_user.list_accounts();    //List current accounts belonging to customer
				cout << "\nd) Non-Owned account";		//List option for cross owner transfer
				cout << "\ne) Cancel\n";

				is_valid = false;
				//Make sure user has selected a valid option
				while (!is_valid) {
					cout << "\nPlease select an account to transfer to: ";
					cin >> input;
					if (input.compare("a") == 0 && active_user.accounts[0].id >= 0) {	//If input matches an option and a valid account was retrieved
						is_valid = true;	//stop looping
						target_account = &active_user.accounts[0];	//Set target account
					}
					else if (input.compare("b") == 0 && active_user.accounts[1].id >= 0) {
						is_valid = true;
						target_account = &active_user.accounts[1];
					}
					else if (input.compare("c") == 0 && active_user.accounts[2].id >= 0) {
						is_valid = true;
						target_account = &active_user.accounts[2];
					}
					else if (input.compare("d") == 0) {	//If external transfer was selected, prompt for account ID
						cout << "\n\nPlease enter the account ID you want to transfer to (or press 0 to cancel): ";
						cin >> int_input;

						if (cin.fail()) {	//If invalid input, clear and reprompt

							if (trace)	//If trace is on, write to file
								write_trace(active_id, "clear_cin");

							clear_cin();
							cout << "\nInvalid ID";
						}
						else if (int_input == 0)	//If 0, cancel
							goto back_option_customer;
						else {	//Otherwise, look for the account

							int int_input2;

							cout << "\nPlease enter your PIN to authorize this transfer: ";
							cin >> int_input2;

							if (cin.fail() || int_input2 != active_user.pin) {	//If invalid data or wrong PIN

								if (trace)	//If trace is on, write to file	
									write_trace(active_id, "clear_cin");

								clear_cin();	//Clear input
								cout << "\nIncorrect PIN. Unable to complete transaction. Press enter to return"; //Display error
								getchar();
								goto back_option_customer;	//Return
							}//If valid input and PINs matched, continue


							if (trace)	//If trace is on, write to file
								write_trace(active_id, "get_account");

							target_account = &bank.get_account(int_input); //Search

							if (target_account->id > 0)	//If returned is positive, match was found
								is_valid = true;
							else	//Otherwise none was found
								cout << "\nNo account with that ID was found, please try again";
						}


					}
					else if (input.compare("e") == 0) {
						goto back_option_customer;
					}
				}

				//Get amount to transfer
				cout << "\n\nHow much would you like to transfer? ";
				cin >> amount;

				//Check if input is valid
				while (cin.fail()) {  //If input is not numeric, keep prompting for proper input

					if (trace)	//If trace is on, write to file
						write_trace(active_id, "clear_cin");

					clear_cin();
					cout << "\nPlease enter a valid number: ";
					cin >> amount;
				}

				//Attempt Transfer

				if (trace)	//If trace is on, write to file
					write_trace(active_id, "transfer");

				if (!active_account->transfer(target_account, amount)) {
					//If a false was returned by the method, there was an error
					cout << "\nThere was an error transferring. Please ensure you have enough funds. Press enter to return ";
					getchar();
					getchar();
				}
            }//End of Transfer

			//Request new account
            else if (input.compare("d") == 0){
				system("CLS"); //Display message
				cout << "Please contact a bank manager, who will be happy to open a new account for you!";

				if (trace)	//If trace is on, write to file
					write_trace(active_id, "list_managers");

				cout << "\n\nManagers at this branch:\n" << bank.list_managers();	//List managers
				cout << "\n\nPress enter to return ";
				getchar();
				getchar();
            }//End of Request new account

			//Request account closure
            else if(input.compare("e") == 0){
				system("CLS");	//Display message and list of managers
				cout << "We're sorry to hear you would like to close an account with us. Please contact a manager for next steps.";

				if (trace)	//If trace is on, write to file
					write_trace(active_id, "list_managers");

				cout << "\n\nManagers at this branch:\n" << bank.list_managers();	//List managers
				cout << "\n\nPress enter to return ";
				getchar();
				getchar();
            }//End of Request account closure

			//Account Info
            else if(input.compare("f") == 0){

				system("CLS");

				if (trace)	//If trace is on, write to file
					write_trace(active_id, "summarize_user");

				cout << active_user.summarize();	//Call summarize user function
				cout << "\n\nPress enter to return to main screen ";
				getchar();
				getchar();

            }//End of account info

			//Log out
			else if (input.compare("g") == 0) {
				goto start;
			}

        }//End of loop until logout

    }//End of customer options

    //If current user is a Manager Display the following
    else if (active_user.type == 2){

	back_option_manager:	//Return label for back option

		system("CLS");	//Display welcome message and options
		cout << "Welcome " << active_user.name << "\n\n";
		cout << "a) View all users\nb) View all accounts\nc) View User\nd) View Account\ne) Add User\nf) Open New Account\ng) Remove User\nh) Remove an Account\ni) Compound Interest\nk) Logout";
		cout << "\n\nPlease select an option: ";

		is_valid = false;
		while (!is_valid) {	//Loop
			cin >> input;

			//View Users
			if (input.compare("a") == 0) {
				system("CLS");

				if (trace)	//If trace is on, write to file
					write_trace(active_id, "list_all_users");

				cout << bank.list_all_users();	//Call list all users function
				cout << "\n\nPress enter to return ";
				getchar();
				getchar();
				goto back_option_manager;

			}
			//View Accounts
			else if (input.compare("b") == 0) {
				system("CLS");	

				if (trace)	//If trace is on, write to file
					write_trace(active_id, "list_all_accounts");

				cout << bank.list_all_accounts();	//Call list all accounts function
				cout << "\n\nPress enter to return ";
				getchar();
				getchar();
				goto back_option_manager;

			}
			//View User
			else if (input.compare("c") == 0) {
				system("CLS");
				cout << "Please enter the ID of the user you would like to view: ";	//Prompt user for ID
				cin >> int_input;

				while (cin.fail()) {	//Loop until valid input is retrieved
					cout << "Please enter a valid id (no characters): ";

					if (trace)	//If trace is on, write to file
						write_trace(active_id, "clear_cin");

					clear_cin();
					cin >> int_input;
				}

				if (trace)	//If trace is on, write to file
					write_trace(active_id, "get_user");

				User u = bank.get_user(int_input); //Get User from list

				if (u.id < 0) {	//If a null user was returned, display error and exit
					cout << "\n\nUnable to find a user with that ID, please press enter to return ";
					getchar();
					getchar();
					goto back_option_manager;
				}
				else {
					system("CLS");	//Otherwise summarize the user

					if (trace)	//If trace is on, write to file
						write_trace(active_id, "summarize");

					cout << "\n" << u.summarize();
					cout << "\n\nPress enter to return ";
					getchar();
					getchar();
					goto back_option_manager;
				}

			}
			//View Account
			else if (input.compare("d") == 0) {

				//Display message
				system("CLS");
				cout << "Please enter the ID of the account you would like to view: ";	//Prompt for ID of account
				cin >> int_input;

				while (cin.fail()) { //Loop until valid input is retrieved
					cout << "Please enter a valid id (no characters): ";

					if (trace)	//If trace is on, write to file
						write_trace(active_id, "clear_cin");

					clear_cin();
					cin >> int_input;
				}

				if (trace)	//If trace is on, write to file
					write_trace(active_id, "get_account");

				Account a = bank.get_account(int_input);	//Get account from list

				if (a.id < 0) {	//If a null account was returned, display error and return
					cout << "\n\nUnable to find an account with that ID, press enter to return ";
					getchar();
					getchar();
					goto back_option_manager;
				}
				else {	//Else display the account summary
					system("CLS");
					cout << "\n" << a.summarize();
					cout << "\n\nPress enter to return ";
					getchar();
					getchar();
					goto back_option_manager;
				}
			}

			//Add User
			else if (input.compare("e") == 0) {

				string name;	//String to contain new user's name
				int id, pin, ssn, type;	//integers for new user data

				//Prompt for user name
				system("CLS");
				cout << "Please enter the Name of the new user (cannot contain numbers): "; \

				is_valid = false;
				while (!is_valid) {	//Loop until valid input is found
					cin >> name;	//Read in name
					if (is_char(name))		//If name has no digits, exit loop
						is_valid = true;
					else {	//else clear cin and reprompt

						if (trace)	//If trace is on, write to file
							write_trace(active_id, "clear_cin");

						clear_cin();
						cout << "\nPlease enter a valid name (no numbers): ";
					}
				}

				//Prompt for PIN
				cout << "Please enter the PIN of the new user (cannot contain characters, greater than 0, and have 4 digits): ";

				is_valid = false;
				while (!is_valid) {
					cin >> pin;
					if (pin < 10000 && pin > 999 && !cin.fail())	//If pin is 4 digits and has no characters, break from loop
						is_valid = true;
					else {

						if (trace)	//If trace is on, write to file
							write_trace(active_id, "clear_cin");

						clear_cin();
						cout << "\nPlease enter a valid PIN (no characters, greater than 0, and 4 digits): ";
					}
				}

				//Prompt for SSN
				cout << "Please enter the SSN of the new user (cannot contain characters, greater than 0, and have 9 digits): ";

				is_valid = false;
				while (!is_valid) {
					cin >> ssn;
					if (ssn < 1000000000 && ssn > 99999999 && !cin.fail())	//If ssn has 9 digits and has no characters
						is_valid = true;
					else {

						if (trace)	//If trace is on, write to file
							write_trace(active_id, "clear_cin");

						clear_cin();
						cout << "\nPlease enter a valid SSN (no characters, greater than 0, and 9 digits): ";
					}
				}

				//Prompt for type
				cout << "\n\nPlease enter type of user (1 for Customer, 2 for Manager, 3 for Maintenance): ";

				is_valid = false;
				while (!is_valid) {
					cin >> type;
					if (type == 1 || type == 2 || type == 3)	//If type matches 1 2 or 3, break from loop
						is_valid = true;
					else {

						if (trace)	//If trace is on, write to file
							write_trace(active_id, "clear_cin");

						clear_cin();
						cout << "\nPlease enter a valid type (1, 2 or 3): ";
					}
				}

				//Confirm creation of new customer
				system("CLS");
				cout << "Create new user: ";
				User u(name, bank.next_user_id, pin, ssn, type);

				if (trace)	//If trace is on, write to file
					write_trace(active_id, "summarize_user");

				cout << u.summarize() << "\n\na) Confirm\nb) Cancel\n\n";	//Summarize new user and display options

				is_valid = false;
				while (!is_valid) {
					cin >> input;
					if (input.compare("a") == 0) {	//If user confirms, add user

						if (trace)	//If trace is on, write to file
							write_trace(active_id, "add_user");

						bank.add_user(u);
						cout << "\n\nUser successfully added to system. Press enter to return";
						getchar();
						getchar();
						goto back_option_manager;	//Return
					}
					else if (input.compare("b") == 0)	//If cancel, just return
						goto back_option_manager;
					else
						cout << "\nPlease select an option (a or b): ";	//Reprompt for valid input
				}

			}
			//Add Account
			else if (input.compare("f") == 0) {

				int type, ownerId;      //Variables to store type and owner's id
				double balance;         //Variable to store current balance of this account
				float rate;             //Variable to hold the interest rate on the account

				//Prompt for owner's ID
				system("CLS");
				cout << "Please enter the id of the owner (cannot contain numbers), or enter 0 to exit: "; 

				is_valid = false;
				while (!is_valid) {	//Loop until valid input is found
					cin >> ownerId;	//Read in owner ID
					if (!cin.fail()) {	//If it has no digits, check if it is a valid ID

						if (trace)	//If trace is on, write to file
							write_trace(active_id, "get_user");

						if (bank.get_user(ownerId).id == ownerId)	//If returned ID from bank equals input ID, exit loop
							is_valid = true;
						else if(ownerId == 0)	//If input was 0, return to manager main menu
							goto back_option_manager;	//Return
						else {	//Otherwise, a valid ID was input but not found as a user
							cout << "\nUnable to find a user with that ID, please try again (or press 0 to exit): ";
						}
					}
					else {	//clear cin and reprompt if invalid input

						if (trace)	//If trace is on, write to file
							write_trace(active_id, "clear_cin");

						clear_cin();
						cout << "\n\nPlease enter a valid name (no numbers): ";
					}
				}

				if (trace)	//If trace is on, write to file
					write_trace(active_id, "get_user");

				User* u = (User *)malloc(sizeof(bank.get_user(ownerId)));
					
				u = &bank.get_user(ownerId);	//Create pointer to owner

				//Prompt for type
				cout << "\n\nPlease enter the type of account (1 for Chequings, 2 for Savings, 3 for Credit Card): ";

				is_valid = false;
				while (!is_valid) {
					cin >> type;
					if (type == 1 || type == 2 || type == 3) {	//If type matches 1 2 or 3, check if user has an account of that type already

						if (trace)	//If trace is on, write to file
							write_trace(active_id, "clear_cin");

						if (bank.get_user(ownerId).accounts[type - 1].id > 0)	//Get the id of the current account of that type from the target user
																			//If id of that account is not -1, an account of that type is assigned to that customer
							cout << "\nThis user already has that type of account. Please try a different type or press 0 to cancel";
						else
							is_valid = true;	//Otherwise user does not have this type of account and we can proceed
					}
					else if (type == 0)	//If they input 0, return to menu
						goto back_option_manager;	//Return
					else {	//if input was not 1 2 or 3, reprompt

						if (trace)	//If trace is on, write to file
							write_trace(active_id, "clear_cin");

						clear_cin();
						cout << "\n\nPlease enter a valid type (1, 2 or 3): ";
					}
				}

				//Prompt for rate
				cout << "Please enter the interest rate for this account (between 0 and 1): ";

				is_valid = false;
				while (!is_valid) {
					cin >> rate;
					if (rate < 1 && rate > 0 && !cin.fail())	//If rate is between 0 and 1, continue
						is_valid = true;
					else {

						if (trace)	//If trace is on, write to file
							write_trace(active_id, "clear_cin");

						clear_cin();
						cout << "\n\nPlease enter a valid rate (between 0 and 1): ";
					}
				}

				//Confirm creation of new customer
				system("CLS");
				cout << "Create new account: ";
				Account a(type, bank.next_account_id, ownerId, rate);

				if (trace)	//If trace is on, write to file
					write_trace(active_id, "summarize_account");

				cout << a.summarize() << "\n\na) Confirm\nb) Cancel\n\n";	//Summarize new account and display options

				is_valid = false;
				while (!is_valid) {
					cin >> input;
					if (input.compare("a") == 0) {	//If user confirms, add user

						if (trace)	//If trace is on, write to file
							write_trace(active_id, "add_account");

						bank.add_account(a, u);		//Add account to system
						//u->accounts[type - 1] = a;	//Assign account to owner
						cout << "\n\nAccount successfully added. Press enter to return";
						getchar();
						getchar();
						goto back_option_manager;	//Return
					}
					else if (input.compare("b") == 0)	//If cancel, return
						goto back_option_manager;
					else
						cout << "\nPlease select an option (a or b): ";	//Reprompt for valid input
				}	

			}

			//Remove User
			else if (input.compare("g") == 0) {

				system("CLS");	//Clear screen and prompt for ID
				cout << "Please enter the ID of the user you wish to remove: ";
				cin >> int_input;

				while (cin.fail() || int_input < 0) {	//while input is invalid, reprompt
					cout << "Please enter a valid id (no characters): ";

					if (trace)	//If trace is on, write to file
						write_trace(active_id, "clear_cin");

					clear_cin();
					cin >> int_input;
				}

				if (trace)	//If trace is on, write to file
					write_trace(active_id, "get_user");

				User u = bank.get_user(int_input);	//Search for user in database

				if (u.id < 0) {	//If an empty user was returned, display error and exit
					cout << "\n\nUnable to find a user with that ID. Press enter to return ";
					getchar();
					getchar();
					goto back_option_manager;
				}
				else {	//If one was found, do the following
					for (Account a : u.accounts) {	//Loop through each account under this user
						if (a.balance != 0 && a.id >= 0) {	//If an account has a non-zero balance, we cannot remove it
							cout << "\n\nUnable to remove this user, one or more accounts under this user has a non-zero balance. Press enter to return to menu ";						
							getchar();
							getchar();
							goto back_option_manager;
						}
					}
					//If all accounts have 0 balance, remove all accounts
					for (Account a : u.accounts) {
						if (a.id >= 0) {

							if (trace)	//If trace is on, write to file
								write_trace(active_id, "remove_account");

							bank.remove_account(a.id);
						}
					}
					
					if (trace)	//If trace is on, write to file
						write_trace(active_id, "remove_user");

					bank.remove_user(int_input);	//Remove user

					cout << "\n\nSuccessfully removed user. Press enter to return ";
					getchar();
					getchar();
					goto back_option_manager;
				}

			}
			//Remove Account
			else if (input.compare("h") == 0) {

				system("CLS");	//Clear screen and prompt for ID
				cout << "Please enter the ID of the account you wish to remove: ";
				cin >> int_input;

				while (cin.fail() || int_input < 0) {	//while input is invalid, reprompt
					cout << "Please enter a valid id (no characters): ";

					if (trace)	//If trace is on, write to file
						write_trace(active_id, "clear_cin");

					clear_cin();
					cin >> int_input;
				}

				if (trace)	//If trace is on, write to file
					write_trace(active_id, "get_account");

				Account a = bank.get_account(int_input);	//Search for account in database

				if (a.id < 0) {	//If an empty account was returned, display error and exit
					cout << "\n\nUnable to find an account with that ID. Press enter to return ";
					getchar();
					getchar();
					goto back_option_manager;
				}

				else if (a.balance != 0) {	//If the account has a non-zero balance, we cannot remove it
					cout << "\n\nUnable to remove this account as it has a non-zero balance. Press enter to return to menu ";						
					getchar();
					getchar();
					goto back_option_manager;
				}
				else{

					if (trace)	//If trace is on, write to file
						write_trace(active_id, "remove_account");

					bank.remove_account(int_input);	//Remove account from list

					if (trace)	//If trace is on, write to file
						write_trace(active_id, "get_user");

					bank.get_user(a.ownerId).accounts[a.type - 1] = Account();	//Remove account from owner

					//Display success
					cout << "\n\nSuccessfully removed account. Press enter to return ";
					getchar();
					getchar();
					goto back_option_manager;
				}

			}

			//Compound Interest
			else if (input.compare("i") == 0) {

				system("CLS");
				cout << "Updating balances...";

				if (trace)	//If trace is on, write to file
					write_trace(active_id, "compound_interest");

				bank.compound_accounts();

				cout << "\n\nDone. Press enter to return";
				getchar();
				getchar();
				goto back_option_manager;

			}

			//Logout
			else if (input.compare("k") == 0) {
				goto start;
			}
			else 
				cout << "\n\nPlease chose an option: ";
		}

    }

    //If the current user is Maintenance
    else {

	back_option_maint:

		system("CLS");
		cout << "Welcome " << active_user.name;
		cout << "\nTrace is ";
		if (trace)
			cout << "On";
		else
			cout << "Off";
		cout << "\n\na) Turn trace ON\nb) Turn trace OFF\nc) Read trace logs\ne) Logout";
		cout << "\n\nPlease select an option: ";

		is_valid = false;

		while (!is_valid) {
			cin >> input;
			if (input.compare("a") == 0) {
				if (trace) {
					cout << "\n\nTrace is already on. Press enter to return";
					getchar();
					getchar();
					goto back_option_maint;
				}
				else {
					trace = true;
					cout << "\n\nTrace is now ON. Press enter to return";
					getchar();
					getchar();
					goto back_option_maint;
				}

			}
			else if (input.compare("b") == 0) {
				if (!trace) {
					cout << "\n\nTrace is already off. Press enter to return";
					getchar();
					getchar();
					goto back_option_maint;
				}
				else {
					trace = false;
					cout << "\n\nTrace is now OFF. Press enter to return";
					getchar();
					getchar();
					goto back_option_maint;
				}

			}
			//Otherwise read a file in
			else if (input.compare("c") == 0) {

				ifstream file;	//File object
				string line;	//Line being read

				//Prompt for file name
				cout << "\n\nPLease enter the name of the log you wish to read: ";
				cin >> input;

				try {	//Try opening the file
					file.open(input);
					cout << "\n";
					while (getline(file, line))		//Loop until getline returns false (no more lines)
						cout << line << "\n";	//Print line
					file.close();
				}
				catch (ifstream::failure e) {	//Catch exceptions being thrown
					cout << "\n\nUnable to open file. Press enter to return to menu. ";	//Display error and return
					getchar();
					getchar();
					goto back_option_maint;
				}

				//Return to main menu
				cout << "\n\nPress enter to return to menu. ";
				getchar();
				getchar();
				goto back_option_maint;	//Return

			}
			else if (input.compare("e") == 0)
				goto start;
			else
				cout << "\nPlease select an option (a, b, c, or d): ";
		}

    }

logout:

	outfile.close();		//Close write to file


    //Display logout message
	system("CLS");
    cout << "Thank you for using the bank. Please press enter to exit the system\n";
    getchar();
	getchar();
    return 0;
}
