#include <fstream>
#define MAX_CS 5
#include "gamescreen.h"
#include <iostream>

using namespace std;

short int MAXX, MAXY;

color_scheme activeCS;

menu main_menu, options_menu, pick_difficulty_menu, change_color_scheme_menu, change_resolution_menu, play_menu, custom_game_menu;

button play_button, options_button, exit_button;
button difficulty_easy_button, difficulty_medium_button, difficulty_hard_button, difficulty_CUSTOM_button;
button res_1920x1080_button, res_1366x768_button, res_1280x800_button, res_1440x900_button;
button res_1280x1024_button, res_1600x900_button, res_1024x768_button, res_800x600_button;
button change_resolution_button, change_color_scheme_button;
button pick_color_scheme1_button, pick_color_scheme2_button, pick_color_scheme3_button;
button back_button, reset_button, apply_button;
button more_lines_button, less_lines_button, more_columns_button, less_columns_button, more_mines_button, less_mines_button;

text resolution_message_text, restart_required_text;
text failed_game_text, succeeded_game_text;

void init_buttons();
void load_menus();
void free_memory_menus();
void load_text();

void get_maximum();
void init_graphics();
void clear_screen();

void load_main_menu();
void load_options_menu();
void load_pick_difficulty_menu();
void load_change_color_scheme_menu();
void load_change_resolution_menu();
void load_play_menu(char difficulty);
void load_custom_game_menu();

int main()
{
  init_graphics();
  load_main_menu();
  free_memory_menus();
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

     if ( is_button_pressed(difficulty_CUSTOM_button,mouseClick) )
        {
         //load_play_menu(CUSTOM);
         load_custom_game_menu();
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
while (1)
    {
     click=get_mouseClick_type();
     mouseClick=get_mouseClick_postion(click);

     if (is_button_pressed(back_button,mouseClick))
         return;

    if (is_button_pressed(pick_color_scheme1_button, mouseClick))
        {
        change_global_color_scheme(1);
        clear_screen();
        draw_menu(change_color_scheme_menu);
        }

    if (is_button_pressed(pick_color_scheme2_button, mouseClick))
        {
        change_global_color_scheme(2);
        clear_screen();
        draw_menu(change_color_scheme_menu);
        }

    if (is_button_pressed(pick_color_scheme3_button, mouseClick))
        {
        change_global_color_scheme(3);
        clear_screen();
        draw_menu(change_color_scheme_menu);
        }
    }

}

void load_change_resolution_menu()
{
char click;
char sir[MAX_TEXT];
char resolution_text[30];
short int x=0,y=0;
bool changedRes=false;
click_position mouseClick;
clear_screen();
draw_menu(change_resolution_menu);
strcpy(sir,resolution_message_text.charString);
while (1)
    {
     click=get_mouseClick_type();
     mouseClick=get_mouseClick_postion(click);

     if (is_button_pressed(back_button, mouseClick))
         return;

     if (is_button_pressed(res_1920x1080_button, mouseClick))
        {
         x=1920; y=1080; changedRes=true;
        }

    if (is_button_pressed(res_1366x768_button, mouseClick))
        {
         x=1366; y=768; changedRes=true;
        }

    if (is_button_pressed(res_1280x800_button, mouseClick))
        {
         x=1280; y=800; changedRes=true;
        }

    if (is_button_pressed(res_1440x900_button, mouseClick))
        {
         x=1440; y=900; changedRes=true;
        }

    if (is_button_pressed(res_1280x1024_button, mouseClick))
        {
         x=1280; y=1024; changedRes=true;
        }

    if (is_button_pressed(res_1600x900_button, mouseClick))
        {
         x=1600; y=900; changedRes=true;
        }

    if (is_button_pressed(res_1024x768_button, mouseClick))
        {
         x=1024; y=768; changedRes=true;
        }

    if (is_button_pressed(res_800x600_button, mouseClick))
        {
         x=800; y=600; changedRes=true;
        }

    if (changedRes)
        {
        //resolution_to_text(x,y,resolution_text);
        //strcpy(resolution_message_text.charString, strcat(sir,resolution_text));
        //resolution_message_text.charString[ strlen(resolution_message_text.charString) ]=0;
        draw_text(resolution_message_text);
        draw_text(restart_required_text);
        }

    if (is_button_pressed(apply_button, mouseClick) && changedRes)
        {
        set_new_screen_resolution(x,y);
        free_memory_menus();
        exit(0);
        }
    }
insert_button_menu(change_resolution_menu,apply_button);

}

void load_custom_game_menu()
{
char click;
click_position mouseClick;
clear_screen();
draw_menu(custom_game_menu);
while (1)
    {
     click=get_mouseClick_type();
     mouseClick=get_mouseClick_postion(click);

     if (is_button_pressed(back_button, mouseClick))
         return;
    }
}

void load_play_menu(char difficulty)
{
char click;
char click_effect;
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
                 click_effect=field_click_effect(playScreen.gameState.gameField, clickedFieldPosition,click);
                 if (click_effect!=NOTHING)
                     {
                     playScreen.gameState.state=solve_click_effect(playScreen.gameState.gameField, clickedFieldPosition, click_effect);
                     //clear_screen();
                     draw_field_graphicalChanges(playScreen.gameState.gameField);
                     //draw_play_screen(playScreen);
                     }
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
         reveal_all(playScreen.gameState.gameField);
         draw_field_graphicalChanges(playScreen.gameState.gameField);
         settextstyle(10,HORIZ_DIR,2);
         setbkcolor(return_rgb_color_code(activeCS.mainColor));
         set_active_color(activeCS.backgroundColor);
         moveto(600,50);
         outtext("SOLVED!");
        }
        else
        if (playScreen.gameState.state==FAILED)
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
if (MAXX<800 && MAXY<600)
    {
    free_memory_menus();
    exit(0);
    }
int gdriver = EGA, gmode = EGAHI, errorcode;
initgraph(&gdriver, &gmode, "");
initwindow(MAXX,MAXY);
activeCS=load_current_color_scheme();
init_buttons();
load_menus();
load_text();
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
insert_button_menu(change_resolution_menu,apply_button);
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
insert_button_menu(pick_difficulty_menu,difficulty_CUSTOM_button);

insert_button_menu(play_menu,back_button);
insert_button_menu(play_menu,reset_button);

insert_button_menu(custom_game_menu,back_button);
insert_button_menu(custom_game_menu,more_lines_button);
insert_button_menu(custom_game_menu,less_lines_button);
insert_button_menu(custom_game_menu,more_columns_button);
insert_button_menu(custom_game_menu,less_columns_button);
insert_button_menu(custom_game_menu,more_mines_button);
insert_button_menu(custom_game_menu,less_mines_button);
}

