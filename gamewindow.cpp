#include "gamewindow.h"

vue::GameWindow::GameWindow(QWidget* parent) : QWidget(parent)
{
    for (int i = 0; i < N_ROWS; i++){
        for(int j = 0; j < N_COLUMNS; j++){
            BoardSquareWindow* position = new BoardSquareWindow(parent);
            position->setAlignment(Qt::AlignCenter);
            position->setPosition(i, j);
            board_[j][i] = position;
            displayedBoard->addWidget(position, i, j, 1, 1);

            connect(position, SIGNAL(press()), this, SLOT(analyseUserInput()));
        }
    }

    displayedBoard->setSpacing(0);
    updatePiecesOnBoard();
    cout << endl;
    cout << "////////Pieces Created////////" << endl;
    cout << "########Start of game########" << endl;
}


void vue::GameWindow::setBoardColor(){
     bool rowIsPair;
     for(int i = 0; i < N_COLUMNS; i++){
        if(i % 2 == 0)
            rowIsPair = true;
        else
            rowIsPair = false;
        for (int j = 0; j < N_ROWS; j++) {
            if ((rowIsPair && (j % 2 == 0)) || (!rowIsPair && !(j % 2 == 0)))
                board_[j][i]->setStyleSheet(LIGHT_SQUARE_COLOR);
            else
                board_[j][i]->setStyleSheet(DARK_SQUARE_COLOR);
        }
    }
}


void vue::GameWindow::clearVisualBoard(){
    for (int i = 0; i < N_COLUMNS; i++) {
        for (int j = 0; j < N_ROWS; j++)
            board_[j][i]->setPixmap(QPixmap());
    }
}


void vue::GameWindow::updatePiecesOnBoard(){
    using namespace model;

    QSize imageSize (PIECE_SIZE, PIECE_SIZE);
    QPixmap pieceImage;

    clearVisualBoard();

    for (auto &&piece : AbsPiece::getPiecesOnBoard()){
        if(piece->getTeam() == Team::WHITE){
            if (piece->getType() == PieceType::KING) {
                pieceImage = QPixmap(WK_IMAGE);
            }
            else if (piece->getType() == PieceType::KNIGHT) {
                pieceImage = QPixmap(WN_IMAGE);
            }
            else if (piece->getType() == PieceType::ROOK) {
                pieceImage = QPixmap (WR_IMAGE);
            }
        }
        else {
            if (piece->getType() == PieceType::KING) {
                pieceImage = QPixmap(BK_IMAGE);
            }
            else if (piece->getType() == PieceType::KNIGHT) {
                pieceImage = QPixmap(BN_IMAGE);
            }
            else if (piece->getType() == PieceType::ROOK) {
                pieceImage = QPixmap(BR_IMAGE);
            }
        }
        board_[piece->getYPos()][piece->getXPos()]->setPixmap(pieceImage.scaled(imageSize));
    }
    setBoardColor();
}


void vue::GameWindow::analyseUserInput(){
    if (squareSelected_ != nullptr){
        model::AbsPiece* pieceOnSelectedSquare = modelBoard_.findPiece(squareSelected_->getPos());

        if (pieceOnSelectedSquare != nullptr){
            BoardSquareWindow* nextSquare = qobject_cast<BoardSquareWindow*>(sender());
            int* nextPos = nextSquare->getPos();
            bool isLegalMove = false;
            {
                isLegalMove = modelBoard_.checkIsValidMove(pieceOnSelectedSquare, nextPos);

                if ( isLegalMove )
                    movePiece(pieceOnSelectedSquare, nextSquare);
                else{
                    showIllegalMoveAttempt(nextSquare);
                    squareSelected_ = nullptr;
                }
            }
        }
        squareSelected_ = nullptr;
    }
    else{
        squareSelected_ = qobject_cast<BoardSquareWindow*>(sender());

        if (squareSelected_ != nullptr){
            model::AbsPiece* pieceOnSelectedSquare = modelBoard_.findPiece(squareSelected_->getPos());
            if (pieceOnSelectedSquare != nullptr){
                if (pieceOnSelectedSquare->getTeam() == modelBoard_.getTurn())
                    showPossibleMoves(pieceOnSelectedSquare);
                else
                    squareSelected_ = nullptr;
            }
            else
                squareSelected_ = nullptr;
        }
    }
}


void vue::GameWindow::showIllegalMoveAttempt(BoardSquareWindow* nextSquare){
    updatePiecesOnBoard();
    nextSquare->setStyleSheet(nextSquare->styleSheet() + SHOW_ERROR_COLOR);

}


void vue::GameWindow::showPossibleMoves(model::AbsPiece* piece){
    updatePiecesOnBoard();
    for (int i = 0; i < piece->getNPossibleMoves(); i++){
        int nextPotentialPos[2] = {piece->getYPos() + piece->getMove(i).first, piece->getXPos() + piece->getMove(i).second};

        if(modelBoard_.checkIsValidMove(piece, nextPotentialPos)){
            BoardSquareWindow* position = board_[nextPotentialPos[0]][nextPotentialPos[1]];
            position->setStyleSheet(position->styleSheet() + SHOW_MOVE_COLOR);
        }
    }
}


void vue::GameWindow::movePiece(model::AbsPiece* piece, BoardSquareWindow* nextSquare){
    int* nextPos = nextSquare->getPos();
    try {
        modelBoard_.movePiece(piece, nextPos);
        updatePiecesOnBoard();
    }
    catch (model::Checkmate& e){
        updatePiecesOnBoard();
        cout << e.what() << endl;
        cout << "This game is finished" << endl;
        for (auto &&piece : model::AbsPiece::getPiecesOnBoard()){
            if (piece->getTeam() != e.getLoser()){
                BoardSquareWindow* pos = board_[piece->getYPos()][piece->getXPos()];
                pos->setStyleSheet(pos->styleSheet() + SHOW_WINNING_COLOR);
            }
        }
    }
    catch (model::Stalemate& e){
        updatePiecesOnBoard();
        cout << e.what() << endl;
        cout << "This game is finished" << endl;
    }
}


void vue::GameWindow::changeBoardLayout(const string& fenString){
    try {
        modelBoard_.changeBoardLayout(fenString);
    }
    catch (model::TooManyKings& e){
        cout << e.what() << endl;
    }

    updatePiecesOnBoard();
}
