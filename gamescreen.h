//#include "button.h"
#include "gamestate.h"

struct node{
    button inf;
    node* next;
};

typedef node* menu;

struct play_screen{
    menu playMenu;
    game_state gameState;
};


void insert_button_menu(menu& M, button B);

void delete_buttons_menu(menu& M);

void draw_menu(menu M);

void draw_play_screen(play_screen PS);
