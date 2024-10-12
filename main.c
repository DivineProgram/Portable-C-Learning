#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

#include "csvTesting.h"


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