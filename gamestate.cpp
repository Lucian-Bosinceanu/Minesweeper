#include "gamestate.h"

game_state init_game_state(char difficultyGS, short int nrLines, short int nrColumns, short int nrMines)
{
game_state createdGameState;

createdGameState.state=PENDING;
createdGameState.difficulty=difficultyGS;
createdGameState.gameField=create_field(nrLines, nrColumns, nrMines);
return createdGameState;
}

custom_game_validity check_custom_game_validity(short int &nrLines, short int &nrColumns, short int &nrMines)
{
custom_game_validity V={true,true,true};
short int height, width;
short int mine_field_position_size;
char heightPercent, widthPercent;

/*if (nrLines<5)
    V.validNrLines=false;
if (nrColumns<5)
    V.validNrColumns=false;
if (nrMines<5 || nrMines>=nrLines*nrColumns)
    V.validNrMines=false;*/

mine_field_position_size=relative_to_absolute_value(3,AFTER_HEIGHT);
if (nrLines>30)
    mine_field_position_size=relative_to_absolute_value(2,AFTER_HEIGHT);
//if (nrLines>45)
//    mine_field_position_size=relative_to_absolute_value(1,AFTER_HEIGHT);

height=mine_field_position_size*nrLines;
width=mine_field_position_size*nrColumns;

heightPercent=absolute_to_relative_value(height, AFTER_HEIGHT);
widthPercent=absolute_to_relative_value(width, AFTER_WIDTH);

if (heightPercent>90 || heightPercent<0)
    V.validNrLines=false;
if (widthPercent>75 || widthPercent<0)
    V.validNrColumns=false;

if (nrLines<5)
    nrLines=5;
if (nrLines>45)
    {
    nrLines=45;
    V.validNrLines=true;
    }
if (nrColumns<5)
    nrColumns=5;
if (nrColumns>65)
    {
    nrColumns=65;
    V.validNrColumns=true;
    }
if (nrMines<=0)
    {
    nrMines=1;
    V.validNrMines=true;
    }
if (nrMines>=nrLines*nrColumns)
    {
    nrMines=nrLines*nrColumns;
    V.validNrMines=true;
    }
if (nrMines>=MAX_MINE)
    nrMines=MAX_MINE-1;

return V;
}
