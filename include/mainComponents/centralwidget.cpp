#include "centralwidget.h"
#include <QTableView>
#include "include/measurement/measurement.h"
#include "include/ChartModelMapper/xytidalchartmodelmapper.h"

//TODO: Revisar todo el codigo pues hay que modificarlo.

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
    //QVector<TidesMeasurement> measurement = readTidesDataFromCVSFile("files/prueba7.csv"); //NOTE: probando remover despues
    //m_dataTable = new TidesDataTable(this);

    //m_tidalTableModel = new ReadOnlyTableModel;

    settingUpTable();

    //TODO: BUSCAR COMO ORDENAR ESTO

    m_tideChart = new SPMChart;
    m_tideChart->setTheme(QChart::ChartThemeQt);

    //m_tideChart->setAnimationOptions(QChart::AllAnimations);

    m_series = new QSplineSeries;
    //XYTidalChartModelMapper *mapper = new XYTidalChartModelMapper(m_tidalTableModel,m_series);


    m_tideChartView = new customChartView(m_tideChart,this);

    //m_tideChartView->setRubberBand(QChartView::RectangleRubberBand);
    //m_tideChartView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    m_timeAxis = new QDateTimeAxis;
    m_timeAxis->setFormat("dd/MM/yyyy h:mm:ss");

    //NOTE: Valorar Remover esto
    m_tideChart->addSeries(m_series);
    m_tideChart->createDefaultAxes();

    m_tideChartView->chart()->setAxisX(m_timeAxis,m_series);

    m_tideChartView->chart()->axisX(m_series)->setTitleText(tr("Tiempo"));

    //m_freqEditor = new FreqEditor;

    QHBoxLayout *mainLayout = new QHBoxLayout;

    mainLayout->addWidget(m_tidalTableView);
    //QVBoxLayout *rigthLayout = new QVBoxLayout; //NOTE: Probando el edit
    //m_edit = new QPlainTextEdit(this);                                //NOTE: creando el edit
    //rigthLayout->addWidget(m_tideChartView);
    //rigthLayout->addWidget(m_edit);
    mainLayout->addWidget(m_tideChartView);

    this->setLayout(mainLayout);

    //Connections

    //connect(m_dataTable,SIGNAL(rowEliminated(int,int)),this,SLOT(updateDataInChartWhenRowIsEliminated(int,int)));
}

/*void CentralWidget::loadDataChart()
{
   // m_tideChart->removeAllSeries(); //NOTE: Para ver luego

    m_series->clear();

    QVector<QDateTime> time;

    for (int i = 0; i < m_tidalTableView->rowCount(); ++i){
            time.push_back(QDateTime(m_tidalTableView->item(i,0)->data(Qt::EditRole).toDate(),m_tidalTableView->item(i,1)->data(Qt::EditRole).toTime()));
            //std::cout << i <<" " << m_dataTable->item(i,0)->text().toStdString() << " " << m_dataTable->item(i,1)->text().toStdString() << " " <<m_dataTable->item(i,2)->text().toStdString() << std::endl;
    }
    for (int i = 0; i < m_dataTable->rowCount(); ++i){
        m_series->append(time[i].toMSecsSinceEpoch(),m_tidalTableView->item(i,2)->data(Qt::EditRole).toDouble());
    }

    m_tideChart->addSeries(m_series);
    m_tideChart->createDefaultAxes();

    m_tideChartView->chart()->setAxisX(m_timeAxis,m_series);
}*/

/*void CentralWidget::updateDataInChartWhenRowIsEliminated(int i, int cont)
{
    m_series->removePoints(i,cont);
}*/

