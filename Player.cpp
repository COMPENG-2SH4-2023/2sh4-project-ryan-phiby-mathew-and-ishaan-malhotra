#include "Player.h"

objPos playerPos;
objPosArrayList* playerPosList;

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    //playerPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, 'X');
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, 'X');
    
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);

    //for debugging inserting another 4 segments

}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    char input = mainGameMechsRef->getInput();

    switch(input)
    {
        case 'W':
        case 'w':
            if (myDir != DOWN) {
                myDir = UP;
            }
            break;

        case 'A':
        case 'a':
            if (myDir != RIGHT) {
                myDir = LEFT;
            }
            break;

        case 'D':
        case 'd':
            if (myDir != LEFT) {
                myDir = RIGHT;
            }
            break;
        
        case 'S':
        case 's':
            if (myDir != UP) {
                myDir = DOWN;
            }
            break;
        case 27:
            mainGameMechsRef->setExitTrue();
        default:
            break;
    }   
    input = 0;
    
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    objPos currHead;
    playerPosList->getHeadElement(currHead);

    switch (myDir)
    {
        case LEFT:
            currHead.x--;
            if (currHead.x <= 0) {
                currHead.x = mainGameMechsRef->getBoardSizeX() - 2;
            }
            break;
        case RIGHT:
            currHead.x++;
            if (currHead.x >= mainGameMechsRef->getBoardSizeX() - 2) {
                currHead.x = 1;
            }
            break;
        case UP:
            currHead.y--;
            if (currHead.y == 0) {
                currHead.y = mainGameMechsRef->getBoardSizeY() - 2;
            }
            break;
        case DOWN:
            currHead.y++;
            if (currHead.y == mainGameMechsRef->getBoardSizeY() - 1) {
                currHead.y = 1;
            }
            break;
        case STOP:
        default:
            break;
    }

    // Check for self-collision
    for (int i = 1; i < playerPosList->getSize(); i++)
    {
        objPos bodyPart;
        playerPosList->getElement(bodyPart, i);
        if (currHead.x == bodyPart.x && currHead.y == bodyPart.y)
        {
            // Snake collided with itself
            mainGameMechsRef->setLoseFlag();
            return;
        }
    }

    playerPosList->insertHead(currHead);
    playerPosList->removeTail();
}
