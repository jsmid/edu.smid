#include <iostream>
#include <cstring>

using namespace std;

char *get_name();

struct book
{
    char *author;
    int index;
};

// This program demonstrates the use of dynamic memory allocation for a struct.
// It creates a struct named 'book' with a pointer to a character array for the author's name
int main()
{
    cout << "This program demonstrates the use of dynamic memory allocation for a struct.\n";
    cout << "It creates a struct named 'book' with a pointer to a character array for the author's name.\n";
    book *k = new book; // dynamically allocate memory for a book struct
    cout << "k = new book; ==> k is a pointer to a book struct.\n";
    k->author = get_name(); // k->author is a pointer to a character array for the author's name
    cout << "k->author = get_name(); ==> k->author is a pointer to a character array for the author's name.\n";
    (*k).index = 0;         // (*k).index is the index of the book
    cout << "(*k).index = 0; ==> (*k).index is the index of the book.\n";
    cout << "book: author = " << k->author << ", strlen(k->author) = " << strlen(k->author) << ", index = " << k->index << "\n";

    book *library = new book[2]; // dynamically allocate memory for an array of 2 book structs
    cout << "book *library = new book[2]; ==> library is a pointer to an array of 2 book structs.\n";
    library[0].author = get_name(); // library[0].author is a pointer to a character array for the author's name of the first book
    cout << "library[0].author = get_name(); ==> library[0].author is a pointer to a character array for the author's name of the first book.\n";
    library[0].index = 1; // library[0].index is the index of the first book
    cout << "library[0].index = 1; ==> library[0].index is the index of the first book.\n";
    library[1].author = get_name(); // library[1].author is a pointer to a character array for the author's name of the second book
    cout << "library[1].author = get_name(); ==> library[1].author is a pointer to a character array for the author's name of the second book.\n";
    library[1].index = 2; // library[1].index is the index of the second book
    cout << "library[1].index = 2; ==> library[1].index is the index of the second book.\n";
    
    cout << "first book: author = " << library[0].author << ", strlen(library[0].author) = " << strlen(library[0].author) << ", index = " << library[0].index << "\n";
    cout << "second book: author = " << library[1].author << ", strlen(library[1].author) = " << strlen(library[1].author) << ", index = " << library[1].index << "\n";

    delete[] library[0].author; // free the memory allocated for the author's name of the first book
    delete[] library[1].author; // free the memory allocated for the author's name of the second book
    delete[] library; // free the memory allocated for the array of book structs
    delete k->author; // free the memory allocated for the author's name of the single book

    return 0;
}

char *get_name()
{
    char temp[80];
    cout << "enter name (max. 80 characters): ";
    cin >> temp;

    char *ret = new char[strlen(temp) + 1]; // increase by one for null terminator
    strcpy(ret, temp);                      // copy string into smaller space

    return ret;
}