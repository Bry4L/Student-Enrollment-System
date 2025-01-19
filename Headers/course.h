#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>
#include <vector>
#include "instructor.h"

using namespace std;

class InstructorList;
class CourseManagement;

// Structure to represent a course
struct Course {
    string id;
    string name;
    int maxSeats;
    int enrolledStudents;
    vector<string> prerequisites; // List of prerequisite course IDs
};

struct InstructorCourseAssignment {
    string instructorID;
    string courseID;
};

// Stack class for assigning courses to instructors
class Stack {
private:
    InstructorCourseAssignment* stackArray;
    int top;
    int capacity;

    void resize();

public:
    Stack(int cap = 5);
    ~Stack();

    bool isEmpty();
    void push(const string& instructorID, const string& courseID); // Update to take both IDs
    InstructorCourseAssignment pop(); // Update to return an assignment
    InstructorCourseAssignment peek(); // Update to return an assignment
    void display(const InstructorList& instructorList, const CourseManagement& courseManagement); // Update to include instructor and course details
};
// CourseManagement class for managing courses
class CourseManagement {
private:
    Course* courses;
    int courseCount;
    int capacity;

    void resize();

public:
    CourseManagement(int cap = 5);
    ~CourseManagement();

    void addCourse(const string& id, const string& name, int maxSeats);
    void deleteCourse(const string& id);
    void updateCourse(const string& id, const string& name = "", int maxSeats = -1);
    void viewAllCourses();
    Course* findCourse(const string& id) const;  // Add this method
};

#endif
