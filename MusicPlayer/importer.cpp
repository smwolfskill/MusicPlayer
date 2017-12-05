#include "importer.h"
#include <QString>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

Vector<std::string> * Importer::readLines(const string fileUrl)
{
    FILE * file = fopen(fileUrl.c_str(), "r");
    if(file == nullptr) {
        return nullptr; //not found
    }
    Vector<string> * lines = new Vector<string>(0);
    //Read file line-by-line, C-style
    char * buf = nullptr;
    size_t capacity = 0;
    ssize_t result = 1;
    while(result > 0) {
        result = getline(&buf, &capacity, file);
        if(result > 0 && buf[result-1] == '\n') {
            buf[result-1] = '\0'; //end string at newline
            //qInfo(buf);
            lines->push_back(string(buf));
        }
    }
    fclose(file);
    free(buf);
    return lines;
}

bool Importer::saveLines(const string fileUrl, const Vector<string> * const lines, unsigned start)
{
    //FILE * file = fopen(fileUrl.c_str(), "w");
    ofstream file;
    file.open(fileUrl, ios::out | ios::trunc); //overwrite
    return saveTo(file, lines, start);

}

bool Importer::appendLines(const string fileUrl, const Vector<string> * const lines, unsigned start)
{
    //FILE * file = fopen(fileUrl.c_str(), "a");
    ofstream file;
    file.open(fileUrl, ios::out | ios::app); //append
    return saveTo(file, lines, start);
}

bool Importer::saveTo(ofstream &openStream, const Vector<string> * const lines, unsigned start)
{
    if(!openStream.is_open()) {
        return false;
    }
    for(unsigned i = start; i < lines->size(); i++) {
        openStream << (*lines)[i] + "\n";
    }
    openStream.close();
    return true;
}
