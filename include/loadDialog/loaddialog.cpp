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

#include <iostream>
using namespace std;

//TODO: ver como exportamos los otros datos que se llenan en este dialogo.
LoadDialog::LoadDialog(QWidget *parent)
    : QDialog(parent)
{
    settingUpEveryThing();


}

LoadDialog::LoadDialog(const QString &filePath, QWidget *parent): QDialog(parent)
{

    //TODO: implementar que si filepath es un string vacio no se crea al dialogo esto de hace en la modulo principal
    settingUpEveryThing();
    QFile file(filePath);

    if (file.open(QIODevice::ReadOnly)){
        QTextStream in(&file);
        QString text = in.readAll();
        m_importTextEdit->setPlainText(text);

        m_fValidator->setTop(m_importTextEdit->blockCount());  //Set the max value that can be inserted to the number of block of the document
        m_lValidator->setTop(m_importTextEdit->blockCount());
    }else{
        QMessageBox::information(this,tr("Marea"),tr("No se puede leer el archivo %1:\n%2.")
                                     .arg(file.fileName().arg(file.errorString())));
    }
}

LoadDialog::~LoadDialog()
{

}

QString LoadDialog::loacationName() const
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
}

//TODO: ProgressBar vinculada al futuro padre del dialog
//TODO: Agregar comprobacion de que si en la ultima linea coincide en la cantidad de campos con la primera
//TODO: Ver como integramos cuando los edit de separadores no esten vacios.
//TODO: agregar que los numeros de campo tienen que ser diferentes.
void LoadDialog::getDataPoints()   //Retorna un Vector StringList con los datos de interes si algo falla retorna un Vector vacio
{
    measurements.clear();

    if (m_dateFormatLineEdit->text().isEmpty() || m_timeFormatLineEdit->text().isEmpty()){
        QMessageBox::critical(this,tr("Error"),tr("Falla al cargar datos."
                                                  " Formatos de fecha y hora no validos."));
        return;
    }
    bool b_ok;
    bool l_ok;
    int from = m_firstLineLineEdit->text().toInt(&b_ok);
    int to = m_lastLineLineEdit->text().toInt(&l_ok);

    if (b_ok && l_ok){
        if (from > m_importTextEdit->blockCount() || to > m_importTextEdit->blockCount()){
            QMessageBox::critical(this,tr("Error"),tr("Falla al cargar datos."
                                                      " Límite de líneas de texto exedidas."));
            //QVector<QStringList> empty;
            return;
        }
        if (from <= to){
            QVector<QStringList> pointsOfData;
            for (int i = from-1; i < to; i++){
                QString str = m_importTextEdit->document()->findBlockByLineNumber(i).text();
                QStringList dataPoint = str.split(QRegExp("\\s+")); //TODO: ver la cosa cuando existan separadores
                pointsOfData.push_back(dataPoint);


            }

            bool dateOk;
            bool timeOk;
            bool heightOk;

            int dateField  = m_fieldDateEdit->text().toInt(&dateOk);
            int timeField  = m_fieldTimeEdit->text().toInt(&timeOk);
            int heightField  = m_fieldHeightEdit->text().toInt(&heightOk);

            if (dateOk && timeOk && heightOk){
                for (int i = 0; i < pointsOfData.size(); ++i){
                    if (dateField <= pointsOfData[i].size() && timeField <= pointsOfData[i].size() && heightField <= pointsOfData[i].size()){ //Chequea que el campo exista

                        QDate date = QDate::fromString(pointsOfData[i].at(dateField - 1),m_dateFormatLineEdit->text());
                        QTime time = QTime::fromString(pointsOfData[i].at(timeField - 1), m_timeFormatLineEdit->text());

                        //TODO: Crear un chequeo para comprobar si se estan cargando bien los datos.

                        bool d_ok;
                        QVariant heightVariant = pointsOfData[i].at(heightField - 1);
                        double height = heightVariant.toDouble(&d_ok);

                        if (date.isValid() && time.isValid() && d_ok){
                            measurements.push_back(TidesMeasurement(height,date,time));
                        }

                    }

                }
                return;
            }
            QMessageBox::critical(this,tr("Error"),tr("Falla al cargar datos."
                                                      " Existen números de campo invalidos."));

            return;

        }else{
            QMessageBox::critical(this,tr("Error"),tr("Falla al cargar datos."
                                                      " La linea final es menor que la linea inicial."));
            //QVector<QStringList> empty;
            return;
        }
    }else{
        if (b_ok || l_ok){
            if (b_ok) QMessageBox::critical(this,tr("Error"),tr("Falla al cargar datos."
                                                                "Número de linea final invalido."));
            if (l_ok) QMessageBox::critical(this,tr("Error"),tr("Falla al cargar datos."
                                                                "Número de linea inicial invalido."));

        } else{
            QMessageBox::critical(this,tr("Error"),tr("Falla al cargar datos."
                                                          "Número de lineas inicial y final invalidas."));
        }

    }

    //QVector<QStringList> empty;
    //return empty;

}

