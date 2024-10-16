
#include <stdio.h>

#include "HeaderFiles/functionWrapper.h"



void test_functionWrapper(void) {
  flexFunc(innerFunc);
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