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

    Course() = default;

    Course(string num, string name, vector<string> prereqs)
        : courseNumber(num), courseName(name), prerequisites(prereqs) {}

};

#endif // COURSE_H
