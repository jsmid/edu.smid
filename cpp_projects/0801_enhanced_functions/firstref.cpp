#include <iostream>
using namespace std;

// This program demonstrates how to use references in C++.
// It shows how a reference variable can refer to the same address as another variable, 
int main()
{
    int rats = 101;
    int &rodents = rats; // rodents and rats now refer to the same address
    int mickey = rats; // mickey has the same value as rats, but a different address

    cout << "Values: rats = " << rats << ", rodents = " << rodents << ", mickey = " << mickey << "\n";
    rats++; // increases the value at the address of &rats or &rodents
    cout << "Values: ++rats = " << rats << ", rodents = " << rodents << ", mickey = " << mickey << "\n";
    cout << "Addresses: &rats = " << &rats << ", &rodents = " << &rodents << ", &mickey = " << &mickey << "\n";

    return 0;
}