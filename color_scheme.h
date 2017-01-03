#include <graphics.h>

struct rgb_color{
    unsigned char R,G,B;
};


struct color_scheme{
    rgb_color backgroundColor;
    rgb_color mainColor;
    rgb_color secondaryColor;
    rgb_color tertiaryColor;
};


color_scheme return_default_color_scheme();

color_scheme create_color_scheme(rgb_color bkC, rgb_color mC, rgb_color sC, rgb_color tC);

void switch_color_scheme(color_scheme& currentCS, color_scheme desiredCS);

rgb_color create_color(unsigned char red, unsigned char green, unsigned char blue);

void upload_all_color_schemes(color_scheme CS[]);

void set_active_color(rgb_color activeC);
void set_active_color_scheme(unsigned char index);
