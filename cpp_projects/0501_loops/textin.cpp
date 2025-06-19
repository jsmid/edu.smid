#include <iostream>

using namespace std;

// This program reads characters from standard input until EOF (End of File) is reached.
// It counts the number of characters read and prints them to the console.
int main()
{
    char ch;
    int count = 0;

    cin.get(ch);
    while (!cin.eof()) // test for EOF
    {
        cout << ch;
        count++;
        cin.get(ch);
    }
    cout << "\n"
         << count << " characters read\n";
    return 0;
}