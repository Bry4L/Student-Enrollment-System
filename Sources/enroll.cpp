#include "enroll.h"

// Function implementations for WaitlistQueue
bool WaitlistQueue::isEmpty() {
    return front == nullptr;
}

void WaitlistQueue::enqueue(const char* studentID, const char* studentName, const char* courseID, const char* courseName) {
    EnrollmentNode* newNode = new EnrollmentNode();
    strcpy(newNode->studentID, studentID);
    strcpy(newNode->studentName, studentName); // Ensure this is correct
    strcpy(newNode->courseID, courseID);
    strcpy(newNode->courseName, courseName);
    newNode->next = nullptr;

    if (isEmpty()) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    cout << "Student added to the waitlist." << endl;
}

void WaitlistQueue::dequeue() {
    if (isEmpty()) {
        cout << "Waitlist is empty." << endl;
        return;
    }
    EnrollmentNode* temp = front;
    front = front->next;
    delete temp;
    if (front == nullptr) {
        rear = nullptr;
    }
}

EnrollmentNode* WaitlistQueue::getFrontNode() {
    return front;
}

// Function implementations for UndoStack
bool UndoStack::isEmpty() {
    return top == nullptr;
}

void UndoStack::push(const char* actionType, const char* studentID, const char* courseID) {
    Action* newAction = new Action();
    strcpy(newAction->actionType, actionType);
    strcpy(newAction->studentID, studentID);
    strcpy(newAction->courseID, courseID);
    newAction->next = top;
    top = newAction;
}

void UndoStack::pop(EnrolledList& list, CourseManagement& courseManagement, WaitlistQueue& waitlist) {
    if (isEmpty()) {
        cout << "No actions to undo." << endl;
        return;
    }

    Action* temp = top;
    top = top->next;

    // Reverse the action
    if (strcmp(temp->actionType, "Enroll") == 0) {
        // Reverse an "Enroll" action by dropping the student
        dropCourse(list, courseManagement, waitlist, *this, temp->studentID, temp->courseID);
        cout << "Undo: Student " << temp->studentID << " dropped from course " << temp->courseID << endl;
    } else if (strcmp(temp->actionType, "Drop") == 0) {
        // Reverse a "Drop" action by re-enrolling the student
        Course* course = courseManagement.findCourse(temp->courseID);
        if (course != nullptr) {
            enrollStudent(list, courseManagement, waitlist, *this, temp->studentID, "Unknown", temp->courseID);
            cout << "Undo: Student " << temp->studentID << " re-enrolled in course " << temp->courseID << endl;
        } else {
            cout << "Course not found. Cannot undo action." << endl;
        }
    }

    delete temp; // Free memory
}

const char* UndoStack::getTopAction() {
    if (isEmpty()) {
        return nullptr;
    }
    return top->actionType;
}

// Other function implementations
void initializeEnrolledList(EnrolledList& list) {
    list.head = nullptr;
}

bool isValidStudentID(const char* studentID) {
    if (strlen(studentID) != 10) {
        return false;
    }
    for (int i = 0; i < 10; i++) {
        if (!isdigit(studentID[i])) {
            return false;
        }
    }
    return true;
}

bool isUniqueStudentID(EnrolledList& list, const char* studentID) {
    EnrollmentNode* temp = list.head;
    while (temp != nullptr) {
        if (strcmp(temp->studentID, studentID) == 0) {
            return false;
        }
        temp = temp->next;
    }
    return true;
}

void displayEnrolledCourses(EnrolledList& list, const char* studentID) {
    EnrollmentNode* temp = list.head;
    bool found = false;
    cout << "\nCourses Enrolled by Student " << studentID << ":" << endl;
    cout << "-----------------------------" << endl;
    while (temp != nullptr) {
        if (strcmp(temp->studentID, studentID) == 0) {
            cout << "Course ID: " << temp->courseID << ", Course Name: " << temp->courseName << endl;
            found = true;
        }
        temp = temp->next;
    }
    if (!found) {
        cout << "No courses enrolled." << endl;
    }
    cout << "-----------------------------" << endl;
}

void displayWaitlist(WaitlistQueue& waitlist, const char* courseID) {
    EnrollmentNode* temp = waitlist.front;
    bool found = false;
    cout << "\nWaitlist for Course " << courseID << ":" << endl;
    cout << "-----------------------------" << endl;
    while (temp != nullptr) {
        if (strcmp(temp->courseID, courseID) == 0) {
            cout << "Student ID: " << temp->studentID << ", Student Name: " << temp->studentName << endl;
            found = true;
        }
        temp = temp->next;
    }
    if (!found) {
        cout << "No students in the waitlist for this course." << endl;
    }
    cout << "-----------------------------" << endl;
}

