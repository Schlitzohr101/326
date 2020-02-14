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
    //temp array to keep a piece of the document in
    int i = 0;
    char temp[word.size()];
    //cout << "ENTERING REC" << endl;
    return findRec(i,word,temp);
}


bool Document::findRec(int index, string word, char temp[]) {
    int n = word.size();
    bool found = false;
    cout << "Testing: \n" << "index: " << index << " of " << length-1 << endl;
    if (index + n < length) {
        int loop = 0;
        //cout << "start loop to create temp" << endl;
        for (int j = index; j < index+n; j++)
        {   
            //cout << "adding " << content[j] << " to temp" << endl;
            temp[loop] = content[j];
            loop++;
        }
        cout << "converting temp to string" << endl;
        string compare = string(temp,n);
        //cout << "deleting temp" << endl;
        //delete temp;
        cout << "Created word: " << compare << endl;
        found = word.compare(compare) == 0;
        if (!found) {
            cout << "NOT FOUND REC AGAIN" << endl;
            return findRec(index+n,word,temp);
        }
    }
    cout << "Exiting the Rec" << endl;
    return found;
}