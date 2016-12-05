#include "nivelacionacuaticawidget.h"

NivelacionAcuaticaWidget::NivelacionAcuaticaWidget(QWidget *parent) : QWidget(parent)
{
    createComponents();
    m_provDataLoadFlag = false;
    m_perm1DataLoadFlag = false;
    m_perm2DataLoadFlag = false;

    m_loadDialog = Q_NULLPTR;
    m_manualDataIntroWidget = Q_NULLPTR;

    connect(m_puestoProvImportButton,SIGNAL(clicked(bool)),this,SLOT(createProvDataLoadDialog()));
    connect(m_puestoPerm1ImportButton,SIGNAL(clicked(bool)),this,SLOT(createPerm1DataLoadDialog()));
    connect(m_puestoPerm2ImportButton,SIGNAL(clicked(bool)),this,SLOT(createPerm2DataLoadDialog()));

    connect(m_puestoProvManualButton,SIGNAL(clicked(bool)),this,SLOT(createProvManualDataIntro()));
    connect(m_puestoPerm1ManualButton,SIGNAL(clicked(bool)),this,SLOT(createPerm1ManualDataIntro()));
    connect(m_puestoPerm2ManualButton,SIGNAL(clicked(bool)),this,SLOT(createPerm2ManualDataIntro()));

    connect(m_metodoComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(setMetodoDeNivelacion(int)));

    setAttribute(Qt::WA_DeleteOnClose);
}

void NivelacionAcuaticaWidget::createProvDataLoadDialog()
{
    m_provDataLoadFlag = true;
    m_perm1DataLoadFlag = false;
    m_perm2DataLoadFlag = false;

    createLoadDialog();
}

void NivelacionAcuaticaWidget::createPerm1DataLoadDialog()
{
    m_provDataLoadFlag = false;
    m_perm1DataLoadFlag = true;
    m_perm2DataLoadFlag = false;

    createLoadDialog();
}

void NivelacionAcuaticaWidget::createPerm2DataLoadDialog()
{
    m_provDataLoadFlag = false;
    m_perm1DataLoadFlag = false;
    m_perm2DataLoadFlag = true;

    createLoadDialog();
}

void NivelacionAcuaticaWidget::createProvManualDataIntro()
{
    m_provDataLoadFlag = true;
    m_perm1DataLoadFlag = false;
    m_perm2DataLoadFlag = false;

    createManualDataIntroWidget();
}

void NivelacionAcuaticaWidget::createPerm1ManualDataIntro()
{
    m_provDataLoadFlag = false;
    m_perm1DataLoadFlag = true;
    m_perm2DataLoadFlag = false;

    createManualDataIntroWidget();
}

void NivelacionAcuaticaWidget::createPerm2ManualDataIntro()
{
    m_provDataLoadFlag = false;
    m_perm1DataLoadFlag = false;
    m_perm2DataLoadFlag = true;

    createManualDataIntroWidget();
}

void NivelacionAcuaticaWidget::beginDataExtrationFromFile()
{
    if (m_provDataLoadFlag){
        m_dataTableModel->setPuestoProvisionalDataSet(m_loadDialog->measurementsData());
        m_loadDialog->close();
        return;
    }

    if (m_perm1DataLoadFlag){
        m_dataTableModel->setPuestoPermanente1DataSet(m_loadDialog->measurementsData());
        m_loadDialog->close();
        return;
    }

    if (m_perm2DataLoadFlag){
        m_dataTableModel->setPuestoPermanente2DataSet(m_loadDialog->measurementsData());
        m_loadDialog->close();
        return;
    }
}

