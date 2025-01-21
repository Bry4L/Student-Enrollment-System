#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include "authentication.h" // For UserList
#include "course.h"
#include "enroll.h"

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
void studentMenu(const char* studentID, const char* studentName, EnrolledList& enrolledList, CourseManagement& courseManagement, WaitlistQueue& waitlist, UndoStack& undoStack);
void searchStudent();

// Declare save and load functions
void saveStudentsToFile();
void loadStudentsFromFile();

// Declare merge sort functions
void merge(vector<Student>& students, int left, int mid, int right);
void mergeSort(vector<Student>& students, int left, int right);
void sortStudents();

// Function to get student name by ID
string getStudentNameById(const string& studentID);

#endif
