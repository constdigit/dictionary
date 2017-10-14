///\file
///\brief Define HashMap data structure and functions for work with it

#include <stdbool.h>
#include "Entry.h"

///Hash map data structure that storing Entry elements
typedef struct _HashMap {
    ///array of lists pointers
    Entry ** table;
    ///size of table
    unsigned length;
    ///max elemets count
    unsigned capacity;
    ///current elemets count
    unsigned size;
    ///controls elements count
    unsigned threshold;
} HashMap;

/**
*   Increase length and capacity when
*   size >= threshold
*   \param hashMap resizeable HashMap
*   \return resized HashMap
*/
HashMap * resizeHashMap(HashMap * hashMap);

/**
*   Returns pointer to new HashMap with specified length and capacity
*   \param len, cap length and capacity of new HashMap
*   \return new HashMap
*/
HashMap * createHashMap(unsigned len, unsigned cap);

/**
*   Returns hash for string
*   \param key string for which hash is calculated
*   \return hash code
*/
unsigned long hashCode(char * key);

/**
*   Adds to HashMap new Entry
*   \param hashMap HashMap in which Record is putted
*   \param newRecord putted Record
*   \return new HashMap if it was resized
*/
HashMap * putRecord(HashMap * hashMap, Record * newRecord);

/**
*   Adds to hashMap new word with its interpret
*   \param hashMap HashMap in which Record is putted
*   \param w, i word and its meaning
*   \return new HashMap if it was resized
*/
HashMap * putWord(HashMap * hashMap, char * w, char * i);

/**
*   Searching for Record
*   \param hashMap HashMap in which searching is processed
*   \param w word for searching
*   \return interpretation of word or empty string if w not found
*/
char * getInterpret(HashMap * hashMap, char * w);

/**
*   Delete word from HashMap
*   \param hashMap HashMap in which word will be deleted
*   \param w word to delete
*/
void removeWord(HashMap * hashMap, char * w);