void LoadDialog::setTopFieldValidValue(const QString &text)
{
    bool ok;

    int top = text.toInt(&ok);

    if (ok){
        QString str = m_importTextEdit->document()->findBlockByLineNumber(top - 1).text();
        QStringList dataPoint = str.split(QRegExp("\\s+"));
        m_fieldValidator->setTop(dataPoint.size());
    }

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
    if (m_dateFormatLineEdit->text().isEmpty() || m_timeFormatLineEdit->text().isEmpty() || !m_fieldDateEdit->isEnabled()
            || m_fieldDateEdit->text().isEmpty() || m_fieldTimeEdit->text().isEmpty() || m_fieldHeightEdit->text().isEmpty()){
        m_importButton->setDisabled(true);
    }else{
        m_importButton->setEnabled(true);
    }
}

void LoadDialog::fillFirstAndLastDataPoints()
{
    if (!m_fieldDateEdit->isEnabled() || m_fieldDateEdit->text().isEmpty() || m_fieldTimeEdit->text().isEmpty()
            || m_fieldHeightEdit->text().isEmpty()){
        m_firstPointDateEdit->setText("");
        m_firstPointTimeEdit->setText("");
        m_firstPointHeigthEdit->setText("");

        m_lastPointDateEdit->setText("");
        m_lastPointTimeEdit->setText("");
        m_lastPointHeigthEdit->setText("");
    }else{
        int first = m_firstLineLineEdit->text().toInt();
        int last = m_lastLineLineEdit->text().toInt();
        QString str1 = m_importTextEdit->document()->findBlockByLineNumber(first - 1).text(); //Reading the line
        QStringList dataPoint1 = str1.split(QRegExp("\\s+"));  //TODO: ver la cosa cuando existan separadores

        QString str2 = m_importTextEdit->document()->findBlockByLineNumber(last - 1).text();   //Reading the line
        QStringList dataPoint2 = str2.split(QRegExp("\\s+"));  //TODO: ver la cosa cuando existan separadores

        m_firstPointDateEdit->setText(dataPoint1.at(m_fieldDateEdit->text().toInt() - 1));
        m_firstPointTimeEdit->setText(dataPoint1.at(m_fieldTimeEdit->text().toInt() - 1));
        m_firstPointHeigthEdit->setText(dataPoint1.at(m_fieldHeightEdit->text().toInt() - 1));

        m_lastPointDateEdit->setText(dataPoint2.at(m_fieldDateEdit->text().toInt() - 1));
        m_lastPointTimeEdit->setText(dataPoint2.at(m_fieldTimeEdit->text().toInt() - 1));
        m_lastPointHeigthEdit->setText(dataPoint2.at(m_fieldHeightEdit->text().toInt() - 1));
    }
}


