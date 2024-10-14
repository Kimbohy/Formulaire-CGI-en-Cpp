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
        while (getline(file, line)) {

            if (line.find(username + ":" + password) != string::npos && username != "" && password != "") {
            return true;
            }
        }
        return false;
    }
};

// Session class
class Session {
private:
    User user;

public:
    Session(User user) : user(user) {}

    string getUsername() { return user.getUsername(); }

    bool isValid() { return user.isValidPassword(); } 
};

int main() {
    string username, password, request;

    // Display the login form
    cout << "Content-type: text/html\r\n\r\n";
    cout << "<link rel='stylesheet' href='style.css'></head><body>";
    cout << "<html><body>";
    cout << "<form action='login.cgi' method='post' class='add-form' >";

    cout << "<div class='form-group'>";
    cout << "<label for='username'>Username:</label>";
    cout << "<input type='text' name='username'>";
    cout << "</div>";

    cout << "<div class='form-group'>";
    cout << "<label for='password'>Password:</label>";
    cout << "<input type='password' name='password'>";
    cout << "</div>";

    cout << "<div class='form-group'>";
    cout << "<input type='submit' value='Login' class='submit-btn'>";
    cout << "</div>";

    cout << "</form>";
    cout << "</body></html>";

    // Handle the login form submission
    cin >> request; //username=test&password=test
    size_t pos = request.find("&");
    username = request.substr(0, pos);
    password = request.substr(pos + 1);
    username = username.substr(username.find("=") + 1);
    password = password.substr(password.find("=") + 1);
    
    User user(username, password);
    Session session(user);
    if (session.isValid()) {
        // Set the session cookie (not implemented in this example)
        // cout << "Content-type: text/html\r\n\r\n";
        cout << "<html><body>";
        // redirection to index.cgi
        cout << "<script>window.location.replace('setSession.cgi?session=" << username << "');</script>";
        cout << "</body></html>";
    } else if (username != "" && password != "")
     {
        // Invalid login credentials
        // cout << "Content-type: text/html\r\n\r\n";
        cout << "<html><body>";
        cout << "Invalid login credentials. Please try again.";
        cout << "</body></html>";
    }

    return 0;
}