#include "loaddialog.h"

#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QComboBox>
#include <QIntValidator>

#include <QLabel>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTextBlock>
#include <QSpinBox>
#include <QRadioButton>
#include <QProgressBar>

#include <iostream>
using namespace std;


LoadDialog::LoadDialog(QWidget *parent)
    : QDialog(parent)
{
    settingUpEveryThing();
}

LoadDialog::LoadDialog(const QString &filePath, QWidget *parent): QDialog(parent)
{

    Qt::WindowFlags flags = Qt::Dialog | Qt::WindowCloseButtonHint;
    this->setWindowFlags(flags);
    settingUpEveryThing();
    QFile file(filePath);

    if (file.open(QIODevice::ReadOnly)){
        QTextStream in(&file);
        QString text = in.readAll();
        m_importTextEdit->setPlainText(text);

        m_firstLineLineEdit->setMaximum(m_importTextEdit->blockCount());
        m_lastLineLineEdit->setMaximum(m_importTextEdit->blockCount());

        setTopFieldValidValue(1);

    }else{
        QMessageBox::information(this,tr("Marea"),tr("No se puede leer el archivo %1:\n%2.")
                                     .arg(file.fileName().arg(file.errorString())));
    }

    this->setWindowIcon(QIcon(":images/import.png"));
    this->setWindowTitle(tr("Importar Datos"));
}

LoadDialog::~LoadDialog()
{

}

bool LoadDialog::isLevelRadioButtonChecked()
{
    return m_levelRadioButton->isChecked();
}

void LoadDialog::setProjectMetaData(const ProjectMetaData &metadata)
{
    m_metaDataWidget->setProjectName(metadata.projectName());
    m_metaDataWidget->setStationName(metadata.stationName());
    m_metaDataWidget->setLocalizationName(metadata.localizationName());
    m_metaDataWidget->setCeroPuestoValueAndUnit(metadata.ceroUnit(),metadata.ceroPuesto());
    m_metaDataWidget->setNivelReferenciaValueAndUnit(metadata.referenciaUnit(),metadata.nivelReferencia());
    m_metaDataWidget->setLatitud(metadata.latitud());
    m_metaDataWidget->setLongitud(metadata.longitud());
    m_metaDataWidget->setEquipmentID(metadata.equipmentID());
}

/*QString LoadDialog::loacationName() const
{
    return m_locationLineEdit->text();
}

QString LoadDialog::equipmentID() const
{
    return m_equipmentIDLineEdit->text();
}

QString LoadDialog::latitud() const
{
    return m_latitudLineEdit->text();
}

QString LoadDialog::longitud() const
{
    return m_longitudLineEdit->text();
}*/


