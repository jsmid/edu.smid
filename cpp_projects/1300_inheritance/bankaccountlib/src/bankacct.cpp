#include <iostream>
#include <cstring>
using namespace std;
#include "bankaccountlib/bankacct.h"

const char *BankAccount::DEF_FULL_NAME = "Nullbody"; // Default full name for the bank account

/// @brief  Constructor for the BankAccount class.
/// Initializes the bank account with a full name, account number, and balance.
/// @param s    pointer to a string representing the full name of the account holder.
/// @param an   account number for the bank account.
/// @param bal  initial balance for the bank account.
/// If no parameters are provided, it uses default values.
BankAccount::BankAccount(const char *s, long an, double bal)
{
    this->full_name = new char[strlen(s) + 1];
    strcpy(this->full_name, s);
    this->account_number = an;
    this->balance = bal;
}

/// @brief  Copy constructor for the BankAccount class.
/// Initializes a new BankAccount object as a copy of an existing one.  
/// @param ba   reference to an existing BankAccount object to copy from.
/// It allocates new memory for the full name and copies the values of account number and balance.
BankAccount::BankAccount(const BankAccount &ba)
{
    char *s = ba.full_name;
    this->full_name = new char[strlen(s) + 1];
    strcpy(this->full_name, s);
    this->account_number = ba.account_number;
    this->balance = ba.balance;
}

/// @brief  Destructor for the BankAccount class.
/// Cleans up the dynamically allocated memory for the full name.
BankAccount::~BankAccount()
{
    delete[] this->full_name;
}

/// @brief  Assignment operator for the BankAccount class.
/// Assigns the values of one BankAccount object to another.
/// @param ba   reference to an existing BankAccount object to assign from.
/// It checks for self-assignment, deletes the existing full name, allocates new memory, and copies the values of account number and balance.
/// @return A reference to the current BankAccount object after assignment.
BankAccount &BankAccount::operator=(const BankAccount &ba)
{
    if (this == &ba)
        return *this;

    char *s = ba.full_name;
    delete[] this->full_name;
    this->full_name = new char[strlen(s) + 1];
    strcpy(this->full_name, s);
    this->account_number = ba.account_number;
    this->balance = ba.balance;
    return *this;
}

/// @brief  Deposits a specified amount into the bank account.
/// @param amt  The amount to be deposited into the account.
/// It adds the specified amount to the current balance of the account.
/// No return value.
void BankAccount::deposit(double amt)
{
    this->balance += amt;
}

/// @brief  Withdraws a specified amount from the bank account.
/// @param amt  The amount to be withdrawn from the account.
/// If the requested amount is less than or equal to the current balance, it deducts the amount from the balance.
/// If the requested amount exceeds the balance, it prints an error message and cancels the withdrawal.
void BankAccount::withdraw(double amt)
{
    if (amt <= this->balance)
    {
        this->balance -= amt;
    }
    else
    {
        cout << "Requested amount " << amt
             << " CZK exceeds the balance.\n"
             << "Withdrawal cancelled.\n";
    }
}

/// @brief  Displays the account details including full name, account number, and balance.
/// It formats the output to show the balance with two decimal places.
void BankAccount::view_account() const
{
    ios_base::fmtflags initial_state = cout.setf(ios_base::fixed, ios_base::floatfield);
    // sets ###.## format
    cout.setf(ios_base::showpoint);
    cout.precision(2);
    cout << "Client: " << this->full_name << endl;
    cout << "Account number: " << this->account_number << endl;
    cout << "Balance: " << this->get_balance() << endl;
    cout.setf(initial_state); // restores original format
}
