//#include "relative_coordinates.h"
#include <graphics.h>
#define LEFT_CLICK 1
#define RIGHT_CLICK 2
#define BOTH_CLICK 3

struct click_position{
    short int X,Y;
};


char get_mouseClick_type();
click_position get_mouseClick_postion(char click_type);
