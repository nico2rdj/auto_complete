#include<iostream>
#include<string>
#include<fstream>
#include<algorithm>
#include<set>
#include<cstdlib>
#include "util.h"
#include "DictionaryTrie.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"
#define LETTERS 26
#define MANY_TIMES 10
using namespace std;


int main( int argc, char** argv){

    if(argc != 5){
        cout << " not equal to 4 " << endl;
        return 0;
    }

    int min_size = stoi(argv[1]);
    int step_size = stoi(argv[2]);
    int num_iterations = stoi(argv[3]);
    char* dictfile = argv[4];

    ifstream dict1 (dictfile);
    ifstream dict2 (dictfile);
    ifstream dict3 (dictfile);
    ifstream dict4 (dictfile);

    const string print_array[] = {"DictionaryTrie", "DictionaryBST", "DictionaryHashtable"};
   
    for (int i = 0; i < 3; i++) {
        cout << print_array[i] << endl;
        ifstream dict(dictfile);

        for( int j = 0; j < num_iterations; j++){
            DictionaryBST d_bst;
            DictionaryHashtable d_ht;
            DictionaryTrie dt;

            // clear all fail and eof bits
            // reset back to start of file
            dict1.clear();                 
            dict1.seekg(0, std::ios::beg); 
            
            // choosing the type of Trie
            switch (i) {
                case 0:
                    Utils::load_dict(dt,dict1, min_size+j*step_size);
                    break;
                case 1:
                    Utils::load_dict(d_bst,dict1, min_size+j*step_size);
                    break;
                case 2:
                    Utils::load_dict(d_ht,dict1, min_size+j*step_size);
                    break;                 
            }
            
            vector<string> words;
            vector<string>::iterator it;            
            Utils::load_dict(words, dict1, 100);
            Timer t1;
            long long tot1 = 0;
            
            // computing the average time of each type of Trie
            for(int k = 0; k < MANY_TIMES; k++) {
                 t1.begin_timer(); 
                 for(it = words.begin(); it != words.end(); ++it){
                    switch (i) {
                        case 0:
                            dt.find(*it);
                            break;
                        case 1:
                            d_bst.find(*it);
                            break;
                        case 2:
                            d_ht.find(*it);
                            break;                  
                    }

                 }
                 tot1 += t1.end_timer();      
            }

            long long avg = tot1/MANY_TIMES;

            cout << min_size+j*step_size << '\t'<< avg << endl;

        }
        cout << endl;
    } 
}
