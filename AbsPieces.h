#ifndef ABSPIECES_H
#define ABSPIECES_H
#include <string>
#include <iostream>
#include <utility>
#include <vector>
#include <list>
using namespace std;

namespace model{
    enum class Team {
        WHITE,
        BLACK
    };


    enum class PieceType {
        KING,
        ROOK,
        KNIGHT
    };


    enum class CheckType {
        NONE,
        CHECK,
        CHECKMATE,
        STALEMATE
    };


    class AbsPiece{
    public:
        virtual ~AbsPiece();

        const Team& getTeam() { return team_; };
        const PieceType& getType() { return type_; };

        int getXPos() { return position_.second; };
        int getYPos() { return position_.first; };

        const pair<int, int>& getMove(int index) { return moves_[index]; };
        int getNPossibleMoves() {return moves_.size(); };

        static list<AbsPiece*>& getPiecesOnBoard();
        static AbsPiece* findPiece(const pair<int, int>& pos);
        static bool checkIfPositionInDanger(int pos[2]);

        void addMove(const pair<int, int>& move);
        void setPosition(int x, int y);
        void returnPreviousPos();

        virtual void updateMoves();
        virtual void updatePossibleMoves() = 0;
        virtual void updateAttackingPos();
        static CheckType lookForCheck(const Team& turn);

    protected:
        AbsPiece(const PieceType& typeOfPiece, const Team& team);

        const Team team_;
        const PieceType type_;
        pair<int, int> position_ = {0, 0};               // {X, Y}
        pair<int, int> previousPos_ = {0, 0};            // {X, Y}
        vector<pair<int, int>> moves_ = {};              // {X, Y}
        vector<pair<int, int>> attackingPositions_ = {}; // {X, Y}
    };
}


#endif // ABSPIECES_H
