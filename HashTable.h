/* Name:   HashTable.h
   Author: Dan Collins
   Date:   16 Apr 2024  */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Course.h"
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

const unsigned int DEFAULT_SIZE = 179;              //constant def w/ prime to reduce collisions

class HashTable {
private:
    struct Node {
        Course course;
        unsigned key;
        Node* next;

        Node() : key(UINT_MAX), next(nullptr) {}
        Node(Course aCourse, unsigned aKey) : course(aCourse), key(aKey), next(nullptr) {}
    };

    vector<Node*> nodes;
    unsigned tableSize = DEFAULT_SIZE;

    unsigned hash(string courseNumber) {            //converts course num to index for hash table
        unsigned int hashValue = 0;
        for (char c : courseNumber) {
            hashValue = hashValue * 31 + c;
        }
        return hashValue % tableSize;
    }

public:
    HashTable() { nodes.resize(DEFAULT_SIZE); }     //default constructor
    ~HashTable() {                                  //destructor
        for (auto& node : nodes) {
            Node* current = node;
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }
    void Insert(Course course) {                    //insert course into hash table
        unsigned key = hash(course.courseNumber);
        Node* newNode = new Node(course, key);
        if (nodes[key] == nullptr) {
            nodes[key] = newNode;
        }
        else {
            Node* current = nodes[key];
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }
    void printCourseList() {                        //print course list
        vector<Course> allCourses;

        for (auto& node : nodes) {
            Node* current = node;
            while (current != nullptr) {
                allCourses.push_back(current->course);
                current = current->next;
            }
        }

        sort(allCourses.begin(), allCourses.end(), [](const Course& a, const Course& b) {
            return a.courseNumber < b.courseNumber;
            });

        for (const auto& course : allCourses) {
            cout << course.courseNumber << ", " << course.courseName << endl;
        }
        
    }

    Course Search(string courseNumber) {             //search for course by number
        unsigned key = hash(courseNumber);
        Node* current = nodes[key];
        while (current != nullptr) {
            if (current->course.courseNumber == courseNumber) {
                return current->course;
            }
            current = current->next;
        }
        cout << "Course not found" << endl;
        return Course();
    }
};

#endif // HASHTABLE_H
