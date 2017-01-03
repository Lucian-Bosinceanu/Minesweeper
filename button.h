#include "relative_coordinates.h"
#include "mouse_click.h"
#include "color_scheme.h"

#define MAX_SIR 30

#define EXIT_GAME 0
#define START_CLASSIC 1
#define OPTIONS 2


struct button{

    relative_rectangle buttonBox;
    char text[MAX_SIR];
    char buttonFunction;
};


button create_button(relative_rectangle rButtonBox, char content[],char function_code);
void press_button(button B);

bool is_button_pressed(button B, click_position mouseClick);

void draw_button(button B);
