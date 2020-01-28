#include"header.h"

int main() {
    const int LIB_SIZE = 1024;
    const int REC_SIZE = 128;

    string words[] = {"FIRST", "CPP", "REVIEW", "PROGRAM", "ASSIGNMENT", "CECS", "BEACH", "ECS", "FALL", "SPRING", "OS", "MAC", "LINUX", "WINDOWS", "LAB"};

    //create the lib array of fixed size 1024
    Document  * lib[LIB_SIZE];

    //dynamic recent list
    Document  * recentList[REC_SIZE];

    //list holding the ejected values
    vector<Document *> ejected;

    //init lists
    cout << "init Lib" << endl;
    //cout << "------------------------------------------------------------------------------" << endl; 
    srand(time(NULL));
    for (int i = 0; i < LIB_SIZE; i++)
    {
        int size = rand()%1000 + 2000;
        //cout << "setting intial size of document#" << i << " to " << size << endl;
        lib[i] = new Document();
        lib[i]->setLength(size);
        lib[i]->initContent();
    }

    cout << "init recent list" << endl;
    //cout << "------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < REC_SIZE; i++)
    {
        int size = rand()%1000 + 2000;
        //cout << "setting intial size of document#" << i << " to " << size << endl;
        recentList[i] = new Document();
        recentList[i]->setLength(size);
        recentList[i]->initContent();
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
        cout << "got " << input << endl;
        for (auto &&word : words)
        {
            if (toupper(input[0]) == word[0]) {
                //cout << "input[0 == word[0]\n"; 
                if (toupper(input[1]) == word[1]) {
                    //cout << "setting input to :" << word << endl;
                    input = word;
                    //break;
                }
            } else if (toupper(input[0]) == 'Q') {
                exited = true;
            }
        }
        if (input[0] != toupper(input[0])) {
            inputError = true;
        }
        if (!exited && !inputError) {
            for (auto &&doc : recentList)
            {
                bool found = doc->findWord(input);
                if (!found) {
                    ejected.push_back(doc);
                    doc = nullptr;
                }
            }
            if (!ejected.empty()) {
                cout << input << ": " << ejected.size() << " documents rejected & reinitialized\n\n";

            }
        } else {
            cout << "ERROR none of the options selected please try again\n";
        }
        cout << "What word would you like to find: " << endl;
        for (int i = 0; i < 15; i++) {
            cout << words[i] << (i+1<15?", ":"\n");
        }
        cout << "Or enter (q)uit" << endl;
    }
    
    cout << "Shutting down ..." << endl;
}

void adjustLists(Document * rec[],Document * lib[],vector<Document*> eject) {
    //adjust recent list
    Document * temp;
    for (int i = 127; i >= 0; i--)
    {
        if (rec[i] == nullptr) {
            int j = i;
            bool exit = false;
            while (j+1 <= 128 && !exit)
            {
                if (rec[j+1] != nullptr) {
                    rec[j]   = rec[j+1];
                    rec[j+1] = nullptr;
                } else {
                    exit = true;
                }
                j++;
            }
        }
    }

    //move top of lib to bottom of rec
    for (int i = 0; i < eject.size(); i++)
    {
        rec[128-eject.size()+i] = lib[i];
        lib[i] = nullptr;
    }
    

    //adjust the lib
    
    
}