#include <fstream>
#include <graphics.h>
#include "relative_coordinates.h"

using namespace std;

ifstream fin("resolution.txt");

short int MAXX, MAXY;

int main()
{
  int i;
  get_maximum();
  initwindow(MAXX,MAXY);
  /*moveto(0,0);
  lineto(50,50);
  lineto(50,100);
  lineto(150,120);*/
  for (i=0;i<=100;i++)
     {
      line(0,relative_to_absolute_value(i,AFTER_HEIGHT),MAXX, relative_to_absolute_value(i,AFTER_HEIGHT));
      line(relative_to_absolute_value(i,AFTER_WIDTH),0,relative_to_absolute_value(i,AFTER_WIDTH), MAXY);
     }
  while(!kbhit());     //wait for user to press a key
  closegraph();        //close graphics window*/
  return 0;
}


void get_maximum()
{
fin>>MAXX>>MAXY;
}
