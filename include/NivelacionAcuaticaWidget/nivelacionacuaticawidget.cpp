#include "nivelacionacuaticawidget.h"
#include "../nivelacion_acuatica_calculo.h"

NivelacionAcuaticaWidget::NivelacionAcuaticaWidget(
    const QVector<TidesMeasurement> &data, QWidget *parent)
    : QWidget(parent), m_mainFormData(data) {
  createComponents();
  m_provDataLoadFlag = false;
  m_perm1DataLoadFlag = false;
  m_perm2DataLoadFlag = false;

  m_loadDialog = Q_NULLPTR;
  m_manualDataIntroWidget = Q_NULLPTR;

  connect(m_puestoProvImportButton, SIGNAL(clicked(bool)), this,
          SLOT(createProvDataLoadDialog()));
  connect(m_puestoPerm1ImportButton, SIGNAL(clicked(bool)), this,
          SLOT(createPerm1DataLoadDialog()));
  connect(m_puestoPerm2ImportButton, SIGNAL(clicked(bool)), this,
          SLOT(createPerm2DataLoadDialog()));

  connect(m_puestoProvManualButton, SIGNAL(clicked(bool)), this,
          SLOT(createProvManualDataIntro()));
  connect(m_puestoPerm1ManualButton, SIGNAL(clicked(bool)), this,
          SLOT(createPerm1ManualDataIntro()));
  connect(m_puestoPerm2ManualButton, SIGNAL(clicked(bool)), this,
          SLOT(createPerm2ManualDataIntro()));

  connect(m_puestoProvGetButton, SIGNAL(clicked(bool)), this,
          SLOT(importProvDataFromMain()));
  connect(m_puestoPerm1GetButton, SIGNAL(clicked(bool)), this,
          SLOT(importPerm1DataFromMain()));
  connect(m_puestoPerm2GetButton, SIGNAL(clicked(bool)), this,
          SLOT(importPerm2DataFromMain()));

  connect(m_metodoComboBox, SIGNAL(currentIndexChanged(int)), this,
          SLOT(setMetodoDeNivelacion(int)));

  setWindowTitle(tr("Nivelación Acuática"));
  setWindowIcon(QIcon(":images/nivelacion_acuatica.png"));
  setWindowState(Qt::WindowMaximized);
  setAttribute(Qt::WA_DeleteOnClose);
}

void NivelacionAcuaticaWidget::createProvDataLoadDialog() {
  m_provDataLoadFlag = true;
  m_perm1DataLoadFlag = false;
  m_perm2DataLoadFlag = false;

  createLoadDialog();
}

void NivelacionAcuaticaWidget::createPerm1DataLoadDialog() {
  m_provDataLoadFlag = false;
  m_perm1DataLoadFlag = true;
  m_perm2DataLoadFlag = false;

  createLoadDialog();
}

void NivelacionAcuaticaWidget::createPerm2DataLoadDialog() {
  m_provDataLoadFlag = false;
  m_perm1DataLoadFlag = false;
  m_perm2DataLoadFlag = true;

  createLoadDialog();
}

void NivelacionAcuaticaWidget::createProvManualDataIntro() {
  m_provDataLoadFlag = true;
  m_perm1DataLoadFlag = false;
  m_perm2DataLoadFlag = false;

  createManualDataIntroWidget();
}

void NivelacionAcuaticaWidget::createPerm1ManualDataIntro() {
  m_provDataLoadFlag = false;
  m_perm1DataLoadFlag = true;
  m_perm2DataLoadFlag = false;

  createManualDataIntroWidget();
}

void NivelacionAcuaticaWidget::createPerm2ManualDataIntro() {
  m_provDataLoadFlag = false;
  m_perm1DataLoadFlag = false;
  m_perm2DataLoadFlag = true;

  createManualDataIntroWidget();
}

void NivelacionAcuaticaWidget::importProvDataFromMain() {
  m_provDataLoadFlag = true;
  m_perm1DataLoadFlag = false;
  m_perm2DataLoadFlag = false;

  importDataFromMainForm();
}

void NivelacionAcuaticaWidget::importPerm1DataFromMain() {
  m_provDataLoadFlag = false;
  m_perm1DataLoadFlag = true;
  m_perm2DataLoadFlag = false;

  importDataFromMainForm();
}

void NivelacionAcuaticaWidget::importPerm2DataFromMain() {
  m_provDataLoadFlag = false;
  m_perm1DataLoadFlag = false;
  m_perm2DataLoadFlag = true;

  importDataFromMainForm();
}

void NivelacionAcuaticaWidget::beginDataExtrationFromFile() {
  if (m_provDataLoadFlag) {
    m_dataTableModel->setPuestoProvisionalDataSet(
        m_loadDialog->measurementsData());
    m_puestoProvSerie->replace(m_dataTableModel->puestoProvDataForGraph());
    setPuestoProvAxis();
    m_loadDialog->close();
    return;
  }

  if (m_perm1DataLoadFlag) {
    m_dataTableModel->setPuestoPermanente1DataSet(
        m_loadDialog->measurementsData());
    m_puestoPerm1Serie->replace(m_dataTableModel->puestoPerm1DataForGraph());
    setPuestoPerm1Axis();
    m_loadDialog->close();
    return;
  }

  if (m_perm2DataLoadFlag) {
    m_dataTableModel->setPuestoPermanente2DataSet(
        m_loadDialog->measurementsData());
    m_puestoPerm2Serie->replace(m_dataTableModel->puestoPerm2DataForGraph());
    setPuestoPerm2Axis();
    m_loadDialog->close();
    return;
  }
}

