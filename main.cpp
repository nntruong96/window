#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
  //  QFont newFont("Courier", 1, QFont::Times, true);
    //set font of application
    //QApplication::setFont(newFont);
    w.setFixedSize(1280,900);
    return a.exec();
}
