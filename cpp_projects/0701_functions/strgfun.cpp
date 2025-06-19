#include <iostream>
using namespace std;

int c_in_str(const char * str, char c);

// This program counts the occurrences of a specific character in two different strings.
// It demonstrates how to pass a string to a function and count the occurrences of a character.
int main()
{
    char mnm[15] = "minimum";
    const char * wail =  "wail"; // Pointer to a string literal

    int ms = c_in_str(mnm, 'm'); // Count occurrences of 'm' in the string "minimum"
    // Note: 'mnm' is a character array, which can be passed as a pointer to the first element.
    int as = c_in_str(wail, 'a'); // Count occurrences of 'a' in the string "wail"   

    cout << ms << " characters m in string " << mnm << "\n";
    cout << as << " characters a in string " << wail << "\n";

    return 0;
}

// This function counts the occurrences of a specific character in a string.
// It takes a pointer to a string and a character as parameters, and returns the count of occurrences.
int c_in_str(const char *str, char c)
{
    int ret = 0;
    while (*str) // end when *str is equal to '\0'
    {
        if (*str == c)
            ret ++;
        str++; // move pointer to next character
    }

    return ret;
}
