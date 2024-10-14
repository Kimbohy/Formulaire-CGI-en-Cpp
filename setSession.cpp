#include <iostream>
#include <string>

using namespace std;

int main(){
    // get the get method request
    string request;

    getenv("QUERY_STRING") ? request = getenv("QUERY_STRING") : request = "";

    size_t pos = request.find("session=");
    if (pos != string::npos) {
        string session = request.substr(pos + 8);
        cout <<"Set-Cookie: session=" << session << "\r\n";
        cout << "Content-type: text/html\r\n\r\n";
        // redirect to the index page
        cout << "<html><head><meta http-equiv='refresh' content='0;url=index.cgi'></head></html>";
    }
    return 0;
}