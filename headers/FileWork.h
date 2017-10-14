///\file
///\brief Functions for file io

#include "../headers/HashMap.h"
/**
*   Getter and setter for name of file with which programm works
*   \param newFileName sets file name, if NULL it works as getter
*   \return current name of file
*/
char * fileName(char * newFileName);

/**
*   Reads data from file that sent as command-line argument
*   \return HashMap populated by data from file
*/
HashMap * readFromFile();

/**
* Save data to file
* \param hashMap data structure that stores all words
*/
void saveToFile(HashMap * hashMap);
