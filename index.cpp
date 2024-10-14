#include "Form.hpp"
#include "Session.hpp"

using namespace std;

int main()
{
    Session session("admin");
    Form form;
    string postData;
    getline(cin, postData);
    // Decode the postData
    form.setData(postData);
    string decodedData = form.urlDecode(postData);

    // Check the POST data to determine the action to be taken
    if (decodedData.find("status=login") != string::npos)         // If the request is of type login
    {
        // cout<< "<h2 class='error'>error:"<< decodedData<<" </h2>" << endl;
        // if the login and password is in the data (decodedData format: status=login&name=login&password=password)
        string login = decodedData.substr(18, decodedData.find("&password=") - 18);
        string password = decodedData.substr(decodedData.find("&password=") + 10);
        // cout << login << " : " << password << endl;
        if (session.isInTheData(login , password)) {
            session.setSessionCookie("admin");
        } else {
            cout << "<h2 class='error'>error: Invalid login or password </h2>" << endl;
        }
    }
    else if (decodedData.find("status=logout") != string::npos)         // If the request is of type logout
    {
        session.invalidateSession();
        session.coutLogin();
    }
    else if (decodedData.find("status=adding") != string::npos)         // If the request is of type adding
    {
        form.printForm();
    }
    else if (decodedData.find("status=long") != string::npos)                // If the request is of type long
    {
        form.printLongTable();
    } 
    else if (decodedData.find("status=remove") != string::npos)         // If the request is of type remove
    {
        string lineRequest = form.formatString(decodedData);
        size_t pos = lineRequest.find("line=");
        if (pos != string::npos) {
            string line = lineRequest.substr(pos + 5);
            form.removeLine(line);
            form.printLongTable();
        }
    } 
    else if (decodedData.find("status=editing") != string::npos)         // If the request is of type editing
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
    else if (decodedData.find("status=edit") != string::npos)         // If the request is of type edit
    {
        string lineRequest = form.formatString(decodedData);
        size_t pos = lineRequest.find("line=");
        if (pos != string::npos) {
            string line = lineRequest.substr(pos + 5);
            form.modificationPage(line);
        }
    }
    else if (decodedData.find("name=") != string::npos)                 
    {
        form.addData(decodedData);
        form.printShortTable();
    }
    else 
    // if (decodedData.find("status=short") != string::npos)         // If the request is of type short
    {
        if (session.hasCookie("admin")) {
            form.printNavigation();
            std::cout << "<h2 class='error'>error: Invalid login or password </h2>" << endl;
            // form.printShortTable();
        } else {
            session.coutLogin();
        }
    }

    return 0;
}