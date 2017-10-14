#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "../headers/Record.h"

Record * createRecord(char * w, char * i) {
    //allocate memory
    Record * newRecord = (Record *) malloc(sizeof(Record));
    if (!newRecord || malloc_usable_size(newRecord) < sizeof(Record)) {
        fprintf(stderr, "%s\n", "Can't allocate memory.");
        return NULL;
    }

    newRecord->word = (char *) calloc(strlen(w) + 1, sizeof(char));
    newRecord->interpret = (char *) calloc(strlen(i) + 1, sizeof(char));

    if (!newRecord->word || !newRecord->interpret
        || malloc_usable_size(newRecord->word) < strlen(w) * sizeof(char)
        || malloc_usable_size(newRecord->interpret) < strlen(i) * sizeof(char)) {
        fprintf(stderr, "%s\n", "Can't allocate memory.");
        return NULL;
    }

    //copy strings to Record
    stpcpy(newRecord->word, w);
    stpcpy(newRecord->interpret, i);

    return newRecord;
}

void removeRecord(Record * rec) {
    free(rec->word);
    free(rec->interpret);
    free(rec);
}
