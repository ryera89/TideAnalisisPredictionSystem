#include "averagedialog.h"
#include "ui_averagedialog.h"

AverageDialog::AverageDialog(const QVector<TidesMeasurement> &data,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AverageDialog), m_data(data)
{
    ui->setupUi(this);

    connect(ui->averageButton,SIGNAL(clicked(bool)),this,SLOT(averageData()));
    connect(ui->okButton,SIGNAL(clicked(bool)),this,SLOT(accept()));
    connect(ui->cancelButton,SIGNAL(clicked(bool)),this,SLOT(close()));

    ui->statusLabel->setText(tr("Puntos de Entrada <b><font color = red>%1</b></font>. ").arg(m_data.size()));

    Qt::WindowFlags flags = Qt::Dialog | Qt::WindowCloseButtonHint;
    this->setWindowFlags(flags);

    setWindowTitle(tr("Promediar"));
    setModal(true);
    setAttribute(Qt::WA_DeleteOnClose);
}

AverageDialog::~AverageDialog()
{
    delete ui;
}

void AverageDialog::averageData()
{

    if (m_data.isEmpty()) return;

    ui->progressBar->setMaximum(m_data.size()-1);
    m_averagedData.clear();
    quint64 timeWindowInSec = ui->spinBox->value()*60;

    QDateTime controlDateTime = m_data.first().measurementDateTime().addSecs(timeWindowInSec);

    quint64 time_sum = 0;
    qreal level_sum = 0;
    int counter = 0;
    int progress = 0;
    int aux = 0;
    foreach (TidesMeasurement measurement, m_data) {
        if (measurement.measurementDateTime() <= controlDateTime){
            time_sum += measurement.measurementDateTime().toMSecsSinceEpoch();
            level_sum += measurement.seaLevel();
            ++counter;
        }else{
            quint64 time_ave = time_sum/counter;
            qreal level_ave = level_sum/counter;
            m_averagedData.push_back(TidesMeasurement(level_ave,QDateTime::fromMSecsSinceEpoch(time_ave)));
            ++aux;
            updateStatusLabel(aux);
            while (controlDateTime < measurement.measurementDateTime()) {
                controlDateTime = controlDateTime.addSecs(timeWindowInSec);
            }
            counter = 1;
            time_sum = measurement.measurementDateTime().toMSecsSinceEpoch();
            level_sum = measurement.seaLevel();
        }
        ++progress;
        ui->progressBar->setValue(progress);
    }
    ui->okButton->setEnabled(true);
}

void AverageDialog::updateStatusLabel(int dataNumber)
{
    ui->statusLabel->setText(tr("Puntos de Entrada <b><font color = red>%1</b></font>. ").arg(m_data.size()) + tr("Puntos de Salida <b><font color = green>%1</b></font>.").arg(dataNumber));
}
