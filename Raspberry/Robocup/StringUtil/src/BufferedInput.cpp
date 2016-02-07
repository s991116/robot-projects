#include <BufferedInput.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#define TSCANOW (0)

void BufferedInput::off(void) {
  tcgetattr(STDIN_FILENO, &t); //get the current terminal I/O structure
  t.c_lflag &= ~ICANON; //Manipulate the flag bits to do what you want it to do
  tcsetattr(STDIN_FILENO, TSCANOW, &t); //Apply the new settings
}

void BufferedInput::on(void) {
  tcgetattr(STDIN_FILENO, &t);
  t.c_lflag |= ICANON; //Manipulate the flag bits to do what you want it to do
  tcsetattr(STDIN_FILENO, TSCANOW, &t); //Apply the new settings
}

int BufferedInput::getch() {
  int ch;
  struct termios oldt, newt;
  long oldf, newf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &=  ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TSCANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  newf = oldf | O_NONBLOCK;
  fcntl(STDIN_FILENO, F_SETFL, newf);
  ch = getchar();
  fcntl(STDIN_FILENO, F_SETFL, oldf);
  tcsetattr(STDIN_FILENO, TSCANOW, &oldt);
  return ch;
}
