// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 748;

// Hash table
node *table[N];
int numberofwords = 0;

//prototype declaration
void lower(char *w);
unsigned int hash(const char *word);
void clear(void);
bool checking(node *ptr, char *w);

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hashnum = 0;
    char tempword[LENGTH + 1];
    node *ptr = NULL;

    strcpy(tempword, word);
    lower(tempword);
    hashnum = hash(tempword);
    ptr = table[hashnum];
    return checking(ptr, tempword);


    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    char temp[LENGTH + 1];
    strcpy(temp, word);
    lower(temp);
    int hashnum = 0;
    int len = strlen(temp);
    if (len < 4)
    {
        for (int i = 0; i < len; i++)
        {
            hashnum += (temp[i] - 39) * (i * 2 + 1);
        }
        return hashnum % N;
    }
    else
    {
        hashnum = (temp[0] - 39) + (temp[1] - 39) * 3 + (temp[2] - 39) * 5;
        return hashnum % N;
    }

    return 0;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    //not sure if clear necessary
    //clear();
    FILE *infile = fopen(dictionary, "r");
    char tempword[LENGTH + 1];
    int hashnum;
    

    if (infile == NULL)
    {
        return false;
    }
    
    //this while loop reads words by word in the dictionary
    while (fscanf(infile, " %46s", tempword) != EOF)
    {
        //THE BIGGEST PROBLEM:
        //mistake: malloc was done outside of while loop, so node was only malloc once
        //resulting in the same node used repeatedly, hence causing all nodes in table to be the last word in dictionary
        //correction: place malloc in while loop so that node is constantly renewed to a new location
        node *nodeone = malloc(sizeof(node));
        if (nodeone == NULL)
        {
            return false;
        }
        lower(tempword);
        hashnum = hash(tempword);
        strcpy(nodeone->word, tempword);

        if (table[hashnum] == NULL)
        {
            table[hashnum] = nodeone;
            nodeone->next = NULL;
            numberofwords += 1;

        }
        else
        {
            nodeone->next = table[hashnum];
            table[hashnum] = nodeone;
            numberofwords += 1;
        }
    }
    fclose(infile);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
//global variable numberofwords is updated along the way
//hence no need to compute in this function
unsigned int size(void)
{
    return numberofwords;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *pointr = table[i];
        while (pointr != NULL)
        {
            node *tempptr = pointr->next;
            free(pointr);
            pointr = tempptr;
        }
    }
    return true;
}

//function "lower" is accepts a pointer to a word
//the word is then modified to all lower case
void lower(char *w)
{
    int len = strlen(w);
    for (int i = 0; i < len; i++)
    {
        w[i] = tolower(w[i]);
    }
    return;
}

//function "clear" is to make sure 
//all the nodes in the table array are pointed to NULL
// NOT NECESSARY (i believe because the table is global, so automatically pointed to NULL for all nodes)
void clear(void)
{
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    return;
}


//function "checking" is to create a recursion 
//it goes from one node to the next until it hits NULL where it terminates 
//returns true if word found, false if not found
bool checking(node *ptr, char *w)
{
    if (ptr != NULL)
    {
        if (strcmp(w, ptr->word) == 0)
        {
            return true;
        }
        else
        {
            ptr = ptr->next;
            return checking(ptr, w);
        }

    }
    return false;
}