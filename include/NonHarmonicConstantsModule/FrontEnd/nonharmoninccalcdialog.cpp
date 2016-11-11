#include "nonharmoninccalcdialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QPushButton>

#include <QHBoxLayout>
#include <QFormLayout>
#include <QVBoxLayout>

NonHarmonicCalcDialog::NonHarmonicCalcDialog(QWidget *parent):QDialog(parent)
{
    createComponents();
    setInterfaceLayout();
}

void NonHarmonicCalcDialog::calculate(int index)
{

    m_displayResultWidgetVector.at(index)->setLineEditText(QString::number(index));
    /*switch (index) {
    case 0:

        break;
    default:
        break;
    }*/
}

void NonHarmonicCalcDialog::createComponents()
{
    m_inputFrame = new QFrame(this);
    m_inputFrame->setFrameStyle(QFrame::Box | QFrame::Raised);

    m_relationFrame = new QFrame(this);
    m_relationFrame->setFrameStyle(QFrame::Box | QFrame::Raised);

    m_column1Frame = new QFrame(this);
    m_column1Frame->setFrameStyle(QFrame::Box | QFrame::Raised);

    m_column2Frame = new QFrame(this);
    m_column2Frame->setFrameStyle(QFrame::Box | QFrame::Raised);

    m_NMMLabel = new QLabel(tr("Nivel Medio:"));
    m_longitudLabel = new QLabel(tr("Longitud:"));
    m_ampRelationLabel = new QLabel(tr("Va Imagen!!!"));
    m_semidiurnalRelationLabel = new QLabel(tr("Va Imagen!!!"));
    m_tipoMareaLabel = new QLabel(tr("Tipo de Marea:"),this);

    m_NMMSpinBox = new QDoubleSpinBox;
    m_NMMSpinBox->setRange(0.0,INT64_MAX);

    m_ampRelationLineEdit = new QLineEdit;
    m_ampRelationLineEdit->setReadOnly(true);

    m_semidiurnalRelationLineEdit = new QLineEdit;
    m_semidiurnalRelationLineEdit->setReadOnly(true);

    m_tipoMareaLineEdit = new QLineEdit(this);
    m_tipoMareaLineEdit->setReadOnly(true);

    m_calcAllPushButton = new QPushButton(tr("Calcular Todos"));
    m_calcAllPushButton->setToolTip(tr("Calcula todas las posibles constantes no armonicas"));

    m_savePushButton = new QPushButton(tr("Guardar"));
    //TODO: Icon & Conexion
    m_closePushButton = new QPushButton(tr("Cerrar"));

    createDisplaysResultWidgets();


}

void NonHarmonicCalcDialog::createDisplaysResultWidgets()
{
    QStringList nonHarmonicNames;

    nonHarmonicNames << "Hora del Puesto Media:" << "Hora del Puesto:" << "Duración del Vaciante:" << "Duración del Llenante:"
                     << "Crecimiento de la Marea Semidiurna:" << "Crecimiento de la Marea Paraláctica" << "Crecimiento de la Marea Diurna:"
                     << "Hora Cotidiana de la Marea Semidiurna:" << "Hora Cotidiana de la Marea Diurna:" << "Altura Promedio de la Marea Semidiurna:"
                     << "Altura Promedio de la Marea en Sicigias:" << "Altura Promedio de la Marea en Cuadratura" << "Altura Promedio de la Marea Tropical:"
                     << "Altura de la Semimarea:" << "Pleamar Media de Sicigias:" << "Pleamar Media de Cuadratura:" << "Pleamar Media de la Marea Tropical:"
                     << "Bajamar Media de Sicigias" << "Bajamar Media de Cuadratura:" << "Bajamar Media de la Marea Tropical:";

    m_mapper = new QSignalMapper(this);

    foreach (QString title, nonHarmonicNames) {
        displayResultWidget *nonHarmonicConstantDisplay = new displayResultWidget(title);
        m_displayResultWidgetVector.append(nonHarmonicConstantDisplay);
        m_mapper->setMapping(nonHarmonicConstantDisplay,m_displayResultWidgetVector.size()-1);
        connect(nonHarmonicConstantDisplay,SIGNAL(pushButtonClicked()),m_mapper,SLOT(map()));
    }
    connect(m_mapper,SIGNAL(mapped(int)),this,SLOT(calculate(int)));
}

void NonHarmonicCalcDialog::setInterfaceLayout()
{
    QFormLayout *inputLayout = new QFormLayout;
    inputLayout->addRow(m_NMMLabel,m_NMMSpinBox);
    inputLayout->addRow(m_longitudLabel,new QLabel("Coordenate Editor"));

    m_inputFrame->setLayout(inputLayout);

    QHBoxLayout *relationLayout = new QHBoxLayout;
    relationLayout->addWidget(m_ampRelationLabel);
    relationLayout->addWidget(m_ampRelationLineEdit);
    relationLayout->addWidget(m_semidiurnalRelationLabel);
    relationLayout->addWidget(m_semidiurnalRelationLineEdit);

    m_relationFrame->setLayout(relationLayout);

    QHBoxLayout *tideTypeLayout = new QHBoxLayout;
    tideTypeLayout->addWidget(m_tipoMareaLabel);
    tideTypeLayout->addWidget(m_tipoMareaLineEdit);
    tideTypeLayout->addStretch();

    QVBoxLayout *column1Layout = new QVBoxLayout;
    QVBoxLayout *column2Layout = new QVBoxLayout;
    int i = 0;
    foreach (displayResultWidget *disp, m_displayResultWidgetVector) {
        if (i < m_displayResultWidgetVector.size()/2) column1Layout->addWidget(disp);
        else column2Layout->addWidget(disp);
        ++i;
    }

    m_column1Frame->setLayout(column1Layout);
    m_column2Frame->setLayout(column2Layout);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(m_calcAllPushButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_savePushButton);
    buttonLayout->addWidget(m_closePushButton);

    QHBoxLayout *upLayout = new QHBoxLayout;
    upLayout->addWidget(m_inputFrame);
    upLayout->addWidget(m_relationFrame);

    QHBoxLayout *displayLayout = new QHBoxLayout;
    displayLayout->addWidget(m_column1Frame);
    displayLayout->addWidget(m_column2Frame);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(upLayout);
    mainLayout->addLayout(tideTypeLayout);
    mainLayout->addLayout(displayLayout);
    mainLayout->addLayout(buttonLayout);

    this->setLayout(mainLayout);

}
