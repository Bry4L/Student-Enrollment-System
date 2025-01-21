#include "instructor.h"
#include <iostream>

using namespace std;

// Display the Instructor Menu and handle user input
void instructorMenu(User* loggedInUser, InstructorList& instructorList, const Stack& instructorStack, const CourseManagement& courseManagement) {
    int choice;
    do {
        cout << "\nInstructor Menu:" << endl;
        cout << "1. View Assigned Courses" << endl;
        cout << "2. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Call the new function to view assigned courses
                instructorList.viewAssignedCourses(loggedInUser->username, instructorStack, courseManagement);
                break;
            case 2:
                cout << "Logging out..." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 2); // Loop until the user chooses to logout
}

// Destructor to clean up the linked list
InstructorList::~InstructorList() {
    InstructorNode* current = head;
    while (current != nullptr) {
        InstructorNode* temp = current;
        current = current->next;
        delete temp; // Calls the destructor of InstructorNode, which deletes the Instructor object
    }
}

// Load instructors from file and add them to the linked list
void InstructorList::loadInstructorsFromFile() {
    ifstream file("instructors.txt");
    if (file.is_open()) {
        string instructorId, name, contactInfo;

        while (file >> instructorId >> name >> contactInfo) {
            // Create a new Instructor object and node
            Instructor* instructor = new Instructor(instructorId, name, contactInfo);
            InstructorNode* newNode = new InstructorNode(instructor);

            // Add to the beginning of the linked list
            newNode->next = head;
            head = newNode;
        }
        file.close();
    } else {
        cerr << "Error: Unable to load instructors from file." << endl;
    }
}

// Save the list of instructors to a file
void InstructorList::saveInstructorsToFile() {
    ofstream file("instructors.txt");
    if (file.is_open()) {
        InstructorNode* current = head;
        while (current != nullptr) {
              // Write instructor data to the file
            file << current->instructor->instructorId << " "
                 << current->instructor->name << " "
                 << current->instructor->contactInfo << endl;
            current = current->next;
        }
        file.close();
    } else {
        cerr << "Error: Unable to save instructors to file." << endl;
    }
}

// Add a new instructor to the list and register them as a user
void InstructorList::addInstructor(UserList& userList) {
    string instructorId, name, contactInfo;
    cout << "Enter instructor ID: ";
    cin >> instructorId;
    cout << "Enter instructor name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter instructor contact info: ";
    getline(cin, contactInfo);

    // Create a new instructor and add to the linked list
    Instructor* instructor = new Instructor(instructorId, name, contactInfo);
    InstructorNode* newNode = new InstructorNode(instructor);

    // Add to the beginning of the linked list
    newNode->next = head;
    head = newNode;

    // Register the instructor's ID as username and password as a new user
    userList.registerUser(instructorId, instructorId, "instructor");

    // Save instructors to file after adding
    saveInstructorsToFile();

    cout << "Instructor added successfully!" << endl;
}

// Update the information of an existing instructor
void InstructorList::updateInstructor() {
    string instructorId;
    cout << "Enter instructor ID to update: ";
    cin >> instructorId;

    InstructorNode* current = head;
    while (current != nullptr) {
        if (current->instructor->instructorId == instructorId) {
            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, current->instructor->name);
            cout << "Enter new contact info: ";
            getline(cin, current->instructor->contactInfo);

            // Save instructors to file after updating
            saveInstructorsToFile();

            cout << "Instructor updated successfully!" << endl;
            return;
        }
        current = current->next;
    }
    cout << "Error: Instructor not found." << endl;
}

// Delete an instructor from the list by their ID
void InstructorList::deleteInstructor(UserList& userList) {
    string instructorId;
    cout << "Enter instructor ID to delete: ";
    cin >> instructorId;

    InstructorNode* current = head;
    InstructorNode* previous = nullptr;

    while (current != nullptr) {
        if (current->instructor->instructorId == instructorId) {
            if (previous == nullptr) {
                // Delete the first node
                head = current->next;
            } else {
                // Delete a middle or last node
                previous->next = current->next;
            }
            delete current; // Calls the destructor of InstructorNode

            // Save instructors to file after deleting
            saveInstructorsToFile();

            // Now, delete the user entry (if it exists) from users.txt
            userList.deleteUserByUsername(instructorId);

            cout << "Instructor deleted successfully!" << endl;
            return;
        }
        previous = current;
        current = current->next;
    }
    cout << "Error: Instructor not found." << endl;
}

// View the list of all instructors in the system
void InstructorList::viewInstructors() {
    if (head == nullptr) {
        cout << "No instructors found." << endl;
        return;
    }

    InstructorNode* current = head;
    while (current != nullptr) {
        // Display instructor information
        cout << "ID: " << current->instructor->instructorId << ", Name: " << current->instructor->name << ", Contact: " << current->instructor->contactInfo << endl;
        current = current->next;
    }
}

//Displays the courses assigned to a specific instructor, along with the enrolled students in each course.
void InstructorList::viewAssignedCourses(const string& instructorId, const Stack& instructorStack, const CourseManagement& courseManagement) {
    cout << "Assigned Courses for Instructor ID: " << instructorId << endl;
    cout << "-----------------------------------" << endl;

    bool found = false;

    // Use peekAll to get all assignmentsOfInstructed Course without modifying the stack
    vector<InstructorCourseAssignment> assignments = instructorStack.peekAll();

    // Loops through the assignments
    for (const auto& assignment : assignments) {
        if (assignment.instructorID == instructorId) {
            found = true;
            string courseID = assignment.courseID;
            Course* course = courseManagement.findCourse(courseID); //use the function find course defined in course.cpp to store into the object

            if (course != nullptr) {
                cout << "Course ID: " << course->id << ", Course Name: " << course->name << endl;
                cout << "Enrolled Students: " << course->enrolledStudents << endl;

                // Display enrolled students (if any)
                if (course->enrolledStudents > 0) {
                    cout << "List of Enrolled Students:" << endl;
                    for (const auto& student : course->enrolledStudentsList) {
                        cout << "Student ID: " << student.first << ", Student Name: " << student.second << endl;
                    }
                } else {
                    cout << "No students enrolled in this course." << endl;
                }
                cout << "-----------------------------------" << endl;
            }
        }
    }

    if (!found) {
        cout << "No courses assigned to this instructor." << endl;
    }
}
