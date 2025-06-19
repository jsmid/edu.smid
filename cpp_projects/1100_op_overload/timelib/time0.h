// File: usestocks1.cpp
#ifndef _TIME0_H_
#define _TIME0_H_

class Time
{
private:
    int hours;
    int minutes;

public:
    Time() {};
    Time(double hours); 
    Time(int hours, int minutes);
    int get_hours() { return hours; };
    int get_minutes() { return minutes; };
    const Time operator+(const Time &t) const;
    const Time operator-(const Time &t) const;
    const Time operator*(double mul) const;
    friend ostream &operator<<(ostream &os, const Time &t);
    friend const Time operator*(double mul, const Time &t);
    operator double() const;
};

#endif