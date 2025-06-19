// File: usetime.cpp
// This program demonstrates the use of the Time class defined in timelib/time0.h.
#include <iostream>

using namespace std;
#include "timelib/time0.h" // Include the header file for the Time class

int main()
{
    Time t0(0, 0);  // Create a Time object representing 0 hours and 0 minutes
    cout << "t0 == " << t0 << "\n";
    Time t1(1, 0); // Create a Time object representing 1 hour and 0 minutes
    cout << "t1 == " << t1 << "\n";
    Time t2(2, 15);     // Create a Time object representing 2 hours and 15 minutes
    cout << "t2 == " << t2 << "\n";
    Time t3(2, 30);   // Create a Time object representing 2 hours and 30 minutes
    cout << "t3 == " << t3 << "\n";

    Time p0_0 = t0 + t0;    // Add t0 to itself
    cout << "t0 + t0 == " << p0_0 << "\n";
    Time m0_0 = t0 - t0;    // Subtract t0 from itself
    cout << "t0 - t0 == " << m0_0 << "\n";
    Time n0_0 =  0 * t0;    // Multiply t0 by 0
    cout << "0 * t0 == " << n0_0 << "\n";
    Time n0_1 = t0 * 0;     // Multiply t0 by 0
    cout << "t0 * 0 == " << n0_1 << "\n";
    Time n0_2 = 1 * t0;     // Multiply t0 by 1
    cout << "1 * t0 == " << n0_2 << "\n";
    Time n0_3 = 1. * t0;    // Multiply t0 by 1.0
    cout << "1. * t0 == " << n0_3 << "\n";

    Time p1_0 = t1 + t0;   // Add t1 and t0
    cout << "t1 + t0 == " << p1_0 << "\n";
    Time m1_0 = t1 - t0;   // Subtract t0 from t1
    cout << "t1 - t0 == " << m1_0 << "\n";
    Time n1_0 = 0 * t1;   // Multiply t1 by 0
    cout << "0 * t1 == " << n1_0 << "\n";
    Time n1_1 = t1 * 0;   // Multiply t1 by 0
    cout << "t1 * 0 == " << n1_1 << "\n";
    Time n1_2 = 1 * t1;   // Multiply t1 by 1
    cout << "1 * t1 == " << n1_2 << "\n";
    Time n1_3 = 1. * t1;  // Multiply t1 by 1.0
    cout << "1. * t1 == " << n1_3 << "\n";

    Time c0 = .9;    // example of implicit conversion from double to Time
    // This will call the constructor Time(double hours) which converts .9 to 0 hours and 54 minutes
    cout << "c0 = .9 == " << c0 << "\n";

    Time c1 = 1; // example of implicit conversion from int to Time
    // This will call the constructor Time(int hours, int minutes) with 1 hour and 0 minutes
    cout << "c1 = 1 == " << c1 << "\n";

    double d_h0 = c0;  // implicit conversion from Time to double
    // This will call the conversion operator Time::operator double() which converts 0 hours and 54 minutes to 0.9
    cout << "d_h0 = c0 == " << d_h0 << "\n";

    double d_h1 = c1; // implicit conversion from Time to double
    cout << "d_h1 = c1 == " << d_h1 << "\n";

    return 0;
}