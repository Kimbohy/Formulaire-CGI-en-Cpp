#include "Session.hpp"

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