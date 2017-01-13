#include "game_time.h"
#include <cstring>

void reset_game_time(game_time& GT)
{
GT.seconds=0;
GT.minutes=0;
}

void add_seconds(game_time& GT, int nrSec)
{
GT.seconds+=nrSec;
GT.minutes+=(GT.seconds)/60;
GT.seconds=GT.seconds%60;
}

char* game_time_as_string(game_time GT)
{
char sir[10];
strcpy(sir, convert_nr_to_char(GT.minutes));

if (strlen(sir)==1)
    {
    sir[1]=sir[0];
    sir[0]='0';
    sir[2]=0;
    }

strcat(sir,":");
strcat(sir, convert_nr_to_char(GT.seconds));

if (strlen(sir)==4)
    {
     sir[4]=sir[3];
     sir[3]='0';
     sir[5]=0;
    }

return sir;
}

char* convert_nr_to_char(short int nr)
{
int poz=0,i, starting_pos=0;
char sir[10];
short int cnr=nr;

if (nr==0)
    {
     sir[0]='0';
     sir[1]=0;
     return sir;
    }

if (nr<0)
    {
     sir[0]='-';
     poz=starting_pos=1;
    }

while (nr!=0)
    {
    if (nr%10>0)
        sir[poz++]=nr%10+'0';
        else
        sir[poz++]=-nr%10+'0';
     nr/=10;
    }
if (poz==1)
    {
    sir[poz]=0;
    return sir;
    }

if (cnr>0)
    for (i=starting_pos;i<poz/2;i++)
        {
        sir[i]=sir[i]^sir[poz-i-1];
        sir[poz-i-1]=sir[i]^sir[poz-i-1];
        sir[i]=sir[i]^sir[poz-i-1];
        }
    else
    for (i=starting_pos;i<(poz+1)/2;i++)
        {
        sir[i]=sir[i]^sir[poz-i];
        sir[poz-i]=sir[i]^sir[poz-i];
        sir[i]=sir[i]^sir[poz-i];
        }

sir[poz]=0;
return sir;
}

