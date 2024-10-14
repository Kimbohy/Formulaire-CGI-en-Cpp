#include "Form.hpp"

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
        cout << "<td class='data-cell'>" << formatString(field) << "</td>";
    }
    cout << "<div class='action-cell'>";
    cout << "<td class='action-cell'><form action='index.cgi' method='post'>";
    cout << "<input type='hidden' name='status' value='remove'>";
    cout << "<input type='hidden' name='line' value='" << line << "'>";
    cout << "<input type='submit' class='remove-btn' value='Remove'></form>";

    cout << "<form action='index.cgi' method='post'>";
    cout << "<input type='hidden' name='status' value='eddit'>";
    cout << "<input type='hidden' name='line' value='" << line << "'>";
    cout << "<input type='submit' class='eddit-btn' value='Edit'></form></td>";
    cout << "</div>";

}

void Form::printNavigation()
{
    // Afficher le type de contenu et l'en-tête HTML
    cout << "Content-type: text/html; charset=utf-8\n\n";
    cout << "<html><head><title>Form</title>";
    cout << "<link rel='stylesheet' href='style.css'></head><body>";

    cout << "<form action='index.cgi' method='post' class='nav-form'>";
    cout << "<input type='hidden' name='status' value='adding'>";
    cout << "<input type='submit' class='add-btn' value='Add'>";
    cout << "</form>";
}

void Form::printShortFormattedLine(const string& line) 
{
    vector<string> data = formatData(line);
    if (data.size() > 3) // Vérifier s'il y a assez de champs
    { 
        cout << "<td class='data-cell'>" << formatString(data[0]) << "</td>"; // Nom
        cout << "<td class='data-cell'>" << formatString(data[3]) << "</td>"; // Pays
    }
}

void Form::printLongTable() 
{
    ifstream file("data.txt");
    if (!file.is_open()) 
    {
        cerr << "<h2 class='error'>error: Can't open data.txt</h2>" << endl;
        return;
    }
        // Afficher le type de contenu et l'en-tête HTML
    cout << "Content-type: text/html; charset=utf-8\n\n";
    cout << "<html><head><title>Form</title>";
    cout << "<link rel='stylesheet' href='style.css'></head><body>";

    cout << "<table class='data-table'>";
    cout << "<tr class='header-row'><th class='header-cell'>Name</th><th class='header-cell'>Age</th><th class='header-cell'>City</th><th class='header-cell'>Country</th><th class='header-cell'>Email</th></tr>";

    string line;
    while (getline(file, line)) 
    {
        cout << "<tr class='data-row'>";
        printLongFormattedLine(line);
        cout << "</tr>";
    }
    cout << "</table>";
    
    file.close();

    cout << "<div class='navigation'>";

    cout << "<form action='index.cgi' method='post' class='nav-form'>";
    cout << "<input type='hidden' name='status' value='short'>";
    cout << "<input type='submit' value='Short' class='add-btn'>";
    cout << "</form>";

    printNavigation();

    cout << "</div>";
}

void Form::printShortTable() 
{

    int count = 0;
    ifstream file2("data.txt");
    if (!file2.is_open()) 
    {
        cerr << "<h2 class='error'>error: Can't open data.txt</h2>" << endl;
        return;
    }

    cout << "<table class='data-table'>";
    cout << "<tr class='header-row' ><th class='header-cell' >Name</th><th class='header-cell' >Country</th></tr>";

    string line;
    while (getline(file2, line)) 
    {
        cout << "<tr class='data-row'>";
        printShortFormattedLine(line);
        cout << "</tr>";
        count++;
    }
    if (count == 0)
    {
        cout << "<td class='data-cell'>" << "-" << "</td>"; // Nom
        cout << "<td class='data-cell'>" << "-" << "</td>"; // Pays
    }
    cout << "</table>";
    
    file2.close();

    cout << "<div class='navigation'>";

    cout << "<form action='index.cgi' method='post' class='nav-form'>";
    cout << "<input type='hidden' name='status' value='long'>";
    cout << "<input type='submit' value='Long' class='add-btn'>";
    cout << "</form>";

    printNavigation();

    cout << "</div>";
}

