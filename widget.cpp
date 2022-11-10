#include "widget.h"
#include <QPalette>
#include <QTimer>
#include <QKeyEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    direction = Direction::Right;
    speed  = 100;
    step = 0;
    needToRemoveHvost = 0;
}

void Widget::startApp()
{
    this->setStyleSheet("background: #505050");

    QPalette redPallete;
    redPallete.setColor(QPalette::Window, Qt::red);

    // set lbl on desk
    for (unsigned i = 0; i < 30; ++i)
        for (unsigned j = 0; j < 30; ++j){
            lbl[i][j] = new QLabel(this);
            lbl[i][j]->setFixedSize(19, 19);
            lbl[i][j]->move(20 * i + 1, 20 * j + 1);
            lbl[i][j]->show();
            makeFree(i, j);
        }

    makeSnakeMega(0, 0);
    makeSnakeMega(1, 0);
    makeSnakeMega(2, 0);
    callTimer();
}

void Widget::makeSnake(int i, int j)
{
    lbl[i][j]->setStyleSheet("background: DarkOliveGreen");
    lbl[i][j]->repaint();
}

void Widget::makeFree(int i, int j)
{
    lbl[i][j]->setStyleSheet("background: #404040");
    lbl[i][j]->repaint();
}

void Widget::makeFruit(int i, int j)
{
    lbl[i][j]->setStyleSheet("background: khaki");
    lbl[i][j]->repaint();
}

void Widget::setFruit()
{
    while (true){
        QPoint position(rand() % 30, rand() % 30);
        bool isPositionClear = !isFruitOnPosition(position) && !isSnakeOnPosition(position);
        if (isPositionClear){
            fruits.push_back(position);
            makeFruit(position.x(), position.y());
            break;
        }
    }
}

bool Widget::isFruitOnPosition(QPoint pos)
{
    for (auto it : fruits)
        if (it == pos)
            return true;
    return false;
}

bool Widget::isSnakeOnPosition(QPoint pos)
{
    for (auto it : snake)
        if (it == pos)
            return true;
    return false;
}

void Widget::callTimer()
{
    switch (lastDirection){
    case Up:    if (direction != Down)  direction = Up;    break;
    case Down:  if (direction != Up)    direction = Down;  break;
    case Left:  if (direction != Right) direction = Left;  break;
    case Right: if (direction != Left)  direction = Right; break;
    default:;
    }
    makeMove();
    QTimer::singleShot(speed, this, &Widget::callTimer);
}

void Widget::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()){
    case Qt::Key::Key_Up:    if (direction != Down)  lastDirection = Up;    break;
    case Qt::Key::Key_Down:  if (direction != Up)    lastDirection = Down;  break;
    case Qt::Key::Key_Left:  if (direction != Right) lastDirection = Left;  break;
    case Qt::Key::Key_Right: if (direction != Left)  lastDirection = Right; break;
    default:;
    }
}

void Widget::makeMove()
{
    step++;
    QPoint endPoint = snake[snake.size() - 1];

    QPoint newHead;
    if (direction == Left){
        if (snake[0].x() == 0)
            newHead = QPoint(29, snake[0].y());
        else
            newHead = QPoint(snake[0].x() - 1, snake[0].y());
    }
    else if (direction == Right)
        newHead = QPoint((snake[0].x() + 1) % 30, snake[0].y());
    else if (direction == Up){
        if (snake[0].y() == 0)
            newHead = QPoint(snake[0].x(), 29);
        else
            newHead = QPoint(snake[0].x(), snake[0].y() - 1);
    }
    else if (direction == Down)
        newHead = QPoint(snake[0].x(), (snake[0].y() + 1) % 30);

    // check is fruit here
    if (isFruitOnPosition(newHead))
        fruits.removeOne(newHead);
    else {
        // remove hvost
        makeFree(endPoint.x(), endPoint.y());
        snake.removeLast();
    }

    if (isSnakeOnPosition(newHead) || needToRemoveHvost > 0)
        needToRemoveHvost = snake.size() - 3;
    else {
        // add head
        makeSnake(newHead.x(), newHead.y());
        snake.insert(0, newHead);
    }

    if (step % 50 == 0)
        setFruit();
}

void Widget::makeSnakeMega(int i, int j)
{
    snake.insert(0, QPoint(i, j));
    makeSnake(i, j);
}
