#include "centralwidget.h"
#include "displayeddatalabels.h"
#include "include/ChartModelMapper/xytidalchartmodelmapper.h"
#include "include/PredictionModule/predictormainwindow.h"
#include "include/measurement/measurement.h"
#include <QSlider>
#include <QSpinBox>
#include <QTableView>
#include <iostream>
CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent) {
  m_currentXZoomLevel = 1;
  createComponents();
  setInterfazLayout();
}

/*void CentralWidget::loadDataChart()
{
   //m_tideChart->removeAllSeries();

    m_series->clear();

    QVector<QDateTime> time;

    for (int i = 0; i < m_tidalTableView->rowCount(); ++i){
            time.push_back(QDateTime(m_tidalTableView->item(i,0)->data(Qt::EditRole).toDate(),m_tidalTableView->item(i,1)->data(Qt::EditRole).toTime()));
            //std::cout << i <<" " <<
m_dataTable->item(i,0)->text().toStdString() << " " <<
m_dataTable->item(i,1)->text().toStdString() << " "
<<m_dataTable->item(i,2)->text().toStdString() << std::endl;
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


    //QFile file(filePath);
    //if (file.open(QIODevice::ReadOnly)){
        //QTextStream in(&file);
        //m_edit->setPlainText(in.readAll());
        //file.close();
    //}
    //--------------------------------------------------------------------
    QVector<TidesMeasurement> measurement = readTidesDataFromCVSFile(filePath);
    loadDataInTable(measurement);
    loadDataChart();
}

void CentralWidget::loadDataInTable(const QVector<TidesMeasurement>
&measurements)
{
    m_dataTable->setData(measurements);
}*/

/*void CentralWidget::recieveData(const QVector<QStringList> &data, int
dateField, int timeField, int heightField, const QString &dateFormat, const
QString &timeFormat) //SLOT para conectar con el dialogo de importar datos y asi
cargar los datos al modulo principal.
{
    QVector<TidesMeasurement> measurements;
    for (int i = 0; i < data.size(); ++i){
        if (dateField <= data[i].size() && timeField <= data[i].size() &&
heightField <= data[i].size()){ //Chequea que el campo exista
            //QVariant dateVariant = data[i].at(dateField - 1);
            //QVariant timeVariant = data[i].at(timeField - 1);

            QDate date = QDate::fromString(data[i].at(dateField -
1),dateFormat); QTime time = QTime::fromString(data[i].at(timeField - 1),
timeFormat);

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

   m_timeAxis->setRange(QDateTime::fromMSecsSinceEpoch(m_series->at(0).x()),QDateTime::fromMSecsSinceEpoch(m_series->at(m_series->count()
- 1).x()));

   m_tideChartView->chart()->addSeries(m_series);
   m_tideChartView->chart()->createDefaultAxes();

   m_tideChartView->chart()->setAxisX(m_timeAxis,m_series);*/
//}

void CentralWidget::updateSerieData(int row) {
  if (row == 0) {
    m_timeAxis->setMin(QDateTime::fromMSecsSinceEpoch(m_series->at(row).x()));
  }
  if (row == m_series->count() - 1) {
    m_timeAxis->setMax(QDateTime::fromMSecsSinceEpoch(m_series->at(row).x()));
  }
}

void CentralWidget::setSeriesData() {
  if (!m_tidalTableModel->measurementData().isEmpty()) {
    settingZoomPosibleValues();
    m_zoomYSpinBox->setValue(10);

    m_selectionSeries->clear();
    m_mapForValuesInMainAndSelectionSeries.clear();

    QPointF MinMax = findMinAndMax(m_tidalTableModel->measurementData());
    m_yMin = MinMax.x();
    m_yMax = MinMax.y();
    if (m_yMin != m_yMax) {
      m_yAxis->setRange(m_yMin, m_yMax);
    } else {
      m_yAxis->setRange(m_yMin - 1.0, m_yMin + 1.0);
    }

    QDateTime datetime0(
        m_tidalTableModel->measurementData().first().measurementDateTime());
    QDateTime datetimef(
        m_tidalTableModel->measurementData().last().measurementDateTime());

    QDateTime aux = datetime0.addSecs(24 * 3600);
    if (aux < datetimef) {
      m_timeAxis->setRange(datetime0, aux);
    } else {
      m_timeAxis->setRange(datetime0, datetimef);
    }

    m_series->replace(m_tidalTableModel->measurementDataRealPoints());

  } else {
    m_series->clear();
    m_selectionSeries->clear();
    m_mapForValuesInMainAndSelectionSeries.clear();
  }

  m_selectionPointRange->setText(tr("<b>[Sin Selección]</b>"));
}

