CC=gcc
CFLAGS=-c
SOURCES=../main.c ../sources/Record.c ../sources/Entry.c ../sources/HashMap.c ../sources/FileWork.c
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=dictionary_EProject

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@