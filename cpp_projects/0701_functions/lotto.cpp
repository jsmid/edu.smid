#include <iostream>
using namespace std;

long double odds(unsigned numbers, unsigned picks);

// This program calculates the odds of winning a lottery game based on the total number of numbers on the game card
// and the number of picks made by the player. It prompts the user to enter these values and calculates the odds
int main()
{
    double total, choices;
    cout << "Enter the total number of numbers on the game card and the number of picks:\n";
    while ((cin >> total >> choices) && choices <= total)
    {
        cout << "You have a one in ";
        cout << odds(total, choices); // calculate probability
        cout << " chance of winning.\n";
        cout << "Enter two more numbers (q to quit): ";
    }
    cout << "Bye.";

    return 0;
}

// This function calculates the odds of winning a lottery game.
// It takes the total number of numbers on the game card and the number of picks as parameters,
long double odds(unsigned numbers, unsigned picks)
{
    long double result = 1.0;
    long double n;
    unsigned p;
    for (n = numbers, p = picks; p > 0; n--, p--)
        result *= n / p;

    return result;
}