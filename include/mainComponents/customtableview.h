#ifndef CUSTOMTABLEVIEW_H
#define CUSTOMTABLEVIEW_H

#include <QTableView>

class CustomTableView : public QTableView
{
    Q_OBJECT
public:
    CustomTableView(QWidget *parent = 0): QTableView(parent){}


    //Funciones Reimplementadas
    //QSize sizeHint() const;
};

#endif // CUSTOMTABLEVIEW_H
