// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

#define HASHTABLE_SIZE 10000

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
//const unsigned int N = 1;

// Hash table
//node *table[N];

node *hashtable[HASHTABLE_SIZE];

// Now hash the word. Word needed to hash is contained in a new node,
//arrow, word. Hashing will supply the index. after insert word in to 
// linked list.

int hash_index(char *hash_this)
{
    
    unsigned int hash = 0;
    for (int i = 0, n = strlen(hash_this); i < n; i++)
    {
        hash = (hash << 2) ^ hash_this[i];
    }
    return hash % HASHTABLE_SIZE;
}

// initiliase counter for the words in dictionary
int word_count = 0;


// load dictionary into memory, return true of success else false
bool load(const char *dictionary)
{
    //opens dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    // scan word by word to add to hash table with nodes containing words found in the dictionary
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        //malloc a node for each new word (create node pointers)
        node *new_node = malloc(sizeof(node));
        //check if success, return false if not
        if (new_node == NULL)
        {
            unload();
            return false;
        }
        //copy word into new node if malloc succeeds
        strcpy(new_node->word, word);
        
        //initialise + calculate index of word for insertion into hashtable
        int h = hash_index(new_node->word);
        
        //head to pint to hastable bucket
        node *head = hashtable[h];
        
        // insert new nodes at beginning of lists
        if (head == NULL)
        {
            hashtable[h] = new_node;
            word_count++;
        }
        else
        {
            new_node->next = hashtable[h];
            hashtable[h] = new_node;
            word_count++;
        }
    }
    fclose(file);
    return true;
}


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    //create copy of word on which hash function can be performed
    int n = strlen(word);
    char word_copy[LENGTH + 1];
    for (int i = 0; i < n; i++)
    {
        word_copy[i] = tolower(word[i]);
    }
    // add \n to word
    word_copy[n] = '\0';
    //index for hashed word
    int h = hash_index(word_copy);
    //set cursor to point to same address as bucket
    node *cursor = hashtable[h];
    
    //if word exists, it will be in the dictionary data structure. 
    // check b y asking; hashtable[hash(word)]
    //while the cursor doesnt point to NULL, search fictionary for word
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word_copy) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    //if cursor reached end of list and word not found == it is misspelt
    return false;
}

// return number of words in dictionary if oaded else 0 not loaded
unsigned int size(void)
{
    return word_count;
}

//unload dictionary from memory, return true if sucessful
bool unload(void)
{
    node *head = NULL;
    node *cursor = head;
    while (cursor != NULL)
    {
        node *temp = cursor;
        cursor = cursor->next;
        free(temp);
    }
    return true;
}