void CentralWidget::zoomXAxis(int level) {
  if (m_series) {
    if (m_series->pointsVector().isEmpty())
      return;

    QVector<QPointF> seriesPoints = m_series->pointsVector();

    quint64 xMin = seriesPoints.first().x();
    quint64 xMax = seriesPoints.last().x();

    quint64 showXMin = m_timeAxis->min().toMSecsSinceEpoch();
    quint64 showXMax = m_timeAxis->max().toMSecsSinceEpoch();

    quint64 interval = 24 * 3600 * 1000 * qAbs(level - m_currentXZoomLevel);
    if (m_currentXZoomLevel < level) {
      showXMin -= interval / 2;
      showXMax += interval / 2;

      if (showXMin < xMin) {
        quint64 dif = xMin - showXMin;
        showXMin = xMin;

        showXMax += dif;
        if (showXMax > xMax) {
          showXMax = xMax;
        }
      }

      if (showXMax > xMax) {
        quint64 dif = showXMax - xMax;
        showXMax = xMax;

        showXMin -= dif;
        if (showXMin < xMin) {
          showXMin = xMin;
        }
      }
    } else {
      showXMax -= interval / 2;
      showXMin += interval / 2;

      quint64 dif = showXMax - showXMin;
      quint64 diflimit = 24 * 3600 * 1000;
      if (dif < diflimit) {
        quint64 lim = diflimit - dif;
        showXMin -= lim / 2;
        showXMax += lim / 2;

        if (showXMin < xMin) {
          quint64 dif = xMin - showXMin;
          showXMin = xMin;

          showXMax += dif;
          if (showXMax > xMax) {
            showXMax = xMax;
          }
        }

        if (showXMax > xMax) {
          quint64 dif = showXMax - xMax;
          showXMax = xMax;

          showXMin -= dif;
          if (showXMin < xMin) {
            showXMin = xMin;
          }
        }
      }
    }

    m_currentXZoomLevel = level;
    m_timeAxis->setRange(QDateTime::fromMSecsSinceEpoch(showXMin),
                         QDateTime::fromMSecsSinceEpoch(showXMax));
  }
}

void CentralWidget::getAndDisplayCursorPosInSeries(QPointF point) {
  QPointF seriesPoint = m_tideChart->mapToValue(point, m_series);
  QDateTime time = QDateTime::fromMSecsSinceEpoch(seriesPoint.x());

  m_cursorPosDDLabel->setInternalData(time, seriesPoint.y());
}

void CentralWidget::getAndDisplayClickedPosInSeries(QPointF point) {
  QVector<QPointF> selectedPoints;
  m_mapForValuesInMainAndSelectionSeries.clear();

  m_tidalTableView->clearSelection();

  QVector<QPointF> seriesPointsVector;
  foreach (QPointF p, m_series->pointsVector()) {
    seriesPointsVector.append(m_tideChart->mapToPosition(p, m_series));
  }

  qreal distance = INT64_MAX;            // distancia al punto
  QPointF closest(INT64_MAX, INT64_MAX); // punto mas cercano

  int posInMainSeries = 0;
  int cont = 0;
  foreach (QPointF po, seriesPointsVector) {
    qreal currentDist =
        qSqrt(qPow((po.y() - point.y()), 2) + qPow((po.x() - point.x()), 2));

    if (currentDist < distance) {
      distance = currentDist;
      closest = po;
      posInMainSeries = cont;
    }
    ++cont;
  }
  if (distance <= 5) {
    QPointF selectedPoint = m_tideChart->mapToValue(closest, m_series);
    selectedPoints.append(selectedPoint);
    m_mapForValuesInMainAndSelectionSeries[posInMainSeries] = 0;

    m_tidalTableView->selectRow(posInMainSeries);

    QDateTime time = QDateTime::fromMSecsSinceEpoch(selectedPoint.x());

    m_selectionPointRange->setInternalData(time, selectedPoint.y(), time,
                                           selectedPoint.y());
  } else {
    m_selectionPointRange->setText(tr("<b>[Sin Selección]</b>"));
  }
  m_selectionSeries->replace(selectedPoints);
}

