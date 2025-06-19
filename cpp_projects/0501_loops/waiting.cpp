#include <iostream>
#include <ctime>

using namespace std;

// This program demonstrates how to create a simple delay in C++.
// It prompts the user to enter a delay in seconds and then waits for that duration
int main()
{
    cout << "Enter delay in seconds: ";
    float secs;
    cin >> secs;
    clock_t delay = secs * CLOCKS_PER_SEC; // converts to clock ticks
    cout << "start\a\n";
    clock_t start = clock();
    while (clock() - start < delay) // wait until time expires
        ;
    cout << "end \a\n";
    return 0;
}