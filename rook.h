#ifndef ROOK_H
#define ROOK_H
#include "AbsPieces.h"


class Rook : public model::AbsPiece
{
public:
    Rook(const model::Team& pieceTeam);
    virtual void updatePossibleMoves() override;
};

#endif // ROOK_H
