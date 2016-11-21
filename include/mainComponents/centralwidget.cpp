#include "centralwidget.h"
#include <QTableView>
#include "include/measurement/measurement.h"
#include "include/ChartModelMapper/xytidalchartmodelmapper.h"
#include "displayeddatalabels.h"
#include <QSpinBox>
#include <QSlider>
#include <iostream>
//TODO: Revisar todo el codigo pues hay que modificarlo.
CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
    m_currentXZoomLevel = 1;
    createComponents();
    setInterfazLayout();
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
    m_mapForValuesInMainAndSelectionSeries.clear();
    m_tideChartView->chart()->removeAxis(m_timeAxis);
    m_tideChartView->chart()->removeAllSeries();

    m_series = new QSplineSeries;
    m_series->setPointsVisible(true);
    m_selectionSeries = new QScatterSeries;
    m_selectionSeries->setMarkerSize(8);
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
    m_tideChartView->chart()->addSeries(m_selectionSeries);
    m_tideChartView->chart()->createDefaultAxes();
    m_tideChartView->chart()->setAxisX(m_timeAxis,m_series);
    m_tideChartView->chart()->setAxisX(m_timeAxis,m_selectionSeries);
    //m_tideChartView->chart()->setAxisX(m_timeAxis,m_scatterSerie);

    //m_mapper->setSeries(m_series);

    QVector<QPointF> Points = m_series->pointsVector();

    int i = 1;
    foreach (QPointF point, Points) {
        std::cout << i << " " << point.x() << " " << point.y() << std::endl;
        ++i;
    }
}

