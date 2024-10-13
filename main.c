#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

#include "HeaderFiles/csvTesting.h"
#include "HeaderFiles/functionWrapper.h"

void nonblock(short state);




int main(void) {

  flexFunc(innerFunc);
  
  struct carStock* table[64] = {0};
  getCarStock(table);
  printf("%s %s %hd %hd\n", table[1]->price, table[1]->brand, table[1]->year, table[1]->remaining);
  closeTable(table);

  nonblock(1);
  printf("!!%c!!\n", getchar());
  nonblock(0);

  char a[5];
  scanf("%s", &a);
  printf("!!%s!!\n", a);
  
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