
#include <stdio.h>
#include <string.h>

#include "HeaderFiles/csvTesting.h"



// get car stock data from csv
void getCarStock(struct carStock* destination[64]) {
  FILE* filePtr = fopen("sample.csv", "r");
  char rawLine[128];
  char* readPtr;
  short r=0; // rowIndex

  while (fgets(rawLine, 128, filePtr)) {
    readPtr = rawLine;

    // allocate struct memory and place
    destination[r] = malloc(sizeof(struct carStock));

    // read line and place in struct
    // the "read head" moves along the line
    readPtr = readString(readPtr, &destination[r]->price);
    readPtr = readString(readPtr, &destination[r]->brand);
    readPtr = readShort(readPtr, &destination[r]->year);
    readPtr = readShort(readPtr, &destination[r]->remaining);

    r++;
  }

  fclose(filePtr);
}

void closeTable(void* table[64]) {
  for (int i=0; i<64; i++) {
    if (table[i] != 0) {
      printf("Freeing: %p\n", table[i]);
      free(table[i]);
    }
  }
}

// read a string field from a record
char* readString(char* readPtr, char* destination) {
  short i=0;
  while ((readPtr[i] != ',') && (i < strlen(readPtr))) {
    printf("%c", readPtr[i]);
    destination[i] = readPtr[i];
    i++;
  }
  printf("\n");
  destination[i] = '\0';
  return &(readPtr[i+2]);
}

// read a short int field from a record
char* readShort(char* readPtr, int* destination) {
  char buffer[64];
  readPtr = readString(readPtr, buffer);
  printf(":: %s\n", buffer);
  *destination = atoi(buffer);
  return readPtr;
}

// read a float field from a record
char* readFloat(char* readPtr, int* destination) {
  char buffer[64];
  readPtr = readString(readPtr, buffer);
  *destination = atof(buffer);
  return readPtr;
}