#ifndef GAME_H
#define GAME_H
#include "chessboard.h"
#include "king.h"
#include "knight.h"
#include "rook.h"

const int MAX_ASCII_DIGIT = 57;
const int MIN_ASCII_DIGIT = 50;
const int MIN_ASCII_CAPITAL_LETTER = 65;
const int MAX_ASCII_CAPITAL_LETTER = 90;
const int MIN_ASCII_MINUSCULE_LETTER = 97;
const int MAX_ASCII_MINUSCULE_LETTER = 122;
const int ASCII_TO_DIGIT = 48;
const int MAX_N_KINGS = 2;


namespace model{

    class Checkmate : std::exception{
    public:
        Checkmate(const Team& losingTeam) : side(losingTeam) {}
        Team getLoser() { return side; }
        const char* what () const throw () {
            if (side == Team::BLACK)
                return "The black king has fallen, WHITE WINS! \nThis game is finished";
            else
                return "The white king has fallen, black WINS! \nThis game is finished";
        }
    private:
        Team side;
    };


    class Stalemate : std::exception {
    public:
        const char* what () const throw () {
                return "Stalemate, nobody won \nThis game is finished";
        }
    };

    class TooManyKings : std::exception {
    public:
        const char* what () const throw () {
                return "There are too many kings!";
        }
    };


    class Game
    {
    public:
        Game();
        ~Game();

        const Team& getTurn();
        void eraseAllPieces();
        void addPieceToBoard(PieceType type, Team color, int position[2]);
        void movePiece(AbsPiece* piece, int newPos[2]);
        model::AbsPiece* findPiece(int pos[2]);

        bool checkIsValidMove(model::AbsPiece* piece, int nextPos[2]);
        void changeBoardLayout(const string& fenString);

    private:
        model::ChessBoard board_;
        int nKings_ = 0;

        void initChessPieces();
        void addPieceWithType(char character, int currentPos[2]);
        void setPiecePos(model::AbsPiece* piece, int pos[2]);
        void setPiecePreviousPos(model::AbsPiece* piece);
        bool checkIfPossibleMove(AbsPiece* piece, int nextPos[2]);
        void updatePiecesMoves();
        int getNbValidMoves(const Team& side);
        CheckType checkIfEndOfGame();
        void updateNKings();
    };
}

#endif // GAME_H
