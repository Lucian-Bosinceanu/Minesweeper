//#include "relative_coordinates.h"
#include <graphics.h>
#define NO_CLICK 0
#define LEFT_CLICK 1
#define RIGHT_CLICK 2
#define BOTH_CLICK 3
#define MIDDLE_CLICK 4

struct click_position{
    short int X,Y;
};


char get_mouseClick_type();
click_position get_mouseClick_postion(char click_type);