void enrollStudent(EnrolledList& list, CourseManagement& courseManagement, WaitlistQueue& waitlist, UndoStack& undoStack, const char* studentID, const char* studentName, const char* courseID) {
    // Check if the student is already enrolled in the same course
    EnrollmentNode* temp = list.head;
    while (temp != nullptr) {
        if (strcmp(temp->studentID, studentID) == 0 && strcmp(temp->courseID, courseID) == 0) {
            cout << "Student is already enrolled in this course!" << endl;
            return;
        }
        temp = temp->next;
    }

    Course* course = courseManagement.findCourse(courseID);
    if (course == nullptr) {
        cout << "\nCourse not found!" << endl;
        return;
    }

    if (course->enrolledStudents >= course->maxSeats) {
        cout << "\nThe course is full. Adding student to the waitlist." << endl;
        waitlist.enqueue(studentID, studentName, courseID, course->name.c_str());
        return;
    }

    // Add the student to the course's enrolled students list
    course->enrolledStudentsList.push_back({studentID, studentName});
    course->enrolledStudents++;

    // Add the student to the enrolled list
    EnrollmentNode* newStudent = new EnrollmentNode();
    strcpy(newStudent->studentID, studentID);
    strcpy(newStudent->studentName, studentName);
    strcpy(newStudent->courseID, courseID);
    strcpy(newStudent->courseName, course->name.c_str());
    newStudent->next = list.head;
    list.head = newStudent;

    // Record the enrollment action in the undo stack
    undoStack.push("Enroll", studentID, courseID);

    cout << "\nStudent enrolled successfully! (Available Seats: " << course->maxSeats - course->enrolledStudents << ")" << endl;
}

void dropCourse(EnrolledList& list, CourseManagement& courseManagement, WaitlistQueue& waitlist, UndoStack& undoStack, const char* studentID, const char* courseID) {
    EnrollmentNode* temp = list.head;
    EnrollmentNode* prev = nullptr;
    bool found = false;

    while (temp != nullptr) {
        if (strcmp(temp->studentID, studentID) == 0 && strcmp(temp->courseID, courseID) == 0) {
            found = true;
            if (prev == nullptr) {
                list.head = temp->next;
            } else {
                prev->next = temp->next;
            }
            delete temp;

            // Update the course's enrolled student count
            Course* course = courseManagement.findCourse(courseID);
            if (course != nullptr) {
                course->enrolledStudents--;
                cout << "\nStudent dropped from the course successfully! (Available Seats: " << course->maxSeats - course->enrolledStudents << ")" << endl;

                // Enroll the next student from the waitlist for the same course
                if (!waitlist.isEmpty()) {
                    EnrollmentNode* waitlistStudent = waitlist.getFrontNode();
                    if (waitlistStudent != nullptr && isValidStudentID(waitlistStudent->studentID) && strcmp(waitlistStudent->courseID, courseID) == 0) {
                        cout << "Enrolling next student from the waitlist: " << waitlistStudent->studentID << endl;

                        // Enroll the student
                        enrollStudent(list, courseManagement, waitlist, undoStack, waitlistStudent->studentID, waitlistStudent->studentName, waitlistStudent->courseID);

                        // Remove the student from the waitlist
                        waitlist.dequeue();
                    } else {
                        cout << "No valid student in the waitlist for this course." << endl;
                    }
                }
            }
            undoStack.push("Drop", studentID, courseID); // Record the action in the undo stack
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    if (!found) {
        cout << "\nStudent not found in this course." << endl;
    }
}

void searchCourse(CourseManagement& courseManagement, const char* searchTerm) {
    Course* course = courseManagement.findCourse(searchTerm);
    if (course != nullptr) {
        cout << "\nSearch Results:" << endl;
        cout << "-----------------------------" << endl;
        cout << "Course ID: " << course->id << ", Course Name: " << course->name
             << ", Available Seats: " << course->maxSeats - course->enrolledStudents << endl;
        cout << "-----------------------------" << endl;
    } else {
        cout << "\nNo matching courses found." << endl;
    }
}

void cleanupEnrolledList(EnrolledList& list) {
    EnrollmentNode* temp = list.head;
    while (temp != nullptr) {
        EnrollmentNode* next = temp->next;
        delete temp;
        temp = next;
    }
    list.head = nullptr;
}
