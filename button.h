#include "relative_coordinates.h"
#include "mouse_click.h"
#include "color_scheme.h"

#define MAX_SIR 30

#define EXIT_GAME 0
#define PLAY_GAME 1
#define OPTIONS 2

#define PICK_EASY_DIF 3
#define PICK_MEDIUM_DIF 4
#define PICK_HARD_DIF 5
#define PICK_INSANE_DIF 6

#define RES_1920X1080 7
#define RES_1366X768 8
#define RES_1280X800 9
#define RES_1440X900 10
#define RES_1280X1024 11
#define RES_1600X900 12
#define RES_1024X768 13
#define RES_800X600 14

#define BACK_BUTTON -1
#define RESET_BUTTON -2
#define CHANGE_COLOR_SCHEME_1 21
#define CHANGE_COLOR_SCHEME_2 22
#define CHANGE_COLOR_SCHEME_3 23

#define CHANGE_COLOR_SCHEME_BUTTON 30
#define CHANGE_RES_BUTTON 31

struct button{

    relative_rectangle buttonBox;
    char text[MAX_SIR];
};


button create_button(relative_rectangle rButtonBox, char content[]);

bool is_button_pressed(button B, click_position mouseClick);

void draw_button(button B);