void LoadDialog::getDataPoints(){
    measurements.clear();

    int unitIndex = m_measurementUnitComboBox->currentIndex();
    //0 - m
    //1 - dm
    //2 - cm
    //3 - mm
    qreal unitScale = 1.0;
    switch (unitIndex) {
    case 1:
        unitScale/=10;
        break;
    case 2:
        unitScale/=100;
        break;
    case 3:
        unitScale/=1000;
        break;
    default:
        break;
    }

    int from = m_firstLineLineEdit->value();
    int to = m_lastLineLineEdit->value();

    m_importProgressBar->setMaximum((to - from + 1)*2);

    int pro = 0;

    QString dateSeparator = m_separatorDateEdit->text();
    QString timeSeparator = m_separatorTimeEdit->text();
    QString levelSeparator = m_separatorHeigthEdit->text();

    if (from <= to){
        QVector<QStringList> pointsOfData;
        for (int i = from-1; i < to; i++){
            QString str = m_importTextEdit->document()->findBlockByLineNumber(i).text();
            QStringList dataPoint = str.split(QRegExp(tr("[\\s+%1%2%3]").arg(dateSeparator).arg(timeSeparator).arg(levelSeparator)));
            pointsOfData.push_back(dataPoint);
            ++pro;
            m_importProgressBar->setValue(pro);
        }

        int dateField  = m_fieldDateEdit->value();
        int timeField  = m_fieldTimeEdit->value();
        int heightField  = m_fieldHeightEdit->value();

        int desition = QMessageBox::Yes;

        for (int i = 0; i < pointsOfData.size(); ++i){
            if (dateField <= pointsOfData[i].size() && timeField <= pointsOfData[i].size() && heightField <= pointsOfData[i].size()){ //Chequea que el campo exista

                QDate date = QDate::fromString(pointsOfData[i].at(dateField - 1),m_dateFormat);
                QTime time = QTime::fromString(pointsOfData[i].at(timeField - 1),m_timeFormat);

                QString level = pointsOfData[i].at(heightField - 1);
                /*for (int i  = 0; i < level.size(); ++i){
                   if (level.at(i) == ",") level.replace(Q)
                }*/
                level.replace(QRegExp(","),".");

                bool d_ok;
                QVariant heightVariant = level;
                double height = heightVariant.toDouble(&d_ok);
                height*=unitScale; //Conversion de unidades llevando a metros

                ++pro; //Progress Bar
                m_importProgressBar->setValue(pro);

                if (date.isValid() && time.isValid() && d_ok){
                    measurements.push_back(TidesMeasurement(height,date,time));
                }else{
                    desition = QMessageBox::question(this,tr("Advertencia"),tr("Falla al cargar datos. \n"
                                                              " Posibles Causas: \n"
                                                                   "1- Formato de fecha o hora no válidos. \n"
                                                                   "2- Número de campos incorrectos. \n"
                                                                   "3- Número de líneas incorrectos. \n"
                                                                    "¿Desea continuar?"));
                    if (desition == QMessageBox::No) break;
                }

            }

        }
        if (desition == QMessageBox::Yes) emit importButtonClicked();
        return;
    }else{
        QMessageBox::critical(this,tr("Error"),tr("Falla al cargar datos."
                                                  " La linea final es menor que la linea inicial."));
        return;
    }
}

void LoadDialog::setTopFieldValidValue(int value)
{
    QString dateSeparator = m_separatorDateEdit->text();
    QString timeSeparator = m_separatorTimeEdit->text();
    QString levelSeparator = m_separatorHeigthEdit->text();

    QString str = m_importTextEdit->document()->findBlockByLineNumber(value - 1).text();
    QStringList dataPoint = str.split(QRegExp(tr("[\\s+%1%2%3]").arg(dateSeparator).arg(timeSeparator).arg(levelSeparator)));
    m_fieldDateEdit->setRange(1,dataPoint.size());
    m_fieldTimeEdit->setRange(1,dataPoint.size());
    m_fieldHeightEdit->setRange(1,dataPoint.size());
}

void LoadDialog::setTopFieldValidValue()
{
    int firstLine = m_firstLineLineEdit->value();
    setTopFieldValidValue(firstLine);
    fillFirstAndLastDataPoints();
}

void LoadDialog::enableFieldEditorsEdition()
{
    if (m_firstLineLineEdit->text().isEmpty() || m_lastLineLineEdit->text().isEmpty()){
        m_fieldDateEdit->setDisabled(true);
        m_fieldTimeEdit->setDisabled(true);
        m_fieldHeightEdit->setDisabled(true);

    }else{
        m_fieldDateEdit->setEnabled(true);
        m_fieldTimeEdit->setEnabled(true);
        m_fieldHeightEdit->setEnabled(true);
    }
}

void LoadDialog::enableImportButton()
{
     if (m_timeFormat != "otro" && m_dateFormat != "otro" && !m_dateFormat.isEmpty() && !m_timeFormat.isEmpty() && m_fieldDateEdit->value() && m_fieldTimeEdit->value()
             && m_fieldHeightEdit->value() && m_fieldDateEdit->value() != m_fieldTimeEdit->value()
             && m_fieldDateEdit->value() != m_fieldHeightEdit->value() && m_fieldTimeEdit->value() != m_fieldHeightEdit->value()){
         m_importButton->setEnabled(true);
     }else{
         m_importButton->setDisabled(true);
     }
}

