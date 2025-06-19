#include <cstdlib>

using namespace std;
#include "simlib/customer.h"

/// @brief Sets the arrival time and processing time for the customer.
/// The processing time is randomly set to a value between 1 and 3.
/// @param when The time when the customer arrives.
/// This function simulates the arrival of a customer at a random processing time.
void Customer::set(long when)
{
    processTime = rand() % 3 + 1;
    arrive = when;
}