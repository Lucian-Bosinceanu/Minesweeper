#include <fstream>
#include <ctime>
#define MAX_CS 5
#include "gamescreen.h"
#include <iostream>

#define DELTA_LINES 5
#define DELTA_COLUMNS 5
#define DELTA_MINES 5

using namespace std;

short int MAXX, MAXY;

highscore highScore;

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

text resolution_message_text, restart_required_text, click_apply_text;
text failed_game_text, succeeded_game_text;
text current_lines_text, current_columns_text, current_mines_text;
text mines_minus_flags_text, timer_text;

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
void load_play_menu(char difficultyGS, short int nrLines, short int nrColumns, short int nrMines);
void load_custom_game_menu();

void screen_text_update(custom_game_validity validity, short int nrLines, short int nrColumns, short int nrMines);

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
absolute_point siglaAnchorPoint;
short int height,width;
click_position mouseClick;
clear_screen();
draw_menu(main_menu);
height=relative_to_absolute_value(40,AFTER_HEIGHT);
width=2*height;
siglaAnchorPoint.Y=relative_to_absolute_value(10,AFTER_HEIGHT);
siglaAnchorPoint.X=(MAXX-width)/2;
readimagefile("./images/sigla.jpg",siglaAnchorPoint.X,siglaAnchorPoint.Y,siglaAnchorPoint.X+width,siglaAnchorPoint.Y+height);
while (1)
    {
     click=get_mouseClick_type();
     mouseClick=get_mouseClick_postion(click);

     if ( is_button_pressed(play_button,mouseClick) )
         {
          load_pick_difficulty_menu();
          clear_screen();
          draw_menu(main_menu);
          readimagefile("./images/sigla.jpg",siglaAnchorPoint.X,siglaAnchorPoint.Y,siglaAnchorPoint.X+width,siglaAnchorPoint.Y+height);
         }

     if ( is_button_pressed(options_button,mouseClick) )
        {
         load_options_menu();
         clear_screen();
         draw_menu(main_menu);
         readimagefile("./images/sigla.jpg",siglaAnchorPoint.X,siglaAnchorPoint.Y,siglaAnchorPoint.X+width,siglaAnchorPoint.Y+height);
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
         load_play_menu(EASY,EASY_LINES,EASY_COLUMNS,EASY_MINES);
         clear_screen();
         draw_menu(pick_difficulty_menu);
        }

     if ( is_button_pressed(difficulty_medium_button,mouseClick) )
        {
         load_play_menu(MEDIUM,MEDIUM_LINES,MEDIUM_COLUMNS,MEDIUM_MINES);
         clear_screen();
         draw_menu(pick_difficulty_menu);
        }

     if ( is_button_pressed(difficulty_hard_button,mouseClick) )
        {
         load_play_menu(HARD,HARD_LINES,HARD_COLUMNS,HARD_MINES);
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
bool changedRes=false, visualUpdate=false;
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
         x=1920; y=1080; changedRes=true; visualUpdate=false;
        }

    if (is_button_pressed(res_1366x768_button, mouseClick))
        {
         x=1366; y=768; changedRes=true; visualUpdate=false;
        }

    if (is_button_pressed(res_1280x800_button, mouseClick))
        {
         x=1280; y=800; changedRes=true; visualUpdate=false;
        }

    if (is_button_pressed(res_1440x900_button, mouseClick))
        {
         x=1440; y=900; changedRes=true; visualUpdate=false;
        }

    if (is_button_pressed(res_1280x1024_button, mouseClick))
        {
         x=1280; y=1024; changedRes=true; visualUpdate=false;
        }

    if (is_button_pressed(res_1600x900_button, mouseClick))
        {
         x=1600; y=900; changedRes=true; visualUpdate=false;
        }

    if (is_button_pressed(res_1024x768_button, mouseClick))
        {
         x=1024; y=768; changedRes=true; visualUpdate=false;
        }

    if (is_button_pressed(res_800x600_button, mouseClick))
        {
         x=800; y=600; changedRes=true; visualUpdate=false;
        }

    if (changedRes && !visualUpdate)
        {
        resolution_to_text(x,y,resolution_text);
        strcpy(sir,resolution_message_text.charString);
        strcat(resolution_message_text.charString, resolution_text);
        draw_text(resolution_message_text);
        draw_text(restart_required_text);
        draw_text(click_apply_text);
        strcpy(resolution_message_text.charString, sir);
        visualUpdate=true;
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
short int nrLines=20, nrColumns=20, nrMines=40;
click_position mouseClick;
custom_game_validity customGameValidity={true,true,true};
clear_screen();
draw_menu(custom_game_menu);
screen_text_update(customGameValidity,nrLines,nrColumns,nrMines);
while (1)
    {
     click=get_mouseClick_type();
     mouseClick=get_mouseClick_postion(click);

     if (is_button_pressed(back_button, mouseClick))
         return;

    if (is_button_pressed(more_lines_button, mouseClick))
        {
        nrLines+=DELTA_LINES;
        customGameValidity=check_custom_game_validity(nrLines,nrColumns,nrMines);
        nrMines=(nrLines*nrColumns)/10;
        screen_text_update(customGameValidity,nrLines,nrColumns,nrMines);
        }

    if ( is_button_pressed(less_lines_button, mouseClick) )
        {
         nrLines-=DELTA_LINES;
         customGameValidity=check_custom_game_validity(nrLines,nrColumns,nrMines);
         nrMines=(nrLines*nrColumns)/10;
         screen_text_update(customGameValidity,nrLines,nrColumns,nrMines);
        }

    if (is_button_pressed(more_columns_button, mouseClick))
        {
         nrColumns+=DELTA_COLUMNS;
         customGameValidity=check_custom_game_validity(nrLines,nrColumns,nrMines);
         nrMines=(nrLines*nrColumns)/10;
         screen_text_update(customGameValidity,nrLines,nrColumns,nrMines);
        }

    if ( is_button_pressed(less_columns_button, mouseClick) )
        {
         nrColumns-=DELTA_COLUMNS;
         customGameValidity=check_custom_game_validity(nrLines,nrColumns,nrMines);
         nrMines=(nrLines*nrColumns)/10;
         screen_text_update(customGameValidity,nrLines,nrColumns,nrMines);
        }

    if (is_button_pressed(more_mines_button, mouseClick))
        {
         nrMines+=DELTA_MINES;
         customGameValidity=check_custom_game_validity(nrLines,nrColumns,nrMines);
         screen_text_update(customGameValidity,nrLines,nrColumns,nrMines);
        }

    if ( is_button_pressed(less_mines_button, mouseClick) )
        {
         nrMines-=DELTA_MINES;
         customGameValidity=check_custom_game_validity(nrLines,nrColumns,nrMines);
         screen_text_update(customGameValidity,nrLines,nrColumns,nrMines);
        }

    if ( is_button_pressed(apply_button, mouseClick) && customGameValidity.validNrLines && customGameValidity.validNrColumns && customGameValidity.validNrMines )
        {
         load_play_menu(CUSTOM,nrLines,nrColumns,nrMines);
         clear_screen();
         draw_menu(custom_game_menu);
         screen_text_update(customGameValidity,nrLines,nrColumns,nrMines);
        }
    }
}

void load_play_menu(char difficultyGS,short int nrLines, short int nrColumns, short int nrMines)
{
char click;
char click_effect;
bool display_message=true, timerHasStarted=false;
int secondsPassed;
relative_rectangle rTextBox;
field_position clickedFieldPosition;
play_screen playScreen;
click_position mouseClick;
game_time gameTime;
time_t now, then;

reset_game_time(gameTime);
playScreen.gameState=init_game_state(difficultyGS,nrLines,nrColumns,nrMines);
playScreen.playMenu=play_menu;
clear_screen();
draw_play_screen(playScreen);

rTextBox.rAnchorPoint=absolute_to_relative_point(playScreen.gameState.gameField.fieldBox.anchorPoint);
rTextBox.rAnchorPoint.rY-=5;
rTextBox.rHeight=5; rTextBox.rWidth=10;
mines_minus_flags_text=create_text(rTextBox,"88888",LEFT,CENTER);

if (difficultyGS!=CUSTOM)
    {
    rTextBox.rAnchorPoint=absolute_to_relative_point(playScreen.gameState.gameField.fieldBox.anchorPoint);
    rTextBox.rAnchorPoint.rY-=10;
    rTextBox.rHeight=5; rTextBox.rWidth=10;
    timer_text=create_text(rTextBox,"00:00",LEFT,CENTER);
    strcpy(timer_text.charString, game_time_as_string(gameTime));
    draw_text(timer_text);
    }

strcpy(mines_minus_flags_text.charString,convert_nr_to_char(nrMines));
draw_text(mines_minus_flags_text);
while (1)
    {

    while (playScreen.gameState.state==PENDING)
           {
            click=get_mouseClick_type();
            mouseClick=get_mouseClick_postion(click);

            if (timerHasStarted && difficultyGS!=CUSTOM)
                {
                 time(&then);
                 secondsPassed=(int)(difftime(then,now));
                 if (secondsPassed>0)
                     {
                      add_seconds(gameTime,1);
                      now=then;
                      strcpy(timer_text.charString, game_time_as_string(gameTime));
                      draw_text(timer_text);
                     }
                }

            if ( is_mine_field_click(playScreen.gameState.gameField,mouseClick) )
                {
                 clickedFieldPosition=get_field_position(playScreen.gameState.gameField,mouseClick);
                 click_effect=field_click_effect(playScreen.gameState.gameField, clickedFieldPosition,click);
                 if (click_effect!=NOTHING)
                     {
                     if (!timerHasStarted && difficultyGS!=CUSTOM)
                         {
                         localtime(&now);
                         now=then;
                         timerHasStarted=true;
                         }
                     playScreen.gameState.state=solve_click_effect(playScreen.gameState.gameField, clickedFieldPosition, click_effect);
                     //clear_screen();
                     draw_field_graphicalChanges(playScreen.gameState.gameField);
                     strcpy(mines_minus_flags_text.charString,convert_nr_to_char(nrMines-playScreen.gameState.gameField.nrOfFlags));
                     draw_text(mines_minus_flags_text);
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
                 playScreen.gameState=init_game_state(difficultyGS,nrLines,nrColumns,nrMines);
                 //playScreen.playMenu=play_menu;
                 clear_screen();
                 display_message=true;
                 draw_play_screen(playScreen);
                 strcpy(mines_minus_flags_text.charString,convert_nr_to_char(nrMines));
                 draw_text(mines_minus_flags_text);
                 if (difficultyGS!=CUSTOM)
                     {
                     reset_game_time(gameTime); timerHasStarted=false;
                     strcpy(timer_text.charString, game_time_as_string(gameTime));
                     draw_text(timer_text);
                     }
                }

            if ( is_button_pressed(back_button,mouseClick) )
                return;

           }

    click=get_mouseClick_type();
    mouseClick=get_mouseClick_postion(click);
    if (display_message)
        {if (playScreen.gameState.state==SOLVED)
            {
            //ceva
            reveal_all(playScreen.gameState.gameField);
            draw_field_graphicalChanges(playScreen.gameState.gameField);
            settextstyle(10,HORIZ_DIR,2);
            set_active_color(activeCS.mainColor);
            draw_text(succeeded_game_text);
            if (difficultyGS!=CUSTOM)
                if ( check_if_is_a_highscore(highScore,difficultyGS,gameTime) )
                    add_highscore_entry(highScore,difficultyGS,gameTime);
            //moveto(600,50);
            //outtext("SOLVED!");
            }
            else
            if (playScreen.gameState.state==FAILED)
                {
                //altceva
                settextstyle(10,HORIZ_DIR,2);
                set_active_color( create_color(255,0,0) );
                draw_text(failed_game_text);
                //moveto(600,50);
                //outtext("FAILED!");
                }
        display_message=false;
        }
    if ( is_button_pressed(reset_button,mouseClick) )
        {
         playScreen.gameState=init_game_state(difficultyGS,nrLines,nrColumns,nrMines);
         //playScreen.playMenu=play_menu;
         clear_screen();
         display_message=true;
         draw_play_screen(playScreen);
         strcpy(mines_minus_flags_text.charString,convert_nr_to_char(nrMines));
         draw_text(mines_minus_flags_text);
         if (difficultyGS!=CUSTOM)
             {
             reset_game_time(gameTime); timerHasStarted=false;
             strcpy(timer_text.charString, game_time_as_string(gameTime));
             draw_text(timer_text);
             }
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
srand( time(NULL) );
load_highscore(highScore);
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
insert_button_menu(custom_game_menu,apply_button);
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
save_highscore(highScore);
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

buttonR.rAnchorPoint.rX=10; buttonR.rAnchorPoint.rY=25;
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
resolution_message_text=create_text(rTextBox,"Resolution will be set to: ",LEFT,CENTER);

rTextBox.rAnchorPoint.rX=33; rTextBox.rAnchorPoint.rY=81;
rTextBox.rHeight=10; rTextBox.rWidth=67;
restart_required_text=create_text(rTextBox,"Restart is required.         ",LEFT,CENTER);

rTextBox.rAnchorPoint.rX=33; rTextBox.rAnchorPoint.rY=88;
rTextBox.rHeight=10; rTextBox.rWidth=67;
click_apply_text=create_text(rTextBox,"Click APPLY to exit the game.",LEFT,CENTER);

rTextBox.rAnchorPoint.rX=10; rTextBox.rAnchorPoint.rY=40;
rTextBox.rHeight=10; rTextBox.rWidth=10;
succeeded_game_text=create_text(rTextBox,"SUCCES!",LEFT,CENTER);

rTextBox.rAnchorPoint.rX=10; rTextBox.rAnchorPoint.rY=40;
rTextBox.rHeight=10; rTextBox.rWidth=10;
failed_game_text=create_text(rTextBox,"FAILED!",LEFT,CENTER);

rTextBox.rAnchorPoint.rX=33; rTextBox.rAnchorPoint.rY=64;
rTextBox.rHeight=10; rTextBox.rWidth=67;
current_lines_text=create_text(rTextBox,"Lines: ",LEFT,CENTER);

rTextBox.rAnchorPoint.rX=33; rTextBox.rAnchorPoint.rY=70;
rTextBox.rHeight=10; rTextBox.rWidth=67;
current_columns_text=create_text(rTextBox,"Columns: ",LEFT,CENTER);

rTextBox.rAnchorPoint.rX=33; rTextBox.rAnchorPoint.rY=76;
rTextBox.rHeight=10; rTextBox.rWidth=67;
current_mines_text=create_text(rTextBox,"Mines: ",LEFT,CENTER);

rTextBox.rAnchorPoint.rX=10; rTextBox.rAnchorPoint.rY=40;
rTextBox.rHeight=5; rTextBox.rWidth=10;
mines_minus_flags_text=create_text(rTextBox,"88888",LEFT,CENTER);

rTextBox.rAnchorPoint.rX=33; rTextBox.rAnchorPoint.rY=45;
rTextBox.rHeight=10; rTextBox.rWidth=10;
timer_text=create_text(rTextBox,"00:00",LEFT,CENTER);

}

void screen_text_update(custom_game_validity validity, short int nrLines, short int nrColumns, short int nrMines)
{
color_scheme activeCS;
rgb_color auxMainColor;
char sir[100];
activeCS=load_current_color_scheme();
auxMainColor=activeCS.mainColor;
setbkcolor( return_rgb_color_code(activeCS.backgroundColor) );


strcpy(sir,current_lines_text.charString);
strcat(current_lines_text.charString,convert_nr_to_char(nrLines));
if (validity.validNrLines)
    {
    setcolor( return_rgb_color_code(activeCS.mainColor) );
    draw_text(current_lines_text);
    }
    else
    {
    setcolor(RED);
    activeCS.mainColor=create_color(255,0,0);
    draw_text(current_lines_text);
    activeCS.mainColor=auxMainColor;
    }
strcpy(current_lines_text.charString,sir);

strcpy(sir,current_columns_text.charString);
strcat(current_columns_text.charString,convert_nr_to_char(nrColumns));
if (validity.validNrColumns)
    {
    setcolor( return_rgb_color_code(activeCS.mainColor) );
    draw_text(current_columns_text);
    }
    else
    {
    setcolor(RED);
    activeCS.mainColor=create_color(255,0,0);
    draw_text(current_columns_text);
    activeCS.mainColor=auxMainColor;
    }
strcpy(current_columns_text.charString,sir);

strcpy(sir,current_mines_text.charString);
strcat(current_mines_text.charString,convert_nr_to_char(nrMines));
if (validity.validNrMines)
    {
    setcolor( return_rgb_color_code(activeCS.mainColor) );
    draw_text(current_mines_text);
    }
    else
    {
    setcolor(RED);
    activeCS.mainColor=create_color(255,0,0);
    draw_text(current_mines_text);
    activeCS.mainColor=auxMainColor;
    }
strcpy(current_mines_text.charString,sir);

}
