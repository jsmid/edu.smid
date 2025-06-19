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
    int i = strlen(input) - 1;
    while (i >= 0)
    {
        cout << input[i];
        i--;
    }
    cout << "\n";

    // We can swap the letters in the variable directly in one loop
    cout << "Swapping letters directly in the variable:\n";
    int ii = strlen(input) - 1;
    int jj = 0;
    while (jj < ii)
    { // Stop swapping letters at the middle of the word, otherwise you'll swap it back to its original state!
        char tmp = input[ii];
        input[ii] = input[jj];
        input[jj] = tmp;
        ii--;
        jj++;
    }
    cout << input << "\n";

    return 0;
}