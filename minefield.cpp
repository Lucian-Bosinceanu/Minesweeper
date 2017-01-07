#include "minefield.h"

short int linDir[]={0,-1,-1,0,1,1,1,0,-1};
short int colDir[]={0,0,1,1,1,0,-1,-1,-1};

void draw_field_position(absolute_point anchorPoint,short int length, char backfieldCODE, char frontfieldCODE);

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

F.fieldBox.rAnchorPoint.rX=30;
F.fieldBox.rAnchorPoint.rY=30;
F.fieldBox.rHeight=60;
F.fieldBox.rWidth=absolute_to_relative_value(relative_to_absolute_value(70,AFTER_HEIGHT),AFTER_WIDTH);
}

mine_field create_field(short nrLines, short nrColumns, short nrMines)
{
short int i, j, dir, adjacentMines;
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

for (i=1;i<=nrLines;i++)
    for (j=1;j<=nrColumns;j++)
         if (F.backField[i][j]==EMPTY)
            {
            adjacentMines=0;
            for (dir=1;dir<=8;dir++)
                if ( F.backField[ i+linDir[dir] ][ j+colDir[dir] ]==MINE )
                    adjacentMines++;
            F.backField[i][j]=adjacentMines;
            }


return F;
}

bool is_mine_field_click(mine_field F, click_position mouseClick)
{
absolute_rectangle hitBoxB;
hitBoxB=relative_to_absolute_rectangle(F.fieldBox);
if ( mouseClick.X>=hitBoxB.anchorPont.X && mouseClick.X<=hitBoxB.anchorPont.X+hitBoxB.width &&
     mouseClick.Y>=hitBoxB.anchorPont.Y && mouseClick.Y<=hitBoxB.anchorPont.Y+hitBoxB.height)
    return true;
return false;
}

