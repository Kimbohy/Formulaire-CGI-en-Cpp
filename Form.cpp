#include "./Form.hpp"

using namespace std;

string Form::urlDecode(const string &src) 
{
    string result;
    for (size_t i = 0; i < src.length(); i++) 
    {
        if (src[i] == '+') 
        {
            result += ' ';
        } 
        else if (src[i] == '%' && i + 2 < src.length()) 
        {
            int hex = stoi(src.substr(i + 1, 2), nullptr, 16); // Convertir le nombre hexadécimal en décimal
            result += static_cast<char>(hex); // Convertir le nombre décimal en caractère
            i += 2;
        } 
        else 
        {
            result += src[i];
        }
    }
    return result;
}

string Form::formatString(string str) 
{
    size_t pos = str.find('=');
    if (pos != string::npos) 
    {
        return urlDecode(str.substr(pos + 1)); // Décoder la chaîne encodée en URL
    }
    return str; // Retourne la chaîne non modifiée si '=' n'est pas trouvé
}

// Formater les données en un vecteur de chaînes
vector<string> Form::formatData(string data) 
{
    vector<string> formattedData;
    size_t start = 0, end = 0;
    while ((end = data.find('&', start)) != string::npos) 
    {
        formattedData.push_back(data.substr(start, end - start));
        start = end + 1;
    }
    formattedData.push_back(data.substr(start)); // Ajouter la dernière partie
    return formattedData;
}

// Print une ligne formatée dans un tableau HTML
void Form::printLongFormattedLine(const string& line) 
{
    vector<string> data = formatData(line);
    for (const string& field : data) 
    {
        cout << "<td>" << formatString(field) << "</td>";
    }

    cout << "<td><form action='index.cgi' method='post'>";
    cout << "<input type='hidden' name='status' value='remove'>";
    cout << "<input type='hidden' name='line' value='" << line << "'>";
    cout << "<input type='submit' value='Remove'></form></td>";
}

void Form::printNavigation()
{
    cout << "<form action='index.cgi' method='post'>";
    cout << "<input type='hidden' name='status' value='adding'>";
    cout << "<input type='submit' value='Add'>";
    cout << "</form>";
}

void Form::printShortFormattedLine(const string& line) 
{
    vector<string> data = formatData(line);
    if (data.size() > 3) // Vérifier s'il y a assez de champs
    { 
        cout << "<td>" << formatString(data[0]) << "</td>"; // Nom
        cout << "<td>" << formatString(data[3]) << "</td>"; // Pays
    }
}

void Form::printLongTable() 
{
    ifstream file("data.txt");
    if (!file.is_open()) 
    {
        cerr << "Erreur: Impossible d'ouvrir le fichier data.txt" << endl;
        return;
    }

    cout << "<table border='1'>";
    cout << "<tr><th>Name</th><th>Age</th><th>City</th><th>Country</th><th>Email</th></tr>";

    string line;
    while (getline(file, line)) 
    {
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

    printNavigation();
}

void Form::printShortTable() 
{
    ifstream file2("data.txt");
    if (!file2.is_open()) 
    {
        cerr << "Erreur: Impossible d'ouvrir le fichier data.txt" << endl;
        return;
    }

    cout << "<table border='1'>";
    cout << "<tr><th>Name</th><th>Country</th></tr>";

    string line;
    while (getline(file2, line)) 
    {
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

    printNavigation();
}

void Form::printForm() 
{
    cout << "<form action='index.cgi' method='post'>";
    cout << "<input type='hidden' name='status' value='adding'>";
    cout << "<input type='text' name='name' placeholder='Name'>";
    cout << "<input type='number' name='age' placeholder='Age'>";
    cout << "<input type='text' name='city' placeholder='City'>";
    cout << "<input type='text' name='country' placeholder='Country'>";
    cout << "<input type='text' name='email' placeholder='Email'>";
    cout << "<input type='submit' value='Add'>";
    cout << "</form>";

    cout << "<form action='index.cgi' method='post'>";
    cout << "<input type='hidden' name='status' value='short'>";
    cout << "<input type='submit' value='back'>";
}

Form::Form()
{
    cout << "Content-type: text/html; charset=utf-8\n\n";
    cout << "<html><head><title>Form</title>";
    cout << "<link rel='stylesheet' href='style.css'></head><body>";
}

Form::~Form()
{
    cout << "</body></html>";
}

void Form::setData(string data) 
{
    this->data = data;
}

void Form::removeLine(const string& sline) 
{
    ifstream inputFile("data.txt"); // Fichier d'entrée
    if (!inputFile.is_open()) {
        cerr << "Erreur: Impossible d'ouvrir le fichier " << "data.txt" << endl;
        return;
    }

    vector<string> lines;
    string line;

    // Lire toutes les lignes du fichier d'entrée
    while (getline(inputFile, line)) 
    {
        // Ajouter uniquement les lignes qui ne contiennent pas la sline spécifique
        if (line.find(sline) == string::npos) 
        {
            lines.push_back(line);
        }
    }

    inputFile.close();

    // Réouvrir le fichier en mode d'écriture pour le mettre à jour
    ofstream outputFile("data.txt");
    if (!outputFile.is_open()) 
    {
        cerr << "Erreur: Impossible d'ouvrir le fichier pour écriture " << "data.txt" << endl;
        return;
    }

    // Écrire les lignes filtrées dans le fichier
    for (const string& outputLine : lines) 
    {
        outputFile << outputLine << endl;
    }

    outputFile.close();
}

void Form::addData(const string& sline) 
{
    ifstream file("data.txt");
    string line;
    bool found = false;

    // Lire le fichier pour vérifier si la ligne existe déjà
    while (getline(file, line)) {
        if (line.find(sline) != string::npos) {
            found = true;
            break;  // Sortir de la boucle dès que la ligne est trouvée
        }
    }
    file.close();

    // Si la ligne n'a pas été trouvée, l'ajouter à la fin du fichier
    if (!found) {
        ofstream file2("data.txt", ios::app);
        if (file2.is_open()) {
            file2 << sline << endl;
            file2.close();
        } else {
            cout << "Erreur: Impossible d'écrire dans le fichier data.txt" << endl;
        }
    }
}
