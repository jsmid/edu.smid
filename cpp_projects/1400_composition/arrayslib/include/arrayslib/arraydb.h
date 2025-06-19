#ifndef _ARRAYDB_H_
#define _ARRAYDB_H_

#include <iostream>

namespace arr // Namespace for the array database library
{
    // This class represents a dynamic array of doubles with various functionalities.
    // It includes constructors for initialization, a destructor for cleanup,
    class ArrayDb
    {
    private:
        unsigned int size; // number of elements in the array
        double *arr;       // address of the first element

    public:
        ArrayDb();
        // A constructor that can be called with a single parameter can serve
        // as an implicit conversion function.
        // In this case, that would not make sense.
        // For example:
        //      ArrayDb doh(20, 100);
        //      doh = 5;
        // would reinitialize doh as an array of length five, each element with value 0.
        //
        // The keyword 'explicit' prevents this constructor from being used for implicit conversion.
        explicit ArrayDb(unsigned int n, double val = 0.0);
        ArrayDb(const double *pn, unsigned int n);
        ArrayDb(const ArrayDb &a);
        virtual ~ArrayDb();
        int get_size() { return this->size; };
        double avg() const;
        virtual double & operator[](int i);
        // For the case when the ArrayDb object is created as a constant variable ...
        virtual const double & operator[](int i) const;
        ArrayDb &operator=(const ArrayDb &a);
        friend std::ostream &operator<<(std::ostream &os, const ArrayDb &a);
    };

    /// @brief  Outputs the contents of the ArrayDb object to the specified output stream.
    /// @param os   The output stream to which the contents of the ArrayDb object will be written.
    /// @param a    The ArrayDb object whose contents will be outputted.
    /// @return     A reference to the output stream after writing the contents of the ArrayDb object.
    /// This function iterates through the elements of the ArrayDb object and outputs them to the specified output stream.
    /// It formats the output such that every five elements are printed on a new line.
    /// If the total number of elements is a multiple of five, it adds an extra newline at the end.
    /// This function is useful for displaying the contents of the ArrayDb object in a readable format.
    std::ostream & operator<<(std::ostream & os, const ArrayDb & a)
    {
        int i;
        for (i = 0; i < a.size; i++)
        {
            os << a.arr[i] << " ";
            if (i % 5 == 4)
                os << "\n";
        }

        if (i % 5 == 0)
            os << "\n";

        return os;
    }
}

#endif