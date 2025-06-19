#include <iostream>
#include <cstdlib> // functions rand(), srand()
#include <ctime>   // function time()

using namespace std;
#include "vectorlib/vector.h" // include the Vector class definition

// This program simulates a random walk in a 2D space.
// The user specifies a target distance and a step length, and the program calculates the number of steps taken 
int main ()
{
    srand(time(0)); // set random number generator
    double direction;
    Vector step; // create a Vector object for the step
    Vector result(0.0, 0.0); // create a Vector object for the result, initialized to (0, 0)
    // The result Vector will accumulate the position after each step.
    unsigned long steps = 0;
    double target;
    double dstep;

    cout << "Enter target distance (q to quit): ";
    // Loop until the user enters 'q' to quit
    // The user is prompted to enter a target distance and a step length.
    while (cin >> target) 
    {
        cout << "Enter step length: ";
        if (!(cin >> dstep))
            break;

        while (result.get_mag() < target)
        {
            direction = rand() % 360;
            step.set(dstep, direction, 'p');
            result = result + step;
            steps++;
        }

        cout << "After " << steps << " steps, the subject has the following position:\n";
        cout << result << "\n";
        result.set_polar_mode(); // switch to polar mode for output
        cout << " or\n" << result << "\n";
        cout << "Average outward distance per step = " << result.get_mag()/steps << "\n";
        steps = 0;
        result.set(0.0, 0.0);   // reset the result Vector to (0, 0) for the next run
        cout << "Enter target distance (q to quit): ";
    }
    cout << "Bye!\n";
    return 0;
}
