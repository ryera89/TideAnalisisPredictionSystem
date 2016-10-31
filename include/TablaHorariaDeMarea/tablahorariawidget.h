#ifndef TABLAHORARIAWIDGET_H
#define TABLAHORARIAWIDGET_H

#include <QWidget>
//#include <QVector>
#include "tablahorariademarea.h"

class QDateEdit;
class QLabel;
class QRadioButton;
class QGroupBox;
class QPushButton;

class TablaHorariaWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TablaHorariaWidget(QWidget *parent = 0);

    QSize sizeHint() const;

signals:

public slots:
    void loadTableData(const TidalData &m_data);

private slots:
    void setIntervalState(bool enabledState);
    void setMinimumEndDateEditValue(const QDate &date);

    void showInterval();
    void showAllData(bool showAll);

private:
    TablaHorariaDeMarea *m_tablaHoraria;

    QGroupBox *m_showDataGroupBox;
    QGroupBox *m_intervalGroupBox;
    QGroupBox *m_extremesGroupBox;

    QRadioButton *m_allRadioButton;
    QRadioButton *m_customRadioButton;

    QLabel *m_iniDateLabel;
    QLabel *m_endDateLabel;
    QLabel *m_maxLabel;
    QLabel *m_minLabel;

    QDateEdit *m_iniDateEdit;
    QDateEdit *m_endDateEdit;

    QPushButton *m_applyPushButton;

    QVector<int> m_notHiddenRows;

    TidesMeasurement m_maximo;
    TidesMeasurement m_minimo;

    TidesMeasurement m_maximoInInterval;
    TidesMeasurement m_minimoInInterval;

    void createComponents();

    void setSumAndMeanOfNotHiddenRows();
    void setSumAndMeanOfAllRows();
};

#endif // TABLAHORARIAWIDGET_H