void LoadDialog::settingUpEveryThing()
{
    this->setWindowTitle(tr("Importar Datos"));
    m_importTextEdit = new LineNumberEditor(this);
    m_importTextEdit->setReadOnly(true);
    m_importTextEdit->setFixedHeight(250);

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

    m_fieldDateEdit = new QLineEdit(this);
    m_fieldDateEdit->setDisabled(true);
    connect(m_fieldDateEdit,SIGNAL(textChanged(QString)),this,SLOT(enableImportButton()));
    connect(m_fieldDateEdit,SIGNAL(textChanged(QString)),this,SLOT(fillFirstAndLastDataPoints()));
    m_fieldTimeEdit = new QLineEdit(this);
    m_fieldTimeEdit->setDisabled(true);
    connect(m_fieldTimeEdit,SIGNAL(textChanged(QString)),this,SLOT(enableImportButton()));
    connect(m_fieldTimeEdit,SIGNAL(textChanged(QString)),this,SLOT(fillFirstAndLastDataPoints()));
    m_fieldHeightEdit = new QLineEdit(this);
    m_fieldHeightEdit->setDisabled(true);
    connect(m_fieldHeightEdit,SIGNAL(textChanged(QString)),this,SLOT(enableImportButton()));
    connect(m_fieldHeightEdit,SIGNAL(textChanged(QString)),this,SLOT(fillFirstAndLastDataPoints()));

    m_fieldValidator = new QIntValidator;  //Validator
    m_fieldValidator->setBottom(1);

    m_fieldDateEdit->setValidator(m_fieldValidator);
    m_fieldTimeEdit->setValidator(m_fieldValidator);
    m_fieldHeightEdit->setValidator(m_fieldValidator);

    m_separatorDateEdit = new QLineEdit(this);
    m_separatorTimeEdit = new QLineEdit(this);
    m_separatorHeigthEdit = new QLineEdit(this);

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

    m_importButton = new QPushButton(tr("Importar"),this);
    m_importButton->setDisabled(true);
    connect(m_importButton,SIGNAL(clicked(bool)),this,SLOT(getDataPoints()));
    connect(m_importButton,SIGNAL(clicked(bool)),this,SIGNAL(importButtonClicked()));

    m_cancelButton = new QPushButton(tr("Cancel"),this);
    connect(m_cancelButton,SIGNAL(clicked(bool)),this,SLOT(close()));

    m_unitGroupBox = new QGroupBox(tr("Unidad de Medición")); //GroupBox de Medidas
    m_correctionGroupBox = new QGroupBox(tr("Corrección de Nivel")); //GrupoBox de Correciones
    m_firstLineGroupBox  = new QGroupBox(tr("Primera Línea")); //GroupBox de carga de datos
    m_lastLineGroupBox  = new QGroupBox(tr("Última Línea")); //GroupBox de carga de datos

    m_unitComboBox = new QComboBox;   //ComboBox de unidad de medida
    m_unitComboBox->addItem(tr("metros"));
    m_unitComboBox->addItem(tr("centimetros"));

    QHBoxLayout *unitLayout = new QHBoxLayout;
    unitLayout->addWidget(m_unitComboBox);

    m_unitGroupBox->setLayout(unitLayout);

    QDoubleValidator *doubleValidator = new QDoubleValidator;

    m_correctionLineEdit = new QLineEdit; //Line edit para correcciones
    m_correctionLineEdit->setValidator(doubleValidator);

    m_fValidator = new QIntValidator;
    m_fValidator->setBottom(1);
    m_firstLineLineEdit = new QLineEdit; //LineEdit para linea de carga.
    m_firstLineLineEdit->setValidator(m_fValidator);
    connect(m_firstLineLineEdit,SIGNAL(textChanged(QString)),this,SLOT(setTopFieldValidValue(QString)));
    connect(m_firstLineLineEdit, SIGNAL(textChanged(QString)),this,SLOT(enableFieldEditorsEdition()));
    connect(m_firstLineLineEdit,SIGNAL(textChanged(QString)),this,SLOT(fillFirstAndLastDataPoints()));

    QHBoxLayout *firstLineLayout = new QHBoxLayout;
    firstLineLayout->addWidget(m_firstLineLineEdit);

    m_firstLineGroupBox->setLayout(firstLineLayout);

    m_lValidator = new QIntValidator;
    m_lValidator->setBottom(1);
    m_lastLineLineEdit = new QLineEdit;
    m_lastLineLineEdit->setValidator(m_lValidator);
    connect(m_lastLineLineEdit, SIGNAL(textEdited(QString)),this,SLOT(enableFieldEditorsEdition()));
    connect(m_lastLineLineEdit,SIGNAL(textChanged(QString)),this,SLOT(fillFirstAndLastDataPoints()));

    QHBoxLayout *lastLineLayout = new QHBoxLayout;
    lastLineLayout->addWidget(m_lastLineLineEdit);

    m_lastLineGroupBox->setLayout(lastLineLayout);

    QHBoxLayout *corrLayout = new QHBoxLayout;
    corrLayout->addWidget(m_correctionLineEdit);

    m_correctionGroupBox->setLayout(corrLayout);

    //TODO: Implementar RegExp
    //Date and Time Format Facilities----------------
    m_dateFormatGroupBox = new QGroupBox(tr("Formato de Fecha"));
    m_dateFormatLineEdit = new QLineEdit;
    connect(m_dateFormatLineEdit,SIGNAL(textChanged(QString)),this,SLOT(enableImportButton()));
    QHBoxLayout *dateFormatLayout = new QHBoxLayout;
    dateFormatLayout->addWidget(m_dateFormatLineEdit);
    m_dateFormatGroupBox->setLayout(dateFormatLayout);

    m_timeFormatGroupBox = new QGroupBox(tr("Formato de Hora"));
    m_timeFormatLineEdit = new QLineEdit;
    connect(m_timeFormatLineEdit,SIGNAL(textChanged(QString)),this,SLOT(enableImportButton()));
    QHBoxLayout *timeFormatLayout = new QHBoxLayout;
    timeFormatLayout->addWidget(m_timeFormatLineEdit);
    m_timeFormatGroupBox->setLayout(timeFormatLayout);

    //Layout medio superior---------------------------
    QVBoxLayout *layout1 = new QVBoxLayout;
    layout1->addWidget(m_firstLineGroupBox);
    layout1->addWidget(m_lastLineGroupBox);

    QVBoxLayout *layout2 = new QVBoxLayout;
    layout2->addWidget(m_dateFormatGroupBox);
    layout2->addWidget(m_timeFormatGroupBox);

    QVBoxLayout *layout3 = new QVBoxLayout;
    layout3->addWidget(m_correctionGroupBox);
    layout3->addWidget(m_unitGroupBox);

    QHBoxLayout *midtopLayout = new QHBoxLayout;
    midtopLayout->addLayout(layout1);
    midtopLayout->addLayout(layout2);
    midtopLayout->addLayout(layout3);


    //------------------------------------------------

    m_measurementGroupBox = new QGroupBox(this);

    QGridLayout *midLayout = new QGridLayout;

    midLayout->addLayout(midtopLayout,0,1,2,4);

    /*midLayout->addWidget(m_firstLineGroupBox,0,1);
    midLayout->addWidget(m_lastLineGroupBox,1,1);
    midLayout->addWidget(m_dateFormatGroupBox,0,2);
    midLayout->addWidget(m_timeFormatGroupBox,1,2);
    midLayout->addWidget(m_correctionGroupBox,0,3);
    midLayout->addWidget(m_unitGroupBox,1,3);*/




    midLayout->addWidget(m_dateLabel,3,0);
    midLayout->addWidget(m_timeLabel,4,0);
    midLayout->addWidget(m_heigthLabel,5,0);

    midLayout->addWidget(m_fieldLabel,2,1);
    midLayout->addWidget(m_fieldDateEdit,3,1);
    midLayout->addWidget(m_fieldTimeEdit,4,1);
    midLayout->addWidget(m_fieldHeightEdit,5,1);

    midLayout->addWidget(m_separatorLabel,2,2);
    midLayout->addWidget(m_separatorDateEdit,3,2);
    midLayout->addWidget(m_separatorTimeEdit,4,2);
    midLayout->addWidget(m_separatorHeigthEdit,5,2);

    midLayout->addWidget(m_firstPointLabel,2,3);
    midLayout->addWidget(m_firstPointDateEdit,3,3);
    midLayout->addWidget(m_firstPointTimeEdit,4,3);
    midLayout->addWidget(m_firstPointHeigthEdit,5,3);

    midLayout->addWidget(m_lastPointLabel,2,4);
    midLayout->addWidget(m_lastPointDateEdit,3,4);
    midLayout->addWidget(m_lastPointTimeEdit,4,4);
    midLayout->addWidget(m_lastPointHeigthEdit,5,4);



    m_measurementGroupBox->setLayout(midLayout);

    //Location facilities-------------------------------

    m_localizationGroupBox = new QGroupBox;

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

    m_localizationGroupBox->setLayout(locationLayout);

    //---------------------------------------------------------

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addStretch();

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(m_importButton);
    buttonLayout->addWidget(m_cancelButton);

    bottomLayout->addLayout(buttonLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_importTextEdit);
    mainLayout->addWidget(m_measurementGroupBox);
    mainLayout->addWidget(m_localizationGroupBox);
    mainLayout->addLayout(bottomLayout);

    this->setLayout(mainLayout);

    this->setAttribute(Qt::WA_DeleteOnClose);
}
