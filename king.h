#ifndef KING_H
#define KING_H
#include "AbsPieces.h"


class King : public model::AbsPiece
{
public:
    King(const model::Team& pieceTeam);
    virtual void updatePossibleMoves() override;
};

#endif // KING_H
