#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <fstream>
#include "bank.h"
#include "transaction.h"
#pragma warning(disable :4996)
using namespace std;

void introText()
{
	cout << "\n************************************\n";
	cout << "Please make your selections:\n";
	cout << "1.  Add an account\n";
	cout << "2.  Delete an account\n";
	cout << "3.  Search an account\n";
	cout << "4.  Make a withdraw\n";
	cout << "5.  Make a deposit\n";
	cout << "6.  Transfer money\n";
	cout << "7.  List all records (no order required)\n";
	cout << "8.  List all records in the increasing order of account number\n";
	cout << "9.  List all records in the increasing order of account balance\n";
	cout << "10. List all transactions (no order required)\n";
	cout << "11. Update customer Information\n";
	cout << "12. List an account information\n";
	cout << "13. Analyze an account transaction\n";
	cout << "14. Exit the program\n";
	cout << "************************************\n\n\n";
}

void addAcc(int accNum, string fname, string lname, double accBal)
{
	ifstream fin("bank.txt");

	int  count = 0, acc;
	double  bal;
	string  first_name, last_name;

	while (fin >> acc >> first_name >> last_name >> bal)
	{
		if (acc == accNum)
		{
			count++;
			ofstream temp("temp.txt");
			temp << acc << " " << first_name << " " << last_name << " " << bal;
			temp.close();
		}
	}
	fin.close();

	if (count == 0)
	{
		ofstream fout("bank.txt", ios::app);

		fout << left << setw(10) << accNum << left << setw(12) << fname << " " << left << setw(12) << lname << " " << left << setw(12) << accBal << "\n";
		cout << "\nNew Account Inserted.\n\n";

		fout.close();

		ofstream transout("transactions.txt", ios::app);

		transout << left << setw(8) << accNum << left << setw(12) << "Deposit" << left << setw(10) << accBal << left << setw(10) << transTime() << "\n";
		transout.close();

		remove("temp.txt");
	}

	//Same account number found. Print it out.
	if (count > 0)
	{
		ifstream output("temp.txt");
		string custInfo;

		while (getline(output, custInfo))
		{
			cout << "\n" << custInfo << "\n";
		}
		cout << "Same account is found. The account can't be added.\n";
		output.close();
		remove("temp.txt");
	}
}

void listAcc()
{
	ifstream fin("bank.txt");

	string custInfo;

	int i = 1, count = 0;

	cout << left << setw(10) << "A/C" << left << setw(13) << "First" << left << setw(13) << "Last" << left << setw(12) << "Balance" << "\n";
	cout << "******************************************\n";
	while (getline(fin, custInfo))
	{
		cout << custInfo << "\n";
		i++;
		count++;
	}

	if (count == 0)
	{
		cout << "Your database is empty. Press 1 to add an account.";
	}

	fin.close();
}

void searchAcc(int acc)
{
	ifstream fin("bank.txt");

	int accNum, count = 0;
	string first_name, last_name;
	double bal;

	while (fin >> accNum >> first_name >> last_name >> bal)
	{
		if (acc == accNum)
		{
			ofstream fout("temp.txt");
			fout << accNum << " " << first_name << " " << last_name << " " << bal;
			count++;
			fout.close();
		}
	}

	if (count == 0)
	{
		cout << "\nCould not find this account\n";
	}

	fin.close();

	ifstream temp("temp.txt");
	string custInfo;

	while (getline(temp, custInfo))
	{
		cout << "\n" << custInfo << "\n";
	}
	temp.close();

	remove("temp.txt");
}

