#include "relative_coordinates.h"

#define MAX_SIR 30

#define EXIT_GAME 0
#define START_CLASSIC 1
#define OPTIONS 2


struct button{

    relative_rectangle buttonBox;
    char text[MAX_SIR];
    char buttonFunction;
};


button create_button(relative_point rAnchorPoint,relative_rectangle rButtonBox, char content[],char function_code);
bool isButtonPressed(button B, absolute_point mouseClick);
void pressButton(button B);
