#include "AbsPieces.h"


model::AbsPiece::AbsPiece(const PieceType& typeOfPiece, const Team& team) : team_(team), type_(typeOfPiece) {
    getPiecesOnBoard().push_back(this);
}


model::AbsPiece::~AbsPiece(){
    getPiecesOnBoard().remove(this);
}


bool model::AbsPiece::checkIfPositionInDanger(int pos[2]){
    int currentAttackingPos[2];
    for (auto &&piece : getPiecesOnBoard()){
        for (auto &&attackingPos : piece->attackingPositions_){
            currentAttackingPos[0] = attackingPos.first;
            currentAttackingPos[1] = attackingPos.second;
            if (pos[0] == currentAttackingPos[0] &&
                    pos[1] == currentAttackingPos[1])
                return true;
        }
    }
    return false;
}

list<model::AbsPiece*> &model::AbsPiece::getPiecesOnBoard(){
    static list<AbsPiece*> piecesOnBoard;
    return piecesOnBoard;
}


void model::AbsPiece::addMove(const pair<int, int>& move){
    moves_.push_back(move);
}


void model::AbsPiece::setPosition(int x, int y){
    previousPos_.first = position_.first;
    previousPos_.second = position_.second;
    position_.first = x;
    position_.second = y;
}


void model::AbsPiece::returnPreviousPos(){
    position_.first = previousPos_.first;
    position_.second = previousPos_.second;
}


model::AbsPiece* model::AbsPiece::findPiece(const pair<int, int>& pos){
    for (auto && piece : getPiecesOnBoard()){
        if ((piece->getYPos() == pos.first) && (piece->getXPos() == pos.second)){
            return piece;
        }
    }
    return nullptr;
}


void model::AbsPiece::updateMoves(){
    updatePossibleMoves();
    updateAttackingPos();
}


void model::AbsPiece::updateAttackingPos(){
    attackingPositions_.clear();
    for (auto &&move : moves_){
        pair<int, int> attackedPos = make_pair(getYPos() + move.first,
                                               getXPos() + move.second);
        attackingPositions_.push_back(attackedPos);
    }
}


model::CheckType model::AbsPiece::lookForCheck(const Team& turn){
    pair<int, int> kingPos;
    for (auto &&piece : getPiecesOnBoard()){
        if ( piece->getType() == PieceType::KING && piece->getTeam() == turn){
            kingPos.first = piece->getYPos();
            kingPos.second = piece->getXPos();
            for (auto &&attackingPiece : getPiecesOnBoard()){
                for (auto &&dangerousPos : attackingPiece->attackingPositions_){
                    if ( kingPos == dangerousPos){
                        if (piece->getTeam() != attackingPiece->getTeam())
                            return CheckType::CHECK;
                    }
                }
            }
        }
    }
    return CheckType::NONE;
}
