#include "centralwidget.h"
#include <QTableView>
#include "include/measurement/measurement.h"
#include "include/ChartModelMapper/xytidalchartmodelmapper.h"
#include "displayeddatalabels.h"
#include <QSpinBox>
#include <QSlider>
//TODO: Revisar todo el codigo pues hay que modificarlo.

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
    m_currentXZoomLevel = 1;
    createComponents();
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

   m_tideChartView->chart()->removeSeries(m_series);
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
    settingZoomPosibleValues();
    //NOTE: Si luego hay problemas es por haber comentariado esto
    m_series->clear();
    m_tideChartView->chart()->removeAxis(m_timeAxis);
    m_tideChartView->chart()->removeAllSeries();

    m_series = new QSplineSeries;
    m_series->setPointsVisible(true);
    //m_scatterSerie = new QScatterSeries;
    //m_scatterSerie->setColor(Qt::red);
    //m_scatterSerie->setMarkerSize(5);
    //m_series = new MySeries;

    int rowNumber = m_tidalTableModel->rowCount(QModelIndex());
    //int columnNumber = m_model->columnCount(QModelIndex());

    QList<QPointF> datos;
    for (int i = 0; i < rowNumber; ++i){
        double y_value;
        QDateTime x_value;
        x_value.setDate(m_tidalTableModel->measurementData().at(i).measurementDate());
        x_value.setTime(m_tidalTableModel->measurementData().at(i).measurementTime());
        y_value = m_tidalTableModel->measurementData().at(i).seaLevel();

        datos.append(QPointF(x_value.toMSecsSinceEpoch(),y_value));
    }

    //m_series->chart()->axisX(m_series)->setRange(QDateTime::fromMSecsSinceEpoch(datos.first().x()),QDateTime::fromMSecsSinceEpoch(datos.last().x()));
    m_series->append(datos);
    //m_scatterSerie->append(datos);


    //m_tideChartView->chart()->removeSeries(m_series);
    //m_tideChartView->chart()->removeAxis(m_timeAxis);

    m_timeAxis->setRange(QDateTime::fromMSecsSinceEpoch(m_series->at(0).x()),QDateTime::fromMSecsSinceEpoch(m_series->at(0).x() + 24*3600*1000));

    //m_tideChartView->chart()->addSeries(m_series);
    //m_tideChartView->chart()->createDefaultAxes();

    m_tideChartView->chart()->addSeries(m_series);
    m_tideChartView->chart()->createDefaultAxes();
    m_tideChartView->chart()->setAxisX(m_timeAxis,m_series);
    //m_tideChartView->chart()->setAxisX(m_timeAxis,m_scatterSerie);

    m_mapper->setSeries(m_series);


}

