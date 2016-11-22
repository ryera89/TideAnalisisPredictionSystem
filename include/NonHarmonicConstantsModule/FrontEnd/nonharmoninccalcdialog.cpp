#include "nonharmoninccalcdialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QPushButton>

#include <QHBoxLayout>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QMessageBox>

#include "include/NonHarmonicConstantsModule/NonHarmonicConstants/amplitudrelation.h"
#include "include/NonHarmonicConstantsModule/NonHarmonicConstants/semidiurnalrelation.h"
#include "include/NonHarmonicConstantsModule/NonHarmonicConstants/hpm.h"
#include "include/NonHarmonicConstantsModule/NonHarmonicConstants/horapuesto.h"
#include "include/NonHarmonicConstantsModule/NonHarmonicConstants/duracionllenante.h"
#include "include/NonHarmonicConstantsModule/NonHarmonicConstants/duracionvaciante.h"
#include "include/NonHarmonicConstantsModule/NonHarmonicConstants/creciemientomareadiurna.h"
#include "include/NonHarmonicConstantsModule/NonHarmonicConstants/crecimientomareaparactica.h"
#include "include/NonHarmonicConstantsModule/NonHarmonicConstants/crecimientomareasemidiurna.h"
#include "include/NonHarmonicConstantsModule/NonHarmonicConstants/horacotidianadiurna.h"
#include "include/NonHarmonicConstantsModule/NonHarmonicConstants/horacotidianasemidiurna.h"
#include "include/NonHarmonicConstantsModule/NonHarmonicConstants/alturapromediomarea.h"
#include "include/NonHarmonicConstantsModule/NonHarmonicConstants/alturasemimarea.h"
#include "include/NonHarmonicConstantsModule/NonHarmonicConstants/pleabajamedia.h"

#include "include/CoordinatesEditionWidget/mycoordinateseditorwidget.h"
NonHarmonicCalcDialog::NonHarmonicCalcDialog(QWidget *parent):QDialog(parent)
{
    createComponents();
    setInterfaceLayout();

    setModal(true);
    setAttribute(Qt::WA_DeleteOnClose);
}