void NivelacionAcuaticaWidget::appendDataFromFile() {
  if (m_provDataLoadFlag) {
    QVector<TidesMeasurement> measurement = m_dataTableModel->puestoProvData();
    measurement.append(m_loadDialog->measurementsData());
    m_dataTableModel->setPuestoProvisionalDataSet(measurement);
    m_puestoProvSerie->replace(m_dataTableModel->puestoProvDataForGraph());
    setPuestoProvAxis();
    m_loadDialog->close();
    return;
  }

  if (m_perm1DataLoadFlag) {
    QVector<TidesMeasurement> measurement = m_dataTableModel->puestoPerm1Data();
    measurement.append(m_loadDialog->measurementsData());
    m_dataTableModel->setPuestoPermanente1DataSet(measurement);
    m_puestoPerm1Serie->replace(m_dataTableModel->puestoPerm1DataForGraph());
    setPuestoPerm1Axis();
    m_loadDialog->close();
    return;
  }

  if (m_perm2DataLoadFlag) {
    QVector<TidesMeasurement> measurement = m_dataTableModel->puestoPerm2Data();
    measurement.append(m_loadDialog->measurementsData());
    m_dataTableModel->setPuestoPermanente2DataSet(measurement);
    m_puestoPerm2Serie->replace(m_dataTableModel->puestoPerm2DataForGraph());
    setPuestoPerm2Axis();
    m_loadDialog->close();
    return;
  }
}

void NivelacionAcuaticaWidget::beginDataExtration() {
  QVector<TidesMeasurement> datos;

  int size = m_manualDataIntroWidget->model()->measurementData().size();

  qreal conversion = m_manualDataIntroWidget->conversionUnit();

  for (int i = 0; i < size; ++i) {
    if (m_manualDataIntroWidget->model()->measurementData().at(i).isValid()) {

      datos.push_back(
          m_manualDataIntroWidget->model()->measurementData().at(i));

      if (conversion != 1.0) {
        qreal value = m_manualDataIntroWidget->model()
                          ->measurementData()
                          .at(i)
                          .seaLevel() *
                      conversion;
        datos[i].setSeaLevel(value);
      }
    }
  }

  /*m_metadataStorage.setProjectName(m_manualDataIntroductionWidget->projectName());
  m_metadataStorage.setStationName(m_manualDataIntroductionWidget->stationName());
  m_metadataStorage.setLocalizationName(m_manualDataIntroductionWidget->localizationName());
  m_metadataStorage.setCeroPuesto(m_manualDataIntroductionWidget->ceroPuesto());
  m_metadataStorage.setCeroUnits(m_manualDataIntroductionWidget->ceroUnit());
  m_metadataStorage.setNivelReferencia(m_manualDataIntroductionWidget->nivelReferencia());
  m_metadataStorage.setReferenceUnits(m_manualDataIntroductionWidget->referenceUnit());
  m_metadataStorage.setLatitud(m_manualDataIntroductionWidget->latitud());
  m_metadataStorage.setLongitud(m_manualDataIntroductionWidget->longitud());
  m_metadataStorage.setEquipmentID(m_manualDataIntroductionWidget->equipmentID());*/

  if (m_provDataLoadFlag) {
    m_dataTableModel->setPuestoProvisionalDataSet(datos);
    m_puestoProvSerie->replace(m_dataTableModel->puestoProvDataForGraph());
    setPuestoProvAxis();
    m_manualDataIntroWidget->close();
    return;
  }

  if (m_perm1DataLoadFlag) {
    m_dataTableModel->setPuestoPermanente1DataSet(datos);
    m_puestoPerm1Serie->replace(m_dataTableModel->puestoPerm1DataForGraph());
    setPuestoPerm1Axis();
    m_manualDataIntroWidget->close();
    return;
  }

  if (m_perm2DataLoadFlag) {
    m_dataTableModel->setPuestoPermanente2DataSet(datos);
    m_puestoPerm1Serie->replace(m_dataTableModel->puestoPerm2DataForGraph());
    setPuestoPerm2Axis();
    m_manualDataIntroWidget->close();
    return;
  }
}

