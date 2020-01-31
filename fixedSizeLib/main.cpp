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
    //calculate bottom of recent list
    int recLargest = -1;
    for (auto const& x : rec)
    {
       recLargest = (x.first > recLargest?x.first:recLargest);
    }
    recLargest++;
    
    cout << "made it past the rec list cal" << endl;

    //add top lib files to recent
    while (rec.size() <= 128)
    {
        int i = 0;
        try {
            rec[recLargest] = lib.at(i);
            lib.erase(i);
        } catch (exception e){
            cout << "broke it" << endl;
        }
        i++;
    }



    int libLargest = -1;
    for (auto const& x : lib)
    {
       libLargest = (x.first > libLargest?x.first:libLargest);
    }
    libLargest++;
    for (auto const& x : eject)
    { 
        x.second->initContent();
        lib[libLargest] = x.second;
        libLargest++;
    }
    
    //clear ejected
    eject.clear();

}