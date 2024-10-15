#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

// User class
class User {
private:
    string username;
    string password;

public:
    User(string username, string password) : username(username), password(password) {}

    string getUsername() { return username; }
    string getPassword() { return password; }
    void setUsername(string username) { this->username = username; }
    void setPassword(string password) { this->password = password; }

    bool isValidPassword() {
        // find in the file pass.txt if the password is correct
        ifstream file("pass.txt");
        if (!file.is_open()) {
            cout << "Error opening file" << endl;
            return false;
        }
        string line;
        string login = username + ":" + password;
        while (getline(file, line)) {
            if (line.find(login) != string::npos && username != "" && password != "" && login.size() == line.size()) {
            return true;
            }
        }
        return false;
    }
};


#endif