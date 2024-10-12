#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>


struct carStock {
  char price[32];
  char brand[32];
  short year;
  short remaining;
};



void getCarStock(struct carStock* destination[64]);
void closeTable(void* table[64]);

char* readString(char* readPtr, char* destination);
char* readShort(char* readPtr, int* destination);
char* readFloat(char* readPtr, int* destination);

void innerFunc(void);
void flexFunc(void (*func)(void));

void nonblock(short state);




int main(void) {
  
  struct carStock* table[64] = {0};
  getCarStock(table);
  printf("%s %s %hd %hd\n", table[1]->price, table[1]->brand, table[1]->year, table[1]->remaining);
  closeTable(table);

  nonblock(1);
  printf("!!%c!!", getchar());
  nonblock(0);

  char a[5];
  scanf("%s", &a);
  printf("!!%s!!", a);
  
}


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



// FUNCTION POINTERS TESTING

void innerFunc(void) {
  printf("\tInner function\n");
}

void flexFunc(void (*func)(void)) {
  printf("Pre-function\n");
  func();
  printf("Post-function\n");
}



// NON CANONICAL INPUT

void nonblock(short state) {
  struct termios ttystate;
  tcgetattr(STDIN_FILENO, &ttystate);
  // turn off canonical mode
  if (state) {
    ttystate.c_lflag &= ~ICANON;
    ttystate.c_cc[VMIN] = 1;
  } 
  // turn on canonical mode
  else { 
    ttystate.c_lflag |= ICANON;
  }
  tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}