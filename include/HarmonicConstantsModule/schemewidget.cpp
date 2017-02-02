#include "schemewidget.h"
#include <QToolButton>
#include <QPushButton>
#include <QProgressBar>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPlainTextEdit>
#include <QTableView>
#include <QRadioButton>
#include <QDateEdit>
#include <QLabel>
#include <QTimeEdit>

#include "include/HarmonicConstantsModule/Model_View/harmonicconstantfulltablemodel.h"
#include "include/HarmonicConstantsModule/Model_View/harmonicconstantfrequencytabledelegate.h"

SchemeWidget::SchemeWidget(const QDateTime &iniDateTime, const QDateTime &endDateTime, const QStringList &schemesLabels, const QStringList &componentsLabels, const QMap<QString,QMap<QString,bool>> &schemes_componentMap,const QMap<QString,QString> &schemeDescription, QWidget *parent):
    QDialog(parent),m_schemesLabels(schemesLabels), m_componentsLabels(componentsLabels),m_schemes_componentMap(schemes_componentMap), m_schemeDescriptionMap(schemeDescription)
{
    m_configSchemeDialog = 0;

    crearComponentes(iniDateTime,endDateTime,schemesLabels,componentsLabels);
    interfazLayout();

    setWindowIcon(QIcon(":images/harmonic-analisis.png"));
    this->setModal(true);

    Qt::WindowFlags flag = Qt::Dialog | Qt::WindowCloseButtonHint;
    this->setWindowFlags(flag);

    this->setAttribute(Qt::WA_DeleteOnClose);
}

QMap<QString, bool> SchemeWidget::selectedSchemeComponentStatus() const
{
    return m_schemes_componentMap.value(m_schemeComboBox->currentText());
}

void SchemeWidget::setHarmonicConstantModelData(const QVector<HarmonicConstant> &datos)
{
    m_harmonicConstantTableModel->setAllData(datos);
}

void SchemeWidget::showHarmonicConstantTable()
{
    m_harmonicConstantTableView->show();

    int width = m_harmonicConstantTableView->geometry().width();
    int heigth = m_harmonicConstantTableView->geometry().height();

    int x = m_harmonicConstantTableView->geometry().left();
    int y = m_harmonicConstantTableView->geometry().top();

    m_animation->setStartValue(QRect(x,y,0,0));
    m_animation->setEndValue(QRect(x,y,width,heigth));
    m_animation->setDuration(1000);
    m_animation->start();
}

int SchemeWidget::harmonicAnalisisTypeMethod()
{
    return m_HarmonicAnalisisMethodComboBox->currentIndex();
}

int SchemeWidget::equationSystemSolutionMethod()
{
    return m_SystemSolutionMethodComboBox->currentIndex();
}

int SchemeWidget::currentSelectionComboBoxIndex() const
{
    return m_dataSelectionComboBox->currentIndex();
}

void SchemeWidget::enableSaveHarmonicConstantButton()
{

    m_loadingMovie->stop();
    m_loadingLabel->setVisible(false);
    showHarmonicConstantTable();

    //m_loadingQuickWidget->setVisible(false);

    //m_saveHarmonicConstantsButton->setEnabled(true);
}
void SchemeWidget::beginHarmonicAnalisis()
{
    m_loadingLabel->setVisible(true);
    m_loadingMovie->start();
    //m_loadingQuickWidget->setVisible(true);
    //m_harmonicConstantTableView->setVisible(false);

    emit analizeButtonClicked();
}

void SchemeWidget::setSchemesLabels(const QStringList &schemesLabels)
{
    m_schemesLabels = schemesLabels;

    m_schemeComboBox->clear();
    m_schemeComboBox->addItem(tr("-Selecciona un esquema de análisis-"));
    m_schemeComboBox->addItems(schemesLabels);
}

void SchemeWidget::setSchemesComponentsMap(const QMap<QString, QMap<QString, bool> > &schemes_componentMap)
{
    m_schemes_componentMap = schemes_componentMap;
}