field_position get_field_position(mine_field F, click_position click)
{
short int field_position_size;
field_position clickedPosition;
absolute_rectangle hitBoxF;

hitBoxF=relative_to_absolute_rectangle(F.fieldBox);
field_position_size=hitBoxF.height/F.nrOfLines-hitBoxF.height%F.nrOfLines;

clickedPosition.lin=(click.X - hitBoxF.anchorPont.X)/field_position_size +1;
clickedPosition.col=(click.Y - hitBoxF.anchorPont.Y)/field_position_size +1;

return clickedPosition;
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
    F.frontField[ FP.lin ][ FP.lin ]=EXPLODED_MINE;
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
if (F.backField[FP.lin][FP.col]==MINE || F.backField[FP.lin][FP.col]==BORDER)
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
         F.frontField[ FP.lin + linDir[dir] ][ FP.col + colDir[dir] ]=EXPLODED_MINE;
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

void reveal_mines(mine_field& F)
{
int i;
for (i=0;i<F.nrOfMines;i++)
     F.frontField[ F.minePositions[i].lin ][ F.minePositions[i].col ]=REVEALED_MINE;
return;
}

void mark_false_flags(mine_field& F)
{
int i,j;
for (i=1;i<=F.nrOfLines;i++)
     for (j=1;j<=F.nrOfColumns;j++)
         if (F.frontField[i][j]==FLAGGED && F.backField[i][j]!=MINE)
             F.frontField[i][j]=FALSE_FLAG;
}

void draw_field(mine_field& F)
{
int i,j,currentX,currentY;
color_scheme activeCS;
activeCS=load_current_color_scheme();
absolute_rectangle aFieldBox;
absolute_point screen_position;
short int field_position_size;
aFieldBox=relative_to_absolute_rectangle(F.fieldBox);
field_position_size=aFieldBox.height/F.nrOfLines-aFieldBox.height%F.nrOfLines;

for (i=1;i<=F.nrOfLines;i++)
     for (j=1;j<=F.nrOfColumns;j++)
         {
          screen_position.X=aFieldBox.anchorPont.X+(i-1)*field_position_size;
          screen_position.Y=aFieldBox.anchorPont.Y+(j-1)*field_position_size;
          draw_field_position(screen_position,field_position_size,F.backField[i][j],F.frontField[i][j]);
         }

set_active_color(activeCS.mainColor);
setlinestyle(0,0,3);
line(aFieldBox.anchorPont.X, aFieldBox.anchorPont.Y, aFieldBox.anchorPont.X+aFieldBox.height, aFieldBox.anchorPont.Y);
line(aFieldBox.anchorPont.X, aFieldBox.anchorPont.Y, aFieldBox.anchorPont.X, aFieldBox.anchorPont.Y+aFieldBox.height);
line(aFieldBox.anchorPont.X+aFieldBox.height, aFieldBox.anchorPont.Y, aFieldBox.anchorPont.X+aFieldBox.height, aFieldBox.anchorPont.Y+aFieldBox.height);
line(aFieldBox.anchorPont.X, aFieldBox.anchorPont.Y+aFieldBox.height, aFieldBox.anchorPont.X+aFieldBox.height, aFieldBox.anchorPont.Y+aFieldBox.height);

setlinestyle(0,0,1);
currentX=aFieldBox.anchorPont.X;
currentY=aFieldBox.anchorPont.Y;
for (i=1;i<=F.nrOfLines;i++)
     {
      line(aFieldBox.anchorPont.X,currentY,aFieldBox.height,currentY);
      line(currentX,aFieldBox.anchorPont.Y,currentX,aFieldBox.height);
      currentX+=field_position_size;
      currentY+=field_position_size;
     }
}

void draw_field_position(absolute_point anchorPoint,short int length, char backfieldCODE, char frontfieldCODE)
{
color_scheme activeCS;
activeCS=load_current_color_scheme();
set_active_color(activeCS.tertiaryColor);
setfillstyle(SOLID_FILL, return_rgb_color_code(activeCS.tertiaryColor) );
if (frontfieldCODE==REVEALED)
    {
     if (backfieldCODE==EMPTY) return;
     if (backfieldCODE==1)
         readimagefile("images\1.jpg",anchorPoint.X,anchorPoint.Y,anchorPoint.X+length,anchorPoint.Y+length);
     if (backfieldCODE==2)
         readimagefile("images\2.jpg",anchorPoint.X,anchorPoint.Y,anchorPoint.X+length,anchorPoint.Y+length);
     if (backfieldCODE==3)
         readimagefile("images\3.jpg",anchorPoint.X,anchorPoint.Y,anchorPoint.X+length,anchorPoint.Y+length);
     if (backfieldCODE==4)
         readimagefile("images\4.jpg",anchorPoint.X,anchorPoint.Y,anchorPoint.X+length,anchorPoint.Y+length);
     if (backfieldCODE==5)
          readimagefile("images\5.jpg",anchorPoint.X,anchorPoint.Y,anchorPoint.X+length,anchorPoint.Y+length);
     if (backfieldCODE==6)
          readimagefile("images\6.jpg",anchorPoint.X,anchorPoint.Y,anchorPoint.X+length,anchorPoint.Y+length);
     if (backfieldCODE==7)
          readimagefile("images\7.jpg",anchorPoint.X,anchorPoint.Y,anchorPoint.X+length,anchorPoint.Y+length);
     if (backfieldCODE==8)
          readimagefile("images\8.jpg",anchorPoint.X,anchorPoint.Y,anchorPoint.X+length,anchorPoint.Y+length);
    return;
    }
    else
    {
     bar(anchorPoint.X,anchorPoint.Y,anchorPoint.X+length,anchorPoint.Y+length);
     if (frontfieldCODE==HIDDEN)
         return;
     if (frontfieldCODE==FLAGGED)
         readimagefile("images\flag.jpg",anchorPoint.X,anchorPoint.Y,anchorPoint.X+length,anchorPoint.Y+length);
     if (frontfieldCODE==REVEALED_MINE)
         readimagefile("images\mine.jpg",anchorPoint.X,anchorPoint.Y,anchorPoint.X+length,anchorPoint.Y+length);
     if (frontfieldCODE==FALSE_FLAG)
         readimagefile("images\false_flag.jpg",anchorPoint.X,anchorPoint.Y,anchorPoint.X+length,anchorPoint.Y+length);
     if (frontfieldCODE==EXPLODED_MINE)
         readimagefile("images\exploded_mine.jpg",anchorPoint.X,anchorPoint.Y,anchorPoint.X+length,anchorPoint.Y+length);
    }
}

bool is_solved_correctly(mine_field F)
{
int i;
for (i=0;i<F.nrOfMines;i++)
     if ( F.frontField[ F.minePositions[i].lin ][ F.minePositions[i].col ]!=FLAGGED )
         return false;
return true;
}
