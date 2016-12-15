#include "samplingdialog.h"
#include <QLabel>
#include <QPushButton>
#include <QDateEdit>
#include <QTimeEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QProgressBar>

SamplingDialog::SamplingDialog(const QVector<TidesMeasurement> &inputMeasurements, QWidget *parent):
    QDialog(parent), m_allData(inputMeasurements)
{

    QDate auxDate = inputMeasurements.first().measurementDate();
    m_mapForFirstDatePos[auxDate] = 0;
    m_mapForEndDatePos[inputMeasurements.last().measurementDate()] = inputMeasurements.size()-1;
    int i = 0;
    foreach (TidesMeasurement measurement, inputMeasurements) {
        if (measurement.measurementDate() != auxDate){
            m_mapForEndDatePos[auxDate] = i-1;
            auxDate = measurement.measurementDate();
            m_mapForFirstDatePos[auxDate] = i;
        }
        ++i;
    }


    m_fechaInicialLabel = new QLabel(tr("Fecha Inicial:"));
    m_fechaFinalLabel = new QLabel(tr("Fecha Final:"));
    m_intervaloLabel = new QLabel(tr("Intervalo:"));

    m_infoLabel = new QLabel(tr("Sampling: Reduce el número total de datos de entrada mediante\n"
                                "la eliminación de datos sujetos a un intervalo de tiempo específico.\n"
                                "Especificar un intervalo de tiempo muy largo puede causar la eliminación\n"
                                "de muchos datos y reducir la calidad de la serie. Un intervalo pequeño\n"
                                "puede  dejar una gran cantidad de datos ralentizando análisis futuro."));

    m_fechaInicialEdit = new QDateEdit(inputMeasurements.first().measurementDate());
    m_fechaInicialEdit->setDateRange(inputMeasurements.first().measurementDate(), inputMeasurements.last().measurementDate());
    m_fechaInicialEdit->setCalendarPopup(true);
    m_fechaInicialEdit->setFixedWidth(100);
    connect(m_fechaInicialEdit,SIGNAL(dateChanged(QDate)),this,SLOT(updateFinalDateEditRange(QDate)));

    m_fechaFinalEdit = new QDateEdit(inputMeasurements.last().measurementDate());
    m_fechaFinalEdit->setDateRange(inputMeasurements.first().measurementDate(), inputMeasurements.last().measurementDate());
    m_fechaFinalEdit->setCalendarPopup(true);
    m_fechaFinalEdit->setFixedWidth(100);
    connect(m_fechaFinalEdit,SIGNAL(dateChanged(QDate)),this,SLOT(updatePotentialPoints()));

    m_intervaloEdit = new QTimeEdit(QTime(1,0));
    m_intervaloEdit->setMinimumTime(QTime(0,1));
    m_intervaloEdit->setDisplayFormat("hh:mm");
    m_intervaloEdit->setFixedWidth(100);
    connect(m_intervaloEdit,SIGNAL(timeChanged(QTime)),this,SLOT(updatePotentialPoints()));

    m_sampleButton = new QPushButton(tr("Sample"));
    m_sampleButton->setToolTip(tr("Inicia el Sampling"));
    connect(m_sampleButton,SIGNAL(clicked(bool)),this,SLOT(sampleData()));

    m_okButton = new QPushButton(QIcon(":images/Ok.png"),tr("Aceptar"));
    m_okButton->setEnabled(false);
    connect(m_okButton,SIGNAL(clicked(bool)),this,SIGNAL(accepted()));

    m_cancelButton = new QPushButton(QIcon(":images/No.png"),tr("Cancelar"));
    connect(m_cancelButton,SIGNAL(clicked(bool)),this,SLOT(close()));

    m_progressBar = new QProgressBar;
    m_progressBar->setMaximum(inputMeasurements.size());
    m_progressBar->setTextVisible(true);

    QDateTime iniDateTime = inputMeasurements.first().measurementDateTime();
    QDateTime endDateTime = inputMeasurements.last().measurementDateTime();

    m_potentialPoints = iniDateTime.secsTo(endDateTime)/3600 + 1;

    m_statusLabel = new QLabel;
    m_statusLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);

    if (m_potentialPoints > m_allData.size()){
        updateStatusText(inputMeasurements.size(),inputMeasurements.size(),0);
    }else{
        updateStatusText(inputMeasurements.size(),m_potentialPoints,0);
    }

    QFormLayout *dateFilteringLayout = new QFormLayout;
    dateFilteringLayout->addRow(m_fechaInicialLabel,m_fechaInicialEdit);
    dateFilteringLayout->addRow(m_fechaFinalLabel,m_fechaFinalEdit);
    dateFilteringLayout->addRow(m_intervaloLabel,m_intervaloEdit);

    QFrame *infoFrame = new QFrame;
    infoFrame->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);

    QHBoxLayout *infoLayout = new QHBoxLayout;
    infoLayout->addWidget(m_infoLabel);

    infoFrame->setLayout(infoLayout);

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(m_sampleButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_okButton);
    buttonLayout->addWidget(m_cancelButton);

    QVBoxLayout *upLeftLayout = new QVBoxLayout;
    upLeftLayout->addLayout(dateFilteringLayout);
    upLeftLayout->addWidget(infoFrame);
    upLeftLayout->addWidget(m_progressBar);

    QHBoxLayout *upLayout = new QHBoxLayout;
    upLayout->addLayout(upLeftLayout);
    upLayout->addLayout(buttonLayout);

    QVBoxLayout *mainLayout= new QVBoxLayout;
    mainLayout->addLayout(upLayout);
    //mainLayout->addWidget(m_progressBar);
    mainLayout->addWidget(m_statusLabel);

    setLayout(mainLayout);

    Qt::WindowFlags flags = Qt::Dialog | Qt::WindowCloseButtonHint;
    this->setWindowFlags(flags);

    setWindowTitle(tr("Sampling"));
    setModal(true);
    setAttribute(Qt::WA_DeleteOnClose);
}