void delAcc(int acc)
{
	ifstream fin("bank.txt");
	ofstream fout("temp.txt");

	int accNum, count = 0;
	string first_name, last_name;
	double bal;

	//All accounts that we do not want to delete should be copied into another file.
	while (fin >> accNum >> first_name >> last_name >> bal)
	{
		if (acc != accNum)
		{
			fout << left << setw(10) << accNum << left << setw(12) << first_name << " " << left << setw(12) << last_name << " " << left << setw(12) << bal << "\n";
		}

		else
		{
			count++;
		}
	}

	//Account could not be found.
	if (count == 0)
	{
		cout << "\nCould not find this account.\n\n";
	}

	fin.close();
	fout.close();

	//Rename temp file back to bank.txt and delete temp file. Account deleted.
	if (count > 0)
	{
		ifstream temp("temp.txt");
		string custInfo;

		temp.close();

		remove("bank.txt");
		rename("temp.txt", "bank.txt");

		cout << "\nAccount deleted.";
	}
}

void withdraw(int acc, double withdrawAmount)
{
	ifstream fin("bank.txt");
	ofstream fout("temp.txt");

	int accNum, custNum;
	double  custAccBal, bal;
	string custFirstName, custLastName, first_name, last_name;

	int count = 0;

	//If account number is found, save the each word/number from that account to a variable.
	while (fin >> accNum >> first_name >> last_name >> bal)
	{
		if (acc == accNum)
		{
			count++;
			custNum = acc;
			custFirstName = first_name;
			custLastName = last_name;
			custAccBal = bal;
		}

		//This will copy all copy all account that does not match account we want to withdraw from into temp file
		if (acc != accNum)
		{
			fout << left << setw(10) << accNum << left << setw(12) << first_name << " " << left << setw(12) << last_name << " " << left << setw(12) << bal << "\n";
		}
	}

	fin.close();
	fout.close();

	if (count > 0)
	{
		//check if account balance is greater than amount to be withdrawn
		if (withdrawAmount > custAccBal)
		{
			cout << "\nNot enough money in the account.\n\n";
		}

		//If amount to be withdrawn is equal to or less than account balance, then withdraw.
		if (withdrawAmount <= custAccBal)
		{
			custAccBal = custAccBal - withdrawAmount;

			ofstream fout("temp.txt", ios::app);

			fout << left << setw(10) << custNum << left << setw(12) << custFirstName << " " << left << setw(12) << custLastName << " " << left << setw(12) << custAccBal << "\n";
			remove("bank.txt");

			fout.close();

			rename("temp.txt", "bank.txt");

			cout << "\nMoney was successfully withdrawn.";

			ofstream transout("transactions.txt", ios::app);

			transout << left << setw(8) << custNum << left << setw(12) << "Withdraw" << left << setw(10) << withdrawAmount << left << setw(10) << transTime() << "\n";
			transout.close();
		}
	}


	if (count == 0) //Account not found.
	{
		cout << "\nThis account does not exist.\n\n";
		remove("temp.txt");
	}
}

void deposit(int acc, double depositAmount)
{
	ifstream fin("bank.txt");
	ofstream fout("temp.txt");

	int accNum, custNum;
	double  custAccBal, bal;
	string custFirstName, custLastname, first_name, last_name;

	int count = 0;

	while (fin >> accNum >> first_name >> last_name >> bal)
	{
		if (acc == accNum)
		{
			count++;
			custNum = accNum;
			custFirstName = first_name;
			custLastname = last_name;
			custAccBal = bal;
		}

		else
		{
			fout << left << setw(10) << accNum << left << setw(12) << first_name << " " << left << setw(12) << last_name << " " << left << setw(12) << bal << "\n";
		}
	}

	fin.close();
	fout.close();

	/*
	If account found, deposit should be made. This function does not test for cases where the user enters a negative number, which will
	actually deduct from the account, rather than deposit into it.
	*/
	if ((count > 0) && (depositAmount >= 0))
	{
		custAccBal = custAccBal + depositAmount;

		ofstream fout("temp.txt", ios::app);

		fout << left << setw(10) << custNum << left << setw(12) << custFirstName << " " << left << setw(12) << custLastname << " " << left << setw(12) << custAccBal << "\n";
		remove("bank.txt");

		fout.close();

		rename("temp.txt", "bank.txt");

		cout << "\nMoney was successfully deposited.";

		ofstream transout("transactions.txt", ios::app);

		transout << left << setw(8) << custNum << left << setw(12) << "Deposit" << left << setw(10) << depositAmount << left << setw(10) << transTime() << "\n";
		transout.close();
	}

	//Account not found.
	if ((count == 0) || (depositAmount < 0))
	{
		cout << "\nThis account does not exist, or you are depositing a negative amount\n\n";
		remove("temp.txt");
	}
}