void CentralWidget::zoomXAxis(int level)
{
    if (m_series){
        if (m_series->pointsVector().isEmpty()) return;

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

void CentralWidget::getAndDisplayCursorPosInSeries(QPointF point)
{
    QDateTime time = QDateTime::fromMSecsSinceEpoch(point.x());

    m_cursorPosDDLabel->setInternalData(time,point.y());
}

void CentralWidget::getAndDisplayClickedPosInSeries(QPointF point)
{
    m_selectionSeries->clear();
    m_mapForValuesInMainAndSelectionSeries.clear();

    QVector<QPointF> seriesPointsVector;
    foreach (QPointF p, m_series->pointsVector()) {
        seriesPointsVector.append(m_tideChart->mapToPosition(p,m_series));
    }

    qreal distance = INT64_MAX; //distancia al punto
    QPointF closest(INT64_MAX, INT64_MAX); //punto mas cercano

    int posInMainSeries = 0;
    int cont = 0;
    foreach (QPointF po, seriesPointsVector) {
        qreal currentDist = qSqrt(qPow((po.y() - point.y()),2) + qPow((po.x() - point.x()),2));

        if (currentDist < distance){
            distance = currentDist;
            closest = po;
            posInMainSeries = cont;
        }
        ++cont;
    }
    if (distance <= 5){
        QPointF selectedPoint = m_tideChart->mapToValue(closest,m_series);
        m_selectionSeries->append(selectedPoint);
        m_mapForValuesInMainAndSelectionSeries[posInMainSeries] = 0;

        QDateTime time = QDateTime::fromMSecsSinceEpoch(selectedPoint.x());

        m_selectionIniDDLabel->setInternalData(time,selectedPoint.y());
    }
    /*QVector<QPointF> seriesPointsVector = m_series->pointsVector();

    qreal distance = INT64_MAX; //distancia al punto
    QPointF closest(INT64_MAX, INT64_MAX); //punto mas cercano

    foreach (QPointF po, seriesPointsVector) {
        qreal currentDist = qSqrt(qPow((po.y() - point.y()),2) + qPow((po.x() - point.x()),2));

        if (currentDist < distance){
            distance = currentDist;
            closest = po;
        }
    }
    if (distance < 50000*m_currentXZoomLevel){
        QDateTime time = QDateTime::fromMSecsSinceEpoch(closest.x());

        m_selectionIniDDLabel->setInternalData(time,closest.y());
    }*/
    //std::cout << distance << std::endl;
}

void CentralWidget::setPointSelectedRange(QPointF pPoint, QPointF rPoint)
{
    /*if (m_selectionSeries == Q_NULLPTR){
        m_selectionSeries = new QScatterSeries;
        m_tideChartView->chart()->addSeries(m_selectionSeries);
        m_tideChartView->chart()->setAxisX(m_timeAxis,m_selectionSeries);
    }*/
    m_selectionSeries->clear();
    m_mapForValuesInMainAndSelectionSeries.clear();

    QPointF pSeriesPoint = m_tideChart->mapToValue(pPoint,m_series);
    QPointF rSeriesPoint = m_tideChart->mapToValue(rPoint,m_series);

    int posInMain = 0;
    int posInSelection = 0;
    foreach (QPointF point, m_series->pointsVector()) {
        if (pSeriesPoint.x() <= rSeriesPoint.x()){
            if (point.x() >= pSeriesPoint.x() && point.x() <= rSeriesPoint.x()){
                m_selectionSeries->append(point);
                m_mapForValuesInMainAndSelectionSeries[posInMain] = posInSelection;
                ++posInSelection;
            }
        }else{
            if (point.x() >= rSeriesPoint.x() && point.x() <= pSeriesPoint.x()){
                m_selectionSeries->append(point);
                m_mapForValuesInMainAndSelectionSeries[posInMain] = posInSelection;
                ++posInSelection;
            }

        }
        ++posInMain;
    }

}

void CentralWidget::deleteSelectedPointOnGraph()
{
    if (m_selectionSeries->pointsVector().isEmpty()) return;

    if (m_selectionSeries->count() == 1){
        QDateTime time = QDateTime::fromMSecsSinceEpoch(m_selectionSeries->at(0).x());
        qreal level = m_selectionSeries->at(0).y();
        int desition = QMessageBox::question(this,tr("Eliminar Datos"),tr("Se eliminara la medición %1 %2\n"
                                                           " ¿Desea continuar?").arg(time.toString("yyyy/MM/dd hh:mm")).arg(QString::number(level)));
        if (desition == QMessageBox::No) return;
        deletePoints();
    }else{
        QDateTime iniTimeRange = QDateTime::fromMSecsSinceEpoch(m_selectionSeries->pointsVector().first().x());
        QDateTime endTimeRange = QDateTime::fromMSecsSinceEpoch(m_selectionSeries->pointsVector().last().x());

        qreal iniLevelRange = m_selectionSeries->pointsVector().first().y();
        qreal endLevelRange = m_selectionSeries->pointsVector().last().y();

        int desition = QMessageBox::question(this,tr("Eliminar Datos"),tr("Se eliminara la medición %1 %2 hasta %3 %4\n"
                                                           " ¿Desea continuar?").arg(iniTimeRange.toString("yyyy/MM/dd hh:mm")).arg(QString::number(iniLevelRange)).
                                             arg(endTimeRange.toString("yyyy/MM/dd hh:mm")).arg(QString::number(endLevelRange)));
        if (desition == QMessageBox::No) return;
        deletePoints();
    }


}

void CentralWidget::updateSelectionSeriesData(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    Q_UNUSED(roles);

    int topRow = topLeft.row();
    int bottomRow = bottomRight.row();

    if (m_selectionSeries->pointsVector().isEmpty()) return;

    for (int i = topRow; i <= bottomRow; ++i){
        if (m_mapForValuesInMainAndSelectionSeries.contains(i)){
           qreal y_value = m_series->at(i).y();
           qreal x_value = m_series->at(i).x();

           m_selectionSeries->replace(m_mapForValuesInMainAndSelectionSeries[i],x_value,y_value);
        }
    }
}

void CentralWidget::updateSeriesData(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    //Q_UNUSED(roles);

    int topRow = topLeft.row();
    int bottomRow = bottomRight.row();

    //int firstColumn = topLeft.column();
    //int lastColumn = bottomRight.column();

    for (int i = topRow; i <= bottomRow; ++i){
        double y_value;
        QDateTime x_value;

        x_value.setDate(m_tidalTableModel->data(m_tidalTableModel->index(i,0),
                                      Qt::DisplayRole).toDate());

        x_value.setTime(m_tidalTableModel->data(m_tidalTableModel->index(i,1),
                                      Qt::DisplayRole).toTime());

        y_value = m_tidalTableModel->data(m_tidalTableModel->index(i,2),
                                Qt::DisplayRole).toDouble();


        if (i < m_series->count()){
            m_series->replace(i,x_value.toMSecsSinceEpoch(),y_value);
        }else{
            if (i == m_series->count()){
                m_series->append(x_value.toMSecsSinceEpoch(),y_value);
            }else{
                int k = m_series->count();
                while (k < i){
                    m_series->append(0,0);
                    ++k;
                }
                m_series->append(x_value.toMSecsSinceEpoch(),y_value);
            }
        }

    }
    updateSelectionSeriesData(topLeft,bottomRight,roles);
}

void CentralWidget::updateSeriesDataAtRowRemove(const QModelIndex &parent, int in, int last)
{
    Q_UNUSED(parent);

    m_series->removePoints(in,last-in+1); //Elimina los datos de la serie principal

    if (!m_selectionSeries->pointsVector().isEmpty()){ //Update los datos de la series para la seleccion
        int cont = 0;
        int begin = 0;
        QVector<int> pointsMarker;
        bool flag = true;
        for (int i = in; i <= last; ++i){
            if (m_mapForValuesInMainAndSelectionSeries.contains(i)){
                if (flag) {begin = i; flag = false;}
                pointsMarker.append(i);
                ++cont;
            }
        }
        if (!cont) return; //si no existen coincidencia retorna
        int selectionBeginin = m_mapForValuesInMainAndSelectionSeries[begin];
        //int selectionEnding = m_mapForValuesInMainAndSelectionSeries[storePointForDelete.last()];

        m_selectionSeries->removePoints(selectionBeginin,cont);
        foreach (int mark, pointsMarker) {
            m_mapForValuesInMainAndSelectionSeries.remove(mark); //REmueve los puntos del map
        }
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
    //m_mapper = new XYTidalChartModelMapper(m_tidalTableModel,m_series);
    connect(m_tidalTableModel,SIGNAL(modelReset()),this,SLOT(setSeriesData()));

    m_selectionSeries = new QScatterSeries;
    m_selectionSeries->setMarkerSize(8);

    m_tideChartView = new customChartView(m_tideChart,this);

    //m_tideChartView->setRubberBand(QChartView::RectangleRubberBand);
    //m_tideChartView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    m_timeAxis = new QDateTimeAxis;
    m_timeAxis->setFormat("d/M/yy h:mm");

    //NOTE: Valorar Remover esto
    m_tideChart->addSeries(m_series);
    m_tideChart->addSeries(m_selectionSeries);
    m_tideChart->createDefaultAxes();

    m_tideChartView->chart()->setAxisX(m_timeAxis,m_selectionSeries);
    m_tideChartView->chart()->setAxisX(m_timeAxis,m_series);
    m_tideChartView->chart()->axisX(m_series)->setTitleText(tr("Tiempo"));
    m_tideChartView->chart()->axisY(m_series)->setTitleText(tr("Nivel"));

    connect(m_tideChartView,SIGNAL(seriesPoint(QPointF)),this,SLOT(getAndDisplayCursorPosInSeries(QPointF)));
    connect(m_tideChartView,SIGNAL(seriesPointPressed(QPointF)),this,SLOT(getAndDisplayClickedPosInSeries(QPointF)));
    connect(m_tideChartView,SIGNAL(seriesPointsPressedAndRealesed(QPointF,QPointF)),this,SLOT(setPointSelectedRange(QPointF,QPointF)));
    connect(m_tideChartView,SIGNAL(deleteSelectedPointsOnGraph()),this,SLOT(deleteSelectedPointOnGraph()));
    //Display facilities
    m_rangeSlider =  new QSlider(Qt::Horizontal,this);
    m_rangeSpinBox = new QSpinBox(this);

    m_rangeSlider->setMinimum(1);
    m_rangeSpinBox->setMinimum(1);

    connect(m_rangeSpinBox,SIGNAL(valueChanged(int)),m_rangeSlider,SLOT(setValue(int)));
    connect(m_rangeSlider,SIGNAL(valueChanged(int)),m_rangeSpinBox,SLOT(setValue(int)));
    connect(m_rangeSpinBox,SIGNAL(valueChanged(int)),this,SLOT(zoomXAxis(int)));

    //QGroupBox *rangeGroupBox = new QGroupBox(this);
    //rangeGroupBox->setLayout(rangeLayout);
    //rangeGroupBox->setFixedWidth(200);

    m_selectionIniDDLabel = new DisplayedDataLabels(this);
    m_selectionIniDDLabel->setLabel(tr("Seleccion"));
    m_selectionIniDDLabel->setFixedWidth(200);
    m_selectionIniDDLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);

    m_selectionEndDDLabel = new DisplayedDataLabels(this);
    m_selectionEndDDLabel->setLabel(tr("Fin"));

    m_cursorPosDDLabel = new DisplayedDataLabels(this);
    m_cursorPosDDLabel->setLabel(tr("Cursor"));
    m_cursorPosDDLabel->setFixedWidth(200);
    m_cursorPosDDLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);

    //QHBoxLayout *cursorLayout =  new QHBoxLayout;
    //cursorLayout->addWidget(m_cursorPosDDLabel);

    //QGroupBox *cursorGroupBox = new QGroupBox(tr("Cursor"),this);
    //cursorGroupBox->setAlignment(Qt::AlignCenter);
    //cursorGroupBox->setLayout(cursorLayout);




    //Connections

    //connect(m_dataTable,SIGNAL(rowEliminated(int,int)),this,SLOT(updateDataInChartWhenRowIsEliminated(int,int)));
}

void CentralWidget::setInterfazLayout()
{
    QHBoxLayout *selectionLayout = new QHBoxLayout;
    //selectionLayout->addWidget(m_selectionIniDDLabel);
    selectionLayout->addWidget(m_selectionEndDDLabel);

    QGroupBox *selectionGroupBox = new QGroupBox(tr("Seleccion"),this);
    selectionGroupBox->setAlignment(Qt::AlignCenter);
    selectionGroupBox->setLayout(selectionLayout);

    QHBoxLayout *displayLayout = new QHBoxLayout; //Parte de arriba
    displayLayout->addWidget(selectionGroupBox);
    //displayLayout->addWidget(cursorGroupBox);

    QGroupBox *displayGroupBox = new QGroupBox;
    displayGroupBox->setLayout(displayLayout);

    QHBoxLayout *leftLayout = new QHBoxLayout;
    //leftLayout->addWidget(rangeGroupBox);
    leftLayout->addWidget(displayGroupBox);

    QHBoxLayout *rangeLayout = new QHBoxLayout; //Parte de Abajo
    rangeLayout->addWidget(m_cursorPosDDLabel);
    rangeLayout->addWidget(m_selectionIniDDLabel);
    rangeLayout->addWidget(m_rangeSlider);
    rangeLayout->addWidget(m_rangeSpinBox);

    //rangeLayout->setSpacing(0);

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
}

void CentralWidget::settingUpTable()
{
    m_tidalTableView = new QTableView;
    m_tidalTableModel = new TableModel;
    m_tidalTableView->setItemDelegate(new TidalTableDelegate);
    m_tidalTableView->setModel(m_tidalTableModel);
    m_tidalTableView->setAlternatingRowColors(true);

    connect(m_tidalTableModel,SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),this,SLOT(updateSeriesData(QModelIndex,QModelIndex,QVector<int>)));
    connect(m_tidalTableModel,SIGNAL(rowsRemoved(QModelIndex,int,int)),this,SLOT(updateSeriesDataAtRowRemove(QModelIndex,int,int)));
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

void CentralWidget::deletePoints()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    int maxFlag = 0;
    int begin = 0;
    bool flag = false;
    //m_tideChartView->chart()->removeSeries(m_series);
    //m_tideChartView->chart()->removeSeries(m_selectionSeries);
    foreach (QPointF point, m_selectionSeries->pointsVector()){
        QDateTime time = QDateTime::fromMSecsSinceEpoch(point.x());
        int i = 0;
        //QVector<TidesMeasurement> dataMeasurement = m_tidalTableModel->measurementData();
        foreach (TidesMeasurement measu, m_tidalTableModel->measurementData()) { //Paracomparar elementos
            if (measu.measurementDateTime() == time){ //Si coinciden en el tiempo eliminarlos
                if (!flag){ begin = i; flag = true;}  //Para guardar la primera ves que se entra en el loop
                ++maxFlag;
                //m_tidalTableModel->removeRow(i,QModelIndex());
                //m_series->remove(point);
                //++flag;
                break;
            }
             ++i;
        }
    }
    m_selectionSeries->clear(); //vacia la serie donde se almacenan los datos seleccionados
    m_mapForValuesInMainAndSelectionSeries.clear();
    m_tidalTableModel->removeRows(begin,maxFlag,QModelIndex());
    //m_tideChartView->chart()->addSeries(m_series);
    //m_tideChartView->chart()->addSeries(m_selectionSeries);

    //m_tideChartView->chart()->setAxisX(m_timeAxis,m_series);
    //m_tideChartView->chart()->setAxisX(m_timeAxis,m_selectionSeries);

    //m_series->clear();
    //m_series->append(m_tidalTableModel->measurementDataRealPoints().toList());
    QApplication::restoreOverrideCursor();
}


