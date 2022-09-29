#include "rook.h"

Rook::Rook(const model::Team& pieceTeam) : AbsPiece(model::PieceType::ROOK, pieceTeam)
{
}


void Rook::updatePossibleMoves(){
    moves_.clear();
    int i = 1;
    AbsPiece* pieceNextPos;
    while (getYPos() + i < 8){
        pieceNextPos = findPiece(make_pair(getYPos() + i, getXPos()));
        if (pieceNextPos != nullptr){
            if (pieceNextPos->getTeam() != team_)
                addMove(make_pair(i, 0));
            break;
        }
        addMove(make_pair(i, 0));
        i++;
    }
    i = 1;
    while (getYPos() - i >= 0){
        pieceNextPos = findPiece(make_pair(getYPos() - i, getXPos()));
        if (pieceNextPos != nullptr){
            if (pieceNextPos->getTeam() != team_)
                addMove(make_pair(-i, 0));
            break;
        }
        addMove(make_pair(-i, 0));
        i++;
    }
    i = 1;
    while (getXPos() + i < 8){
        pieceNextPos = findPiece(make_pair(getYPos(), getXPos() + i));
        if (pieceNextPos != nullptr){
            if (pieceNextPos->getTeam() != team_)
                addMove(make_pair(0, i));
            break;
        }
        addMove(make_pair(0, i));
        i++;
    }
    i = 1;
    while (getXPos() - i >= 0){
        pieceNextPos = findPiece(make_pair(getYPos(), getXPos() - i));
        if (pieceNextPos != nullptr){
            if (pieceNextPos->getTeam() != team_)
                addMove(make_pair(0, -i));
            break;
        }
        addMove(make_pair(0, -i));
        i++;
    }
}
