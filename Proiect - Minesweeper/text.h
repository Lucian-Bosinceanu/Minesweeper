#include "relative_coordinates.h"
#include "color_scheme.h"
#include <graphics.h>

#define MAX_TEXT 100

#define TOP 1
#define BOTTOM 2
#define LEFT 3
#define RIGHT 4
#define CENTER 5


struct text{

    relative_rectangle rTextBox;
    char charString[MAX_TEXT];
    char horizontalAlign;
    char verticalAlign;
    char textSize;
    absolute_point drawingPoint;
};

text create_text(relative_rectangle textBox, char sir[],char hAlign, char vAlign);
void draw_text(text T);