void NivelacionAcuaticaWidget::appendDataFromManual() {
  QVector<TidesMeasurement> datos;

  int size = m_manualDataIntroWidget->model()->measurementData().size();

  qreal conversion = m_manualDataIntroWidget->conversionUnit();

  for (int i = 0; i < size; ++i) {
    if (m_manualDataIntroWidget->model()->measurementData().at(i).isValid()) {

      datos.push_back(
          m_manualDataIntroWidget->model()->measurementData().at(i));

      if (conversion != 1.0) {
        qreal value = m_manualDataIntroWidget->model()
                          ->measurementData()
                          .at(i)
                          .seaLevel() *
                      conversion;
        datos[i].setSeaLevel(value);
      }
    }
  }

  if (m_provDataLoadFlag) {
    QVector<TidesMeasurement> measurement = m_dataTableModel->puestoProvData();
    measurement.append(datos);
    m_dataTableModel->setPuestoProvisionalDataSet(measurement);
    m_puestoProvSerie->replace(m_dataTableModel->puestoProvDataForGraph());
    setPuestoProvAxis();
    m_manualDataIntroWidget->close();
    return;
  }

  if (m_perm1DataLoadFlag) {
    QVector<TidesMeasurement> measurement = m_dataTableModel->puestoPerm1Data();
    measurement.append(datos);
    m_dataTableModel->setPuestoPermanente1DataSet(measurement);
    m_puestoPerm1Serie->replace(m_dataTableModel->puestoPerm1DataForGraph());
    setPuestoPerm1Axis();
    m_manualDataIntroWidget->close();
    return;
  }

  if (m_perm2DataLoadFlag) {
    QVector<TidesMeasurement> measurement = m_dataTableModel->puestoPerm2Data();
    measurement.append(datos);
    m_dataTableModel->setPuestoPermanente2DataSet(measurement);
    m_puestoPerm1Serie->replace(m_dataTableModel->puestoPerm2DataForGraph());
    setPuestoPerm2Axis();
    m_manualDataIntroWidget->close();
    return;
  }
}

void NivelacionAcuaticaWidget::importDataFromMainForm() {
  if (m_provDataLoadFlag) {
    m_dataTableModel->setPuestoProvisionalDataSet(m_mainFormData);
    m_puestoProvSerie->replace(m_dataTableModel->puestoProvDataForGraph());
    setPuestoProvAxis();
    return;
  }

  if (m_perm1DataLoadFlag) {
    m_dataTableModel->setPuestoPermanente1DataSet(m_mainFormData);
    m_puestoPerm1Serie->replace(m_dataTableModel->puestoPerm1DataForGraph());
    setPuestoPerm1Axis();
    return;
  }

  if (m_perm2DataLoadFlag) {
    m_dataTableModel->setPuestoPermanente2DataSet(m_mainFormData);
    m_puestoPerm1Serie->replace(m_dataTableModel->puestoPerm2DataForGraph());
    setPuestoPerm2Axis();
    return;
  }
}

void NivelacionAcuaticaWidget::setMetodoDeNivelacion(int index) {
  switch (index) {
  case 0:
    m_puestoPerm2DataLoadFrame->setEnabled(false);
    m_puestoPerm1Serie->setName("Puesto Permanente");
    if (m_chart->series().contains(m_puestoPerm2Serie))
      m_chart->removeSeries(m_puestoPerm2Serie);
    if (m_chart->axes().contains(m_puestoPerm2YAxis))
      m_puestoPerm2YAxis->hide();
    break;
  case 1:
    m_puestoPerm2DataLoadFrame->setEnabled(true);
    m_puestoPerm1Serie->setName(tr("Puesto Permanente #1"));
    m_chart->addSeries(m_puestoPerm2Serie);
    m_puestoPerm2YAxis->show();
    if (m_chart->axisX(m_puestoPerm2Serie) != m_dateTimeXAxis) {
      m_chart->setAxisX(m_dateTimeXAxis, m_puestoPerm2Serie);
    }
    break;
  default:
    break;
  }

  m_dataTableModel->setMetododeNivelacion(index);
}

