#include <iostream>

using namespace std;

int main()
{
    int arr_1[3]; // uninitialized array, contents can be anything
    cout << "int arr_1[3]; [0]=" << arr_1[0] << ", [1]=" << arr_1[1] << ", [2]=" << arr_1[2] << "\n";

    int arr_2[3] = {1}; // partially initialized array, remaining elements are set to zero
    cout << "int arr_2[3] = {1}; [0]=" << arr_2[0] << ", [1]=" << arr_2[1] << ", [2]=" << arr_2[2] << "\n";

    int arr_3[3] = {0}; // partially initialized array, entire array is set to zero
    cout << "int arr_3[3] = {0}; [0]=" << arr_3[0] << ", [1]=" << arr_3[1] << ", [2]=" << arr_3[2] << "\n";

    // an initialized array cannot be assigned to another array
    // but you can change the values of an initialized array
    arr_3[0] = 20;
    cout << "arr_3[0] = 20; [0]=" << arr_3[0] << ", [1]=" << arr_3[1] << ", [2]=" << arr_3[2] << "\n";

    // you can create an array without specifying its length and let the compiler deduce it from the number of initialized elements
    char arr_4[] = "hoj!";
    cout << "char arr_4[] = \"hoj!\" => " << arr_4 << "\n";

    arr_4[2] = '\0';
    cout << "arr_4[2] = '\\0'; => " << arr_4 << "\n";

    char arr_5[20];
    cin.getline(arr_5, 20).get(); // safely reads multi-word input, the following get removes the newline character from the buffer
    cout << "you entered: " << arr_5 << "\n";
    cin.clear();

    char arr_6[20]; // if the input is longer than 20 characters, the rest is read here :-(
    cin.getline(arr_6, 20).get();
    cout << "you entered: " << arr_6 << "\n";
    cin.clear();
}
