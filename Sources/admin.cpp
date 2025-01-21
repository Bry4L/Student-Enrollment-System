#include "admin.h"
#include "student.h"
#include "instructor.h"
#include "course.h"
#include <iostream>
#include <limits>

using namespace std;

//Printing adminMenu function
void adminMenu(UserList& userList, vector<Student>& students, InstructorList& instructorList, CourseManagement& courseManagement, Stack& instructorStack) {
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
            //If not it will exist run time error
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
                    instructorList.addInstructor(userList); //add instructor function
                    break;
                case 2:
                    instructorList.updateInstructor(); //update instructor function
                    break;
                case 3:
                    instructorList.deleteInstructor(userList); //delete instructor function
                    break;
                case 4:
                    instructorList.viewInstructors(); //View instructor function
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
                // Course management
                int courseChoice;
                do {
                    cout << "\nCourse Management System" << endl;
                    cout << "1. Add Course" << endl;
                    cout << "2. Update Course" << endl;
                    cout << "3. Delete Course" << endl;
                    cout << "4. View All Courses" << endl;
                    cout << "5. Assign Course to Instructor" << endl;
                    cout << "6. View Instructor's Courses" << endl;
                    cout << "7. Return to Admin Menu" << endl;
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
            if (courseChoice < 1 || courseChoice > 7) {
                cout << "Invalid choice. Try again." << endl;
                continue; // Skip the rest of the loop and prompt again
            }
                    string id, name;
                    int maxSeats;
                    switch (courseChoice) {
                        case 1:
                            cout << "Enter Course ID: ";
                            cin >> id;
                            cout << "Enter Course Name: ";
                            cin.ignore();
                            getline(cin, name);
                            cout << "Enter Max Seats: ";
                            cin >> maxSeats;
                            courseManagement.addCourse(id, name, maxSeats);
                            break;
                        case 2:
                            cout << "Enter Course ID to update: ";
                            cin >> id;
                            cout << "Enter new name (leave blank to keep unchanged): ";
                            cin.ignore();
                            getline(cin, name);
                            cout << "Enter new max seats (0 to keep unchanged): ";
                            cin >> maxSeats;
                            courseManagement.updateCourse(id, name, maxSeats);
                            break;
                        case 3:
                            cout << "Enter Course ID to delete: ";
                            cin >> id;
                            courseManagement.deleteCourse(id);
                            break;
                        case 4:
                            courseManagement.viewAllCourses();
                            break;
                         case 5: {
                            // Assign course to instructor
                            string instructorID, courseID;
                            cout << "Enter Instructor ID: ";
                            cin.ignore(); // Clear the input buffer
                            getline(cin, instructorID);

                            // Check if the instructor exists
                            ifstream instructorFile("instructors.txt");
                            bool instructorExists = false;
                            string id, name, contactInfo;
                            while (instructorFile >> id >> name >> contactInfo) {
                                if (id == instructorID) {
                                    instructorExists = true;
                                    break;
                                }
                            }
                            instructorFile.close();

                            if (!instructorExists) {
                                cout << "Error: Instructor ID '" << instructorID << "' does not exist." << endl;
                                break;
                            }

                            cout << "Enter Course ID to assign to the instructor: ";
                            getline(cin, courseID);
                            // Check if the course exists
                            if (courseManagement.findCourse(courseID) == nullptr) {
                            cout << "Error: Course ID '" << courseID << "' does not exist." << endl;
                            break;
                            }

                            // Assign the course to the instructor
                            instructorStack.push(instructorID, courseID); // Pass both IDs
                            cout << "Course ID '" << courseID << "' assigned to instructor ID '" << instructorID << "'." << endl;
                                break;
                        }
                        case 6: {
                            // View instructor's courses
                             instructorStack.display(instructorList, courseManagement);
                            break;
                        }
                        case 7:
                            cout << "Returning to Admin Menu..." << endl;
                            break;
                        default:
                            cout << "Invalid choice. Try again." << endl;
                    }
                } while (courseChoice != 7);
                break;
            }
            case 4:
                userList.updateAdmin();
                break;
            case 5:
                userList.deleteUser();
                break;
           case 6: {
                int reportChoice;
                do {
                    cout << "\nGenerate Report Menu:" << endl;
                    cout << "1. Enrolled Students Report" << endl;
                    cout << "2. Available Courses Report" << endl;
                    cout << "3. Return to Admin Menu" << endl;
                    cout << "Enter your choice: ";
                    cin >> reportChoice;

                    switch (reportChoice) {
                        case 1:
                            generateEnrolledStudentsReport(courseManagement);
                            break;
                        case 2:
                            generateAvailableCoursesReport(courseManagement);
                            break;
                        case 3:
                            cout << "Returning to Admin Menu..." << endl;
                            break;
                        default:
                            cout << "Invalid choice. Try again." << endl;
                    }
                } while (reportChoice != 3);
                break;
            }
            case 7:
                cout << "Logging out..." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 7);
}


