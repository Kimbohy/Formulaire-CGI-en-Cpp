#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>

using namespace std;

// Function to decode URL encoded strings
string urlDecode(const string& src) {
    string result;
    for (size_t i = 0; i < src.length(); i++) {
        if (src[i] == '+') {
            result += ' ';
        } else if (src[i] == '%' && i + 2 < src.length()) {
            int hex = stoi(src.substr(i + 1, 2), nullptr, 16);
            result += static_cast<char>(hex);
            i += 2;
        } else {
            result += src[i];
        }
    }
    return result;
}

// Function to format data
vector<string> formatData(const string& data) {
    vector<string> formattedData;
    size_t start = 0, end = 0;
    while ((end = data.find('&', start)) != string::npos) {
        formattedData.push_back(data.substr(start, end - start));
        start = end + 1;
    }
    formattedData.push_back(data.substr(start));
    return formattedData;
}

// Function to print HTML header
void printHeader() {
    cout << "Content-type: text/html; charset=utf-8\n\n";
    cout << "<html><head><title>Data Table</title></head><body>";
}

// Function to print HTML footer
void printFooter() {
    cout << "</body></html>";
}

// Function to print login form
void printLoginForm() {
    cout << "<form action='index.cgi' method='post'>";
    cout << "<input type='hidden' name='status' value='login'>";
    cout << "<label for='name'>Name:</label>";
    cout << "<input type='text' id='name' name='name' placeholder='Enter your name'>";
    cout << "<br><br>";
    cout << "<label for='password'>Password:</label>";
    cout << "<input type='password' id='password' name='password' placeholder='Enter your password'>";
    cout << "<br><br>";
    cout << "<input type='submit' value='Login'>";
    cout << "</form>";
}

// Function to print add form
void printAddForm() {
    cout << "<form action='index.cgi' method='post'>";
    cout << "<input type='hidden' name='status' value='add'>";
    cout << "<label for='name'>Name:</label>";
    cout << "<input type='text' id='name' name='name' placeholder='Enter your name'>";
    cout << "<br><br>";
    cout << "<label for='age'>Age:</label>";
    cout << "<input type='number' id='age' name='age' placeholder='Enter your age'>";
    cout << "<br><br>";
    cout << "<label for='city'>City:</label>";
    cout << "<input type='text' id='city' name='city' placeholder='Enter your city'>";
    cout << "<br><br>";
    cout << "<label for='country'>Country:</label>";
    cout << "<input type='text' id='country' name='country' placeholder='Enter your country'>";
    cout << "<br><br>";
    cout << "<label for='email'>Email:</label>";
    cout << "<input type='email' id='email' name='email' placeholder='Enter your email'>";
    cout << "<br><br>";
    cout << "<input type='submit' value='Add'>";
    cout << "</form>";
}

// Function to print data table
void printDataTable(const string& data) {
    cout << "<table border='1'>";
    cout << "<tr><th>Name</th><th>Age</th><th>City</th><th>Country</th><th>Email</th></tr>";
    vector<string> rows;
    size_t start = 0, end = 0;
    while ((end = data.find('\n', start)) != string::npos) {
        rows.push_back(data.substr(start, end - start));
        start = end + 1;
    }
    rows.push_back(data.substr(start));
    for (const string& row : rows) {
        vector<string> fields = formatData(row);
        if (fields.size() == 5) {
            cout << "<tr>";
            for (const string& field : fields) {
                cout << "<td>" << urlDecode(field) << "</td>";
            }
            cout << "<td><form action='index.cgi' method='post'>";
            cout << "<input type='hidden' name='status' value='edit'>";
            cout << "<input type='hidden' name='line' value='" << row << "'>";
            cout << "<input type='submit' value='Edit'>";
            cout << "</form></td>";
            cout << "<td><form action='index.cgi' method='post'>";
            cout << "<input type='hidden' name='status' value='remove'>";
            cout << "<input type='hidden' name='line' value='" << row << "'>";
            cout << "<input type='submit' value='Remove'>";
            cout << "</form></td>";
            cout << "</tr>";
        }
    }
    cout << "</table>";
}

// Function to print navigation
void printNavigation() {
    cout << "<form action='index.cgi' method='post'>";
    cout << "<input type='hidden' name='status' value='long'>";
    cout << "<input type='submit' value='Long Table'>";
    cout << "</form>";
    cout << "<form action='index.cgi' method='post'>";
    cout << "<input type='hidden' name='status' value='short'>";
    cout << "<input type='submit' value='Short Table'>";
    cout << "</form>";
    cout << "<form action='index.cgi' method='post'>";
    cout << "<input type='hidden' name='status' value='logout'>";
    cout << "<input type='submit' value='Logout'>";
    cout << "</form>";
}

