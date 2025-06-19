#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>
using std::ostream;

class Vector
{
private:
    double x;   // Value of horizontal coordinate
    double y;   // Value of vertical coordinate
    double mag; // Vector magnitude
    double ang; // Vector angle
    char mode;  // 'r' = rectangular, 'p' = polar
    // Private methods for setting values
    void set_mag();
    void set_ang();
    void set_x();
    void set_y();

public:
    Vector();
    Vector(double n1, double n2, char form = 'r');
    void set(double n1, double n2, char form = 'r');
    ~Vector();
    double get_x() { return x; }
    double get_y() { return y; }
    double get_mag() { return mag; }
    double get_ang() { return ang; }
    void set_polar_mode() { this->mode = 'p'; } // set mode to 'p' (polar)
    void set_rect_mode() { this->mode = 'r'; }  // set mode to 'r' (rectangular)
    bool is_polar_mode() const { return this->mode == 'p'; }
    bool is_rect_mode() const { return this->mode == 'r'; }
    Vector operator+(const Vector &v) const;
    Vector operator-(const Vector &v) const;
    Vector operator-() const;
    Vector operator*(double n) const;
    friend Vector operator*(double n, const Vector &v);
    friend ostream &operator<<(ostream &os, const Vector &v);
};

#endif