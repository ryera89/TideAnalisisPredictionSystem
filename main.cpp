#include "mainwindow.h"
#include <QApplication>
#include "include/mainComponents/spmmainwindow.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("SIPMAR");
    QApplication::setApplicationDisplayName("SIPMAR");
    SPMmainWindow *spm = new SPMmainWindow;
    spm->show();

    return a.exec();
}
