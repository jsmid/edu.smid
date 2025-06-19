#include <iostream>
using namespace std;

struct travel_time
{
    int hours;
    int minutes;
};

travel_time sum(travel_time t1, travel_time t2);
travel_time *sum2(const travel_time *t1, const travel_time *t2);
void show_time(travel_time tm);

// This program demonstrates how to pass structures by value and by pointer in C++.
// It defines a structure for travel time and provides functions to sum two travel times and display the result.
int main()
{
    travel_time t1 = {5, 20};
    travel_time t2 = {6, 0};
    travel_time res1 = sum(t1, t2);
    travel_time *res2 = sum2(&t1, &t2);
    cout << "Travel time passed by value:\n";
    show_time(res1); // Show the result of summing by value
    cout << "Travel time passed by pointer:\n";
    show_time(*res2);   // Show the result of summing by pointer

    delete res2;
}

// This function sums two travel_time structures passed by value.
// It adds the hours and minutes, adjusting for overflow of minutes into hours.
travel_time sum(travel_time t1, travel_time t2)
{
    travel_time ret;
    ret.hours = t1.hours + t2.hours + (t1.minutes + t2.minutes) / 60;
    ret.minutes = (t1.minutes + t2.minutes) % 60;

    return ret;
}

// This function sums two travel_time structures passed by pointer.
// It allocates a new travel_time structure and returns a pointer to it.
travel_time *sum2(const travel_time *t1, const travel_time *t2)
{
    travel_time *ret = new travel_time;
    ret->hours = t1->hours + t2->hours + (t1->minutes + t2->minutes) / 60;
    ret->minutes = (t1->minutes + t2->minutes) % 60;

    return ret;
}

// This function displays the travel_time structure.
// It takes a travel_time structure by value and prints the hours and minutes.
void show_time(travel_time tm)
{
    cout << "Travel time passed by value: " << tm.hours << " hours " << tm.minutes << " minutes\n";
}
