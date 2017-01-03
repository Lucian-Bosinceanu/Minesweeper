#include "color_scheme.h"

color_scheme return_default_color_scheme()
{
color_scheme CS;

CS.backgroundColor=create_color(255,255,255);
CS.mainColor=create_color(40,100,60);
CS.secondaryColor=create_color(0,0,0);
CS.tertiaryColor=create_color(0,0,200);

return CS;
}

color_scheme create_color_scheme(rgb_color bkC, rgb_color mC, rgb_color sC, rgb_color tC)
{
color_scheme newCS;

newCS.backgroundColor=bkC;
newCS.mainColor=mC;
newCS.secondaryColor=sC;
newCS.tertiaryColor=tC;

return newCS;
}

void switch_color_scheme(color_scheme& currentCS, color_scheme desiredCS)
{
currentCS.backgroundColor=desiredCS.backgroundColor;
currentCS.mainColor=desiredCS.mainColor;
currentCS.secondaryColor=desiredCS.secondaryColor;
currentCS.tertiaryColor=desiredCS.tertiaryColor;
}

rgb_color create_color(unsigned char red, unsigned char green, unsigned char blue)
{
rgb_color newColor;

newColor.R=red;
newColor.G=green;
newColor.B=blue;

return newColor;
}

color_scheme defaultCS=return_default_color_scheme();


void set_active_color_scheme(unsigned char index)
{
activeCS=index;
}

void set_active_color(rgb_color activeC)
{
setcolor( COLOR(activeC.R, activeC.G, activeC.B) );
}

void upload_all_color_schemes(color_scheme CS[]);
{
CS[0]=defaultCS;
CS[1]=defaultCS;
CS[2]=defaultCS;
CS[3]=defaultCS;
}
