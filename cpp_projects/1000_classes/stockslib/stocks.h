// File: stockslib/stocks.h
// This header file defines the Stock class, which represents a stock with a company name, number of shares, share value, and total value.
#ifndef _STOCKS_H_
#define _STOCKS_H_

class Stock
{
private:
    static const int COMPANY_LEN = 30; // constant valid only within the class
    char company[COMPANY_LEN];
    int shares;
    double share_val;
    double total_val;
    void set_tot() { this->total_val = this->shares * this->share_val; }

public:
    Stock();
    Stock(const char *co, int n = 0, double pr = 0.0);
    ~Stock();
    const char *get_company() const { return company; };
    double get_total_val() const { return total_val; };
    void acquire(const char *co, int n, double pr);
    void buy(int num, double price);
    void sell(int num, double price);
    void update(double price);
    void show() const;                        // this method does not intend to modify any class attributes
    const Stock &greater(Stock &other) const; // returns the greater of the compared objects
};

#endif