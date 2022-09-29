#include "boardsquarewindow.h"

BoardSquareWindow::BoardSquareWindow(QWidget* parent) : QLabel(parent){

}


void BoardSquareWindow::mousePressEvent(QMouseEvent*){
    emit press();
}


void BoardSquareWindow::setPosition(int x, int y){
    position_[0] = y;
    position_[1] = x;
}


int* BoardSquareWindow::getPos(){
    return position_;
}