void CentralWidget::setPointSelectedRange(QPointF pPoint, QPointF rPoint) {

  m_mapForValuesInMainAndSelectionSeries.clear();

  QPointF pSeriesPoint = m_tideChart->mapToValue(pPoint, m_series);
  QPointF rSeriesPoint = m_tideChart->mapToValue(rPoint, m_series);

  m_tidalTableView->clearSelection();

  QVector<QPointF> selectedPoints;

  int posInMain = 0;
  int posInSelection = 0;
  foreach (QPointF point, m_series->pointsVector()) {
    if (pSeriesPoint.x() <= rSeriesPoint.x()) {
      if (point.x() >= pSeriesPoint.x() && point.x() <= rSeriesPoint.x()) {
        selectedPoints.append(point);
        m_mapForValuesInMainAndSelectionSeries[posInMain] = posInSelection;
        ++posInSelection;
      }
      if (point.x() > rSeriesPoint.x())
        break;
    } else {
      if (point.x() >= rSeriesPoint.x() && point.x() <= pSeriesPoint.x()) {
        selectedPoints.append(point);
        m_mapForValuesInMainAndSelectionSeries[posInMain] = posInSelection;
        ++posInSelection;
      }
      if (point.x() > pSeriesPoint.x())
        break;
    }
    ++posInMain;
  }

  m_selectionSeries->replace(selectedPoints);

  if (!m_mapForValuesInMainAndSelectionSeries.isEmpty()) {
    int aux1 = m_mapForValuesInMainAndSelectionSeries.keys().first();
    int aux2 = m_mapForValuesInMainAndSelectionSeries.keys().last();
    m_tidalTableView->setRowSelection(0, aux1, 2, aux2,
                                      QItemSelectionModel::Select);
  }
  updateDisplayRangeLabel();
}

void CentralWidget::deleteSelectedPointOnGraph() {
  if (m_selectionSeries->pointsVector().isEmpty())
    return;

  if (m_selectionSeries->count() == 1) {
    QDateTime time =
        QDateTime::fromMSecsSinceEpoch(m_selectionSeries->at(0).x());
    qreal level = m_selectionSeries->at(0).y();
    int desition =
        QMessageBox::question(this, tr("Eliminar Datos"),
                              tr("Se eliminara la medición %1 %2\n"
                                 " ¿Desea continuar?")
                                  .arg(time.toString("yyyy/MM/dd hh:mm"))
                                  .arg(QString::number(level)));
    if (desition == QMessageBox::No)
      return;
    deletePoints();
  } else {
    QDateTime iniTimeRange = QDateTime::fromMSecsSinceEpoch(
        m_selectionSeries->pointsVector().first().x());
    QDateTime endTimeRange = QDateTime::fromMSecsSinceEpoch(
        m_selectionSeries->pointsVector().last().x());

    qreal iniLevelRange = m_selectionSeries->pointsVector().first().y();
    qreal endLevelRange = m_selectionSeries->pointsVector().last().y();

    int desition = QMessageBox::question(
        this, tr("Eliminar Datos"),
        tr("Se eliminara la medición %1 %2 hasta %3 %4\n"
           " ¿Desea continuar?")
            .arg(iniTimeRange.toString("yyyy/MM/dd hh:mm"))
            .arg(QString::number(iniLevelRange))
            .arg(endTimeRange.toString("yyyy/MM/dd hh:mm"))
            .arg(QString::number(endLevelRange)));
    if (desition == QMessageBox::No)
      return;
    deletePoints();
  }
}

