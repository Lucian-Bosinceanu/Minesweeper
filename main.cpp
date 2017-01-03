#include <fstream>
#define MAX_CS 5
#include "button.h"


using namespace std;

short int MAXX, MAXY;

void get_maximum();
void init_graphics();
void init_color_schemes();

relative_rectangle buttonR;
click_position mouseClick;
button exit_button;

unsigned char activeCS;
color_scheme allCS[MAX_CS];

int main()
{
  int i;
  init_graphics();
  /*moveto(0,0);
  lineto(50,50);
  lineto(50,100);
  lineto(150,120);*/
  setcolor(2);
  setpalette(WHITE,GREEN);
  setbkcolor(WHITE);
  //setcolor( COLOR(255,0,0) );
  //setcolor(2);
  for (i=0;i<=100;i++)
     {
      line(0,relative_to_absolute_value(i,AFTER_HEIGHT),MAXX, relative_to_absolute_value(i,AFTER_HEIGHT));
      line(relative_to_absolute_value(i,AFTER_WIDTH),0,relative_to_absolute_value(i,AFTER_WIDTH), MAXY);
     }

  buttonR.rAnchorPoint.rX=40;
  buttonR.rAnchorPoint.rY=40;
  buttonR.rHeight=10;
  buttonR.rWidth=20;
  exit_button=create_button(buttonR,"EXIT",EXIT_GAME);
  for (i=0;i<=100;i++)
     {
      line(0,relative_to_absolute_value(i,AFTER_HEIGHT),MAXX, relative_to_absolute_value(i,AFTER_HEIGHT));
      line(relative_to_absolute_value(i,AFTER_WIDTH),0,relative_to_absolute_value(i,AFTER_WIDTH), MAXY);
     }
   while (1)
     {
      mouseClick=get_mouseClick_postion(LEFT_CLICK);
      if (is_button_pressed(exit_button,mouseClick))
          break;
     }

  closegraph();        //close graphics window*/
  return 0;
}

void init_graphics()
{
get_maximum();
init_color_schemes();
int gdriver = EGA, gmode = EGAHI, errorcode;
initgraph(&gdriver, &gmode, "");
initwindow(MAXX,MAXY);
}

void get_maximum()
{
ifstream fin("resolution.txt");
fin>>MAXX>>MAXY;
fin.close();
}

void init_color_schemes()
{
int index;
ifstream fin("color_scheme.txt");
fin>>index;
upload_all_color_schemes();
set_active_color_scheme(index);
}
