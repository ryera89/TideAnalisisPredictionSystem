#ifndef TABLAHORARIADEMAREA_H
#define TABLAHORARIADEMAREA_H

#include "../measurement/tidaldata.h"
#include <QTableWidget>
class TablaHorariaDeMarea : public QTableWidget {
  Q_OBJECT
public:
  TablaHorariaDeMarea(QWidget *parent = 0) : QTableWidget(parent) {}

public slots:
  void loadData(const TidalData &m_data);

private:
  void createTable(const TidalData &m_data);
  void populateTable(const TidalData &m_data);
  // TidalData *m_data;
};

#endif // TABLAHORARIADEMAREA_H
