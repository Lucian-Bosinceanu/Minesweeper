#include "minefield.h"
#include "game_time.h"
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

#define MAX_ENTRIES 5
#define MAX_PLAYER_NAME 25

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

struct highscore_entry{
    char player_name[MAX_PLAYER_NAME];
    game_time player_time;
};

struct highscore_tab{
    short int nr_of_entries;
    highscore_entry entries[MAX_ENTRIES];
};

struct highscore{
    char difficulty_code;
    highscore_tab highscore_pages[3];
};

game_state init_game_state(char difficultyGS, short int nrLines, short int nrColumns, short int nrMines);

custom_game_validity check_custom_game_validity(short int &nrLines, short int &nrColumns, short int &nrMines);

void load_highscore(highscore& HS);
void save_highscore(highscore HS);
bool check_if_is_a_highscore(highscore HS, char difficultyCode, game_time scoredTime);
void add_highscore_entry(highscore& HS, char difficultyCode, game_time scoredTime);
void draw_high_score_tab(highscore_tab HT);