void Form::printForm() 
{

    // Afficher le type de contenu et l'en-tête HTML
    cout << "Content-type: text/html; charset=utf-8\n\n";
    cout << "<html><head><title>Form</title>";
    cout << "<link rel='stylesheet' href='style.css'></head><body>";

    cout << "<form action='index.cgi' method='post' class='add-form'>";
    
    cout << "<div class='form-group'>";
    cout << "<label for='name'>Name:</label>";
    cout << "<input type='text' id='name' class='input-field' name='name' placeholder='Enter your name'>";
    cout << "</div>";
    
    cout << "<div class='form-group'>";
    cout << "<label for='age'>Age:</label>";
    cout << "<input type='number' id='age' class='input-field' name='age' placeholder='Enter your age'>";
    cout << "</div>";
    
    cout << "<div class='form-group'>";
    cout << "<label for='city'>City:</label>";
    cout << "<input type='text' id='city' class='input-field' name='city' placeholder='Enter your city'>";
    cout << "</div>";
    
    cout << "<div class='form-group'>";
    cout << "<label for='country'>Country:</label>";
    cout << "<input type='text' id='country' class='input-field' name='country' placeholder='Enter your country'>";
    cout << "</div>";
    
    cout << "<div class='form-group'>";
    cout << "<label for='email'>Email:</label>";
    cout << "<input type='email' id='email' class='input-field' name='email' placeholder='Enter your email'>";
    cout << "</div>";
    
    cout << "<div class='form-group'>";
    cout << "<input type='submit' class='submit-btn' value='Add'>";
    cout << "</div>";
    
    cout << "</form>";

    cout << "<form action='index.cgi' method='post' class='navig-form'>";
    cout << "<input type='hidden' name='status' value='short'>";
    cout << "<input type='submit' value='Back' class='submit-btn'>";
    cout << "</form>";
}

Form::Form()
{
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
        cerr << "<h2 class='error'>error: Can't open data.txt " << "data.txt </h2>" << endl;
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
        cerr << "<h2 class='error'>error: Can't write in data.txt " << "data.txt </h2>" << endl;
        return;
    }

    // Écrire les lignes filtrées dans le fichier
    for (const string& outputLine : lines) 
    {
        outputFile << outputLine << endl;
    }

    outputFile.close();
}

void Form::printWarningEmptySection()
{
    cout << "<h2 class='error'>Warning: Empty cell added </h2>" << endl;
}


bool isValidName(const string& name) 
{
    // Vérifier si le nom ne contient que des lettres et des espaces
    return !name.empty() && regex_match(name, regex("^[A-Za-z ]+$"));
}

bool isValidAge(const string& age) 
{
    return !age.empty() && regex_match(age, regex("^[0-9]+$"));
}

bool isValidEmail(const string& email) 
{
    // [\\w.%+-] : regex pour les caractères autorisés dans le nom d'utilisateur 
    const regex emailPattern("^[\\w.+-]+@[\\w.-]+\\.[A-Za-z]{2,}$");
    return regex_match(email, emailPattern);
}

void Form::addData(const string& sline) 
{
    vector<string> data = formatData(sline);

    if (data.size() < 5) {
        cout << "<h2 class='error'>error: Incomplete data </h2>" << endl;
        return;
    }

    string name = formatString(data[0]);
    string age = formatString(data[1]);
    string city = formatString(data[2]);
    string country = formatString(data[3]);
    string email = formatString(data[4]);

    if (!isValidName(name)) {
        cout << "<h2 class='error'>error: Invalid name </h2>" << endl;
        return;
    }
    if (!isValidAge(age)) {
        cout << "<h2 class='error'>error: Invalid age </h2>" << endl;
        return;
    }
    if (city.empty()) {
        cout << "<h2 class='error'>error: City is required </h2>" << endl;
        return;
    }
    if (country.empty()) {
        cout << "<h2 class='error'>error: Country is required </h2>" << endl;
        return;
    }
    if (!isValidEmail(email)) {
        cout << "<h2 class='error'>error: Invalid email format </h2>" << endl;
        return;
    }

    // Proceed with checking for duplicates and adding data
    ifstream file("data.txt");
    string line;
    bool found = false;

    while (getline(file, line)) {
        if (line.find(sline) != string::npos) {
            found = true;
            cout << "<h2 class='error'>error: Line already exists </h2>" << endl;
            break;
        }
    }
    file.close();

    if (!found) {
        ofstream file2("data.txt", ios::app);
        if (file2.is_open()) {
            file2 << sline << endl;
            file2.close();
        } else {
            cout << "<h2 class='error'>error: Can't write in data.txt </h2>" << endl;
        }
    }
}

