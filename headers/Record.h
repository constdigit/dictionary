///\file
///\brief Define Record structure

///Represents word and its interpretation
typedef struct _Record {
    char * word;
    char * interpret;
} Record;

/**
*   Create new Recrod for word ant its meaning
*   \param w, i word and its interpretation
*   \return pointer to new Record
*/
Record * createRecord(char * w, char * i);

/**
*   Free all fields and it self
*   \param rec pointer to Record which must be deleted
*/
void removeRecord(Record * rec);
