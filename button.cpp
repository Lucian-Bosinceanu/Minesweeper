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
color_scheme activeCS;
absolute_rectangle buttonBorder;
activeCS=load_current_color_scheme();
buttonBorder=relative_to_absolute_rectangle(B.buttonBox);

set_active_color( activeCS.mainColor );
setfillstyle(SOLID_FILL, return_rgb_color_code(activeCS.mainColor) );
bar(buttonBorder.anchorPont.X,buttonBorder.anchorPont.Y, buttonBorder.anchorPont.X + buttonBorder.width, buttonBorder.anchorPont.Y + buttonBorder.height);

setlinestyle(0,0,2);
set_active_color(activeCS.secondaryColor);
rectangle(buttonBorder.anchorPont.X,buttonBorder.anchorPont.Y, buttonBorder.anchorPont.X + buttonBorder.width, buttonBorder.anchorPont.Y + buttonBorder.height);

for (i=4;i>=0;i--)
    {
     settextstyle(10,HORIZ_DIR,i);
     if ( textheight(B.text)<=buttonBorder.height/2 )
         break;
    }

for (;i>=0;i--)
{
 settextstyle(10,HORIZ_DIR,i);
 if ( textwidth(B.text)<=buttonBorder.width )
     break;
}

//setbkcolor(WHITE);
setbkcolor(return_rgb_color_code(activeCS.mainColor));
set_active_color(activeCS.backgroundColor);
moveto(buttonBorder.anchorPont.X + ( buttonBorder.width-textwidth(B.text) )/2, buttonBorder.anchorPont.Y + ( buttonBorder.height-textheight(B.text) )/2 );
outtext(B.text);
}
