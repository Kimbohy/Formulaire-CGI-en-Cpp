#ifndef SESSION_HPP
#define SESSION_HPP

#include <string>
#include <iostream>
#include <fstream>

#include "User.hpp"

using namespace std;

// Session class
class Session {
private:
    User user;

public:
    Session(User user) : user(user) {}

    string getUsername() { return user.getUsername(); }

    bool isValid() { return user.isValidPassword(); } 
};

#endif