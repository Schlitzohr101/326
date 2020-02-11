//William Murray
//main.cpp document.cpp document.h header.h
//Program main. Creates maps for lib and recent list, as well as the ejected list
//program logic for taking inputs for selections, and processing based on selection
#include"header.h"

int main() {
    srand(time(NULL));
    const int LIB_SIZE = 1024;
    const int REC_SIZE = 128;

    string words[] = {"FIRST", "CPP", "REVIEW", "PROGRAM", "ASSIGNMENT", "CECS",
    "BEACH", "ECS", "FALL", "SPRING", "OS", "MAC", "LINUX", "WINDOWS", "LAB"};

    //create the main lib 
    map<int,Document*> lib;

    //dynamic recent list lib
    map<int,Document*> recentList;

    //list holding the ejected documents indexes in rec list
    map<int,int> ejected;

    //init maps
    for (int i = 0; i < LIB_SIZE; i++)
    {
        //int size = rand()%1000000 + 2000000;
        lib[i] = new Document(size);
        //lib.insert(pair<int,Document*>(i,new Document(size)));
    }
    for (int i = 0; i < REC_SIZE; i++)
    {
        int size = rand()%1000 + 2000;
        //int size = rand()%1000000 + 2000000;
        recentList.insert(pair<int,Document*>(i,new Document(size)));
    }
    

    //Program loop init
    bool exited = false;
    cout << "What word would you like to find: " << endl;
    for (int i = 0; i < 15; i++) {
        cout << words[i] << (i+1<15?", ":"\n");
    }
    cout << "Or enter (q)uit: ";
    string input;
    
    while (!exited)
    {
        bool inputError = false;
        getline(cin, input);
        //input handeling
        bool isInt = true;
        try {
            stoi(input);
        } catch (exception e) {
            isInt = false;
            //check what was entered against all words
            for (auto &&word : words)
            {
                //if the first two characters match, then set the input to the word
                if (toupper(input[0]) == word[0] && toupper(input[1]) == word[1]) {
                    input = word;
                } else if (toupper(input[0]) == 'Q') {
                    exited = true;
                }
            }
        }
        //set input error to if the input was a int
        inputError = isInt;
        if (input[0] != toupper(input[0]) && !exited) {
            inputError = true;
        }
        //if the input wasn't garbage search for word
        if (!exited && !inputError) {
            int index = 0;
            for (auto const& recDoc : recentList)
            {
                if (!recDoc.second->findWord(input))
                {
                    //if found add index to ejected lib
                    ejected.insert(pair<int,int>(index,recDoc.first));
                    index++;
                }  
            }
            //adjust libs if need be
            if (!ejected.empty()) {
                cout << input << ": " << ejected.size() << " documents rejected & reinitialized\n\n";
                adjustLibs(recentList,lib,ejected);
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
            cout << "Or enter (q)uit: ";
        }
    }
    
    cout << "Shutting down ..." << endl;
}

//adds to end of recent from beginning of lib, reinits ejected docs to the 
//end of lib with their previous lengths
void adjustLibs(map<int,Document*> &rec,map<int,Document*> &lib,map<int,int> &eject) {
    //store lengths of all ejected documents
    //delete all indexes stored in eject from rec lib
    int ar[eject.size()];
    for (int i = 0; i < eject.size(); i++)
    {
        ar[i] = rec[eject[i]]->getLength();
        rec.erase(eject[i]);
    }

    //calculate the largest index in rec list
    int lrgstRecInd = -1;
    for (auto &&x : lib)
    {
        lrgstRecInd = (x.first>lrgstRecInd?x.first:lrgstRecInd);
    }
    lrgstRecInd++; // no duplicates allowed in map

    //calculate largest index in lib
    int lrgstLibInd = -1;
    for (auto &&x : lib)
    {
        lrgstLibInd = (x.first>lrgstLibInd?x.first:lrgstLibInd);
    }
    lrgstLibInd++;

    //add top lib files to recent
    int index = lrgstRecInd-1024;
    while (rec.size() < 128)
    {
        try {
            pair<map<int,Document*>::iterator, bool> didInsert = 
                rec.insert(pair<int,Document*>(lrgstRecInd,lib.at(index)));
                
            if (didInsert.second) {
                lib.erase(index);
                lrgstRecInd++;
            }
        } catch (exception e){
            cout << "EXCEPTION" << endl;
        } //handle any time there is a skip in the lib
        index++; 
    }

    //reint the lib
    for (int i = 0; i < eject.size(); i++)
    {
        try {
            lib.insert(pair<int,Document*>(lrgstLibInd,new Document(ar[i])));
        } catch (exception e) {
            cout << "falied to put back in lib\nlargest index used was invalid" 
                 << endl;
        }
        lrgstLibInd++;
    }
    
    //clear ejected
    eject.clear();

}