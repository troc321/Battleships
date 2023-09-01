/**
 * @author Stefan Brandle, Jonathan Geisler
 * @date September, 2004
 *
 * Please type in your name[s] here if you change the code:
 * Esther Brandle, Trent Repass
 */

#ifndef BATTLEPEARL_H// Double inclusion protection
#define BATTLEPEARL_H

using namespace std;

#include "PlayerV2.h"
#include "Message.h"
#include "defines.h"

class BattlePearl: public PlayerV2 {
  public:
    BattlePearl( int boardSize );
    ~BattlePearl();
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
    void findInitProb();
    int vWeight(int row, int col);
    int hWeight(int row, int col);

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
    int probBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
};

#endif
