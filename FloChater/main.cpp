#include "MnWin/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.init();
    w.showMaximized();
    //w.show();

    return a.exec();
}
