
struct game_time{
    int seconds;
    int minutes;
};


void reset_game_time(game_time& GT);
void add_seconds(game_time& GT, int nrSec);
char* game_time_as_string(game_time GT);

char* convert_nr_to_char(short int nr);
