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

  int size_word = prefix.length();
  trieNode** currentList = root;
  bool add_word = false;
  
  trieNode* currentNode;

  if( this->find(prefix) == true){
       
  }

  for( int i = 0; i < size_word; i++){
    char symbol = prefix[i];
    int index = 26;
    if (symbol != ' ')
        index = symbol % (SIZE - 1);

    if(currentList[index] == NULL){
        return words;
    } else {
         currentNode = currentList[index];

        if (i == size_word - 1) {
            if(currentNode->flag == true) {
                add_word = true;
            }
            break;
        }
    }
    currentList = currentNode->nextList;
  }
                      


  pqtype *tmpWords = new pqtype();

  if (add_word == true) {
      tmpWords->push(std::make_tuple(prefix, currentNode->freq));    
  }
  std::string empty("");
  currentNode->recursiveCompletions(tmpWords, empty, prefix );

  for(unsigned int i = 0 ;i < num_completions && !tmpWords->empty(); i++){
      std::tuple<std::string, unsigned int> word= tmpWords->top();
      words.push_back(std::get<0>(word));
      tmpWords->pop();
  }

  return words;
}

void trieNode::recursiveCompletions(pqtype *tmpWords, std::string word, std::string prefix) {
    if( this->nextList == NULL)
           return;

    for( int i = 0; i < SIZE; i++){
       if(this->nextList[i] != NULL){
            if(this->nextList[i]->flag == true){
                std::string end(word);
                end += this->nextList[i]->symbol;
                tmpWords->push(std::make_tuple(prefix + end, this->nextList[i]->freq));
            }

            this->nextList[i]->recursiveCompletions(tmpWords, word + this->nextList[i]->symbol, prefix);


       }
    }
}
 
/* Destructor */
void deleteAll(trieNode ** ptr){
    for( int i = 0; i < SIZE; i++){
       if( (ptr[i]) ){
            deleteAll((ptr[i])->nextList);
            delete(ptr[i]->nextList);            
            delete(ptr[i]);

                }
   
    }
   // if( ptr != NULL)
       // delete(ptr);
    }

DictionaryTrie::~DictionaryTrie(){
deleteAll(root);
delete(root);
}