void NivelacionAcuaticaWidget::calculate() {
  if (m_metodoComboBox->currentIndex() == 0) {
    // Metodo de un puesto de nivel

    // Checking data time relation;
    bool okToCalculate = true;
    foreach (const TidesMeasurement &measurement,
             m_dataTableModel->diffPProvPuestoPerm1()) {
      if (!measurement.isValid()) {
        okToCalculate = false;
        QMessageBox::information(
            this, tr("Info"),
            tr("Los mediciones del Puesto Provicional y del"
               "Puesto Permanente no son simultaneas"));
        break;
      }
    }
    if (okToCalculate) { // calculate
      calculateMetodoDeUnPuestoPermanente();
    }
  }
  if (m_metodoComboBox->currentIndex() == 1) {
    // Metodo de 2 puestos de nivel

    // Checking data time relation;
    bool okToCalculate = true;

    for (int i = 0; i < m_dataTableModel->puestoPerm1Data().size(); ++i) {
      if (!m_dataTableModel->diffPProvPuestoPerm1().at(i).isValid() ||
          !m_dataTableModel->diffPProvPuestoPerm2().at(i).isValid()) {
        okToCalculate = false;

        QMessageBox::information(
            this, tr("Info"),
            tr("Los mediciones del Puesto Provicional y la/s del"
               "Puesto Permanente #1 y Puesto Permanente #2 no son"
               " simultaneas"));
        break;
      }
    }

    if (okToCalculate) { // calculate
      calculateMetodoDeDosPuestosPermanentes();
    }
  }
}
void NivelacionAcuaticaWidget::createComponents() {
  //------------------------------------------------------------------------
  m_chartFrame = new QFrame;
  m_chartFrame->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);

  m_chart = new QChart;

  m_chartView = new customChartView(m_chart);
  m_chartView->setRenderHint(QPainter::Antialiasing, true);

  m_puestoProvSerie = new QSplineSeries;
  m_puestoPerm1Serie = new QSplineSeries;
  m_puestoPerm2Serie = new QSplineSeries;
  m_nivelMedioLineSerie = new QLineSeries;

  m_puestoProvSerie->setPointsVisible(true);
  m_puestoPerm1Serie->setPointsVisible(true);
  m_puestoPerm1Serie->setPointsVisible(true);

  m_puestoProvSerie->setName(tr("Puesto Provisional"));
  m_puestoPerm1Serie->setName(tr("Puesto Permanente"));
  m_puestoPerm2Serie->setName(tr("Puesto Permanente #2"));

  m_nivelMedioLineSerie->setName(tr("Nivel Medio"));

  m_chart->addSeries(m_puestoProvSerie);
  m_chart->addSeries(m_puestoPerm1Serie);

  m_chart->createDefaultAxes();

  QHBoxLayout *chartLayout = new QHBoxLayout;
  chartLayout->addWidget(m_chartView);

  m_chartFrame->setLayout(chartLayout); // upWidgetLayout
  m_chartFrame->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

  m_puestoProvYAxis = new QValueAxis;
  m_puestoPerm1YAxis = new QValueAxis;
  m_puestoPerm2YAxis = new QValueAxis;

  m_dateTimeXAxis = new QDateTimeAxis;
  m_dateTimeXAxis->setFormat("d/M/yy h:mm");
  // m_dateTimeXAxis->setRange(QDateTime::currentDateTime(),
  // QDateTime::currentDateTime().addDays(1));

  // m_chart->setAxisX(m_dateTimeXAxis);

  //----------------------------------------------------------------------------

  // Table View-Model
  m_dataTableModel = new NivelacionAcuaticaTableModel;
  m_dataTableView = new QTableView;
  m_dataTableView->setModel(m_dataTableModel);
  m_dataTableView->setSizePolicy(QSizePolicy::Expanding,
                                 QSizePolicy::Preferred);

  //----------------------------------------------------------------------------

  m_metodoGroupBox = new QGroupBox(tr("Método de Cálculo:"));

  m_metodoComboBox = new QComboBox;
  m_metodoComboBox->addItem(tr("1 Puesto de Nivel"));
  m_metodoComboBox->addItem(tr("2 Puestos de Nivel"));

  QHBoxLayout *metodoLayout = new QHBoxLayout;
  metodoLayout->addWidget(m_metodoComboBox);

  m_metodoGroupBox->setLayout(metodoLayout);

  //----------------------------------------------------------------------------------

  m_puestoProvDataLoadFrame = new QFrame;
  m_puestoProvDataLoadFrame->setFrameStyle(QFrame::Box);

  m_puestoProvDataLoadLabel = new QLabel(tr("Puesto Provisional"));

  m_puestoProvImportButton = new QToolButton;
  m_puestoProvImportButton->setIcon(QIcon(":images/importButton.png"));
  m_puestoProvImportButton->setToolTip(
      tr("Importar serie desde archivo ASCII"));
  m_puestoProvManualButton = new QToolButton;
  m_puestoProvManualButton->setIcon(QIcon(":images/table_pencil.png"));
  m_puestoProvManualButton->setToolTip(tr("Introducción manual de serie"));
  m_puestoProvGetButton = new QToolButton;
  m_puestoProvGetButton->setIcon(QIcon(":images/from_project.png"));
  m_puestoProvGetButton->setToolTip(
      tr("Cargar serie desde el módulo principal"));

  QHBoxLayout *puestoProvDataLoadLayout = new QHBoxLayout;
  puestoProvDataLoadLayout->addWidget(m_puestoProvDataLoadLabel);
  puestoProvDataLoadLayout->addWidget(m_puestoProvImportButton);
  puestoProvDataLoadLayout->addWidget(m_puestoProvManualButton);
  puestoProvDataLoadLayout->addWidget(m_puestoProvGetButton);

  m_puestoProvDataLoadFrame->setLayout(puestoProvDataLoadLayout);

  //--------------------------------------------------------------------------------------

  m_puestoPerm1DataLoadFrame = new QFrame;
  m_puestoPerm1DataLoadFrame->setFrameStyle(QFrame::Box);

  m_puestoPerm1DataLoadLabel = new QLabel(tr("Puesto Permanente #1"));

  m_puestoPerm1ImportButton = new QToolButton;
  m_puestoPerm1ImportButton->setIcon(QIcon(":images/importButton.png"));
  m_puestoPerm1ImportButton->setToolTip(
      tr("Importar serie desde archivo ASCII"));
  m_puestoPerm1ManualButton = new QToolButton;
  m_puestoPerm1ManualButton->setIcon(QIcon(":images/table_pencil.png"));
  m_puestoPerm1ManualButton->setToolTip(tr("Introducción manual de serie"));
  m_puestoPerm1GetButton = new QToolButton;
  m_puestoPerm1GetButton->setIcon(QIcon(":images/from_project.png"));
  m_puestoPerm1GetButton->setToolTip(
      tr("Cargar serie desde el módulo principal"));

  QHBoxLayout *puestoPerm1DataLoadLayout = new QHBoxLayout;
  puestoPerm1DataLoadLayout->addWidget(m_puestoPerm1DataLoadLabel);
  puestoPerm1DataLoadLayout->addWidget(m_puestoPerm1ImportButton);
  puestoPerm1DataLoadLayout->addWidget(m_puestoPerm1ManualButton);
  puestoPerm1DataLoadLayout->addWidget(m_puestoPerm1GetButton);

  m_puestoPerm1DataLoadFrame->setLayout(puestoPerm1DataLoadLayout);

  //-----------------------------------------------------------------------------------------

  m_puestoPerm2DataLoadFrame = new QFrame;
  m_puestoPerm2DataLoadFrame->setFrameShape(QFrame::Box);
  m_puestoPerm2DataLoadFrame->setEnabled(false);

  m_puestoPerm2DataLoadLabel = new QLabel(tr("Puesto Permanente #2"));

  m_puestoPerm2ImportButton = new QToolButton;
  m_puestoPerm2ImportButton->setIcon(QIcon(":images/importButton.png"));
  m_puestoPerm2ImportButton->setToolTip(
      tr("Importar serie desde archivo ASCII"));
  m_puestoPerm2ManualButton = new QToolButton;
  m_puestoPerm2ManualButton->setIcon(QIcon(":images/table_pencil.png"));
  m_puestoPerm2ManualButton->setToolTip(tr("Introducción manual de serie"));
  m_puestoPerm2GetButton = new QToolButton;
  m_puestoPerm2GetButton->setIcon(QIcon(":images/from_project.png"));
  m_puestoPerm2GetButton->setToolTip(
      tr("Cargar serie desde el módulo principal"));

  QHBoxLayout *puestoPerm2DataLoadLayout = new QHBoxLayout;
  puestoPerm2DataLoadLayout->addWidget(m_puestoPerm2DataLoadLabel);
  puestoPerm2DataLoadLayout->addWidget(m_puestoPerm2ImportButton);
  puestoPerm2DataLoadLayout->addWidget(m_puestoPerm2ManualButton);
  puestoPerm2DataLoadLayout->addWidget(m_puestoPerm2GetButton);

  m_puestoPerm2DataLoadFrame->setLayout(puestoPerm2DataLoadLayout);

  //---------------------------------------------------------------------------------------------

  m_cargaDeDatosGroupBox = new QGroupBox(tr("Serie de Datos:"));

  QVBoxLayout *loadDataLayout = new QVBoxLayout;
  loadDataLayout->addWidget(m_puestoProvDataLoadFrame);
  loadDataLayout->addWidget(m_puestoPerm1DataLoadFrame);
  loadDataLayout->addWidget(m_puestoPerm2DataLoadFrame);

  m_cargaDeDatosGroupBox->setLayout(loadDataLayout);

  //------------------------------------------------------------------------------------------------

  QVBoxLayout *secondBottomLayout = new QVBoxLayout;
  secondBottomLayout->addWidget(m_metodoGroupBox);
  secondBottomLayout->addWidget(m_cargaDeDatosGroupBox);

  //------------------------------------------------------------------------------------------------

  m_puestoProvMetaDataGroupBox = new QGroupBox(tr("Puesto Provisional:"));

  m_puestoProvStationLabel = new QLabel(tr("Estación:"));
  m_puestoProvLocationLabel = new QLabel(tr("Situación:"));
  m_puestoProvLatitudLabel = new QLabel(tr("Latitud:"));
  m_puestoProvLongitudLabel = new QLabel(tr("Longitud:"));
  m_puestoProvNMMLabel = new QLabel("Nivel Medio:");

  m_puestoProvStationEdit = new QLineEdit;
  m_puestoProvLocationEdit = new QLineEdit;

  m_puestoProvLatitudEdit = new MyCoordinatesEditorWidget;
  m_puestoProvLongitudEdit = new MyCoordinatesEditorWidget;
  m_puestoProvLongitudEdit->setHType(MyCoordinatesEditorWidget::longitud);

  m_puestoProvNMMDisplayResult = new QLabel;
  m_puestoProvNMMDisplayResult->setFrameStyle(QFrame::StyledPanel |
                                              QFrame::Sunken);

  QFormLayout *puestoProvMetaDataLayout = new QFormLayout;
  puestoProvMetaDataLayout->addRow(m_puestoProvStationLabel,
                                   m_puestoProvStationEdit);
  puestoProvMetaDataLayout->addRow(m_puestoProvLocationLabel,
                                   m_puestoProvLocationEdit);
  puestoProvMetaDataLayout->addRow(m_puestoProvLatitudLabel,
                                   m_puestoProvLatitudEdit);
  puestoProvMetaDataLayout->addRow(m_puestoProvLongitudLabel,
                                   m_puestoProvLongitudEdit);
  puestoProvMetaDataLayout->addRow(m_puestoProvNMMLabel,
                                   m_puestoProvNMMDisplayResult);

  m_puestoProvMetaDataGroupBox->setLayout(puestoProvMetaDataLayout);

  //--------------------------------------------------------------------------------------------------
  m_puestoPerm1MetaDataGroupBox = new QGroupBox(tr("Puesto Permanente #1:"));

  m_puestoPerm1StationLabel = new QLabel(tr("Estación:"));
  m_puestoPerm1LocationLabel = new QLabel(tr("Situación:"));
  m_puestoPerm1LatitudLabel = new QLabel(tr("Latitud:"));
  m_puestoPerm1LongitudLabel = new QLabel(tr("Longitud:"));
  m_puestoPerm1NMMLabel = new QLabel("Nivel Medio:");

  m_puestoPerm1StationEdit = new QLineEdit;
  m_puestoPerm1LocationEdit = new QLineEdit;

  m_puestoPerm1LatitudEdit = new MyCoordinatesEditorWidget;
  m_puestoPerm1LongitudEdit = new MyCoordinatesEditorWidget;
  m_puestoPerm1LongitudEdit->setHType(MyCoordinatesEditorWidget::longitud);

  m_puestoPerm1NMMEdit = new MeasurementUnitEditWidget;

  QFormLayout *puestoPerm1MetaDataLayout = new QFormLayout;
  puestoPerm1MetaDataLayout->addRow(m_puestoPerm1StationLabel,
                                    m_puestoPerm1StationEdit);
  puestoPerm1MetaDataLayout->addRow(m_puestoPerm1LocationLabel,
                                    m_puestoPerm1LocationEdit);
  puestoPerm1MetaDataLayout->addRow(m_puestoPerm1LatitudLabel,
                                    m_puestoPerm1LatitudEdit);
  puestoPerm1MetaDataLayout->addRow(m_puestoPerm1LongitudLabel,
                                    m_puestoPerm1LongitudEdit);
  puestoPerm1MetaDataLayout->addRow(m_puestoPerm1NMMLabel,
                                    m_puestoPerm1NMMEdit);

  m_puestoPerm1MetaDataGroupBox->setLayout(puestoPerm1MetaDataLayout);

  //-------------------------------------------------------------------------------

  m_puestoPerm2MetaDataGroupBox = new QGroupBox(tr("Puesto Permanente #2:"));
  m_puestoPerm2MetaDataGroupBox->setEnabled(false);

  m_puestoPerm2StationLabel = new QLabel(tr("Estación:"));
  m_puestoPerm2LocationLabel = new QLabel(tr("Situación:"));
  m_puestoPerm2LatitudLabel = new QLabel(tr("Latitud:"));
  m_puestoPerm2LongitudLabel = new QLabel(tr("Longitud:"));
  m_puestoPerm2NMMLabel = new QLabel("Nivel Medio:");

  m_puestoPerm2StationEdit = new QLineEdit;
  m_puestoPerm2LocationEdit = new QLineEdit;

  m_puestoPerm2LatitudEdit = new MyCoordinatesEditorWidget;
  m_puestoPerm2LongitudEdit = new MyCoordinatesEditorWidget;
  m_puestoPerm2LongitudEdit->setHType(MyCoordinatesEditorWidget::longitud);

  m_puestoPerm2NMMEdit = new MeasurementUnitEditWidget;

  QFormLayout *puestoPerm2MetaDataLayout = new QFormLayout;
  puestoPerm2MetaDataLayout->addRow(m_puestoPerm2StationLabel,
                                    m_puestoPerm2StationEdit);
  puestoPerm2MetaDataLayout->addRow(m_puestoPerm2LocationLabel,
                                    m_puestoPerm2LocationEdit);
  puestoPerm2MetaDataLayout->addRow(m_puestoPerm2LatitudLabel,
                                    m_puestoPerm2LatitudEdit);
  puestoPerm2MetaDataLayout->addRow(m_puestoPerm2LongitudLabel,
                                    m_puestoPerm2LongitudEdit);
  puestoPerm2MetaDataLayout->addRow(m_puestoPerm2NMMLabel,
                                    m_puestoPerm2NMMEdit);

  m_puestoPerm2MetaDataGroupBox->setLayout(puestoPerm2MetaDataLayout);

  //--------------------------------------------------------------------------------
  // PushButtons
  m_calcNMMButton = new QPushButton(tr("Calcular"));
  m_calcNMMButton->setToolTip(tr("Calcular nivelación acuática"));
  connect(m_calcNMMButton, SIGNAL(clicked(bool)), this, SLOT(calculate()));

  QHBoxLayout *buttonLayout = new QHBoxLayout;
  buttonLayout->addStretch();
  buttonLayout->addWidget(m_calcNMMButton);

  QHBoxLayout *upBottomLayout = new QHBoxLayout;
  upBottomLayout->addLayout(secondBottomLayout);
  upBottomLayout->addWidget(m_puestoProvMetaDataGroupBox);
  upBottomLayout->addWidget(m_puestoPerm1MetaDataGroupBox);
  upBottomLayout->addWidget(m_puestoPerm2MetaDataGroupBox);

  QVBoxLayout *bottomRightLayout = new QVBoxLayout;
  bottomRightLayout->addLayout(upBottomLayout);
  bottomRightLayout->addLayout(buttonLayout);

  QHBoxLayout *bottomLayout = new QHBoxLayout;
  bottomLayout->addWidget(m_dataTableView);
  bottomLayout->addLayout(bottomRightLayout);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(m_chartFrame);
  mainLayout->addLayout(bottomLayout);

  this->setLayout(mainLayout);
}

