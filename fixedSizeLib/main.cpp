#include"header.h"

int main() {
    const int LIB_SIZE = 1024;
    const int REC_SIZE = 128;

    string words[] = {"FIRST", "CPP", "REVIEW", "PROGRAM", "ASSIGNMENT", "CECS", "BEACH", "ECS", "FALL", "SPRING", "OS", "MAC", "LINUX", "WINDOWS", "LAB"};

    //create the lib array of fixed size 1024
    Document  * lib[LIB_SIZE];

    //dynamic recent list
    Document  * recnet_list[REC_SIZE];

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
        recnet_list[i] = new Document();
        recnet_list[i]->setLength(size);
        recnet_list[i]->initContent();
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
        // input = new char[256];
        //cout << "before input" << endl; 
        getline(cin, input);
        //cin.get();
        cout << "got " << input << endl;
        for (auto &&word : words)
        {
            if (toupper(input[0]) == word[0]) {
                if (toupper(input[1]) == word[1]) {
                    input = word;
                    break;
                }
            } else if (toupper(input[0]) == 'Q') {
                exited = true;
            }      
        }
        if (!exited) {
            for (auto &&doc : recnet_list)
            {
                bool found = doc->findWord(input);
                if (!found) {
                    ejected.push_back(doc);
                    doc = new Document();
                }
            }
            if (!ejected.empty()) {
                cout << input << ": " << ejected.size() << " documents rejected & reinitialized";

            }
        }
    }
    
    cout << "Shutting down ..." << endl;
}

void adjustRec(Document * rec[]) {
    for (int i = 0; i < 128; i++)
    {
        
    }
    
}