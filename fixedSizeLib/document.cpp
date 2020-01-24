#include "header.h"

Document::Document() {
    length = -1;
}

void Document::initContent() {
    content = new char[length];
    srand(time(NULL));
    for (int i = 0; i < length; i++) {
        content[i] = rand()%26 + 65;
        //cout << content[i];
    }
    //cout << endl;
}

int Document::getLength() {
    return length;
}

void Document::setLength(int len) {
    length = len;
}

bool Document::findWord(string word) {
    int n = word.size()-1;
    for (int i =n; i < length; i++)
    {
        if (word[n] == content[i])
        {
            /* code */
        }
        
    }
    
}
