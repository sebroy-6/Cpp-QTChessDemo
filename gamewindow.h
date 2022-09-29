#ifndef CHESSBOARDWINDOW_H
#define CHESSBOARDWINDOW_H
#include <QGridLayout>
#include <QPixmap>
#include <QString>
#include <QApplication>
#include "game.h"
#include "boardsquarewindow.h"

using namespace std;

// The "non-POD" warnings can be ignored here since they exist to prevent the
// app from initialising const variables that may not be used afterwards.
// In our case, every const variable is used so the warning is not relevant here.

const QString SHOW_MOVE_COLOR = "border: 3px solid darkgrey";
const QString SHOW_ERROR_COLOR = "border: 2px solid red";
const QString SHOW_WINNING_COLOR = "border: 10px solid gold";

const QString LIGHT_SQUARE_COLOR = "background-color: beige;";
const QString DARK_SQUARE_COLOR = "background-color: #355E3B;";

const QString WK_IMAGE = ":/img/images/WhiteKing.png";
const QString WN_IMAGE = ":/img/images/WhiteKnight.png";
const QString WR_IMAGE = ":/img/images/WhiteRook.png";
const QString BK_IMAGE = ":/img/images/BlackKing.png";
const QString BN_IMAGE = ":/img/images/BlackKnight.png";
const QString BR_IMAGE = ":/img/images/BlackRook.png";

const int PIECE_SIZE = 80;


namespace vue {

    class GameWindow : public QWidget
    {
        Q_OBJECT
    public:
        GameWindow(QWidget* parent);
        QGridLayout* displayedBoard = new QGridLayout();

        void changeBoardLayout(const string& fenString);

    public slots:
        void analyseUserInput();

    private:
        BoardSquareWindow* board_[N_COLUMNS][N_ROWS];
        model::Game modelBoard_;
        BoardSquareWindow* squareSelected_ = nullptr;

        void clearVisualBoard();
        void setBoardColor();
        void updatePiecesOnBoard();
        void showIllegalMoveAttempt(BoardSquareWindow* nextSquare);
        void showPossibleMoves(model::AbsPiece* piece);
        void movePiece(model::AbsPiece* piece, BoardSquareWindow* nextPos);
    };
}

#endif // CHESSBOARDWINDOW_H
