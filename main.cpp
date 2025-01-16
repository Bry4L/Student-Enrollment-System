#include "authentication.h"
#include "admin.h"
#include "student.h"
#include "instructor.h"
#include <iostream>

using namespace std;


int main() {
    // Create instances of UserList, StudentList, and CourseList
    UserList userList;
    StudentList studentList;
    InstructorList instructorList;
    //CourseList courseList;

    // Load users and instructors from file at startup
    userList.loadUsersFromFile();
    instructorList.loadInstructorsFromFile();

    cout << "----------Welcome-----------------" << endl;
    cout << "STUDENT ENROLLMENT SYSTEM" << endl;

    int choice;
    User* loggedInUser = nullptr;

    do {
        cout << "\nMain Menu:" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

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
                        adminMenu(userList, studentList, instructorList);
                    } else if (loggedInUser->role == "instructor") {
                        instructorMenu(); // Call the instructorMenu function
                    } else if (loggedInUser->role == "student") {
                        studentMenu();
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
