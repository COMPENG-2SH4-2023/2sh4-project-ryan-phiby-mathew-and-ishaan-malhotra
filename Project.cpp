#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"


using namespace std;

#define DELAY_CONST 100000

// Creating Global references to access each class

Player* myplayer;
GameMechs* myGM;

// Routine Prototypes

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);


// Main
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
  
    myGM = new GameMechs(30, 10);  // initializing game board

    myplayer = new Player(myGM);   //initializing player

    // Pass the head element to generateFood
    objPos headElement;
    myplayer->getPlayerPos()->getHeadElement(headElement);
    myGM->generateFood(headElement);
}


void GetInput(void)
{
    myGM->getInput(); //Accessing the getInput function in the GameMechanics file
    if (MacUILib_hasChar()) {
        myGM->setInput(MacUILib_getChar());
    }
}

void RunLogic(void)
{
    if (myGM->getInput() != 0)  // if not null character
    {
        if (myGM->getInput() == 27) // Exit conditon is ESC
        {
            myGM->setExitTrue();
        } 
        else 
        {
            myplayer->updatePlayerDir();
        }
        myGM->clearInput();
    }

    myplayer->movePlayer();

    // Get the head position from the player's position list
    objPosArrayList* playerBody = myplayer->getPlayerPos();
    objPos headPos;
    playerBody->getHeadElement(headPos);

    // Check if the head position matches the food position (collision detection)
    objPos foodPos;
    myGM->getFoodPos(foodPos);

    if (headPos.x == foodPos.x && headPos.y == foodPos.y)
    {
        // Handle collision with food (increase score and snake size, generate new food)
        myGM->generateFood(headPos);
        myGM->incrementScore();
        playerBody->insertHead(headPos);
    }
    
    
}



void DrawScreen(void)
{
    
    MacUILib_clearScreen();
    bool drawn;  // drawing flag

    objPosArrayList* playerBody = myplayer->getPlayerPos();  // initializing objPos list
    objPos tempBody;

    // Get the food position
    objPos foodPos;
    myGM->getFoodPos(foodPos);

    for(int i = 0; i < myGM->getBoardSizeY(); i++)
    {
        for (int j = 0; j < myGM->getBoardSizeX(); j++)
        {
            drawn = false;
            // initializing isBorder variable for border printing
            int isBorder = (i == 0 || i == myGM->getBoardSizeY() - 1 || j == 0 || j == myGM->getBoardSizeX() - 1);

            // Check if the current position matches the food position
            if (foodPos.x == j && foodPos.y == i)
            {
                MacUILib_printf("%c", foodPos.symbol);  // printf symbol over food
                drawn = true;                           // set flag t true to prevent further printing
            }

            // Check if the current position matches any part of the player's body
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

            // If no food or player body, print the border or empty space
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
    playerBody->getHeadElement(tempBody);

    // Display Score
    MacUILib_printf("Score: %d\n", myGM->getScore());
}


void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    // Check if the player lost but eating into body
    if (myGM->getLoseFlagStatus() == true && myGM->getExitFlagStatus() == true) {
        MacUILib_printf("You Lose! You Scored: %d", myGM->getScore());
    }
    else
    {
        MacUILib_printf("Game Ended. You Scored: %d", myGM->getScore());
    }
    MacUILib_uninit();

    delete myGM;
    delete myplayer;
}
