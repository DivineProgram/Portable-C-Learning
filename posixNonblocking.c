
#include <termios.h>
#include <unistd.h>

#include "HeaderFiles/posixNonblocking.h"



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