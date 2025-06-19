#include <iostream>

using namespace std;

// This program prompts the user to input the number of fleas their cat has
// and then outputs a message indicating that the number of fleas is excessive.
int main()
{
    int fleas;

    cout << "How many fleas does your cat have?\n";
    cin >> fleas;
    cout << "Well. " << fleas << " fleas is a lot!\n";

    return 0;
}