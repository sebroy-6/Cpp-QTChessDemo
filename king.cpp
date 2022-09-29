#include "king.h"

King::King(const model::Team& pieceTeam) : AbsPiece(model::PieceType::KING, pieceTeam)
{
    moves_.push_back(make_pair(1, 0));
    moves_.push_back(make_pair(0, 1));
    moves_.push_back(make_pair(1, 1));
    moves_.push_back(make_pair(-1, 0));
    moves_.push_back(make_pair(0, -1));
    moves_.push_back(make_pair(-1, -1));
    moves_.push_back(make_pair(1, -1));
    moves_.push_back(make_pair(-1, 1));
}


void King::updatePossibleMoves(){}
