#include "minefield.h"
#include <ctime>

//vectorii merg mai intai in forma de plus primele 5 pozitii, apoi in forma de X ultimele 4 pozitii
short int linDir[]={0,-1,0,1,0,-1,1,1,-1};
short int colDir[]={0,0,1,0,-1,1,1,-1,-1};

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

F.graphicalChanges=NULL;
}

mine_field create_field(short nrLines, short nrColumns, short nrMines)
{
short int i, j, dir, adjacentMines,field_position_size;
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

field_position_size=relative_to_absolute_value(3,AFTER_HEIGHT);
if (nrLines>30)
    field_position_size=relative_to_absolute_value(2,AFTER_HEIGHT);
if (nrLines>45)
    field_position_size=relative_to_absolute_value(1,AFTER_HEIGHT);

F.fieldBox.height=field_position_size*F.nrOfLines;
F.fieldBox.width=field_position_size*F.nrOfColumns;
F.fieldBox.anchorPoint.Y=relative_to_absolute_value( ( 100- absolute_to_relative_value(F.fieldBox.height,AFTER_HEIGHT) )/2,AFTER_HEIGHT);
F.fieldBox.anchorPoint.X=relative_to_absolute_value(20,AFTER_WIDTH) + relative_to_absolute_value( ( 80 - absolute_to_relative_value(F.fieldBox.width,AFTER_WIDTH) )/2,AFTER_WIDTH);
//F.fieldBox.rAnchorPoint.rY=25;
//F.fieldBox.rHeight=70;
//F.fieldBox.rWidth=absolute_to_relative_value(relative_to_absolute_value(60,AFTER_HEIGHT),AFTER_WIDTH);

return F;
}

bool is_mine_field_click(mine_field F, click_position mouseClick)
{
absolute_rectangle hitBoxB=F.fieldBox;
//hitBoxB=relative_to_absolute_rectangle(F.fieldBox);
//hitBoxB.width=hitBoxB.height;
if ( mouseClick.X>=hitBoxB.anchorPoint.X && mouseClick.X<=hitBoxB.anchorPoint.X+hitBoxB.width &&
     mouseClick.Y>=hitBoxB.anchorPoint.Y && mouseClick.Y<=hitBoxB.anchorPoint.Y+hitBoxB.height)
    return true;
return false;
}

field_position get_field_position(mine_field F, click_position click)
{
short int field_position_size;
field_position clickedPosition;
absolute_rectangle hitBoxF=F.fieldBox;

//hitBoxF=relative_to_absolute_rectangle(F.fieldBox);
field_position_size=hitBoxF.height/F.nrOfLines;
//F.fieldBox.height=F.fieldBox.width=field_position_size*F.nrOfLines;

clickedPosition.col=(click.X - hitBoxF.anchorPoint.X)/field_position_size +1;
clickedPosition.lin=(click.Y - hitBoxF.anchorPoint.Y)/field_position_size +1;

return clickedPosition;
}

