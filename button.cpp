#include "button.h"
#include <cstring>

button create_button(relative_point rAnchorPoint,relative_rectangle rButtonBox, char content[], char function_code)
{
button newButton;

newButton.buttonAnchorPoint=rAnchorPoint;
newButton.buttonBox=rButtonBox;
strcpy(newButton.text, content);
newButton.buttonFunction=function_code;

return newButton;
}

bool isButtonPressed(button B, absolute_point mouseClick)
{
absolute_rectangle hitBoxB;
hitBoxB=relative_to_absolute_rectangle(B.buttonBox);
if ( mouseClick.X>=hitBoxB.anchorPont.X && mouseClick.X<=hitBoxB.anchorPont.X+hitBoxB.width &&
     mouseClick.Y>=hitBoxB.anchorPont.Y && mouseClick.Y<=hitBoxB.anchorPont.Y+hitBoxB.height)
    return true;
return false;
}

void pressButton(button B)
{

}

