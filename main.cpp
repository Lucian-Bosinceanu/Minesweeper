#include <fstream>
#define MAX_CS 5
#include "gamescreen.h"
#include <iostream>

using namespace std;

short int MAXX, MAXY;

color_scheme activeCS;

menu main_menu, options_menu, pick_difficulty_menu, change_color_scheme_menu, change_resolution_menu, play_menu;

button play_button, options_button, exit_button;
button difficulty_easy_button, difficulty_medium_button, difficulty_hard_button, difficulty_insane_button;

button res_1920x1080_button, res_1366x768_button, res_1280x800_button, res_1440x900_button;
button res_1280x1024_button, res_1600x900_button, res_1024x768_button, res_800x600_button;

button change_resolution_button, change_color_scheme_button;
button pick_color_scheme1_button, pick_color_scheme2_button, pick_color_scheme3_button;

button back_button, reset_button;

void init_buttons();
void load_menus();

void get_maximum();
void init_graphics();
void clear_screen();

void load_main_menu();
void load_options_menu();
void load_pick_difficulty_menu();
void load_change_color_scheme_menu();
void load_change_resolution_menu();
void load_play_menu(char difficulty);

int main()
{
  init_graphics();
  load_main_menu();
  closegraph();
  return 0;
}

void load_main_menu()
{
char click;
click_position mouseClick;
clear_screen();
draw_menu(main_menu);
while (1)
    {
     click=get_mouseClick_type();
     mouseClick=get_mouseClick_postion(click);

     if ( is_button_pressed(play_button,mouseClick) )
         {
          load_pick_difficulty_menu();
          clear_screen();
          draw_menu(main_menu);
         }

     if ( is_button_pressed(options_button,mouseClick) )
        {
         load_options_menu();
         clear_screen();
         draw_menu(main_menu);
        }

     if ( is_button_pressed(exit_button,mouseClick) )
        return;
    }
}

void load_options_menu()
{
char click;
click_position mouseClick;
clear_screen();
draw_menu(options_menu);
while (1)
    {
     click=get_mouseClick_type();
     mouseClick=get_mouseClick_postion(click);

     if ( is_button_pressed(change_color_scheme_button,mouseClick) )
         {
          load_change_color_scheme_menu();
          clear_screen();
          draw_menu(options_menu);
         }

     if ( is_button_pressed(change_resolution_button,mouseClick) )
        {
         load_change_resolution_menu();
         clear_screen();
         draw_menu(options_menu);
        }

     if ( is_button_pressed(back_button,mouseClick) )
        return;
    }
}

void load_pick_difficulty_menu()
{
char click;
click_position mouseClick;
clear_screen();
draw_menu(pick_difficulty_menu);
while (1)
    {
     click=get_mouseClick_type();
     mouseClick=get_mouseClick_postion(click);

     if ( is_button_pressed(difficulty_easy_button,mouseClick) )
        {
         load_play_menu(EASY);
         clear_screen();
         draw_menu(pick_difficulty_menu);
        }

     if ( is_button_pressed(difficulty_medium_button,mouseClick) )
        {
         load_play_menu(MEDIUM);
         clear_screen();
         draw_menu(pick_difficulty_menu);
        }

     if ( is_button_pressed(difficulty_hard_button,mouseClick) )
        {
         load_play_menu(HARD);
         clear_screen();
         draw_menu(pick_difficulty_menu);
        }

     if ( is_button_pressed(difficulty_insane_button,mouseClick) )
        {
         load_play_menu(INSANE);
         clear_screen();
         draw_menu(pick_difficulty_menu);
        }

     if (is_button_pressed(back_button,mouseClick))
         return;
    }
}

void load_change_color_scheme_menu()
{
char click;
click_position mouseClick;
clear_screen();
draw_menu(change_color_scheme_menu);
}

void load_change_resolution_menu()
{
char click;
click_position mouseClick;
clear_screen();
draw_menu(change_resolution_menu);
}

