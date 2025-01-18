#include "student.h"
#include <iostream>
#include <string>

using namespace std;

// Destructor to clean up the linked list
StudentList::~StudentList() {
    StudentNode* current = head;
    while (current != nullptr) {
        StudentNode* temp = current;
        current = current->next;
        delete temp; // Calls the destructor of StudentNode, which deletes the Student object
    }
}

void StudentList::addStudent(UserList& userList) {
    string studentId, name, contactInfo;
    cout << "Enter student ID: ";
    cin >> studentId;
    cout << "Enter student name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter student contact info: ";
    getline(cin, contactInfo);

    Student* student = new Student(studentId, name, contactInfo);
    StudentNode* newNode = new StudentNode(student);

    // Add to the beginning of the linked list
    newNode->next = head;
    head = newNode;

   // Register the student's ID as username and password
    userList.registerUser(studentId, studentId, "student");

    cout << "Student added successfully!" << endl;
}

void StudentList::updateStudent() {
    string studentId;
    cout << "Enter student ID to update: ";
    cin >> studentId;

    StudentNode* current = head;
    while (current != nullptr) {
        if (current->student->studentId == studentId) {
            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, current->student->name);
            cout << "Enter new contact info: ";
            getline(cin, current->student->contactInfo);
            cout << "Student updated successfully!" << endl;
            return;
        }
        current = current->next;
    }
    cout << "Error: Student not found." << endl;
}

void StudentList::deleteStudent() {
    string studentId;
    cout << "Enter student ID to delete: ";
    cin >> studentId;

    StudentNode* current = head;
    StudentNode* previous = nullptr;

    while (current != nullptr) {
        if (current->student->studentId == studentId) {
            if (previous == nullptr) {
                // Delete the first node
                head = current->next;
            } else {
                // Delete a middle or last node
                previous->next = current->next;
            }
            delete current; // Calls the destructor of StudentNode
            cout << "Student deleted successfully!" << endl;
            return;
        }
        previous = current;
        current = current->next;
    }
    cout << "Error: Student not found." << endl;
}

void StudentList::viewStudents() {
    if (head == nullptr) {
        cout << "No students found." << endl;
        return;
    }

    StudentNode* current = head;
    while (current != nullptr) {
        cout << "ID: " << current->student->studentId << ", Name: " << current->student->name << ", Contact: " << current->student->contactInfo << endl;
        current = current->next;
    }
}

void studentMenu() {
    int choice;
    do {
        cout << "\nStudent Menu:" << endl;
        cout << "1. View Courses" << endl;
        cout << "2. Enroll in a Course" << endl;
        cout << "3. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "View Courses functionality not implemented yet." << endl;
                break;
            case 2:
                cout << "Enroll in a Course functionality not implemented yet." << endl;
                break;
            case 3:
                cout << "Logging out..." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 3); // Loop until the user chooses to logout
}
