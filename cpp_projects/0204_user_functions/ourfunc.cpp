#include <iostream>

using namespace std;

// The function prototype is declared before main() to inform the compiler about its existence.
void simon(int); 

// This program prompts the user to input an integer and then calls the simon() function
// to print a message instructing the user to touch their toes that many times.
int main()
{
    cout << "Enter an integer: ";
    int count;
    cin >> count;
    simon(count);

    return 0;
}

// This function simon() takes an integer n as an argument and prints a message
// instructing the user to touch their toes n times.
// The function does not return any value, hence its return type is void.
void simon(int n)
{
    cout << "Simon says touch your toes " << n << " times.\n";
}