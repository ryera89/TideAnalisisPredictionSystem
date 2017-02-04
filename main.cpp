#include "mainwindow.h"
#include <QApplication>
#include "include/mainComponents/spmmainwindow.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SPMmainWindow *spm = new SPMmainWindow;
    spm->show();
    //QList<QByteArray> timeZones = QTimeZone::availableTimeZoneIds(-18000);

    //QByteArray timeZoneId("UTC-05:00",9);
    //QTimeZone zone(timeZoneId);
    //std::cout << timeZoneId.toStdString() << " " << zone.offsetFromUtc(QDateTime(QDate(2017,8,1))) << " " << zone.hasDaylightTime() <<std::endl;




    /*foreach (QByteArray array, timeZones) {
        std::cout << array.toStdString() << std::endl;
    }*/
    return a.exec();
}
