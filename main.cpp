#include "evgui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EVgui w;
    w.setWindowTitle("StrawTest");
    w.show();

    return a.exec();
}
