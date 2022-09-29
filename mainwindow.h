#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "gamewindow.h"

// The "non-POD" warnings can be ignored here since they exist to prevent the
// app from initialising const variables that may not be used afterwards.
// In our case, every const variable is used so the warning is not relevant here.

// All the selectable starting positions
const string EMPTY_BOARD = "";
const string TRANDITIONAL_POSITIONS = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
const string FEN_1 = "4r3/4k3/1r3n2/3n1N2/6R1/R3N3/3K4/8 b - - 0 1";
const string FEN_2 = "8/R4R2/4K3/r1k3n1/2n5/4N3/8/8 w - - 0 1";
const string FEN_3 = "8/8/1r3N2/4k3/4N3/3K4/8/8 w - - 0 1";
const string FEN_4 = "5r2/6r1/2k5/8/8/7K/8/8 w - - 0 1";

const QString MENU_BACKGROUND_COLOR = "background-color: darkbrown;";
const QString BUTTON_COLOR = "background-color: grey;";
const QFont BUTTON_FONT = QFont("times", 21);
const QFont LABEL_FONT = QFont("times", 30);

const int CHESSBOARD_HEIGHT = 800;
const int CHESSBOARD_WIDTH = 800;
const int MENU_HEIGHT = 800;
const int MENU_WIDTH = 350;
const int LABEL_WIDTH = 250;
const int LABEL_HEIGHT= 50;
const int BUTTON_WIDTH = 200;
const int BUTTON_HEIGHT= 50;

const int SPACE_BETWEEN_ELEMENTS = 10;

const QString RESET_BUTTON_TEXT = "reset";
const QString FIRST_BUTTON_TEXT = "Traditionnal";
const QString SECOND_BUTTON_TEXT = "Option 1";
const QString THIRD_BUTTON_TEXT = "Option 2";
const QString FOURTH_BUTTON_TEXT = "Option 3";
const QString FIFTH_BUTTON_TEXT = "Option 4";



class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

private:
    vue::GameWindow* gameWindow = nullptr;
    void initMenu(QWidget* menuWidget);
    void addLabelToMenu(QWidget* menuWidget, const QString& text, int Xpos, int Ypos);
    void addButtonToMenu(QWidget* menuWidget, const QString& text, int Xpos, int Ypos);

private slots:
    void interpreteMenuSelection();
};
#endif // MAINWINDOW_H
