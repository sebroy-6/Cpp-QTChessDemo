#include "game.h"

model::Game::Game()
{
    initChessPieces();
    updatePiecesMoves();
}


model::Game::~Game(){
    eraseAllPieces();
}


void model::Game::initChessPieces(){
    eraseAllPieces();
    int currentPos[2] = {0, 0};

    for (char character : board_.getInitPositions()){
        bool isNumber = MIN_ASCII_DIGIT <= character && character <= MAX_ASCII_DIGIT;
        bool isLetter = (MIN_ASCII_CAPITAL_LETTER <= character && character <= MAX_ASCII_CAPITAL_LETTER) ||
                        (MIN_ASCII_MINUSCULE_LETTER <= character && character <= MAX_ASCII_MINUSCULE_LETTER);
        if (isNumber){
            currentPos[0] += character - ASCII_TO_DIGIT;
        }
        else if (character == '/'){
            currentPos[0] = 0;
            currentPos[1] += 1;
        }
        else if (isLetter){
            if (currentPos[0] >= N_COLUMNS && (currentPos[1] + 1) >= N_ROWS){
                if (character == 'w'){
                    board_.changeTurn(Team::WHITE);
                    break;
                }
                else if (character == 'b'){
                    board_.changeTurn(Team::BLACK);
                    break;
                }
            }
            else {
                addPieceWithType(character, currentPos);
                currentPos[0]++;
            }
        }
        else
            currentPos[0]++;
    }
    updateNKings();
}

void model::Game::addPieceWithType(char character, int currentPos[2]){

    if (character == 'k')
        addPieceToBoard(PieceType::KING, Team::BLACK, currentPos);
    else if (character == 'K')
        addPieceToBoard(PieceType::KING, Team::WHITE, currentPos);
    else if (character == 'n')
        addPieceToBoard(PieceType::KNIGHT, Team::BLACK, currentPos);
    else if (character == 'N')
        addPieceToBoard(PieceType::KNIGHT, Team::WHITE, currentPos);
    else if (character == 'r')
        addPieceToBoard(PieceType::ROOK, Team::BLACK, currentPos);
    else if (character == 'R')
        addPieceToBoard(PieceType::ROOK, Team::WHITE, currentPos);
}

void model::Game::setPiecePos(model::AbsPiece* piece, int pos[2]){
    piece->setPosition(pos[0], pos[1]);
    updatePiecesMoves();
}

void model::Game::setPiecePreviousPos(model::AbsPiece* piece){
    piece->returnPreviousPos();
    updatePiecesMoves();
}

const model::Team& model::Game::getTurn(){
    return board_.getTurn();
}


void model::Game::eraseAllPieces(){
    while (AbsPiece::getPiecesOnBoard().size() != 0){
        for (auto &&piece : AbsPiece::getPiecesOnBoard()){
            delete piece;
            break;
        }
    }
}


void model::Game::addPieceToBoard(PieceType type, Team color, int pos[2]){
    if ( findPiece(pos) == nullptr ){
        AbsPiece* piece;
        switch (type) {
            case PieceType::KING :
                piece = new King(color);
                // No worries for memory leaks, the piece pointer is stored in
                // AbsPiece::piecesOnBoard_ by it's constructor
                break;
            case PieceType::KNIGHT :
                piece = new Knight(color);
                break;
            case PieceType::ROOK :
                piece = new Rook(color);
                break;
        }
        setPiecePos(piece, pos);
    }
}


void model::Game::movePiece(model::AbsPiece* piece, int newPos[2]) {
    model::AbsPiece* pieceNextPos = findPiece(newPos);
    if (pieceNextPos != nullptr){
        delete pieceNextPos;
        updatePiecesMoves();
    }
    setPiecePos(piece, newPos);
    board_.switchTurn();

    CheckType isInCheck = checkIfEndOfGame();
    if (isInCheck == CheckType::CHECKMATE)
        throw Checkmate(getTurn());
    else if (isInCheck == CheckType::STALEMATE)
        throw Stalemate();

}


model::AbsPiece* model::Game::findPiece(int pos[2]){
    return model::AbsPiece::findPiece(make_pair(pos[0], pos[1]));
}


