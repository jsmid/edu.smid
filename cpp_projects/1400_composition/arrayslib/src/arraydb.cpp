#include "arrayslib/arraydb.h"

/// @brief Default constructor for the ArrayDb class.
/// Initializes the size to 0 and the array pointer to NULL.
arr::ArrayDb::ArrayDb()
{
    this->size = 0;
    this->arr = NULL;
}

/// @brief Constructor for the ArrayDb class.
/// Initializes the array with a specified size and fills it with a given value.
/// @param n   The size of the array.
/// @param val The value to fill the array with (default is 0.0).
/// This constructor allows creating an ArrayDb object with a specified size and initial value for all elements.
arr::ArrayDb::ArrayDb(unsigned int n, double val)
{
    this->size = n;
    this->arr = new double[n];
    for (int i = 0; i < n; i++)
    {
        this->arr[i] = val;
    }
}

/// @brief Constructor for the ArrayDb class.
/// Initializes the array with values from a given pointer and size.
/// @param pn  Pointer to an array of doubles.
/// @param n   The size of the array.
/// This constructor allows creating an ArrayDb object from an existing array of doubles.
/// It allocates memory for the array and copies the values from the provided pointer.
arr::ArrayDb::ArrayDb(const double *pn, unsigned int n)
{
    this->size = n;
    this->arr = new double[n];
    for (int i = 0; i < n; i++)
    {
        this->arr[i] = pn[i];
    }
}

/// @brief Copy constructor for the ArrayDb class.
/// Initializes a new ArrayDb object as a copy of an existing one.
/// @param a   Reference to an existing ArrayDb object to copy from.
/// This constructor allows creating a new ArrayDb object that is a copy of an existing one.
arr::ArrayDb::ArrayDb(const ArrayDb &a)
{
    this->size = a.size;
    this->arr = new double[a.size];
    for (int i = 0; i < a.size; i++)
    {
        this->arr[i] = a.arr[i];
    }
}

/// @brief Destructor for the ArrayDb class.
/// Cleans up the dynamically allocated memory for the array.
arr::ArrayDb::~ArrayDb()
{
    delete[] this->arr;
}

/// @brief Calculates the average of the elements in the array.
/// @return The average value of the elements in the array.
double arr::ArrayDb::avg() const
{
    unsigned int sum = 0;
    if (this->size > 0)
    {
        for (int i = 0; i < this->size; i++)
        {
            sum += this->arr[i];
        }

        return sum / this->size;
    }

    return 0.0;
}

/// @brief  Accesses the element at the specified index.
/// @param i    The index of the element to access.
/// @return     A reference to the element at the specified index.
/// This function allows both reading and modifying the element at the specified index.
double &arr::ArrayDb::operator[](int i)
{
    if (i < 0 || i >= this->size)
    {
        std::cerr << "Index " << i << " je mimo meze [0, " << this->size - 1 << "]\n";
        exit(1);
    }

    return this->arr[i];
}

/// @brief  Accesses the element at the specified index for constant objects.
/// @param i    The index of the element to access. 
/// @return     A constant reference to the element at the specified index.
/// This function allows reading the element at the specified index without modifying it.
const double &arr::ArrayDb::operator[](int i) const
{
    if (i < 0 || i >= this->size)
    {
        std::cerr << "Index " << i << " je mimo meze [0, " << this->size - 1 << "]\n";
        exit(1);
    }

    return this->arr[i];
}

/// @brief  Assignment operator for the ArrayDb class.
/// Assigns the values of one ArrayDb object to another.
/// @param a   Reference to an existing ArrayDb object to assign from.
/// @return A reference to the current ArrayDb object after assignment.
arr::ArrayDb &arr::ArrayDb::operator=(const ArrayDb &a)
{
    if (this == &a)
        return *this;
    delete[] this->arr;
    this->arr = new double[a.size];
    for (int i = 0; i < a.size; i++)
    {
        this->arr[i] = a.arr[i];
    }
    this->size = a.size;
    return *this;
}