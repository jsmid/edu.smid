#include <iostream>
#include <cctype>

using namespace std;
// This program reads characters from standard input until EOF (End of File) is reached.
// It counts the number of alphabetic characters, whitespace characters, digits, punctuation marks, 
// and other characters, and prints the counts to the console.
// It uses functions from the cctype library to classify characters.
int main()
{
    cout << "Enter input text, finish with EOF:\n";
    char ch;
    int whitespace = 0;
    int digits = 0;
    int chars = 0;
    int punct = 0;
    int others = 0;
    while (!cin.get(ch).eof())
    {
        if (isalpha(ch)) // is it an alphabetic character?
            chars++;
        else if (isspace(ch))
            whitespace++;
        else if (isdigit(ch))
            digits++;
        else if (ispunct(ch))
            punct++;
        else
            others++;
    }

    cout << "chars == " << chars << "\n"
         << "whitespaces == " << whitespace << "\n"
         << "digits == " << digits << "\n"
         << "puncts == " << punct << "\n"
         << "other characters == " << (others == 0 ? "none" : (const char *)others) << "\n"; // ? == ternary operator

    return 0;
}