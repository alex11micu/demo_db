#include "DAL.h"




  

bool DAL::createUser(const User& user) {
    nanodbc::statement stmt(conn);
    nanodbc::prepare(stmt, R"(
            INSERT INTO users (username, email) VALUES (?, ?);
        )");

    
    stmt.bind(0, user.username.c_str());
    stmt.bind(1, user.email.c_str());
    nanodbc::result rez = stmt.execute();

    return rez.has_affected_rows();
}

User DAL::getUserById(int id) {
    User user;
    nanodbc::statement stmt(conn);
    nanodbc::prepare(stmt, R"(
        SELECT id, username, email FROM users WHERE id = ?;
    )");
    stmt.bind(0, &id);

    nanodbc::result result = stmt.execute();
    
    const short columns = result.columns();
    //cout << "\nDisplaying " << result.rowset_size() << " rows "
    //    << "(" << result.rowset_size() << " fetched at a time):" << endl;

    //// show the column names
    //cout << "row\t";
    //for (short i = 0; i < columns; ++i)
    //    cout << result.column_name(i) << "\t";
    //cout << endl;

    if (result.next()) {
        user.id = result.get<int>(0);
        user.username = result.get<std::string>(1);
        user.email = result.get<std::string>(2);
    }

    return user;
}

bool DAL::updateUser(const User& user) {
        nanodbc::statement stmt(conn);
        nanodbc::prepare(stmt, R"(
            UPDATE users SET username = ?, email = ? WHERE id = ?;
        )");

        stmt.bind(0, user.username.c_str());
        stmt.bind(1, user.email.c_str());
        stmt.bind(2, &user.id);

        nanodbc::result rez = stmt.execute();

        return rez.has_affected_rows();
    }

bool DAL::deleteUser(int id) {
        nanodbc::statement stmt(conn);
        nanodbc::prepare(stmt, R"(
            DELETE FROM users WHERE id = ?;
        )");

        stmt.bind(0, &id);

        nanodbc::result rez = stmt.execute();

        return rez.has_affected_rows();
    }

vector<User> DAL::getUsersByEmail(const std::string& email) 
{
        std::vector<User> users;
        nanodbc::statement stmt(conn);
        nanodbc::prepare(stmt, R"(
            SELECT id, username, email FROM users WHERE email LIKE ?;
        )");

        std::string email_pattern = "%" + email + "%";
        stmt.bind(0, email_pattern.c_str());

        nanodbc::result result = stmt.execute();

        while (result.next()) {
            User user;
            user.id = result.get<int>(0);
            user.username = result.get<std::string>(1);
            user.email = result.get<std::string>(2);
            users.push_back(user);
        }

        return users;
    }



void DAL::disconnect() {
    if (conn.connected()) {
        conn.disconnect();
        conn.deallocate();
    }
}


