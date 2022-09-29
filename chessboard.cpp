#include "chessboard.h"


model::ChessBoard::ChessBoard(){
}


model::ChessBoard::~ChessBoard(){
}


const string& model::ChessBoard::getInitPositions(){
    return initPositions_;
}


const model::Team& model::ChessBoard::getTurn(){
    return turn_;
}


void model::ChessBoard::switchTurn(){
    if (turn_ == Team::WHITE)
        turn_ = Team::BLACK;
    else
        turn_ = Team::WHITE;
}


void model::ChessBoard::changeTurn(const Team& nextTurn){
    turn_ = nextTurn;
}


bool model::ChessBoard::checkIfIsPositionOnBoard(int pos[2]) {
    return (0 <= pos[0] && pos[0] < N_COLUMNS) && (0 <= pos[1] && pos[1] < N_ROWS) ;
}


void model::ChessBoard::changeFenString(const string& newFenString) {
    initPositions_ = newFenString;
}
