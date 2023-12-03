#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    boardSizeX = 20;
    boardSizeY = 10;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
    boardSizeX = boardX;
    boardSizeY = boardY;
}

// do you need a destructor?


bool GameMechs::getExitFlagStatus()
{
   return exitFlag;
}

char GameMechs::getInput()
{
    if (MacUILib_hasChar())
    {
        input = MacUILib_getChar();
    }
    return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

void GameMechs::generateFood(objPos blockOff)
{
    srand(static_cast<unsigned>(time(nullptr)));

    // Generate a random position for the food, excluding the player position
    do
    {
        foodPos.x = rand() % (boardSizeX - 2) + 1;  // Excluding borders
        foodPos.y = rand() % (boardSizeY - 2) + 1;  // Excluding borders
    } while (foodPos.x == blockOff.x && foodPos.y == blockOff.y);

    foodPos.symbol = '*';  // You can change the symbol as needed
}

void GameMechs::getFoodPos(objPos &returnPos)
{
    returnPos = foodPos;
}