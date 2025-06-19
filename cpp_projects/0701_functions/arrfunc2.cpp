#include <iostream>
using namespace std;

int sum(const int (*arr)[4], int rows);

// This program demonstrates how to pass a 2D array to a function in C++.
// It calculates the sum of all elements in a 2D array of integers.
int main()
{
    int data[3][4] = {{1, 2, 3, 4}, {9, 8, 7, 6}, {4, 5, 6, 7}};
    int total = sum(data, 3);
    cout << "Total: " << total << "\n";

    return 0;
}

// This function takes a pointer to a 2D array and the number of rows,
// and calculates the sum of all elements in the array.
int sum(const int (*arr)[4], int rows)
{
    int ret = 0;
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            ret += arr[row][col];
        }
    }
    return ret;
}
