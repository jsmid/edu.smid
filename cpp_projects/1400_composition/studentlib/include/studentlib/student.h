#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <string>
#include "arrayslib/arraydb.h"

namespace stu
{
    class Student
    {
    private:
        std::string name;
        arr::ArrayDb scores;

    public:
        Student() : name("null student"), scores() {}
        Student(const std::string &s) : name(s), scores() {}
        Student(int n) : name("null student"), scores(n) {}
        Student(const std::string &s, const arr::ArrayDb &a) : name(s), scores(a) {}
        Student(const char *str, const double *pd, int n) : name(str), scores(pd, n) {}
        ~Student() {}

        double &operator[](int i);
        const double &operator[](int i) const;
        double avg_score() const;

        /// @brief  Outputs the student's results to the specified output stream.
        /// @param os   The output stream to which the student's results will be written.
        /// @param stu  The Student object whose results will be outputted.
        /// @return     A reference to the output stream after writing the student's results.
        /// This function outputs the student's name and scores to the specified output stream.
        /// It formats the output to display the student's results in a readable manner.
        friend std::ostream &operator<<(std::ostream &os, const Student &stu)
        {
            os << "Student results: " << stu.name << ":\n";
            os << stu.scores;
            return os;
        }

        /// @brief  Reads the student's name from the specified input stream.
        /// @param is   The input stream from which the student's name will be read.
        /// @param stu  The Student object into which the name will be read.
        /// @return     A reference to the input stream after reading the student's name.
        /// This function reads the student's name from the specified input stream.
        /// It expects the name to be provided as a string and stores it in the Student object.
        friend std::istream &operator>>(std::istream &is, Student &stu)
        {
            is >> stu.name;
            return is;
        }
    };
}

#endif
