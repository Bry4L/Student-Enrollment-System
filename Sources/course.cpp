#include "course.h"
#include <iostream>

using namespace std;

// Stack class implementation
Stack::Stack(int cap) : capacity(cap), top(-1) {
    stackArray = new InstructorCourseAssignment[capacity]; // Initialize the array
}

//Destructor
Stack::~Stack() {
    delete[] stackArray;
}

//Resize function
//Doubles the capacity of the stack when it becomes full.
//Copies existing elements to a new, larger array.
void Stack::resize() {
    int newCapacity = capacity * 2;
    InstructorCourseAssignment* newStack = new InstructorCourseAssignment[newCapacity];
    for (int i = 0; i < capacity; ++i) {
        newStack[i] = stackArray[i];
    }
    delete[] stackArray;
    stackArray = newStack;
    capacity = newCapacity;
}

//Check whether stack is empty
bool Stack::isEmpty() {
    return top == -1;
}

//Adds a new InstructorCourseAssignment to the top of the stack.
void Stack::push(const string& instructorID, const string& courseID) {
    if (top == capacity - 1) {
        resize(); //Resizes the stack if necessary
    }
    stackArray[++top] = {instructorID, courseID}; // Store both IDs
}

//Removes and returns the top assignment from the stack.
InstructorCourseAssignment Stack::pop() {
    if (isEmpty()) {
        cout << "Error: Stack is empty!" << endl;
        return {"", ""}; // Return an empty assignment
    }
    return stackArray[top--]; // Return the assignment
}

//Returns the top assignment without removing it.
InstructorCourseAssignment Stack::peek() {
    if (isEmpty()) {
        cout << "Error: Stack is empty!" << endl;
        return {"", ""}; // Return an empty assignment
    }
    return stackArray[top]; // Return the assignment
}

//Returns a vector containing all assignments in the stack.
//Use for instructor.cpp could get all the instructed course and enrolled students multiple times else it will pop and only show 1 time
vector<InstructorCourseAssignment> Stack::peekAll() const {
    vector<InstructorCourseAssignment> assignments;
    for (int i = 0; i <= top; ++i) {
        assignments.push_back(stackArray[i]); // Add each assignment to the vector
    }
    return assignments;
}

//Displays all assigned courses along with instructor and course details.
void Stack::display(const InstructorList& instructorList, const CourseManagement& courseManagement) {
    if (isEmpty()) {
        cout << "No courses assigned to instructors." << endl;
    } else {
        cout << "Assigned Courses:" << endl;
        for (int i = 0; i <= top; ++i) {
            string instructorID = stackArray[i].instructorID;
            string courseID = stackArray[i].courseID;

            // Find instructor name
            string instructorName = "Unknown";
            InstructorNode* current = instructorList.head;
            while (current != nullptr) {
                if (current->instructor->instructorId == instructorID) {
                    instructorName = current->instructor->name;
                    break;
                }
                current = current->next;
            }

            // Find course name
            string courseName = "Unknown";
            Course* course = courseManagement.findCourse(courseID);
            if (course != nullptr) {
                courseName = course->name;
            }

            // Display the assignment details
            cout << "Instructor ID: " << instructorID
                 << ", Instructor Name: " << instructorName
                 << ", Course ID: " << courseID
                 << ", Course Name: " << courseName << endl;
        }
    }
}

// CourseManagement class implementation
CourseManagement::CourseManagement(int cap) : capacity(cap), courseCount(0) {
    courses = new Course[capacity];
}

//Destructor for CourseManagement object
CourseManagement::~CourseManagement() {
    delete[] courses;
}

//Doubles the capacity of the courses array when it becomes full.
void CourseManagement::resize() {
    int newCapacity = capacity * 2;
    Course* newCourses = new Course[newCapacity];
    for (int i = 0; i < courseCount; ++i) {
        newCourses[i] = courses[i];
    }
    delete[] courses;
    courses = newCourses;
    capacity = newCapacity;
}

//Adds a new course to the courses array.
void CourseManagement::addCourse(const string& id, const string& name, int maxSeats) {
    for (int i = 0; i < courseCount; ++i) {

           // Validate course ID (assuming it must be non-empty)
            if (id.empty()) {
                cout << "Error: Course ID cannot be empty.\n";
            return;
        }
        if (courses[i].id == id) {
            cout << "Error: Course ID '" << id << "' already exists." << endl;
            return;
        }
    }

    if (courseCount == capacity) {
        resize();
    }

    courses[courseCount++] = {id, name, maxSeats, 0};
    cout << "Course '" << name << "' added successfully." << endl;
}

//Deletes a course by its ID.
void CourseManagement::deleteCourse(const string& id) {
    int index = -1;
    for (int i = 0; i < courseCount; ++i) {
        if (courses[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Error: Course ID '" << id << "' does not exist." << endl;
        return;
    }

    for (int i = index; i < courseCount - 1; ++i) {
        courses[i] = courses[i + 1];
    }

    courseCount--;
    cout << "Course ID '" << id << "' deleted successfully." << endl;
}

//Updates the name and/or max seats of a course.
void CourseManagement::updateCourse(const string& id, const string& name, int maxSeats) {
    for (int i = 0; i < courseCount; ++i) {
        if (courses[i].id == id) {
            if (!name.empty()) {
                courses[i].name = name;
            }
            if (maxSeats > 0) {
                courses[i].maxSeats = maxSeats;
            }
            cout << "Course ID '" << id << "' updated successfully." << endl;
            return;
        }
    }
    cout << "Error: Course ID '" << id << "' does not exist." << endl;
}

//Displays all courses
void CourseManagement::viewAllCourses() {
    if (courseCount == 0) {
        cout << "No courses available." << endl;
        return;
    }

    cout << "Course List:" << endl;
    for (int i = 0; i < courseCount; ++i) {
        cout << "ID: " << courses[i].id
             << ", Name: " << courses[i].name
             << ", Max Seats: " << courses[i].maxSeats
             << ", Enrolled: " << courses[i].enrolledStudents << endl;
    }
}

//FindCourse method used for displaying the course assigned to instructor on instructor menu
//Finds and returns a course by its ID.
Course* CourseManagement::findCourse(const string& id) const {
    for (int i = 0; i < courseCount; ++i) {
        if (courses[i].id == id) {
            return &courses[i]; // Return a pointer to the course if found
        }
    }
    return nullptr; // Return nullptr if the course is not found
}

//Returns the list of enrolled students for a specific course.
vector<pair<string, string>> CourseManagement::getEnrolledStudents(const string& courseID) const {
    for (int i = 0; i < courseCount; ++i) {
        if (courses[i].id == courseID) {
            return courses[i].enrolledStudentsList; // Return the list of enrolled students (ID and Name)
        }
    }
    return {}; // Return an empty vector if the course is not found
}

//Get Course Count
int CourseManagement::getCourseCount() const {
    return courseCount;
}

//Get Course by Index
const Course* CourseManagement::getCourse(int index) const {
    if (index >= 0 && index < courseCount) {
        return &courses[index];
    }
    return nullptr;
}
