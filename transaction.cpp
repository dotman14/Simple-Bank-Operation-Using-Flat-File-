#include <iostream>
#include <algorithm>
#include <vector>
#include "header/transaction.h"

//initialize bankaccount and set Customer_ID to id, first_name to fname, last_name to lname, and balance to b 
bank_account::bank_account(int id, string fname, string lname, double b)
{
	Customer_ID = id;
	first_name = fname;
	last_name = lname;
	balance = b;
}

bank_account::bank_account()
{
	Customer_ID = 9999;
	first_name = "anonymous";
	last_name = "anonymous";
	balance = 0;
}

//rest first_name to s
void bank_account::reset_first_name(string s)
{
	first_name = s;
}

//reset last_name to s
void bank_account::reset_last_name(string s)
{
	last_name = s;
}

int bank_account::get_id()
{
	return Customer_ID;
}

string bank_account::get_first_name()
{
	return first_name;
}


//return last name
string bank_account::get_last_name()
{
	return last_name;
}


// return balance
double bank_account::get_balance()
{
	return balance;
}


// initialize transaction and set account_number to act, transaction_type to type, amount to a, and date_and_time to day
transaction::transaction(int act, string type, double a, string day) : account_number(act), transaction_type(type), amount(a), date_and_time(day)
{
}

transaction::transaction()
{
	account_number = 9999;
	transaction_type = "unknown";
	amount = 0;
	date_and_time = "unknown";
}

int transaction::get_account_number()
{
	return account_number;
}

string transaction::get_transaction_type()
{
	return transaction_type;
}

double transaction::get_amount()
{
	return amount;
}

string transaction::get_transaction_date()
{
	return date_and_time;
}

void transaction::output()
{
	if (transaction_type == "Deposit")
	{
		cout << date_and_time << "\t" << "+" << amount << " USD\n";
	}
	else if (transaction_type == "Withdraw")
	{
		cout << date_and_time << "\t" << "-" << amount << " USD\n";
	}
}

//constructor
account_analysis::account_analysis(int id)
{
	this->id = id;
}

//insert a transaction into the vector
void account_analysis::insert_transaction(transaction t)
{
	all_trans.push_back(t);
}

//return the number of transactions in the vector
int account_analysis::number_transactions()
{
	return all_trans.size();
}

//return the average amount of deposit
double account_analysis::average_deposit()
{
	int i = 0;
	double totalDeposit = 0;

	for (vector<transaction>::iterator Iter = all_trans.begin(); Iter != all_trans.end(); ++Iter)
	{
		if (Iter->get_transaction_type() == "Deposit")
		{
			i++;
			totalDeposit += Iter->get_amount();
		}
	}
	if (i == 0)
		return 0;
	else
		return  (totalDeposit / static_cast<double>(i));
}

//return the average amount of withdraw
double account_analysis::average_withdraw()
{
	int i = 0;
	double totalWithdraw = 0;

	for (vector<transaction>::iterator Iter = all_trans.begin(); Iter != all_trans.end(); ++Iter)
	{
		if (Iter->get_transaction_type() == "Withdraw")
		{
			i++;
			totalWithdraw += Iter->get_amount();
		}
	}
	if (i == 0)
		return 0;
	else
		return  (totalWithdraw / static_cast<double>(i));
}

//return the maximum amount of deposit
double account_analysis::max_deposit()
{
	vector<double> maxDeposit;

	for (vector<transaction>::iterator Iter = all_trans.begin(); Iter != all_trans.end(); ++Iter)
	{
		if (Iter->get_transaction_type() == "Deposit")
		{
			maxDeposit.push_back(Iter->get_amount());
		}
	}
	if (maxDeposit.empty())
		return 0;
	else
	{
		vector<double>::iterator max;
		max = max_element(maxDeposit.begin(), maxDeposit.end());
		return *max;
	}
}

//return the maximum amount of withdraw
double account_analysis::max_withdraw()
{
	vector<double> maxWithdraw;

	for (vector<transaction>::iterator Iter = all_trans.begin(); Iter != all_trans.end(); ++Iter)
	{
		if (Iter->get_transaction_type() == "Withdraw")
		{
			maxWithdraw.push_back(Iter->get_amount());
		}
	}
	if (maxWithdraw.empty())
		return 0;
	else
	{
		vector<double>::iterator max;
		max = max_element(maxWithdraw.begin(), maxWithdraw.end());
		return *max;
	}
}