void SchemeWidget::createConfigSchemeDialog()
{
    m_configSchemeDialog = new SchemeConfigDialog(m_schemesLabels,m_componentsLabels, m_schemes_componentMap,m_schemeDescriptionMap, this,Qt::WindowCloseButtonHint);
    connect(m_configSchemeDialog,SIGNAL(acceptButtonClicked()),this,SLOT(updateInternalData()));
    m_configSchemeDialog->setModal(true);
    m_configSchemeDialog->show();
}

void SchemeWidget::selectAnalisisScheme(const QString &str)
{
    //if (m_schemes_componentMap.contains(str))
    m_tidalSchemeComponents->setCheckBoxesStatus(m_schemes_componentMap.value(str));
    //new code
    m_schemeDescriptionPlainTextEdit->setPlainText(m_schemeDescriptionMap.value(str));

    if (str == "-Selecciona un esquema de análisis-") m_analizarPushButton->setEnabled(false);
    else m_analizarPushButton->setEnabled(true);
}

void SchemeWidget::updateInternalData()
{
    setSchemesLabels(m_configSchemeDialog->schemes());
    setSchemesComponentsMap(m_configSchemeDialog->schemeComponentStatus());

    //new code
    m_schemeDescriptionMap = m_configSchemeDialog->schemeDescription();

    m_configSchemeDialog->close();
}

void SchemeWidget::changeScheme(const QString &newScheme)
{
    m_tidalSchemeComponents->setCheckBoxesStatus(m_schemes_componentMap.value(newScheme));
}

void SchemeWidget::setIniDate(QDate date)
{
    m_initialDateTime.setDate(date);
}

void SchemeWidget::setEndDate(QDate date)
{
    m_endDateTime.setDate(date);
}

void SchemeWidget::setIniTime(QTime time)
{
    m_initialDateTime.setTime(time);
}

void SchemeWidget::setEndTime(QTime time)
{
    m_endDateTime.setTime(time);
}

void SchemeWidget::updateTimeInterval(QTime time)
{
    m_timeInterval = time.hour()*3600 + time.minute()*60;
}