void CentralWidget::updateSelectionSeriesData(const QModelIndex &topLeft,
                                              const QModelIndex &bottomRight,
                                              const QVector<int> &roles) {
  Q_UNUSED(roles);

  int topRow = topLeft.row();
  int bottomRow = bottomRight.row();

  if (m_selectionSeries->pointsVector().isEmpty())
    return;

  // QVector<QPointF> selectedPoints = m_selectionSeries->pointsVector();
  for (int i = topRow; i <= bottomRow; ++i) {
    if (m_mapForValuesInMainAndSelectionSeries.contains(i)) {
      qreal y_value = m_series->at(i).y();
      qreal x_value = m_series->at(i).x();

      m_selectionSeries->replace(m_mapForValuesInMainAndSelectionSeries[i],
                                 QPointF(x_value, y_value));
    }
  }
  // m_selectionSeries->replace(selectedPoints);
}

void CentralWidget::updateSeriesData(const QModelIndex &topLeft,
                                     const QModelIndex &bottomRight,
                                     const QVector<int> &roles) {
  // Q_UNUSED(roles);

  int topRow = topLeft.row();
  int bottomRow = bottomRight.row();

  // int firstColumn = topLeft.column();
  // int lastColumn = bottomRight.column();
  for (int i = topRow; i <= bottomRow; ++i) {
    double y_value;
    QDateTime x_value;

    x_value.setDate(
        m_tidalTableModel->data(m_tidalTableModel->index(i, 0), Qt::DisplayRole)
            .toDate());

    x_value.setTime(
        m_tidalTableModel->data(m_tidalTableModel->index(i, 1), Qt::DisplayRole)
            .toTime());

    y_value =
        m_tidalTableModel->data(m_tidalTableModel->index(i, 2), Qt::DisplayRole)
            .toDouble();

    m_series->replace(i, x_value.toMSecsSinceEpoch(), y_value);

    bool isAxisMod = false;

    QPointF MinMax = findMinAndMax(m_tidalTableModel->measurementData());

    if (m_yMin != MinMax.x()) {
      m_yMin = MinMax.x();
      isAxisMod = true;
    }
    if (m_yMax != MinMax.y()) {
      m_yMax = MinMax.y();
      isAxisMod = true;
    }
    if (isAxisMod) {
      m_zoomYSpinBox->setValue(10);
      if (m_yMin != m_yMax) {
        m_yAxis->setRange(m_yMin, m_yMax);
      } else {
        m_yAxis->setRange(m_yMin - 1.0, m_yMax + 1.0);
      }
    }
  }
  updateSelectionSeriesData(topLeft, bottomRight, roles);
}

void CentralWidget::updateSeriesDataAtRowRemove(const QModelIndex &parent,
                                                int in, int last) {
  Q_UNUSED(parent);

  m_series->removePoints(in, last - in +
                                 1); // Elimina los datos de la serie principal

  if (!m_selectionSeries->pointsVector()
           .isEmpty()) { // Update los datos de la series para la seleccion
    int cont = 0;
    int begin = 0;
    QVector<int> pointsMarker;
    bool flag = true;
    for (int i = in; i <= last; ++i) {
      if (m_mapForValuesInMainAndSelectionSeries.contains(i)) {
        if (flag) {
          begin = i;
          flag = false;
        }
        pointsMarker.append(i);
        ++cont;
      }
    }
    if (!cont)
      return; // si no existen coincidencia retorna
    int selectionBeginin = m_mapForValuesInMainAndSelectionSeries[begin];
    // int selectionEnding =
    // m_mapForValuesInMainAndSelectionSeries[storePointForDelete.last()];

    m_selectionSeries->removePoints(selectionBeginin, cont);
    foreach (int mark, pointsMarker) {
      m_mapForValuesInMainAndSelectionSeries.remove(
          mark); // REmueve los puntos del map
    }
  }
}

