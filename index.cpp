#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Fonction pour décoder les chaînes encodées en URL
string urlDecode(const string &src) {
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

// Fonction pour formater une chaîne en extrayant la partie après le signe '='
string formatString(string str) {
    size_t pos = str.find('=');
    if (pos != string::npos) {
        return str.substr(pos + 1);
    }
    str = urlDecode(str); // Décoder la chaîne encodée en URL
    return str; // Retourne la chaîne non modifiée si '=' n'est pas trouvé
}

// Fonction pour formater les données sous forme de vecteur à partir d'une chaîne de données
vector<string> formatData(string data) {
    vector<string> formattedData;
    size_t start = 0, end = 0;
    while ((end = data.find('&', start)) != string::npos) {
        formattedData.push_back(data.substr(start, end - start));
        start = end + 1;
    }
    formattedData.push_back(data.substr(start)); // Ajouter la dernière partie
    return formattedData;
}

// Fonction pour afficher les lignes formatées pour le tableau long
void printLongFormattedLine(const string& line) {
    vector<string> data = formatData(line);
    for (const string& field : data) {
        cout << "<td>" << formatString(field) << "</td>";
    }
}

// Fonction pour afficher les lignes formatées pour le tableau court
void printShortFormattedLine(const string& line) {
    vector<string> data = formatData(line);
    if (data.size() > 3) { // Vérifier s'il y a assez de champs
        cout << "<td>" << formatString(data[0]) << "</td>"; // Nom
        cout << "<td>" << formatString(data[3]) << "</td>"; // Pays
    }
}

// Fonction pour afficher le tableau long
void printLongTable() {
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

// Fonction pour afficher le tableau court
void printShortTable() {
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

int main() {
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
    // cout << "<p>POST data: " << postData << "</p>";
    // Vérification des données POST pour déterminer l'action à effectuer
    if (postData.find("status=long") != string::npos) {
        printLongTable();
    } else if (postData.find("name=") != string::npos) {
        ofstream file("data.txt", ios::app);
        if (file.is_open()) {
            file << postData << endl;
            file.close();
        } else {
            cerr << "Erreur: Impossible d'écrire dans le fichier data.txt" << endl;
        }
        printShortTable();
    } else {
        printShortTable();
    }

    cout << "</body></html>";
    return 0;
}