void SchemeWidget::enableCustomDataSelection(int index)
{
    if (index) m_customDataSelectionGroupBox->setEnabled(true);
    else m_customDataSelectionGroupBox->setEnabled(false);
}
void SchemeWidget::crearComponentes(const QDateTime &iniDateTime, const QDateTime &endDateTime, const QStringList &schemesLabels, const QStringList &componentsLabels)
{
     //TODO:connections

    //m_loadingQuickWidget = new QQuickWidget(QUrl(QStringLiteral("qrc:/analizing.qml")));

    /*QSurfaceFormat format;
    if (QCoreApplication::arguments().contains(QStringLiteral("--coreprofile"))) {
        format.setVersion(4, 4);
        format.setProfile(QSurfaceFormat::CoreProfile);
    }
    if (QCoreApplication::arguments().contains(QStringLiteral("--multisample")))
        format.setSamples(4);
    m_loadingQuickWidget->setFormat(format);*/

    //m_loadingQuickWidget->resize(100,200);
    //m_loadingQuickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

    //m_loadingQuickWidget->setVisible(false);

    m_schemeComboBox = new QComboBox;
    m_schemeComboBox->addItem(tr("-Selecciona un esquema de análisis-"));
    m_schemeComboBox->addItems(schemesLabels);
    connect(m_schemeComboBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(selectAnalisisScheme(QString)));

    m_tidalSchemeComponents = new TidalSchemeSelectionWidget(componentsLabels,this);
    m_tidalSchemeComponents->setCheckBoxesEnabledStatus(false);
    m_tidalSchemeComponents->setMinimumHeight(300);

    m_descriptionGroupBox = new QGroupBox(tr("Descripción:"));
    m_descriptionGroupBox->setFixedHeight(110);

    m_componentGroupBox = new QGroupBox(tr("Componentes"));

    m_schemeDescriptionPlainTextEdit = new QPlainTextEdit;
    m_schemeDescriptionPlainTextEdit->setDisabled(true);
    //m_schemeDescriptionPlainTextEdit->setFixedHeight(100);

    m_configEsquemaToolButton = new QToolButton(this);
    m_configEsquemaToolButton->setIcon(QIcon(":images/configure.png"));
    m_configEsquemaToolButton->setToolTip(tr("Configurar esquemas de analisis"));
    connect(m_configEsquemaToolButton,SIGNAL(clicked(bool)),this,SLOT(createConfigSchemeDialog()));

    m_analizarPushButton = new QPushButton(QIcon(":images/analisis.png"),tr("Analizar"),this);
    m_analizarPushButton->setMinimumWidth(100);
    m_analizarPushButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    m_analizarPushButton->setToolTip(tr("Calcular constantes armónicas"));
    m_analizarPushButton->setEnabled(false);
    connect(m_analizarPushButton,SIGNAL(clicked(bool)),this,SLOT(beginHarmonicAnalisis()));

    //m_analizandoProgressBar = new QProgressBar;
    //m_analizandoProgressBar->setTextVisible(true);

    //m_saveHarmonicConstantsButton = new QPushButton(QIcon(":images/save.png"),tr("Guardar C.Armonicas"));
    //m_saveHarmonicConstantsButton->setToolTip(tr("Guardar Constantes Armónicas"));
    //m_saveHarmonicConstantsButton->setEnabled(false);
    //connect(m_saveHarmonicConstantsButton,SIGNAL(clicked(bool)),this,SIGNAL(saveHarmonicConstantsButtonClicked()));

    m_harmonicConstantTableView = new QTableView(this);

    m_harmonicConstantTableModel = new HarmonicConstantFullTableModel;
    m_harmonicConstantTableView->setModel(m_harmonicConstantTableModel);

    int width = 15;
    for (int i = 0; i<m_harmonicConstantTableView->model()->columnCount(QModelIndex()); ++i){
        width+=m_harmonicConstantTableView->columnWidth(i);
    }
    m_harmonicConstantTableView->setMinimumWidth(width);

    m_harmonicConstantTableView->hide();

    m_analisisTypeGroupBox = new QGroupBox(tr("Análisis Armónico"));
    m_fitMethodGroupBox = new QGroupBox(tr("Método de Ajuste"));
    //m_luRadioButton = new QRadioButton(tr("Descomposicion LU"),this);
    //m_luRadioButton->setChecked(true);
    //m_svdRadioButton = new QRadioButton(tr("SVD"),this);

    m_HarmonicAnalisisMethodComboBox = new QComboBox;
    m_HarmonicAnalisisMethodComboBox->addItem(tr("Factores Nodales Fijos"));
    m_HarmonicAnalisisMethodComboBox->addItem(tr("Factores Nodales Variables"));

    m_SystemSolutionMethodComboBox = new QComboBox;
    m_SystemSolutionMethodComboBox->addItem(tr("DCMP LU"));
    m_SystemSolutionMethodComboBox->addItem(tr("SVD"));
    //*********************Data time filter*******************************
    m_dataSelectionGroupBox = new QGroupBox(tr("Seleccion de Datos"),this);
    m_dataSelectionComboBox = new QComboBox(this);
    m_dataSelectionComboBox->addItem(tr("Todos"));
    m_dataSelectionComboBox->addItem(tr("Personalizado"));

    m_customDataSelectionGroupBox = new QGroupBox(tr("Personalizado"),this);

    m_iniDateEdit = new QDateEdit(this);
    m_iniDateEdit->setDisplayFormat("dd/MM/yyyy");
    m_iniDateEdit->setCalendarPopup(true);
    connect(m_iniDateEdit,SIGNAL(dateChanged(QDate)),this,SLOT(setIniDate(QDate)));
    m_iniDateEdit->setDate(iniDateTime.date());
    m_endDateEdit = new QDateEdit(this);
    m_endDateEdit->setDisplayFormat("dd/MM/yyyy");
    m_endDateEdit->setCalendarPopup(true);
    connect(m_endDateEdit,SIGNAL(dateChanged(QDate)),this,SLOT(setEndDate(QDate)));
    m_endDateEdit->setDate(endDateTime.date());

    m_iniTimeEdit = new QTimeEdit(this);
    m_iniTimeEdit->setDisplayFormat("hh:mm");
    connect(m_iniTimeEdit,SIGNAL(timeChanged(QTime)),this,SLOT(setIniTime(QTime)));
    m_iniTimeEdit->setTime(iniDateTime.time());

    m_endTimeEdit = new QTimeEdit(this);
    m_endTimeEdit->setDisplayFormat("hh:mm");
    connect(m_endTimeEdit,SIGNAL(timeChanged(QTime)),this,SLOT(setEndTime(QTime)));
    m_endTimeEdit->setTime(endDateTime.time());

    m_customIntervalLabel = new QLabel(tr("&Intervalo"),this);
    m_customIntervalTimeEdit = new QTimeEdit(this);
    m_customIntervalTimeEdit->setDisplayFormat("hh:mm");
    connect(m_customIntervalTimeEdit,SIGNAL(timeChanged(QTime)),this,SLOT(updateTimeInterval(QTime)));
    m_customIntervalTimeEdit->setTime(QTime(1,0));
    m_customIntervalLabel->setBuddy(m_customIntervalTimeEdit);

    connect(m_dataSelectionComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(enableCustomDataSelection(int)));

    m_saveSelectedData = new QPushButton(QIcon(":images/save.png"),tr("Guardar Datos"));
    connect(m_saveSelectedData,SIGNAL(clicked(bool)),this,SIGNAL(saveDataButtonClicked()));

    //********************************************************************
    m_animation = new QPropertyAnimation(m_harmonicConstantTableView,"geometry",this);

    //Loading label
    m_loadingLabel = new QLabel;
    m_loadingMovie = new QMovie(":images/carga7.gif");
    m_loadingLabel->setMovie(m_loadingMovie);
}

