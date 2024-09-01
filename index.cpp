// web cgi withe c++ of an formulary to add to an array

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

string formatString(string str) 
{
    int i = 0;
    while (str[i] != '='){
        str = str.substr(i+1);
    }
    str = str.substr(1);
    
    return str;
}

vector<string> formatData(string data) 
{
    vector<string> formatedData;
    int i = 0;
    while (i < data.size()) {
        string temp = "";
        while (data[i] != '&' && i < data.size()) {
            temp += data[i];
            i++;
        }
        formatedData.push_back(temp);
        i++;
    }
    return formatedData;
}

void printLongFormatedLine(string line) 
{
    vector<string> data = formatData(line);

    for (int i = 0; i < data.size(); i++) {
        string temp = data[i];
        cout << "<td>" << formatString(temp) << "</td>";
    }
}

void printShortFormatedLine(string line) 
{
    vector<string> data = formatData(line);

    cout << "<td>" << formatString(data[0]) << "</td>";
    cout << "<td>" << formatString(data[3]) << "</td>";
}

void printLongTable()
{
    int i = 0 ;
    cout << "<table border='1'>";
    cout << "<tr>";
    cout << "<th>Name</th>";
    cout << "<th>Age</th>";
    cout << "<th>City</th>";
    cout << "<th>Country</th>";
    cout << "<th>Email</th>";
    cout << "</tr>";

    ifstream file("data.txt");
    string line;
    while (getline(file, line)) 
    {
        cout << "<tr>";
        printLongFormatedLine(line);
        cout << "</tr>";
        i++;
    }
    if (i != 0){
        cout << "<form action='index.cgi' method='post'>";
        cout << "<input type='hidden' name='status' value='short'>";
        cout << "<input type='submit' value='Short'>";
        cout << "</form>";
    }
}

void printShortTable()
{
    int i = 0;

    ifstream file2("data.txt");
    string line;
    cout << "<table border='1'>";
    cout << "<tr>";
    cout << "<th>Name</th>";
    cout << "<th>Country</th>";
    cout << "</tr>";
    while (getline(file2, line)) 
    {
        cout << "<tr>";
        printShortFormatedLine(line);
        cout << "</tr>";
        i++;
    }
    if (i != 0){
        cout << "<form action='index.cgi' method='post'>";
        cout << "<input type='hidden' name='status' value='long'>";
        cout << "<input type='submit' value='Long'>";
        cout << "</form>";
    }
    cout << "</table>";
    file2.close();
}

int main() 
{
    int i = 0;
    cout << "Content-type: text/html; charset=utf-8\n\n";
    cout << "<html><head><title>Form</title></head><body>";
    cout << "<form action='index.cgi' method='post'>";
    cout << "<input type='text' name='name' placeholder='Name'>";
    cout << "<input type='number' name='age' placeholder='Age'>";
    cout << "<input type='text' name='city' placeholder='City'>";
    cout << "<input type='text' name='country' placeholder='Country'>";
    cout << "<input type='text' name='email' placeholder='Email'>";
    cout << "<input type='submit' value='Add'>";
    cout << "</form>";

    string postData;
    getline(cin, postData);
    cout << "postData: " << postData << endl;
    if (postData == "status=long"){
        printLongTable();
    }
    else 
    // if the first part of the string is equal to "name="
    if (postData.substr(0, 5) == "name=")
    {
        ofstream file("data.txt", ios::app);
        file << postData << endl;
        file.close();
        printShortTable();
    }
    else
    {
        printShortTable();
    }

    cout << "</body></html>";
    return 0;
}