#ifndef FORM_HPP
#define FORM_HPP

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Form {
public:
    Form();
    ~Form();
    string urlDecode(const string &src);
    string formatString(string str);
    vector<string> formatData(string data);
    void printLongFormattedLine(const string& line);
    void printShortFormattedLine(const string& line);
    void printLongTable();
    void printShortTable();
    void setData(string data);
private:
    string data;
};

#endif