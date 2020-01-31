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
    //cout << length << endl;
    // string word = "OSFIRSTCPPREVIEWPROGRAMASSIGNMENTCECS";
    // content = new char[word.size()];
    // for (int i = 0; i < word.size(); i++)
    // {//adjust the lib
    //     content[i] = word[i];
    // }
    
    //cout << "-----------------------------------------------" <<endl;
    for (int i = 0; i < length; i++) {
        content[i] = rand()%26 + 65;
        //cout << content[i] << (i+1<length?", ":"\n");
    }
}

int Document::getLength() {
    return length;
}

void Document::setLength(int len) {
    length = len;
}

bool Document::findWord(string word) {
    bool found = false;
    int n = word.size()-1; 
    //cout << "n:" << n << endl;
    //const char * search = word.c_str();
    int i = n;
    while (i < length && !found)
    {
        //if the last char in the search word hits on the current index
        if (word[n] == content[i])
        {
            //cout << "got hit at i:" << i << endl;
            //check the last the last n indexs and see if they are hits as well
            int count = 1;
            int j = i-1;
            found = true;
            while ( j >= i-n && found) {
                if (word[n-count] != content[j]) {
                    //cout << "stopped hitting at j:" << j << endl;
                    found = false;
                }
                count++;
                j--;
            }
        }
        i++;
    }
    return found;
}
