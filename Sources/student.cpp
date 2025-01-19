#include "student.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

// Vector to store students
vector<Student> students;

Node* head = nullptr;
// Insert a student into the linked list
void insertStudent(Node*& head, const Student& student) {
    Node* newNode = new Node();
    newNode->student = student;
    newNode->next = head;
    head = newNode;
}

// Delete a student from the linked list by ID
void deleteStudentFromList(Node*& head, const string& id) {
    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr) {
        if (current->student.id == id) {
            if (previous == nullptr) {
                // Deleting the head node
                head = current->next;
            } else {
                // Deleting a middle or last node
                previous->next = current->next;
            }
            delete current;
            return;
        }
        previous = current;
        current = current->next;
    }
}


// Add a new student
void addStudent(UserList& userList) {
    string id, name, ageOrContact;
    cout << "Enter Student ID: ";
    cin >> id;
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

    Student newStudent = {id, name, ageOrContact};
    students.push_back({id, name, ageOrContact});

    // Insert the student into the linked list
    insertStudent(head, newStudent);

    // Write the student's details to students.txt
    ofstream studentFile("students.txt", ios::app); // Open in append mode
    if (studentFile.is_open()) {
        studentFile << id << " " << name << " " << ageOrContact << endl;
        studentFile.close();
        cout << "Student details saved to students.txt." << endl;
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

            // Delete the student from the linked list
            deleteStudentFromList(head, id);
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

     sortStudents();
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
        cout << "Students saved to students.txt." << endl;
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

// Student menu
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
    } while (choice != 3);
}
