#include <iostream>
using namespace std;

template <class T> 
void swap_values(T &v1, T &v2); 

// Overloaded template for arrays
template <class T>
void swap_values(T v1[], T v2[], int len);

struct some_structure
{
    int x;
    char y[10];
};

struct other_struct
{
    int c;
    double d;
};

// Explicit specialization
template <>
void swap_values<other_struct>(other_struct &v1, other_struct &v2);

// This program demonstrates how to swap values of different types using templates.
// It swaps integers, doubles, structures, and arrays using template functions.
int main()
{
    int val_a = 5;
    int val_b = 6;

    swap_values(val_a, val_b); // Call the template function to swap integers
    // After the swap, val_a should be 6 and val_b should be 5
    cout << "swap integers: val_a = " << val_a << ", val_b = " << val_b << "\n";

    double val_c = 5.;
    double val_d = 6.;
    swap_values(val_c, val_d); // Call the template function to swap doubles
    // After the swap, val_c should be 6.0 and val_d should be 5.0
    cout << "swap doubles: val_c = " << val_c << ", val_d = " << val_d << "\n";

    some_structure struct_a = {10, "hoj"};
    some_structure struct_b = {20, "ahoj"};
    swap_values(struct_a, struct_b);    // Call the template function to swap structures    
    cout << "swap structures: struct_a.x = " << struct_a.x << ", struct_b.x = " << struct_b.x << "\n"; 
    cout << "                 struct_a.y = " << struct_a.y << ", struct_b.y = " << struct_b.y << "\n";

    int f[] = {1, 2, 3};
    int g[] = {4, 5, 6};
    swap_values(f, g, 3); // Call the overloaded template function to swap arrays
    // After the swap, f[0] should be 4 and g[0] should be 1
    cout << "swap arrays: f[0] = " << f[0] << ", g[0] = " << g[0] << "\n";

    other_struct struct_c = {10, 3.}; 
    other_struct struct_d = {20, 4.};
    swap_values(struct_c, struct_d);     // Call the explicit specialization to swap other_struct instances
    // After the swap, struct_c.c should be 20 and struct_d.c should be 10  
    cout << "swap structures: struct_c.c = " << struct_c.c << ", struct_d.c = " << struct_d.c << "\n"; 
    cout << "                 struct_c.d = " << struct_c.d << ", struct_d.d = " << struct_d.d << "\n";

    return 0;
}

// Template function to swap values of any type
// This function takes two references to values of type T and swaps them.
template <class T>
void swap_values(T &v1, T &v2)
{
    T tmp = v1;
    v1 = v2;
    v2 = tmp;
}

// Overloaded template function to swap values of arrays
// This function takes two arrays of type T and their length, and swaps the elements.
template <class T>
void swap_values(T v1[], T v2[], int len)
{
    T tmp; 
    for (int i = 0; i < len; i++)
    {
        tmp = v1[i];
        v1[i] = v2[i];
        v2[i] = tmp;
    }
}

// Explicit specialization for other_struct
// This function swaps the values of two other_struct instances.
template <>
void swap_values(other_struct &v1, other_struct &v2)
{
    double tmp_d = v1.d;
    v1.d = v2.d;
    v2.d = tmp_d;
}
