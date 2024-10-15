
#ifndef CSVTESTING_INCLUDED
#define CSVTESTING_INCLUDED

struct carStock {
  char price[32];
  char brand[32];
  short year;
  short remaining;
};

void test_csvTesting(void);

void getCarStock(struct carStock* destination[64]);
void closeTable(void* table[64]);

char* readString(char* readPtr, char* destination);
char* readShort(char* readPtr, int* destination);
char* readFloat(char* readPtr, int* destination);

#endif