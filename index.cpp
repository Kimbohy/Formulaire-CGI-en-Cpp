#include "Form.hpp"

using namespace std;

string checkSession() 
{
    string session;
    getenv("HTTP_COOKIE") ? session = getenv("HTTP_COOKIE") : session = "";
    if (session.find("session=") == string::npos) 
    {
        cout << "Content-type: text/html\r\n\r\n";
        cout << "<html><head><meta http-equiv='refresh' content='0;url=login.cgi'></head></html>";
        exit(0);
    }
    return session;
}

int main() 
{
    string session = checkSession();
    session = session.substr(8);
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
        size_t pos = lineRequest.find("line=");
        if (pos != string::npos) {
            string line = lineRequest.substr(pos + 5);
            form.removeLine(line);
            form.printLongTable();
        }
    } 
    else if (decodedData.find("status=editing") != string::npos)         // Si la requête est de type editing
    {
        string lineRequest = form.formatString(decodedData);
        size_t namePos = lineRequest.find("name=");
        size_t linePos = lineRequest.find("line=");
        if (namePos != string::npos && linePos != string::npos) {
            string newLine = lineRequest.substr(namePos, linePos - namePos - 1);
            string line = lineRequest.substr(linePos + 5);
            form.modifyData(line, newLine);
            form.printLongTable();
        }
    }
    else if (decodedData.find("status=edit") != string::npos)         // Si la requête est de type edit
    {
        string lineRequest = form.formatString(decodedData);
        size_t pos = lineRequest.find("line=");
        if (pos != string::npos) {
            string line = lineRequest.substr(pos + 5);
            form.modificationPage(line);
        }
    }
    else if (decodedData.find("name=") != string::npos)                 // Si la requête est de type add
    {
        form.addData(decodedData);
        form.printShortTable();
    }
    else
    {
        form.printShortTable();
    }

    cout<<"<a href='logout.cgi?session=" << session << "' class=\"submit-btn\"'>Logout</a>";

    return 0;
}