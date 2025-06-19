#include <iostream>
using namespace std;

struct inflatable // structure template
{
    char name[20] = {'\0'};
    float volume = .0;
    double price = .0;
};

struct toggle_register // bitfield structure template
{
    int sn : 4; // 4 bits for 'sn' value
    int : 4;    // unused 4 bits
    bool goodIn : 1;
    bool goodOut : 1;
};

enum traffic_light // enumerator template
{
    green,
    yellow,
    red
};

enum position // enumerator template with defined values
{
    one = 1,
    two = 2,
    four = 4,
    eight = 8
};

enum position_1 // enumerator template with partial value definitions
{
    zero,
    null = 0,
    oone,
    nr_one = 1
};

// The enumerators can be initialized with values from the enumerator template
// but they can also be used without initialization, in which case they take the next available value
//
// The first enumerator starts with 0, the next one takes the value of the previous one + 1, and so on.
// If an enumerator is initialized with a value, the next one takes the value of the previous one + 1, 
// unless it is explicitly initialized with a different value. If an enumerator is not initialized, 
// it takes the value of the previous one + 1, starting from 0 for the first enumerator.
// The enumerators can be used as integers, but they are not strictly typed, so they can be mixed with other integer types.
// This can lead to confusion, so it is recommended to use enumerators only for their intended purpose and not mix them with other integer types.
//
// It is also recommended to use enumerators with a specific type, such as 'enum class', to avoid name conflicts and improve type safety.
// The 'enum class' is a scoped enumeration that provides better type safety and avoids name conflicts.
// It is defined using the 'enum class' keyword and can have a specific underlying type, such as 'int', 'unsigned int', etc.
int main()
{
    inflatable strt1;
    cout << "inflatable strt1; ==> name=" << strt1.name << ", volume=" << strt1.volume << ", price=" << strt1.price << "\n";
    inflatable strt2 = {"Fabulous", 15., 221.};
    cout << "inflatable strt2 = {\"Fabulous\", 15., 221.}; ==> name=" << strt2.name << ", volume=" << strt2.volume << ", price=" << strt2.price << "\n";
    strt1 = strt2;
    cout << "strt1 = strt2; ==> name=" << strt1.name << ", volume=" << strt1.volume << ", price=" << strt1.price << "\n";

    inflatable strt_arr[2] = // initialization of structure array
        {
            {"Bambi", .5, 21.99},
            {"Godzilla", 200, 565.99}};
    cout << strt_arr[1].name << "\n";

    toggle_register regs[2] = // initialization of bitfield array
        {
            {4, true, false}, {7, false, true}};

    cout << "regs[0] == sn: " << regs[0].sn << ", goodIn: " << regs[0].goodIn << ", goodOut: " << regs[0].goodOut << "\n\n";

    traffic_light g, y, r;
    g = green;
    y = yellow;
    r = red;
    cout << "uninitialized enum: green=" << g << ", yellow=" << y << ", red=" << r << "\n";

    position p_one, p_two, p_four, p_eight;
    p_one = one;
    p_two = two;
    p_four = four;
    p_eight = eight;
    cout << "initialized enum: one=" << p_one << ", two=" << p_two << ", four=" << p_four << ", eight=" << p_eight << "\n";

    position_1 e_zero, e_null, e_one, e_nr_one;
    e_zero = zero;
    e_null = null;
    e_one = oone;
    e_nr_one = oone;
    cout << "partially initialized enum: zero=" << e_zero << ", null=" << e_null << ", one=" << e_one << ", nr_one=" << e_nr_one << "\n";
}