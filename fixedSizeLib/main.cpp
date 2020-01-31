//William Murray
//
//Program generates 1024 documents of size 2Mb to 3Mb, of random uppercase characters. 
//Program then asks for users choice, and 
#include"header.h"



int main() {
    srand(time(NULL));
    const int LIB_SIZE = 1024;
    const int REC_SIZE = 128;

    string words[] = {"FIRST", "CPP", "REVIEW", "PROGRAM", "ASSIGNMENT", "CECS", "BEACH", "ECS", "FALL", "SPRING", "OS", "MAC", "LINUX", "WINDOWS", "LAB"};

    //create the lib array of fixed size 1024
    map<int,Document*> lib;

    //dynamic recent list
    map<int,Document*> recentList;

    //list holding the ejected values
    map<int,Document*> ejected;

    //init lists
    std::cout << "init Lib" << endl;
    //cout << "------------------------------------------------------------------------------" << endl; 
    
    for (int i = 0; i < LIB_SIZE; i++)
    {
        
        int size = rand()%1000 + 2000;
        //cout << "setting intial size of document#" << i << " to " << size << endl;
        lib.insert(pair<int,Document*>(i,new Document(size)));
    }

    cout << "init recent list" << endl;
    //cout << "------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < REC_SIZE; i++)
    {
        int size = rand()%1000 + 2000;
        //cout << "setting intial size of document#" << i << " to " << size << endl;
        recentList.insert(pair<int,Document*>(i,new Document(size)));
    }
    
    bool exited = false;

    cout << "What word would you like to find: " << endl;
    for (int i = 0; i < 15; i++) {
        cout << words[i] << (i+1<15?", ":"\n");
    }
    cout << "Or enter (q)uit" << endl;
    string input;
    
    while (!exited)
    {
        bool inputError = false;
        // input = new char[256];
        //cout << "before input" << endl; 
        getline(cin, input);
        //cin.get();
        //cout << "got " << input << endl;
        for (auto &&word : words)
        {
            if (toupper(input[0]) == word[0] && toupper(input[1]) == word[1]) {
                input = word;
            } else if (toupper(input[0]) == 'Q') {
                exited = true;
            }
        }
        if (input[0] != toupper(input[0]) && !exited) {
            inputError = true;
        }
        if (!exited && !inputError) {

            
            for (auto const& x : recentList)
            {
                if (!x.second->findWord(input))
                {
                    ejected.insert(pair<int,Document*>(x.first,x.second));
                    recentList.erase(x.first);
                }  
            }
            if (!ejected.empty()) {
                cout << input << ": " << ejected.size() << " documents rejected & reinitialized\n\n";
                adjustLists(recentList,lib,ejected);
                ejected.clear();
            } else {
                cout << input << ": found in all cases, no files reinitialized\n\n";
            }
        }
        if (inputError) {
            cout << "ERROR none of the options selected please try again\n";
        }
        if (!exited)
        {
            cout << "What word would you like to find: " << endl;
            for (int i = 0; i < 15; i++) {
                cout << words[i] << (i+1<15?", ":"\n");
            }
            cout << "Or enter (q)uit" << endl;
        }
    }
    
    cout << "Shutting down ..." << endl;
}

void adjustLists(map<int,Document*> &rec,map<int,Document*> &lib,map<int,Document*> &eject) {
    //adjust recent list
    if (eject.size() < 128) {
        cout << "adjusting the recent list" << endl;
        int currentKey = 0;
        for (auto const& x : rec)
        {
            cout << x.first << endl;
        }
    }

    cout << eject.size() << endl;
    cout << "adding lib files to recent" << endl;
    //move top of lib to bottom of rec
    for (int i = 0; i < eject.size(); i++)
    {
        //cout << "128-eject.size()+i: " << 128-eject.size()+i << endl;
        rec[128-eject.size()+i] = lib[i];
        lib[i] = nullptr;
    }

    cout << "recent list status: " << endl;
    int nulls = 0;
    for (int i = 0; i < 128; i++) {
        if (rec[i] == nullptr) {
            nulls++;
        }
        cout << rec[i] << endl;
    }
    cout << "There are " << nulls << " nullpointers" << endl;

    
    //this list will hold the temp files as we move along the lib
    Document * tempAr[eject.size()];
    Document * temp;
    cout << "adjust the lib" << endl;
    int i = 1023; //start at the last index, we are gonna be moving these up the list
    int tempPlace = 0;
    while (i >= 0)
    {
        //cout << "lib[" << i << "]: " << lib[i] << endl;
        if (tempPlace >= eject.size()) {
            tempPlace = 0;
        }
        if (i < eject.size()) { //dont need to start replacing the values, so just store
            tempAr[tempPlace] = lib[i];
            lib[i] = nullptr;
        } else { //hopefully our shit is solid here so we can just replace vals
            temp = lib[i];
            lib[i] = tempAr[tempPlace];
            tempAr[tempPlace] = temp;
        }
        tempPlace++;
        i--;
    }

    //     cout << "lib status: " << endl;
    // nulls = 0;
    // for (int i = 0; i < 1024; i++) {
    //     if (lib[i] == nullptr) {
    //         nulls++;
    //     }
    //     cout << lib[i] << endl;
    // }
}