bool model::Game::checkIfPossibleMove(AbsPiece* piece, int nextPos[2]){
    int currentPos[2] = {piece->getYPos(), piece->getXPos()};

    for (int i = 0; i < piece->getNPossibleMoves(); i++){
        pair<int, int> move = piece->getMove(i);

        if ((currentPos[0] + move.first == nextPos[0]) &&
                (currentPos[1] + move.second == nextPos[1])){
            return true;
        }
    }
    return false;
}


bool model::Game::checkIsValidMove(AbsPiece* piece, int nextPos[2]) {
    if (board_.checkIfIsPositionOnBoard(nextPos)) {
        if (piece->getTeam() == board_.getTurn()) {
            if (checkIfPossibleMove(piece, nextPos)) {
                if (findPiece(nextPos) != nullptr) {
                    AbsPiece* pieceAtNextPos = findPiece(nextPos);
                    if (pieceAtNextPos->getTeam() != piece->getTeam()) {
                        AbsPiece::getPiecesOnBoard().remove(pieceAtNextPos);
                        setPiecePos(piece, nextPos);

                        updatePiecesMoves();
                        if (model::AbsPiece::lookForCheck(board_.getTurn()) != CheckType::NONE){
                            setPiecePreviousPos(piece);
                            model::AbsPiece::getPiecesOnBoard().push_back(pieceAtNextPos);
                            updatePiecesMoves();
                            return false;
                        }
                        else{
                            setPiecePreviousPos(piece);
                            model::AbsPiece::getPiecesOnBoard().push_back(pieceAtNextPos);
                            updatePiecesMoves();
                            return true;
                        }
                    }
                    return false;
                }
                else {
                    setPiecePos(piece, nextPos);
                    if (model::AbsPiece::lookForCheck(board_.getTurn()) != CheckType::NONE){
                        setPiecePreviousPos(piece);
                        return false;
                    }
                    else{
                        setPiecePreviousPos(piece);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}


void model::Game::updatePiecesMoves(){
    for (auto &&piece : AbsPiece::getPiecesOnBoard()) {
        if ( piece->getType() == PieceType::KING )
            dynamic_cast<King*>(piece)->updateMoves();
        else if ( piece->getType() == PieceType::KNIGHT)
            dynamic_cast<Knight*>(piece)->updateMoves();
        else if ( piece->getType() == PieceType::ROOK)
            dynamic_cast<Rook*>(piece)->updateMoves();
    }
}


int model::Game::getNbValidMoves(const Team& side){
    int nbTeamPossibleMoves = 0;
    for (auto &&piece : model::AbsPiece::getPiecesOnBoard()){
        if (piece->getTeam() == side){
            for (int i = 0; i < piece->getNPossibleMoves(); i++){
                int nextPotentialPos[2] = {piece->getYPos() + piece->getMove(i).first, piece->getXPos() + piece->getMove(i).second};
                if(checkIsValidMove(piece, nextPotentialPos)){
                    nbTeamPossibleMoves++;
                }
            }
        }
    }
    return nbTeamPossibleMoves;
}


model::CheckType model::Game::checkIfEndOfGame(){
    if (getNbValidMoves(getTurn()) == 0){
        for (auto &&piece : model::AbsPiece::getPiecesOnBoard()){
            if (piece->getTeam() == getTurn() && piece->getType() == PieceType::KING){
                int pos[2] = {piece->getYPos(), piece->getXPos()};
                if (model::AbsPiece::checkIfPositionInDanger(pos))
                    return CheckType::CHECKMATE;
                else
                    return CheckType::STALEMATE;
            }
        }
    }
    return CheckType::NONE;
}

void model::Game::updateNKings(){
    nKings_ = 0;
    for (auto&& piece : AbsPiece::getPiecesOnBoard()){
        if (piece->getType() == PieceType::KING)
            nKings_++;
    }
}


// usefull for the menu
void model::Game::changeBoardLayout(const string& fenString){
    board_.changeFenString(fenString);
    initChessPieces();
    if (nKings_ > MAX_N_KINGS){
        while (nKings_ > 2){
            for (auto &&piece : AbsPiece::getPiecesOnBoard()){
                if (piece->getType() == PieceType::KING){
                    delete piece;
                    nKings_--;
                    break;
                }
            }
        }
        throw TooManyKings();
    }
    updatePiecesMoves();
}
