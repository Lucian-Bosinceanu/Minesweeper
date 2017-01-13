#include "gamestate.h"
#include <cstring>
#include <fstream>

using namespace std;

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

void load_highscore(highscore& HS)
{
int i,tabs;
char nume[MAX_PLAYER_NAME];
ifstream fin("highscores.txt");
for (tabs=0;tabs<=2;tabs++)
    {
    fin>>HS.highscore_pages[tabs].nr_of_entries; fin.get();
    for (i=0;i<HS.highscore_pages[tabs].nr_of_entries;i++)
        {
         fin.getline(nume,MAX_PLAYER_NAME);
         strcpy(HS.highscore_pages[tabs].entries[i].player_name,nume);
         fin>>HS.highscore_pages[tabs].entries[i].player_time.minutes;
         fin>>HS.highscore_pages[tabs].entries[i].player_time.seconds;
        }
    }
fin.close();
}

void save_highscore(highscore HS)
{
int i,tabs;
ofstream fout("highscores.txt");
for (tabs=0;tabs<=2;tabs++)
    {
    fout<<HS.highscore_pages[tabs].nr_of_entries<<'\n';
    for (i=0;i<HS.highscore_pages[tabs].nr_of_entries;i++)
        {
         //fin.getline(nume,MAX_PLAYER_NAME);
         //strcpy(HS.highscore_pages[tabs].entries[i].player_name,nume);
         fout<<HS.highscore_pages[tabs].entries[i].player_name<<'\n';
         fout<<HS.highscore_pages[tabs].entries[i].player_time.minutes<<' ';
         fout<<HS.highscore_pages[tabs].entries[i].player_time.seconds<<'\n';
        }
    }
fout.close();
}

bool check_if_is_a_highscore(highscore HS, char difficultyCode, game_time scoredTime)
{
int i;
short int scoredTimeSec=scoredTime.minutes*60+scoredTime.seconds;
short int currentTime;
if (HS.highscore_pages[difficultyCode-1].nr_of_entries==0)
    return true;
for (i=HS.highscore_pages[difficultyCode-1].nr_of_entries;i>=0;i--)
    {
     currentTime=HS.highscore_pages[difficultyCode-1].entries[i].player_time.minutes*60+HS.highscore_pages[difficultyCode-1].entries[i].player_time.seconds;
     if (scoredTimeSec<currentTime)
         return true;
    }
return false;
}

void add_highscore_entry(highscore& HS, char difficultyCode, game_time scoredTime)
{
int i,j;
char name[MAX_PLAYER_NAME];
ifstream fin("player_name.txt");
short int scoredTimeSec=scoredTime.minutes*60+scoredTime.seconds;
short int currentTime;

fin.getline(name,MAX_PLAYER_NAME);

if (HS.highscore_pages[difficultyCode-1].nr_of_entries==0)
    {
     HS.highscore_pages[difficultyCode-1].nr_of_entries=1;
     strcpy(HS.highscore_pages[difficultyCode-1].entries[0].player_name,name);
     HS.highscore_pages[difficultyCode-1].entries[0].player_time=scoredTime;
    }
    else
    {
    ++HS.highscore_pages[difficultyCode-1].nr_of_entries;
    for (i=HS.highscore_pages[difficultyCode-1].nr_of_entries-1;i>=0;i--)
        {
         currentTime=HS.highscore_pages[difficultyCode-1].entries[i].player_time.minutes*60+HS.highscore_pages[difficultyCode-1].entries[i].player_time.seconds;
         if (scoredTimeSec<currentTime)
             {
              for (j=HS.highscore_pages[difficultyCode-1].nr_of_entries;j>i;j--)
                   HS.highscore_pages[difficultyCode-1].entries[j]=HS.highscore_pages[difficultyCode-1].entries[j-1];

              strcpy(HS.highscore_pages[difficultyCode-1].entries[i].player_name,name);
              HS.highscore_pages[difficultyCode-1].entries[i].player_time=scoredTime;
             }
        }
    }
fin.close();
}

void draw_high_score_tab(highscore_tab HT)
{

}
