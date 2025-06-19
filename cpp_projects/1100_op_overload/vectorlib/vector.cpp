// File: vector.cpp
// This file implements the Vector class, which represents a vector in either rectangular or polar coordinates.
#include <iostream>
#include <cmath>
using namespace std;

#include "vector.h" // Include the header file for the Vector class
const double Rad_to_deg = 57.2957795130823; // Conversion factor from radians to degrees

/// @brief calculates magnitude from x, y components
void Vector::set_mag()
{
    this->mag = sqrt(this->x * this->x + this->y * this->y);
}

/// @brief calculates angle from x, y components
/// The angle is calculated using the atan2 function, which takes into account the signs of both x and y to determine the correct quadrant.
void Vector::set_ang()
{
    if (this->x == 0.0 && this->y == 0.0)
        this->ang = 0.0;
    else
        this->ang = atan2(this->y, this->x);
}

/// @brief sets x from polar coordinates
/// The x component is calculated as the magnitude multiplied by the cosine of the angle.
void Vector::set_x()
{ 
    this->x = this->mag * cos(this->ang);
}

/// @brief sets y from polar coordinates
/// The y component is calculated as the magnitude multiplied by the sine of the angle.
void Vector::set_y()
{
    this->y = this->mag * sin(this->ang);
}

/// @brief Default constructor
/// Initializes the vector to zero in rectangular coordinates and sets the mode to 'r' (rectangular).
Vector::Vector()
{
    this->x = this->y = this->mag = this->ang = 0.0;
    this->mode = 'r';
}

/// @brief  Constructor with parameters
/// Initializes the vector with given values in either rectangular or polar coordinates based on the specified mode.        
/// @param n1 parameter for the first coordinate (x or magnitude)
/// @param n2 parameter for the second coordinate (y or angle)
/// @param form parameter to specify the coordinate system ('r' for rectangular, 'p' for polar)
/// If the form is invalid, it defaults to 'r' (rectangular) and prints a warning message.
Vector::Vector(double n1, double n2, char form)
{
    this->set(n1, n2, form);
}

/// @brief Sets the vector's coordinates based on the specified mode
/// @param n1 parameter for the first coordinate (x or magnitude)
/// @param n2 parameter for the second coordinate (y or angle)
/// @param form parameter to specify the coordinate system ('r' for rectangular, 'p' for polar)
void Vector::set(double n1, double n2, char form)
{
    if (form != 'r' && form != 'p') {
        cout << "Invalid Vector mode: " << form << ". Vector object will be set to 'r' mode.\n";
        this->mode = 'r';
    } else {
        this->mode = form;
    }

    if (this->is_rect_mode()) 
    {
        this->x = n1;
        this->y = n2;
        this->set_mag();
        this->set_ang();
    }
    else if (this->is_polar_mode())
    {
        this->mag = n1;
        this->ang = n2 / Rad_to_deg;
        this->set_x();
        this->set_y();
    }
}

/// @brief Destructor
/// Cleans up the Vector object when it is no longer needed.
Vector::~Vector()
{
}

/// @brief      Addition operator for Vector
/// @param v    the Vector object to add to this Vector object
/// This operator adds the corresponding x and y components of two vectors and returns a new Vector object.
/// @return     a new Vector object representing the sum of the two vectors
/// @details    The addition operator works in rectangular coordinates, adding the x components and y components separately.
Vector Vector::operator+(const Vector &v) const
{
    return Vector(this->x + v.x, this->y + v.y);
}

/// @brief      Subtraction operator for Vector
/// @param v    the Vector object to subtract from this Vector object   
/// This operator subtracts the corresponding x and y components of two vectors and returns a new Vector object.
/// @return     a new Vector object representing the difference between the two vectors
Vector Vector::operator-(const Vector &v) const
{
    return Vector(this->x - v.x, this->y - v.y);
}

/// @brief      Negation operator for Vector
/// This operator negates the x and y components of the vector and returns a new Vector object.     
/// @return     a new Vector object representing the negation of this vector
/// @details    The negation operator simply multiplies both components by -1, effectively reversing the direction of the vector.
Vector Vector::operator-() const
{
    return Vector(-this->x, -this->y);
}

/// @brief      Multiplication operator for Vector
/// @param n    the scalar value to multiply the vector by
/// This operator multiplies both the x and y components of the vector by a scalar value and returns a new Vector object.
/// @return     a new Vector object representing the scaled vector
Vector Vector::operator*(double n) const
{
    return Vector(n * this->x, n * this->y);
}

/// @brief      Multiplication operator for Vector
/// @param n    the scalar value to multiply the vector by
/// @param v    the Vector object to multiply by the scalar
/// This operator allows for scalar multiplication of a vector, where the scalar is on the left side of the multiplication.
Vector operator*(double n, const Vector &v)
{
    return v * n;
}

/// @brief      Output stream operator for Vector
/// @param os   the output stream to write to
/// @param v    the Vector object to output
/// This operator formats the output of the Vector object based on its mode (rectangular or polar) and writes it to the output stream.
/// @return     the output stream after writing the Vector object
ostream &operator<<(ostream &os, const Vector &v)
{
    if (v.is_rect_mode())
        os << "(x,y) = (" << v.x << ", " << v.y << ")";
    else if (v.is_polar_mode())
    {
        os << "(m, a) = (" << v.mag << ", " << v.ang * Rad_to_deg << ")";
    } else {
        os << "Invalid Vector mode";
    }

    return os;
}