void SamplingDialog::sampleData()
{
    QDate iniDate = m_fechaInicialEdit->date();
    QDate endDate = m_fechaFinalEdit->date();

    m_reducedData.clear();

    quint64 intervalInSecs = m_intervaloEdit->time().hour()*3600 + m_intervaloEdit->time().minute()*60;

    quint64 counter = 0;
    int progress = 0;

    int beg = m_mapForFirstDatePos.value(iniDate);
    int end = m_mapForEndDatePos.value(endDate);

    QDateTime auxDateTime(m_allData.at(beg).measurementDateTime());

    m_progressBar->setMaximum(end-beg);

    for (int k = beg; k <= end; ++k){
        while (auxDateTime < m_allData.at(k).measurementDateTime()){
            auxDateTime = auxDateTime.addSecs(intervalInSecs);
        }
        if (auxDateTime == m_allData.at(k).measurementDateTime()){
            m_reducedData.push_back(m_allData.at(k));
            auxDateTime = auxDateTime.addSecs(intervalInSecs);
            ++counter;
            updateStatusText(m_allData.size(),m_potentialPoints,counter);
        }
        ++progress;
        m_progressBar->setValue(progress);
    }
    /*bool flag = true; //flag para igualar la fecha auxiliar a la primera para agregar
    foreach (TidesMeasurement measurement, m_allData) {
        if (measurement.measurementDate() >= iniDate && measurement.measurementDate() <= endDate){
           if (flag){
               auxDateTime = measurement.measurementDateTime();
               flag = false;
           }
           if (auxDateTime == measurement.measurementDateTime()){
               m_reducedData.push_back(measurement);
               ++counter;
               updateStatusText(m_allData.size(),m_potentialPoints,counter);
               auxDateTime = auxDateTime.addSecs(intervalInSecs);
           }
           while (auxDateTime < measurement.measurementDateTime()) {
               auxDateTime = auxDateTime.addSecs(intervalInSecs);
           }

        }
        ++progress;
        m_progressBar->setValue(progress);
        if (measurement.measurementDate() > endDate){
            m_progressBar->setValue(m_allData.size());
            break;
        }
    }*/
    m_okButton->setEnabled(true);
}

void SamplingDialog::updateFinalDateEditRange(const QDate &iniDate)
{
    m_fechaFinalEdit->setDateRange(iniDate,m_allData.last().measurementDate());

    if (iniDate <= m_fechaFinalEdit->date()) updatePotentialPoints();
}

void SamplingDialog::updatePotentialPoints()
{
    m_okButton->setEnabled(false);
    m_progressBar->setValue(0);
    QDate inDate = m_fechaInicialEdit->date();
    QDate endDate = m_fechaFinalEdit->date();

    QDateTime beginDateTime = m_allData.at(m_mapForFirstDatePos.value(inDate)).measurementDateTime();
    QDateTime endDateTime = m_allData.at(m_mapForEndDatePos.value(endDate)).measurementDateTime();

    /*bool flagBeg = true;
    foreach (TidesMeasurement measu, m_allData) {
        if (measu.measurementDate() == inDate && flagBeg){
            beginDateTime = measu.measurementDateTime();
            flagBeg = false;
        }
        if (measu.measurementDate() == endDate){
            endDateTime = measu.measurementDateTime();
        }

        if (measu.measurementDate() > endDate) break;
    }*/

    quint64 intervalInSecs = m_intervaloEdit->time().hour()*3600 + m_intervaloEdit->time().minute()*60;

    m_potentialPoints = beginDateTime.secsTo(endDateTime)/intervalInSecs + 1;

    if (m_potentialPoints > m_allData.size()){
        updateStatusText(m_allData.size(),m_allData.size(),0);
    }else{
        updateStatusText(m_allData.size(),m_potentialPoints,0);
    }
}

void SamplingDialog::updateStatusText(quint64 datosEntrada,quint64 datosSalidaPotenciales, quint64 currentAddedPoints)
{
    m_statusLabel->setText(tr("Datos de Entrada: <font color = red> %1 </font>. ").arg(datosEntrada) +
                           tr("Datos de Salida [potenciales] <font color = blue> %1 </font>. ").arg(datosSalidaPotenciales) +
                           tr("Datos de Salida [reales] <font color = green> %1 </font>").arg(currentAddedPoints));
}