/*void CentralWidget::loadData(const QString &filePath)
{
    //TODO: Poner esto en un dialogo de tal forma que se haga solo.

    //QFile file(filePath);
    //if (file.open(QIODevice::ReadOnly)){
        //QTextStream in(&file);
        //m_edit->setPlainText(in.readAll());
        //file.close();
    //}
    //--------------------------------------------------------------------
    QVector<TidesMeasurement> measurement = readTidesDataFromCVSFile(filePath); //NOTE: probando remover despues
    loadDataInTable(measurement);
    loadDataChart();
}

void CentralWidget::loadDataInTable(const QVector<TidesMeasurement> &measurements)
{
    m_dataTable->setData(measurements);
}*/
//TODO: connectar este slot al dialogo.
//TODO: fecha y hora formatos
/*void CentralWidget::recieveData(const QVector<QStringList> &data, int dateField, int timeField, int heightField, const QString &dateFormat, const QString &timeFormat) //SLOT para conectar con el dialogo de importar datos y asi cargar los datos al modulo principal.
{
    QVector<TidesMeasurement> measurements;
    for (int i = 0; i < data.size(); ++i){
        if (dateField <= data[i].size() && timeField <= data[i].size() && heightField <= data[i].size()){ //Chequea que el campo exista
            //QVariant dateVariant = data[i].at(dateField - 1);
            //QVariant timeVariant = data[i].at(timeField - 1);

            QDate date = QDate::fromString(data[i].at(dateField - 1),dateFormat);
            QTime time = QTime::fromString(data[i].at(timeField - 1), timeFormat);

            //TODO: Crear un chequeo para comprobar si se estan cargando bien los datos.

            bool d_ok;
            QVariant heightVariant = data[i].at(heightField - 1);
            double height = heightVariant.toDouble(&d_ok);

            if (date.isValid() && time.isValid() && d_ok){
                measurements.push_back(TidesMeasurement(height,date,time));
            }

        }

    }
    //Esto  es lo que se cambiaria
   m_tidalTableModel->setMeasurements(measurements);

   /*m_tideChartView->chart()->removeSeries(m_series);
   m_tideChartView->chart()->removeAxis(m_timeAxis);

   m_timeAxis->setRange(QDateTime::fromMSecsSinceEpoch(m_series->at(0).x()),QDateTime::fromMSecsSinceEpoch(m_series->at(m_series->count() - 1).x()));

   m_tideChartView->chart()->addSeries(m_series);
   m_tideChartView->chart()->createDefaultAxes();

   m_tideChartView->chart()->setAxisX(m_timeAxis,m_series);*/
//}

void CentralWidget::updateSerieData(int row)
{
    if (row == 0){
        m_timeAxis->setMin(QDateTime::fromMSecsSinceEpoch(m_series->at(row).x()));
    }
    if (row == m_series->count() - 1){
        m_timeAxis->setMax(QDateTime::fromMSecsSinceEpoch(m_series->at(row).x()));
    }

}

void CentralWidget::setSeriesData()
{
    //NOTE: Si luego hay problemas es por haber comentariado esto

    //m_tideChartView->chart()->removeSeries(m_series);
    //m_tideChartView->chart()->removeAxis(m_timeAxis);

    m_timeAxis->setRange(QDateTime::fromMSecsSinceEpoch(m_series->at(0).x()),QDateTime::fromMSecsSinceEpoch(m_series->at(m_series->count() - 1).x()));

    //m_tideChartView->chart()->addSeries(m_series);
    //m_tideChartView->chart()->createDefaultAxes();

    //m_tideChartView->chart()->setAxisX(m_timeAxis,m_series);
}

void CentralWidget::settingUpTable()
{
    m_tidalTableView = new QTableView;

    m_tidalTableView->setItemDelegate(new TidalTableDelegate);
    //m_tidalTableView->setModel(m_tidalTableModel);
    m_tidalTableView->setAlternatingRowColors(true);
    //m_tidalTableView->setBackgroundRole(QPalette::Dark);
    //m_tidalTableView->setAutoFillBackground(true);

    /*int width = 20 + m_tidalTableView->verticalHeader()->width();
    for (int i = 0; i < m_tidalTableModel->columnCount(QModelIndex()); ++i){
         width += m_tidalTableView->columnWidth(i);
    }
    m_tidalTableView->setFixedWidth(width);*/
}