void CentralWidget::zoomYAxis(int zoomLevel) {
  double scale = 0.0;

  switch (zoomLevel) {
  case 1:
    scale = 0.9;
    break;
  case 2:
    scale = 0.8;
    break;
  case 3:
    scale = 0.7;
    break;
  case 4:
    scale = 0.6;
    break;
  case 5:
    scale = 0.5;
    break;
  case 6:
    scale = 0.4;
    break;
  case 7:
    scale = 0.3;
    break;
  case 8:
    scale = 0.2;
    break;
  case 9:
    scale = 0.1;
    break;
  default:
    scale = 0.0;
    break;
  }

  if (m_series) {
    double minYAxis = m_yMin - scale * (m_yMax - m_yMin);
    double maxYAxis = m_yMax + scale * (m_yMax - m_yMin);

    if (minYAxis < maxYAxis)
      m_yAxis->setRange(minYAxis, maxYAxis);
  }
}

void CentralWidget::updateOnRealTimeSelectionRange(QPointF iniPos,
                                                   QPointF currentPos) {
  QPointF iniPoint;
  QPointF currentPoint;

  if (iniPos.x() <= currentPos.x()) {
    iniPoint = m_tideChart->mapToValue(iniPos, m_series);
    currentPoint = m_tideChart->mapToValue(currentPos, m_series);
  } else {
    iniPoint = m_tideChart->mapToValue(currentPos, m_series);
    currentPoint = m_tideChart->mapToValue(iniPos, m_series);
  }

  QDateTime iniDateTime = QDateTime::fromMSecsSinceEpoch(iniPoint.x());
  qreal iniValue = iniPoint.y();

  QDateTime endDateTime = QDateTime::fromMSecsSinceEpoch(currentPoint.x());
  qreal endValue = currentPoint.y();

  m_selectionPointRange->setInternalData(iniDateTime, iniValue, endDateTime,
                                         endValue);
}

void CentralWidget::selectDataInChart(int row0, int rowf) {
  m_selectionSeries->clear();
  m_mapForValuesInMainAndSelectionSeries.clear();

  if (m_series->pointsVector().isEmpty())
    return;

  int k = 0; // Para la posicion en la serie para seleccion
  for (int i = row0; i <= rowf; ++i) {
    m_selectionSeries->append(m_series->at(i));
    m_mapForValuesInMainAndSelectionSeries[i] = k;
  }
  updateDisplayRangeLabel();
}

void CentralWidget::deselectDataInChart() { m_selectionSeries->clear(); }

void CentralWidget::updateDisplayRangeLabel() {
  if (!m_selectionSeries->pointsVector().isEmpty()) {
    QDateTime iniDateTime = QDateTime::fromMSecsSinceEpoch(
        m_selectionSeries->pointsVector().first().x());
    qreal iniValue = m_selectionSeries->pointsVector().first().y();

    QDateTime endDateTime = QDateTime::fromMSecsSinceEpoch(
        m_selectionSeries->pointsVector().last().x());
    qreal endValue = m_selectionSeries->pointsVector().last().y();

    m_selectionPointRange->setInternalData(iniDateTime, iniValue, endDateTime,
                                           endValue);
  } else {
    m_selectionPointRange->setText(tr("<b>[Sin Selección]</b>"));
  }
}

QPointF CentralWidget::seekMaxAndMinViewYSerieValue(const QDateTime &beg,
                                                    const QDateTime &end) {

  qreal max = -10000000;
  qreal min = 10000000;

  foreach (TidesMeasurement measurement, m_tidalTableModel->measurementData()) {
    if (measurement.measurementDateTime() >= beg &&
        measurement.measurementDateTime() <= end) {
      qreal aux = measurement.seaLevel();
      if (aux > max)
        max = aux;
      if (aux < min)
        min = aux;
    }
    if (measurement.measurementDateTime() > end)
      break;
  }
  return QPointF(min, max);
}

