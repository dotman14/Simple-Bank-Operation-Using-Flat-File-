#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
using namespace std;

struct Bank
{
	int account;
	string first_name, last_name;
	double balance;
	Bank * next;
};

/*
introtext:
This function is void. It simply displays MENU for the application. 
When you add new functionalities to the MENU, make sure to add corresponding SWITCH statement in project3.cpp
*/
void introText();

/*
addAcc:
 This function takes 4 parameters.
 INT - Account Number.
 STRING - Account First Name.
 STRING - Account Last Name.
 INT - Opening Account Balance.
 First it checks if the account number exists in the database, if it does, new account is not added, if not, new account is added to the database.
*/
void addAcc(int, string, string, double);

/*
delAcc :
This function deletes an account from the database. It takes a single parameter.
INT - Account Number.
First it checks if the account number exists in the database, if it does, account is deleted, if not nothing happens.
*/
void delAcc(int);

/*
searchAcc :
This function looks up an account from the database. It takes a single parameter.
INT - Account Number
It prints out the Account Number, First Name, Last Name and Account Balance.
*/
void searchAcc(int);


/*
withdraw:
This function takes 2 parameters.
INT - Account Number you want to withdraw from.
DOUBLE - Amount you want to withdraw.
Amount to withdraw must be non negative number (double/int).
*/
void withdraw(int, double);

/*
deposit :
This function takes 2 parameters.
INT - Account Number you want to deposit into.
DOUBLE - Amount you want to deposit.
Amount to deposit must be a non negative number (double/int)
*/
void deposit(int, double);

/*
transfer :
This function takes 3 parameters.
INT - Account Number you want to transfer from.
INT - Account Number you want to transfer into.
DOUBLE - Amount you want to transfer.
Available deposit in the transferring account must be more than amount you want to transfer .
We also assume that amount you want to transfer is a positive number.
*/
void transfer(int, int, double);

/*
listAcc :
This function takes no parameter.
It simply list all accounts.
*/
void listAcc();

/*This function is used to call orderByAcc or orderByBal depending on what we want to sort account by. */
void sortBy(Bank *& head, Bank * data, string);

/*
orderByBal  :
This function inserts sorted nodes into a LinkedList in decreasing order of Account Balance.
*/
void orderByBal(Bank *& head, int, string, string, double);

/*
orderByBal  :
This function inserts sorted nodes into a LinkedList in decreasing order of Account Number.
*/
void orderByAcc(Bank *& head, int, string, string, double);

/*
This function deletes all the nodes in a LinkedList, including the head of the LinkedList.
This function will be called after all LinkedList has been called at least once while the program is still active.  
This was done to avoid duplicate entry into the LinkedList whenever, orderByAcc or orderByBal functions are called.  
*/
void freeList(Bank *& head);

/*
This function prints out all the nodes of a LinkeList.
*/
void printList(Bank * head);

/*
This function prints out all transaction entries in transaction.txt
*/
void listTransactions();

/*
updateAcc:
This function takes one int parameter (Account Number you want to update)
Account First Name and Last Names are updated using this function.
*/
void updateAcc(int);

/*
accInfo:
This function takes int parameter (Account Number)
It displays all transactions for the specified account.
*/
void accInfo(int);

/*
This function generates a date-time string for each transaction. Deposit and withdrawal  
*/
string transTime();

/*
This function displays the max and average withdraw and deposit for a specified account.
*/
void analyze(int acc);
