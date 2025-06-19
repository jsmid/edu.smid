#include <iostream>
using namespace std;

void swapr(int &a, int &b);
void swapp(int *a, int* b);
void swapv(int a, int b);

// This program demonstrates three different ways to swap two integers in C++:
// 1. By value (swapv) - does not change the original variables.    
// 2. By pointer (swapp) - changes the original variables using pointers.
// 3. By reference (swapr) - changes the original variables using references.
int main()
{
    int a = 2;
    int b = 3;
    int c = 4;
    int d = 5;
    int e = 6;
    int f = 7;

    cout << "a = " << a << ", b = " << b;
    swapv(a, b);
    cout << " passed by value, a = " << a << ", b = " << b << "\n";

    cout << "c = " << c << ", d = " << d;
    swapp(&c, &d);
    cout << " passed by pointer, c = " << c << ", d = " << d << "\n";

    cout << "e = " << e << ", f = " << f;
    swapr(e, f);
    cout << " passed by reference, e = " << e << ", f = " << f << "\n";

    return 0;
}

// This function swaps two integers by reference.
// It takes two integers by reference and swaps their values.
void swapr(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

// This function swaps two integers by pointer.
// It takes two pointers to integers and swaps the values they point to.
void swapp(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// This function swaps two integers by value.
// It takes two integers as parameters, but does not change the original variables.
void swapv(int a, int b)
{
    int tmp = a;
    a = b;
    b = tmp;
}
