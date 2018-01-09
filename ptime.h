#ifndef PTIME_H
#define PTIME_H

#include <cstring>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;

int sleep(int ms)
{
  this_thread::sleep_for(chrono::milliseconds(ms));
}

char ctmcpy(char *tar, struct tm *td, int sz)
{
  strftime(tar, sz, "%r",td);
}

char moncpy(char *tar, struct tm *td, int sz)
{
  strftime(tar, sz, "%B", td);
}

char wkdcpy(char *tar, struct tm *td, int sz)
{
  strftime(tar, sz, "%A", td);
}

char mndcpy(char *tar, struct tm *td, int sz)
{
  strftime(tar, sz, "%d", td);
}

char yrcpy(char *tar, struct tm *td, int sz)
{
  strftime(tar, sz, "%Y", td);
}

char ydcpy(char *tar, struct tm *td, int sz)
{
  strftime(tar, sz, "%j", td);
}

#endif
