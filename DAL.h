#pragma once
#include <iostream>
#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
#include <string>
#include "User.h"
#include <vector>
#include <iostream>
#include <string>
#include <vector>
#include <nanodbc.h>


using namespace std;

class DAL {
private:
    nanodbc::connection conn;

    void disconnect();
public:
        DAL(const string connectionString) : conn(connectionString) {}
        ~DAL(){}

        bool createUser(const User& user);
        User getUserById(int id);
        bool updateUser(const User& user);
        bool deleteUser(int id);
        vector<User> getUsersByEmail(const std::string& email);
};