void transfer(int transFromAcc, int transToAcc, double transferAmount)
{
	ifstream fin("bank.txt");

	int fromAcc, toAcc, accNum;
	double fromBal, toBal, bal;
	bool boolfromAcc = false, booltoAcc = false, boolTransBal = false;
	string fromFirstName, fromLastName, toFirstName, toLastName, first_name, last_name;

	int count = 1;

	//By default, this loop will save all accounts that are not part of the transfer process (withdraw and deposit.)
	while (fin >> accNum >> first_name >> last_name >> bal)
	{

		if ((accNum != transFromAcc) && (accNum != transToAcc))
		{
			ofstream fout("temp.txt", ios::app);

			fout << left << setw(10) << accNum << left << setw(12) << first_name << " " << left << setw(12) << last_name << " " << left << setw(12) << bal << "\n";
			
            fout.close();
		}

		//If transferring account is found on file, it's data should be stored in variables. And then return true.
		if (accNum == transFromAcc)
		{
			fromAcc = accNum;
			fromFirstName = first_name;
			fromLastName = last_name;
			fromBal = bal;

			boolfromAcc = true;

			//If Amount to be transferred is greater than the available balance, then return true. 
			if (transferAmount <= fromBal)
			{
				boolTransBal = true;
			}
		}

		//If depositing account is found on file, it's data should be stored in variables. Then return true.
		if (accNum == transToAcc)
		{
			toAcc = accNum;
			toFirstName = first_name;
			toLastName = last_name;
			toBal = bal;

			booltoAcc = true;
		}
	}
	fin.close();

	/*This will check if both withdrawing and depositing accounts both exists, and available balance in withdrawing account is greater than
	amount to be transferred. If TRUE, money is withdrawn and deposited respectively. Updated accounts are appended to temp.txt, bank.txt
	is deleted, then temp.txt is renamed to bank.txt.
	*/
	if ((boolfromAcc) && (booltoAcc) && (boolTransBal))
	{
		fromBal = fromBal - transferAmount;
		toBal = toBal + transferAmount;

		ofstream fout("temp.txt", ios::app);

		fout << left << setw(10) << fromAcc << left << setw(12) << fromFirstName << " " << left << setw(12) << fromLastName << " " << left << setw(12) << fromBal << "\n";
		fout << left << setw(10) << toAcc << left << setw(12) << toFirstName << " " << left << setw(12) << toLastName << " " << left << setw(12) << toBal << "\n";

		ofstream transout("transactions.txt", ios::app);
		string transactionTime = transTime();

		transout << left << setw(8) << fromAcc << left << setw(12) << "Withdraw" << left << setw(10) << transferAmount << left << setw(10) << transactionTime << "\n";
		transout << left << setw(8) << toAcc << left << setw(12) << "Deposit" << left << setw(10) << transferAmount << left << setw(10) << transactionTime << "\n";
		transout.close();

		remove("bank.txt");

		fout.close();

		rename("temp.txt", "bank.txt");

		cout << "\nTransfer successful. \n";
	}

	/*
	If both accounts exist, but there is insufficient account balance to withdraw from, then do not carry out transfer operation, then delete
	temp.txt. This also does not affect the bank.txt.
	*/
	if ((boolfromAcc) && (booltoAcc) && (!boolTransBal))
	{
		cout << "\nBalance in first account is less than amount you want to transfer\n";
		remove("temp.txt");
	}

	/*
	If either accounts does not exist, then do not carry out transfer operation, then delete temp.txt. This also does not affect the bank.txt.
	*/
	if ((!boolfromAcc) || (!booltoAcc))
	{
		cout << "\nEither one of the accounts does not exist";
		remove("temp.txt");
	}
}

