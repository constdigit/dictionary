#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "../headers/FileWork.h"

char * fileName(char * newFileName) {
    //default file
    static char * currentFileName = "dictionary_file.txt";
    //custom file
    if (newFileName) {
        currentFileName = newFileName;
    }
    return currentFileName;
}

HashMap * readFromFile() {
    HashMap * hashMap = createHashMap(8, 50);
    //open file
    FILE * dictionary_file = fopen(fileName(NULL), "r");
    if (!dictionary_file) {
        fprintf(stderr, "%s\n", "Opening file error");
        return NULL;
    }

    //read file by char
    char c;
    char * word, * interpret;
    //keeps readed lines
    char * buffer = (char *) calloc(1, sizeof(char));
    if (!buffer) {
        fprintf(stderr, "%s\n", "Can't allocate memory.");
        return NULL;
    }
    //current line length, index of separator
    int len = 0, bufferCapacity = 1;
    while(!feof(dictionary_file)) {
       c = fgetc(dictionary_file);
       //handle error
       if (ferror(dictionary_file)) {
           return NULL;
       }
       if (c != '\n') {
           //append character to buffer
           if (len == bufferCapacity) {
               bufferCapacity++;
               buffer = (char *) realloc(buffer, bufferCapacity * sizeof(char));
               if (!buffer || malloc_usable_size(buffer) < bufferCapacity * sizeof(char)) {
                   fprintf(stderr, "%s\n", "Can't allocate memory.");
                   return NULL;
               }
           }
           buffer[len] = c;
           len++;
       } else {
           //add null-terminator
           if (len == bufferCapacity) {
               bufferCapacity++;
               buffer = (char *) realloc(buffer, bufferCapacity * sizeof(char));
               if (!buffer || malloc_usable_size(buffer) < bufferCapacity * sizeof(char)) {
                   fprintf(stderr, "%s\n", "Can't allocate memory.");
                   return NULL;
               }
           }
           buffer[len] = '\0';
           //split by separator == '\t'
           word = strtok(buffer, "/");
           interpret = strtok(NULL,"/");
           hashMap = putWord(hashMap, word, interpret);
           //restore buffer, because strtok is destructive
           buffer[strlen(word)] = '/';
           buffer[len] = '\0';
           len = 0;
       }
    }
    free(buffer);
    fclose(dictionary_file);
    return hashMap;
}

void saveToFile(HashMap * hashMap) {
    FILE * dictionary_file = fopen(fileName(NULL), "w");
    char key;
    //handle error
    if (!dictionary_file) {
        printf("%s\n", "Invalid file. Data will be saved to default file (dictionary_file.txt) at programm folder.");
        //try to open new file
        dictionary_file = fopen("dictionary_file.txt", "w");
    }

    int i;
    Entry * currentEntry;
    //goes through all HashMap
    for (i = 0; i < hashMap->length; i++) {
        for (currentEntry = hashMap->table[i]; currentEntry != NULL; currentEntry = currentEntry->next) {
            //writting
            fprintf(dictionary_file, "%s/%s\n",
                currentEntry->value->word, currentEntry->value->interpret);
            //free memory
            removeEntry(&hashMap->table[i], currentEntry->hash);
        }
    }

    free(hashMap->table);
    free(hashMap);
    fclose(dictionary_file);
}
