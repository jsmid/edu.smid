#ifndef _STRING2_H_
#define _STRING2_H_

#include <iostream>
using namespace std;

class String
{
private:
    char *str;          // pointer to the string
    int len;            // length of the string
    static int str_num; // number of String class instances

public:
    static int num_strings() { return str_num; };
    String();
    String(const char *s);
    String(const String &s);
    ~String();
    String &operator=(const String &s);
    String &operator=(const char* str);
    friend ostream &operator<<(ostream &os, const String &s);
    friend istream &operator>>(istream &is, const String &s);
};

#endif