// Function to generate a report of enrolled students
void generateEnrolledStudentsReport(const CourseManagement& courseManagement) {
    ofstream reportFile("enrolled_students_report.txt"); //create and write a textfile called enrolled_students.txt
    if (reportFile.is_open()) {
        // Display header on console
        cout << "Enrolled Students Report\n";
        cout << "------------------------\n";

        // Write header to file
        reportFile << "Enrolled Students Report\n";
        reportFile << "------------------------\n";

        // Loop through all courses in the CourseManagement object
        for (int i = 0; i < courseManagement.getCourseCount(); ++i) {
            // Get the course at index 0 which is the first till the last of it
            const Course* course = courseManagement.getCourse(i);

            // Check if the course pointer is valid
            if (course) {
                // Display course details on console
                cout << "Course ID: " << course->id << ", Course Name: " << course->name << "\n";
                cout << "Enrolled Students: " << course->enrolledStudents << "\n";

                // Write course details to file
                reportFile << "Course ID: " << course->id << ", Course Name: " << course->name << "\n";
                reportFile << "Enrolled Students: " << course->enrolledStudents << "\n";

                // Check if there are enrolled students in the course
                if (course->enrolledStudents > 0) {
                    // Display enrolled students on console
                    cout << "List of Enrolled Students:\n";
                    for (const auto& student : course->enrolledStudentsList) {
                        cout << "Student ID: " << student.first << ", Student Name: " << student.second << "\n";
                    }

                    // Write enrolled students to file
                    reportFile << "List of Enrolled Students:\n";
                    for (const auto& student : course->enrolledStudentsList) {
                        reportFile << "Student ID: " << student.first << ", Student Name: " << student.second << "\n";
                    }
                } else {
                    // Display message if no students are enrolled
                    cout << "No students enrolled in this course.\n";

                    // Write message to file
                    reportFile << "No students enrolled in this course.\n";
                }

                // Display separator on console
                cout << "------------------------\n";

                // Write separator to file
                reportFile << "------------------------\n";
            }
        }
        reportFile.close();
        cout << "Enrolled students report generated successfully! (Saved to 'enrolled_students_report.txt')\n";
    } else {
        cerr << "Error: Unable to generate enrolled students report.\n";
    }

}


// Function to generate a report of available courses
void generateAvailableCoursesReport(const CourseManagement& courseManagement) {
    ofstream reportFile("available_courses_report.txt"); // Open a file for writing the available courses report
    if (reportFile.is_open()) {
        cout << "Available Courses Report\n"; // Display on console
        cout << "------------------------\n"; // Display on console
        reportFile << "Available Courses Report\n"; // Write to file
        reportFile << "------------------------\n"; // Write to file

        bool hasAvailableCourses = false; // Flag to check if there are any courses with available seats

        // Loop through all courses in the CourseManagement object
        for (int i = 0; i < courseManagement.getCourseCount(); ++i) {
            const Course* course = courseManagement.getCourse(i);
            if (course) {
                int availableSeats = course->maxSeats - course->enrolledStudents;

                // Only process courses with available seats
                if (availableSeats > 0) {
                    hasAvailableCourses = true;

                    // Display on console
                    cout << "Course ID: " << course->id << ", Course Name: " << course->name << "\n";
                    cout << "Max Seats: " << course->maxSeats << ", Available Seats: " << availableSeats << "\n";
                    cout << "------------------------\n";

                    // Write to file
                    reportFile << "Course ID: " << course->id << ", Course Name: " << course->name << "\n";
                    reportFile << "Max Seats: " << course->maxSeats << ", Available Seats: " << availableSeats << "\n";
                    reportFile << "------------------------\n";
                }
            }
        }

        if (!hasAvailableCourses) {
            // If no courses have available seats, display a message
            cout << "No courses with available seats found.\n";
            reportFile << "No courses with available seats found.\n";
        }

        reportFile.close();
        cout << "Available courses report generated successfully! (Saved to 'available_courses_report.txt')" << endl;
    } else {
        cerr << "Error: Unable to generate available courses report." << endl;
    }
}
