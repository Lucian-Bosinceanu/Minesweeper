#include "graphics.h"
#include "relative_coordinates.h"

#define LEFT_CLICK 1
#define RIGHT_CLICK 2
#define BOTH_CLICK 3

absolute_point mouseClickPosition;

char get_mouseClick_type();
absolute_point get_mouseClick_postion(char click_type);
