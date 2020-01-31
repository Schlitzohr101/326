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
};

#endif