char field_click_effect(mine_field F, field_position FP, char clickType)
{
if ( F.frontField[ FP.lin ][ FP.col ]==REVEALED && clickType!=MIDDLE_CLICK)
    return NOTHING;

if ( F.backField[ FP.lin ][ FP.col ]==MINE && clickType==LEFT_CLICK )
    return MINE_CLICK;

if (clickType==LEFT_CLICK && F.frontField[ FP.lin ][ FP.col ]==HIDDEN)
    return REVEAL_CLICK;

if (clickType==RIGHT_CLICK && F.frontField[ FP.lin ][ FP.col ]!=FLAGGED)
    return PLACE_FLAG_CLICK;

if (clickType==RIGHT_CLICK && F.frontField[ FP.lin ][ FP.col ]==FLAGGED)
    return REMOVE_FLAG_CLICK;

if (clickType==MIDDLE_CLICK && F.frontField[ FP.lin ][ FP.col ]==REVEALED && F.backField[ FP.lin ][ FP.col ]!=0)
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
    F.frontField[ FP.lin ][ FP.col ]=EXPLODED_MINE;
    push_stack_list(F.graphicalChanges,FP);
    reveal_mines(F);
    mark_false_flags(F);
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
if (F.backField[FP.lin][FP.col]==MINE || F.backField[FP.lin][FP.col]==BORDER || F.frontField[FP.lin][FP.col]==REVEALED)
    return;
F.frontField[FP.lin][FP.col]=REVEALED;
push_stack_list(F.graphicalChanges,FP);
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
bool failed_chord=false;
field_position new_FP;
for (dir=1;dir<=8;dir++)
     if (F.backField[ FP.lin + linDir[dir] ][ FP.col + colDir[dir] ]==MINE &&
         F.frontField[ FP.lin + linDir[dir] ][ FP.col + colDir[dir] ]!=FLAGGED)
        {
         F.frontField[ FP.lin + linDir[dir] ][ FP.col + colDir[dir] ]=EXPLODED_MINE;
         new_FP.lin=FP.lin + linDir[dir];
         new_FP.col=FP.col + colDir[dir];
         push_stack_list(F.graphicalChanges,new_FP);
         failed_chord=true;
        }
if (failed_chord)
    {
    reveal_mines(F);
    mark_false_flags(F);
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
push_stack_list(F.graphicalChanges,flagPosition);
F.frontField[flagPosition.lin][flagPosition.col]=FLAGGED;
return;
}

void remove_flag(mine_field& F, field_position flagPosition)
{
F.nrOfFlags--;
push_stack_list(F.graphicalChanges,flagPosition);
F.frontField[flagPosition.lin][flagPosition.col]=HIDDEN;
}

void reveal_mines(mine_field& F)
{
int i;
for (i=0;i<F.nrOfMines;i++)
     if ( F.frontField[ F.minePositions[i].lin ][ F.minePositions[i].col ]!=EXPLODED_MINE &&
         F.frontField[ F.minePositions[i].lin ][ F.minePositions[i].col ]!=FLAGGED )
        {
        F.frontField[ F.minePositions[i].lin ][ F.minePositions[i].col ]=REVEALED_MINE;
        push_stack_list(F.graphicalChanges,F.minePositions[i]);
        }
return;
}

void mark_false_flags(mine_field& F)
{
int i,j;
field_position FP;
for (i=1;i<=F.nrOfLines;i++)
     for (j=1;j<=F.nrOfColumns;j++)
         if (F.frontField[i][j]==FLAGGED && F.backField[i][j]!=MINE)
             {
              F.frontField[i][j]=FALSE_FLAG;
              FP.lin=i;
              FP.col=j;
              push_stack_list(F.graphicalChanges,FP);
             }
}

void reveal_all(mine_field& F)
{
int i,j;
field_position FP;
for (i=1;i<=F.nrOfLines;i++)
     for (j=1;j<=F.nrOfColumns;j++)
         if (F.frontField[i][j]==HIDDEN)
             {
              F.frontField[i][j]=REVEALED;
              FP.lin=i;
              FP.col=j;
              push_stack_list(F.graphicalChanges,FP);
             }
}

void draw_field(mine_field& F)
{
int i,j;
color_scheme activeCS;
activeCS=load_current_color_scheme();
absolute_point screen_position;
short int field_position_size;
field_position_size=F.fieldBox.height/F.nrOfLines;

setfillstyle(SOLID_FILL, return_rgb_color_code(activeCS.tertiaryColor) );
bar(F.fieldBox.anchorPoint.X,F.fieldBox.anchorPoint.Y,F.fieldBox.anchorPoint.X+F.fieldBox.width,F.fieldBox.anchorPoint.Y+F.fieldBox.height);

set_active_color(activeCS.mainColor);
/*setlinestyle(0,0,3);
line(F.fieldBox.anchorPoint.X, F.fieldBox.anchorPoint.Y, F.fieldBox.anchorPoint.X+F.fieldBox.height, F.fieldBox.anchorPoint.Y);
line(F.fieldBox.anchorPoint.X, F.fieldBox.anchorPoint.Y, F.fieldBox.anchorPoint.X, F.fieldBox.anchorPoint.Y+F.fieldBox.height);
line(F.fieldBox.anchorPoint.X+F.fieldBox.height, F.fieldBox.anchorPoint.Y, F.fieldBox.anchorPoint.X+F.fieldBox.height, F.fieldBox.anchorPoint.Y+F.fieldBox.height);
line(F.fieldBox.anchorPoint.X, F.fieldBox.anchorPoint.Y+F.fieldBox.height, F.fieldBox.anchorPoint.X+F.fieldBox.height, F.fieldBox.anchorPoint.Y+F.fieldBox.height);
*/

draw_field_graphicalChanges(F);
}

void draw_field_graphicalChanges(mine_field& F)
{
int i;
color_scheme activeCS;
activeCS=load_current_color_scheme();
short int currentX,currentY;
absolute_point screenPosition;
field_position currentPosition;
short int field_position_size;
field_position_size=F.fieldBox.height/F.nrOfLines;
while ( F.graphicalChanges!=0 )
        {
         currentPosition=pop_stack_list(F.graphicalChanges);
         screenPosition.X=F.fieldBox.anchorPoint.X+(currentPosition.col-1)*field_position_size;
         screenPosition.Y=F.fieldBox.anchorPoint.Y+(currentPosition.lin-1)*field_position_size;
         draw_field_position(screenPosition,field_position_size,F.backField[currentPosition.lin][currentPosition.col],F.frontField[currentPosition.lin][currentPosition.col]);
        }
set_active_color(activeCS.mainColor);
/*setlinestyle(0,0,3);
line(F.fieldBox.anchorPoint.X, F.fieldBox.anchorPoint.Y, F.fieldBox.anchorPoint.X+F.fieldBox.height, F.fieldBox.anchorPoint.Y);
line(F.fieldBox.anchorPoint.X, F.fieldBox.anchorPoint.Y, F.fieldBox.anchorPoint.X, F.fieldBox.anchorPoint.Y+F.fieldBox.height);
line(F.fieldBox.anchorPoint.X+F.fieldBox.height, F.fieldBox.anchorPoint.Y, F.fieldBox.anchorPoint.X+F.fieldBox.height, F.fieldBox.anchorPoint.Y+F.fieldBox.height);
line(F.fieldBox.anchorPoint.X, F.fieldBox.anchorPoint.Y+F.fieldBox.height, F.fieldBox.anchorPoint.X+F.fieldBox.height, F.fieldBox.anchorPoint.Y+F.fieldBox.height);
*/
setlinestyle(0,0,1);

currentX=F.fieldBox.anchorPoint.X;
currentY=F.fieldBox.anchorPoint.Y;
for (i=1;i<=F.nrOfLines+1;i++)
     {
      line(F.fieldBox.anchorPoint.X,currentY,F.fieldBox.anchorPoint.X+F.fieldBox.width,currentY);
      currentY+=field_position_size;
     }
for (i=1;i<=F.nrOfColumns+1;i++)
    {
    line(currentX,F.fieldBox.anchorPoint.Y,currentX,F.fieldBox.anchorPoint.Y+F.fieldBox.height);
    currentX+=field_position_size;
    }
}

void draw_field_position(absolute_point anchorPoint,short int length, char backfieldCODE, char frontfieldCODE)
{
color_scheme activeCS;
activeCS=load_current_color_scheme();

if (frontfieldCODE==REVEALED)
    {
     if (backfieldCODE==EMPTY)
        {
         set_active_color(activeCS.backgroundColor);
         setfillstyle(SOLID_FILL, return_rgb_color_code(activeCS.backgroundColor) );
         bar(anchorPoint.X,anchorPoint.Y,anchorPoint.X+length,anchorPoint.Y+length);
        }
     if (backfieldCODE==1)
         readimagefile("1.jpg",anchorPoint.X,anchorPoint.Y,anchorPoint.X+length,anchorPoint.Y+length);
     if (backfieldCODE==2)
         readimagefile("2.jpg",anchorPoint.X,anchorPoint.Y,anchorPoint.X+length,anchorPoint.Y+length);
     if (backfieldCODE==3)
         readimagefile("3.jpg",anchorPoint.X,anchorPoint.Y,anchorPoint.X+length,anchorPoint.Y+length);
     if (backfieldCODE==4)
         readimagefile("4.jpg",anchorPoint.X,anchorPoint.Y,anchorPoint.X+length,anchorPoint.Y+length);
     if (backfieldCODE==5)
          readimagefile("5.jpg",anchorPoint.X,anchorPoint.Y,anchorPoint.X+length,anchorPoint.Y+length);
     if (backfieldCODE==6)
          readimagefile("6.jpg",anchorPoint.X,anchorPoint.Y,anchorPoint.X+length,anchorPoint.Y+length);
     if (backfieldCODE==7)
          readimagefile("7.jpg",anchorPoint.X,anchorPoint.Y,anchorPoint.X+length,anchorPoint.Y+length);
     if (backfieldCODE==8)
          readimagefile("8.jpg",anchorPoint.X,anchorPoint.Y,anchorPoint.X+length,anchorPoint.Y+length);
    }
    else
    {
     set_active_color(activeCS.tertiaryColor);
     setfillstyle(SOLID_FILL, return_rgb_color_code(activeCS.tertiaryColor) );
     bar(anchorPoint.X,anchorPoint.Y,anchorPoint.X+length,anchorPoint.Y+length);
     if (frontfieldCODE==HIDDEN)
         return;
     if (frontfieldCODE==FLAGGED)
         readimagefile("flag.jpg",anchorPoint.X,anchorPoint.Y,anchorPoint.X+length,anchorPoint.Y+length);
     if (frontfieldCODE==REVEALED_MINE)
         readimagefile("mine.jpg",anchorPoint.X,anchorPoint.Y,anchorPoint.X+length,anchorPoint.Y+length);
     if (frontfieldCODE==FALSE_FLAG)
         readimagefile("false_flag.jpg",anchorPoint.X,anchorPoint.Y,anchorPoint.X+length,anchorPoint.Y+length);
     if (frontfieldCODE==EXPLODED_MINE)
         readimagefile("exploded_mine.jpg",anchorPoint.X,anchorPoint.Y,anchorPoint.X+length,anchorPoint.Y+length);
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

void push_stack_list(stack_list& SL, field_position FP)
{
nod* p=new nod;
p->inf=FP;
p->next=SL;
SL=p;
}

field_position pop_stack_list(stack_list& SL)
{
nod* p;
field_position FP;
if (SL->next==NULL)
    {
     p=SL;
     FP=p->inf;
     delete p;
     SL=0;
    }
    else
    {
     p=SL;
     FP=p->inf;
     SL=SL->next;
     delete p;
    }

return FP;
}

bool is_empty_stack_list(stack_list SL)
{
return SL==0;
}

