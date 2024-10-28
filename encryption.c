
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "HeaderFiles/encryption.h"

void test_encryption(void) {
  
  srand(time(NULL));
  
  char str[] = "Hello world!";
  
  char key[64];
  genKey(key, strlen(str));
  
  char output[64];
  encode(str, key, output);
  printf("%s\n%s\n%s\n", str, key, output);
  
  char original[64];
  decode(output, original);
  printf("%s", original);
  
}


int randint(int a, int b) {
  return (a + (rand() % (b-a)));
}



void genKey(char* destination, const int len) {
  for (int i=0; i<len; i++) {
    destination[i] = (char) (randint(32, 126));
  }
  destination[len] = '\0';
}



void encode(char* string, char* key, char* output) {
  int i=0;
  while (string[i]) {
    output[i] = string[i] ^ key[i];
    i++;
  }
  memcpy(output+i, key, i*sizeof(char));
  output[2*i] = '\0';
}

void decode(char* string, char* output) {
  int len = strlen(string) / 2;
  for (int i=0; i<len; i++) {
    output[i] = string[i] ^ string[len+i];
  }
  output[len] = '\0';
}