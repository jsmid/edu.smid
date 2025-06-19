#include <iostream>
using namespace std;

inline double square(double x) { return x * x; }; // Inline function to calculate the square of a number

// This program demonstrates the use of an inline function to calculate the square of a number.
// It defines an inline function that takes a double as input and returns its square.
int main()
{
    double a, b;
    double c = 13.;

    a = square(5.);
    b = square(4.5 + 7.5);
    cout << "a = " << a << ", b = " << b << "\n";
    cout << "c = " << c;
    cout << ", c squared = " << square(c++) << "\n";
    cout << "Now c = " << c << "\n";

    return 0; 
}