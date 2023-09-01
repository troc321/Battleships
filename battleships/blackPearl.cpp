/**
 * @brief blackPearl AI for battleships
 * @file blackPearl.cpp
 * @author Trent Repass, Esther Brandle
 * @date September, 2004 Updated 2015 for multi-round play.
 *
 * This Battleships AI is very simple and does nothing beyond playing
 * a legal game. However, that makes it a good starting point for writing
 * a more sophisticated AI.
 */

#include <iostream>
#include <cstdio>

#include "blackPearl.h"

/**
 * @brief Constructor that initializes any inter-round data structures.
 * @param boardSize Indication of the size of the board that is in use.
 *
 * The constructor runs when the AI is instantiated (the object gets created)
 * and is responsible for initializing everything that needs to be initialized
 * before any of the rounds happen. The constructor does not get called 
 * before rounds; newRound() gets called before every round.
 */

BlackPearl::BlackPearl( int boardSize )
    :PlayerV2(boardSize)
{
    // Could do any initialization of inter-round data structures here.
}

/**
 * @brief Destructor placeholder.
 * If your code does anything that requires cleanup when the object is
 * destroyed, do it here in the destructor.
 */
BlackPearl::~BlackPearl( ) {}

/*
 * Private internal function that initializes a MAX_BOARD_SIZE 2D array of char to water.
 */
void BlackPearl::initializeBoard() {
    for(int row=0; row<boardSize; row++) {
        for(int col=0; col<boardSize; col++) {
            this->board[row][col] = WATER;
            this->myShips[row][col] = WATER;
        }
    }
}

void BlackPearl::markShip(int row, int col, Direction dir, int len){
    if(dir == Horizontal){
        for(int c = col; c < len+col; c++){
            this->myShips[row][c] = SHIP;
        }
    } else {
        for(int r = row; r < len+row; r++){
            this->myShips[r][col] = SHIP;
        }   
    }
}   

/**
 * @brief Specifies the AI's shot choice and returns the information to the caller.
 * @return Message The most important parts of the returned message are 
 * the row and column values. 
 *
 * See the Message class documentation for more information on the 
 * Message constructor.
 */
Message BlackPearl::getMove() {
    if(firstShot==true){
        initializeBoard();
        shotRow = 0;
        shotCol = 2;
        scanRow = shotRow;
        scanCol = shotCol;
        firstShot = false;
    } else if(board[scanRow][scanCol] == HIT){
        sinkShip(scanRow, scanCol, shotRow, shotCol);
    }
    else{
        while(board[scanRow][scanCol] != WATER){
            shotRow = scanRow;
            shotCol = scanCol;
            if(scanCol+3<boardSize){
                scanCol+=3;
                shotCol=scanCol;
            }else{
                shotRow++;
                scanRow=shotRow;
                if(boardSize%3!=0){
                    shotCol=shotCol+3-boardSize;
                    scanCol=shotCol;
                }else{
                    shotCol=shotCol+2-boardSize;
                    if(shotCol==-1) shotCol=2;
                    scanCol=shotCol;
                }
            }
        }
    }
    Message result( SHOT, shotRow, shotCol, "", None, 1 );
    return result;
}

void BlackPearl::sinkShip(int scanRow, int scanCol, int& shotRow, int& shotCol){
    if(sinkShipN(scanRow, scanCol, shotRow, shotCol)) return;
    else if(sinkShipS(scanRow, scanCol, shotRow, shotCol)) return;
    else if(sinkShipE(scanRow, scanCol, shotRow, shotCol)) return;
    else if(sinkShipW(scanRow, scanCol, shotRow, shotCol)) return;
    else return;
}

bool BlackPearl::sinkShipN(int scanRow, int scanCol, int& shotRow, int& shotCol){
    //North
    for(int r = scanRow-1; r >= 0; r--){
        switch(board[r][scanCol]){
            case WATER:
                shotRow = r;
                shotCol = scanCol;
                return true;
            case HIT:
                break;
            case KILL:
            case MISS:
                return false;
        }
    }
    return false;
}

bool BlackPearl::sinkShipS(int scanRow, int scanCol, int& shotRow, int& shotCol){
    //South
    for(int r = scanRow+1; r < boardSize; r++){
        switch(board[r][scanCol]){
            case WATER:
                shotRow = r;
                shotCol = scanCol;
                return true;
            case HIT:
                break;
            case KILL:
            case MISS:
                return false;
        }
    }
    return false;
}

