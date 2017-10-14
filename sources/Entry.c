#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include "../headers/Entry.h"

char addEntry(Entry ** head, Record * v, unsigned long h) {
    //allocate memory
    Entry * newEntry = (Entry *) malloc(sizeof(Entry));
    if (!newEntry || malloc_usable_size(newEntry) < sizeof(Entry)) {
        fprintf(stderr, "%s\n", "Can't allocate memory.");
        //error code
        return 1;
    }
    //set fields
    newEntry->value = v;
    newEntry->hash = h;

    //if it is empty list
    if (* head == NULL) {
        newEntry->next = NULL;
        * head = newEntry;
    } else {
        //replace head and newEntry
        Entry * temp = * head;
        * head = newEntry;
        newEntry->next = temp;
    }

    return 0;
}

void removeEntry(Entry ** head, unsigned long h) {
    //empty list
    if (* head == NULL) {
        return;
    }

    //if it is a first element in the list
    if ((* head)->hash == h) {
        Entry * temp = * head;
        //new head
        * head = temp->next;
        //delete old head
        removeRecord(temp->value);
        free(temp);
        return;
    }

    //goes through list to find Entry with hash == h
    Entry * previous = * head;
    Entry * current = * head;
    for (; current != NULL; previous = current, current = current->next) {
        if (current->hash == h) {
            //throw over pointer to next node in the list
            previous->next = current->next;
            //delete element
            removeRecord(current->value);
            free(current);
            return;
        }
    }
}

Record getRecord(Entry * head, unsigned long h) {
    //bypassing the list
    while (head != NULL) {
        if (head->hash == h) {
            return *head->value;
        }
        head = head->next;
    }
    //nothing found - return empty Record
    Record empty = {"", ""};
    return empty;
}
