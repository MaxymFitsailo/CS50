/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"


struct node {
char* word;
struct node* next;
} node;

struct node* hashTable[676];

int hash(char* word);
int wordsCount=0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word) {
    //prepare word to check.
    char* checkWord=malloc(sizeof(char)*(strlen(word)+1));
    for (int i=0; i<strlen(word); i++) checkWord[i]=tolower(word[i]);
    checkWord[strlen(word)]='\0';

    //check the presence of the word in dictionary
    struct node* cursor=hashTable[hash(checkWord)];
    while(cursor!=NULL) {
        if (strcmp(cursor->word,checkWord)==0) {
            free(checkWord);
            return true;
        }
        else cursor=cursor->next;
    }
    free(checkWord);
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary) {
    FILE* dict=fopen(dictionary,"r");
    while (feof(dict)==0) {
        char* word=malloc(sizeof(char)*(LENGTH+1));
        fscanf(dict,"%s",word);
        if (strcmp(word,"")!=0){
            if (hashTable[hash(word)]==NULL) {
                hashTable[hash(word)]=malloc(sizeof(node));
                hashTable[hash(word)]->word=word;
                hashTable[hash(word)]->next=NULL;
            } else {
                struct node* cursor=hashTable[hash(word)]
                while (cursor->next!=NULL) cursor=cursor->next;
                struct node* newNode=malloc(sizeof(node));
             newNode->word=word;
             cursor->next=newNode
            }
        wordsCount++;
        }

    }
    fclose(dict);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return wordsCount;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void) {
    for (int i=0; i<676; i++) {
        struct node* cursor=hashTable[i];
        while(cursor!=NULL) {
            struct node* tmp=cursor;
            cursor=cursor->next;
            free(tmp);
        }
    }
    return true;
}

int hash(char* word) {
    if(strlen(word)<2) return (int)word[0]-97;
    else return ((int)word[0]-97)*26+(int)word[1]-97;
}
