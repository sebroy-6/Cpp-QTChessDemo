#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget* boardWidget = new QWidget(this);
    QWidget* menuWidget = new QWidget(this);
    gameWindow = new vue::GameWindow(boardWidget);
    gameWindow->changeBoardLayout(TRANDITIONAL_POSITIONS);

    setGeometry(0, 0, CHESSBOARD_WIDTH + MENU_WIDTH,
                CHESSBOARD_HEIGHT + (MENU_HEIGHT - CHESSBOARD_HEIGHT));
    boardWidget->setGeometry(0, 0, CHESSBOARD_WIDTH, CHESSBOARD_HEIGHT);
    menuWidget->setGeometry(CHESSBOARD_WIDTH, 0, MENU_WIDTH, MENU_HEIGHT);

    boardWidget->setLayout(gameWindow->displayedBoard);
    initMenu(menuWidget);
}


void MainWindow::addButtonToMenu(QWidget* menuWidget, const QString& text, int Xpos, int Ypos){
    QPushButton* button = new QPushButton(menuWidget);
    button->setStyleSheet(BUTTON_COLOR);
    button->setText(text);
    button->setGeometry(Xpos, Ypos, BUTTON_WIDTH, BUTTON_HEIGHT);
    button->setFont(BUTTON_FONT);

    connect(button, SIGNAL(clicked()), this, SLOT(interpreteMenuSelection()));
}

void MainWindow::addLabelToMenu(QWidget* menuWidget, const QString& text, int Xpos, int Ypos){
    QLabel* label = new QLabel(menuWidget);
    label->setText(text);
    label->setGeometry(Xpos, Ypos, LABEL_WIDTH, LABEL_HEIGHT);
    label->setFont(LABEL_FONT);
}

void MainWindow::initMenu(QWidget* menuWidget){
    int horizontalMiddle = (MENU_WIDTH / 2) - (BUTTON_WIDTH / 2);
    int currentVerticalPos = 0;
    menuWidget->setStyleSheet(MENU_BACKGROUND_COLOR);

    currentVerticalPos += MENU_HEIGHT / SPACE_BETWEEN_ELEMENTS;
    addLabelToMenu(menuWidget, "  Chess Game!", horizontalMiddle, currentVerticalPos);
    currentVerticalPos += MENU_HEIGHT / SPACE_BETWEEN_ELEMENTS;
    addButtonToMenu(menuWidget, RESET_BUTTON_TEXT, horizontalMiddle, currentVerticalPos);
    currentVerticalPos += MENU_HEIGHT / SPACE_BETWEEN_ELEMENTS;
    addLabelToMenu(menuWidget, "Starting Positions", horizontalMiddle, currentVerticalPos);
    currentVerticalPos += MENU_HEIGHT / SPACE_BETWEEN_ELEMENTS;
    addButtonToMenu(menuWidget, FIRST_BUTTON_TEXT, horizontalMiddle, currentVerticalPos);
    currentVerticalPos += BUTTON_HEIGHT;
    addButtonToMenu(menuWidget, SECOND_BUTTON_TEXT, horizontalMiddle, currentVerticalPos);
    currentVerticalPos += BUTTON_HEIGHT;
    addButtonToMenu(menuWidget, THIRD_BUTTON_TEXT, horizontalMiddle, currentVerticalPos);
    currentVerticalPos += BUTTON_HEIGHT;
    addButtonToMenu(menuWidget, FOURTH_BUTTON_TEXT, horizontalMiddle, currentVerticalPos);
    currentVerticalPos += BUTTON_HEIGHT;
    addButtonToMenu(menuWidget, FIFTH_BUTTON_TEXT, horizontalMiddle, currentVerticalPos);

}

void MainWindow::interpreteMenuSelection(){
    QString senderText = qobject_cast<QPushButton*>(sender())->text();
    if (senderText == RESET_BUTTON_TEXT)
        gameWindow->changeBoardLayout(EMPTY_BOARD);
    else {
        if (senderText == FIRST_BUTTON_TEXT)
            gameWindow->changeBoardLayout(TRANDITIONAL_POSITIONS);
        else if (senderText == SECOND_BUTTON_TEXT)
            gameWindow->changeBoardLayout(FEN_1);
        else if (senderText == THIRD_BUTTON_TEXT)
            gameWindow->changeBoardLayout(FEN_2);
        else if (senderText == FOURTH_BUTTON_TEXT)
            gameWindow->changeBoardLayout(FEN_3);
        else if (senderText == FIFTH_BUTTON_TEXT)
            gameWindow->changeBoardLayout(FEN_4);
        cout << "////////NEW GAME////////" << endl;
    }
}

