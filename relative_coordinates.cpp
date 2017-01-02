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

absolute_rectangle relative_to_absolute_rectangle(relative_rectangle rRect)
{
absolute_rectangle rect;

rect.anchorPont=relative_to_absolute_point(rRect.rAnchorPoint);
rect.width=relative_to_absolute_value(rRect.rWidth, AFTER_WIDTH);
rect.height=relative_to_absolute_value(rRect.rHeight, AFTER_HEIGHT);

return rect;
}



relative_rectangle absolute_to_relative_rectangle(absolute_rectangle rect)
{
relative_rectangle rRect;

rRect.rAnchorPoint=absolute_to_relative_point(rect.anchorPont);
rRect.rHeight=absolute_to_relative_value(rect.height, AFTER_HEIGHT);
rRect.rWidth=absolute_to_relative_value(rect.width, AFTER_WIDTH);

return rRect;
}

