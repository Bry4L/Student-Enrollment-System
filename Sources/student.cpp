#include "student.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <limits>

using namespace std;

// Vector to store students
vector<Student> students;

// Head of the linked list for students
Node* head = nullptr;

//Validation on creation of studentID
bool isValidStudentID(const char* studentID) {
    if (strlen(studentID) != 10) { // ID must be exactly 10 characters long
        return false;
    }
    for (int i = 0; i < 10; i++) {
        if (!isdigit(studentID[i])) {
            return false; // Each character must be a digit
        }
    }
    return true;
}

// Add a new student
void addStudent(UserList& userList) {
    string id, name, ageOrContact;
    cout << "Enter Student ID: ";
    cin >> id;

        // Validate student ID
    if (!isValidStudentID(id.c_str())) {
        cout << "Error: Student ID must be exactly 10 digits.\n";
        return;
    }

    for (const auto& student : students) {
        if (student.id == id) {
            cout << "Student with this ID already exists!" << endl;
            return;
        }
    }
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Age/Contact Info (optional): ";
    getline(cin, ageOrContact);

     // Create a new student and add to the vector
    Student newStudent = {id, name, ageOrContact};
    students.push_back({id, name, ageOrContact});

    // Write the student's details to students.txt
    ofstream studentFile("students.txt", ios::app); // Open in append mode
    if (studentFile.is_open()) {
        studentFile << id << " " << name << " " << ageOrContact << endl;
        studentFile.close();

    } else {
        cerr << "Error: Unable to open students.txt for writing." << endl;
    }

    // Register the student as a user
    userList.registerUser(id, id, "student");

    // Save students to file
    saveStudentsToFile();

    cout << "Student added successfully!" << endl;
}

// Update a student's details
void updateStudent() {
    string id;
    cout << "Enter Student ID to update: ";
    cin >> id;
    for (auto& student : students) {
        if (student.id == id) {
            cout << "Enter new Name: ";
            cin.ignore();
            getline(cin, student.name);
            cout << "Enter new Age/Contact Info (optional): ";
            getline(cin, student.ageOrContact);

            // Save students to file
            saveStudentsToFile();

            cout << "Student updated successfully!" << endl;
            return;
        }
    }
    cout << "Student ID not found!" << endl;
}

// Delete a student by ID
void deleteStudent(UserList& userList) {
    string id;
    cout << "Enter Student ID to delete: ";
    cin >> id;
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->id == id) {
            students.erase(it);

            // Save students to file
            saveStudentsToFile();

            // Delete the corresponding user from users.txt
            userList.deleteUserByUsername(id);

            cout << "Student deleted successfully!" << endl;
            return;
        }
    }
    cout << "Student ID not found!" << endl;
}

// Search for a student by ID or name
void searchStudent() {
    string query;
    cout << "Enter Student ID or Name to search: ";
    cin.ignore();
    getline(cin, query);

    bool found = false;

    // Check if the linked list is available (not empty)
    if (head != nullptr) {
        // Search using the linked list
        Node* current = head;

        while (current != nullptr) {
            if (current->student.id == query || current->student.name == query) {
                cout << "Student Found!!!!" << endl;
                cout << "Student ID: " << current->student.id
                     << ", Name: " << current->student.name
                     << ", Age/Contact: " << current->student.ageOrContact << endl;
                found = true;
            }
            current = current->next;
        }
    } else {
        // Search using the file
        ifstream file("students.txt"); // Open the file for reading
        if (!file.is_open()) {
            cerr << "Error: Unable to open students.txt for reading." << endl;
            return;
        }

        string id, name, ageOrContact;

        // Read the file line by line
        while (file >> id >> name >> ageOrContact) {
            // Check if the current line matches the query
            if (id == query || name == query) {
                cout << "Student Found!!!!" << endl;
                cout << "Student ID: " << id
                     << ", Name: " << name
                     << ", Age/Contact: " << ageOrContact << endl;
                found = true;
            }
        }

        file.close();
    }

    if (!found) {
        cout << "Student not found!" << endl;
    }
}