void NivelacionAcuaticaWidget::setPuestoProvAxis() {
  qreal max = 0.0;
  qreal min = 0.0;

  foreach (QPointF point, m_puestoProvSerie->pointsVector()) {
    qreal aux = point.y();
    if (aux > max)
      max = aux;
    if (aux < min)
      min = aux;
  }
  m_puestoProvYAxis->setRange(min, max);
  m_puestoProvYAxis->applyNiceNumbers();

  m_puestoProvYAxis->setLabelsColor(m_puestoProvSerie->color());
  if (!m_chart->axes().contains(m_puestoProvYAxis))
    m_chart->setAxisY(m_puestoProvYAxis, m_puestoProvSerie);

  setPuestoProvXAxis();
}

void NivelacionAcuaticaWidget::setPuestoPerm1Axis() {

  qreal max = 0.0;
  qreal min = 0.0;

  foreach (QPointF point, m_puestoPerm1Serie->pointsVector()) {
    qreal aux = point.y();
    if (aux > max)
      max = aux;
    if (aux < min)
      min = aux;
  }
  m_puestoPerm1YAxis->setRange(min, max);
  m_puestoPerm1YAxis->applyNiceNumbers();

  m_puestoPerm1YAxis->setLabelsColor(m_puestoPerm1Serie->color());
  if (!m_chart->axes().contains(m_puestoPerm1YAxis))
    m_chart->setAxisY(m_puestoPerm1YAxis, m_puestoPerm1Serie);

  setPuestoPerm1XAxis();
}

