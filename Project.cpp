#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"


using namespace std;

#define DELAY_CONST 100000

Player* myplayer;
GameMechs* myGM;
objPos myPos;


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myGM = new GameMechs(30, 10);
    myplayer = new Player(myGM);
}

void GetInput(void)
{
    myGM->getInput();
    if (MacUILib_hasChar()) {
        myGM->setInput(MacUILib_getChar());
    }
}

void RunLogic(void)
{
    if (myGM->getInput() != 0)  // if not null character
    {

        if (myGM->getInput() == 27) {
            myGM->setExitTrue();
        } else {
            myplayer->updatePlayerDir();
        }
        myGM->clearInput();
    }

    myplayer->movePlayer();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    bool drawn;

    objPosArrayList* playerBody = myplayer->getPlayerPos();
    objPos tempBody;

    for(int i = 0; i < myGM->getBoardSizeY(); i++)
    {
        for (int j = 0; j < myGM->getBoardSizeX(); j++)
        {
            drawn = false;
            int isBorder = (i == 0 || i == myGM->getBoardSizeY() - 1 || j == 0 || j == myGM->getBoardSizeX() - 1);
            for (int k = 0; k < playerBody->getSize(); k++)
            {
                playerBody->getElement(tempBody, k);
                if (tempBody.x == j && tempBody.y == i)
                {
                    MacUILib_printf("%c", tempBody.symbol);
                    drawn = true;
                    break;
                }
            }

            if(drawn) continue;
            if (isBorder) 
            {
                MacUILib_printf("#");
            } 
            
            else 
            {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    }
    
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
  
    MacUILib_uninit();

    delete myGM;
    delete myplayer;
}
