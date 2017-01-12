#include "gamestate.h"

game_state init_game_state(char difficultyGS)
{
game_state createdGameState;

createdGameState.state=PENDING;
createdGameState.difficulty=difficultyGS;

if (difficultyGS==EASY)
    createdGameState.gameField=create_field(EASY_LINES, EASY_COLUMNS, EASY_MINES);
if (difficultyGS==MEDIUM)
    createdGameState.gameField=create_field(MEDIUM_LINES, MEDIUM_COLUMNS, MEDIUM_MINES);
if (difficultyGS==HARD)
    createdGameState.gameField=create_field(HARD_LINES, HARD_COLUMNS, HARD_MINES);
//if (difficultyGS==INSANE)
//    createdGameState.gameField=create_field(INSANE_LINES, INSANE_COLUMNS, INSANE_MINES);

return createdGameState;
}