void NivelacionAcuaticaWidget::setPuestoPerm2Axis() {

  qreal max = 0.0;
  qreal min = 0.0;

  foreach (QPointF point, m_puestoPerm2Serie->pointsVector()) {
    qreal aux = point.y();
    if (aux > max)
      max = aux;
    if (aux < min)
      min = aux;
  }
  m_puestoPerm2YAxis->setRange(min, max);
  m_puestoPerm2YAxis->applyNiceNumbers();

  m_puestoPerm2YAxis->setLabelsColor(m_puestoPerm2Serie->color());
  if (!m_chart->axes().contains(m_puestoPerm2YAxis))
    m_chart->setAxisY(m_puestoPerm2YAxis, m_puestoPerm2Serie);

  setPuestoPerm2XAxis();
}

void NivelacionAcuaticaWidget::setPuestoProvXAxis() {
  if (m_chart->axisX(m_puestoProvSerie) != m_dateTimeXAxis) {

    if (!m_dataTableModel->puestoProvData().isEmpty()) {
      QDateTime inDateTime =
          m_dataTableModel->puestoProvData().first().measurementDateTime();
      QDateTime endDateTime = inDateTime.addSecs(3600 * 24);

      m_dateTimeXAxis->setRange(inDateTime, endDateTime);
    }

    m_chart->setAxisX(m_dateTimeXAxis, m_puestoProvSerie);
  }
}

