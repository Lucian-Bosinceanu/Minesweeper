#include <cstdlib>
#include "button.h"

#define MAX_LIN 100
#define MAX_COL 100
#define MAX_MINE 300

#define MINE -1
#define EMPTY 0
#define BORDER -2

#define FLAGGED -1
#define REVEALED 1
#define HIDDEN 0
#define EXPLODED_MINE 2
#define FALSE_FLAG 3
#define REVEALED_MINE 4

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
    char lin;
    char col;
};

struct nod{
    field_position inf;
    nod* next;
};

typedef nod* stack_list;

struct mine_field{
    short int nrOfLines;
    short int nrOfColumns;
    short int nrOfMines;
    short int nrOfFlags;

    char backField[MAX_LIN][MAX_COL];
    char frontField[MAX_LIN][MAX_COL];

    field_position minePositions[MAX_MINE];

    absolute_rectangle fieldBox;

    stack_list graphicalChanges;
};


void clear_field(mine_field& F);

mine_field create_field(short nrLines, short nrColumns, short nrMines);

bool is_mine_field_click(mine_field F, click_position mouseClick);
field_position get_field_position(mine_field F, click_position click);
char field_click_effect(mine_field F, field_position FP, char clickType);
bool solve_click_effect(mine_field& F, field_position FP, char clickEffect);

void field_reveal(mine_field& F, field_position FP);
bool field_chord(mine_field& F, field_position FP);

void place_flag(mine_field& F, field_position flagPosition);
void remove_flag(mine_field& F, field_position flagPosition);

void reveal_mines(mine_field& F);
void mark_false_flags(mine_field& F);
void reveal_all(mine_field& F);

void draw_field(mine_field& F);
void draw_field_graphicalChanges(mine_field& F);

bool is_solved_correctly(mine_field F);

void push_stack_list(stack_list& SL, field_position FP);
bool is_empty_stack_list(stack_list SL);
field_position pop_stack_list(stack_list& SL);
