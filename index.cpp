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
    if (decodedData.find("status=adding") != string::npos)         // Si la requête est de type adding
    {
        form.printForm();
    }
    else if (decodedData.find("status=long") != string::npos)                // Si la requête est de type long
    {
        form.printLongTable();
    } 
    else if (decodedData.find("status=remove") != string::npos)         // Si la requête est de type remove
    {
        string lineRequest = form.formatString(decodedData);
        string line = lineRequest.substr(lineRequest.find("line=") + 5);
        form.removeLine(line);
        form.printLongTable();
    } 
    else if (decodedData.find("name=") != string::npos)                 // Si la requête est de type add
    {
        form.addData(decodedData);
        form.printShortTable();
    }
    else                                                                // Si la requête est de type short
    {
        form.printShortTable();
    }

    return 0;
}
 