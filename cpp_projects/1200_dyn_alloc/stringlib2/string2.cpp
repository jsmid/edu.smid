#include <cstring>

using namespace std;
#include "string2.h" // include the String class definition

int String::str_num = 0;    // initialize static member variable

/// @brief Default constructor
/// Initializes the string to an empty string and increments the static string count.
String::String()
{
    this->len = 0;
    this->str = new char[1];
    cout << "Creating " << this->str << " by an implicit constructor.\n";
    String::str_num++;
}

/// @brief Constructor accepting a string
/// Initializes the string with the provided C-style string and increments the static string count.
/// @param s the C-style string to initialize the String object  
String::String(const char *s)
{
    this->len = strlen(s);
    this->str = new char[this->len + 1];
    strcpy(this->str, s);
    cout << "Creating " << this->str << " by a constructor accepting a string.\n";
    String::str_num++;
}

/// @brief Copy constructor
/// Initializes a new String object as a copy of an existing String object.
/// @param s the String object to copy
/// @details This constructor allocates new memory for the string and copies the content from the source String object.
String::String(const String &s)
{
    this->len = s.len;
    this->str = new char[this->len + 1];
    strcpy(this->str, s.str);
    cout << "Creating " << this->str << " by a copy constructor.\n";
    String::str_num++;
}

/// @brief Destructor
/// Cleans up the String object by deleting the dynamically allocated memory for the string and decrements the static string count.
String::~String()
{
    --String::str_num;
    cout << "Deleting: " << this->str << "\n";
    delete[] this->str;
    cout << "Strings left: " << String::str_num << "\n";
}

/// @brief Assignment operator
/// Replaces the content of this String object with the content of another String object.
/// @param s the String object to copy from
/// @return a reference to this String object after the assignment
String &String::operator=(const String &s)
{
    if (this == &s)
        return *this;

    cout << "Replacing this->str: '" << this->str << "' with: '" << s.str << "'\n";
    delete[] this->str;
    this->len = s.len;
    this->str = new char[this->len + 1];
    strcpy(this->str, s.str);

    return *this;
}

/// @brief Assignment operator for C-style strings
/// Replaces the content of this String object with the content of a C-style string.
/// @param str the C-style string to copy from
/// @return a reference to this String object after the assignment
String &String::operator=(const char *str)
{
    delete[] this->str;
    this->len = strlen(str);
    this->str = new char[this->len + 1];
    strcpy(this->str, str);

    return *this;
}

/// @brief Returns the number of String instances
/// @param os the output stream to write to
/// @param s the String object to output
/// @return the number of String instances currently in existence
ostream &operator<<(ostream &os, const String &s)
{
    return os << s.str;
}

/// @brief Input stream operator for String
/// Reads a line from the input stream and assigns it to the String object.
/// @param is the input stream to read from
/// @param s the String object to assign the input to
/// @return the input stream after reading
istream &operator>>(istream &is, String &s)
{
    char temp[80];
    is.get(temp, 80);
    if (is)
        s = temp; // operator=(const char* str)
    while (is && is.get() != '\n') // clear the input buffer
        continue;

    return is;
}
