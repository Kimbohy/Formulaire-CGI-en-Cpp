#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "./Form.hpp"

using namespace std;

string Form::urlDecode(const string &src) {
    string result;
    for (size_t i = 0; i < src.length(); i++) {
        if (src[i] == '+') {
            result += ' ';
        } else if (src[i] == '%' && i + 2 < src.length()) {
            int hex = stoi(src.substr(i + 1, 2), nullptr, 16); // Convertir le nombre hexadécimal en décimal
            result += static_cast<char>(hex); // Convertir le nombre décimal en caractère
            i += 2;
        } else {
            result += src[i];
        }
    }
    return result;
}

string Form::formatString(string str) {
    size_t pos = str.find('=');
    if (pos != string::npos) {
        return urlDecode(str.substr(pos + 1)); // Décoder la chaîne encodée en URL
    }
    return str; // Retourne la chaîne non modifiée si '=' n'est pas trouvé
}

vector<string> Form::formatData(string data) {
    vector<string> formattedData;
    size_t start = 0, end = 0;
    while ((end = data.find('&', start)) != string::npos) {
        formattedData.push_back(data.substr(start, end - start));
        start = end + 1;
    }
    formattedData.push_back(data.substr(start)); // Ajouter la dernière partie
    return formattedData;
}

void Form::printLongFormattedLine(const string& line) {
    vector<string> data = formatData(line);
    for (const string& field : data) {
        cout << "<td>" << formatString(field) << "</td>";
    }
}

void Form::printShortFormattedLine(const string& line) {
    vector<string> data = formatData(line);
    if (data.size() > 3) { // Vérifier s'il y a assez de champs
        cout << "<td>" << formatString(data[0]) << "</td>"; // Nom
        cout << "<td>" << formatString(data[3]) << "</td>"; // Pays
    }
}

void Form::printLongTable() {
    ifstream file("data.txt");
    if (!file.is_open()) {
        cerr << "Erreur: Impossible d'ouvrir le fichier data.txt" << endl;
        return;
    }

    cout << "<table border='1'>";
    cout << "<tr><th>Name</th><th>Age</th><th>City</th><th>Country</th><th>Email</th></tr>";

    string line;
    while (getline(file, line)) {
        cout << "<tr>";
        printLongFormattedLine(line);
        cout << "</tr>";
    }
    cout << "</table>";
    
    file.close();

    cout << "<form action='index.cgi' method='post'>";
    cout << "<input type='hidden' name='status' value='short'>";
    cout << "<input type='submit' value='Short'>";
    cout << "</form>";
}

void Form::printShortTable() {
    ifstream file2("data.txt");
    if (!file2.is_open()) {
        cerr << "Erreur: Impossible d'ouvrir le fichier data.txt" << endl;
        return;
    }

    cout << "<table border='1'>";
    cout << "<tr><th>Name</th><th>Country</th></tr>";

    string line;
    while (getline(file2, line)) {
        cout << "<tr>";
        printShortFormattedLine(line);
        cout << "</tr>";
    }
    cout << "</table>";
    
    file2.close();

    cout << "<form action='index.cgi' method='post'>";
    cout << "<input type='hidden' name='status' value='long'>";
    cout << "<input type='submit' value='Long'>";
    cout << "</form>";
}

Form::Form()
{
    cout << "Content-type: text/html; charset=utf-8\n\n";
    cout << "<html><head><title>Form</title></head><body>";
    cout << "<form action='index.cgi' method='post'>" << endl;
    cout << "<input type='text' name='name' placeholder='Name'>";
    cout << "<input type='number' name='age' placeholder='Age'>";
    cout << "<input type='text' name='city' placeholder='City'>";
    cout << "<input type='text' name='country' placeholder='Country'>";
    cout << "<input type='text' name='email' placeholder='Email'>";
    cout << "<input type='submit' value='Add'>";
    cout << "</form>";
}

Form::~Form()
{
    cout << "</body></html>";
}

void Form::setData(string data) {
    this->data = data;
}