void CentralWidget::createComponents() {

  settingUpTable();

  m_tideChart = new SPMChart;
  m_tideChart->setTheme(QChart::ChartThemeDark);

  // m_tideChart->setAnimationOptions(QChart::AllAnimations);

  m_series = new QSplineSeries;
  m_series->setPointsVisible(true);
  m_series->setName(tr("Serie de Datos"));
  m_series->replace(m_tidalTableModel->measurementDataRealPoints());
  // m_series->setUseOpenGL(true);
  // m_series = new MySeries;
  // m_mapper = new XYTidalChartModelMapper(m_tidalTableModel,m_series);
  connect(m_tidalTableModel, SIGNAL(modelReset()), this, SLOT(setSeriesData()));

  m_selectionSeries = new QScatterSeries;
  // m_selectionSeries->setUseOpenGL(true);
  m_selectionSeries->setMarkerSize(7);
  m_selectionSeries->setName(tr("Selección"));

  m_tideChartView = new customChartView(m_tideChart, this);

  // m_tideChartView->setRubberBand(QChartView::RectangleRubberBand);
  // m_tideChartView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

  m_timeAxis = new QDateTimeAxis;
  m_timeAxis->setFormat("d/M/yy h:mm");

  m_yAxis = new QValueAxis;

  m_tideChart->addSeries(m_series);
  m_tideChart->addSeries(m_selectionSeries);
  m_tideChart->legend()->hide();
  // m_tideChart->createDefaultAxes();

  m_tideChartView->chart()->setAxisX(m_timeAxis, m_selectionSeries);
  m_tideChartView->chart()->setAxisX(m_timeAxis, m_series);
  m_tideChart->setAxisY(m_yAxis, m_series);
  m_tideChart->setAxisY(m_yAxis, m_selectionSeries);
  m_tideChartView->chart()->axisX(m_series)->setTitleText(tr("Fecha & Hora"));
  m_tideChartView->chart()->axisY(m_series)->setTitleText(tr("Nivel [m]"));

  connect(m_tideChartView, SIGNAL(seriesPoint(QPointF)), this,
          SLOT(getAndDisplayCursorPosInSeries(QPointF)));
  connect(m_tideChartView, SIGNAL(seriesPointPressed(QPointF)), this,
          SLOT(getAndDisplayClickedPosInSeries(QPointF)));
  connect(m_tideChartView,
          SIGNAL(seriesPointsPressedAndRealesed(QPointF, QPointF)), this,
          SLOT(setPointSelectedRange(QPointF, QPointF)));
  connect(m_tideChartView, SIGNAL(deleteSelectedPointsOnGraph()), this,
          SLOT(deleteSelectedPointOnGraph()));
  connect(m_tideChartView, SIGNAL(selectionUpdated(QPointF, QPointF)), this,
          SLOT(updateOnRealTimeSelectionRange(QPointF, QPointF)));
  // Display facilities
  m_rangeSlider = new QSlider(Qt::Horizontal, this);
  m_rangeSlider->setFixedWidth(80);
  m_rangeSlider->setTickInterval(1);
  m_rangeSpinBox = new QSpinBox(this);

  m_rangeSlider->setMinimum(1);
  m_rangeSpinBox->setMinimum(1);

  connect(m_rangeSpinBox, SIGNAL(valueChanged(int)), m_rangeSlider,
          SLOT(setValue(int)));
  connect(m_rangeSlider, SIGNAL(valueChanged(int)), m_rangeSpinBox,
          SLOT(setValue(int)));
  connect(m_rangeSpinBox, SIGNAL(valueChanged(int)), this,
          SLOT(zoomXAxis(int)));

  m_zoomYSlider = new QSlider(Qt::Horizontal);
  m_zoomYSlider->setFixedWidth(100);
  m_zoomYSlider->setTickInterval(1);
  m_zoomYSlider->setRange(1, 10);
  m_zoomYSlider->setValue(10);

  m_zoomYSpinBox = new QSpinBox;
  m_zoomYSpinBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  m_zoomYSpinBox->setRange(1, 10);
  m_zoomYSpinBox->setValue(10);

  connect(m_zoomYSlider, &QAbstractSlider::valueChanged, m_zoomYSpinBox,
          &QSpinBox::setValue);
  connect(m_zoomYSpinBox, SIGNAL(valueChanged(int)), m_zoomYSlider,
          SLOT(setValue(int)));
  connect(m_zoomYSpinBox, SIGNAL(valueChanged(int)), this,
          SLOT(zoomYAxis(int)));

  m_cursorPosDDLabel = new DisplayedDataLabels(this);
  QFont labelFont = m_cursorPosDDLabel->font();
  labelFont.setBold(true);
  m_cursorPosDDLabel->setFont(labelFont);
  m_cursorPosDDLabel->setLabel(tr("Cursor"));
  m_cursorPosDDLabel->setFixedWidth(220);
  m_cursorPosDDLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);

  m_selectionPointRange = new SelectionRangeLabel(tr("Selección"), this);
  m_selectionPointRange->setText(tr("<b>[Sin Selección]</b>"));
  m_selectionPointRange->setFixedWidth(370);
  m_selectionPointRange->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);

  // connect(m_dataTable,SIGNAL(rowEliminated(int,int)),this,SLOT(updateDataInChartWhenRowIsEliminated(int,int)));
}

