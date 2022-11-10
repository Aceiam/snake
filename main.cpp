#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget window;
    window.setWindowIcon(QIcon("://title2.png"));
    window.setWindowTitle("Дракончик");
    window.setFixedSize(601, 601);

    window.show();
    window.startApp();

    return a.exec();
}
