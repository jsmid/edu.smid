#include <iostream>
using namespace std;

struct nametag 
{
    char name[25];
    int shown;
};

nametag &show(nametag &tag);

// This program demonstrates how to return a reference to a structure from a function.
// It defines a structure for a nametag and provides a function to display the nametag's information.
int main()
{
    nametag tag1 = {"Adamek", 0};
    nametag tag2 = {"Stelinka", 0};
    cout << "show(tag1)\n"; 
    show(tag1);  // Call show function with tag1
    cout << "show(show(tag1))\n";
    show(show(tag1)); // Call show function with the return value of show(tag1), which is a reference to tag1
    nametag tmp_tag = tag1;
    cout << "show(tag1) = tag2\n";
    show(tag1) = tag2;  // Assign tag2 to the return value of show(tag1), which is a reference to tag1  
    cout << "show(tag1)\n";
    show(tag1);     // Call show function with tag1, which is now tag2
    cout << "show(tmp_tag) .. tmp_tag == original tag1, before calling show(tag1) = tag2\n";
    show(tmp_tag); // Call show function with tmp_tag, which is a copy of the original tag1
    cout << "tag1 = tmp_tag; show(tag1)\n";
    tag1 = tmp_tag;
    show(tag1); // Call show function with tag1, which is now back to the original tag1

    return 0;
}

// This function takes a nametag structure by reference, increments the shown count,
// and prints the name and shown count. It returns a reference to the nametag structure.
nametag &show(nametag &tag)
{
    tag.shown += 1;
    cout << "Name = " << tag.name << ", shown = " << tag.shown << "\n";

    return tag;
}