void CentralWidget::setInterfazLayout() {
  // QHBoxLayout *selectionLayout = new QHBoxLayout;
  // selectionLayout->addWidget(m_selectionIniDDLabel);
  // selectionLayout->addWidget(m_selectionEndDDLabel);

  // QGroupBox *selectionGroupBox = new QGroupBox(tr("Seleccion"),this);
  // selectionGroupBox->setAlignment(Qt::AlignCenter);
  // selectionGroupBox->setLayout(selectionLayout);

  // QHBoxLayout *displayLayout = new QHBoxLayout; //Parte de arriba
  // displayLayout->addWidget(selectionGroupBox);
  // displayLayout->addWidget(cursorGroupBox);

  // QGroupBox *displayGroupBox = new QGroupBox;
  // displayGroupBox->setLayout(displayLayout);

  // QHBoxLayout *leftLayout = new QHBoxLayout;
  // leftLayout->addWidget(rangeGroupBox);
  // leftLayout->addWidget(displayGroupBox);

  QHBoxLayout *rangeLayout = new QHBoxLayout; // Parte de Abajo
  rangeLayout->addWidget(m_cursorPosDDLabel);
  rangeLayout->addWidget(m_selectionPointRange);
  rangeLayout->addStretch();
  rangeLayout->addWidget(m_zoomYSlider);
  rangeLayout->addWidget(m_zoomYSpinBox);
  rangeLayout->addWidget(m_rangeSlider);
  rangeLayout->addWidget(m_rangeSpinBox);

  // rangeLayout->setSpacing(0);

  QVBoxLayout *rigthLayout = new QVBoxLayout;
  // rigthLayout->addLayout(leftLayout);
  rigthLayout->addWidget(m_tideChartView);
  rigthLayout->addLayout(rangeLayout);

  QHBoxLayout *mainLayout = new QHBoxLayout;

  mainLayout->addWidget(m_tidalTableView);
  mainLayout->addLayout(rigthLayout);

  this->setLayout(mainLayout);
}

