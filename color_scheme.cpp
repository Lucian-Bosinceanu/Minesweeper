#include "color_scheme.h"
#include "fstream"

using namespace std;

color_scheme return_default_color_scheme()
{
color_scheme CS;

CS.backgroundColor=create_color(255,255,255); //alb
CS.mainColor=create_color(10,15,13);
CS.secondaryColor=create_color(238,66,102);
CS.tertiaryColor=create_color(196,196,196); //gri

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


/*void set_active_color_scheme(unsigned char index)
{
activeCS=index;
}*/

void set_active_color(rgb_color activeC)
{
setcolor( COLOR(activeC.R, activeC.G, activeC.B) );
}

int return_rgb_color_code(rgb_color C)
{
return COLOR(C.R, C.G, C.B);
}

/*void upload_all_color_schemes(color_scheme CS[]);
{
CS[0]=defaultCS;
CS[1]=defaultCS;
CS[2]=defaultCS;
CS[3]=defaultCS;
}*/

color_scheme load_current_color_scheme()
{
int index;
ifstream fin ("color_scheme.txt");
fin>>index;
if (index==1)
    return return_default_color_scheme();
if (index==2)
    return create_color_scheme( create_color(255,255,255), create_color(64,64,64), create_color(33,161,121), create_color(196,196,196) );
if (index==3)
    return create_color_scheme( create_color(255,255,255), create_color(28,49,68), create_color(126,161,107), create_color(196,196,196) );

return return_default_color_scheme();
}

void change_global_color_scheme(int index)
{
ofstream fout("color_scheme.txt");
fout<<index<<'\n';
fout.close();
}
