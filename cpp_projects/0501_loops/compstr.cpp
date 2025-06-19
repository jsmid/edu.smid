#include <iostream>
#include <cstring>

using namespace std;

// This program demonstrates a simple brute-force search for a word that matches a given pattern.
// It starts with a word containing a wildcard character and iterates through the alphabet
// to find a word that matches the pattern. The search continues until the word matches a predefined target word.
// The program uses a loop to change the first character of the word and checks if it matches the target word.  
int main()
{
    char word[] = "?ate";
    // the condition can be anything
    for (char ch = 'a'; strcmp(word, "mate"); ch++)
    {
        cout << word << "\n";
        word[0] = ch;
    }
    cout << "found: " << word << "\n";

    return 0;
}