#ifndef KBHIT_H
#define KBHIT_H

#include <termios.h>
#include <sys/ioctl.h>

int kbhit()
{
  static const int STDIN = 0;
  static bool init = false;

  if (!init)
    {
      termios term;
      tcgetattr(STDIN, &term);
      term.c_lflag &= ~ICANON;
      tcsetattr(STDIN, TCSANOW, &term);
      setbuf(stdin, NULL);
      init = true;
    }

  int bytesWaiting;
  ioctl(STDIN, FIONREAD, &bytesWaiting);
  return bytesWaiting;
}

#endif
