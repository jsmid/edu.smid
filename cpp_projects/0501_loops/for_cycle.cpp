#include <iostream>
using namespace std;

const int arr_length = 15;

// This program calculates the factorial of numbers from 0 to 14
// and stores them in an array. It then prints the factorials of each number.
// The factorial of a number n is the product of all positive integers from 1 to n.
// For example, 5! = 5 * 4 * 3 * 2 * 1 = 120.
int main()
{
    double factorials[arr_length];
    factorials[1] = factorials[0] = 1.;
    int i;
    for (i = 2; i < arr_length; i++)
        factorials[i] = i * factorials[i - 1];
    for (i = 0; i < arr_length; i++)
        cout << i << "! = " << factorials[i] << "\n";

    return 0;
}