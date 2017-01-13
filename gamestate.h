#include "minefield.h"
#define PENDING 1
#define FAILED 0
#define SOLVED 2

#define EASY 1
#define MEDIUM 2
#define HARD 3
#define CUSTOM 4

#define EASY_LINES 9
#define EASY_COLUMNS 9
#define EASY_MINES 10

#define MEDIUM_LINES 16
#define MEDIUM_COLUMNS 16
#define MEDIUM_MINES 40

#define HARD_LINES 20
#define HARD_COLUMNS 20
#define HARD_MINES 60

#define INSANE_LINES 30
#define INSANE_COLUMNS 30
#define INSANE_MINES 100

struct game_state{
    char state;
    mine_field gameField;
    char difficulty;
};

struct custom_game_validity{
    bool validNrLines;
    bool validNrColumns;
    bool validNrMines;
};

struct high_score{
    char player_name[35];
};

game_state init_game_state(char difficultyGS, short int nrLines, short int nrColumns, short int nrMines);

custom_game_validity check_custom_game_validity(short int &nrLines, short int &nrColumns, short int &nrMines);
