#ifndef TABLAHORARIAWIDGET_H
#define TABLAHORARIAWIDGET_H

#include <QWidget>
#include "tablahorariademarea.h"
class TablaHorariaWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TablaHorariaWidget(QWidget *parent = 0);

signals:

public slots:
    void loadTableData(TidalData *m_data);

private:
    TablaHorariaDeMarea *m_tablaHoraria;
};

#endif // TABLAHORARIAWIDGET_H