void NonHarmonicCalcDialog::loadHarmonicConstants(const QVector<HarmonicConstant> &harmonicConstants)
{
    bool m2Present = false;
    bool s2Present = false;
    bool n2Present = false;
    bool k2Present = false;

    bool k1Present = false;
    bool o1Present = false;
    bool p1Present = false;
    bool q1Present = false;

    bool m4Present = false;
    bool m6Present = false;

    foreach (HarmonicConstant harmonic, harmonicConstants) {
        if (harmonic.name() == "M2") {m_M2 = harmonic; m2Present = true;}
        if (harmonic.name() == "S2") {m_S2 = harmonic; s2Present = true;}
        if (harmonic.name() == "N2") {m_N2 = harmonic; n2Present = true;}
        if (harmonic.name() == "K2") {m_K2 = harmonic; k2Present = true;}
        if (harmonic.name() == "K1") {m_K1 = harmonic; k1Present = true;}
        if (harmonic.name() == "O1") {m_O1 = harmonic; o1Present = true;}
        if (harmonic.name() == "P1") {m_P1 = harmonic; p1Present = true;}
        if (harmonic.name() == "Q1") {m_Q1 = harmonic; q1Present = true;}
        if (harmonic.name() == "M4") {m_M4 = harmonic; m4Present = true;}
        if (harmonic.name() == "M6") {m_M6 = harmonic; m6Present = true;}
    }
    if (!m2Present || !s2Present || !k1Present || !o1Present){
        QMessageBox::critical(this,tr("Faltan Componentes Principales"), tr("Alguna/s de las componentes "
                                                                            "M2, S2, K1, O1 faltan en el "
                                                                            "analisis armonico. Estas son "
                                                                            "esenciales para el calculo de "
                                                                            "las constantes no armonicas."));
        return;
    }
    if (!n2Present || !k2Present || !p1Present || !q1Present || !m4Present || !m6Present){
        QMessageBox::information(this,tr("Faltan Componentes"), tr("Alguna/s de las componentes"
                                                                            "N2, K2, P1, Q1, M4, M6 faltan en el"
                                                                            "analisis armonico. Estas no se "
                                                                            "tomaran en cuenta para el calculo "
                                                                            "de las constantes no armonicas"));


    }
    double ampRelation = calculateAmplitudRelation();
    double semidiurnalRelation = calculateSemidiurnalRelation();

    QFont font = m_ampRelationLineEdit->font();
    font.setBold(true);
    m_ampRelationLineEdit->setFont(font);
    m_semidiurnalRelationLineEdit->setFont(font);
    m_tipoMareaLineEdit->setFont(font);
    m_ampRelationLineEdit->setText(QString::number(ampRelation,'g',3));
    m_semidiurnalRelationLineEdit->setText(QString::number(semidiurnalRelation,'g',3));

    m_tipoMareaLineEdit->setText(tipoDeMarea(ampRelation));
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

    m_column3Frame = new QFrame(this);
    m_column3Frame->setFrameStyle(QFrame::Box | QFrame::Raised);

    m_NMMLabel = new QLabel(tr("Nivel Medio:"));
    m_longitudLabel = new QLabel(tr("Longitud:"));
    m_ampRelationLabel = new QLabel(tr("Va Imagen!!!"));
    m_semidiurnalRelationLabel = new QLabel(tr("Va Imagen!!!"));
    m_tipoMareaLabel = new QLabel(tr("Tipo de Marea:"),this);

    m_NMMSpinBox = new QDoubleSpinBox;
    m_NMMSpinBox->setRange(0.0,INT64_MAX);

    m_longitudEditor = new MyCoordinatesEditorWidget;
    m_longitudEditor->setHType(MyCoordinatesEditorWidget::longitud);
    m_longitudEditor->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);

    m_ampRelationLineEdit = new QLineEdit;
    m_ampRelationLineEdit->setReadOnly(true);

    m_semidiurnalRelationLineEdit = new QLineEdit;
    m_semidiurnalRelationLineEdit->setReadOnly(true);

    m_tipoMareaLineEdit = new QLineEdit(this);
    m_tipoMareaLineEdit->setReadOnly(true);

    m_calcAllPushButton = new QPushButton(tr("Calcular Todos"));
    m_calcAllPushButton->setToolTip(tr("Calcula todas las posibles constantes no armonicas"));

    m_savePushButton = new QPushButton(QIcon(":images/save.png"),tr("Guardar"));
    //TODO: Conexion
    m_closePushButton = new QPushButton(QIcon(":images/No.png"),tr("Cerrar"));

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
        nonHarmonicConstantDisplay->setPushButtonStatus(false);
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
    inputLayout->addRow(m_longitudLabel,m_longitudEditor);

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
    QVBoxLayout *column3Layout = new QVBoxLayout;
    uint i = 0;
    uint displayWidgetNumber = m_displayResultWidgetVector.size();
    foreach (displayResultWidget *disp, m_displayResultWidgetVector) {
        if (i <= displayWidgetNumber/3) column1Layout->addWidget(disp);
        else if (i <= 2*displayWidgetNumber/3)column2Layout->addWidget(disp);
        else column3Layout->addWidget(disp);
        ++i;
    }

    m_column1Frame->setLayout(column1Layout);
    m_column2Frame->setLayout(column2Layout);
    m_column3Frame->setLayout(column3Layout);

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
    displayLayout->addWidget(m_column3Frame);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(upLayout);
    mainLayout->addLayout(tideTypeLayout);
    mainLayout->addLayout(displayLayout);
    mainLayout->addLayout(buttonLayout);

    this->setLayout(mainLayout);

}

double NonHarmonicCalcDialog::calculateAmplitudRelation()
{
    AmplitudRelation ampR(m_M2, m_K1, m_O1);

    return ampR.amplRelation();
}

double NonHarmonicCalcDialog::calculateSemidiurnalRelation()
{
    SemidiurnalRelation semiR(m_M2,m_S2);

    return semiR.relationS2M2();
}

QString NonHarmonicCalcDialog::tipoDeMarea(double ampRelation)
{
    if (0.0 < ampRelation && 0.5 >= ampRelation) return "MAREA SEMIDIURNA";
    if (0.5 < ampRelation && 2.0 >= ampRelation) return "MAREA MIXTA SEMIDIURNA IRREGULAR";
    if (2.0 < ampRelation && 4.0 >= ampRelation) return "MAREA MIXTA DIURNA IRREGULAR";
    if (4.0 < ampRelation) return "MAREA DIURNA";

    return "ERROR DE DATOS";
}

double NonHarmonicCalcDialog::calculateHPM()
{
    HPM hpm(m_M2,m_M4,m_M6);

    return hpm.HoraPuestoMedia();
}

double NonHarmonicCalcDialog::calculateHP()
{
    HoraPuesto hp(m_M2,m_S2,HPM(m_M2,m_M4,m_M6));

    return hp.HP();
}

double NonHarmonicCalcDialog::calculateDV()
{
    DuracionVaciante dv(m_M2,m_M4,m_M6);

    return dv.DV();
}

double NonHarmonicCalcDialog::calculateDLL()
{
    DuracionLLenante dll(m_M2,m_M4,m_M6);

    return dll.DLL();
}

