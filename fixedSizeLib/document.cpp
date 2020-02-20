//William Murray
//main.cpp document.cpp document.h header.h
//Document logic. Handles creating random character array and finding 
//searched word in array
#include "header.h"

Document::Document() {
    length = -1;
}

Document::Document(int size) {
    length = size;
    initContent();
}

void Document::initContent() {
    content = new char[length];
    for (int i = 0; i < length; i++) {
        content[i] = rand()%26 + 65;
    }
}

int Document::getLength() {
    return length;
}

void Document::setLength(int len) {
    length = len;
}

//find a word in the documentall
//param: string word - word to search for
//return: if found
bool Document::findWord(string word) {
   return string(content).find(word) != -1;
}