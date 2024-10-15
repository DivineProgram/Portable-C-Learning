#include <stdio.h>

#include "HeaderFiles/csvTesting.h"
#include "HeaderFiles/functionWrapper.h"
#include "HeaderFiles/posixNonblocking.h"
#include "HeaderFiles/recursiveSorting.h"





int main(void) {

  test_functionWrapper();

  test_csvTesting();

  test_posixNonblocking();

  test_recursiveSorting();

}