void listTransactions()
{
	ifstream fin("transactions.txt");

	string transactions;
	int i = 1;
	int count = 0;

	while (getline(fin, transactions))
	{
		cout << i << ".  " << transactions << "\n";
		i++;
		count++;
	}
	if (count == 0)
	{
		cout << "There are no transactions. Withdraw, Deposit or Transfer Money.";
	}
	fin.close();
}

string transTime()
{
	stringstream timeString;

	time_t current_time = time(NULL);

	timeString << put_time(localtime(&current_time), "%a %d %b %Y %I:%M:%S%p");

	string myTime = timeString.str();

	return  myTime;
}

void printList(Bank * head)
{
	Bank* temp = head;

	cout << left << setw(10) << "A/C" << left << setw(12) << "First" << left << setw(12) << "Last" << left << setw(12) << "Balance" << "\n";
	cout << "******************************************\n";
	while (temp != NULL)
	{
		cout << left << setw(10) << temp->account << left << setw(12) << temp->first_name << left << setw(12) << temp->last_name << left << setw(12) << temp->balance << "\n";
		temp = temp->next;
	}
}

void freeList(Bank *& head)
{
	Bank * temp = head;
	Bank * next;

	while (temp != NULL)
	{
		next = temp->next;
		free(temp);
		temp = next;
	}
	head = NULL;
}

void orderByAcc(Bank *& head, int acc, string first_name, string last_name, double bal)
{
	Bank *data = new Bank;
	data->account = acc;
	data->first_name = first_name;
	data->last_name = last_name;
	data->balance = bal;
	data->next = NULL;

	if (head == NULL)
	{
		head = data;
	}
	else if (data->account <= head->account)
	{
		data->next = head;
		head = data;
	}
	else
	{
		Bank * t1 = head;
		Bank  * t2 = t1->next;

		while (t2 != NULL && data->account > t2->account)
		{
			t1 = t2;
			t2 = t2->next;
		}
		data->next = t2;
		t1->next = data;
	}
}

void orderByBal(Bank *& head, int acc, string first_name, string last_name, double bal)
{
	Bank *data = new Bank;
	data->account = acc;
	data->first_name = first_name;
	data->last_name = last_name;
	data->balance = bal;
	data->next = NULL;

	if (head == NULL)
	{
		head = data;
	}
	else if (data->balance <= head->balance)
	{
		data->next = head;
		head = data;
	}
	else
	{
		Bank * t1 = head;
		Bank  * t2 = t1->next;

		while (t2 != NULL && data->balance > t2->balance)
		{
			t1 = t2;
			t2 = t2->next;
		}
		data->next = t2;
		t1->next = data;
	}
}

void sortBy(Bank *& head, Bank * data, string sort)
{
	ifstream fin("bank.txt");
	int acc, count = 0; string first_name, last_name; double bal;
	while (fin >> acc >> first_name >> last_name >> bal)
	{
		count++;
		if (sort == "account")
			orderByAcc(head, acc, first_name, last_name, bal);
		else if (sort == "balance")
			orderByBal(head, acc, first_name, last_name, bal);
	}
	if (count == 0)
		cout << "Bank Database is empty.\n";
	fin.close();
}

