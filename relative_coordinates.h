//#include <graphics.h>
#include <fstream>
#define AFTER_WIDTH 1
#define AFTER_HEIGHT 2



struct relative_point{
    char rX, rY;
};

struct absolute_point{
    short int X,Y;
};

struct relative_rectangle{
    relative_point rAnchorPoint;
    char rWidth, rHeight;
};

struct absolute_rectangle{
    absolute_point anchorPoint;
    short int width, height;
};

short int relative_to_absolute_value(char percent, char dimension_code);
char absolute_to_relative_value(short int position, char dimension_code);

absolute_point relative_to_absolute_point(relative_point rP);
relative_point absolute_to_relative_point(absolute_point P);

absolute_rectangle relative_to_absolute_rectangle(relative_rectangle rRectangle);
relative_rectangle absolute_to_relative_rectangle(absolute_rectangle rectangle);

void set_new_screen_resolution(short int width, short int height);
void resolution_to_text(short int width, short int height, char sir[]);
