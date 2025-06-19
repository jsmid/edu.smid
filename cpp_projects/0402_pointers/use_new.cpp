#include <iostream>
using namespace std;

// This program demonstrates the use of variables, pointers, and addresses in C++.
// It initializes two variables, prints their values and addresses,
// and shows how to manipulate a variable using a pointer.
int main()
{ 
    double *pd = new double; // dynamically allocates memory for a double variable
    cout << "pd = " << pd << "\n"; // prints the address of the allocated memory
    *pd = 45.55874;          // assigns a value to the memory location pointed to by pd
    
    cout << "value of *pd = " << *pd << ", location of pd = " << pd << "\n";
    cout << "size of *pd = " << sizeof(*pd) << ", size of pd = " << sizeof(pd) << "\n";

    delete pd; // releases the memory allocated for the double variable
    cout << "memory for pd released\n";
    pd = NULL; // sets pd to NULL to avoid dangling pointer
    cout << "pd set to NULL: pd = " << pd << "\n"; // prints the address of pd, which is now NULL

    double wages[3] = {10000., 20000., 30000.};
    short stacks[3] = {3, 2, 1};

    double *pw = wages;     // C++ interprets the array name as the address of its first element
    short *ps = &stacks[0]; // explicitly assigns the address of the first element of the stacks array
    cout << "wages[0] = " << wages[0] << ", wages[1] = " << wages[1] << ", wages[2] = " << wages[2] << "\n";
    cout << "stacks[0] = " << stacks[0] << ", stacks[1] = " << stacks[1] << ", stacks[2] = " << stacks[2] << "\n";

    cout << "pw = " << pw << ", *pw = " << *pw << "\n"; // prints the address of the first element of the wages array and its value
    cout << "ps = " << ps << ", *ps = " << *ps << "\n"; // prints the address of the first element of the stacks array and its value

    pw = pw + 1; // increments the pointer to point to the next element in the wages array
    ps = ps + 1; // increments the pointer to point to the next element in the stacks array
    cout << "After incrementing pointers:\n";
    cout << "pw = pw + 1; => pw = " << pw << ", *pw = " << *pw << "\n";
    cout << "ps = ps + 1; => ps = " << ps << ", *ps = " << *ps << "\n";

    cout << "stacks[0] = " << stacks[0] << ", stacks[1] = " << stacks[1] << "\n"; // prints the values of the first two elements of the stacks array
    cout << "stacks = " << stacks << ", stacks + 1 = " << stacks + 1 << "\n"; // prints the address of the first element and the address of the second element of the stacks array
    cout << "*stacks = " << *stacks << ", *(stacks + 1) = " << *(stacks + 1) << "\n"; // prints the value of the first element and the value of the second element of the stacks array

    // number of elements can be obtained by dividing the size of the array by the size of one element
    cout << "sizeof(stacks) = " << sizeof(stacks) << ", sizeof(*stacks) = " << sizeof(*stacks) << ", number of elements = " << sizeof(stacks) / sizeof(*stacks) << "\n";
    cout << "sizeof(ps) = " << sizeof(ps) << " in this case returns the size of the address of the first element!\n\n";

    const char *bird = "wren";
    cout << "in the case of char*, cout << bird prints the string content and not the address: " << bird << ", to print the address you need to cast char* to int*: cout << (int*) bird: " << (int *)bird << "\n";

    return 0;
}