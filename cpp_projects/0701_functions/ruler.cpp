#include <iostream>
using namespace std;

int main();

void reset_str(int str_len, char *ruler);

void subdivide(char *arr, int low, int high, int level);

// This program generates a ruler-like string representation with subdivisions.
int main()
{
    int str_len; // length of the ruler string
    // str_len should be at least 3 to accommodate the two ends and the middle division
    int div_levels; // number of levels of subdivisions
    cout << "This program generates a ruler-like string representation with subdivisions.\n";
    cout << "Enter width: ";
    cin >> str_len;
    cout << "Enter number of levels: ";
    cin >> div_levels;
    char *ruler = new char[str_len];

    reset_str(str_len, ruler); // Initialize the ruler string with spaces and '|' at the ends
    int min = 0; // min is the starting index of the ruler string
    // max is the ending index of the ruler string minus 1, since we will place '|' at the end
    int max = str_len - 2; // max is str_len - 2 because the last character is reserved for the null terminator
    for (int j = 1; j <= div_levels; j++) 
    { 
        subdivide(ruler, min, max, j); 
        cout << ruler << "\n";
        reset_str(str_len, ruler);
    }

    delete[] ruler;
    return 0;
}

// This function resets the ruler string to its initial state with spaces in between the ends.
// It sets the first and last characters to '|' and fills the rest with spaces.
void reset_str(int str_len, char *ruler)
{
    for (int i = 0; i < str_len - 2; i++)
    {
        ruler[i] = ' ';
    }
    ruler[str_len - 1] = '\0';
    ruler[0] = '|';
    ruler[str_len - 2] = '|';
}

// This function subdivides the ruler string by placing a '|' at the midpoint of the specified range.
// It recursively subdivides the left and right halves until the specified level is reached.
void subdivide(char *arr, int low, int high, int level)
{
    if (level == 0)
        return;

    int mid = (high + low) / 2;
    arr[mid] = '|';
    subdivide(arr, low, mid, level - 1);
    subdivide(arr, mid, high, level - 1);
}
