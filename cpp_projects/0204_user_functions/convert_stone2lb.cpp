#include <iostream>

using namespace std;

int stonetolb(int);

// This program converts a weight in stones to pounds.
// It prompts the user to input a weight in stones and then calculates  
int main()
{
    int stone;
    cout << "Enter weight in stones: ";
    cin >> stone;
    int pounds = stonetolb(stone);
    cout << stone << " stones are equal to ";
    // the equivalent weight in pounds.
    cout << pounds << " pounds.\n";

    return 0;
}

// This function takes an integer value representing the weight in stones and returns
// the equivalent weight in pounds as an integer.
// The conversion factor is 14 pounds per stone.
int stonetolb(int sts)
{
    return 14 * sts;
}