void LoadDialog::fillFirstAndLastDataPoints() //conectado los edit de primera y ultima linea
{
    fillFirstAndLastDate(m_fieldDateEdit->value());
    fillFirstAndLastTime(m_fieldTimeEdit->value());
    fillFirstAndLastHeigth(m_fieldHeightEdit->value());
}

void LoadDialog::fillFirstAndLastDate(int index)
{
    int first = m_firstLineLineEdit->value();
    int last = m_lastLineLineEdit->value();

    QString dateSeparator = m_separatorDateEdit->text();
    QString timeSeparator = m_separatorTimeEdit->text();
    QString levelSeparator = m_separatorHeigthEdit->text();

    QString str1 = m_importTextEdit->document()->findBlockByLineNumber(first - 1).text(); //Reading the line
    QStringList dataPoint1 = str1.split(QRegExp(tr("[\\s+%1%2%3]").arg(dateSeparator).arg(timeSeparator).arg(levelSeparator)));

    QString str2 = m_importTextEdit->document()->findBlockByLineNumber(last - 1).text();   //Reading the line
    QStringList dataPoint2 = str2.split(QRegExp(tr("[\\s+%1%2%3]").arg(dateSeparator).arg(timeSeparator).arg(levelSeparator)));
    if (index <= dataPoint1.size())
        m_firstPointDateEdit->setText(dataPoint1.at(index - 1));
    else m_firstPointDateEdit->setText(tr(""));

    if (index <= dataPoint2.size())
        m_lastPointDateEdit->setText(dataPoint2.at(index - 1));
    else m_lastPointDateEdit->setText("");

}

void LoadDialog::fillFirstAndLastTime(int index)
{
    int first = m_firstLineLineEdit->value();
    int last = m_lastLineLineEdit->value();

    QString dateSeparator = m_separatorDateEdit->text();
    QString timeSeparator = m_separatorTimeEdit->text();
    QString levelSeparator = m_separatorHeigthEdit->text();

    QString str1 = m_importTextEdit->document()->findBlockByLineNumber(first - 1).text(); //Reading the line
    QStringList dataPoint1 = str1.split(QRegExp(tr("[\\s+%1%2%3]").arg(dateSeparator).arg(timeSeparator).arg(levelSeparator)));

    QString str2 = m_importTextEdit->document()->findBlockByLineNumber(last - 1).text();   //Reading the line
    QStringList dataPoint2 = str2.split(QRegExp(tr("[\\s+%1%2%3]").arg(dateSeparator).arg(timeSeparator).arg(levelSeparator)));

    if (index <= dataPoint1.size())
        m_firstPointTimeEdit->setText(dataPoint1.at(index - 1));
    else m_firstPointTimeEdit->setText(tr(""));

    if (index <= dataPoint2.size())
        m_lastPointTimeEdit->setText(dataPoint2.at(index - 1));
    else m_lastPointTimeEdit->setText("");
}

void LoadDialog::fillFirstAndLastHeigth(int index)
{
    int first = m_firstLineLineEdit->value();
    int last = m_lastLineLineEdit->value();

    QString dateSeparator = m_separatorDateEdit->text();
    QString timeSeparator = m_separatorTimeEdit->text();
    QString levelSeparator = m_separatorHeigthEdit->text();

    QString str1 = m_importTextEdit->document()->findBlockByLineNumber(first - 1).text(); //Reading the line
    QStringList dataPoint1 = str1.split(QRegExp(tr("[\\s+%1%2%3]").arg(dateSeparator).arg(timeSeparator).arg(levelSeparator)));

    QString str2 = m_importTextEdit->document()->findBlockByLineNumber(last - 1).text();   //Reading the line
    QStringList dataPoint2 = str2.split(QRegExp(tr("[\\s+%1%2%3]").arg(dateSeparator).arg(timeSeparator).arg(levelSeparator)));

    if (index <= dataPoint1.size())
        m_firstPointHeigthEdit->setText(dataPoint1.at(index - 1));
    else m_firstPointHeigthEdit->setText(tr(""));

    if (index <= dataPoint2.size())
        m_lastPointHeigthEdit->setText(dataPoint2.at(index - 1));
    else m_lastPointHeigthEdit->setText("");
}

