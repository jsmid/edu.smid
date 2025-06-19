#include "studentlib/student.h"

/// @brief   operator[] for accessing student scores.
/// @param i  The index of the score to access.
/// @return  A reference to the score at the specified index.
/// @details This function allows both reading and modifying the score at the specified index.
double &stu::Student::operator[](int i)
{
    return this->scores[i];
}

/// @brief   operator[] for accessing student scores.
/// @param i  The index of the score to access.
/// @return  A constant reference to the score at the specified index.
/// @details This function allows reading the score at the specified index without modifying it.
const double &stu::Student::operator[](int i) const
{
    return this->scores[i];
}

/// @brief   Calculates the average score of the student.
/// @return  The average score of the student.
double stu::Student::avg_score() const
{
    return this->scores.avg();
}
