#include <iostream>
using namespace std;

int fill_array(double ar[], int limit);
void apply_coefficient(double coef, double ar[], int limit);
void apply_coefficient_in_range(double coef, double *begin, double *end);
void show_array(const double ar[], int limit);

// This program demonstrates how to pass an array to a function in C++.
// It fills an array with user input, applies a coefficient to all elements,
int main()
{
    int const arr_limit = 5;
    double ar[arr_limit] = {0}; // initialize the array to zero to avoid garbage values
    cout << "This program fills an array with user input, applies a coefficient to all elements, and modifies a range of elements by a different coefficient.\n";
    int arr_size = fill_array(ar, arr_limit);
    show_array(ar, arr_size);
    apply_coefficient(.5, ar, arr_size);
    cout << "modified by coefficient 0.5:\n";
    show_array(ar, arr_size);
    cout << "the second and third item are modified by new coefficient 2.: \n";
    apply_coefficient_in_range(2., &ar[1], &ar[3]);
    show_array(ar, arr_size);
}

// This function displays the contents of an array up to a specified limit.
// It does not modify the array, hence it takes the array as a const reference.
void show_array(const double ar[], int limit)
{ 
    for (int i = 0; i < limit; i++)
    {
        cout << "item " << i << ": " << ar[i] << "\n";
    }
    cout << "\n"; 
}

// This function fills an array with user input and returns the number of elements filled.
// It stops filling when the user enters invalid input or reaches the limit.
int fill_array(double ar[], int limit)    
{
    int i;
    for (i = 0; i < limit; i++)
    {
        cout << "enter value: ";
        if (!(cin >> ar[i]))
        {
            cin.clear();
            while (cin.get() != '\n')
                continue;
            cout << "invalid input, input terminated.\n";
            break;
        }
    }

    return i;
}

// This function applies a coefficient to each element of an array.
// It modifies the array in place, multiplying each element by the given coefficient.
void apply_coefficient(double coef, double ar[], int limit)
{
    for (int i = 0; i < limit; i++)
    {
        ar[i] *= coef;
    }
}

// This function applies a coefficient to a range of elements in an array.
// It takes pointers to the beginning and end of the range, allowing for more flexible usage.
void apply_coefficient_in_range(double coef, double *begin, double *end)
{
    for (double *pt = begin; pt != end; pt++)
        *pt = *pt * coef;
}