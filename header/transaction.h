//do not make changes to this file

#include <string>
#include <vector>
using namespace std;

class bank_account
{
private:
	int Customer_ID;
	string first_name;
	string last_name;
	double balance;

public:
	bank_account(int, string, string, double);
	bank_account();
	void reset_first_name(string);
	void reset_last_name(string);
	int get_id();
	string get_first_name();
	string get_last_name();
	double get_balance();
};

class transaction
{
private:
	int account_number;
	string transaction_type;
	double amount;
	string date_and_time;

public:
	transaction(int, string, double, string);
	transaction();
	int get_account_number();
	string get_transaction_type();
	double get_amount();
	string get_transaction_date();
	void output();
};

class account_analysis
{
private:
	int id; //account number
	vector<transaction> all_trans;
public:
	account_analysis(int);
	void insert_transaction(transaction);
	int number_transactions();
	double average_deposit();
	double average_withdraw();
	double max_deposit();
	double max_withdraw();
};
