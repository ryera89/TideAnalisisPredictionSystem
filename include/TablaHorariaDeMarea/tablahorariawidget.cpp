#include "tablahorariawidget.h"
#include <QHBoxLayout>
TablaHorariaWidget::TablaHorariaWidget(QWidget *parent) : QWidget(parent)
{
    m_tablaHoraria = new TablaHorariaDeMarea(this);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(m_tablaHoraria);

    this->setLayout(mainLayout);
}

void TablaHorariaWidget::loadTableData(TidalData *m_data)
{
    m_tablaHoraria->loadData(m_data);
}
