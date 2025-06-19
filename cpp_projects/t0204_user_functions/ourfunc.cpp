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
    // TODO: Prompt the user to enter an integer, read the value into 'count',
    // and then call the simon() function with 'count' as the argument.
    // This will test your understanding of function calls and user input in C++.

    return 0;
}

// This function simon() takes an integer n as an argument and prints a message
// instructing the user to touch their toes n times.
// The function does not return any value, hence its return type is void.

// TODO: Define the simon() function here.
// The function should take an integer parameter 'n' and print a message
// telling the user to touch their toes 'n' times.
// Example output: "Simon says touch your toes 3 times."