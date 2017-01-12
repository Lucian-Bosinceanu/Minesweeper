#include "button.h"
#include <cstring>


button create_button(relative_rectangle rButtonBox, char content[])
{
button newButton;

newButton.buttonBox=rButtonBox;
strcpy(newButton.text, content);

return newButton;
}

bool is_button_pressed(button B, click_position mouseClick)
{
absolute_rectangle hitBoxB;
hitBoxB=relative_to_absolute_rectangle(B.buttonBox);
if ( mouseClick.X>=hitBoxB.anchorPoint.X && mouseClick.X<=hitBoxB.anchorPoint.X+hitBoxB.width &&
     mouseClick.Y>=hitBoxB.anchorPoint.Y && mouseClick.Y<=hitBoxB.anchorPoint.Y+hitBoxB.height)
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
bar(buttonBorder.anchorPoint.X,buttonBorder.anchorPoint.Y, buttonBorder.anchorPoint.X + buttonBorder.width, buttonBorder.anchorPoint.Y + buttonBorder.height);

setlinestyle(0,0,2);
set_active_color(activeCS.secondaryColor);
rectangle(buttonBorder.anchorPoint.X,buttonBorder.anchorPoint.Y, buttonBorder.anchorPoint.X + buttonBorder.width, buttonBorder.anchorPoint.Y + buttonBorder.height);

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
set_active_color(activeCS.secondaryColor);
moveto(buttonBorder.anchorPoint.X + ( buttonBorder.width-textwidth(B.text) )/2, buttonBorder.anchorPoint.Y + ( buttonBorder.height-textheight(B.text) )/2 );
outtext(B.text);
}