void SchemeWidget::interfazLayout()
{
    QHBoxLayout *upLayout = new QHBoxLayout;
    upLayout->addWidget(m_schemeComboBox);
    upLayout->addWidget(m_configEsquemaToolButton);

    QHBoxLayout *componetesLayout = new QHBoxLayout;
    componetesLayout->addWidget(m_tidalSchemeComponents);
    m_componentGroupBox->setLayout(componetesLayout);

    QHBoxLayout *descriptionLayout = new QHBoxLayout;

    descriptionLayout->addWidget(m_schemeDescriptionPlainTextEdit);
    m_descriptionGroupBox->setLayout(descriptionLayout);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(m_analizarPushButton);
    bottomLayout->addWidget(m_loadingLabel);
    bottomLayout->setAlignment(m_analizarPushButton,Qt::AlignLeft);
    //bottomLayout->addStretch();
    //bottomLayout->addWidget(m_saveHarmonicConstantsButton);

    QHBoxLayout *analisisLayout = new QHBoxLayout;
    analisisLayout->addWidget(m_HarmonicAnalisisMethodComboBox);
    m_analisisTypeGroupBox->setLayout(analisisLayout);

    QHBoxLayout *fitMethodLayout = new QHBoxLayout;
    fitMethodLayout->addWidget(m_SystemSolutionMethodComboBox);
    m_fitMethodGroupBox->setLayout(fitMethodLayout);
    //m_radiosButtonGroupBox->setLayout(radioLayout);

    QHBoxLayout *calcTypeMethod = new QHBoxLayout;
    calcTypeMethod->addWidget(m_analisisTypeGroupBox);
    calcTypeMethod->addWidget(m_fitMethodGroupBox);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(upLayout);
    mainLayout->addWidget(m_componentGroupBox);
    mainLayout->addWidget(m_descriptionGroupBox);
    mainLayout->addLayout(calcTypeMethod);
    mainLayout->addLayout(bottomLayout);

    QGroupBox *analisisGroupBox = new QGroupBox(tr("Analisis"));
    analisisGroupBox->setLayout(mainLayout);

    //************Time data filter******************************
    QHBoxLayout *customIntervalLayout = new QHBoxLayout;
    customIntervalLayout->addWidget(m_customIntervalLabel);
    customIntervalLayout->addWidget(m_customIntervalTimeEdit);

    QGroupBox *iniTimeGroupBox = new QGroupBox(tr("Inicio"));
    QGroupBox *endTimeGroupBox = new QGroupBox(tr("Fin"));
    QGroupBox *intervalGroupBox = new QGroupBox;
    intervalGroupBox->setLayout(customIntervalLayout);


    QVBoxLayout *iniDateTimeLayout = new QVBoxLayout;
    iniDateTimeLayout->addWidget(m_iniDateEdit);
    iniDateTimeLayout->addWidget(m_iniTimeEdit);

    QHBoxLayout *iniTimeLayout = new QHBoxLayout;
    iniTimeLayout->addLayout(iniDateTimeLayout);
    iniTimeGroupBox->setLayout(iniTimeLayout);

    QVBoxLayout *endDateTimeLayout = new QVBoxLayout;
    endDateTimeLayout->addWidget(m_endDateEdit);
    endDateTimeLayout->addWidget(m_endTimeEdit);


    QHBoxLayout *endTimeLayout = new QHBoxLayout;
    endTimeLayout->addLayout(endDateTimeLayout);
    endTimeGroupBox->setLayout(endTimeLayout);

    QVBoxLayout *customTimeLayout = new QVBoxLayout;
    customTimeLayout->addWidget(iniTimeGroupBox);
    customTimeLayout->addWidget(endTimeGroupBox);
    customTimeLayout->addWidget(intervalGroupBox);

    m_customDataSelectionGroupBox->setLayout(customTimeLayout);
    m_customDataSelectionGroupBox->setDisabled(true);

    QHBoxLayout *saveButtonLayout = new QHBoxLayout;
    saveButtonLayout->addStretch();
    saveButtonLayout->addWidget(m_saveSelectedData);

    //QGroupBox *buttonGroupBox = new QGroupBox;
    //buttonGroupBox->setLayout(saveButtonLayout);

    QVBoxLayout *mainLeftLayout = new QVBoxLayout;
    mainLeftLayout->addWidget(m_dataSelectionComboBox);
    mainLeftLayout->addWidget(m_customDataSelectionGroupBox);
    mainLeftLayout->addStretch();
    //mainLeftLayout->addWidget(m_loadingQuickWidget);
    mainLeftLayout->addStretch();
    mainLeftLayout->addWidget(m_saveSelectedData);

    m_dataSelectionGroupBox->setLayout(mainLeftLayout);


    //**********************************************************

    QHBoxLayout *definiteLayout = new QHBoxLayout;
    definiteLayout->addWidget(m_dataSelectionGroupBox);
    definiteLayout->addWidget(analisisGroupBox);
    definiteLayout->addWidget(m_harmonicConstantTableView);

    this->setLayout(definiteLayout);
}

/*void SchemeWidget::createLoadingWidget()
{
    m_loadingQuickWidget = new QQuickWidget(QUrl(QStringLiteral("qrc:/analizing.qml")));

    QSurfaceFormat format;
    if (QCoreApplication::arguments().contains(QStringLiteral("--coreprofile"))) {
        format.setVersion(4, 4);
        format.setProfile(QSurfaceFormat::CoreProfile);
    }
    if (QCoreApplication::arguments().contains(QStringLiteral("--multisample")))
        format.setSamples(4);
    m_loadingQuickWidget->setFormat(format);

    m_loadingQuickWidget->resize(100,100);
    m_loadingQuickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView );

    m_loadingQuickWidget->show();
    m_loadingQuickWidget->raise();
}*/