void NivelacionAcuaticaWidget::setPuestoPerm1XAxis() {
  if (m_chart->axisX(m_puestoPerm1Serie) != m_dateTimeXAxis) {
    if (!m_dataTableModel->puestoPerm1Data().isEmpty()) {
      QDateTime inDateTime =
          m_dataTableModel->puestoPerm1Data().first().measurementDateTime();
      QDateTime endDateTime = inDateTime.addSecs(3600 * 24);

      m_dateTimeXAxis->setRange(inDateTime, endDateTime);
    }

    m_chart->setAxisX(m_dateTimeXAxis, m_puestoPerm1Serie);
  }
}

void NivelacionAcuaticaWidget::setPuestoPerm2XAxis() {
  if (m_chart->axisX(m_puestoPerm2Serie) != m_dateTimeXAxis) {
    if (!m_dataTableModel->puestoPerm2Data().isEmpty()) {
      QDateTime inDateTime =
          m_dataTableModel->puestoPerm2Data().first().measurementDateTime();
      QDateTime endDateTime = inDateTime.addSecs(3600 * 24);

      m_dateTimeXAxis->setRange(inDateTime, endDateTime);
    }

    m_chart->setAxisX(m_dateTimeXAxis, m_puestoPerm2Serie);
  }
}
void NivelacionAcuaticaWidget::createLoadDialog() {
  QString fileName = QFileDialog::getOpenFileName(this, tr("Cargar Archivo"));
  if (!fileName.isEmpty()) {
    m_loadDialog = new LoadDialog(fileName, this);
    // m_loadDialog->setProjectMetaData(m_metadataStorage);
    // connect(m_loadDialog,SIGNAL(dataGeted(QVector<QStringList>,int,int,int,
    // const QString&, const QString&)),
    // this,SLOT(recieveData(QVector<QStringList>,int,int,int, const QString&,
    // const QString&)));
    connect(m_loadDialog, SIGNAL(importButtonClicked()), this,
            SLOT(beginDataExtrationFromFile()));
    connect(m_loadDialog, SIGNAL(appendDataActionTrigered()), this,
            SLOT(appendDataFromFile()));

    m_loadDialog->show();
  }
}

