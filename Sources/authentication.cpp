#include "authentication.h"
#include <iostream>
#include <fstream>
#ifdef _WIN32
#include <conio.h> // For Windows
#endif

using namespace std;

// Function to hide password input
string getHiddenInput() {
    string input;
#ifdef _WIN32
    //read characters without displaying them
    char ch;
    while ((ch = _getch()) != '\r') { // '\r' is the Enter key on Windows
        if (ch == '\b') { // Handle backspace
            if (!input.empty()) {
                input.pop_back();
                cout << "\b \b"; // Move cursor back, overwrite with space, move back again
            }
        } else {
            input.push_back(ch);
            cout << '*'; // Display '*' for each character
        }
    }
#endif
    cout << endl; // Move to the next line after input
    return input;
}

// Destructor to clean up the linked list
UserList::~UserList() {
    UserNode* current = head; // Start from the head of the linked list

    //loop through the link list
    while (current != nullptr) {
        UserNode* temp = current; // Store the current node in a temporary pointer
        current = current->next; // Move to the next node
        delete temp; // Calls the destructor of UserNode, which deletes the User object
    }
}

// Load users from file
void UserList::loadUsersFromFile() {
    ifstream file("users.txt"); // Open the file for reading

    if (file.is_open()) {
        string username, password, role;
        // Read each line from the file and extract all the variables
        while (file >> username >> password >> role) {
            User* user = new User(username, password, role); // Create a new User object
            UserNode* newNode = new UserNode(user);          // Create a new UserNode containing the User

            // Add to the beginning of the linked list
            newNode->next = head;
            head = newNode; // Update the head to the new node
        }
        file.close(); // Close the file after reading all users
    } else {
        cerr << "Error: Unable to load users from file." << endl;
    }
}

// Save users to file
void UserList::saveUsersToFile() {
    ofstream file("users.txt"); // Open the file for writing
    if (file.is_open()) {
        UserNode* current = head;
        while (current != nullptr) {
                 // Write the user's data to the file
            file << current->user->username << " " << current->user->password << " " << current->user->role << endl;
            current = current->next;
        }
        file.close();
    } else {
        cerr << "Error: Unable to save users to file." << endl;
    }
}
// Check if username is already taken
bool UserList::isUsernameTaken(const string& username) {
    UserNode* current = head;
    while (current != nullptr) {
        if (current->user->username == username) {  // Check if the current node's username matches the input
            return true; // Username is already taken
        }
        current = current->next; // Move to the next node
    }
    return false; // Username not found in the list
}

// Register a new user
void UserList::registerUser(string username, string password, string role) {
    // Check if the username is already taken
    if (isUsernameTaken(username)) {
        cout << "Error: Username '" << username << "' is already taken. Please choose a different username." << endl;
        return;
    }
    // Create a new user and add a new node for the linked list
    User* user = new User(username, password, role); // Create a new User object
    UserNode* newNode = new UserNode(user);          // Create a new UserNode containing the User

    // Add to the beginning of the linked list
    newNode->next = head;
    head = newNode;  // Update the head to the new node

    // Save users to file
    saveUsersToFile();

    cout << "User registered successfully!" << endl;
}

// Login a user
User* UserList::loginUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin.ignore(); // Clear the input buffer
    password = getHiddenInput();    // this function masks user input for privacy

    //current pointer pointing at head pointer which is start of a link list
    UserNode* current = head;
    while (current != nullptr) {
        if (current->user->username == username && current->user->password == password) {   //Verify user username and password matches any of the stored record
            cout << "Login successful! Role: " << current->user->role << endl;
            return current->user; // Return the logged-in user
        }
        current = current->next; // Move to the next node in the list
    }
    cout << "Error: Invalid username or password." << endl;
    return nullptr;
}

// Update admin details
void UserList::updateAdmin() {
    string username;
    cout << "Enter admin username to update: ";
    cin >> username;

    UserNode* current = head;
    while (current != nullptr) {
        if (current->user->username == username && current->user->role == "admin") {  //Check the input username matches any of the record with condition of it's admin
            string newPassword;
            cout << "Enter new password: ";
            cin >> newPassword;
            current->user->password = newPassword; // Update the password
            saveUsersToFile(); // Save changes to file
            cout << "Admin updated successfully!" << endl;
            return;
        }
        current = current->next;
    }
    cout << "Error: Admin not found." << endl;
}

// Delete account
void UserList::deleteUser() {
    string username;
    cout << "Enter user's username to delete: ";
    cin >> username;

    UserNode* current = head; // Pointer to traverse the linked list, starting at the head
    UserNode* previous = nullptr; // Pointer to keep track of the previous node for linking adjustments

    //lookthrough the link list to find user
    while (current != nullptr) {
        // Check if the current node contains the user with the matching username
        if (current->user->username == username) {
            if (previous == nullptr) {
                // If the user is at the head of the list
                head = current->next;    // Update the head pointer to the next node
            } else {
                // Delete a middle or last node
                previous->next = current->next; // Skip over the current node
            }
        // Delete the current node to free memory
            delete current;
            saveUsersToFile(); // Save changes to file
            cout << "User deleted successfully!" << endl;
            return;
        }
         // Move to the next node
        previous = current; // Update previous to the current node
        current = current->next; // Move current to the next node in the list
    }
    cout << "Error: User not found." << endl;
}

// Function to delete a user by username (removes from users.txt)
void UserList::deleteUserByUsername(const string& username) {
    UserNode* current = head;
    UserNode* previous = nullptr;

    while (current != nullptr) {
        if (current->user->username == username) {
            if (previous == nullptr) {
                // Deleting the first node
                head = current->next;
            } else {
                // Deleting a middle or last node
                previous->next = current->next;
            }
            delete current; // Deleting the user node (and User object)

            // Save the updated user list to the file
            saveUsersToFile();

            cout << "User with username '" << username << "' deleted from users file." << endl;
            return;
        }
        previous = current;
        current = current->next;
    }
    cout << "Error: User not found." << endl; // If the user does not exist
}