//Sort function using merge sort by sorting student by their id
void merge(vector<Student>& students, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Student> leftArray(n1), rightArray(n2);

    for (int i = 0; i < n1; i++)
        leftArray[i] = students[left + i];
    for (int i = 0; i < n2; i++)
        rightArray[i] = students[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArray[i].id <= rightArray[j].id) {
            students[k] = leftArray[i];
            i++;
        } else {
            students[k] = rightArray[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        students[k] = leftArray[i];
        i++;
        k++;
    }

    while (j < n2) {
        students[k] = rightArray[j];
        j++;
        k++;
    }
}

void mergeSort(vector<Student>& students, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(students, left, mid);
        mergeSort(students, mid + 1, right);
        merge(students, left, mid, right);
    }
}

void sortStudents() {
    if (students.empty()) {
        return;
    }
    mergeSort(students, 0, students.size() - 1);
}

// View all students
void viewStudents() {

     sortStudents(); // Sort students before displaying
    if (students.empty()) {
        cout << "No students enrolled yet." << endl;
        return;
    }
    cout << "\nList of All Students:\n";
    for (const auto& student : students) {
        cout << "ID: " << student.id << ", Name: " << student.name
             << ", Age/Contact: " << student.ageOrContact << endl;
    }
}

// Save the list of students to a file
void saveStudentsToFile() {
    ofstream file("students.txt"); // Open the file for writing
    if (file.is_open()) {
        for (const auto& student : students) {
            // Write student data to the file
            file << student.id << " "
                 << student.name << " "
                 << student.ageOrContact << endl;
        }
        file.close();
    } else {
        cerr << "Error: Unable to save students to file." << endl;
    }
}

void loadStudentsFromFile() {
    ifstream file("students.txt"); // Open the file for reading
    if (file.is_open()) {
        string id, name, ageOrContact;
        while (file >> id >> name >> ageOrContact) {
            students.push_back({id, name, ageOrContact});
        }
        file.close();

    } else {
        cerr << "Error: Unable to open students.txt for reading." << endl;
    }
}

string getStudentNameById(const string& studentID) {
    for (const auto& student : students) {
        if (student.id == studentID) {
            return student.name;
        }
    }
    return "Unknown"; // Return a default value if the student is not found
}

void studentMenu(const char* studentID, const char* studentName, EnrolledList& enrolledList, CourseManagement& courseManagement, WaitlistQueue& waitlist, UndoStack& undoStack) {
    int choice;
    char courseID[10];
    string searchTerm;
    do {
        cout << "\nStudent Menu:" << endl;
        cout << "1. View All Courses" << endl;
        cout << "2. Enroll in a Course" << endl;
        cout << "3. Drop a Course" << endl;
        cout << "4. View Enrolled Courses" << endl;
        cout << "5. Search for a Course" << endl;
        cout << "6. View Waitlist for a Course" << endl;
        cout << "7. Undo Last Action" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";


        // Check if the input is valid
        if (!(cin >> choice)) {
            cin.clear(); // Clear the error state of cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input in the buffer
            cout << "Invalid choice. Try again." << endl;
            continue; // Skip the rest of the loop and prompt again
        }

        // Check if the input is within the valid range
        if (choice < 1 || choice > 8) {
            cout << "Invalid choice. Try again." << endl;
            continue; // Skip the rest of the loop and prompt again
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the buffer after reading the choice
        switch (choice) {
            case 1:
                courseManagement.viewAllCourses();
                break;
            case 2:
                cout << "Enter Course ID to enroll: ";
                cin >> courseID;
                enrollStudent(enrolledList, courseManagement, waitlist, undoStack, studentID, studentName, courseID);
                break;
            case 3:
                cout << "Enter Course ID to drop: ";
                cin >> courseID;
                dropCourse(enrolledList, courseManagement, waitlist, undoStack, studentID, courseID);
                break;
            case 4:
                displayEnrolledCourses(enrolledList, studentID);
                break;
            case 5:
                  cout << "Enter Course ID or Name to search: ";
                getline(cin, searchTerm); // Use getline for safer input
                searchCourse(courseManagement, searchTerm.c_str()); // Convert to const char*
                break;
            case 6:
                cout << "Enter Course ID to view waitlist: ";
                cin >> courseID;
                displayWaitlist(waitlist, courseID);
                break;
            case 7:
                cout << "Undoing last action..." << endl;
                undoStack.pop(enrolledList, courseManagement, waitlist);
                break;
            case 8:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 8);
}
