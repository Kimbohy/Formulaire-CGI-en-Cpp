#include "./Form.hpp"

using namespace std;

int main() {
    Form form;
    string postData;
    getline(cin, postData);
    // Décoder les données postData
    form.setData(postData);
    string decodedData = form.urlDecode(postData);

    // Vérification des données POST pour déterminer l'action à effectuer
    if (decodedData.find("status=long") != string::npos) {
        form.printLongTable();
    } 
    else if (decodedData.find("status=remove") != string::npos) 
    {
        string lineRequest = form.formatString(decodedData);
        string line = lineRequest.substr(lineRequest.find("line=") + 5);
        form.removeLine(line);
        form.printLongTable();
    } 
    else if (decodedData.find("name=") != string::npos) {
        ofstream file("data.txt", ios::app);
        if (file.is_open()) {
            file << decodedData << endl;
            file.close();
        } else {
            cout << "Erreur: Impossible d'écrire dans le fichier data.txt" << endl;
        }
        form.printShortTable();
    }
     else {
        form.printShortTable();
    }

    return 0;
}
 