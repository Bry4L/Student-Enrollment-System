#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <string>

using namespace std;

class User {
public:
    string username;
    string password;
    string role;

    User(string uname, string pwd, string r) : username(uname), password(pwd), role(r) {}
};

// Node for linked list
struct UserNode {
    User* user;     // Pointer to a User object
    UserNode* next; // Pointer to the next node in the linked list

    UserNode(User* u) : user(u), next(nullptr) {} //Constructor for the UserNode structure
    ~UserNode() {
        delete user; // Delete the User object
    }
};

// Linked list to store users
class UserList {
public:
    UserNode* head;

    UserList() : head(nullptr) {}
    ~UserList(); // Destructor to clean up the linked list

    void loadUsersFromFile();
    void saveUsersToFile();
    bool isUsernameTaken(const string& username); // Check if username is already taken
    void registerUser(string username, string password, string role);
    User* loginUser();
    void updateAdmin();
    void deleteUser();
    void deleteUserByUsername(const string& username);
};

#endif
