#include <iostream>
#include <sstream>
#include <ctime>
#include <cstring>
#include <curses.h>
#include <string>
#include <thread>
#include <chrono>
#include <termios.h>
#include <sys/ioctl.h>
#define MST (-7)

int kbhit();

using namespace std;

int main()
{
  int c,ch,ctml,maxx,maxy,midx,midy,ydln,ydln2;

  char ctm[25], mon[10], wkd[10], yr[10], mnd[10], yd[10], ydl[10];
  time_t t = time(0);
  char *timestr;
  const char *hrtime, *mintime, *sectime;
  struct tm *today = localtime(&t);
  
  initscr();

  maxx = getmaxx(stdscr);
  maxy = getmaxy(stdscr);

  midy = maxy/2;
  midx = maxx/2;
  
  while(1)
    {
      int sum = 0;
      curs_set(0);
      move(0,0);
      printw("Press q to exit");
      t = time(0);
      today = localtime(&t);
      
      strftime(ctm, sizeof(ctm), "%r", today);
      strftime(mon, sizeof(mon), "%B", today); //full month name
      strftime(wkd, sizeof(wkd), "%A", today); //full weekday name
      strftime(mnd, sizeof(mnd), "%d", today); //day of the month 
      strftime(yr, sizeof(yr), "%Y", today); //current year into string
      strftime(yd, sizeof(yd), "%j", today);
           
      sum = ((strlen(mon) + strlen(wkd) + strlen(yr) + strlen(mnd) + 3)/2);

      stringstream geek(yd);
      geek >> ydln;

      ydln2 = 365 - ydln;
      sprintf(ydl,"%d",ydln2);
      
      move(midy/2,midx/3);
      printw(yd);
      printw("/");
      printw(ydl);
      
      move(midy-1,midx-sum);
      printw(wkd);
      printw(" ");
      printw(mon);
      printw(" ");
      printw(mnd);
      printw(" ");
      printw(yr);

      ctml = (strlen(ctm)/2);
      
      move(midy,midx-ctml);
      printw(ctm);
      
      refresh();
      this_thread::sleep_for(chrono::milliseconds(150));
      clear();

      if(kbhit())
	{
	  ch = getch();
	  if(ch == 'q')
	    {
	      fflush(stdout);
	      break;
	    }
	}

      refresh();
    }
  clear();
  endwin();
}

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