bool BlackPearl::sinkShipE(int scanRow, int scanCol, int& shotRow, int& shotCol){
    //East
    for(int c = scanCol+1; c < boardSize ; c++){
        switch(board[scanRow][c]){
            case WATER:
                shotCol = c;
                shotRow = scanRow;
                return true;
            case HIT:
                break;
            case KILL:
            case MISS:
                return false;
        }
    }
    return false;
}

bool BlackPearl::sinkShipW(int scanRow, int scanCol, int& shotRow, int& shotCol){
    //West
    for(int c = scanCol-1; c >= 0; c--){
        switch(board[scanRow][c]){
            case WATER:
                shotCol = c;
                shotRow = scanRow;
                return true;
            case HIT:
                break;
            case KILL:
            case MISS:
                return false;
        }
    }
    return false;
}

/**
 * @brief Tells the AI that a new round is beginning.
 * The AI show reinitialize any intra-round data structures.
 */
void BlackPearl::newRound() {
    /* Smarter players 
     * reinitialize any round-specific data structures here.
     */
    firstShot = true;
    this->shotRow = 0;
    this->shotCol = -1;
    this->numShipsPlaced = 0;

    this->initializeBoard();
}

/**
 * @brief Checks to see if a given ship can be placed on 
 * the game board legally.
 * @returns a boolean that determines if a ship has a legal 
 * placement.
 */
bool BlackPearl::placeOk(int row,int col,Direction dir,int len) {
    if (dir == Horizontal) {
        if (row < 0 or row >= boardSize) return false;
        if (col < 0 or col+len > boardSize) return false;
        for (int c = col; c < col+len; c++) {
            if (myShips[row][c] == SHIP) return false;
        }
    } else {
            if (col < 0 or col >= boardSize) return false;
            if (row < 0 or row+len > boardSize) return false;
            for (int r = row; r < row+len; r++) {
                if (myShips[r][col] == SHIP) return false;
        }
    }
    return true;
}

/**
 * @brief Gets the AI's ship placement choice. This is then returned to the caller.
 * @param length The length of the ship to be placed.
 * @return Message The most important parts of the returned message are 
 * the direction, row, and column values. 
 *
 * The parameters returned via the message are:
 * 1. the operation: must be PLACE_SHIP 
 * 2. ship top row value
 * 3. ship top col value
 * 4. a string for the ship name
 * 5. direction Horizontal/Vertical (see defines.h)
 * 6. ship length (should match the length passed to placeShip)
 */
Message BlackPearl::placeShip(int length) {
    char shipName[10];
    snprintf(shipName, sizeof shipName, "Ship%d", numShipsPlaced);
    int row = -1;
    int col = -1;
    Direction dir = Vertical;
    if(numShipsPlaced == 0){
        row = boardSize - 1;
        col = 1;
        dir = Horizontal;
        numShipsPlaced++;
    } else{
        while(placeOk(row, col, dir, length)==false){
            row = rand()%boardSize;
            col = rand()%boardSize;
            dir = Direction(rand()%2+1);
            for(int i = row; i<=length+row; i++){
                if(i + 1 <= boardSize-1 && myShips[i+1][col] == SHIP){
                     row = rand()%boardSize;
                     col = rand()%boardSize;
                     continue;
                } else if(i - 1 >= 1 && myShips[i-1][col] == SHIP){
                    row = rand()%boardSize;
                    col = rand()%boardSize;
                    continue;
                }
            }
            for(int c = col; c<=length+col; c++){
                if(c + 1 <= boardSize-1 && myShips[row][c+1]) {
                    continue;
                } else if(c - 1 >= 1 && myShips[row][c-1]){
                    continue;
                }
            }

            if(dir == Horizontal){
                if(row <= 2 || row >= boardSize - 2){
                    continue;
                }
            } else if(dir == Vertical){
                if(col <= 2 || col >= boardSize - 2){
                    continue;
                }
            }
            row = rand()%boardSize;
            col = rand()%boardSize;
        }
    }
    numShipsPlaced++;
    markShip(row, col, dir, length);
    Message ship(PLACE_SHIP, row, col,"", dir, length);
    return ship;
}              

/**
 * @brief Updates the AI with the results of its shots and where the opponent is shooting.
 * @param msg Message specifying what happened + row/col as appropriate.
 */
void BlackPearl::update(Message msg) {
    switch(msg.getMessageType()) {
        case HIT:
        case KILL:
        case MISS:
            board[msg.getRow()][msg.getCol()] = msg.getMessageType();
            break;
        case WIN:
            break;
        case LOSE:
            break;
        case TIE:
            break;
        case OPPONENT_SHOT:
            // TODO: replace in your AI with code that does something useful with the information about where the opponent is shooting.
            break;
    }
}
