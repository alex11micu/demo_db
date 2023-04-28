#include <iostream>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <odbcss.h>
#include "DAL.h"

using namespace std;


int main() {
    std::string connection_string = "Driver={ODBC Driver 17 for SQL Server};Server=localhost;Database=POO;Trusted_Connection=yes;";

    DAL db(connection_string);

    // Create a new user
    User newUser{ 1, "John Doeeee", "johndoeeee@example.com" };
    if (db.createUser(newUser)) {
        std::cout << "User created successfully.\n";
    }
    else {
        std::cout << "Error creating user.\n";
    }

    // Fetch user by ID
    User fetchedUser = db.getUserById(2);
    std::cout << "Fetched user: " << fetchedUser.id << ", " << fetchedUser.username << ", " << fetchedUser.email << '\n';

    // Update user
    fetchedUser.username = "Jake Doe";
    fetchedUser.email = "jakedoe@example.com";
    if (db.updateUser(fetchedUser)) {
        std::cout << "User updated successfully.\n";
    }
    else {
        std::cout << "Error updating user.\n";
    }

    // Fetch users by email
    std::vector<User> users = db.getUsersByEmail("janedoe@example.com");
    for (const auto& user : users) {
        std::cout << "User found: " << user.id << ", " << user.username << ", " << user.email << '\n';
    }

    // Delete user
    if (db.deleteUser(1)) {
        std::cout << "User deleted successfully.\n";
    }
    else {
        std::cout << "Error deleting user.\n";
    }

    return 0;
}