void load_play_menu(char difficulty)
{
char click;
field_position clickedFieldPosition;
play_screen playScreen;
click_position mouseClick;
playScreen.gameState=init_game_state(difficulty);
playScreen.playMenu=play_menu;
clear_screen();
draw_play_screen(playScreen);
while (1)
    {

    while (playScreen.gameState.state==PENDING)
           {
            click=get_mouseClick_type();
            mouseClick=get_mouseClick_postion(click);
            if ( is_mine_field_click(playScreen.gameState.gameField,mouseClick) )
                {
                 clickedFieldPosition=get_field_position(playScreen.gameState.gameField,mouseClick);
                 playScreen.gameState.state=solve_click_effect(playScreen.gameState.gameField, clickedFieldPosition, click);
                 clear_screen();
                 draw_play_screen(playScreen);
                }
            if (playScreen.gameState.gameField.nrOfMines==playScreen.gameState.gameField.nrOfFlags)
                {
                if ( is_solved_correctly(playScreen.gameState.gameField) )
                    playScreen.gameState.state=SOLVED;
                }

            if ( is_button_pressed(reset_button,mouseClick) )
                {
                 playScreen.gameState=init_game_state(difficulty);
                 playScreen.playMenu=play_menu;
                 clear_screen();
                 draw_play_screen(playScreen);
                }

            if ( is_button_pressed(back_button,mouseClick) )
                return;

           }

    click=get_mouseClick_type();
    mouseClick=get_mouseClick_postion(click);

    if (playScreen.gameState.state==SOLVED)
        {
         //ceva
         settextstyle(10,HORIZ_DIR,2);
         setbkcolor(return_rgb_color_code(activeCS.mainColor));
         set_active_color(activeCS.backgroundColor);
         moveto(600,50);
         outtext("SOLVED!");
        }
        else
        if (playScreen.gameState.state=FAILED)
            {
            //altceva
            settextstyle(10,HORIZ_DIR,2);
            setbkcolor(return_rgb_color_code(activeCS.mainColor));
            set_active_color(activeCS.backgroundColor);
            moveto(600,50);
            outtext("FAILED!");
            }
    if ( is_button_pressed(reset_button,mouseClick) )
                {
                 playScreen.gameState=init_game_state(difficulty);
                 playScreen.playMenu=play_menu;
                 clear_screen();
                 draw_play_screen(playScreen);
                }

            if ( is_button_pressed(back_button,mouseClick) )
                return;
    }
}

void init_graphics()
{
get_maximum();
int gdriver = EGA, gmode = EGAHI, errorcode;
initgraph(&gdriver, &gmode, "");
initwindow(MAXX,MAXY);
activeCS=load_current_color_scheme();
init_buttons();
load_menus();
clear_screen();
}

void get_maximum()
{
ifstream fin("resolution.txt");
fin>>MAXX>>MAXY;
fin.close();
}

void clear_screen()
{
cleardevice();
set_active_color(activeCS.backgroundColor);
setfillstyle(SOLID_FILL,return_rgb_color_code(activeCS.backgroundColor));
bar(0,0,MAXX,MAXY);
}

void load_menus()
{
insert_button_menu(main_menu, play_button);
insert_button_menu(main_menu, options_button);
insert_button_menu(main_menu, exit_button);

insert_button_menu(options_menu, back_button);
insert_button_menu(options_menu, change_resolution_button);
insert_button_menu(options_menu, change_color_scheme_button);

insert_button_menu(change_resolution_menu,back_button);
insert_button_menu(change_resolution_menu,res_1920x1080_button);
insert_button_menu(change_resolution_menu,res_1366x768_button);
insert_button_menu(change_resolution_menu,res_1280x800_button);
insert_button_menu(change_resolution_menu,res_1440x900_button);
insert_button_menu(change_resolution_menu,res_1280x1024_button);
insert_button_menu(change_resolution_menu,res_1600x900_button);
insert_button_menu(change_resolution_menu,res_1024x768_button);
insert_button_menu(change_resolution_menu,res_800x600_button);

insert_button_menu(change_color_scheme_menu,back_button);
insert_button_menu(change_color_scheme_menu,pick_color_scheme1_button);
insert_button_menu(change_color_scheme_menu,pick_color_scheme2_button);
insert_button_menu(change_color_scheme_menu,pick_color_scheme3_button);

insert_button_menu(pick_difficulty_menu,back_button);
insert_button_menu(pick_difficulty_menu,difficulty_easy_button);
insert_button_menu(pick_difficulty_menu,difficulty_medium_button);
insert_button_menu(pick_difficulty_menu,difficulty_hard_button);
insert_button_menu(pick_difficulty_menu,difficulty_insane_button);

insert_button_menu(play_menu,back_button);
insert_button_menu(play_menu,reset_button);
}

