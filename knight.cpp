#include "knight.h"

Knight::Knight(const model::Team& pieceTeam) : AbsPiece(model::PieceType::KNIGHT, pieceTeam)
{
    addMove(make_pair(2, 1));
    addMove(make_pair(1, 2));
    addMove(make_pair(-2, 1));
    addMove(make_pair(-1, 2));
    addMove(make_pair(2, -1));
    addMove(make_pair(1, -2));
    addMove(make_pair(-2, -1));
    addMove(make_pair(-1, -2));
}

void Knight::updatePossibleMoves(){}
