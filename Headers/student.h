#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include "authentication.h"

using namespace std;

class Student {
public:
    string studentId;
    string name;
    string contactInfo;

    Student(string id, string n, string contact) : studentId(id), name(n), contactInfo(contact) {}
};

// Node for linked list
struct StudentNode {
    Student* student;
    StudentNode* next;

    StudentNode(Student* s) : student(s), next(nullptr) {}
    ~StudentNode() {
        delete student; // Delete the Student object
    }
};

// Linked list to store students
class StudentList {
public:
    StudentNode* head;

    StudentList() : head(nullptr) {}
    ~StudentList(); // Destructor to clean up the linked list

    void addStudent(UserList& userList); // Pass UserList as a parameter
    void updateStudent();
    void deleteStudent();
    void viewStudents();
};

void studentMenu();
#endif
