/* Name:   HashTable.cpp
   Author: Dan Collins
   Date:   16 Apr 2024  */

#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <sstream>



void loadCourses(HashTable& table) {                //user inputs file, gets read and parsed
    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Could not open file." << endl;
        return;
    }

    string line, num, name, prereq;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, num, ',');
        getline(ss, name, ',');
        vector<string> prereqs;
        while (getline(ss, prereq, ',')) {
            prereqs.push_back(prereq);
        }
        Course course(num, name, prereqs);
        table.Insert(course);
    }

    cout << "Data loaded successfully." << endl;
}

void displayMenu() {                                //display menu options
    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit" << endl;
}

int main() {
    HashTable courseTable;
    int choice = 0;

    cout << "Welcome to the course planner." << endl;

    do {
        displayMenu();
        cout << "What would you like to do? ";
        cin >> choice;

        switch (choice) {
        case 1:
            loadCourses(courseTable);
            break;
        case 2:
            courseTable.printCourseList();
            break;
        case 3: {
            string courseNumber;
            cout << "What course do you want to know about? ";
            cin >> courseNumber;
            Course course = courseTable.Search(courseNumber);
            if (!course.courseNumber.empty()) {
                cout << course.courseNumber << ", " << course.courseName << "\nPrerequisites: ";
                for (const auto& prereq : course.prerequisites) {
                    cout << prereq << ", ";
                }
                cout << endl;
            }
            else {
                cout << "Course not found." << endl;
            }
            break;
        }
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;
        default:
            cout << choice << " is not a valid option." << endl;
            break;
        }
    } while (choice != 9);

    return 0;
}
