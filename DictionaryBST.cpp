#include "util.h"
#include "DictionaryBST.h"

/* Create a new Dictionary that uses a BST back end */
DictionaryBST::DictionaryBST(){
	bst = new std::set<std::string>();		
}

/* Insert a word into the dictionary. */
bool DictionaryBST::insert(std::string word)
{
    if( this->find(word))
	return false;
    bst->insert(word);
    return true;    
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryBST::find(std::string word) const
{
   if(bst->find(word) == bst->end())
	return false;
   return true;
}

/* Destructor */
DictionaryBST::~DictionaryBST(){
	delete(bst);
}
