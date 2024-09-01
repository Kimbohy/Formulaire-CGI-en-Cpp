#include "./Form.hpp"
#include <fstream>
#include <iostream>

using namespace std;

int main() {
    Form form;
    string postData;
    getline(cin, postData);
    cout << "Post data: " << postData << endl;
    cout << "<br>";
    // Décoder les données postData
    form.setData(postData);
    string decodedData = form.urlDecode(postData);

    // Vérification des données POST pour déterminer l'action à effectuer
    if (decodedData.find("status=long") != string::npos) {
        form.printLongTable();
    } else if (decodedData.find("name=") != string::npos) {
        ofstream file("data.txt", ios::app);
        if (file.is_open()) {
            cout << decodedData << endl;
            file << decodedData << endl;
            file.close();
        } else {
            cerr << "Erreur: Impossible d'écrire dans le fichier data.txt" << endl;
        }
        form.printShortTable();
    } else {
        form.printShortTable();
    }

    return 0;
}