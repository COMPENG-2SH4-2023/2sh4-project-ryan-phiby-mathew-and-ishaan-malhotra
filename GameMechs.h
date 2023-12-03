#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;


class GameMechs
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

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
        //objPosArrayList regularFoods;
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

        //int getRegularFoodCount();
        //void getRegularFoodPos(objPos& returnPos, int index);
        //bool hasSpecialFood();
        //void getSpecialFoodPos(objPos& returnPos);
        
        void generateFood(objPos blockOff);
        //void generateFood(objPosArrayList& snakeBody);
        void getFoodPos(objPos &returnPos);
        
        //void updateGameState();
        //void generateRegularFood();
        //void generateSpecialFood();

        int getScore();
        void incrementScore();
};

#endif