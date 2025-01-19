#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include "authentication.h" // For UserList

using namespace std;

// Student structure
struct Student {
    string id;
    string name;
    string ageOrContact;
};

// Node structure for linked list
struct Node {
    Student student;
    Node* next;
};

// Function declarations
void addStudent(UserList& userList);
void updateStudent();
void deleteStudent(UserList& userList);
void viewStudents();
void studentMenu();
void searchStudent();

// Declare save and load functions
void saveStudentsToFile();
void loadStudentsFromFile();

// Declare merge sort functions
void merge(vector<Student>& students, int left, int mid, int right);
void mergeSort(vector<Student>& students, int left, int right);
void sortStudents();

#endif
