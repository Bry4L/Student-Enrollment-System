#include "admin.h"
#include "student.h"
#include "instructor.h"
#include <iostream>
#include <limits>

using namespace std;

//Printing adminMenu function
void adminMenu(UserList& userList, vector<Student>& students, InstructorList& instructorList) {
    int choice;
    do {
        cout << "\nAdmin Menu:" << endl;
        cout << "1. Manage Students" << endl;
        cout << "2. Manage Instructors" << endl;
        cout << "3. Manage Courses" << endl;
        cout << "4. Update Admin" << endl;
        cout << "5. Delete Admin" << endl;
        cout << "6. Generate Report" << endl;
        cout << "7. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

   switch (choice) {
    case 1: {
        int studentChoice;
        do {
            // Student Management Menu
            cout << "\nStudent Management Menu:" << endl;
            cout << "1. Add Student" << endl;
            cout << "2. Update Student" << endl;
            cout << "3. Delete Student" << endl;
            cout << "4. View Students" << endl;
            cout << "5. Search Students" << endl;
            cout << "6. Return to Admin Menu" << endl;
            cout << "Enter your choice: ";

            // Check if the input is valid
            if (!(cin >> studentChoice)) {
                // Clear the error state of cin
                cin.clear();
                // Ignore invalid input in the buffer
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid choice. Try again." << endl;
                continue; // Skip the rest of the loop and prompt again
            }

            // Check if the input is within the valid range
            if (studentChoice < 1 || studentChoice > 6) {
                cout << "Invalid choice. Try again." << endl;
                continue; // Skip the rest of the loop and prompt again
            }

            switch (studentChoice) {
                case 1:
                    addStudent(userList); // Add student
                    break;
                case 2:
                    updateStudent(); // Update student
                    break;
                case 3:
                    deleteStudent(userList); // Delete student
                    break;
                case 4:
                    viewStudents(); // View students
                    break;
                case 5:
                    searchStudent(); // Search students
                    break;
                case 6:
                    cout << "Returning to Admin Menu..." << endl;
                    break;
                default:
                    // This should never be reached because of the range check above
                    cout << "Invalid choice. Try again." << endl;
            }
        } while (studentChoice != 6);
        break;
    }
    case 2: {
        int instructorChoice;
        do {
            // Instructor Management Menu
            cout << "\nInstructor Management Menu:" << endl;
            cout << "1. Add Instructor" << endl;
            cout << "2. Update Instructor" << endl;
            cout << "3. Delete Instructor" << endl;
            cout << "4. View Instructors" << endl;
            cout << "5. Return to Admin Menu" << endl;
            cout << "Enter your choice: ";

            // Check if the input is valid
            if (!(cin >> instructorChoice)) {
                // Clear the error state of cin
                cin.clear();
                // Ignore invalid input in the buffer
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid choice. Try again." << endl;
                continue; // Skip the rest of the loop and prompt again
            }

            // Check if the input is within the valid range
            if (instructorChoice < 1 || instructorChoice > 5) {
                cout << "Invalid choice. Try again." << endl;
                continue; // Skip the rest of the loop and prompt again
            }

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
                    // This should never be reached because of the range check above
                    cout << "Invalid choice. Try again." << endl;
            }
        } while (instructorChoice != 5);
        break;
    }
    case 3: {
        int courseChoice;
        do {
            // Course Management Menu
            cout << "\nCourse Management Menu:" << endl;
            cout << "1. Add Course" << endl;
            cout << "2. Update Course" << endl;
            cout << "3. Delete Course" << endl;
            cout << "4. Return to Admin Menu" << endl;
            cout << "Enter your choice: ";

            // Check if the input is valid
            if (!(cin >> courseChoice)) {
                // Clear the error state of cin
                cin.clear();
                // Ignore invalid input in the buffer
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid choice. Try again." << endl;
                continue; // Skip the rest of the loop and prompt again
            }

            // Check if the input is within the valid range
            if (courseChoice < 1 || courseChoice > 4) {
                cout << "Invalid choice. Try again." << endl;
                continue; // Skip the rest of the loop and prompt again
            }

            switch (courseChoice) {
                case 1:
                    // courseList.addCourse();
                    break;
                case 2:
                    // courseList.updateCourse();
                    break;
                case 3:
                    // courseList.deleteCourse();
                    break;
                case 4:
                    cout << "Returning to Admin Menu..." << endl;
                    break;
                default:
                    // This should never be reached because of the range check above
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
                cout << "Generate Report function to be implemented..." << endl;
                break;
            case 7:
                cout << "Logging out..." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 7);
}
