#include <iostream>
using namespace std;

const int max_num = 5;
// This program reads a specified number of integers from the user,
// calculates their average, and handles invalid input gracefully.
// It uses a loop to repeatedly prompt the user for input until a valid number is entered.
// The program ensures that the input is a valid integer and does not crash if the user enters non-numeric input.
int main()
{
    int nums[5];
    cout << "enter a number:\n";

    for (int i = 0; i < max_num; i++)
    {
        cout << "number " << i + 1 << ": ";
        // if the input does not contain a number
        // - the value of nums[i] remains unchanged
        // - invalid input remains in the input buffer
        // - the error flag is set in the cin object
        // the result of calling the cin object method converted to bool is false
        while (!(cin >> nums[i]))
        {
            cin.clear(); // input is not a number, restore input
            while (cin.get() != '\n')
            {
                continue; // empty the input buffer
            }
            cout << "enter a number: ";
        }
    }

    int total = 0;
    double avg = .0;
    for (int i = 0; i < max_num; i++)
    {
        total += nums[i];
    }
    avg = total / float(max_num);
    cout << "average of entered numbers: " << avg << "\n";

    return 0;
}