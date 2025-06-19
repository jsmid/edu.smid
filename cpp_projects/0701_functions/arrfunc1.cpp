#include <iostream>
using namespace std;

int sum_desserts(int eaten_by_person[], int num_people);

// This program demonstrates how to pass an array to a function in C++.
// It calculates the total number of desserts eaten by a group of people.
int main()
{
    int tst00[] = {};
    int tst01[] = {0};
    int tst02[] = {0, 1, 2};
    cout << "total eaten: " << sum_desserts(tst00, sizeof(tst00) / sizeof(*tst00)) << " desserts\n";
    cout << "total eaten: " << sum_desserts(tst01, sizeof(tst01) / sizeof(*tst01)) << " desserts\n";
    cout << "total eaten: " << sum_desserts(tst02, sizeof(tst02) / sizeof(*tst02)) << " desserts\n";
}

// This function takes an array of integers representing the number of desserts eaten by each person,
// and the number of people, and returns the total number of desserts eaten.
int sum_desserts(int eaten_by_person[], int num_people)
{
    int result = 0;
    cout << "warning, instead of the array, only the address is passed to the function, i.e. sizeof(eaten_by_person) == " << sizeof(eaten_by_person) <<
            " is the size of the address of the first element of the array and not the size of the whole array!\n";
    for (int i = 0; i < num_people; i++)
    {
        result += eaten_by_person[i];
    }

    return result;
}