// Un formulaire deja rempli par les données à modifier
void Form::modificationPage(const string& sline)
{
    string name = sline.substr(sline.find("name=") + 5, sline.find("age=") -6);
    string age = sline.substr(sline.find("age=") + 4, sline.find("city=") - sline.find("age=") - 5);
    string city = sline.substr(sline.find("city=") + 5, sline.find("country=") - sline.find("city=") - 6);
    string country = sline.substr(sline.find("country=") + 8, sline.find("email=") - sline.find("country=") - 9);
    string email = sline.substr(sline.find("email=") + 6);

    // cout << sline << endl;

    // Afficher le type de contenu et l'en-tête HTML
    cout << "Content-type: text/html; charset=utf-8\n\n";
    cout << "<html><head><title>Form</title>";
    cout << "<link rel='stylesheet' href='style.css'></head><body>";

    cout << "<form action='index.cgi' method='post' class='add-form'>";
    cout << "<input type='hidden' name='status' value='edditing'>";

    cout << "<div class='form-group'>";
    cout << "<label for='name'>Name:</label>";
    cout << "<input type='text' id='name' class='input-field' name='name' placeholder='Enter your name' value='" << name << "'>";
    cout << "</div>";
    
    cout << "<div class='form-group'>";
    cout << "<label for='age'>Age:</label>";
    cout << "<input type='number' id='age' class='input-field' name='age' placeholder='Enter your age' value='" << age << "'>";
    cout << "</div>";
    
    cout << "<div class='form-group'>";
    cout << "<label for='city'>City:</label>";
    cout << "<input type='text' id='city' class='input-field' name='city' placeholder='Enter your city' value='" << city << "'>";
    cout << "</div>";
    
    cout << "<div class='form-group'>";
    cout << "<label for='country'>Country:</label>";
    cout << "<input type='text' id='country' class='input-field' name='country' placeholder='Enter your country' value='" << country << "'>";
    cout << "</div>";
    
    cout << "<div class='form-group'>";
    cout << "<label for='email'>Email:</label>";
    cout << "<input type='email' id='email' class='input-field' name='email' placeholder='Enter your email' value='" << email << "'>";
    cout << "</div>";

    cout << "<input type='hidden' name='line' value='" << sline << "'>";
    
    cout << "<div class='form-group'>";
    cout << "<input type='submit' class='submit-btn' value='Change'>";
    cout << "</div>";
    
    cout << "</form>";

    cout << "<form action='index.cgi' method='post' class='navig-form'>";
    cout << "<input type='hidden' name='status' value='long'>";
    cout << "<input type='submit' value='Back' class='submit-btn'>";
    cout << "</form>";
    
}

void Form::modifyData(const string& sline, const string& newLine) 
{
    ifstream file("data.txt");
    string line;
    vector<string> lines;
    bool found = false;

    vector<string> data = formatData(newLine);

    if (data.size() < 5) {
        cout << "<h2 class='error'>error: Incomplete data </h2>" << endl;
        return;
    }

    string name = formatString(data[0]);
    string age = formatString(data[1]);
    string city = formatString(data[2]);
    string country = formatString(data[3]);
    string email = formatString(data[4]);


    if (!isValidName(name)) {
        cout << "<h2 class='error'>error: Invalid name </h2>" << endl;
        return;
    }
    if (!isValidAge(age)) {
        cout << "<h2 class='error'>error: Invalid age </h2>" << endl;
        return;
    }
    if (city.empty()) {
        cout << "<h2 class='error'>error: City is required </h2>" << endl;
        return;
    }
    if (country.empty()) {
        cout << "<h2 class='error'>error: Country is required </h2>" << endl;
        return;
    }
    if (!isValidEmail(email)) {
        cout << "<h2 class='error'>error: Invalid email format </h2>" << endl;
        return;
    }

    if (newLine.size() == 32) {
        cout << "<h2 class='error'>error: Les données sont vide </h2>" << endl;
        return;
    }
    else if (newLine.find("=&") != string::npos)
    {
        printWarningEmptySection();
    }
    
    // Lire chaque ligne du fichier et edditer la ligne spécifique puis l'ajouter au vecteur
    while (getline(file, line)) {
        if (line.find(sline) != string::npos) 
        {
            lines.push_back(newLine);
            found = true;
        } else {
            lines.push_back(line);
        }
    }
    file.close();

    if (!found) 
    {
        cout << "<h2 class='error'>error: Line not found </h2>" << endl;
        return;
    }
    else {

    // Réouvrir le fichier en mode d'écriture pour le mettre à jour
    ofstream file2("data.txt");
    if (file2.is_open()) {
        for (const string& outputLine : lines) 
        {
            file2 << outputLine << endl;
        }
        file2.close();
    } 
    else 
    {
        cout << "<h2 class='error'>error: Can't write in data.txt </h2>" << endl;
    }
    }
}
