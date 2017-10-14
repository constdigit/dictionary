#include <stdlib.h>
#include <malloc.h>
#include "../headers/HashMap.h"

//required for counting threshold
const float LOAD_FACTOR = 0.75;

HashMap * createHashMap(unsigned len, unsigned cap) {
    //memory for HashMap structure
    HashMap * hashMap = (HashMap *) malloc(sizeof(HashMap));
    if (!hashMap || malloc_usable_size(hashMap) < sizeof(hashMap)) {
        fprintf(stderr, "%s\n", "Can't allocate memory.");
        return NULL;
    }

    //memory for table array
    hashMap->table = (Entry **) calloc(len, sizeof(Entry *));;
    if (!hashMap->table || malloc_usable_size(hashMap->table) < len * sizeof(Entry *)) {
        fprintf(stderr, "%s\n", "Can't allocate memory.");
        return NULL;
    }

    //other fields
    hashMap->length = len;
    hashMap->capacity = cap;
    hashMap->size = 0;
    hashMap->threshold = cap * LOAD_FACTOR;
    return hashMap;
}

unsigned long hashCode(char * key) {
    //djb2 algorithm
    unsigned long hash = 5381;
    int c;

    while (c = * key++) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

HashMap * putRecord(HashMap * hashMap, Record * newRecord) {
    //get hash
    unsigned long hash = hashCode(newRecord->word);
    //identify index of list in table and add it
    if (addEntry(&hashMap->table[hash & (hashMap->length - 1)], newRecord, hash)) {
        return hashMap;
    }
    hashMap->size++;
    //may be resizing required
    return resizeHashMap(hashMap);
}

HashMap * putWord(HashMap * hashMap, char * w, char * i) {
    Record * newRecord = createRecord(w, i);
    if (!newRecord) {
        return hashMap;
    }
    return putRecord(hashMap, newRecord);
}

char * getInterpret(HashMap * hashMap, char * w) {
    unsigned long hash = hashCode(w);
    //return result of searching in identified list
    return getRecord(hashMap->table[hash & (hashMap->length - 1)], hash).interpret;
}

void removeWord(HashMap * hashMap, char * w) {
    unsigned long hash = hashCode(w);
    //identify list index in table and remove Entry with specified hash
    removeEntry(&hashMap->table[hash & (hashMap->length - 1)], hash);
    hashMap->size--;
}

HashMap * resizeHashMap(HashMap * hashMap) {
    if (hashMap->size > hashMap->threshold) {
        //new HashMap with increased length and capacity
        HashMap * newHashMap = createHashMap(hashMap->length * 2, hashMap->capacity * 2);
        int i;
        Entry * currentEntry, * temp;

        //goes through HashMap.table
        for (i = 0; i < hashMap->length; i++) {
            //goes through each list
            currentEntry = hashMap->table[i];
            while (currentEntry != NULL) {
                //transfer data
                putRecord(newHashMap, currentEntry->value);
                //clears old HashMap
                temp = currentEntry;
                currentEntry = currentEntry->next;
                free(temp);
            }
        }

        //delete old HashMap
        free(hashMap->table);
        free(hashMap);
        return newHashMap;
    }
    return hashMap;
}
