#include <iostream>
using namespace std;

enum traffic_light 
{
    green,
    yellow,
    red
};

void what_is_on(traffic_light color);

// This program defines an enumeration for traffic light colors and a function to print the current color.
int main()
{
    what_is_on(green);
    what_is_on(yellow);
    what_is_on(red);
    what_is_on(traffic_light(3)); // This will invoke the default case in the switch statement, as 3 is not defined in the enum.
    // Note: Using traffic_light(3) is not recommended as it does not correspond to any defined value in the enum.

    return 0;
}

// This function takes a traffic_light enum value and prints the corresponding color.
// It uses a switch statement to determine which color is currently on.
void what_is_on(traffic_light color)
{
    cout << "Traffic light status: ";
    switch (color)
    {
    case green:
        cout << "the green light is on\n";
        break;
    case yellow:
        cout << "the yellow light is on\n";
        break;
    case red:
        cout << "the red light is on\n";
        break;
    default:
        cout << "well, this is definitely not on!\n";
    }
}