void CentralWidget::settingUpTable() {
  m_tidalTableView = new MyTableView;
  m_tidalTableView->setSelectionMode(QAbstractItemView::ContiguousSelection);
  m_tidalTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
  connect(m_tidalTableView, &MyTableView::rowsSelected, this,
          &CentralWidget::selectDataInChart);
  connect(m_tidalTableView, &MyTableView::noRowsSelected, this,
          &CentralWidget::deselectDataInChart);
  connect(m_tidalTableView, &MyTableView::deleteKeyPressed, this,
          &CentralWidget::deleteSelectedPointOnGraph);

  m_tidalTableModel = new TableModel;
  m_tidalTableView->setItemDelegate(new TidalTableDelegate);
  m_tidalTableView->setModel(m_tidalTableModel);
  m_tidalTableView->setAlternatingRowColors(true);

  connect(m_tidalTableModel,
          SIGNAL(dataChanged(QModelIndex, QModelIndex, QVector<int>)), this,
          SLOT(updateSeriesData(QModelIndex, QModelIndex, QVector<int>)));
  connect(m_tidalTableModel, SIGNAL(rowsRemoved(QModelIndex, int, int)), this,
          SLOT(updateSeriesDataAtRowRemove(QModelIndex, int, int)));

  int width = 20 + m_tidalTableView->verticalHeader()->width();
  for (int i = 0; i < m_tidalTableModel->columnCount(QModelIndex()); ++i) {
    width += m_tidalTableView->columnWidth(i);
  }
  m_tidalTableView->setFixedWidth(width);
  m_tidalTableView->resizeRowsToContents();
  // m_tidalTableView->resizeColumnsToContents();
}

void CentralWidget::settingZoomPosibleValues() {
  m_rangeSpinBox->setValue(1);
  if (!m_tidalTableModel->measurementData().isEmpty()) {
    QDateTime ini =
        m_tidalTableModel->measurementData().first().measurementDateTime();
    QDateTime end =
        m_tidalTableModel->measurementData().last().measurementDateTime();

    quint64 days = ini.daysTo(end);

    m_rangeSpinBox->setMaximum(days + 1);
    m_rangeSlider->setMaximum(days + 1);
  }
}

void CentralWidget::deletePoints() {
  QApplication::setOverrideCursor(Qt::WaitCursor);
  /*int maxFlag = 0;
  int begin = 0;
  bool flag = false;
  int i = 0;
  foreach (QPointF point, m_selectionSeries->pointsVector()){
      QDateTime time = QDateTime::fromMSecsSinceEpoch(point.x());

      for (int k = i; k < m_tidalTableModel->measurementData().size();++k){
          if (m_tidalTableModel->measurementData().at(k).measurementDateTime()
  == time){ //Si coinciden en el tiempo eliminarlos if (!flag){ begin = i; flag
  = true;}  //Para guardar la primera ves que se entra en el loop
              ++maxFlag;
              ++i;
              break;
          }
          ++i;
      }
  }
  m_selectionSeries->clear(); //vacia la serie donde se almacenan los datos
  seleccionados m_mapForValuesInMainAndSelectionSeries.clear();
  m_tidalTableModel->removeRows(begin,maxFlag-1,QModelIndex());
  m_selectionPointRange->setText(tr("<b><font color = green> SIN
  SELECCIÓN</b></font>"));*/

  int begin = m_mapForValuesInMainAndSelectionSeries.keys().first();
  int max = m_mapForValuesInMainAndSelectionSeries.size();

  m_selectionSeries
      ->clear(); // vacia la serie donde se almacenan los datos seleccionados
  m_mapForValuesInMainAndSelectionSeries.clear();

  m_tidalTableModel->removeRows(begin, max - 1, QModelIndex());

  m_selectionPointRange->setText(
      tr("<b><font color = green> SIN SELECCIÓN</b></font>"));

  QPointF MinMax = findMinAndMax(m_tidalTableModel->measurementData());

  bool isAxisMod = false;

  if (m_yMin < MinMax.x()) {
    m_yMin = MinMax.x();
    isAxisMod = true;
  }
  if (m_yMax > MinMax.y()) {
    m_yMax = MinMax.y();
    isAxisMod = true;
  }
  if (isAxisMod) {
    m_zoomYSpinBox->setValue(10);
    if (m_yMin != m_yMax) {
      m_yAxis->setRange(m_yMin, m_yMax);
    } else {
      m_yAxis->setRange(m_yMin - 1.0, m_yMax + 1.0);
    }
  }

  QApplication::restoreOverrideCursor();
}
