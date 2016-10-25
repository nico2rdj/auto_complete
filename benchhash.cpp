#include<iostream>
#include<string>
#include<fstream>
#include<set>
#include<cstdlib>
#include "util.h"
#include "DictionaryTrie.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"
using namespace std;

// from stackflow
unsigned int hashFunction1 (string word, int tableSize)   

{       unsigned int sum = 0;
        for (unsigned int k = 0; k < word.length(); k++)
            sum += (unsigned int) word[k];
        return  sum % tableSize; 
}

// from stackflow
int hashFunction2 (string word, int tableSize)
{
   int seed = 131; 
   unsigned long hash = 0;
   for(unsigned int i = 0; i < word.length(); i++)
   {
      hash = (hash * seed) + word[i];
   }
   return hash % tableSize;
}

// max function of an array
int funMax (int tab[], int size){
    
    int max = tab[0];
    for( int i = 0; i < size ; i++){
        if( tab[i] > max)
            max = tab[i];
    }
    return max;
}

int main(int argc, char** argv){
    
    if(argc != 3){
        cout << " not equal to 2 " << endl;
        return 0;
    }

   
    int num_words = stoi(argv[2]);
    char* dictfile = argv[1];

    ifstream dict1 (dictfile);


    vector<string> words;
    vector<string> words1;

    vector<string>::iterator it;    

    Utils::load_dict(words, dict1, num_words);
    Utils::load_dict(words1, dict1, num_words);
    
    int number_hit[num_words*2] = {0};
    int number_hit1[num_words*2] = {0};

    // computing number of hits in an array 
    for(it = words.begin(); it != words.end(); ++it){
        int index = hashFunction1(*it, num_words*2);
        number_hit[index]++;
    }

    for(it = words1.begin(); it != words1.end(); ++it){
        int index = hashFunction2(*it, num_words*2);
        number_hit1[index]++;
    }

       
    int max = funMax(number_hit, num_words*2);
    int max1 = funMax(number_hit1, num_words*2);
    
    int tabMax[max +1] = {0};
    int tabMax1[max1 + 1] = {0};
   
    // computing total number of hit that receive a slot
    for( int i = 0 ; i < num_words*2; i++){
        tabMax[number_hit[i]] += 1;
        tabMax1[number_hit1[i]] += 1;
    }
    

     cout << "Printing the statistics for hashFunction1 with hash table size " << argv[2] << endl;
     cout << "\n#hits    #slots receiving that #hits" << endl;

     for( int i = 0; i < max + 1; i++){
        cout << i << "     " << tabMax[i] << endl;
     }
        
     //computing the average nulber of step
     double average = 0;
     for( int i = 1; i < max+1; i++){
         int sum = 0;
         for( int j = i; j < max + 1; j++)
             sum += tabMax[j];
        average += sum*i;
     }
     average = average/((double)num_words);

     double average1 = 0;
     for( int i = 1; i < max1+1; i++){
         int sum = 0;
         for( int j = i; j < max1 + 1; j++)
             sum += tabMax1[j];
        average1 += sum*i;
     }
     average1 = average1/((double)num_words);

        
     cout << "The worst case steps that would be needed to find a word is " << max << endl;
     cout << "The average number of steps for a successful search for hash function 1 would be " << average << endl;

     cout << "\nPrinting the statistics for hashFunction1 with hash table size " << argv[2] << endl;
     cout << "\n#hits    #slots receiving that #hits" << endl;

     for( int i = 0; i < max1 + 1; i++){
        cout << i << "     " << tabMax1[i] << endl;
     }
        
     cout << "The worst case steps that would be needed to find a word is " << max1 << endl;
     cout << "The average number of steps for a successful search for hash function 1 would be " << average1 << endl;







}

