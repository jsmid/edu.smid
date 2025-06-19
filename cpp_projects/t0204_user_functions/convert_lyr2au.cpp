#include <iostream>

using namespace std;

int ly_to_au(double lyrs);

// This program converts light years to astronomical units.
// It prompts the user to input a distance in light years and then calculates   
// the equivalent distance in astronomical units (AU).
int main()
{
    double lyrs;
    cout << "Enter the distance in light years: ";
    int aus;
    // TODO: Prompt the user to enter a distance in light years and store it in the variable 'lyrs'.
    // Then, call the ly_to_au function with 'lyrs' as the argument and store the result in an integer variable named 'aus'.
    cout << lyrs << " light years are " << aus << " astronomical units.\n";

    return 0;
}

// This function converts light years to astronomical units.
// It takes a double value representing the distance in light years and returns 
// the equivalent distance in astronomical units as an integer.
// 1 light year is approximately equal to 63240 astronomical units. 

//  TODO
//  Implement the function 'ly_to_au' that takes a double value representing the distance in light years
//  and returns the equivalent distance in astronomical units as an integer.
//
//  INSTRUCTIONS:
//      1. Implement the function 'ly_to_au' that takes a double value representing the distance in light years and returns the equivalent distance in astronomical units as an integer.
//      2. Recall that 1 light year is approximately equal to 63,240 astronomical units.
//      3. Write the function definition below.
// 