/*void LoadDialog::enableTimeFormatEdit(const QString &str)
{
    if (str == "otro"){
        m_timeFormatLineEdit->setEnabled(true);
    }else{
        m_timeFormatLineEdit->setDisabled(true);
    }
}*/

/*void LoadDialog::enableDateFormatEdit(const QString &str)
{
    if (str == "otro"){
        m_dateFormatLineEdit->setEnabled(true);
    }else{
        m_dateFormatLineEdit->setDisabled(true);
    }
}*/

void LoadDialog::setTimeFormat(const QString &format)
{
    if (format == "otro"){
        m_timeFormatLineEdit->setEnabled(true);
    }else{
        m_timeFormatLineEdit->setDisabled(true);
    }

    m_timeFormat = format;

    enableImportButton();
}

void LoadDialog::setDateFormat(const QString &format)
{
    if (format == "otro"){
        m_dateFormatLineEdit->setEnabled(true);
    }else{
        m_dateFormatLineEdit->setDisabled(true);
    }

    m_dateFormat = format;

    enableImportButton();
}

void LoadDialog::setCustomTimeFormat(const QString &format)
{
    m_timeFormat = format;
}

void LoadDialog::setCustomDateFormat(const QString &format)
{
    m_dateFormat = format;
}

void LoadDialog::setMinimumLastLineValue(int value)
{
    if (m_lastLineLineEdit->value() < value ) m_lastLineLineEdit->setValue(value);

    m_lastLineLineEdit->setMinimum(value);
}