void updateAcc(int acc)
{
	ifstream fin("bank.txt");
	ofstream fout("temp.txt");

	int accNum, aNum, count = 0;
	string fname, first_name, lname, last_name;
	double accBal, bal;

	while (fin >> accNum >> first_name >> last_name >> bal)
	{
		if (acc == accNum)
		{
			aNum = accNum;
			fname = first_name;
			lname = last_name;
			accBal = bal;
			count++;
		}
		else
		{
			fout << accNum << " " << first_name << " " << last_name << " " << bal << "\n";
		}
	}

	fin.close();
	fout.close();

	if (count == 0)
	{
		cout << "\nCould not find this account.\n\n";
	}
	else
	{
		cout << "The first name of this account holder is : " << fname << "\n";
		cout << "The last name of this account holder is : " << lname << "\n";

		string newFirstName;
		string newLastName;

		cout << "Enter new first name : ";
		cin >> newFirstName;
		cout << "Enter new last name : ";
		cin >> newLastName;

		bank_account Customer(aNum, fname, lname, accBal);

		Customer.reset_first_name(newFirstName);
		Customer.reset_last_name(newLastName);

		ofstream fout("temp.txt", ios::app);
		fout << Customer.get_id() << " " << Customer.get_first_name() << " " << Customer.get_last_name() << " " << Customer.get_balance() << "\n";
		fout.close();
		remove("bank.txt");
		rename("temp.txt", "bank.txt");
		cout << "\nThe customer name was successfully updated.\n\n";
	}
}

void accInfo(int acc)
{
	ifstream fin("bank.txt");

	int accNum, custNum = 0;
	double  custAccBal = 0, bal;
	string custFirstName, custLastname, first_name, last_name;

	int count = 0;

	while (fin >> accNum >> first_name >> last_name >> bal)
	{
		if (acc == accNum)
		{
			count++;
			custNum = accNum;
			custFirstName = first_name;
			custLastname = last_name;
			custAccBal = bal;
		}
	}

	fin.close();

	if (count > 0)
	{
		bank_account Customer(custNum, custFirstName, custLastname, custAccBal);

		cout << "\nThe account information is listed below : \n\n";
		cout << "Customer Name : " << Customer.get_first_name() << " " << Customer.get_last_name() << "\n";
		cout << "Account Balance is : " << Customer.get_balance() << "\n\n";
	}
	else //Account not found(deleted :)) in bank.txt, but there could be transactions on the account in transactions.txt
		cout << "\nAccount deleted/does not exist. But here are their transactions.\n\n";

	fin.close();

	ifstream ftrans("transactions.txt");

	string transType, weekDay, month, time;
	int dayOfTrans, year;
	double amount;

	cout << left << setw(32) << "Date & Time" << "Amount\n";
	cout << "***************************************\n";
	while (ftrans >> accNum >> transType >> amount >> weekDay >> dayOfTrans >> month >> year >> time)
	{
		if (acc == accNum)
		{
			string date_and_time = weekDay + " " + to_string(dayOfTrans) + " " + month + " " + to_string(year) + " " + time;

			transaction transaction(accNum, transType, amount, date_and_time);

			transaction.output();
		}
	}

	ftrans.close();
}

void analyze(int acc)
{
	account_analysis AA(acc);

	ifstream fin("transactions.txt");
	string transType, weekDay, month, time;
	int dayOfTrans, year, accNum, count = 0;
	double amount;

	while (fin >> accNum >> transType >> amount >> weekDay >> dayOfTrans >> month >> year >> time)
	{
		if (acc == accNum)
		{
			count++;
			string date_and_time = weekDay + " " + to_string(dayOfTrans) + " " + month + " " + to_string(year) + " " + time;
			transaction T(accNum, transType, amount, date_and_time);
			AA.insert_transaction(T);
		}
	}

	if (count != 0)
	{
		cout << "\nThe number of transactions is : " << AA.number_transactions() << "\n\n";
		cout << "The average deposit is  : $" << AA.average_deposit() << "\n";
		cout << "The maximum deposit is  : $" << AA.max_deposit() << "\n\n";
		cout << "The Average withdraw is : $" << AA.average_withdraw() << "\n";
		cout << "The maximum withdraw is : $" << AA.max_withdraw() << "\n";

	}
	else
		cout << "\nEither this account does not exist or has no transaction.\n";

	fin.close();
}
