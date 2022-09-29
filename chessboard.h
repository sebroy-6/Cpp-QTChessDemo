#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "AbsPieces.h"

const int N_COLUMNS = 8;
const int N_ROWS = 8;

using namespace std;

namespace model {

    class ChessBoard
    {
    public:
        ChessBoard();
        ~ChessBoard();

        const string& getInitPositions();
        const Team& getTurn();
        void switchTurn();
        void changeTurn(const Team& nextTurn);
        void changeFenString(const string& newFenString);

        static bool checkIfIsPositionOnBoard(int pos[2]);

    private:
        Team turn_ = Team::WHITE;
        string initPositions_ = ""; // using the Forsyth-Edwards notation (FEN)
    };
}

#endif // CHESSBOARD_H