void LoadDialog::settingUpEveryThing()
{
    this->setWindowTitle(tr("Importar Datos"));
    m_importTextEdit = new LineNumberEditor(this);
    m_importTextEdit->setReadOnly(true);
    //m_importTextEdit->setFixedHeight(250);
    m_importTextEdit->setFixedWidth(500);

    m_metaDataWidget = new metaDataWidget;

    m_dateLabel = new QLabel(tr("Fecha"),this);
    m_dateLabel->setAlignment(Qt::AlignVCenter);
    m_timeLabel = new QLabel(tr("Hora"),this);
    m_timeLabel->setAlignment(Qt::AlignVCenter);
    m_heigthLabel = new QLabel(tr("Nivel"),this);
    m_heigthLabel->setAlignment(Qt::AlignVCenter);

    m_fieldLabel = new QLabel(tr("Campo"),this);
    m_fieldLabel->setAlignment(Qt::AlignHCenter);
    m_separatorLabel = new QLabel(tr("Separador"),this);
    m_separatorLabel->setAlignment(Qt::AlignHCenter);
    m_firstPointLabel = new QLabel(tr("Primera Medición"), this);
    m_firstPointLabel->setAlignment(Qt::AlignHCenter);
    m_lastPointLabel = new QLabel(tr("Última Medición"), this);
    m_lastPointLabel->setAlignment(Qt::AlignHCenter);

    m_fieldDateEdit = new QSpinBox(this);
    //m_fieldDateEdit->setDisabled(true);
    connect(m_fieldDateEdit,SIGNAL(valueChanged(int)),this,SLOT(enableImportButton()));
    connect(m_fieldDateEdit,SIGNAL(valueChanged(int)),this,SLOT(fillFirstAndLastDate(int)));
    m_fieldTimeEdit = new QSpinBox(this);
    //m_fieldTimeEdit->setDisabled(true);
    connect(m_fieldTimeEdit,SIGNAL(valueChanged(int)),this,SLOT(enableImportButton()));
    connect(m_fieldTimeEdit,SIGNAL(valueChanged(int)),this,SLOT(fillFirstAndLastTime(int)));
    m_fieldHeightEdit = new QSpinBox(this);
    //m_fieldHeightEdit->setDisabled(true);
    connect(m_fieldHeightEdit,SIGNAL(valueChanged(int)),this,SLOT(enableImportButton()));
    connect(m_fieldHeightEdit,SIGNAL(valueChanged(int)),this,SLOT(fillFirstAndLastHeigth(int)));

    //m_fieldDateEdit->setMinimum(1);
    //m_fieldTimeEdit->setMinimum(1);
    //m_fieldHeightEdit->setMinimum(1);

    //m_fieldValidator = new QIntValidator;  //Validator
    //m_fieldValidator->setBottom(1);

    //m_fieldDateEdit->setValidator(m_fieldValidator);
    //m_fieldTimeEdit->setValidator(m_fieldValidator);
    //m_fieldHeightEdit->setValidator(m_fieldValidator);

    m_separatorDateEdit = new QLineEdit(this);
    m_separatorDateEdit->setAlignment(Qt::AlignRight);
    connect(m_separatorDateEdit,SIGNAL(textChanged(QString)),this,SLOT(setTopFieldValidValue()));
    m_separatorTimeEdit = new QLineEdit(this);
    m_separatorTimeEdit->setAlignment(Qt::AlignRight);
    connect(m_separatorTimeEdit,SIGNAL(textChanged(QString)),this,SLOT(setTopFieldValidValue()));
    m_separatorHeigthEdit = new QLineEdit(this);
    m_separatorHeigthEdit->setAlignment(Qt::AlignRight);
    connect(m_separatorHeigthEdit,SIGNAL(textChanged(QString)),this,SLOT(setTopFieldValidValue()));

    m_firstPointDateEdit = new QLineEdit(this);
    m_firstPointDateEdit->setDisabled(true);
    m_firstPointTimeEdit = new QLineEdit(this);
    m_firstPointTimeEdit->setDisabled(true);
    m_firstPointHeigthEdit = new QLineEdit(this);
    m_firstPointHeigthEdit->setDisabled(true);

    m_lastPointDateEdit = new QLineEdit(this);
    m_lastPointDateEdit->setDisabled(true);
    m_lastPointTimeEdit = new QLineEdit(this);
    m_lastPointTimeEdit->setDisabled(true);
    m_lastPointHeigthEdit = new QLineEdit(this);
    m_lastPointHeigthEdit->setDisabled(true);

    m_importButton = new QPushButton(QIcon(":images/importButton.png"),tr("Importar"),this);
    m_importButton->setDisabled(true);
    connect(m_importButton,SIGNAL(clicked(bool)),this,SLOT(getDataPoints()));
    //connect(m_importButton,SIGNAL(clicked(bool)),this,SIGNAL(importButtonClicked()));

    m_cancelButton = new QPushButton(QIcon(":images/No.png"),tr("Cancelar"),this);
    connect(m_cancelButton,SIGNAL(clicked(bool)),this,SLOT(close()));

    //m_unitGroupBox = new QGroupBox(tr("Unidad de Medida:")); //GroupBox de Medidas
    //m_correctionGroupBox = new QGroupBox(tr("Corrección de Nivel")); //GrupoBox de Correciones
    m_firstLineGroupBox  = new QGroupBox(tr("Primera Línea:")); //GroupBox de carga de datos
    m_lastLineGroupBox  = new QGroupBox(tr("Última Línea:")); //GroupBox de carga de datos
    m_measurementUnitGroupBox = new QGroupBox(tr("Unidad de Medición:"),this);

    //m_unitComboBox = new QComboBox;   //ComboBox de unidad de medida
    //m_unitComboBox->addItem(tr("metros"));
    //m_unitComboBox->addItem(tr("centimetros"));

    //QHBoxLayout *unitLayout = new QHBoxLayout;
    //unitLayout->addWidget(m_unitComboBox);

    //m_unitGroupBox->setLayout(unitLayout);

    //QDoubleValidator *doubleValidator = new QDoubleValidator;

    //m_correctionLineEdit = new QLineEdit; //Line edit para correcciones
    //m_correctionLineEdit->setValidator(doubleValidator);

    //m_fValidator = new QIntValidator;
    //m_fValidator->setBottom(1);

    m_firstLineLineEdit = new QSpinBox; //LineEdit para linea de carga.
    m_firstLineLineEdit->setMinimum(1);
    connect(m_firstLineLineEdit,SIGNAL(valueChanged(int)),this,SLOT(setTopFieldValidValue(int)));
    connect(m_firstLineLineEdit,SIGNAL(valueChanged(int)),this,SLOT(setMinimumLastLineValue(int)));
    //connect(m_firstLineLineEdit,SIGNAL(valueChanged(int)),this,SLOT(enableFieldEditorsEdition()));
    connect(m_firstLineLineEdit,SIGNAL(valueChanged(int)),this,SLOT(fillFirstAndLastDataPoints()));

    QHBoxLayout *firstLineLayout = new QHBoxLayout;
    firstLineLayout->addWidget(m_firstLineLineEdit);

    m_firstLineGroupBox->setLayout(firstLineLayout);

    //m_lValidator = new QIntValidator;
    //m_lValidator->setBottom(1);

    m_lastLineLineEdit = new QSpinBox;
    m_lastLineLineEdit->setMinimum(1);
    //connect(m_lastLineLineEdit,SIGNAL(valueChanged(int)),this,SLOT(enableFieldEditorsEdition()));
    connect(m_lastLineLineEdit,SIGNAL(valueChanged(int)),this,SLOT(fillFirstAndLastDataPoints()));

    m_measurementUnitComboBox = new QComboBox;
    m_measurementUnitComboBox->addItem("m");
    m_measurementUnitComboBox->addItem("dm");
    m_measurementUnitComboBox->addItem("cm");
    m_measurementUnitComboBox->addItem("mm");

    QHBoxLayout *unitLayout = new QHBoxLayout;
    unitLayout->addWidget(m_measurementUnitComboBox);
    m_measurementUnitGroupBox->setLayout(unitLayout);

    QHBoxLayout *lastLineLayout = new QHBoxLayout;
    lastLineLayout->addWidget(m_lastLineLineEdit);

    m_lastLineGroupBox->setLayout(lastLineLayout);

    //QHBoxLayout *corrLayout = new QHBoxLayout;
    //corrLayout->addWidget(m_correctionLineEdit);

    //m_correctionGroupBox->setLayout(corrLayout);

    //Date and Time Format Facilities----------------
    m_dateFormatGroupBox = new QGroupBox(tr("Formato de Fecha:"));

    m_dateFormatLineEdit = new QLineEdit;
    m_dateFormatLineEdit->setDisabled(true);
    connect(m_dateFormatLineEdit,SIGNAL(textEdited(QString)),this,SLOT(setCustomDateFormat(QString)));
    connect(m_dateFormatLineEdit,SIGNAL(textEdited(QString)),this,SLOT(enableImportButton()));

    m_dateFormatComboBox = new QComboBox;
    m_dateFormatComboBox->addItem("yyyy/MM/dd");
    m_dateFormatComboBox->addItem("dd/MM/yyyy");
    m_dateFormatComboBox->addItem("d/MM/yyyy");
    m_dateFormatComboBox->addItem("d/M/yyyy");
    m_dateFormatComboBox->addItem("yyyy.MM.dd");
    m_dateFormatComboBox->addItem("dd.MM.yyyy");
    m_dateFormatComboBox->addItem("otro");

    m_dateFormat = m_dateFormatComboBox->currentText();

    connect(m_dateFormatComboBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(setDateFormat(QString)));
    //connect(m_dateFormatComboBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(enableDateFormatEdit(QString)));

    QVBoxLayout *dateFormatLayout = new QVBoxLayout;
    dateFormatLayout->addWidget(m_dateFormatComboBox);
    dateFormatLayout->addWidget(m_dateFormatLineEdit);
    m_dateFormatGroupBox->setLayout(dateFormatLayout);

    m_timeFormatGroupBox = new QGroupBox(tr("Formato de Hora:"));

    m_timeFormatLineEdit = new QLineEdit;
    m_timeFormatLineEdit->setDisabled(true);
    connect(m_timeFormatLineEdit,SIGNAL(textEdited(QString)),this,SLOT(setCustomTimeFormat(QString)));
    connect(m_timeFormatLineEdit,SIGNAL(textChanged(QString)),this,SLOT(enableImportButton()));

    m_timeFormatComboBox = new QComboBox;
    m_timeFormatComboBox->addItem("hh:mm:ss");
    m_timeFormatComboBox->addItem("h:mm:ss");
    m_timeFormatComboBox->addItem("hh:mm");
    m_timeFormatComboBox->addItem("h:mm");
    m_timeFormatComboBox->addItem("otro");

    m_timeFormat = m_timeFormatComboBox->currentText();

    connect(m_timeFormatComboBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(setTimeFormat(QString)));
    //connect(m_timeFormatComboBox,SIGNAL(currentIndexChanged(QStri)),this,SLOT(enableTimeFormatEdit(int)));

    QVBoxLayout *timeFormatLayout = new QVBoxLayout;
    timeFormatLayout->addWidget(m_timeFormatComboBox);
    timeFormatLayout->addWidget(m_timeFormatLineEdit);
    m_timeFormatGroupBox->setLayout(timeFormatLayout);

    //Layout medio superior---------------------------
    QHBoxLayout *layout1 = new QHBoxLayout;
    layout1->addWidget(m_firstLineGroupBox);
    layout1->addWidget(m_lastLineGroupBox);
    layout1->addWidget(m_measurementUnitGroupBox);

    QHBoxLayout *layout2 = new QHBoxLayout;
    layout2->addWidget(m_dateFormatGroupBox);
    layout2->addWidget(m_timeFormatGroupBox);

    //QVBoxLayout *layout3 = new QVBoxLayout;
    //layout3->addWidget(m_correctionGroupBox);
    //layout3->addWidget(m_unitGroupBox);

    QVBoxLayout *midtopLayout = new QVBoxLayout;
    midtopLayout->addLayout(layout1);
    midtopLayout->addSpacing(20);
    midtopLayout->addLayout(layout2);
    //midtopLayout->addLayout(layout3);


    //------------------------------------------------

    m_measurementGroupBox = new QGroupBox(this);

    QVBoxLayout *midLayout = new QVBoxLayout;

    midLayout->addLayout(midtopLayout);

    /*midLayout->addWidget(m_firstLineGroupBox,0,1);
    midLayout->addWidget(m_lastLineGroupBox,1,1);
    midLayout->addWidget(m_dateFormatGroupBox,0,2);
    midLayout->addWidget(m_timeFormatGroupBox,1,2);
    midLayout->addWidget(m_correctionGroupBox,0,3);
    midLayout->addWidget(m_unitGroupBox,1,3);*/


    QGridLayout *myLayout = new QGridLayout;

    QGroupBox *myBox = new QGroupBox;

    myLayout->addWidget(m_dateLabel,1,0);
    myLayout->addWidget(m_timeLabel,2,0);
    myLayout->addWidget(m_heigthLabel,3,0);

    myLayout->addWidget(m_fieldLabel,0,1);
    myLayout->addWidget(m_fieldDateEdit,1,1);
    myLayout->addWidget(m_fieldTimeEdit,2,1);
    myLayout->addWidget(m_fieldHeightEdit,3,1);

    myLayout->addWidget(m_separatorLabel,0,2);
    myLayout->addWidget(m_separatorDateEdit,1,2);
    myLayout->addWidget(m_separatorTimeEdit,2,2);
    myLayout->addWidget(m_separatorHeigthEdit,3,2);

    myLayout->addWidget(m_firstPointLabel,0,3);
    myLayout->addWidget(m_firstPointDateEdit,1,3);
    myLayout->addWidget(m_firstPointTimeEdit,2,3);
    myLayout->addWidget(m_firstPointHeigthEdit,3,3);

    myLayout->addWidget(m_lastPointLabel,0,4);
    myLayout->addWidget(m_lastPointDateEdit,1,4);
    myLayout->addWidget(m_lastPointTimeEdit,2,4);
    myLayout->addWidget(m_lastPointHeigthEdit,3,4);

    myBox->setLayout(myLayout);

    midLayout->addSpacing(20);

    midLayout->addWidget(myBox);

    m_measurementGroupBox->setLayout(midLayout);
    m_measurementGroupBox->setFixedWidth(350);

    m_importProgressBar = new QProgressBar(this);
    m_importProgressBar->setTextVisible(true);
    m_importProgressBar->setMinimum(0);

    //Location facilities-------------------------------

    /*m_localizationGroupBox = new QGroupBox;

    m_locationLineEdit = new QLineEdit;
    m_equipmentIDLineEdit =  new QLineEdit;
    m_latitudLineEdit = new QLineEdit;
    m_longitudLineEdit = new QLineEdit;

    m_locationLabel = new QLabel(tr("Localización"));
    m_equimentIDLabel = new QLabel(tr("ID del Equipo"));
    m_latitudLabel = new QLabel(tr("Latitud"));
    m_latitudLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    m_longitudLabel = new QLabel(tr("Longitud"));
    m_longitudLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    QGridLayout *locationLayout = new QGridLayout;
    locationLayout->addWidget(m_locationLabel,0,0);
    locationLayout->addWidget(m_locationLineEdit,0,1);
    locationLayout->addWidget(m_equimentIDLabel,0,2);
    locationLayout->addWidget(m_equipmentIDLineEdit,0,3);
    locationLayout->addWidget(m_latitudLabel,1,0);
    locationLayout->addWidget(m_latitudLineEdit,1,1);
    locationLayout->addWidget(m_longitudLabel,1,2);
    locationLayout->addWidget(m_longitudLineEdit,1,3);

    m_localizationGroupBox->setLayout(locationLayout);*/

    //---------------------------------------------------------

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(m_importProgressBar);
    //bottomLayout->addStretch();


    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(m_importButton);
    buttonLayout->addWidget(m_cancelButton);

    bottomLayout->addLayout(buttonLayout);

    QGroupBox *metaGroupBox = new QGroupBox;

    QHBoxLayout *metaLayout = new QHBoxLayout;
    metaLayout->addWidget(m_metaDataWidget);
    metaGroupBox->setLayout(metaLayout);

    QGroupBox *primaryData = new QGroupBox(tr("Tipo de Datos Primarios:"));
    m_corrRadioButton = new QRadioButton(tr("Correcciones"));
    m_corrRadioButton->setChecked(true);
    m_levelRadioButton = new QRadioButton(tr("Niveles"));

    QVBoxLayout *primaryDataTypeLayout = new QVBoxLayout;
    primaryDataTypeLayout->addWidget(m_corrRadioButton);
    primaryDataTypeLayout->addWidget(m_levelRadioButton);

    primaryData->setLayout(primaryDataTypeLayout);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(metaGroupBox);
    leftLayout->addWidget(primaryData);
    leftLayout->addWidget(m_measurementGroupBox);

    QHBoxLayout *mainUpperLayout = new QHBoxLayout;
    //mainUpperLayout->addWidget(m_dataWidget);
    mainUpperLayout->addLayout(leftLayout);
    //mainUpperLayout->addWidget(m_measurementGroupBox);
    mainUpperLayout->addWidget(m_importTextEdit);
    //mainLayout->addWidget(m_localizationGroupBox);
    //mainLayout->addLayout(bottomLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(mainUpperLayout);
    mainLayout->addLayout(bottomLayout);

    this->setLayout(mainLayout);

    this->setAttribute(Qt::WA_DeleteOnClose);
}
