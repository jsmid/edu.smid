#include <iostream>
using namespace std;

// This program demonstrates the use of variables, pointers, and addresses in C++.
// It initializes two variables, prints their values and addresses,
// and shows how to manipulate a variable using a pointer.
int main()
{
    int donuts = 6;
    double cups = 5.4;
    // The variables donuts and cups are initialized with values.
    cout << "value of variable donuts = " << donuts << "\n";
    cout << "value of variable cups = " << cups << "\n";
    cout << "address of variable donuts = " << unsigned(&donuts) << "\n";
    cout << "address of variable cups = " << unsigned(&cups) << "\n";

    int updates = 6;      // variable
    int *p_updates;       // pointer to variable
    p_updates = &updates; // assigns address to int pointer

    // pointer initialization with variable address
    cout << "pointer p_updates initialized with address of updates\n";
    cout << "values: updates = " << updates << ", *p_updates = " << *p_updates << "\n";
    cout << "addresses: &updates = " << &updates << ", p_updates = " << p_updates << "\n";

    // pointer dereferencing
    cout << "pointer dereferencing: *p_updates = " << *p_updates << "\n";
    *p_updates = *p_updates + 1;
    cout << "variable updates after incrementing pointer content = " << updates << "\n";

    // pointer initialization with address
    int higgens = 5;
    // The pointer p_higgens is initialized with the address of the variable higgens.
    int *p_higgens = &higgens;
    // The pointer p_higgens now points to the variable higgens.
    cout << "pointer p_higgens initialized with address of higgens\n";
    cout << "values: higgens = " << higgens << ", *p_higgens = " << *p_higgens << "\n";
    cout << "addresses: &higgens = " << &higgens << ", p_higgens = " << p_higgens << "\n";

    return 0;
}