// File: usestocks1.cpp
#include <iostream>

using namespace std;
#include "stockslib/stocks.h" // include the header file for the Stock class

// This program demonstrates the use of the Stock class defined in stockslib/stocks.h.
int main()
{
    cout << "Stock stock1;\n";
    Stock stock1; // default constructor    
    cout << "stock1.acquire(\"NanoSamurai\", 20, 12.5);\n";
    stock1.acquire("NanoSamurai", 20, 12.5); // acquire initializes the company name, number of shares, and share value
    cout.precision(2); // set the precision for floating-point output
    cout.setf(ios_base::fixed); // set the output format to fixed-point notation
    cout.setf(ios_base::showpoint); // show decimal point even for whole numbers
    stock1.show();
    cout << "stock1.buy(15, 18.25);\n";
    stock1.buy(15, 18.25); // buy updates the number of shares and the share value  
    stock1.show();
    cout << "stock1.sell(5, 22.30);\n";
    stock1.sell(5, 22.30); // sell updates the number of shares and the share value
    stock1.show();
    cout << "stock1.update(21.5);\n";
    stock1.update(21.5); // update changes the share value and recalculates the total value
    stock1.show();

    cout << "Stock stock2 = Stock(\"World Cabbage\", 200, .2);\n";
    Stock stock2 = Stock("World Cabbage", 200, .2); // explicit constructor call
    // this is equivalent to Stock stock2("World Cabbage", 200, .2);
    stock2.show();

    cout << "Stock stock3(\"Audio Broccoli\", 10, 25.3);\n";
    Stock stock3("Audio Broccoli", 10, 25.3); // another explicit constructor call
    // this is equivalent to Stock stock3 = Stock("Audio Broccoli", 10, 25.3);
    stock3.show();

    cout << "&stock1 = " << &stock1 << ", &stock2 = " << &stock2 << "\n";
    cout << "stock2 = stock1;\n";
    stock2 = stock1;    // assignment operator, copies the values from stock1 to stock2
    cout << "&stock1 = " << &stock1 << ", &stock2 = " << &stock2 << "\n";
    stock2.show();

    cout << "const Stock stock4(\"Constant Cabbage\");\n";
    const Stock stock4("Constant Cabbage"); // calls Stock(const char *co, int n = 0, double pr = 0.0) with default values for n and pr
    stock4.show();

    Stock stocks[5] =
        {
            Stock("A", 10, 1.),
            Stock("B", 20, .7),
            Stock("C", 40, .2),
            Stock("D", 80, .1),
            Stock("E", 100, .05)
        };

    const Stock * greatest = NULL;
    // since the temporary variable is a pointer, the result of the comparison will not be stored in new memory
    // instead, only the address of the object with the highest value will be changed
    for (int i = 0; i < 5; i++) 
    {
        if (greatest == NULL)
            greatest = &stocks[i];
        else 
            greatest = &(greatest->greater(stocks[i]));

        cout << "&stocks[" << i << "] == " << &stocks[i] << "\n";
        stocks[i].show();
    }
    cout << "The best stock is " << greatest->get_company() << " at address: " << greatest << " with value of: " << greatest->get_total_val() << "\n";

    return 0;
}