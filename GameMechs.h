#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;


class GameMechs
{
    private:
        char input;
        bool exitFlag;
        bool loseFlag;
        int score;
        
        int boardSizeX;
        int boardSizeY;

        objPos foodPos;
        objPos specialFood;   
        int specialFoodEffect;  
        objPosArrayList foodPosList;

    public:
        GameMechs();
        GameMechs(int boardX, int boardY);
        
        bool getExitFlagStatus();
        void setExitTrue();

        bool getLoseFlagStatus();
        void setLoseFlag();

        char getInput();
        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX();
        int getBoardSizeY();
        
        void generateFood(objPos blockOff);
        void getFoodPos(objPos &returnPos);
        
        int getScore();
        void incrementScore();
};

#endif