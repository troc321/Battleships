/**
 * @author Stefan Brandle, Jonathan Geisler
 * @date September, 2004
 *
 * Please type in your name[s] here if you change the code:
 * Esther Brandle, Trent Repass
 */

#ifndef BLACKPEARL_H// Double inclusion protection
#define BLACKPEARL_H

using namespace std;

#include "PlayerV2.h"
#include "Message.h"
#include "defines.h"

// DumbPlayer inherits from/extends PlayerV2

class BlackPearl: public PlayerV2 {
  public:
    BlackPearl( int boardSize );
    ~BlackPearl();
    void newRound();
    Message placeShip(int length);
    Message getMove();
    void update(Message msg);
    bool placeOk(int row, int col, Direction dir, int len);
    void markShip(int row, int col, Direction dir, int len);
    void sinkShip(int scanRow, int scanCol, int& shotRow, int& shotCol);
    bool sinkShipN(int scanRow, int scanCol, int& shotRow, int& shotCol);
    bool sinkShipS(int scanRow, int scanCol, int& shotRow, int& shotCol);
    bool sinkShipE(int scanRow, int scanCol, int& shotRow, int& shotCol);
    bool sinkShipW(int scanRow, int scanCol, int& shotRow, int& shotCol);
    void findShot(int& scanRow, int& scanCol);

  private:
    void initializeBoard();
    int shotRow;
    int shotCol;
    int scanRow;
    int scanCol;
    bool firstShot;
    int numShipsPlaced;
    char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    char myShips[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
};

#endif