double NonHarmonicCalcDialog::calculateCMS()
{
   CrecimientoMareaSemidiurna cms(m_M2,m_S2);

   return cms.CMS();
}

double NonHarmonicCalcDialog::calculateCMP()
{
    CrecimientoMareaParactica cmp(m_M2,m_N2);

    cmp.CMP();
}

double NonHarmonicCalcDialog::calculateCMD()
{
    CreciemientoMareaDiurna cmd(m_K1,m_O1);

    return cmd.CMD();
}

double NonHarmonicCalcDialog::calculateHCMS()
{
    HoraCotidianaSemidiurna hcms(m_M2,m_M4,m_M6,m_longitud);

    return hcms.HCS();
}

double NonHarmonicCalcDialog::calculateHCMD()
{
    HoraCotidianaDiurna hcmd(m_K1,m_O1,m_longitud);

    return hcmd.HCD();
}

double NonHarmonicCalcDialog::calculateAPMS()
{
    AlturaPromedioMarea apm(m_M2,m_S2,m_N2,m_K2,m_K1,m_O1,m_P1,m_Q1,m_M4,m_M6);

    return apm.AlturaPromedioSemidiurna();
}

double NonHarmonicCalcDialog::calculateAPMSS()
{

    AlturaPromedioMarea apm(m_M2,m_S2,m_N2,m_K2,m_K1,m_O1,m_P1,m_Q1,m_M4,m_M6);

    return apm.AlturaPromedioSicigias();
}

double NonHarmonicCalcDialog::calculateAPMC()
{

    AlturaPromedioMarea apm(m_M2,m_S2,m_N2,m_K2,m_K1,m_O1,m_P1,m_Q1,m_M4,m_M6);

    return apm.AlturaPromedioCuadratura();
}

double NonHarmonicCalcDialog::calculateAPMT()
{

    AlturaPromedioMarea apm(m_M2,m_S2,m_N2,m_K2,m_K1,m_O1,m_P1,m_Q1,m_M4,m_M6);

    return apm.AlturaPromedioTropical();
}

double NonHarmonicCalcDialog::calculateAS()
{
    AlturaSemimarea as(m_M2,m_K1,m_O1,m_M4,m_nivelMedio);

    return as.AlturaDeSemimarea();
}

double NonHarmonicCalcDialog::calculatePMS()
{
    PleaBajaMedia pbm(AlturaPromedioMarea(m_M2,m_S2,m_N2,m_K2,m_K1,m_O1,m_P1,m_Q1,m_M4,m_M6),AlturaSemimarea(m_M2,m_K1,m_O1,m_M4,m_nivelMedio));

    return pbm.PleamarMediaSicigias();
}

double NonHarmonicCalcDialog::calculatePMC()
{
    PleaBajaMedia pbm(AlturaPromedioMarea(m_M2,m_S2,m_N2,m_K2,m_K1,m_O1,m_P1,m_Q1,m_M4,m_M6),AlturaSemimarea(m_M2,m_K1,m_O1,m_M4,m_nivelMedio));

    return pbm.PleamarMediaCuadratura();
}

double NonHarmonicCalcDialog::calculatePMMT()
{
    PleaBajaMedia pbm(AlturaPromedioMarea(m_M2,m_S2,m_N2,m_K2,m_K1,m_O1,m_P1,m_Q1,m_M4,m_M6),AlturaSemimarea(m_M2,m_K1,m_O1,m_M4,m_nivelMedio));

    return pbm.PleamarMediaTropical();
}

double NonHarmonicCalcDialog::calculateBMSS()
{
    PleaBajaMedia pbm(AlturaPromedioMarea(m_M2,m_S2,m_N2,m_K2,m_K1,m_O1,m_P1,m_Q1,m_M4,m_M6),AlturaSemimarea(m_M2,m_K1,m_O1,m_M4,m_nivelMedio));

    return pbm.BajamarMediaSicigias();
}

double NonHarmonicCalcDialog::calculateBMC()
{
    PleaBajaMedia pbm(AlturaPromedioMarea(m_M2,m_S2,m_N2,m_K2,m_K1,m_O1,m_P1,m_Q1,m_M4,m_M6),AlturaSemimarea(m_M2,m_K1,m_O1,m_M4,m_nivelMedio));

    return pbm.BajamarMediaCuadratura();
}

double NonHarmonicCalcDialog::calculateBMMT()
{
    PleaBajaMedia pbm(AlturaPromedioMarea(m_M2,m_S2,m_N2,m_K2,m_K1,m_O1,m_P1,m_Q1,m_M4,m_M6),AlturaSemimarea(m_M2,m_K1,m_O1,m_M4,m_nivelMedio));

    return pbm.BajamarMediaTropical();
}

