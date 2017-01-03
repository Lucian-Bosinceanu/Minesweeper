#include "button.h"
#include <cstring>


button create_button(relative_rectangle rButtonBox, char content[], char function_code)
{
button newButton;

newButton.buttonBox=rButtonBox;
strcpy(newButton.text, content);
newButton.buttonFunction=function_code;

return newButton;
}


void press_button(button B)
{
if (B.buttonFunction==EXIT_GAME)
    return;
}

bool is_button_pressed(button B, click_position mouseClick)
{
absolute_rectangle hitBoxB;
hitBoxB=relative_to_absolute_rectangle(B.buttonBox);
if ( mouseClick.X>=hitBoxB.anchorPont.X && mouseClick.X<=hitBoxB.anchorPont.X+hitBoxB.width &&
     mouseClick.Y>=hitBoxB.anchorPont.Y && mouseClick.Y<=hitBoxB.anchorPont.Y+hitBoxB.height)
    return true;
return false;
}

void draw_button(button B)
{
int i=4;
absolute_rectangle buttonBorder;

buttonBorder=relative_to_absolute_rectangle(B.buttonBox);
setlinestyle(0,0,3);
set_active_color( allCS[activeCS].mainColor );
rectangle(buttonBorder.anchorPont.X,buttonBorder.anchorPont.Y, buttonBorder.anchorPont.X + buttonBorder.width, buttonBorder.anchorPont.Y + buttonBorder.height);

for (i=4;i>=0;i--)
    {
     settextstyle(10,HORIZ_DIR,i);
     if ( textheight(B.text)<=buttonBorder.height )
         break;
    }

set_active_color(allCS[activeCS].secondaryColor);
moveto(buttonBorder.anchorPont.X + ( buttonBorder.width-textwidth(B.text) )/2, buttonBorder.anchorPont.Y + ( buttonBorder.height-textheight(B.text) )/2 );
outtext(B.text);
}
