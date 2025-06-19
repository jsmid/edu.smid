#include <iostream>
using namespace std;

void estimate(int code, double (*f)(int));
double betsy(int code);
double pam(int code);

// This program estimates the time required to write a certain number of lines of code
// using two different estimation functions: betsy and pam.
int main()
{
    int code;
    cout << "How many lines of program code do you need? ";
    cin >> code;
    cout << "Here is Betsy's estimate:\n";
    estimate(code, betsy);
    cout << "Here is Pam's estimate:\n";
    estimate(code, pam);

    return 0;
}

// This function takes a number of lines of code and a pointer to a function that estimates time,
// and prints the estimated time in hours.
void estimate(int code, double (*f)(int))
{
    cout << code << " lines will take " << (*f)(code) << " hours.\n";
}

// These are two different estimation functions that calculate the time required to write code.
// Betsy's function estimates time as 0.5 hours per line of code,
double betsy(int code)
{
    return 0.5 * code;
}

// Pam's function estimates time as 0.3 hours per line of code plus a small quadratic term.
// This reflects a more complex estimation model that accounts for additional overhead.
double pam(int code)
{
    return 0.3 * code + .0004 * code * code;
}
