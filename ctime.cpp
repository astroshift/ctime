#include <iostream>
#include <sstream>
#include <string>
#include <curses.h>
#include "kbhit.h"
#include "ptime.h"

using namespace std;

int main()
{
  int c,ch,ctml,maxx,maxy,midx,midy,ydln,ydln2;
  int els = 10;
  int hln = 25;

  char ctm[hln], mon[els], wkd[els], yr[els], mnd[els], yd[els], ydl[els];
  time_t t = time(0);
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
      box(stdscr,0,0);
      move(0,0);
      printw("Press q to exit");
      t = time(0);
      today = localtime(&t);
      
      ctmcpy(ctm,today,hln);
      moncpy(mon,today,els);
      wkdcpy(wkd,today,els);
      mndcpy(mnd,today,els);
      yrcpy(yr,today,els);
      ydcpy(yd,today,els);
   
      sum = ((strlen(mon) + strlen(wkd) + strlen(yr) + strlen(mnd) + 3)/2);

      stringstream geek(yd);
      geek >> ydln;

      ydln2 = 365 - ydln;
      sprintf(ydl,"%d",ydln2);      
      
      move((midy/4)*7,midx/4);
      printw("DT:");
      printw(yd);
      printw("/");
      printw(ydl);
      printw(":DL");
      
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
      sleep(150);
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
