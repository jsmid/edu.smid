#include <iostream>
#include <cstring>

using namespace std;

// This program reads a word from the user and prints it in reverse order.
// It also demonstrates how to swap letters in the word directly in one loop.
int main()
{
    char input[20];
    cout << "Enter a word, no longer than twenty characters: ";
    cin >> input;
    for (int i = strlen(input) - 1; i >= 0; i--)
    {
        cout << input[i];
    }
    cout << "\n";

    // we can swap the letters in the variable directly in one loop
    cout << "swapping letters directly in the variable: \n";
    for (int i = strlen(input) - 1, j = 0; j < i; i--, j++)
    { // stop swapping letters in the middle of the word, otherwise you'll swap it back to its original state!
        char tmp = input[i];
        input[i] = input[j];
        input[j] = tmp;
    }

    cout << input << "\n";

    return 0;
}