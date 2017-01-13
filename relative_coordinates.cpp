#include "relative_coordinates.h"

using namespace std;


short int relative_to_absolute_value(char percent, char dimension_code)
{
short int result;
short int MAXX,MAXY;
ifstream fin("resolution.txt");
fin>>MAXX>>MAXY;

if (dimension_code==AFTER_WIDTH)
    result=(percent*MAXX)/100;
    else
    if (dimension_code==AFTER_HEIGHT)
        result=(percent*MAXY)/100;

fin.close();
return result;
}

char absolute_to_relative_value(short int position, char dimension_code)
{
char percent;
short int MAXX,MAXY;
ifstream fin("resolution.txt");
fin>>MAXX>>MAXY;

if (dimension_code==AFTER_WIDTH)
    {
     if (position>MAXX || position<0)
         return -1;
    }
    else
    if (dimension_code==AFTER_HEIGHT)
        {
        if (position>MAXY || position<0)
            return -1;
        }

if (dimension_code==AFTER_WIDTH)
    percent=(100*position)/MAXX;
    else
    if (dimension_code==AFTER_HEIGHT)
        percent=(100*position)/MAXY;

fin.close();
return percent;
}


absolute_point relative_to_absolute_point(relative_point rP)
{
absolute_point P;
short int MAXX,MAXY;
ifstream fin("resolution.txt");
fin>>MAXX>>MAXY;

P.X=(rP.rX*MAXX)/100;
P.Y=(rP.rY*MAXY)/100;

fin.close();
return P;
}

relative_point absolute_to_relative_point(absolute_point P)
{
relative_point rP;
short int MAXX,MAXY;
ifstream fin("resolution.txt");
fin>>MAXX>>MAXY;

rP.rX=(100*P.X)/MAXX;
rP.rY=(100*P.Y)/MAXY;

fin.close();
return rP;
}

absolute_rectangle relative_to_absolute_rectangle(relative_rectangle rRectangle)
{
absolute_rectangle rectangle;

rectangle.anchorPoint=relative_to_absolute_point(rRectangle.rAnchorPoint);
rectangle.width=relative_to_absolute_value(rRectangle.rWidth, AFTER_WIDTH);
rectangle.height=relative_to_absolute_value(rRectangle.rHeight, AFTER_HEIGHT);

return rectangle;
}



relative_rectangle absolute_to_relative_rectangle(absolute_rectangle rectangle)
{
relative_rectangle rRectangle;

rRectangle.rAnchorPoint=absolute_to_relative_point(rectangle.anchorPoint);
rRectangle.rHeight=absolute_to_relative_value(rectangle.height, AFTER_HEIGHT);
rRectangle.rWidth=absolute_to_relative_value(rectangle.width, AFTER_WIDTH);

return rRectangle;
}

void set_new_screen_resolution(short int width, short int height)
{
ofstream fout("resolution.txt");
fout<<width<<' '<<height<<'\n';
fout.close();
}

void resolution_to_text(short int width, short int height,char sir[])
{
short int X,Y,position=0,i;
X=width; Y=height;
while (Y!=0)
    {
    sir[position++]=Y%10+'0';
    Y/=10;
    }
sir[position++]=' ';

while (X!=0)
    {
    sir[position++]=X%10+'0';
    X/=10;
    }
for (i=0;i<position/2;i++)
    {
     sir[i]=sir[i]^sir[position-i-1];
     sir[position-i-1]=sir[i]^sir[position-i-1];
     sir[i]=sir[i]^sir[position-i-1];
    }
sir[position]=0;
}
