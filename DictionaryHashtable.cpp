#include "util.h"
#include "DictionaryHashtable.h"

/* Create a new Dictionary that uses a Hashset back end */
DictionaryHashtable::DictionaryHashtable(){
	hashtable = new std::unordered_set<std::string>();
}

/* Insert a word into the dictionary. */
bool DictionaryHashtable::insert(std::string word)
{
    if( this->find(word))
	return false;
    hashtable->insert(word);
    return true;  
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryHashtable::find(std::string word) const
{
   if(hashtable->find(word) == hashtable->end())
	return false;
   return true;

}

/* Destructor */
DictionaryHashtable::~DictionaryHashtable(){
	delete(hashtable);
}
