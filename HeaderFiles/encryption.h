
#ifndef ENCRYPTION_H
#define ENCRYPTION_H

void test_encryption(void);

int randint(int a, int b);
void genKey(char* destination, const int len);
void encode(char* string, char* key, char* output);
void decode(char* string, char* output);

#endif