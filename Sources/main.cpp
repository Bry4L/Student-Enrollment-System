#include "authentication.h"
#include "admin.h"
#include "student.h"
#include "instructor.h"
#include "enroll.h"
#include <iostream>

using namespace std;


int main() {
    // Create instances of UserList, StudentList, and CourseList
    UserList userList;
    vector<Student> students;
    InstructorList instructorList;
    CourseManagement courseManagement;
    Stack instructorStack;


     // Initialize enrollment system
    EnrolledList enrolledList;
    initializeEnrolledList(enrolledList);

    WaitlistQueue waitlist;
    UndoStack undoStack;

    // Load users and instructors from file at startup
    loadStudentsFromFile();
    userList.loadUsersFromFile();
    instructorList.loadInstructorsFromFile();
    cout << "=====================================" << endl;
    cout << "       STUDENT ENROLLMENT SYSTEM     " << endl;
    cout << "=====================================" << endl;
    int choice;
    User* loggedInUser = nullptr;

    do {
        cout << "\nMain Menu:" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        // Handle invalid input for choice
        if (!(cin >> choice)) {
            cin.clear(); // Clear the error flag
            cin.ignore(1000, '\n'); // Discard invalid input (up to 1000 characters or until newline)
            cout << "Invalid input. Please enter a number." << endl;
            continue; // Skip the rest of the loop and prompt again
        }
        cin.ignore(1000, '\n'); // Clear the buffer after reading the choice

        switch (choice) {
              case 1: {
                string username, password;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                userList.registerUser(username, password, "admin"); // Default role is admin
                break;
            }
          case 2:
                loggedInUser = userList.loginUser();
                if (loggedInUser) {
                    if (loggedInUser->role == "admin") {
                        adminMenu(userList, students, instructorList, courseManagement, instructorStack);
                    } else if (loggedInUser->role == "instructor") {
                          instructorMenu(loggedInUser, instructorList, instructorStack, courseManagement);
                    } else if (loggedInUser->role == "student") {
                       // Retrieve the student's name from the students vector
                        string studentName = getStudentNameById(loggedInUser->username);
                        studentMenu(loggedInUser->username.c_str(), studentName.c_str(), enrolledList, courseManagement, waitlist, undoStack);
                    }
                }
                break;
            case 3:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 3);

    return 0;
}
