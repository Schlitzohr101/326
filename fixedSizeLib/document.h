//William Murray
//main.cpp document.cpp document.h header.h
//Document header. Class definition of Documents
#ifndef DOCUMENT_H
#define DOCUMENT_H
#include <string>


class Document {
    private:
        char * content;
        int    length;
    
    public:
        Document();
        Document(int);
        void initContent();
        int getLength();
        void setLength(int);
        bool findWord(std::string);
        bool findRec(int,std::string,char []);
};

#endif