void CentralWidget::zoomXAxis(int level)
{
    if (m_series){
        quint64 xMin = m_series->at(0).x();
        quint64 xMax = m_series->at(m_series->count()-1).x();

        quint64 showXMin = m_timeAxis->min().toMSecsSinceEpoch();
        quint64 showXMax = m_timeAxis->max().toMSecsSinceEpoch();

        quint64 interval = 24*3600*1000*qAbs(level-m_currentXZoomLevel);
        if (m_currentXZoomLevel < level){
            showXMin-=interval/2;
            showXMax+=interval/2;

            if (showXMin < xMin){
                quint64 dif = xMin - showXMin;
                showXMin = xMin;

                showXMax+=dif;
                if (showXMax > xMax){
                    showXMax = xMax;
                }
            }

            if (showXMax > xMax){
                quint64 dif = showXMax - xMax;
                showXMax = xMax;

                showXMin-=dif;
                if (showXMin < xMin){
                    showXMin = xMin;
                }
            }
        }else{
            showXMax-=interval/2;
            showXMin+=interval/2;

            quint64 dif = showXMax - showXMin;
            quint64 diflimit = 24*3600*1000;
            if (dif < diflimit){
                quint64 lim = diflimit - dif;
                showXMin-=lim/2;
                showXMax+=lim/2;

                if (showXMin < xMin){
                    quint64 dif = xMin - showXMin;
                    showXMin = xMin;

                    showXMax+=dif;
                    if (showXMax > xMax){
                        showXMax = xMax;
                    }
                }

                if (showXMax > xMax){
                    quint64 dif = showXMax - xMax;
                    showXMax = xMax;

                    showXMin-=dif;
                    if (showXMin < xMin){
                        showXMin = xMin;
                    }
                }

            }
        }

        m_currentXZoomLevel = level;
        m_timeAxis->setRange(QDateTime::fromMSecsSinceEpoch(showXMin),QDateTime::fromMSecsSinceEpoch(showXMax));
    }
}
void CentralWidget::createComponents()
{
    //QVector<TidesMeasurement> measurement = readTidesDataFromCVSFile("files/prueba7.csv"); //NOTE: probando remover despues
    //m_dataTable = new TidesDataTable(this);

    //m_tidalTableModel = new ReadOnlyTableModel;

    settingUpTable();

    //TODO: BUSCAR COMO ORDENAR ESTO

    m_tideChart = new SPMChart;
    m_tideChart->setTheme(QChart::ChartThemeDark);

    //m_tideChart->setAnimationOptions(QChart::AllAnimations);

    m_series = new QSplineSeries;
    //m_series = new MySeries;
    m_mapper = new XYTidalChartModelMapper(m_tidalTableModel,m_series);
    connect(m_tidalTableModel,SIGNAL(modelReset()),this,SLOT(setSeriesData()));


    m_tideChartView = new customChartView(m_tideChart,this);

    //m_tideChartView->setRubberBand(QChartView::RectangleRubberBand);
    //m_tideChartView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    m_timeAxis = new QDateTimeAxis;
    m_timeAxis->setFormat("d/M/yy h:mm");

    //NOTE: Valorar Remover esto
    m_tideChart->addSeries(m_series);
    m_tideChart->createDefaultAxes();

    m_tideChartView->chart()->setAxisX(m_timeAxis,m_series);

    m_tideChartView->chart()->axisX(m_series)->setTitleText(tr("Tiempo"));


    //Display facilities
    m_rangeSlider =  new QSlider(Qt::Horizontal,this);
    m_rangeSpinBox = new QSpinBox(this);

    m_rangeSlider->setMinimum(1);
    m_rangeSpinBox->setMinimum(1);

    connect(m_rangeSpinBox,SIGNAL(valueChanged(int)),m_rangeSlider,SLOT(setValue(int)));
    connect(m_rangeSlider,SIGNAL(valueChanged(int)),m_rangeSpinBox,SLOT(setValue(int)));
    connect(m_rangeSpinBox,SIGNAL(valueChanged(int)),this,SLOT(zoomXAxis(int)));

    QHBoxLayout *rangeLayout = new QHBoxLayout;
    rangeLayout->addWidget(m_rangeSlider);
    rangeLayout->addWidget(m_rangeSpinBox);
    rangeLayout->setSpacing(0);

    //QGroupBox *rangeGroupBox = new QGroupBox(this);
    //rangeGroupBox->setLayout(rangeLayout);
    //rangeGroupBox->setFixedWidth(200);

    m_selectionIniDDLabel = new DisplayedDataLabels(this);
    m_selectionIniDDLabel->setLabel(tr("Inicio"));
    m_selectionEndDDLabel = new DisplayedDataLabels(this);
    m_selectionEndDDLabel->setLabel(tr("Fin"));

    QHBoxLayout *selectionLayout = new QHBoxLayout;
    selectionLayout->addWidget(m_selectionIniDDLabel);
    selectionLayout->addWidget(m_selectionEndDDLabel);

    QGroupBox *selectionGroupBox = new QGroupBox(tr("Seleccion"),this);
    selectionGroupBox->setAlignment(Qt::AlignCenter);
    selectionGroupBox->setLayout(selectionLayout);

    m_cursorPosDDLabel = new DisplayedDataLabels(this);
    m_cursorPosDDLabel->setLabel(tr("Posicion"));

    QHBoxLayout *cursorLayout =  new QHBoxLayout;
    cursorLayout->addWidget(m_cursorPosDDLabel);

    QGroupBox *cursorGroupBox = new QGroupBox(tr("Cursor"),this);
    cursorGroupBox->setAlignment(Qt::AlignCenter);
    cursorGroupBox->setLayout(cursorLayout);

    QHBoxLayout *displayLayout = new QHBoxLayout;
    displayLayout->addWidget(selectionGroupBox);
    displayLayout->addWidget(cursorGroupBox);

    QGroupBox *displayGroupBox = new QGroupBox;
    displayGroupBox->setLayout(displayLayout);

    QHBoxLayout *leftLayout = new QHBoxLayout;
    //leftLayout->addWidget(rangeGroupBox);
    leftLayout->addWidget(displayGroupBox);

    QVBoxLayout *rigthLayout = new QVBoxLayout;
    rigthLayout->addLayout(leftLayout);
    rigthLayout->addWidget(m_tideChartView);
    rigthLayout->addLayout(rangeLayout);

    QHBoxLayout *mainLayout = new QHBoxLayout;

    mainLayout->addWidget(m_tidalTableView);
    //QVBoxLayout *rigthLayout = new QVBoxLayout; //NOTE: Probando el edit
    //m_edit = new QPlainTextEdit(this);                                //NOTE: creando el edit
    //rigthLayout->addWidget(m_tideChartView);
    //rigthLayout->addWidget(m_edit);
    mainLayout->addLayout(rigthLayout);

    this->setLayout(mainLayout);

    //Connections

    //connect(m_dataTable,SIGNAL(rowEliminated(int,int)),this,SLOT(updateDataInChartWhenRowIsEliminated(int,int)));
}

void CentralWidget::settingUpTable()
{
    m_tidalTableView = new QTableView;
    m_tidalTableModel = new ReadOnlyTableModel;
    m_tidalTableView->setItemDelegate(new TidalTableDelegate);
    m_tidalTableView->setModel(m_tidalTableModel);
    m_tidalTableView->setAlternatingRowColors(true);

    int width = 20 + m_tidalTableView->verticalHeader()->width();
    for (int i = 0; i < m_tidalTableModel->columnCount(QModelIndex()); ++i){
         width += m_tidalTableView->columnWidth(i);
    }
    m_tidalTableView->setFixedWidth(width);
}

void CentralWidget::settingZoomPosibleValues()
{
    m_rangeSpinBox->setValue(1);
    if (!m_tidalTableModel->measurementData().isEmpty()){
       QDateTime ini = m_tidalTableModel->measurementData().first().measurementDateTime();
       QDateTime end = m_tidalTableModel->measurementData().last().measurementDateTime();

       quint64 days= ini.daysTo(end);

       m_rangeSpinBox->setMaximum(days + 1);
       m_rangeSlider->setMaximum(days + 1);
    }

}


