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

//find a word in the document
//param: string word - word to search for
//return: if found
bool Document::findWord(string word) {
    bool found = false;
    int n = word.size();
    //temp array to keep a piece of the document in
    char * temp = new char[n];
    int i = 0;
    while(i < length && !found)
    {
        //check to see if we can create temp
        if (i+n < length)
        {   
            int loop = 0;
            for (int j = i; j < i+n; j++)
            {
                temp[loop] = content[j];
                loop++;
            }
            string compare = string(temp,n);
            found = word == compare;
        }
        i++;
    }
    
    return found;
}
