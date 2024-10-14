#include "Session.hpp"

// Helper function to extract cookies from environment variables
std::map<std::string, std::string> Session::parseCookies() {
    std::map<std::string, std::string> cookies;
    char* cookieEnv = getenv("HTTP_COOKIE");
    if (cookieEnv) {
        std::string cookieStr = cookieEnv;
        size_t pos = 0;
        while ((pos = cookieStr.find(";")) != std::string::npos) {
            std::string token = cookieStr.substr(0, pos);
            size_t equalPos = token.find("=");
            if (equalPos != std::string::npos) {
                std::string name = token.substr(0, equalPos);
                std::string value = token.substr(equalPos + 1);
                cookies[name] = value;
            }
            cookieStr.erase(0, pos + 1);
        }
    }
    return cookies;
}

// Set a session cookie with the specified value
void Session::setSessionCookie(const std::string& value) {
    sessionValue = value;
    std::cout << "Set-Cookie: " << cookieName << "=" << sessionValue << "; HttpOnly; Path=/\r\n";
}

// Retrieve session cookie from the request (if exists)
std::string Session::getSessionCookie() {
    auto cookies = parseCookies();
    if (cookies.find(cookieName) != cookies.end()) {
        return cookies[cookieName];
    }
    return "";
}

// Invalidate the session by removing the cookie
void Session::invalidateSession() {
    sessionValue = "";
    std::cout << "Set-Cookie: " << cookieName << "=; HttpOnly; Path=/; Max-Age=0\r\n";
}

// Check if session is valid
bool Session::isValidSession() {
    return !sessionValue.empty();
}

// method to cout a form for the login
void Session::coutLogin(){
    std::cout<< "<form action='index.cgi' method='post' class='add-form'>";
    std::cout<< "<div class='form-group'>";
    std::cout<< "<label for='name'>Name:</label>";
    std::cout<< "<input type='text' id='name' class='input-field' name='name' placeholder='Enter your name'>";
    std::cout<< "</div>";
    std::cout<< "<div class='form-group'>";
    std::cout<< "<label for='password'>Password:</label>";
    std::cout<< "<input type='password' id='password' class='input-field' name='password' placeholder='Enter your password'>";
    std::cout<< "</div>";
    std::cout<< "<div class='form-group'>";
    std::cout<< "<input type='submit' class='submit-btn' value='Login'>";
    std::cout<< "</div>";
    std::cout<< "</form>";
}

// method to cout a form for the logout
void Session::coutLogout(){
    std::cout<< "<form action='index.cgi' method='post' class='add-form'>";
    std::cout<< "<input type='hidden' name='status' value='logout'>";
    std::cout<< "<div class='form-group'>";
    std::cout<< "<input type='submit' class='submit-btn' value='Logout'>";
    std::cout<< "</div>";
    std::cout<< "</form>";
}

// method to check if the login and password are in the pass.txt
bool Session::isInTheData(const std::string login, const std::string password){
    std::string line;
    std::ifstream file("pass.txt");
    while (getline(file, line)) {
        if (line.find(login) != std::string::npos && line.find(password) != std::string::npos) { // nedd to by fixed later 
            return true;
        }
    }
    return false;
}

Session::Session(const std::string& name){
    cookieName = name;
    sessionValue = "";
    // if the session is already set in the cookie, we keep it
    if (isValidSession()) {
        setSessionCookie(sessionValue);
    } else {
        this->coutLogin();
    }
}