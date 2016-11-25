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
}

bool SchemeWidget::isLuDecompositionAnalisis()
{
    return m_luRadioButton->isChecked();
}

int SchemeWidget::currentSelectionComboBoxIndex() const
{
    return m_dataSelectionComboBox->currentIndex();
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
    m_analizarPushButton->setToolTip(tr("Calcular constantes armónicas"));
    connect(m_analizarPushButton,SIGNAL(clicked(bool)),this,SIGNAL(analizeButtonClicked()));

    m_analizandoProgressBar = new QProgressBar;
    m_analizandoProgressBar->setTextVisible(true);

    m_harmonicConstantTableView = new QTableView(this);

    m_harmonicConstantTableModel = new HarmonicConstantFullTableModel;
    m_harmonicConstantTableView->setModel(m_harmonicConstantTableModel);

    int width = 15;
    for (int i = 0; i<m_harmonicConstantTableView->model()->columnCount(QModelIndex()); ++i){
        width+=m_harmonicConstantTableView->columnWidth(i);
    }
    m_harmonicConstantTableView->setMinimumWidth(width);

    m_harmonicConstantTableView->hide();

    m_radiosButtonGroupBox = new QGroupBox(this);
    m_luRadioButton = new QRadioButton(tr("Descomposicion LU"),this);
    m_luRadioButton->setChecked(true);
    m_svdRadioButton = new QRadioButton(tr("SVD"),this);

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

    m_saveSelectedData = new QPushButton(tr("Guardar Datos"));
    connect(m_saveSelectedData,SIGNAL(clicked(bool)),this,SIGNAL(saveDataButtonClicked()));

    //********************************************************************

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
    bottomLayout->addWidget(m_analizandoProgressBar);

    QHBoxLayout *radioLayout = new QHBoxLayout;
    radioLayout->addWidget(m_luRadioButton);
    radioLayout->addWidget(m_svdRadioButton);
    m_radiosButtonGroupBox->setLayout(radioLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(upLayout);
    mainLayout->addWidget(m_componentGroupBox);
    mainLayout->addWidget(m_descriptionGroupBox);
    mainLayout->addWidget(m_radiosButtonGroupBox);
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
    mainLeftLayout->addWidget(m_saveSelectedData);

    m_dataSelectionGroupBox->setLayout(mainLeftLayout);


    //**********************************************************

    QHBoxLayout *definiteLayout = new QHBoxLayout;
    definiteLayout->addWidget(m_dataSelectionGroupBox);
    definiteLayout->addWidget(analisisGroupBox);
    definiteLayout->addWidget(m_harmonicConstantTableView);

    this->setLayout(definiteLayout);
}

