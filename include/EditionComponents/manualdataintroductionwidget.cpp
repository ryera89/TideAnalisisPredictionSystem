#include "manualdataintroductionwidget.h"
#include "include/model_view/tidaltabledelegate.h"


#include <iostream>

#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QComboBox>
#include <QTimeEdit>
#include <QDateEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHeaderView>
#include <QMessageBox>

ManualDataIntroductionWidget::ManualDataIntroductionWidget(QWidget *parent) : QDialog(parent)
{
    m_model = new TableModel(this);

    m_timeInterval = 3600;

    createComponents();

    m_editionTable->setModel(m_model);
    m_editionTable->setItemDelegate(new TidalTableDelegate(this));

    settingTableWidth();

    this->setFixedSize(sizeHint());

    this->setAttribute(Qt::WA_DeleteOnClose);

}

void ManualDataIntroductionWidget::setMinimumDateEditValue(const QDate &date)
{
    if (m_endDateEdit->date() < date){
        m_endDateEdit->setDate(date);
    }
    m_endDateEdit->setMinimumDate(date);
}

void ManualDataIntroductionWidget::enableTimeIntervalEdit(int index)
{
    if (index == 3){
        m_timeIntervalTimeEdit->setEnabled(true);
    }else{
        if (m_timeIntervalTimeEdit->isEnabled()){
            m_timeIntervalTimeEdit->setDisabled(true);
        }
    }
}

void ManualDataIntroductionWidget::updateTimeInterval(int index)
{
    switch (index) {
    case 0:
        m_timeInterval = 3600;
        break;
    case 1:
        m_timeInterval = 1800;
        break;
    case 2:
        m_timeInterval = 300;
        break;
    case 3:
        m_timeInterval = m_timeIntervalTimeEdit->time().hour()*3600 + m_timeIntervalTimeEdit->time().minute()*60 + m_timeIntervalTimeEdit->time().second();
        break;
    default:
        break;
    }

    //std::cout << m_timeInterval << std::endl;
}

void ManualDataIntroductionWidget::setTimeInterval(const QTime &time)
{
    m_timeInterval = time.hour()*3600 + time.minute()*60 + time.second();

    //std::cout << m_timeInterval << std::endl;
}

void ManualDataIntroductionWidget::removeLastMeasurement()
{
    m_model->removeRow(m_model->measurementData().size() - 1,QModelIndex());
}

void ManualDataIntroductionWidget::insertMeasurement()
{
    m_model->insertRow(m_model->measurementData().size(),QModelIndex());
}

void ManualDataIntroductionWidget::clearMeasurements()
{
    int button = QMessageBox::question(this,tr("Introducción manual de datos"),tr("Se borraran todos los datos,"
                                                                    "¿Desea continuar?"));
    if (button == QMessageBox::Yes){
        m_model->removeRows(0,m_model->rowCount(QModelIndex()) - 1,QModelIndex());
    }
}

/*void ManualDataIntroductionWidget::beginDataTranfer()
{
    QVector<TidesMeasurement> datos;

    for (int i = (m_model->rowCount(QModelIndex())-1); i >= 0; --i){
        if (m_model->measurementData().at(i).isValid()){
            datos.push_front(m_model->measurementData().at(i));
        }
       // m_model->removeRow(i,QModelIndex());
    }
    emit dataTrenfer(datos);

    this->close();

}*/

void ManualDataIntroductionWidget::generateData()
{
    QDateTime begin = QDateTime(m_iniDateEdit->date(),m_iniTimeEdit->time(),Qt::UTC);
    QDateTime end = QDateTime(m_endDateEdit->date(),m_endTimeEdit->time(),Qt::UTC);

    if (begin > end){
        QMessageBox::information(this,tr("Error de Tiempo"),tr("El momento de tiempo de inicio de las mediciones /n "
                                                               "no puede ser mayor que el momento de tiempo de fin."));
        return;
    }

    int seconds = begin.secsTo(end);

    if (seconds % m_timeInterval){
        QMessageBox::information(this,tr("Error de Tiempo"),tr("El intervalo de medición no coincide con el tiempo final"));
        return;
    }

    QVector<TidesMeasurement> measurements;
    while(begin <= end){
        measurements.push_back(TidesMeasurement(0.0,begin.date(),begin.time()));
        begin = begin.addSecs(m_timeInterval);
    }

    m_model->setMeasurements(measurements);

}

