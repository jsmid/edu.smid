#include <iostream>
#include <climits>
// The climits header provides limits for integral types, such as SCHAR_MAX, SHRT_MAX, INT_MAX, etc.

using namespace std;

// This program demonstrates the sizes and limits of various data types in C++.
// It prints the size of each data type in bytes and their maximum values.
// It also shows the difference between signed and unsigned types, as well as the precision of floating-point types.
// The program also illustrates the behavior of floating-point arithmetic and integer division.
// It includes examples of how to use constants and the effects of type conversion.
int main()
{
    bool bool_max = true;
    char char_max = SCHAR_MAX;
    short short_max = SHRT_MAX;
    int int_max = INT_MAX;
    long long_max = LONG_MAX;
    long long llong_max = LLONG_MAX;

    cout << "the size of bool is " << sizeof(bool_max) << " bytes.\n";
    cout << "the size of char is " << sizeof(char_max) << " bytes.\n";
    cout << "the size of short is " << sizeof(short_max) << " bytes.\n";
    cout << "the size of int is " << sizeof(int_max) << " bytes.\n";
    cout << "the size of long is " << sizeof(long_max) << " bytes.\n";
    cout << "the size of llong is " << sizeof(llong_max) << " bytes.\n";

    unsigned char uchar_max = UCHAR_MAX;
    unsigned short ushort_max = USHRT_MAX;
    unsigned int uint_max = UINT_MAX;
    unsigned long ulong_max = ULONG_MAX;
    unsigned long long ullong_max = ULLONG_MAX;

    cout << "\nMaximum values:\n";
    cout << "bool = " << bool_max << "\n";
    cout << "char = " << (int)char_max << "\n";
    cout << "short = " << short_max << "\n";
    cout << "int = " << int_max << "\n";
    cout << "long = " << long_max << "\n";
    cout << "llong = " << llong_max << "\n\n";
    cout << "unsigned char = " << (int)uchar_max << "\n";
    cout << "unsigned short = " << ushort_max << "\n";
    cout << "unsinged int = " << uint_max << "\n";
    cout << "unsigned long = " << ulong_max << "\n";
    cout << "unsigned llong = " << ullong_max << "\n\n";

    // usage of the constant 128 with the type definition unsigned long long
    cout << "128 ma " << sizeof(128) << " bajty.\n";
    cout << "128ULL ma " << sizeof(128ULL) << " bajty.\n\n";

    cout.setf(ios_base::fixed, ios_base::floatfield); // use fixed-point notation
    float dot_three_inf_float = 10. / 3.;             // precision about 6 digits
    double dot_three_inf_double = 10. / 3.;           // precision about 15 digits
    long double dot_three_inf_long_double = 10. / 3.; // precision about 16 digits

    cout << ".333..3 as float = " << dot_three_inf_float << "\n";
    cout << ".333..3 as double = " << dot_three_inf_double << "\n";
    cout << "3333333.33..3 as float = " << dot_three_inf_float * 1.0e6 << "\n";
    cout << "3333333.33..3 as double = " << dot_three_inf_double * 1.0e6 << "\n";
    cout << "333333333.33..3 as float = " << dot_three_inf_float * 1.0e8 << "\n";
    cout << "333333333.33..3 as double = " << dot_three_inf_double * 1.0e8 << "\n";
    cout << "333333333333333.33..3 as double = " << dot_three_inf_double * 1.0e14 << "\n";
    cout << "3333333333.33..3 as long double = " << dot_three_inf_long_double * 1.0e9 << "\n";
    cout << "333333333333333.33..3 as long double = " << dot_three_inf_long_double * 1.0e14 << "\n\n";

    float a_float = 2.34e8;
    float b_float = a_float + 1.f;
    cout << "a_float = " << a_float << "\n";
    cout << "b_float - a_float = " << (b_float - a_float) << "\n"; // 0.000000! type float distinguishes only the first 6 or 7 digits
    double a_double = 2.34e8;
    double b_double = a_double + 1.f;
    cout << "a_double = " << a_double << "\n";
    cout << "b_double - a_double = " << (b_double - a_double) << "\n\n"; // 1.000000 OK

    cout << "Integer division: 9/5 = " << 9 / 5 << "\n";
    cout << "Division of decimal numbers: 9./5. = " << 9. / 5. << "\n";
    cout << "Mixed division: 9./5 = " << 9. / 5 << "\n";
    cout << "Division with type double: 1e7/9. = " << 1e7 / 9. << "\n";
    cout << "Division with type float: 1e7f/9.f = " << 1e7f / 9.f << "\n\n";

    int int_val1 = 3.9832;
    int int_val2 = 3.0e12;
    cout << "Assigning 3.9832 to a variable of type int: " << int_val1 << "\n";
    cout << "Assigning 3.0e12 to a variable of type int: " << int_val2 << "\n";

    return 0;
}