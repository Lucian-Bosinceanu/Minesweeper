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

int return_rgb_color_code(rgb_color C);

color_scheme return_default_color_scheme();

color_scheme create_color_scheme(rgb_color bkC, rgb_color mC, rgb_color sC, rgb_color tC);

color_scheme load_current_color_scheme();

void switch_color_scheme(color_scheme& currentCS, color_scheme desiredCS);

rgb_color create_color(unsigned char red, unsigned char green, unsigned char blue);

void upload_all_color_schemes(color_scheme CS[]);

void set_active_color(rgb_color activeC);
//void set_active_color_scheme(unsigned char index);
