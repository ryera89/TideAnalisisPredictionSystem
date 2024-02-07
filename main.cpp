#include "include/mainComponents/spmmainwindow.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QApplication::setApplicationName("SIPMAR");
  QApplication::setApplicationDisplayName("SIPMAR");

  // QLocale::setDefault(QLocale::C);

  SPMmainWindow *spm = new SPMmainWindow;
  spm->show();

  return a.exec();
}
