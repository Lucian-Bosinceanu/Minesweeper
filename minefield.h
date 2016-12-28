#include <cstdlib>
#include <ctime>

#define MAX_LIN 100
#define MAX_COL 100
#define MAX_MINE 100

#define MINE -1
#define EMPTY 0
#define BORDER -2

#define FLAGGED -1
#define REVEALED 1
#define HIDDEN 0
#define EXPLODED 2

#define LEFT_CLICK 1
#define RIGHT_CLICK 2
#define BOTH_CLICK 3

#define NOTHING 0
#define PLACE_FLAG_CLICK 1
#define REMOVE_FLAG_CLICK 2
#define MINE_CLICK 3
#define REVEAL_CLICK 4
#define CHORD_CLICK 5

struct field_position{
    short int lin;
    short int col;
};


struct mine_field{
    short int nrOfLines;
    short int nrOfColumns;
    short int nrOfMines;
    short int nrOfFlags;

    char backField[MAX_LIN][MAX_COL];
    char frontField[MAX_LIN][MAX_COL];

    field_position minePositions[MAX_MINE];
};

void clear_field(mine_field& F);

mine_field create_field(short nrLines, short nrColumns, short nrMines);

char field_click_effect(mine_field F, field_position FP, char clickType);
bool solve_click_effect(mine_field& F, field_position FP, char clickEffect);

void field_reveal(mine_field& F, field_position FP);
bool field_chord(mine_field& F, field_position FP);

void place_flag(mine_field& F, field_position flagPosition);
void remove_flag(mine_field& F, field_position flagPosition);

void explode_mines(mine_field& F);
