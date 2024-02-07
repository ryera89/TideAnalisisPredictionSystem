#include "nonharmoninccalcdialog.h"
#include <QDoubleSpinBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include <QFormLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QVBoxLayout>

#include "include/NonHarmonicConstantsModule/NonHarmonicConstants/alturapromediomarea.h"
#include "include/NonHarmonicConstantsModule/NonHarmonicConstants/alturasemimarea.h"
#include "include/NonHarmonicConstantsModule/NonHarmonicConstants/amplitudrelation.h"
#include "include/NonHarmonicConstantsModule/NonHarmonicConstants/creciemientomareadiurna.h"
#include "include/NonHarmonicConstantsModule/NonHarmonicConstants/crecimientomareaparactica.h"
#include "include/NonHarmonicConstantsModule/NonHarmonicConstants/crecimientomareasemidiurna.h"
#include "include/NonHarmonicConstantsModule/NonHarmonicConstants/duracionllenante.h"
#include "include/NonHarmonicConstantsModule/NonHarmonicConstants/duracionvaciante.h"
#include "include/NonHarmonicConstantsModule/NonHarmonicConstants/horacotidianadiurna.h"
#include "include/NonHarmonicConstantsModule/NonHarmonicConstants/horacotidianasemidiurna.h"
#include "include/NonHarmonicConstantsModule/NonHarmonicConstants/horapuesto.h"
#include "include/NonHarmonicConstantsModule/NonHarmonicConstants/hpm.h"
#include "include/NonHarmonicConstantsModule/NonHarmonicConstants/pleabajamedia.h"
#include "include/NonHarmonicConstantsModule/NonHarmonicConstants/semidiurnalrelation.h"

#include <QFile>
#include <QFileDialog>
#include <QTextStream>

#include "include/CoordinatesEditionWidget/mycoordinateseditorwidget.h"
#include <QtMath>
NonHarmonicCalcDialog::NonHarmonicCalcDialog(qreal longitud, QWidget *parent)
    : QDialog(parent) {
  createComponents();
  setInterfaceLayout();

  // m_NMMSpinBox->setSpinAndComboBoxesValues(unit,nmm);
  m_longitudEditor->setEditorAndComboValue(longitud);

  this->setWindowTitle(tr("Constantes No Armónicas"));
  this->setWindowIcon(QIcon(":images/non_harmonic-analisis.png"));
  setModal(true);

  Qt::WindowFlags flag = Qt::Dialog | Qt::WindowCloseButtonHint;
  this->setWindowFlags(flag);

  setAttribute(Qt::WA_DeleteOnClose);
}

