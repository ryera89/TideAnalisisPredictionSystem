#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>

#include "tidesdatatable.h"
#include "freqeditor.h"
#include <QHBoxLayout>
#include "spmchart.h"
#include <QPlainTextEdit>
#include "include/model_view/tablemodel.h"
#include "include/model_view/tidaltabledelegate.h"
#include <QTableView>

class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CentralWidget(QWidget *parent = 0);

signals:

public slots:
    //void loadData(const QString &filePath);
    //void loadDataInTable(const QVector<TidesMeasurement> &measurements);
    void recieveData(const QVector<QStringList> &data, int dateField, int timeField, int heightField, const QString &dateFormat, const QString &timeFormat);
    //void  checkDateTimeStringFormat(const QString &dateFormat, const QString &timeFormat);

    void loadDataChart(); //Funcion para actualizar la grafica.
    //void updateDataInChartWhenRowIsEliminated(int i, int cont); //Slot para modificar la tabla cuando se elimina una fila

private:
    //TidesDataTable *m_dataTable;  //Tabla donde se muestran los datos de las mediciones.
    QTableView *m_tidalTableView;
    TableModel *m_tidalTableModel;
    //TidalTableDelegate *m_tidalTableDelegate;

    SPMChart *m_tideChart;
    QChartView *m_tideChartView;
    //QPlainTextEdit *m_edit;
    QDateTimeAxis *m_timeAxis;
    QSplineSeries *m_series;

    //FreqEditor *m_freqEditor;  //NOTE: freq editor remover luego

};

#endif // CENTRALWIDGET_H
