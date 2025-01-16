#include "admin.h"
#include "instructor.h"
#include <iostream>

using namespace std;

//Printing adminMenu function
void adminMenu(UserList& userList, StudentList& studentList, InstructorList& instructorList) {
    int choice;
    do {
        cout << "\nAdmin Menu:" << endl;
        cout << "1. Manage Students" << endl;
        cout << "2. Manage Instructors" << endl;
        cout << "3. Manage Courses" << endl;
        cout << "4. Update Admin" << endl;
        cout << "5. Delete Admin" << endl;
        cout << "6. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int studentChoice;
                do {
                    //Student Management Menu
                    cout << "\nStudent Management Menu:" << endl;
                    cout << "1. Add Student" << endl;
                    cout << "2. Update Student" << endl;
                    cout << "3. Delete Student" << endl;
                    cout << "4. Return to Admin Menu" << endl;
                    cout << "Enter your choice: ";
                    cin >> studentChoice;

                    switch (studentChoice) {
                        case 1:
                            studentList.addStudent(userList);
                            break;
                        case 2:
                            studentList.updateStudent();
                            break;
                        case 3:
                            studentList.deleteStudent();
                            break;
                        case 4:
                            cout << "Returning to Admin Menu..." << endl;
                            break;
                        default:
                            cout << "Invalid choice. Try again." << endl;
                    }
                } while (studentChoice != 4);
                break;
            }
            case 2: {
                int instructorChoice;
                do {
                    //Instructor Management Menu
                    cout << "\nInstructor Management Menu:" << endl;
                    cout << "1. Add Instructor" << endl;
                    cout << "2. Update Instructor" << endl;
                    cout << "3. Delete Instructor" << endl;
                    cout << "4. View Instructors" << endl;
                    cout << "5. Return to Admin Menu" << endl;
                    cout << "Enter your choice: ";
                    cin >> instructorChoice;

                    switch (instructorChoice) {
                        case 1:
                            instructorList.addInstructor(userList);
                            break;
                        case 2:
                            instructorList.updateInstructor();
                            break;
                        case 3:
                            instructorList.deleteInstructor(userList);
                            break;
                        case 4:
                            instructorList.viewInstructors();
                            break;
                        case 5:
                            cout << "Returning to Admin Menu..." << endl;
                            break;
                        default:
                            cout << "Invalid choice. Try again." << endl;
                    }
                } while (instructorChoice != 5);
                break;
            }
            case 3: {
                int courseChoice;
                do {
                    //Course Managemenrt
                    cout << "\nCourse Management Menu:" << endl;
                    cout << "1. Add Course" << endl;
                    cout << "2. Update Course" << endl;
                    cout << "3. Delete Course" << endl;
                    cout << "4. Return to Admin Menu" << endl;
                    cout << "Enter your choice: ";
                    cin >> courseChoice;

                    switch (courseChoice) {
                        case 1:
                            //courseList.addCourse();
                            break;
                        case 2:
                            //courseList.updateCourse();
                            break;
                        case 3:
                            //courseList.deleteCourse();
                            break;
                        case 4:
                            cout << "Returning to Admin Menu..." << endl;
                            break;
                        default:
                            cout << "Invalid choice. Try again." << endl;
                    }
                } while (courseChoice != 4);
                break;
            }
            case 4:
                userList.updateAdmin();
                break;
            case 5:
                userList.deleteUser();
                break;
            case 6:
                cout << "Logging out..." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 6);
}