void NonHarmonicCalcDialog::loadHarmonicConstants(
    const QVector<HarmonicConstant> &harmonicConstants) {
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
    if (harmonic.name() == "M2") {
      m_M2 = harmonic;
      m2Present = true;
    }
    if (harmonic.name() == "S2") {
      m_S2 = harmonic;
      s2Present = true;
    }
    if (harmonic.name() == "N2") {
      m_N2 = harmonic;
      n2Present = true;
    }
    if (harmonic.name() == "K2") {
      m_K2 = harmonic;
      k2Present = true;
    }
    if (harmonic.name() == "K1") {
      m_K1 = harmonic;
      k1Present = true;
    }
    if (harmonic.name() == "O1") {
      m_O1 = harmonic;
      o1Present = true;
    }
    if (harmonic.name() == "P1") {
      m_P1 = harmonic;
      p1Present = true;
    }
    if (harmonic.name() == "Q1") {
      m_Q1 = harmonic;
      q1Present = true;
    }
    if (harmonic.name() == "M4") {
      m_M4 = harmonic;
      m4Present = true;
    }
    if (harmonic.name() == "M6") {
      m_M6 = harmonic;
      m6Present = true;
    }
  }
  if (!m2Present || !s2Present || !k1Present || !o1Present) {
    QMessageBox::critical(this, tr("Faltan Componentes Principales"),
                          tr("Alguna/s de las componentes "
                             "M2, S2, K1, O1 faltan en el "
                             "análisis armónico. Estas son "
                             "esenciales para el cálculo de "
                             "las constantes no armónicas."));
    return;
  }
  if (!n2Present || !k2Present || !p1Present || !q1Present || !m4Present ||
      !m6Present) {
    QMessageBox::information(this, tr("Faltan Componentes"),
                             tr("Alguna/s de las componentes"
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
  m_ampRelationLineEdit->setText(QString::number(ampRelation, 'g', 3));
  m_semidiurnalRelationLineEdit->setText(
      QString::number(semidiurnalRelation, 'g', 3));

  m_tipoMareaLineEdit->setText(tipoDeMarea(ampRelation));

  enableNonHarmonicConstantCalc(ampRelation);
}

void NonHarmonicCalcDialog::setMetaData(const ProjectMetaData &metadata) {
  m_metaData = metadata;
}

QString NonHarmonicCalcDialog::relacionDeAmplitud() const {
  return m_ampRelationLineEdit->text();
}

QString NonHarmonicCalcDialog::horaDelPuestoMedia() const {
  return m_displayResultWidgetVector.at(0)->lineEditText();
}

QString NonHarmonicCalcDialog::horaDelPuesto() const {
  return m_displayResultWidgetVector.at(1)->lineEditText();
}

QString NonHarmonicCalcDialog::duracionDelVaciante() const {
  return m_displayResultWidgetVector.at(2)->lineEditText();
}

QString NonHarmonicCalcDialog::duracionDelLenante() const {
  return m_displayResultWidgetVector.at(3)->lineEditText();
}

QString NonHarmonicCalcDialog::crecimientoDeLaMareaSemidiurna() const {
  return m_displayResultWidgetVector.at(4)->lineEditText();
}

QString NonHarmonicCalcDialog::crecimientoDeLaMareaParalactica() const {
  return m_displayResultWidgetVector.at(5)->lineEditText();
}

QString NonHarmonicCalcDialog::crecimientoDeLaMareaDiurna() const {
  return m_displayResultWidgetVector.at(6)->lineEditText();
}

QString NonHarmonicCalcDialog::horaCotidianaMareaSemidiurna() const {
  return m_displayResultWidgetVector.at(7)->lineEditText();
}

QString NonHarmonicCalcDialog::horaCotidianaMareaDiurna() const {
  return m_displayResultWidgetVector.at(8)->lineEditText();
}

QString NonHarmonicCalcDialog::alturaPromedioDeLaMareaSemidiurna() const {
  return m_displayResultWidgetVector.at(9)->lineEditText();
}

QString NonHarmonicCalcDialog::alturaPromedioDeLaMareaSicigias() const {
  return m_displayResultWidgetVector.at(10)->lineEditText();
}

QString NonHarmonicCalcDialog::alturaPromedioDeLaMareaCuadratura() const {
  return m_displayResultWidgetVector.at(11)->lineEditText();
}

QString NonHarmonicCalcDialog::alturaPromedioDeLaMareaTropical() const {
  return m_displayResultWidgetVector.at(12)->lineEditText();
}

void NonHarmonicCalcDialog::calculate(int index) {

  // m_displayResultWidgetVector.at(index)->setLineEditText(QString::number(index));
  switch (index) {
  case 0: {
    double val = calculateHPM();
    m_displayResultWidgetVector.at(index)->setLineEditText(
        fromDoubleToHoursAndMinutes(val));
    break;
  }
  case 1: {
    double val = calculateHP();
    m_displayResultWidgetVector.at(index)->setLineEditText(
        fromDoubleToHoursAndMinutes(val));
    break;
  }
  case 2: {
    double val = calculateDV();
    m_displayResultWidgetVector.at(index)->setLineEditText(
        fromDoubleToHoursAndMinutes(val));
    break;
  }
  case 3: {
    double val = calculateDLL();
    m_displayResultWidgetVector.at(index)->setLineEditText(
        fromDoubleToHoursAndMinutes(val));
    break;
  }
  case 4: {
    double val = calculateCMS();
    m_displayResultWidgetVector.at(index)->setLineEditText(
        fromDoubleToDaysAndHours(val));
    break;
  }
  case 5: {
    double val = calculateCMP();
    m_displayResultWidgetVector.at(index)->setLineEditText(
        fromDoubleToDaysAndHours(val));
    break;
  }
  case 6: {
    double val = calculateCMD();
    m_displayResultWidgetVector.at(index)->setLineEditText(
        fromDoubleToDaysAndHours(val));
    break;
  }
  case 7: {
    double val = calculateHCMS();
    m_displayResultWidgetVector.at(index)->setLineEditText(
        fromDoubleToHoursAndMinutes(val));
    break;
  }
  case 8: {
    double val = calculateHCMD();
    m_displayResultWidgetVector.at(index)->setLineEditText(
        fromDoubleToHoursAndMinutes(val));
    break;
  }
  case 9: {
    double val = calculateAPMS();
    m_displayResultWidgetVector.at(index)->setLineEditText(
        QString::number(val, 'g', 3) + "m");
    break;
  }
  case 10: {
    double val = calculateAPMSS();
    m_displayResultWidgetVector.at(index)->setLineEditText(
        QString::number(val, 'g', 3) + "m");
    break;
  }
  case 11: {
    double val = calculateAPMC();
    m_displayResultWidgetVector.at(index)->setLineEditText(
        QString::number(val, 'g', 3) + "m");
    break;
  }
  case 12: {
    double val = calculateAPMT();
    m_displayResultWidgetVector.at(index)->setLineEditText(
        QString::number(val, 'g', 3) + "m");
    break;
  }
  case 13: {
    double val = calculateAS();
    m_displayResultWidgetVector.at(index)->setLineEditText(
        QString::number(val, 'g', 3) + "m");
    break;
  }
  case 14: {
    double val = calculatePMS();
    m_displayResultWidgetVector.at(index)->setLineEditText(
        QString::number(val, 'g', 3) + "m");
    break;
  }
  case 15: {
    double val = calculatePMC();
    m_displayResultWidgetVector.at(index)->setLineEditText(
        QString::number(val, 'g', 3) + "m");
    break;
  }
  case 16: {
    double val = calculatePMMT();
    m_displayResultWidgetVector.at(index)->setLineEditText(
        QString::number(val, 'g', 3) + "m");
    break;
  }
  case 17: {
    double val = calculateBMSS();
    m_displayResultWidgetVector.at(index)->setLineEditText(
        QString::number(val, 'g', 3) + "m");
    break;
  }
  case 18: {
    double val = calculateBMC();
    m_displayResultWidgetVector.at(index)->setLineEditText(
        QString::number(val, 'g', 3) + "m");
    break;
  }
  case 19: {
    double val = calculateBMMT();
    m_displayResultWidgetVector.at(index)->setLineEditText(
        QString::number(val, 'g', 3) + "m");
    break;
  }
  default:
    break;
  }
}

void NonHarmonicCalcDialog::saveToFile() {
  QString fileName = QFileDialog::getSaveFileName(
      this, tr("Guardar Constantes No Armonicas"), QString(), "*.txt");
  if (!fileName.isEmpty()) {
    if (QFileInfo(fileName).suffix().isEmpty())
      fileName.append(".txt");

    saveNonHarmonicConstants(fileName);
  }
}

void NonHarmonicCalcDialog::calculateAll() {
  foreach (displayResultWidget *dispWid, m_displayResultWidgetVector) {
    if (dispWid->pushButtonStatus()) {
      dispWid->pushButtonClicked();
    }
  }
}

void NonHarmonicCalcDialog::closeEvent(QCloseEvent *event) {
  emit closed();

  QDialog::closeEvent(event);
}

void NonHarmonicCalcDialog::createComponents() {
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
  m_ampRelationLabel = new QLabel(this);
  m_ampRelationLabel->setPixmap(QPixmap(":images/semidiurnal_relation.png"));
  m_ampRelationLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
  m_semidiurnalRelationLabel = new QLabel(this);
  m_semidiurnalRelationLabel->setPixmap(
      QPixmap(":images/amplitud_relation.png"));
  m_semidiurnalRelationLabel->setFrameStyle(QFrame::StyledPanel |
                                            QFrame::Sunken);
  m_tipoMareaLabel = new QLabel(tr("Tipo de Marea:"), this);

  m_NMMSpinBox = new MeasurementUnitEditWidget;

  m_longitudEditor = new MyCoordinatesEditorWidget;
  m_longitudEditor->setHType(MyCoordinatesEditorWidget::longitud);
  m_longitudEditor->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);

  m_ampRelationLineEdit = new QLineEdit;
  m_ampRelationLineEdit->setReadOnly(true);

  m_semidiurnalRelationLineEdit = new QLineEdit;
  m_semidiurnalRelationLineEdit->setReadOnly(true);

  m_tipoMareaLineEdit = new QLineEdit(this);
  m_tipoMareaLineEdit->setReadOnly(true);

  m_calcAllPushButton = new QPushButton(tr("Calcular"));
  m_calcAllPushButton->setToolTip(
      tr("Calcula todas las posibles constantes no armónicas"));
  connect(m_calcAllPushButton, SIGNAL(clicked(bool)), this,
          SLOT(calculateAll()));

  m_savePushButton =
      new QPushButton(QIcon(":images/writeToFile1.png"), tr("Guardar"));
  m_savePushButton->setToolTip(tr("Guardar constantes no armónicas"));
  connect(m_savePushButton, SIGNAL(clicked(bool)), this, SLOT(saveToFile()));
  m_closePushButton = new QPushButton(QIcon(":images/No.png"), tr("Cerrar"));
  connect(m_closePushButton, SIGNAL(clicked(bool)), this, SLOT(close()));

  createDisplaysResultWidgets();
}

void NonHarmonicCalcDialog::createDisplaysResultWidgets() {
  QStringList nonHarmonicNames;

  nonHarmonicNames << "Hora del Puesto Media:"
                   << "Hora del Puesto:"
                   << "Duración del Vaciante:"
                   << "Duración del Llenante:"
                   << "Crecimiento de la Marea Semidiurna:"
                   << "Crecimiento de la Marea Paraláctica"
                   << "Crecimiento de la Marea Diurna:"
                   << "Hora Cotidiana de la Marea Semidiurna:"
                   << "Hora Cotidiana de la Marea Diurna:"
                   << "Altura Promedio de la Marea Semidiurna:"
                   << "Altura Promedio de la Marea en Sicigias:"
                   << "Altura Promedio de la Marea en Cuadratura"
                   << "Altura Promedio de la Marea Tropical:"
                   << "Altura de la Semimarea:"
                   << "Pleamar Media de Sicigias:"
                   << "Pleamar Media de Cuadratura:"
                   << "Pleamar Media de la Marea Tropical:"
                   << "Bajamar Media de Sicigias"
                   << "Bajamar Media de Cuadratura:"
                   << "Bajamar Media de la Marea Tropical:";

  m_mapper = new QSignalMapper(this);

  foreach (QString title, nonHarmonicNames) {
    displayResultWidget *nonHarmonicConstantDisplay =
        new displayResultWidget(title);
    nonHarmonicConstantDisplay->setPushButtonStatus(false);
    m_displayResultWidgetVector.append(nonHarmonicConstantDisplay);
    m_mapper->setMapping(nonHarmonicConstantDisplay,
                         m_displayResultWidgetVector.size() - 1);
    connect(nonHarmonicConstantDisplay, SIGNAL(pushButtonClicked()), m_mapper,
            SLOT(map()));
  }
  connect(m_mapper, SIGNAL(mapped(int)), this, SLOT(calculate(int)));
}

void NonHarmonicCalcDialog::setInterfaceLayout() {
  QFormLayout *inputLayout = new QFormLayout;
  inputLayout->addRow(m_NMMLabel, m_NMMSpinBox);
  inputLayout->addRow(m_longitudLabel, m_longitudEditor);

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
    if (i <= displayWidgetNumber / 3)
      column1Layout->addWidget(disp);
    else if (i <= 2 * displayWidgetNumber / 3)
      column2Layout->addWidget(disp);
    else
      column3Layout->addWidget(disp);
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

double NonHarmonicCalcDialog::calculateAmplitudRelation() {
  AmplitudRelation ampR(m_M2, m_K1, m_O1);

  return ampR.amplRelation();
}

double NonHarmonicCalcDialog::calculateSemidiurnalRelation() {
  SemidiurnalRelation semiR(m_M2, m_S2);

  return semiR.relationS2M2();
}

QString NonHarmonicCalcDialog::tipoDeMarea(double ampRelation) {
  if (0.0 < ampRelation && 0.5 >= ampRelation)
    return "MAREA SEMIDIURNA";
  if (0.5 < ampRelation && 2.0 >= ampRelation)
    return "MAREA MIXTA SEMIDIURNA IRREGULAR";
  if (2.0 < ampRelation && 4.0 >= ampRelation)
    return "MAREA MIXTA DIURNA IRREGULAR";
  if (4.0 < ampRelation)
    return "MAREA DIURNA";

  return "ERROR DE DATOS";
}

void NonHarmonicCalcDialog::enableNonHarmonicConstantCalc(double ampRelation) {
  if (0.0 < ampRelation && 0.5 >= ampRelation) {
    for (int i = 0; i < m_displayResultWidgetVector.size(); ++i) {
      if (i != 12 && i != 16 && i != 19)
        m_displayResultWidgetVector.at(i)->setPushButtonStatus(true);
    }
    return;
  }
  if (0.5 < ampRelation && 2.0 >= ampRelation) {
    for (int i = 0; i < m_displayResultWidgetVector.size(); ++i) {
      m_displayResultWidgetVector.at(i)->setPushButtonStatus(true);
    }
    return;
  }
  if (2.0 < ampRelation && 4.0 >= ampRelation) {
    for (int i = 0; i < m_displayResultWidgetVector.size(); ++i) {
      if (i != 1 && i != 2 && i != 3 && i != 9 && i != 10 && i != 11 &&
          i != 14 && i != 15 && i != 17 && i != 18)
        m_displayResultWidgetVector.at(i)->setPushButtonStatus(true);
    }
    return;
  }
  if (4.0 < ampRelation) {
    for (int i = 0; i < m_displayResultWidgetVector.size(); ++i) {
      if (i != 1 && i != 2 && i != 3 && i != 9 && i != 10 && i != 11 &&
          i != 14 && i != 15 && i != 17 && i != 18)
        m_displayResultWidgetVector.at(i)->setPushButtonStatus(true);
    }
    return;
  }
}

double NonHarmonicCalcDialog::calculateHPM() {
  HPM hpm(m_M2, m_M4, m_M6);

  return hpm.HoraPuestoMedia();
}

double NonHarmonicCalcDialog::calculateHP() {
  HoraPuesto hp(m_M2, m_S2, HPM(m_M2, m_M4, m_M6));

  return hp.HP();
}

double NonHarmonicCalcDialog::calculateDV() {
  DuracionVaciante dv(m_M2, m_M4, m_M6);

  return dv.DV();
}

double NonHarmonicCalcDialog::calculateDLL() {
  DuracionLLenante dll(m_M2, m_M4, m_M6);

  return dll.DLL();
}

double NonHarmonicCalcDialog::calculateCMS() {
  CrecimientoMareaSemidiurna cms(m_M2, m_S2);

  return cms.CMS();
}

double NonHarmonicCalcDialog::calculateCMP() {
  CrecimientoMareaParactica cmp(m_M2, m_N2);

  return cmp.CMP();
}

double NonHarmonicCalcDialog::calculateCMD() {
  CreciemientoMareaDiurna cmd(m_K1, m_O1);

  return cmd.CMD();
}

double NonHarmonicCalcDialog::calculateHCMS() {
  HoraCotidianaSemidiurna hcms(m_M2, m_M4, m_M6,
                               m_longitudEditor->coordinate());

  return hcms.HCS();
}

double NonHarmonicCalcDialog::calculateHCMD() {
  HoraCotidianaDiurna hcmd(m_K1, m_O1, m_longitudEditor->coordinate());

  return hcmd.HCD();
}

double NonHarmonicCalcDialog::calculateAPMS() {
  AlturaPromedioMarea apm(m_M2, m_S2, m_N2, m_K2, m_K1, m_O1, m_P1, m_Q1, m_M4,
                          m_M6);

  return apm.AlturaPromedioSemidiurna();
}

double NonHarmonicCalcDialog::calculateAPMSS() {

  AlturaPromedioMarea apm(m_M2, m_S2, m_N2, m_K2, m_K1, m_O1, m_P1, m_Q1, m_M4,
                          m_M6);

  return apm.AlturaPromedioSicigias();
}

double NonHarmonicCalcDialog::calculateAPMC() {

  AlturaPromedioMarea apm(m_M2, m_S2, m_N2, m_K2, m_K1, m_O1, m_P1, m_Q1, m_M4,
                          m_M6);

  return apm.AlturaPromedioCuadratura();
}

double NonHarmonicCalcDialog::calculateAPMT() {

  AlturaPromedioMarea apm(m_M2, m_S2, m_N2, m_K2, m_K1, m_O1, m_P1, m_Q1, m_M4,
                          m_M6);

  return apm.AlturaPromedioTropical();
}

double NonHarmonicCalcDialog::calculateAS() {
  AlturaSemimarea as(m_M2, m_K1, m_O1, m_M4, m_NMMSpinBox->value());

  return as.AlturaDeSemimarea();
}

double NonHarmonicCalcDialog::calculatePMS() {
  PleaBajaMedia pbm(
      AlturaPromedioMarea(m_M2, m_S2, m_N2, m_K2, m_K1, m_O1, m_P1, m_Q1, m_M4,
                          m_M6),
      AlturaSemimarea(m_M2, m_K1, m_O1, m_M4, m_NMMSpinBox->value()));

  return pbm.PleamarMediaSicigias();
}

double NonHarmonicCalcDialog::calculatePMC() {
  PleaBajaMedia pbm(
      AlturaPromedioMarea(m_M2, m_S2, m_N2, m_K2, m_K1, m_O1, m_P1, m_Q1, m_M4,
                          m_M6),
      AlturaSemimarea(m_M2, m_K1, m_O1, m_M4, m_NMMSpinBox->value()));

  return pbm.PleamarMediaCuadratura();
}

double NonHarmonicCalcDialog::calculatePMMT() {
  PleaBajaMedia pbm(
      AlturaPromedioMarea(m_M2, m_S2, m_N2, m_K2, m_K1, m_O1, m_P1, m_Q1, m_M4,
                          m_M6),
      AlturaSemimarea(m_M2, m_K1, m_O1, m_M4, m_NMMSpinBox->value()));

  return pbm.PleamarMediaTropical();
}

double NonHarmonicCalcDialog::calculateBMSS() {
  PleaBajaMedia pbm(
      AlturaPromedioMarea(m_M2, m_S2, m_N2, m_K2, m_K1, m_O1, m_P1, m_Q1, m_M4,
                          m_M6),
      AlturaSemimarea(m_M2, m_K1, m_O1, m_M4, m_NMMSpinBox->value()));

  return pbm.BajamarMediaSicigias();
}

double NonHarmonicCalcDialog::calculateBMC() {
  PleaBajaMedia pbm(
      AlturaPromedioMarea(m_M2, m_S2, m_N2, m_K2, m_K1, m_O1, m_P1, m_Q1, m_M4,
                          m_M6),
      AlturaSemimarea(m_M2, m_K1, m_O1, m_M4, m_NMMSpinBox->value()));

  return pbm.BajamarMediaCuadratura();
}

double NonHarmonicCalcDialog::calculateBMMT() {
  PleaBajaMedia pbm(
      AlturaPromedioMarea(m_M2, m_S2, m_N2, m_K2, m_K1, m_O1, m_P1, m_Q1, m_M4,
                          m_M6),
      AlturaSemimarea(m_M2, m_K1, m_O1, m_M4, m_NMMSpinBox->value()));

  return pbm.BajamarMediaTropical();
}

QString NonHarmonicCalcDialog::fromDoubleToDaysAndHours(double value) {
  QString resp("0");

  if (value > 0.0) {
    int days = qFloor(value);

    int hours = qFloor((value - days) * 24);

    if (days == 1)
      resp = QString::number(days) + " día ";
    else
      resp = QString::number(days) + " días ";
    if (hours == 1)
      resp += QString::number(hours) + " hora";
    else
      resp += QString::number(hours) + " horas";

    // resp = QString::number(days) + " días " + QString::number(hours) + "
    // horas";
    return resp;
  }
  if (value < 0.0) {
    int days = qCeil(value);

    int hours = qCeil((value - days) * 24);

    if (days == -1)
      resp = QString::number(days) + " día ";
    else
      resp = QString::number(days) + " días ";
    if (hours == -1)
      resp += QString::number(hours) + " hora";
    else
      resp += QString::number(hours) + " horas";

    // resp = QString::number(days) + " días " + QString::number(hours) + "
    // horas";
    return resp;
  }
  return resp;
}

QString NonHarmonicCalcDialog::fromDoubleToHoursAndMinutes(double value) {
  QString resp("0");

  if (value > 0.0) {
    int days = qFloor(value);

    int hours = qFloor((value - days) * 60);

    if (days == 1)
      resp = QString::number(days) + " día ";
    else
      resp = QString::number(days) + " días ";
    if (hours == 1)
      resp += QString::number(hours) + " hora";
    else
      resp += QString::number(hours) + " horas";

    // resp = QString::number(days) + " Horas " + QString::number(hours) + "
    // Minutos";
    return resp;
  }
  if (value < 0.0) {
    int days = qCeil(value);

    int hours = qCeil((value - days) * 60);

    if (days == -1)
      resp = QString::number(days) + " día ";
    else
      resp = QString::number(days) + " días ";
    if (hours == -1)
      resp += QString::number(hours) + " hora";
    else
      resp += QString::number(hours) + " horas";

    // resp = QString::number(days) + " Horas " + QString::number(hours) + "
    // Minutos";
    return resp;
  }
  return resp;
}

void NonHarmonicCalcDialog::saveNonHarmonicConstants(const QString &filePath) {
  QFile file(filePath);

  if (file.open(QIODevice::WriteOnly)) {
    QTextStream out(&file);

    out << "CONSTANTES NO ARMONICAS"
        << "\n";
    out << "\n";

    qreal latitud = m_metaData.latitud();
    qreal longitud = m_metaData.longitud();

    out << "PROYECTO: " << m_metaData.projectName() << "\n";
    out << "ESTACION: " << m_metaData.stationName() << "\n";
    out << "SITUACION: " << m_metaData.localizationName() << "\n";

    if (latitud < 0.0)
      out << "LATITUD: " << qFabs(latitud) << "S"
          << "\n";
    if (latitud > 0.0)
      out << "LATITUD: " << latitud << "N"
          << "\n";
    if (latitud == 0.0)
      out << "LATITUD: "
          << "0.000"
          << "\n";

    if (longitud < 0.0)
      out << "LONGITUD: " << qFabs(longitud) << "W"
          << "\n";
    if (longitud > 0.0)
      out << "LONGITUD: " << longitud << "E"
          << "\n";
    if (longitud == 0.0)
      out << "LONGITUD: "
          << "0.000"
          << "\n";

    out << "\n";

    out << "TIPO DE MAREA: " << m_tipoMareaLineEdit->text() << "\n";
    out << "RELACION DE AMPLITUD: " << m_ampRelationLineEdit->text() << "\n";
    out << "RELACION SEMIDIURNA: " << m_semidiurnalRelationLineEdit->text()
        << "\n";

    foreach (displayResultWidget *disp, m_displayResultWidgetVector) {
      if (!disp->lineEditText().isEmpty()) {
        out << disp->title() << " " << disp->lineEditText() << "\n";
      }
    }

  } else {
    QMessageBox::information(this, tr("Error Guardando Archivo"),
                             tr("No se puede escribir el archivo"
                                "%1")
                                 .arg(file.fileName()));
  }
  file.close();
}
