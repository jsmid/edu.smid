// File: stocks.cpp
// This file implements the Stock class, which represents a stock with a company name, number of shares, share value, and total value.
// It provides methods to acquire stocks, buy and sell shares, update share value, and display stock information.

#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;
#include "stocks.h"

/// @brief Default constructor
Stock::Stock()
{
}

/// @brief Constructor with parameters
/// Initializes a Stock object with the company name, number of shares, and share value.
/// @param co the name of the company
/// @param n  the number of shares
/// @param pr the value of a single share
Stock::Stock(const char *co, int n, double pr)
{
    strncpy(this->company, co, COMPANY_LEN - 1);
    this->shares = n;
    this->share_val = pr;
    this->set_tot();
}

/// @brief Destructor
/// Cleans up the Stock object when it is no longer needed.
Stock::~Stock()
{
    cout << "Destroying: " << this->company << "\n";
}

/// @brief Acquires new stocks
/// @param co the name of the company
/// @param n  the number of shares
/// @param pr the value of a single share
void Stock::acquire(const char *co, int n, double pr)
{
    strncpy(this->company, co, COMPANY_LEN - 1);
    this->company[29] = '\0';
    this->shares = n;
    this->share_val = pr;
    this->set_tot();
}

/// @brief Buys shares of the stock
/// This method updates the number of shares and the share value when shares are bought.
/// @param num the number of bought shares
/// @param price the value of a single share
void Stock::buy(int num, double price)
{
    this->share_val = price;
    this->shares += num;
    this->set_tot();
}

/// @brief Sells shares from already acquired stocks
/// @param num the number of sold shares
/// @param price the value of a single share
void Stock::sell(int num, double price)
{
    this->share_val = price;
    this->shares -= num;
    this->set_tot();
}

/// @brief Updates the share value
/// This method updates the share value and recalculates the total value of the stock.
/// @param price the new price per share
void Stock::update(double price)
{
    this->share_val = price;
    this->set_tot();
}

/// @brief Displays the stock information
/// This method prints the company name, number of shares, average price per share, and total value of the stock.
void Stock::show() const
{
    cout << "Company: " << this->company << '\n'
         << " Shares: " << this->shares << '\n'
         << " Avg. price (CZK): " << this->share_val << '\n'
         << " Total (CZK): " << this->total_val << "\n";
}

/// @brief Compares two Stock objects and returns the one with the greater total value
/// This method compares the total values of two Stock objects and returns a reference to the one with the greater value.
/// @param other the other Stock object to compare with
/// @return a reference to the Stock object with the greater total value
const Stock &Stock::greater(Stock &other) const
{
    if (this->total_val < other.total_val)
    {
        return other;
    }
    else
    {
        return *this; // the 'this' pointer points to the address of the object that called this member function
                      // '*this' returns the address of this object
    }
}
