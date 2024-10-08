#ifndef FORM_HPP
#define FORM_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex> 
using namespace std;

class Form {
public:
    Form();
    ~Form();
    string urlDecode(const string &src);
    string formatString(string str);
    vector<string> formatData(string data);
    void printForm();
    void printNavigation();
    void printLongFormattedLine(const string& line);
    void printShortFormattedLine(const string& line);
    void printLongTable();
    void printShortTable();
    void setData(string data);
    void removeLine(const string& sline);
    void addData(const string& sline);
    void modifyData(const string &sline, const string &newLine);
    void modificationPage(const string &sline);
    void printWarningEmptySection();

private:
    string data;
};


#endif