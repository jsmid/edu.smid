#include <iostream>
#include <cmath>
// The cmath header provides mathematical functions, including sqrt for square root calculations.
#include <iomanip>
// The iomanip header provides input/output manipulators, such as setprecision for formatting output.

using namespace std;

// This program calculates the side length of a square that can be covered by a given area in square meters.
// It prompts the user to input the area and then computes the side length using the square root function.  
int main()
{
    double cover;

    cout << "How many square meters do your sheets have?\n";
    cin >> cover;
    if (cover < 0) {
        cout << "Error: Area cannot be negative.\n";
        return 1;
    }
    double side = sqrt(cover);
    cout << "Your sheets can cover\n";
    cout << "a square with side length " << fixed << setprecision(2) << side << " meters.\n";

    return 0;
}