#include <cstring>
#include "text.h"

text create_text(relative_rectangle textBox, char sir[],char hAlign=CENTER, char vAlign=CENTER)
{
text T;
int i;
absolute_rectangle aTextBox=relative_to_absolute_rectangle(textBox);
strcpy(T.charString,sir);
T.rTextBox=textBox;
T.horizontalAlign=hAlign;
T.verticalAlign=vAlign;

for (i=4;i>=0;i--)
    {
     settextstyle(10,HORIZ_DIR,i);
     if ( textheight(T.charString)<=aTextBox.height/2 )
         break;
    }

for (;i>=0;i--)
    {
     settextstyle(10,HORIZ_DIR,i);
     if ( textwidth(T.charString)<=aTextBox.width )
         break;
    }

T.textSize=i;

if (T.horizontalAlign==LEFT)
    T.drawingPoint.X=aTextBox.anchorPoint.X;
    else
    if (T.horizontalAlign==RIGHT)
        T.drawingPoint.X=aTextBox.anchorPoint.X+aTextBox.width-textwidth(T.charString);
        else
        if (T.horizontalAlign==CENTER)
            T.drawingPoint.X=aTextBox.anchorPoint.X+(aTextBox.width-textwidth(T.charString))/2;

if (T.verticalAlign==TOP)
    T.drawingPoint.Y=aTextBox.anchorPoint.Y;
    else
    if (T.verticalAlign==BOTTOM)
        T.drawingPoint.Y=aTextBox.anchorPoint.Y+aTextBox.height-textheight(T.charString);
        else
        if (T.verticalAlign==CENTER)
            T.drawingPoint.Y=aTextBox.anchorPoint.Y+(aTextBox.height-textheight(T.charString))/2;

return T;
}

void draw_text(text T)
{
color_scheme activeCS;
activeCS=load_current_color_scheme();

setbkcolor(return_rgb_color_code(activeCS.backgroundColor));
set_active_color(activeCS.mainColor);
settextstyle(10,HORIZ_DIR,T.textSize);
moveto(T.drawingPoint.X, T.drawingPoint.Y);
outtext(T.charString);
}