void NivelacionAcuaticaWidget::beginDataExtration()
{
    QVector<TidesMeasurement> datos;

    int size = m_manualDataIntroWidget->model()->measurementData().size();

    qreal conversion = m_manualDataIntroWidget->conversionUnit();


    for (int i = 0; i < size ; ++i){
        if (m_manualDataIntroWidget->model()->measurementData().at(i).isValid()){

            datos.push_back(m_manualDataIntroWidget->model()->measurementData().at(i));

            if (conversion != 1.0){
                qreal value = m_manualDataIntroWidget->model()->measurementData().at(i).seaLevel()*conversion;
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

    if (m_provDataLoadFlag){
        m_dataTableModel->setPuestoProvisionalDataSet(datos);
        m_manualDataIntroWidget->close();
        return;
    }

    if (m_perm1DataLoadFlag){
        m_dataTableModel->setPuestoPermanente1DataSet(datos);
        m_manualDataIntroWidget->close();
        return;
    }

    if (m_perm2DataLoadFlag){
        m_dataTableModel->setPuestoPermanente2DataSet(datos);
        m_manualDataIntroWidget->close();
        return;
    }
}

void NivelacionAcuaticaWidget::setMetodoDeNivelacion(int index)
{
    switch (index) {
    case 0:
        m_puestoPerm2DataLoadFrame->setEnabled(false);
        break;
    case 1:
        m_puestoPerm2DataLoadFrame->setEnabled(true);
        break;
    default:
        m_puestoPerm2DataLoadFrame->setEnabled(false);
        break;
    }
    m_dataTableModel->setMetododeNivelacion(index);
}
void NivelacionAcuaticaWidget::createComponents()
{
    //------------------------------------------------------------------------
    m_chartFrame = new QFrame;
    m_chartFrame->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);

    m_chart = new QChart;

    m_chartView = new customChartView(m_chart);

    m_puestoProvSerie = new QSplineSeries;
    m_puestoPerm1Serie = new QSplineSeries;
    m_puestoPerm2Serie = new QSplineSeries;
    m_nivelMedioLineSerie = new QLineSeries;

    QHBoxLayout *chartLayout = new QHBoxLayout;
    chartLayout->addWidget(m_chartView);

    m_chartFrame->setLayout(chartLayout); //upWidgetLayout
    m_chartFrame->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    //----------------------------------------------------------------------------

    //Table View-Model
    m_dataTableModel = new NivelacionAcuaticaTableModel;
    m_dataTableView = new QTableView;
    m_dataTableView->setModel(m_dataTableModel);
    m_dataTableView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

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
    m_puestoProvImportButton->setToolTip(tr("Importar serie desde archivo ASCII"));
    m_puestoProvManualButton = new QToolButton;
    m_puestoProvManualButton->setIcon(QIcon(":images/table_pencil.png"));
    m_puestoProvManualButton->setToolTip(tr("Introducción manual de serie"));
    m_puestoProvGetButton = new QToolButton;
    m_puestoProvGetButton->setIcon(QIcon(":images/from_project.png"));
    m_puestoProvGetButton->setToolTip(tr("Cargar serie desde el módulo principal"));

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
    m_puestoPerm1ImportButton->setToolTip(tr("Importar serie desde archivo ASCII"));
    m_puestoPerm1ManualButton = new QToolButton;
    m_puestoPerm1ManualButton->setIcon(QIcon(":images/table_pencil.png"));
    m_puestoPerm1ManualButton->setToolTip(tr("Introducción manual de serie"));
    m_puestoPerm1GetButton = new QToolButton;
    m_puestoPerm1GetButton->setIcon(QIcon(":images/from_project.png"));
    m_puestoPerm1GetButton->setToolTip(tr("Cargar serie desde el módulo principal"));

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
    m_puestoPerm2ImportButton->setToolTip(tr("Importar serie desde archivo ASCII"));
    m_puestoPerm2ManualButton = new QToolButton;
    m_puestoPerm2ManualButton->setIcon(QIcon(":images/table_pencil.png"));
    m_puestoPerm2ManualButton->setToolTip(tr("Introducción manual de serie"));
    m_puestoPerm2GetButton = new QToolButton;
    m_puestoPerm2GetButton->setIcon(QIcon(":images/from_project.png"));
    m_puestoPerm2GetButton->setToolTip(tr("Cargar serie desde el módulo principal"));

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
    m_puestoProvNMMDisplayResult->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);

    QFormLayout *puestoProvMetaDataLayout = new QFormLayout;
    puestoProvMetaDataLayout->addRow(m_puestoProvStationLabel,m_puestoProvStationEdit);
    puestoProvMetaDataLayout->addRow(m_puestoProvLocationLabel,m_puestoProvLocationEdit);
    puestoProvMetaDataLayout->addRow(m_puestoProvLatitudLabel,m_puestoProvLatitudEdit);
    puestoProvMetaDataLayout->addRow(m_puestoProvLongitudLabel,m_puestoProvLongitudEdit);
    puestoProvMetaDataLayout->addRow(m_puestoProvNMMLabel,m_puestoProvNMMDisplayResult);

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
    puestoPerm1MetaDataLayout->addRow(m_puestoPerm1StationLabel,m_puestoPerm1StationEdit);
    puestoPerm1MetaDataLayout->addRow(m_puestoPerm1LocationLabel,m_puestoPerm1LocationEdit);
    puestoPerm1MetaDataLayout->addRow(m_puestoPerm1LatitudLabel,m_puestoPerm1LatitudEdit);
    puestoPerm1MetaDataLayout->addRow(m_puestoPerm1LongitudLabel,m_puestoPerm1LongitudEdit);
    puestoPerm1MetaDataLayout->addRow(m_puestoPerm1NMMLabel,m_puestoPerm1NMMEdit);

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
    puestoPerm2MetaDataLayout->addRow(m_puestoPerm2StationLabel,m_puestoPerm2StationEdit);
    puestoPerm2MetaDataLayout->addRow(m_puestoPerm2LocationLabel,m_puestoPerm2LocationEdit);
    puestoPerm2MetaDataLayout->addRow(m_puestoPerm2LatitudLabel,m_puestoPerm2LatitudEdit);
    puestoPerm2MetaDataLayout->addRow(m_puestoPerm2LongitudLabel,m_puestoPerm2LongitudEdit);
    puestoPerm2MetaDataLayout->addRow(m_puestoPerm2NMMLabel,m_puestoPerm2NMMEdit);

    m_puestoPerm2MetaDataGroupBox->setLayout(puestoPerm2MetaDataLayout);

    //--------------------------------------------------------------------------------
    //PushButtons
    m_calcNMMButton = new QPushButton(tr("Calcular"));
    m_calcNMMButton->setToolTip(tr("Calcular nivelación acuática"));

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

void NivelacionAcuaticaWidget::createLoadDialog()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Cargar Archivo"));
    if (!fileName.isEmpty()){
        m_loadDialog = new LoadDialog(fileName,this);
        //m_loadDialog->setProjectMetaData(m_metadataStorage);
        //connect(m_loadDialog,SIGNAL(dataGeted(QVector<QStringList>,int,int,int, const QString&, const QString&)),
                    //this,SLOT(recieveData(QVector<QStringList>,int,int,int, const QString&, const QString&)));
        connect(m_loadDialog,SIGNAL(importButtonClicked()),this,SLOT(beginDataExtrationFromFile()));

        //TODO: Las conexiones de los senales del dialogo para coger la localizacion Eq_Id, Lat, Long
        m_loadDialog->show();
    }
}

void NivelacionAcuaticaWidget::createManualDataIntroWidget()
{
    m_manualDataIntroWidget = new ManualDataIntroductionWidget(this);
    //m_manualDataIntroWidget->setProjectMetaData(m_metadataStorage);
    connect(m_manualDataIntroWidget,SIGNAL(okButtonClicked()),
            this,SLOT(beginDataExtration()));
    m_manualDataIntroWidget->show();
}
