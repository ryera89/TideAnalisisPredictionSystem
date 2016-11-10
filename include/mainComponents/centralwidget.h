#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>

class QTableView;
#include <QHBoxLayout>
#include "spmchart.h"
#include <QPlainTextEdit>
#include "include/model_view/tablemodel.h"
#include "include/model_view/tidaltabledelegate.h"
#include "include/model_view/readonlytablemodel.h"
#include "customchartview.h"
#include <iostream>


class DisplayedDataLabels;
class QSpinBox;
class QSlider;

class XYTidalChartModelMapper;

class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CentralWidget(QWidget *parent = 0);

    //MySeries* chartSerie() const{return m_series;}
    QSplineSeries* chartSerie() const{return m_series;}
    QTableView* tableView() const{return m_tidalTableView;}
    QChartView* chartView() const{return m_tideChartView;}
    ReadOnlyTableModel* tableModel() const{return m_tidalTableModel;}


signals:

public slots:
    //void loadData(const QString &filePath);
    //void loadDataInTable(const QVector<TidesMeasurement> &measurements);
    //void loadDataChart(); //Funcion para actualizar la grafica.
    //void updateDataInChartWhenRowIsEliminated(int i, int cont); //Slot para modificar la tabla cuando se elimina una fila
    //void  checkDateTimeStringFormat(const QString &dateFormat, const QString &timeFormat);


    void updateSerieData(int row);
    void setSeriesData();

private slots:
    void zoomXAxis(int level);
private:
    //Table Facilities
    QTableView *m_tidalTableView;

    //Chart Facilities

    SPMChart *m_tideChart;
    customChartView *m_tideChartView;

    QDateTimeAxis *m_timeAxis;
    //QValueAxis *m_yAxis;
    QSplineSeries *m_series;
    //QScatterSeries *m_scatterSerie;
    //MySeries *m_series;
    //Display Facilities
    QSlider *m_rangeSlider;
    QSpinBox *m_rangeSpinBox;
    //DisplayedDataLabels *m_rangeIniDDLabel;
    //DisplayedDataLabels *m_rangeEndDDLabel;
    DisplayedDataLabels *m_selectionIniDDLabel;
    DisplayedDataLabels *m_selectionEndDDLabel;
    DisplayedDataLabels *m_cursorPosDDLabel;

    //Storage and sync facilities
    ReadOnlyTableModel *m_tidalTableModel;
    XYTidalChartModelMapper *m_mapper;


    int m_currentXZoomLevel;

    void createComponents();
    void settingUpTable();
    void settingZoomPosibleValues();

};

#endif // CENTRALWIDGET_H
