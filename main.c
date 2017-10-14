///\file
///\represents the UI

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "headers/FileWork.h"

///Maximum avalible length of word in dictionary (with null-terminator)
const int MAX_WORD_LENGTH = 129;
///Esc key code
const char ESC = 27;

/**
* Clears input stream
*/
void clearStdin() {
    while (getchar() != '\n');
}

/**
*   Searchs for word inputed by user and prints its interpretation
*   \param hashMap HashMap in which searching is processed
*/
void searching(HashMap * hashMap) {
    char word[MAX_WORD_LENGTH];
    printf("%s", "Type word for searching: ");
    //scan word
    scanf("%[^\n]s",word);
    word[MAX_WORD_LENGTH - 1] = '\0';
    //truncate excess characters
    clearStdin();
    //try to get interpretation
    char * interpret = getInterpret(hashMap, word);
    if (!strlen(interpret)) {
        //error
        printf("%s\n", "Word not found");
        return;
    } else {
        //print result
        printf("%s - %s\n", word, interpret);
    }
}

/**
*   Adds word inputed by user
*   \param hashMap HashMap in which word is adding
*   \return Resized HashMap if resizing was occured
*/
HashMap * adding(HashMap * hashMap) {
    char word[MAX_WORD_LENGTH];
    char key;
    printf("%s", "Type word for adding: ");
    //scan word
    scanf("%[^\n]s",word);
    word[MAX_WORD_LENGTH - 1] = '\0';
    //truncate excess characters
    clearStdin();

    //this word already in HashMap
    if (strlen(getInterpret(hashMap, word))) {
        printf("%s\n", "This word already exist. Do you want to replace it? [y/n]");

        //handle user selection
        do {
            key = getchar();
        } while (key != 'y' && key != 'Y' && key != 'n' && key != 'N');

        //decline
        if (key == 'n' || key == 'N') {
            return hashMap;
        } else {
            //accept
            removeWord(hashMap, word);
        }
    }

    printf("%s", "Type interpretation of word: ");
    char * interpret = (char *) malloc(sizeof(char));
    if (!interpret) {
        fprintf(stderr, "%s\n", "Can't allocate memory.");
        return hashMap;
    }
    int len = 0;
    key = 0;
    //scan interpretation
    while (key != '\n') {
        key = getchar();
        if (key != '\n') {
            //append new character
            interpret = (char *) realloc(interpret, (len + 1) * sizeof(char));
            if (!interpret
                || malloc_usable_size(interpret) < (len + 1) * sizeof(char)) {
                fprintf(stderr, "%s\n", "Can't allocate memory.");
                return hashMap;
            }
            interpret[len] = key;
            len++;
        } else {
            //stop scanning
            interpret = (char *) realloc(interpret, (len + 1) * sizeof(char));
            if (!interpret
                || malloc_usable_size(interpret) < (len + 1) * sizeof(char)) {
                fprintf(stderr, "%s\n", "Can't allocate memory.");
                return hashMap;
            }
            interpret[len] = '\0';
        }
    }

    //add to HashMap if input is correct
    if (strlen(interpret)) {
        return putWord(hashMap, word, interpret);
    } else {
        printf("%s\n", "Error: empty interpretation");
        return hashMap;
    }
}

/**
*   Deletes inputed word
*   \param hashMap HashMap in which deleting is processing
*/
void deleting(HashMap * hashMap) {
    char word[MAX_WORD_LENGTH];
    printf("%s", "Type word for deleting: ");
    //scan word
    scanf("%[^\n]s",word);
    word[MAX_WORD_LENGTH - 1] = '\0';
    //truncate excess characters
    clearStdin();
    removeWord(hashMap, word);
}

/**
*   Prints all words
*   \param hashMap HashMap that stores words
*/
void showAll(HashMap * hashMap) {
    if (!hashMap->size) {
        printf("%s\n", "Dictionary is empty");
        return;
    }
    char key = 0;
    int i, j = 1;
    Entry * currentEntry;
    //goes through all HashMap
    for (i = 0; i < hashMap->length; i++) {
        for (currentEntry = hashMap->table[i]; currentEntry != NULL; currentEntry = currentEntry->next) {
            printf("%d. %s - %s\n", j,
                currentEntry->value->word, currentEntry->value->interpret);

            //print by batch
            if (j % 10 == 0) {
                printf("%s\n", "Print next 10 words? [y/n]");
                do {
                    key = getchar();
                    clearStdin();
                } while (key != 'y' && key != 'Y' && key != 'n' && key != 'N');

                //stop printing
                if (key == 'n' || key == 'N') {
                    //make indent
                    putchar('\n');
                    return;
                }
            }
            j++;
        }
    }
    //make indent
    putchar('\n');
}

int main(int argc, char * argv[]) {
    HashMap * dictionary;
    if (argc == 1) {
        //no arguments
        dictionary = createHashMap(8, 50);
    } else {
        //set file name from command-line argument
        fileName(argv[1]);
        dictionary = readFromFile();
    }

    //creating HashMap error
    if (!dictionary) {
        return 0;
    }

    //programm menu
    char key;
    do {
        printf("1. %s\n2. %s\n3. %s\n4. %s\n%s\n",
        "Search word.", "Add word.", "Delete word.", "Show all words.", "Press Esc to exit.");
        key = getchar();
        clearStdin();
        switch (key) {
            case '1': searching(dictionary); break;
            case '2': dictionary = adding(dictionary); break;
            case '3': deleting(dictionary); break;
            case '4': showAll(dictionary); break;
        }
    } while (key != ESC);

    if (dictionary->size) {
        saveToFile(dictionary);
    }
    return 0;
}
