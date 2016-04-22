/*
	Assumptions
	===========
	This programs assumes the following:

	a. Initial balance alloted during account creation is a non-negative number (integer/double)
	b. Value of deposited, withdrawn and transferred amounts are non negative numbers.
	c. All primitive data types are valid within their scope.
	d. Account Numbers are positive integers
	e. First Name and Last Names are a single word each.
	f. Code written in Visual Studio 2013.
	g. Error warning 4996 was suppressed using : #pragma warning(disable :4996)

*/


#include <iostream>
#include <string>
#include <fstream>
#include "header/bank.h"
using namespace std;


int main()
{
	Bank * head = NULL;
	Bank * temp = new Bank;
	bool exit = false;

	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	while (exit == false)
	{
		introText();

		int response, acc;
		double bal, withdrawAmount, depositAmount;
		string first_name, last_name, sort;

		cout << "Your selection" << "  ";
		cin >> response;
		cout << "\n";

		switch (response)
		{

			case 1:
				cout << "Enter account number : ";
				cin >> acc;

				cout << "Enter first name : ";
				cin >> first_name;

				cout << "Enter last name : ";
				cin >> last_name;

				cout << "Enter account balance : ";
				cin >> bal;
				addAcc(acc, first_name, last_name, bal);
				break;

			case 2:
				cout << "Enter account number you wish to delete : ";
				cin >> acc;
				delAcc(acc);
				break;

			case 3:
				cout << "Enter account number you are looking for : ";
				cin >> acc;
				searchAcc(acc);
				break;

			case 4:
				cout << "Enter account number you want to withdraw from ";
				cin >> acc;

				cout << "Enter amount you want to withdraw ";
				cin >> withdrawAmount;

				withdraw(acc, withdrawAmount);
				break;

			case 5:
				cout << "Enter account number you want to deposit into ";
				cin >> acc;

				cout << "Enter amount you want to deposit ";
				cin >> depositAmount;
				deposit(acc, depositAmount);
				break;

			case 6:
				int transFromAcc, transToAcc;
				double transferAmount;
				cout << "Enter account you want to transfer from ";
				cin >> transFromAcc;

				cout << "Enter account you want to transfer in ";
				cin >> transToAcc;

				cout << "Enter amount you want to transfer ";
				cin >> transferAmount;

				transfer(transFromAcc, transToAcc, transferAmount);
				break;

			case 7:
				listAcc();
				break;

			case 8:
				sort = "account";
				sortBy(head, temp, sort);
				printList(head);
				freeList(head);
				break;

			case 9:
				sort = "balance";
				sortBy(head, temp, sort);
				printList(head);
				freeList(head);
				break;

			case 10:
				listTransactions();
				break;

			case 11:
				cout << "Enter account number to Update: ";
				cin >> acc;
				updateAcc(acc);
				break;

			case 12:
				cout << "Enter account number : ";
				cin >> acc;
				accInfo(acc);
				break;

			case 13:
				cout << "Enter account number you want to analyze : ";
				cin >> acc;
				 analyze(acc);
				break;

			case 14:
				exit = true;
				break;

			default:
				cout << "Wrong selection. Response must be between 1 and 14\n\n";
		}
	}
	return 0;
}
