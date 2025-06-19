#include <iostream>
using namespace std;

char *buildstr(char ch, int times);

// This program builds a string of a specified character repeated a specified number of times.
// It prompts the user for a character and an integer, then creates a dynamic string with that character repeated.
int main()
{
    int times;
    char ch;

    cout << "Enter a character: ";
    cin >> ch;
    cout << "Enter an integer: ";
    cin >> times;
    char *ps = buildstr(ch, times); // Call the function to build the string
    cout << ps << "\n";
    delete[] ps; // Free the dynamically allocated memory
    cout << "Done.\n";

    return 0;
}

// This function builds a string of a specified character repeated a specified number of times.
// It dynamically allocates memory for the string, fills it with the character, and returns a pointer to the string.
char *buildstr(char ch, int times)
{
    char *ret = new char[times + 1];
    for (int i = 0; i < times; i++)
    {
        ret[i] = ch;
    }

    return ret;
}
