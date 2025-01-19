#ifndef ADMIN_H
#define ADMIN_H

#include "authentication.h"
#include "student.h"
#include "instructor.h"
#include <vector>

void adminMenu(UserList& userList, vector<Student>& students, InstructorList& instructorList); // reference to the object contain list of all data //allow to perform

#endif