int main() {
    string postData;
    getline(cin, postData);
    string decodedData = urlDecode(postData);

    if (decodedData.find("status=login") != string::npos) {
        vector<string> fields = formatData(decodedData);
        string name = fields[1].substr(5);
        string password = fields[2].substr(9);
        if (name == "admin" && password == "password") {
            printHeader();
            cout << "<h2>Welcome, " << name << "!</h2>";
            printAddForm();
            printNavigation();
            printFooter();
        } else {
            printHeader();
            cout << "<h2>Invalid login or password</h2>";
            printLoginForm();
            printFooter();
        }
    } else if (decodedData.find("status=add") != string::npos) {
        vector<string> fields = formatData(decodedData);
        string name = fields[1].substr(5);
        string age = fields[2].substr(4);
        string city = fields[3].substr(5);
        string country = fields[4].substr(8);
        string email = fields[5].substr(6);
        ofstream file("data.txt", ios::app);
        if (file.is_open()) {
            file << name << "&" << age << "&" << city << "&" << country << "&" << email << "\n";
            file.close();
        }
        printHeader();
        cout << "<h2>Data added successfully!</h2>";
        printAddForm();
        printNavigation();
        printFooter();
    } else if (decodedData.find("status=long") != string::npos) {
        ifstream file("data.txt");
        string data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();
        printHeader();
        cout << "<h2>Data Table</h2>";
        printDataTable(data);
        printNavigation();
        printFooter();
    } else if (decodedData.find("status=short") != string::npos) {
        printHeader();
        cout << "<h2>Short Table</h2>";
        printNavigation();
        printFooter();
    } else if (decodedData.find("status=remove") != string::npos) {
        vector<string> fields = formatData(decodedData);
        string line = fields[2].substr(5);
        ifstream file("data.txt");
        string data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();
        ofstream temp("temp.txt");
        size_t start = 0, end = 0;
        while ((end = data.find('\n', start)) != string::npos) {
            string row = data.substr(start, end - start);
            if (row != line) {
                temp << row << "\n";
            }
            start = end + 1;
        }
        string lastRow = data.substr(start);
        if (lastRow != line) {
            temp << lastRow;
        }
        temp.close();
        remove("data.txt");
        rename("temp.txt", "data.txt");
        printHeader();
        cout << "<h2>Data removed successfully!</h2>";
        printNavigation();
        printFooter();
    } else if (decodedData.find("status=edit") != string::npos) {
        vector<string> fields = formatData(decodedData);
        string line = fields[2].substr(5);
        ifstream file("data.txt");
        string data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();
        size_t start = 0, end = 0;
        while ((end = data.find('\n', start)) != string::npos) {
            string row = data.substr(start, end - start);
            if (row == line) {
                vector<string> fields = formatData(row);
                string name = fields[0].substr(5);
                string age = fields[1].substr(4);
                string city = fields[2].substr(5);
                string country = fields[3].substr(8);
                string email = fields[4].substr(6);
                printHeader();
                cout << "<h2>Edit Data</h2>";
                cout << "<form action='index.cgi' method='post'>";
                cout << "<input type='hidden' name='status' value='update'>";
                cout << "<input type='hidden' name='line' value='" << line << "'>";
                cout << "<label for='name'>Name:</label>";
                cout << "<input type='text' id='name' name='name' value='" << name << "'>";
                cout << "<br><br>";
                cout << "<label for='age'>Age:</label>";
                cout << "<input type='number' id='age' name='age' value='" << age << "'>";
                cout << "<br><br>";
                cout << "<label for='city'>City:</label>";
                cout << "<input type='text' id='city' name='city' value='" << city << "'>";
                cout << "<br><br>";
                cout << "<label for='country'>Country:</label>";
                cout << "<input type='text' id='country' name='country' value='" << country << "'>";
                cout << "<br><br>";
                cout << "<label for='email'>Email:</label>";
                cout << "<input type='email' id='email' name='email' value='" << email << "'>";
                cout << "<br><br>";
                cout << "<input type='submit' value='Update'>";
                cout << "</form>";
                printFooter();
                return 0;
            }
            start = end + 1;
        }
        printHeader();
        cout << "<h2>Data not found!</h2>";
        printFooter();
    } else if (decodedData.find("status=update") != string::npos) {
        vector<string> fields = formatData(decodedData);
        string line = fields[2].substr(5);
        string name = fields[3].substr(5);
        string age = fields[4].substr(4);
        string city = fields[5].substr(5);
        string country = fields[6].substr(8);
        string email = fields[7].substr(6);
        ifstream file("data.txt");
        string data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();
        ofstream temp("temp.txt");
        size_t start = 0, end = 0;
        while ((end = data.find('\n', start)) != string::npos) {
            string row = data.substr(start, end - start);
            if (row == line) {
                temp << name << "&" << age << "&" << city << "&" << country << "&" << email << "\n";
            } else {
                temp << row << "\n";
            }
            start = end + 1;
        }
        string lastRow = data.substr(start);
        if (lastRow != line) {
            temp << lastRow;
        }
        temp.close();
        remove("data.txt");
        rename("temp.txt", "data.txt");
        printHeader();
        cout << "<h2>Data updated successfully!</h2>";
        printNavigation();
        printFooter();
    } else if (decodedData.find("status=logout") != string::npos) {
        printHeader();
        cout << "<h2>Logged out successfully!</h2>";
        printLoginForm();
        printFooter();
    } else {
        printHeader();
        cout << "<h2>Invalid request!</h2>";
        printFooter();
    }

    return 0;
}