
#include <stdio.h>

#include "HeaderFiles/recursiveSorting.h"



void test_recursiveSorting(void) {
  printf("Sum of 1000: %d\n", sum(1000));

  // len: 11     0 1 2  3 4/5 6 7 8 9 10
  int array[] = {6,9,8,10,2,1,4,7,0,3,5};
  // printf("%d %d", *array, *(array + 5));
  mergeSort(array, 11);
  for (int i=0; i<11; i++) {
    printf("- %d\n", array[i]);
  }
}



void mergeSort(int* arrPtr, short len) {
  int lenL = len/2; // 5
  int lenR = len-lenL; // 6
  int* leftPtr = arrPtr;
  int* rightPtr = arrPtr + lenL;

  if (len > 1) {
    mergeSort(leftPtr, lenL);
    mergeSort(rightPtr, lenR);
  }

  int result[len];

  int l=0, r=0;
  for (int i=0; i<len; i++) {
    if (*leftPtr <= *rightPtr) {
      result[i] = *leftPtr;
      if (l<lenL-1) {
        leftPtr++;
        l++;
      } else {
        *leftPtr = 999;
      }
    } else {
      result[i] = *rightPtr;
      if (r<lenR-1) {
        rightPtr++;
        r++;
      } else {
        *rightPtr = 999;
      }
    }
  }

  memcpy(arrPtr, result, len*sizeof(int));
}

int sum(int x) {
  if (x >= 1) {
    int a = x + sum(x-1);
    return a;
  } else {
    return 0; 
  }
}