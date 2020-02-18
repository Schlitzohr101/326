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
    return findRec(word,0,false);
}


bool Document::findRec(string word,int index,bool found) {
    cout << "create n"<<endl;
    int n = word.size();
    cout << "checking \nindex: "<<index<<endl;
    cout << "for document #"<<length<<endl;
    if (index+n < length) {
        char ar[n];
        for (int i = 0; i < n; i++){
            ar[i] = content[index+i];
            cout << "ar#"<<i<<" :"<<ar[i]<<endl;
        }
        found = (word.compare(string(ar)) == 0);
        index += n;
        if (found)
        {
            cout << "found" << endl;
            return true;   
        } else {
            cout << "rec again" << endl;
            try {
                findRec(word,index,found);
            } catch(exception e) {
                cout << "borked rec"<<endl;
            }
        }
    }
    cout << "exiting rec" << endl;
    return false;
    
}