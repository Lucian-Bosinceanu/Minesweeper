#include "minefield.h"

short int linDir[]={0,-1,-1,0,1,1,1,0,-1};
short int colDir[]={0,0,1,1,1,0,-1,-1,-1};

void clear_field(mine_field& F)
{
int i, j;

F.nrOfLines=0;
F.nrOfColumns=0;
F.nrOfFlags=0;
F.nrOfMines=0;

for (i=0;i<MAX_LIN;i++)
     for (j=0;j<MAX_COL;j++)
        {
        F.backField[i][j]=EMPTY;
        F.frontField[i][j]=HIDDEN;
        }

for (i=0;i<MAX_MINE;i++)
     F.minePositions[i].lin=F.minePositions[i].col=EMPTY;
}

mine_field create_field(short nrLines, short nrColumns, short nrMines)
{
int i, j;
mine_field F;
field_position P;
clear_field(F);

F.nrOfLines=nrLines;
F.nrOfColumns=nrColumns;
F.nrOfMines=nrMines;

for (i=0,j=0;i<=nrLines+1;i++)
     F.backField[i][j]=F.backField[i][nrColumns+1]=BORDER;
for (i=0,j=0;j<=nrColumns+1;j++)
     F.backField[i][j]=F.backField[nrLines+1][j]=BORDER;

srand( time(NULL) );
i=0;
while (i<nrMines)
    {
     P.lin=rand()%nrLines+1;
     P.col=rand()%nrColumns+1;
     if ( F.backField[P.lin][P.col]!=MINE )
        {
         F.backField[P.lin][P.col]=MINE;
         F.minePositions[i]=P;
         ++i;
        }
    }
return F;
}


char field_click_effect(mine_field F, field_position FP, char clickType)
{
if ( F.frontField[ FP.lin ][ FP.col ]==REVEALED )
    return NOTHING;

if ( F.backField[ FP.lin ][ FP.col ]==MINE )
    return MINE_CLICK;

if (clickType==LEFT_CLICK)
    return REVEAL_CLICK;

if (clickType==RIGHT_CLICK && F.frontField[ FP.lin ][ FP.col ]!=FLAGGED)
    return PLACE_FLAG_CLICK;

if (clickType==RIGHT_CLICK && F.frontField[ FP.lin ][ FP.col ]==FLAGGED)
    return REMOVE_FLAG_CLICK;

if (clickType==BOTH_CLICK && F.frontField[ FP.lin ][ FP.col ]==REVEALED && F.backField[ FP.lin ][ FP.col ]!=0)
    {
     int adjacent_flags=0;
     for (int dir=1;dir<=8;dir++)
          if (F.frontField[ FP.lin + linDir[dir] ][ FP.col + colDir[dir] ]==FLAGGED)
              adjacent_flags++;
     if (adjacent_flags>=F.backField[ FP.lin ][ FP.col ])
         return CHORD_CLICK;
    }

return NOTHING;
}

bool solve_click_effect(mine_field& F, field_position FP, char clickEffect)
{
if (clickEffect==NOTHING)
    return true;

if (clickEffect==MINE_CLICK)
    {
    F.frontField[ FP.lin ][ FP.lin ]=EXPLODED;
    return false;
    }

if (clickEffect==REVEAL_CLICK)
    {
    field_reveal(F, FP);
    return true;
    }
if (clickEffect==PLACE_FLAG_CLICK)
    {
    place_flag(F, FP);
    return true;
    }
if (clickEffect==REMOVE_FLAG_CLICK)
    {
     remove_flag(F, FP);
     return true;
    }
if (clickEffect==CHORD_CLICK)
    return field_chord(F, FP);
}

void field_reveal(mine_field& F, field_position FP)
{
int dir;
field_position new_FP;
if (F.backField[FP.lin][FP.col]==MINE)
    return;
F.frontField[FP.lin][FP.col]=REVEALED;
if (F.backField[FP.lin][FP.col]!=EMPTY)
    return;
for (dir=1;dir<=8;dir++)
    {
     new_FP.lin=FP.lin + linDir[dir];
     new_FP.col=FP.col + colDir[dir];
     field_reveal(F, new_FP);
     }
}
bool field_chord(mine_field& F, field_position FP)
{
int dir;
field_position new_FP;
for (dir=1;dir<=8;dir++)
     if (F.backField[ FP.lin + linDir[dir] ][ FP.col + colDir[dir] ]==MINE &&
         F.frontField[ FP.lin + linDir[dir] ][ FP.col + colDir[dir] ]!=FLAGGED)
        {
         F.frontField[ FP.lin + linDir[dir] ][ FP.col + colDir[dir] ]=EXPLODED;
         return false;
        }
for (dir=1;dir<=8;dir++)
     if (F.frontField[ FP.lin + linDir[dir] ][ FP.col + colDir[dir] ]==HIDDEN)
         {
         new_FP.lin=FP.lin + linDir[dir];
         new_FP.col=FP.col + colDir[dir];
         field_reveal(F, new_FP);
         }
return true;
}

void place_flag(mine_field& F, field_position flagPosition)
{
F.nrOfFlags++;
F.frontField[flagPosition.lin][flagPosition.col]=FLAGGED;
return;
}

void remove_flag(mine_field& F, field_position flagPosition)
{
F.nrOfFlags--;
F.frontField[flagPosition.lin][flagPosition.col]=HIDDEN;
}

void explode_mines(mine_field& F)
{
int i;
for (i=0;i<F.nrOfMines;i++)
     F.frontField[ F.minePositions[i].lin ][ F.minePositions[i].col ]=EXPLODED;
return;
}
