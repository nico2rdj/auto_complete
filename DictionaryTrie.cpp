#include "util.h"
#include "DictionaryTrie.h"


/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie(){
	root = new trieNode*[SIZE]();
}

trieNode::trieNode(char symbol, bool flag, unsigned int freq){
    this->symbol = symbol;
    this->flag = flag;
    nextList = new trieNode*[SIZE]();
    this->freq = freq;
    }

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
  int size_word = word.length();
  if (size_word == 0)
    return false; 

  trieNode** currentList = root;
  for( int i = 0; i < size_word; i++){
    char symbol = word[i];
    int index = 26;
    if (symbol != ' ')
        index = symbol % (SIZE - 1);

    trieNode* currentNode;

    if(currentList[index] == NULL){
        if( i == size_word-1) {
            currentNode = new trieNode(symbol, true, freq );
        } else {
            currentNode = new trieNode(symbol, false, 0);
        }    
        currentList[index] = currentNode;
    } else {
         currentNode = currentList[index];

        if (i == size_word - 1) {
            if( currentNode->flag == true)
                return false;
            currentNode->flag = true;
        }
    }
    currentList = currentNode->nextList;
    

  }
  
  return true;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const{
 int size_word = word.length();
  if (size_word == 0)
    return false; 

  trieNode** currentList = root;
  for( int i = 0; i < size_word; i++){
    char symbol = word[i];
    int index = 26;
    if (symbol != ' ')
        index = symbol % (SIZE - 1);

    trieNode* currentNode;

    if(currentList[index] == NULL){
        return false;
    } else {
         currentNode = currentList[index];

        if (i == size_word - 1) {
            if( currentNode->flag == true)
                return true;
        }
    }
    currentList = currentNode->nextList;
    

  }
  

return false;
}

/* Return up to num_completions of the most frequent completions
 * of the prefix, such that the completions are words in the dictionary.
 * These completions should be listed from most frequent to least.
 * If there are fewer than num_completions legal completions, this
 * function returns a vector with as many completions as possible.
 * If no completions exist, then the function returns a vector of size 0.
 * The prefix itself might be included in the returned words if the prefix
 * is a word (and is among the num_completions most frequent completions
 * of the prefix)
 */
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
  std::vector<std::string> words;
  return words;
}
 
/* Destructor */
void deleteAll(trieNode ** ptr){
    }

DictionaryTrie::~DictionaryTrie(){
deleteAll(root);

delete root;
}
