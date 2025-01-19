#ifndef ENROLL_H
#define ENROLL_H

#include <iostream>
#include <cstring>
#include "course.h"

using namespace std;

// Structure for a Node in the enrolled students list
struct EnrollmentNode {
    char studentID[11];       // Stores the student's ID (10 digits + null terminator)
    char studentName[50];     // Stores the student's name
    char courseID[10];        // Stores the course ID
    char courseName[50];      // Stores the course name
    EnrollmentNode* next;     // Pointer to the next node in the list
};

// Structure for the enrolled list
struct EnrolledList {
    EnrollmentNode* head;  // Pointer to the head of the list
};

// Queue for waitlist management
struct WaitlistQueue {
    EnrollmentNode* front; // Pointer to the front of the queue
    EnrollmentNode* rear;  // Pointer to the rear of the queue

    WaitlistQueue() : front(nullptr), rear(nullptr) {}

    bool isEmpty();
    void enqueue(const char* studentID, const char* studentName, const char* courseID, const char* courseName);
    void dequeue();
    EnrollmentNode* getFrontNode();
};

// Stack for undo functionality
struct UndoStack {
    struct Action {
        char actionType[20];  // Type of action (e.g., "Enroll", "Drop")
        char studentID[11];   // Student ID (10 digits + null terminator)
        char courseID[10];    // Course ID
        Action* next;         // Pointer to the next action in the stack
    };

    Action* top; // Pointer to the top of the stack

    UndoStack() : top(nullptr) {}

    bool isEmpty();
    void push(const char* actionType, const char* studentID, const char* courseID);
    void pop(EnrolledList& list, CourseManagement& courseManagement, WaitlistQueue& waitlist);
    const char* getTopAction();
};

// Function declarations
void initializeEnrolledList(EnrolledList& list);
bool isValidStudentID(const char* studentID);
bool isUniqueStudentID(EnrolledList& list, const char* studentID);
void displayEnrolledCourses(EnrolledList& list, const char* studentID);
void displayWaitlist(WaitlistQueue& waitlist, const char* courseID);
void enrollStudent(EnrolledList& list, CourseManagement& courseManagement, WaitlistQueue& waitlist, UndoStack& undoStack, const char* studentID, const char* studentName, const char* courseID);
void dropCourse(EnrolledList& list, CourseManagement& courseManagement, WaitlistQueue& waitlist, UndoStack& undoStack, const char* studentID, const char* courseID);
void searchCourse(CourseManagement& courseManagement, const char* searchTerm);
void cleanupEnrolledList(EnrolledList& list);

#endif