void init_buttons()
{
relative_rectangle buttonR;

buttonR.rAnchorPoint.rX=40; buttonR.rAnchorPoint.rY=55;
buttonR.rHeight=10; buttonR.rWidth=20;
play_button=create_button(buttonR,"PLAY",PLAY_GAME);

buttonR.rAnchorPoint.rX=40; buttonR.rAnchorPoint.rY=70;
buttonR.rHeight=10; buttonR.rWidth=20;
options_button=create_button(buttonR,"OPTIONS",OPTIONS);

buttonR.rAnchorPoint.rX=40; buttonR.rAnchorPoint.rY=85;
buttonR.rHeight=10; buttonR.rWidth=20;
exit_button=create_button(buttonR,"EXIT",EXIT_GAME);

buttonR.rAnchorPoint.rX=30; buttonR.rAnchorPoint.rY=15;
buttonR.rHeight=10; buttonR.rWidth=40;
difficulty_easy_button=create_button(buttonR,"EASY (9x9, 10 MINES)",PICK_EASY_DIF);

buttonR.rAnchorPoint.rX=30; buttonR.rAnchorPoint.rY=35;
buttonR.rHeight=10; buttonR.rWidth=40;
difficulty_medium_button=create_button(buttonR,"MEDIUM (16X16, 40 MINES)",PICK_MEDIUM_DIF);

buttonR.rAnchorPoint.rX=30; buttonR.rAnchorPoint.rY=55;
buttonR.rHeight=10; buttonR.rWidth=40;
difficulty_hard_button=create_button(buttonR,"HARD (20X20, 60 MINES)",PICK_HARD_DIF);

buttonR.rAnchorPoint.rX=30; buttonR.rAnchorPoint.rY=75;
buttonR.rHeight=10; buttonR.rWidth=40;
difficulty_insane_button=create_button(buttonR,"INSANE (30X30, 100 MINES)",PICK_INSANE_DIF);

buttonR.rAnchorPoint.rX=40; buttonR.rAnchorPoint.rY=40;
buttonR.rHeight=10; buttonR.rWidth=20;
res_1920x1080_button=create_button(buttonR,"1920x1080",RES_1920X1080);

buttonR.rAnchorPoint.rX=40; buttonR.rAnchorPoint.rY=40;
buttonR.rHeight=10; buttonR.rWidth=20;
res_1366x768_button=create_button(buttonR,"1366x768",RES_1366X768);

buttonR.rAnchorPoint.rX=40; buttonR.rAnchorPoint.rY=40;
buttonR.rHeight=10; buttonR.rWidth=20;
res_1280x800_button=create_button(buttonR,"1280x800",RES_1280X800);

buttonR.rAnchorPoint.rX=40; buttonR.rAnchorPoint.rY=40;
buttonR.rHeight=10; buttonR.rWidth=20;
res_1440x900_button=create_button(buttonR,"1440x900",RES_1440X900);

buttonR.rAnchorPoint.rX=40; buttonR.rAnchorPoint.rY=40;
buttonR.rHeight=10; buttonR.rWidth=20;
res_1280x1024_button=create_button(buttonR,"1280x1024",RES_1280X1024);

buttonR.rAnchorPoint.rX=40; buttonR.rAnchorPoint.rY=40;
buttonR.rHeight=10; buttonR.rWidth=20;
res_1600x900_button=create_button(buttonR,"1600x900",RES_1600X900);

buttonR.rAnchorPoint.rX=40; buttonR.rAnchorPoint.rY=40;
buttonR.rHeight=10; buttonR.rWidth=20;
res_1024x768_button=create_button(buttonR,"1024x768",RES_1024X768);

buttonR.rAnchorPoint.rX=40; buttonR.rAnchorPoint.rY=40;
buttonR.rHeight=10; buttonR.rWidth=20;
res_800x600_button=create_button(buttonR,"800x600",RES_800X600);

buttonR.rAnchorPoint.rX=10; buttonR.rAnchorPoint.rY=10;
buttonR.rHeight=10; buttonR.rWidth=10;
back_button=create_button(buttonR,"BACK",BACK_BUTTON);

buttonR.rAnchorPoint.rX=40; buttonR.rAnchorPoint.rY=40;
buttonR.rHeight=10; buttonR.rWidth=10;
reset_button=create_button(buttonR,"RESET",RESET_BUTTON);

buttonR.rAnchorPoint.rX=40; buttonR.rAnchorPoint.rY=40;
buttonR.rHeight=10; buttonR.rWidth=20;
pick_color_scheme1_button=create_button(buttonR,"COLOR SCHEME 1",CHANGE_COLOR_SCHEME_1);

buttonR.rAnchorPoint.rX=40; buttonR.rAnchorPoint.rY=40;
buttonR.rHeight=10; buttonR.rWidth=20;
pick_color_scheme2_button=create_button(buttonR,"COLOR SCHEME 2",CHANGE_COLOR_SCHEME_2);

buttonR.rAnchorPoint.rX=40; buttonR.rAnchorPoint.rY=40;
buttonR.rHeight=10; buttonR.rWidth=20;
pick_color_scheme3_button=create_button(buttonR,"COLOR SCHEME 3",CHANGE_COLOR_SCHEME_3);

buttonR.rAnchorPoint.rX=30; buttonR.rAnchorPoint.rY=35;
buttonR.rHeight=10; buttonR.rWidth=40;
change_color_scheme_button=create_button(buttonR,"CHANGE COLOR SCHEME",CHANGE_COLOR_SCHEME_BUTTON);

buttonR.rAnchorPoint.rX=30; buttonR.rAnchorPoint.rY=55;
buttonR.rHeight=10; buttonR.rWidth=40;
change_resolution_button=create_button(buttonR,"CHANGE RESOLUTION",CHANGE_RES_BUTTON);

}
