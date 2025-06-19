// File: usestocks1.cpp
#include <iostream>

using namespace std;
#include "time0.h" // Include the header file for the Time class

/// @brief Conversion constructor from double
/// @param hours the number of hours as a double
Time::Time(double hours)
{
    this->hours = int(hours);
    this->minutes = int((hours - this->hours) * 60);
}

/// @brief Constructor with hours and minutes
/// @param hours the number of hours
Time::Time(int hours, int minutes)
{
    this->hours = hours;
    this->minutes = minutes;
}

/// @brief  Addition operator for Time
/// Adds two Time objects together, taking care of overflow in minutes.
/// @param t  the Time object to add to this Time object
/// @return  a new Time object representing the sum of the two Time objects
/// @details The addition operator handles the case where the sum of minutes exceeds 60, converting excess minutes into hours.
const Time Time::operator+(const Time &t) const
{
    Time ret;
    ret.hours = this->hours + t.hours + (this->minutes + t.minutes) / 60;
    ret.minutes = (this->minutes + t.minutes) % 60;

    return ret;
}

/// @brief Subtraction operator for Time
/// @param t the Time object to subtract from this Time object
/// @return a new Time object representing the difference between the two Time objects
/// @details The subtraction operator handles the case where minutes in the first Time object are less than those in the second, adjusting hours accordingly.
const Time Time::operator-(const Time &t) const
{
    Time ret;
    ret.hours = this->hours - t.hours;
    int tmp_mins = this->minutes;
    if (tmp_mins < t.minutes)
    {
        ret.hours--;
        tmp_mins += 60;
    }
    ret.minutes = tmp_mins - t.minutes;

    return ret;
}

/// @brief Multiplication operator for Time
/// @param mul the multiplier to apply to this Time object
/// @return a new Time object representing the product of this Time object and the multiplier
/// @details The multiplication operator scales the hours and minutes by the given multiplier, converting minutes to hours as necessary.
const Time Time::operator*(double mul) const
{
    Time ret;
    ret.hours = this->hours * mul + int(this->minutes * mul) / 60;
    ret.minutes = int(this->minutes * mul) % 60;

    return ret;
}

/// @brief Conversion operator to double
/// Converts the Time object to a double representing the total hours
/// @return the total hours as a double, where minutes are converted to a fraction of an hour
Time::operator double() const
{
    return double (this->hours + this->minutes / 60.);
}

/// @brief Output stream operator for Time
/// @param os the output stream to write to
/// @param t the Time object to output
/// @return the output stream after writing the Time object
ostream &operator<<(ostream &os, const Time &t)
{
    os << t.hours << " hours, " << t.minutes << " minutes.\n";
    return os;
}

/// @brief Multiplication operator for Time with double on the left
/// This operator allows for multiplying a Time object by a double, with the double on the left side.
/// @param mul the multiplier to apply to the Time object
/// @param t the Time object to multiply    
/// @return a new Time object representing the product of the Time object and the multiplier
/// @details This operator is defined as a free function to allow for the syntax `double * Time`.
const Time operator*(double mul, const Time &t)
{
    return t * mul;
}
