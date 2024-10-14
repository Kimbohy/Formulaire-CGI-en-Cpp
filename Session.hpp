#ifndef SESSION_H
#define SESSION_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <map>

class Session {
private:
    std::string cookieName;
    std::string sessionValue;

public:
    Session(const std::string& name);

    std::string getCookieValue(const std::string &cookieName);

    bool hasCookie(const std::string &cookieName);

    // Set a session cookie with the specified value
    void setSessionCookie(const std::string& value);

    // Retrieve session cookie from the request (if exists)
    std::string getSessionCookie();

    // Invalidate the session by removing the cookie
    void invalidateSession();

    void coutLogin();

    void coutLogout();

    bool isInTheData(const std::string login, const std::string password);
};

#endif
