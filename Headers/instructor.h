#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include <string>
#include <fstream>
#include "authentication.h"
#include "course.h"

using namespace std;

// Forward declarations
class Stack;
class CourseManagement;

// Instructor class to hold individual instructor data
class Instructor {
public:
    string instructorId;
    string name;
    string contactInfo;

    // Constructor to initialize the instructor object
    Instructor(string id, string n, string contact) : instructorId(id), name(n), contactInfo(contact) {}
};

// Node for linked list to store instructor data
struct InstructorNode {
    Instructor* instructor; // Pointer to an Instructor object
    InstructorNode* next;    // Pointer to the next node in the linked list

    // Constructor to initialize the InstructorNode with an Instructor object
    InstructorNode(Instructor* i) : instructor(i), next(nullptr) {}
    // Destructor to clean up memory by deleting the Instructor object
    ~InstructorNode() {
        delete instructor; // Delete the Instructor object
    }
};

// Linked list to store instructors
class InstructorList {
public:
    InstructorNode* head;   // Head pointer for the linked list of instructors

     // Constructor to initialize the InstructorList (starts with no instructors)
    InstructorList() : head(nullptr) {}
    ~InstructorList(); // Destructor to clean up the linked list

    void loadInstructorsFromFile();
    void saveInstructorsToFile();
    void addInstructor(UserList& userList); // Add instructor and register as user
    void updateInstructor();
    void deleteInstructor(UserList& userList);
    void viewInstructors();
    void viewAssignedCourses(const string& instructorId, const Stack& instructorStack, const CourseManagement& courseManagement); // Updated function
};

void instructorMenu(User* loggedInUser, InstructorList& instructorList, const Stack& instructorStack, const CourseManagement& courseManagement); // Updated function

#endif
