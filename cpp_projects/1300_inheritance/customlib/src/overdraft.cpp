#include <iostream>
using namespace std;
#include <cstring>
#include "customlib/overdraft.h"

const char *Overdraft::DEF_CODE_NAME = "NULL-00"; // Default code name for the overdraft account

/// @brief  Constructor for the Overdraft class.
/// Initializes the overdraft account with a full name, code name, account number, balance, maximum loan amount, and interest rate.
/// @param s    pointer to a string representing the full name of the account holder.
/// @param cn   pointer to a string representing the code name of the overdraft account.
/// @param an   account number for the overdraft account.
/// @param bal  initial balance for the overdraft account.
/// @param ml   maximum loan amount for the overdraft account.
/// @param r    interest rate for the overdraft account.
Overdraft::Overdraft(const char *s, const char *cn, long an, double bal, double ml, double r) : BankAccount(s, an, bal)
{
    this->code_name = new char[strlen(cn) + 1];
    strcpy(this->code_name, cn);
    this->max_loan = ml;
    this->owes_bank = 0.0;
    this->rate = r;
}

/// @brief  Constructor for the Overdraft class.
/// Initializes the overdraft account with a BankAccount object and a code name, maximum loan amount, and interest rate.
/// @param ba   reference to a BankAccount object to initialize the overdraft account.
/// @param cn   pointer to a string representing the code name of the overdraft account.
/// @param ml   maximum loan amount for the overdraft account.
/// @param r    interest rate for the overdraft account.
/// This constructor allows creating an Overdraft account from an existing BankAccount object.
Overdraft::Overdraft(const BankAccount &ba, const char *cn, double ml, double r) : BankAccount(ba)
{
    this->code_name = new char[strlen(cn) + 1];
    strcpy(this->code_name, cn);
    this->max_loan = ml;
    this->owes_bank = 0.0;
    this->rate = r;
}

/// @brief  Destructor for the Overdraft class.
/// Cleans up the dynamically allocated memory for the code name.
Overdraft::~Overdraft()
{
    // Just need to free the memory of dynamic variables defined in the derived class
    // The base class destructor is called automatically
    delete[] this->code_name;
}

/// @brief  Assignment operator for the Overdraft class.
/// Assigns the values of one Overdraft object to another.
/// @param od   reference to an existing Overdraft object to assign from.
/// It checks for self-assignment, deletes the existing code name, allocates new memory, and copies the values of the base class and derived class attributes.
Overdraft &Overdraft::operator=(const Overdraft &od)
{
    if (this == &od)
        return *this;

    // The assignment operator is not inherited nor called automatically like the destructor
    BankAccount::operator=(od);
    delete[] this->code_name;
    this->code_name = new char[strlen(od.code_name) + 1];
    strcpy(this->code_name, od.code_name);
    this->max_loan = od.max_loan;
    this->owes_bank = od.owes_bank;
    this->rate = od.rate;

    return *this;
}

/// @brief  Withdraws a specified amount from the overdraft account.
/// If the amount is less than or equal to the current balance, it withdraws from the balance.
/// If the amount exceeds the balance but is within the maximum loan limit, it takes a bank loan to cover the difference.
/// If the amount exceeds the maximum loan limit, it cancels the transaction.
/// @param amt  The amount to be withdrawn from the overdraft account.
/// It checks if the requested amount can be withdrawn based on the current balance, maximum loan limit, and interest rate.
void Overdraft::withdraw(double amt)
{
    double bal = this->get_balance();
    if (amt <= bal)
    {
        BankAccount::withdraw(amt);
    }
    else if (amt <= bal + this->max_loan - this->owes_bank - (amt - bal) * this->rate)
    {
        double advance = amt - bal;
        this->owes_bank += advance * (1.0 + this->rate);
        cout << "Bank loan: " << advance << " CZK\n";
        cout << "Finance charge: " << advance * rate << " CZK\n";
        this->deposit(advance);
        BankAccount::withdraw(amt);
    }
    else
    {
        cout << "Credit limit exceeded. Transaction cancelled.\n";
    }
}

/// @brief  Displays the account details of the overdraft account.
/// It shows the full name, account number, balance, code name, maximum loan amount, and amount owed to the bank.
void Overdraft::view_account() const
{
    ios_base::fmtflags initial_state = cout.setf(ios_base::fixed, ios_base::floatfield);
    cout.setf(ios_base::showpoint);
    cout.precision(2);
    // The derived class BankAccount does not have access to private attributes of the base class.
    BankAccount::view_account(); // displays the base part
    cout << "Code: " << this->code_name << "\n";
    cout << "Maximum loan amount: " << this->max_loan << " CZK\n";
    cout << "Amount owed: " << this->owes_bank << " CZK\n";
    cout.setf(initial_state);
}