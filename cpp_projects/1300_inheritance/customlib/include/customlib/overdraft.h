#ifndef _OVERDRAFT_H_
#define _OVERDRAFT_H_

#include "bankaccountlib/bankacct.h"

class Overdraft : public BankAccount
{
private:
    char *code_name;
    double max_loan;
    double rate;
    double owes_bank;

protected:
    static const char *DEF_CODE_NAME;

public:
    Overdraft(const char *s = DEF_FULL_NAME, const char *cn = DEF_CODE_NAME, long an = -1,
              double bal = 0.0, double ml = 500, double r = 0.1);
    Overdraft(const BankAccount &ba, const char *cn = DEF_CODE_NAME, double ml = 500, double r = 0.1);
    virtual ~Overdraft();
    Overdraft & operator=(const Overdraft & od);
    virtual void withdraw(double amt);
    virtual void view_account() const;
    void reset_max(double m) { this->max_loan = m; };
    void reset_rate(double r) { this->rate = r; };
    void reset_owes() { this->owes_bank = 0; };
};

#endif