void ManualDataIntroductionWidget::createComponents()
{
    m_mainGroupBox = new QGroupBox(this);

    m_ini_endGroupBox  = new QGroupBox(tr("Inicio y Fin de las Mediciones"));

    m_iniDateLabel = new QLabel(tr("Fecha de Inicio"));
    m_iniDateLabel->setAlignment(Qt::AlignCenter);

    m_endDateLabel = new QLabel(tr("Fecha de Fin"));
    m_endDateLabel->setAlignment(Qt::AlignCenter);

    m_iniTimeLabel = new QLabel(tr("Hora de Inicio"));
    m_iniTimeLabel->setAlignment(Qt::AlignCenter);

    m_endTimeLabel = new QLabel(tr("Hora de Fin"));
    m_endTimeLabel->setAlignment(Qt::AlignCenter);

    m_iniDateEdit = new QDateEdit;
    m_iniDateEdit->setCalendarPopup(true);
    m_iniDateEdit->setDisplayFormat("yyyy/MM/dd");
    m_iniDateEdit->setMinimumDate(QDate(1970,1,1));
    connect(m_iniDateEdit,SIGNAL(dateChanged(QDate)),this,SLOT(setMinimumDateEditValue(QDate)));

    m_endDateEdit = new QDateEdit;
    m_endDateEdit->setCalendarPopup(true);
    m_endDateEdit->setDisplayFormat("yyyy/MM/dd");
    m_endDateEdit->setMinimumDate(QDate(m_iniDateEdit->date()));

    m_iniTimeEdit = new QTimeEdit;
    m_iniTimeEdit->setDisplayFormat("hh:mm");

    m_endTimeEdit = new QTimeEdit;
    m_endTimeEdit->setDisplayFormat("hh:mm");

    QGridLayout *ini_endGridLayout = new QGridLayout;
    ini_endGridLayout->addWidget(m_iniDateLabel,0,0,1,1);
    ini_endGridLayout->addWidget(m_endDateLabel,0,1,1,1);
    ini_endGridLayout->addWidget(m_iniDateEdit,1,0,2,1,Qt::AlignTop);
    ini_endGridLayout->addWidget(m_endDateEdit,1,1,2,1,Qt::AlignTop);
    ini_endGridLayout->addWidget(m_iniTimeLabel,3,0,1,1);
    ini_endGridLayout->addWidget(m_endTimeLabel,3,1,1,1);
    ini_endGridLayout->addWidget(m_iniTimeEdit,4,0,1,1);
    ini_endGridLayout->addWidget(m_endTimeEdit,4,1,1,1);

    m_ini_endGroupBox->setLayout(ini_endGridLayout);

    m_timeIntervalGroupBox = new QGroupBox(tr("Intervalo de Medición"),m_mainGroupBox);

    m_timeIntervalComboBox = new QComboBox;
    m_timeIntervalComboBox->addItem(tr("1 Hora"));
    m_timeIntervalComboBox->addItem(tr("30 Minutos"));
    m_timeIntervalComboBox->addItem(tr("5 minutos"));
    m_timeIntervalComboBox->addItem(tr("Personalizado"));
    connect(m_timeIntervalComboBox,SIGNAL(activated(int)),this,SLOT(enableTimeIntervalEdit(int)));
    connect(m_timeIntervalComboBox,SIGNAL(activated(int)),this,SLOT(updateTimeInterval(int)));

    m_timeIntervalTimeEdit = new QTimeEdit;
    m_timeIntervalTimeEdit->setDisplayFormat("hh:mm");
    m_timeIntervalTimeEdit->setDisabled(true);
    connect(m_timeIntervalTimeEdit,SIGNAL(timeChanged(QTime)),this,SLOT(setTimeInterval(QTime)));

    QHBoxLayout *timeIntervalLayout = new QHBoxLayout;
    timeIntervalLayout->addWidget(m_timeIntervalComboBox);
    timeIntervalLayout->addWidget(m_timeIntervalTimeEdit);

    m_timeIntervalGroupBox->setLayout(timeIntervalLayout);

    m_genPushButton = new QPushButton(tr("Generar"),this);
    //TODO tolTip
    connect(m_genPushButton,SIGNAL(clicked(bool)),this,SLOT(generateData()));

    QHBoxLayout *genButtonLayout = new QHBoxLayout;
    genButtonLayout->addStretch();
    genButtonLayout->addWidget(m_genPushButton);

    QVBoxLayout *mainGroupBoxLayout = new QVBoxLayout;
    mainGroupBoxLayout->addSpacing(10);
    mainGroupBoxLayout->addWidget(m_ini_endGroupBox);
    mainGroupBoxLayout->addSpacing(30);
    mainGroupBoxLayout->addWidget(m_timeIntervalGroupBox);
    mainGroupBoxLayout->addSpacing(20);
    mainGroupBoxLayout->addLayout(genButtonLayout);

    m_mainGroupBox->setLayout(mainGroupBoxLayout);

    m_buttonsGroupBox = new QGroupBox;

    m_insertPushButton = new QPushButton(QIcon(":images/table_row_new.png"),tr("Insertar"));
    m_insertPushButton->setToolTip(tr("Inserta una nueva medición"));
    connect(m_insertPushButton,SIGNAL(clicked(bool)),this,SLOT(insertMeasurement()));

    m_removePushButton = new QPushButton(QIcon(":images/table_row_delete.png"),tr("Eliminar"));
    m_removePushButton->setToolTip(tr("Elimina la última medición"));
    connect(m_removePushButton,SIGNAL(clicked(bool)),this,SLOT(removeLastMeasurement()));

    m_clearPushButton = new QPushButton(QIcon(":images/table_delete.png"),tr("Limpiar"));
    m_clearPushButton->setToolTip(tr("Elimina todas la mediciones"));
    connect(m_clearPushButton,SIGNAL(clicked(bool)),this,SLOT(clearMeasurements()));

    m_okPushButton = new QPushButton(QIcon(":images/Ok.png"),tr("Aceptar"));
    connect(m_okPushButton,SIGNAL(clicked(bool)),this,SIGNAL(okButtonClicked()));

    m_cancelPushButton = new QPushButton(QIcon(":images/No.png"),tr("Cancelar"));
    connect(m_cancelPushButton,SIGNAL(clicked(bool)),this,SLOT(close()));

    QVBoxLayout *upButtonsLayout = new QVBoxLayout;
    upButtonsLayout->addWidget(m_insertPushButton);
    upButtonsLayout->addWidget(m_removePushButton);
    upButtonsLayout->addWidget(m_clearPushButton);

    m_buttonsGroupBox->setLayout(upButtonsLayout);

    m_desitionButtonsGroupBox = new QGroupBox;

    QVBoxLayout *downButtonsLayout = new QVBoxLayout;
    downButtonsLayout->addWidget(m_okPushButton);
    downButtonsLayout->addWidget(m_cancelPushButton);

    m_desitionButtonsGroupBox->setLayout(downButtonsLayout);

    //QVBoxLayout *downLayout = new QVBoxLayout;
    //downLayout->addLayout(upButtonsLayout);
    //downLayout->addSpacing(30);
    //downLayout->addLayout(downButtonsLayout);

    //m_buttonsGroupBox->setLayout(downLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_mainGroupBox);
    mainLayout->addSpacing(50);
    mainLayout->addWidget(m_buttonsGroupBox);
    mainLayout->addSpacing(50);
    mainLayout->addWidget(m_desitionButtonsGroupBox);

    //Layout Central

    m_editionTable = new EditionTable(this);

    QHBoxLayout *centralLayout = new QHBoxLayout;
    centralLayout->addWidget(m_editionTable);
    centralLayout->addLayout(mainLayout);

    this->setLayout(centralLayout);
}

void ManualDataIntroductionWidget::settingTableWidth()
{
    int width = 20 + m_editionTable->verticalHeader()->width();
    for (int i = 0; i < m_model->columnCount(QModelIndex()); ++i){
         width += m_editionTable->columnWidth(i);
    }
    m_editionTable->setFixedWidth(width);

}
