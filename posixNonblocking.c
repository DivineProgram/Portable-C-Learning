
#include <termios.h>
#include <unistd.h>

#include "HeaderFiles/posixNonblocking.h"



void test_posixNonblocking(void) {
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