#ifndef BOARDSQUAREWINDOW_H
#define BOARDSQUAREWINDOW_H

#include <QLabel>
#include <QMouseEvent>
#include <iostream>
#include "AbsPieces.h"

class BoardSquareWindow : public QLabel
{
    Q_OBJECT
public:
    BoardSquareWindow(QWidget* parent = nullptr);
    void setPosition(int y, int x);
    int* getPos();

signals:
    void press();

private:
    int position_[2];
    void mousePressEvent(QMouseEvent *e) override;
};

#endif // BOARDSQUAREWINDOW_H
