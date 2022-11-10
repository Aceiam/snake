#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget() = default;

    void startApp();

    uint8_t mapSize;
    QLabel *lbl[30][30];

    void makeSnake(int i, int j);
    void makeFree(int i, int j);
    void makeFruit(int i, int j);

    void callTimer();
    void makeMove();

protected:
    void keyPressEvent(QKeyEvent* e);

    enum Direction {
        Up, Down, Left, Right
    };
    Direction direction;
    Direction lastDirection;

    int speed;
    QList <QPoint> snake;
    QList <QPoint> fruits;
    void makeSnakeMega(int i, int j);
    void setFruit();
    bool isFruitOnPosition(QPoint pos);
    bool isSnakeOnPosition(QPoint pos);

    uint step;
    uint needToRemoveHvost;
};
#endif // WIDGET_H
