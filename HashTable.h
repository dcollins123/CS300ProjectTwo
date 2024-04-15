#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Course.h"
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const unsigned int DEFAULT_SIZE = 179;

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

    unsigned hash(string courseNumber) {
        unsigned int hashValue = 0;
        for (char c : courseNumber) {
            hashValue = hashValue * 31 + c;
        }
        return hashValue % tableSize;
    }

public:
    HashTable() { nodes.resize(DEFAULT_SIZE); }
    ~HashTable() {
        for (auto& node : nodes) {
            Node* current = node;
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }
    void Insert(Course course) {
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
    void PrintAll() {
        for (auto& node : nodes) {
            Node* current = node;
            while (current != nullptr) {
                cout << current->course.courseNumber << ", " << current->course.courseName << endl;
                current = current->next;
            }
        }
    }
    Course Search(string courseNumber) {
        unsigned key = hash(courseNumber);
        Node* current = nodes[key];
        while (current != nullptr) {
            if (current->course.courseNumber == courseNumber) {
                return current->course;
            }
            current = current->next;
        }
        cout << "Course not found" << endl;
        return Course(); // Return an empty course if not found
    }
};

#endif // HASHTABLE_H