void NivelacionAcuaticaWidget::createManualDataIntroWidget() {
  m_manualDataIntroWidget = new ManualDataIntroductionWidget(this);
  // m_manualDataIntroWidget->setProjectMetaData(m_metadataStorage);
  connect(m_manualDataIntroWidget, SIGNAL(okButtonClicked()), this,
          SLOT(beginDataExtration()));
  connect(m_manualDataIntroWidget, SIGNAL(appendDataTrigered()), this,
          SLOT(appendDataFromManual()));
  m_manualDataIntroWidget->show();
}

void NivelacionAcuaticaWidget::calculateMetodoDeUnPuestoPermanente() {
  qreal nmm0 = m_puestoPerm1NMMEdit->value();

  qreal value = calcularNivelacionAcuatica1PuestoPermanete(
      m_dataTableModel->diffPProvPuestoPerm1(), nmm0);

  m_puestoProvNMMDisplayResult->setText(QString::number(value, 'g', 3));

  m_nivelMedioLineSerie->clear();

  m_nivelMedioLineSerie->append(m_puestoProvSerie->pointsVector().first().x(),
                                value);
  m_nivelMedioLineSerie->append(m_puestoProvSerie->pointsVector().last().x(),
                                value);

  if (!m_chart->series().contains(m_nivelMedioLineSerie)) {
    m_chart->addSeries(m_nivelMedioLineSerie);
    if (m_chart->axisY(m_nivelMedioLineSerie) != m_puestoProvYAxis) {
      m_chart->setAxisY(m_puestoProvYAxis, m_nivelMedioLineSerie);
    }
    if (m_chart->axisX(m_nivelMedioLineSerie) != m_dateTimeXAxis) {
      m_chart->setAxisX(m_dateTimeXAxis, m_nivelMedioLineSerie);
    }
  }

  QString color = m_nivelMedioLineSerie->color().name();

  m_puestoProvNMMDisplayResult->setText("<b><font color = " + color + ">" +
                                        QString::number(value, 'g', 3) +
                                        "</b></font>");
}

void NivelacionAcuaticaWidget::calculateMetodoDeDosPuestosPermanentes() {
  qreal nmm01 = m_puestoPerm1NMMEdit->value();
  qreal nmm02 = m_puestoPerm2NMMEdit->value();

  QGeoCoordinate pProvCoordinates(m_puestoProvLatitudEdit->coordinate(),
                                  m_puestoProvLongitudEdit->coordinate());
  QGeoCoordinate pPerm1Coordinates(m_puestoPerm1LatitudEdit->coordinate(),
                                   m_puestoPerm1LongitudEdit->coordinate());
  QGeoCoordinate pPerm2Coordinates(m_puestoPerm2LatitudEdit->coordinate(),
                                   m_puestoPerm2LongitudEdit->coordinate());

  qreal value = calcularNivelacionAcuatica2PuestoPermanete(
      m_dataTableModel->diffPProvPuestoPerm1(),
      m_dataTableModel->diffPProvPuestoPerm2(), nmm01, nmm02, pProvCoordinates,
      pPerm1Coordinates, pPerm2Coordinates);

  m_nivelMedioLineSerie->clear();

  m_nivelMedioLineSerie->append(m_puestoProvSerie->pointsVector().first().x(),
                                value);
  m_nivelMedioLineSerie->append(m_puestoProvSerie->pointsVector().last().x(),
                                value);

  if (!m_chart->series().contains(m_nivelMedioLineSerie)) {
    m_chart->addSeries(m_nivelMedioLineSerie);
    if (m_chart->axisY(m_nivelMedioLineSerie) != m_puestoProvYAxis) {
      m_chart->setAxisY(m_puestoProvYAxis, m_nivelMedioLineSerie);
    }
    if (m_chart->axisX(m_nivelMedioLineSerie) != m_dateTimeXAxis) {
      m_chart->setAxisX(m_dateTimeXAxis, m_nivelMedioLineSerie);
    }
  }

  QString color = m_nivelMedioLineSerie->color().name();

  m_puestoProvNMMDisplayResult->setText("<b><font color = " + color + ">" +
                                        QString::number(value, 'g', 3) +
                                        "</b></font>");
}
