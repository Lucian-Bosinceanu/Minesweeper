#include "gamescreen.h"

void insert_button_menu(menu& M, button B)
{
node* p=new node;
p->inf=B;
p->next=M;
M=p;
}

void delete_buttons_menu(menu& M)
{
menu iterator_pointer;
if (M==0)
    return;
while (M!=0)
    {
     iterator_pointer=M;
     M=M->next;
     delete iterator_pointer;
    }
}

void draw_menu(menu M)
{
menu iterator_pointer;
iterator_pointer=M;
while (iterator_pointer!=0)
    {
    draw_button(iterator_pointer->inf);
    iterator_pointer=iterator_pointer->next;
    }
}

void draw_play_screen(play_screen PS)
{
draw_menu(PS.playMenu);
draw_field(PS.gameState.gameField);
}
