#include "mouse_click.h"

char get_mouseClick_type()
{
char result=NO_CLICK;
if (ismouseclick(WM_LBUTTONDOWN) && ismouseclick(WM_RBUTTONDOWN) )
        result=BOTH_CLICK;
if ( ismouseclick(WM_LBUTTONDOWN) )
    result=LEFT_CLICK;
if ( ismouseclick(WM_RBUTTONDOWN) )
    result=RIGHT_CLICK;
//clearmouseclick(WM_LBUTTONDOWN);
//clearmouseclick(WM_RBUTTONDOWN);
return result;
}

click_position get_mouseClick_postion(char click_type)
{
click_position mouseClick;
int lx, ly;
int rx, ry;
mouseClick.X=0;
mouseClick.Y=0;
if (click_type==NO_CLICK)
    return mouseClick;
if (click_type==LEFT_CLICK)
    {
    getmouseclick(WM_LBUTTONDOWN,lx,ly);
    mouseClick.X=lx;
    mouseClick.Y=ly;
    }
if (click_type==RIGHT_CLICK)
    {
    getmouseclick(WM_RBUTTONDOWN,rx,ry);
    mouseClick.X=rx;
    mouseClick.Y=ry;
    }
if (click_type==BOTH_CLICK)
    {
    getmouseclick(WM_LBUTTONDOWN,lx,ly);
    getmouseclick(WM_RBUTTONDOWN,rx,ry);
    if ( lx=rx && ly==ry )
        {
        mouseClick.X=rx;
        mouseClick.Y=ry;
        }
    }

return mouseClick;
}
