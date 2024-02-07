#ifndef TABLAHORARIAREPORT_H
#define TABLAHORARIAREPORT_H

#include "include/Report/reportwindow.h"

class TablaHorariaReport : public ReportWindow {
  Q_OBJECT
public:
  TablaHorariaReport(QWidget *parent = 0);

public slots:
  virtual void print();
  virtual void printPDF();
};

#endif // TABLAHORARIAREPORT_H
