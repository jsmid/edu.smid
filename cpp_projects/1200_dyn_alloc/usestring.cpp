#include <iostream>
using namespace std;

#include "stringlib2/string2.h" // include the String class definition
 
// This function creates a local variable of type String
void create_local_vars()
{
    String l1 = "local string l1";
}

// This function returns a pointer to a dynamically allocated String object
// Note: This is not a good practice, as it can lead to memory leaks if not handled properly.
String * return_local_var()
{
    String * l2 = new String("local string l2");
    return l2;
}

// This program demonstrates the use of the String class defined in stringlib2/string2.h.
// It creates several String objects, performs assignments, and shows how the static member variable str_num tracks the number of String instances.
int main()
{
    cout << "String s1 = \"string s1\";\n";
    String s1 = "string s1";    // Create a String object using a string literal    
    cout << "nr. of strings = " << String::num_strings() << "\n\n";

    cout << "String s2 = String(\"string s2\");\n";
    String s2 = String("string s2");    // Create a String object using the String constructor   
    cout << "nr. of strings = " << String::num_strings() << "\n\n";

    cout << "String s3 = \"string s3\";\n";
    String s3 = "string s3";        // Create another String object using a string literal
    cout << "nr. of strings = " << String::num_strings() << "\n\n";

    cout << "String s4 = s3;\n";
    String s4 = s3;     // Create a String object using the copy constructor
    cout << "nr. of strings = " << String::num_strings() << "\n\n";

    cout << "String s5 = \"string s5\";\n";
    String s5 = "string s5";    // Create another String object using a string literal
    cout << "nr. of strings = " << String::num_strings() << "\n\n";

    cout << "s5 = s3;\n";
    s5 = s3;    // Assign the value of s3 to s5 using the assignment operator
    cout << "nr. of strings = " << String::num_strings() << "\n\n";

    cout << "create_local_vars();\n";    
    create_local_vars();    // Create local String variables
    // Note: Local variables are destroyed when they go out of scope, so they do not affect the static count.
    cout << "nr. of strings = " << String::num_strings() << "\n\n";

    cout << "String * ps5 = return_local_var();\n";
    String * ps5 = return_local_var();   // Create a String object dynamically and return a pointer to it  
    cout << "nr. of strings = " << String::num_strings() << "\n\n";

    cout << "delete ps5;\n";
    delete ps5; // Delete the dynamically allocated String object
    // This will call the destructor and decrement the static count of String instances
    cout << "nr. of strings = " << String::num_strings() << "\n\n";
}