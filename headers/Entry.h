///\file
///\brief Define Entry data structure

#include "Record.h"

///Each element in HashMap
typedef struct _Entry {
    Record * value;
    unsigned long hash;
    struct _Entry * next;
} Entry;

/**
*   Creates a new entry and adds it to the  list
*   \param head address of pointer to beginning of list
*   \param v value field of new Entry
*   \param h hash
*   \return 0 on succes, 1 otherwise
*/
char addEntry(Entry ** head, Record * v, unsigned long h);

/**
*   Removes Entry from list
*   \param head address of pointer to beginning of list from which Entry will be deleted
*   \param h hash
*/
void removeEntry(Entry ** head, unsigned long h);

/**
*   Returns value field of Entry with hash == h
*   \param head beginning of list in which searching are processing
*   \param h hash
*   \return Record that stores in searched Entry or empty Record if nothing found
*/
Record getRecord(Entry * head, unsigned long h);
