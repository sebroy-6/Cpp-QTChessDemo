#ifndef KNIGHT_H
#define KNIGHT_H
#include "AbsPieces.h"


class Knight : public model::AbsPiece
{
public:
    Knight(const model::Team& pieceTeam);
    virtual void updatePossibleMoves() override;
};

#endif // KNIGHT_H
