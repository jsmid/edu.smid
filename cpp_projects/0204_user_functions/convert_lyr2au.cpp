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
    cin >> lyrs;
    int aus;
    aus = ly_to_au(lyrs);
    cout << lyrs << " light years are " << aus << " astronomical units.\n";

    return 0;
}

// This function converts light years to astronomical units.
// It takes a double value representing the distance in light years and returns 
// the equivalent distance in astronomical units as an integer.
// 1 light year is approximately equal to 63240 astronomical units. 
int ly_to_au(double lyrs)
{
    return lyrs * 63240;
}