void free_memory_menus()
{
delete_buttons_menu(main_menu);
delete_buttons_menu(options_menu);
delete_buttons_menu(change_color_scheme_menu);
delete_buttons_menu(change_color_scheme_menu);
delete_buttons_menu(pick_difficulty_menu);
delete_buttons_menu(play_menu);
delete_buttons_menu(custom_game_menu);
}

void init_buttons()
{
relative_rectangle buttonR;

buttonR.rAnchorPoint.rX=40; buttonR.rAnchorPoint.rY=55;
buttonR.rHeight=10; buttonR.rWidth=20;
play_button=create_button(buttonR,"PLAY");

buttonR.rAnchorPoint.rX=40; buttonR.rAnchorPoint.rY=70;
buttonR.rHeight=10; buttonR.rWidth=20;
options_button=create_button(buttonR,"OPTIONS");

buttonR.rAnchorPoint.rX=40; buttonR.rAnchorPoint.rY=85;
buttonR.rHeight=10; buttonR.rWidth=20;
exit_button=create_button(buttonR,"EXIT");

buttonR.rAnchorPoint.rX=30; buttonR.rAnchorPoint.rY=15;
buttonR.rHeight=10; buttonR.rWidth=40;
difficulty_easy_button=create_button(buttonR,"EASY (9x9, 10 MINES)");

buttonR.rAnchorPoint.rX=30; buttonR.rAnchorPoint.rY=35;
buttonR.rHeight=10; buttonR.rWidth=40;
difficulty_medium_button=create_button(buttonR,"MEDIUM (16X16, 40 MINES)");

buttonR.rAnchorPoint.rX=30; buttonR.rAnchorPoint.rY=55;
buttonR.rHeight=10; buttonR.rWidth=40;
difficulty_hard_button=create_button(buttonR,"HARD (20X20, 60 MINES)");

buttonR.rAnchorPoint.rX=30; buttonR.rAnchorPoint.rY=75;
buttonR.rHeight=10; buttonR.rWidth=40;
difficulty_CUSTOM_button=create_button(buttonR,"CUSTOM");

buttonR.rAnchorPoint.rX=66; buttonR.rAnchorPoint.rY=61;
buttonR.rHeight=10; buttonR.rWidth=20;
res_1920x1080_button=create_button(buttonR,"1920x1080");

buttonR.rAnchorPoint.rX=66; buttonR.rAnchorPoint.rY=10;
buttonR.rHeight=10; buttonR.rWidth=20;
res_1366x768_button=create_button(buttonR,"1366x768");

buttonR.rAnchorPoint.rX=33; buttonR.rAnchorPoint.rY=44;
buttonR.rHeight=10; buttonR.rWidth=20;
res_1280x800_button=create_button(buttonR,"1280x800");

buttonR.rAnchorPoint.rX=66; buttonR.rAnchorPoint.rY=27;
buttonR.rHeight=10; buttonR.rWidth=20;
res_1440x900_button=create_button(buttonR,"1440x900");

buttonR.rAnchorPoint.rX=33; buttonR.rAnchorPoint.rY=61;
buttonR.rHeight=10; buttonR.rWidth=20;
res_1280x1024_button=create_button(buttonR,"1280x1024");

buttonR.rAnchorPoint.rX=66; buttonR.rAnchorPoint.rY=44;
buttonR.rHeight=10; buttonR.rWidth=20;
res_1600x900_button=create_button(buttonR,"1600x900");

buttonR.rAnchorPoint.rX=33; buttonR.rAnchorPoint.rY=27;
buttonR.rHeight=10; buttonR.rWidth=20;
res_1024x768_button=create_button(buttonR,"1024x768");

buttonR.rAnchorPoint.rX=33; buttonR.rAnchorPoint.rY=10;
buttonR.rHeight=10; buttonR.rWidth=20;
res_800x600_button=create_button(buttonR,"800x600");

buttonR.rAnchorPoint.rX=10; buttonR.rAnchorPoint.rY=10;
buttonR.rHeight=10; buttonR.rWidth=10;
back_button=create_button(buttonR,"BACK");

buttonR.rAnchorPoint.rX=10; buttonR.rAnchorPoint.rY=40;
buttonR.rHeight=10; buttonR.rWidth=10;
reset_button=create_button(buttonR,"RESET");

buttonR.rAnchorPoint.rX=10; buttonR.rAnchorPoint.rY=25;
buttonR.rHeight=10; buttonR.rWidth=10;
apply_button=create_button(buttonR,"APPLY");

buttonR.rAnchorPoint.rX=35; buttonR.rAnchorPoint.rY=35;
buttonR.rHeight=10; buttonR.rWidth=30;
pick_color_scheme1_button=create_button(buttonR,"COLOR SCHEME 1");

buttonR.rAnchorPoint.rX=35; buttonR.rAnchorPoint.rY=55;
buttonR.rHeight=10; buttonR.rWidth=30;
pick_color_scheme2_button=create_button(buttonR,"COLOR SCHEME 2");

buttonR.rAnchorPoint.rX=35; buttonR.rAnchorPoint.rY=75;
buttonR.rHeight=10; buttonR.rWidth=30;
pick_color_scheme3_button=create_button(buttonR,"COLOR SCHEME 3");

buttonR.rAnchorPoint.rX=30; buttonR.rAnchorPoint.rY=35;
buttonR.rHeight=10; buttonR.rWidth=40;
change_color_scheme_button=create_button(buttonR,"CHANGE COLOR SCHEME");

buttonR.rAnchorPoint.rX=30; buttonR.rAnchorPoint.rY=55;
buttonR.rHeight=10; buttonR.rWidth=40;
change_resolution_button=create_button(buttonR,"CHANGE RESOLUTION");

//
buttonR.rAnchorPoint.rX=33; buttonR.rAnchorPoint.rY=10;
buttonR.rHeight=10; buttonR.rWidth=20;
more_lines_button=create_button(buttonR," (+) LINES ");

buttonR.rAnchorPoint.rX=66; buttonR.rAnchorPoint.rY=10;
buttonR.rHeight=10; buttonR.rWidth=20;
less_lines_button=create_button(buttonR," (-) LINES ");

buttonR.rAnchorPoint.rX=33; buttonR.rAnchorPoint.rY=27;
buttonR.rHeight=10; buttonR.rWidth=20;
more_columns_button=create_button(buttonR,"(+) COLUMNS");

buttonR.rAnchorPoint.rX=66; buttonR.rAnchorPoint.rY=27;
buttonR.rHeight=10; buttonR.rWidth=20;
less_columns_button=create_button(buttonR,"(-) COLUMNS");

buttonR.rAnchorPoint.rX=33; buttonR.rAnchorPoint.rY=44;
buttonR.rHeight=10; buttonR.rWidth=20;
more_mines_button=create_button(buttonR," (+) MINES ");

buttonR.rAnchorPoint.rX=66; buttonR.rAnchorPoint.rY=44;
buttonR.rHeight=10; buttonR.rWidth=20;
less_mines_button=create_button(buttonR," (-) MINES ");
}

void load_text()
{
relative_rectangle rTextBox;

rTextBox.rAnchorPoint.rX=33; rTextBox.rAnchorPoint.rY=74;
rTextBox.rHeight=10; rTextBox.rWidth=67;
resolution_message_text=create_text(rTextBox,"Resolution has changed.",LEFT,CENTER);

rTextBox.rAnchorPoint.rX=33; rTextBox.rAnchorPoint.rY=80;
rTextBox.rHeight=10; rTextBox.rWidth=67;
restart_required_text=create_text(rTextBox,"Restart is required. Click APPLY to exit the game.",LEFT,CENTER);

rTextBox.rAnchorPoint.rX=0; rTextBox.rAnchorPoint.rY=10;
rTextBox.rHeight=10; rTextBox.rWidth=80;
succeeded_game_text=create_text(rTextBox,"Success! You won the game! Click RESET to start a new game.",CENTER,CENTER);

rTextBox.rAnchorPoint.rX=0; rTextBox.rAnchorPoint.rY=10;
rTextBox.rHeight=10; rTextBox.rWidth=0;
succeeded_game_text=create_text(rTextBox,"Failed! Click RESET to retry.",CENTER,CENTER);
}
