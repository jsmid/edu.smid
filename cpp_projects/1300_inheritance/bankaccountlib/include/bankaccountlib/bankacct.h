#ifndef _BANKACCT_H_
#define _BANKACCT_H_

class BankAccount
{
private:
    // For memory deallocation, an explicit destructor, copy constructor,
    // and assignment operator will be needed
    char *full_name;
    long account_number;
    double balance;

protected:
    static const char *DEF_FULL_NAME;

public:
    BankAccount(const char *s = DEF_FULL_NAME, long an = -1, double bal = 0.0);
    BankAccount(const BankAccount &ba);
    virtual ~BankAccount();
    BankAccount &operator=(const BankAccount &ba);
    // If we do not expect or do not want the method
    // to be overloaded in a derived class, we do not need to declare it
    // as virtual ==> static binding.
    void deposit(double amt);
    // The method must be virtual because, when casting
    // to a reference or pointer to the base class, the variable
    // would call the base class's methods ==> dynamic binding.
    virtual void withdraw(double amt);
    double get_balance() const { return this->balance; };
    // The method should be virtual. This method will
    // probably be overloaded in derived classes!
    virtual void view_account() const;
};

#endif