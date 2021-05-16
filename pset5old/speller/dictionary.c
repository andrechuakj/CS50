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
// can change 
const unsigned int N = 121147;
int numword = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false

//string -> passed thru hash to get an integer -> goes to that integer in the table[]
//-> goes thru the linked list one node at a time to check if string exists in dictionary
//-> if yes, return true,, else return false
bool check(const char *word)
{
    // TODO
    char *tempword = NULL;
    int hashnum;
    node *tempn;
    char copy[LENGTH + 1];
    strcpy(tempword, word);
    
    lower(tempword);
    hashnum = hash(tempword);
    tempn = table[hashnum];
    do
    {
        if (strcasecmp(word, tempn->word) == 0)
        {
            return true;
        }
        else 
        {
            tempn = tempn->next;
        }
    }while(tempn != NULL);
    
    return false;
}

// Hashes word to a number

//turns string into lowercase
//turns first 3 char into a number eg A -> 1, B -> 2 etc
//hash#1: string[0] * 1 + string[1] * 3 + string[2] * 5
unsigned int hash(const char *word)
{
    // TODO
    char copy[LENGTH + 1];
    strcpy(copy, word);
    lower(copy);
    int hash = 0;
    int length = strlen(copy);
    int g = 31;
    
    if (length < 4)
    {
        for (int i = 0; i < length; i++)
        {
            hash = hash * g + copy[i];
        }
        return hash;
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            hash = hash * g + copy[i];
        }
        return hash;
    }
    
    return 0;
}

// Loads dictionary into memory, returning true if successful else false
//open file -> 
//false scenarios: dictionary == NULL,, 
bool load(const char *dictionary)
{
    // TODO
    char w[LENGTH];
    FILE *infile = fopen(dictionary, "r");
    node *temp;
    node *temp1;

    int hashnum;
    
    if (infile == NULL)
    {
        return false;
    }
    while (fscanf(infile, "%s", w) != EOF)
    {
        temp = malloc(sizeof(node));
        if (temp == NULL)
        {
            return false;
        }
        strcpy(temp->word, w);
        temp->next = NULL;
        hashnum = hash(w);
        
        if (table[hashnum] == NULL)
        {
            table[hashnum] = temp;
            numword++;
        }
        else
        {
            temp1 = malloc(sizeof(node));
            if (temp1 == NULL)
            {
                return false;
            }
            temp1->next = table[hashnum]->next;
            table[hashnum]->next = temp->next;
            temp->next = temp1->next;
            free(temp1);
            numword++;
        }
    }
    
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (numword > 0)
    {
        return numword;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    node *temp;
    node *temp1;
    
    for (int i = 0; i < N; i++)
    {
        temp = table[i];
        do
        {
            temp1 = temp->next;
            free(temp);
            temp = temp1;
        }while (temp != NULL);
    }
    return false;
}

void lower(char str[])
{
    int n = strlen(str);
    for (int i = 0; i < n; i++)
    {
        str[i] = tolower(str[i]);
    }
}