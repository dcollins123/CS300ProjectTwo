/* Name:   Course.h
   Author: Dan Collins
   Date:   16 Apr 2024  */

#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>

using namespace std;

class Course {
public:
    string courseNumber;
    string courseName;
    vector<string> prerequisites;

    Course() = default;                                          //Default constructor
    Course(string num, string name, vector<string> prereqs)      //Initialize course
        : courseNumber(num), courseName(name), prerequisites(prereqs) {}

};

#endif // COURSE_H
