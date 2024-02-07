#include "manualharmonicconstantintrodialog.h"

#include <QFormLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QTableView>
#include <QVBoxLayout>

#include "include/mainComponents/spmmainwindow.h"

ManualHarmonicConstantIntroDialog::ManualHarmonicConstantIntroDialog(
    QWidget *parent)
    : QDialog(parent, Qt::WindowCloseButtonHint) {
  m_provinciaLabel = new QLabel(tr("Provincia:"));
  m_localidadLabel = new QLabel(tr("Localidad:"));

  m_latitudLabel = new QLabel(tr("Latitud:"));
  m_longitudLabel = new QLabel(tr("Longitud"));

  m_provinciaEdit = new QLineEdit;
  m_localidadEdit = new QLineEdit;

  m_latitudEditor = new MyCoordinatesEditorWidget;

  m_longitudEditor = new MyCoordinatesEditorWidget;
  m_longitudEditor->setHType(MyCoordinatesEditorWidget::longitud);

  m_tableView = new QTableView;
  m_tableModel = new ManualHarmonicConstantsModel;
  m_tableView->setModel(m_tableModel);
  m_tableView->setItemDelegate(new ManualHarmonicConstantsDelegate);

  int width = m_tableView->verticalHeader()->width() + 20;

  for (int i = 0; i < m_tableView->model()->columnCount(QModelIndex()); ++i) {
    width += m_tableView->columnWidth(i);
  }
  m_tableView->setFixedWidth(width);

  m_tableView->resizeRowsToContents();

  m_timeZoneSelection = new TimeZoneSelection;
  m_timeZoneSelection->setTimeZone(7);

  m_acceptButton =
      new QPushButton(QIcon(":images/data-upload.png"), tr("Registrar"));
  connect(m_acceptButton, &QPushButton::clicked, this,
          &ManualHarmonicConstantIntroDialog::saveToDataBase);

  m_cancelButton = new QPushButton(QIcon(":images/No.png"), tr("Cancelar"));
  connect(m_cancelButton, &QPushButton::clicked, this,
          &ManualHarmonicConstantIntroDialog::close);

  QFormLayout *layout1 = new QFormLayout;
  layout1->addRow(m_provinciaLabel, m_provinciaEdit);
  layout1->addRow(m_localidadLabel, m_localidadEdit);
  layout1->addRow(m_latitudLabel, m_latitudEditor);
  layout1->addRow(m_longitudLabel, m_longitudEditor);

  QVBoxLayout *layout2 = new QVBoxLayout;
  layout2->addLayout(layout1);
  layout2->addWidget(m_timeZoneSelection);
  layout2->addStretch();
  layout2->addWidget(m_acceptButton);
  layout2->addWidget(m_cancelButton);

  QHBoxLayout *layout = new QHBoxLayout;
  layout->addWidget(m_tableView);
  layout->addLayout(layout2);

  setLayout(layout);

  this->setMinimumHeight(500);
  setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
  setAttribute(Qt::WA_DeleteOnClose);
}

void ManualHarmonicConstantIntroDialog::setHCVector(
    const QVector<HarmonicConstant> &hcVector) {
  m_tableModel->setAllData(hcVector);
}

void ManualHarmonicConstantIntroDialog::saveToDataBase() {
  selectManualIntroducedHarmonicConstant();
  determineCorrectedPhaseForHCVector();

  uploadHCToDataBase();
}

void ManualHarmonicConstantIntroDialog::determineCorrectedPhaseForHCVector() {
  double longitud = m_longitudEditor->coordinate();
  int timeOffset = m_timeZoneSelection->timeZoneOffset();

  longitud *= -1.0;
  timeOffset *= -1;

  for (int i = 0; i < m_hcVector.size(); ++i) {
    double phase = m_hcVector.at(i).phase();

    double cphase = phase - m_hcVector.at(i).frequency() * timeOffset +
                    m_hcVector.at(i).doodsonNumbers().D1() * longitud;

    m_hcVector[i].setCorrectedPhase(cphase);
  }
}

void ManualHarmonicConstantIntroDialog::
    selectManualIntroducedHarmonicConstant() {
  m_hcVector.clear();
  foreach (const HarmonicConstant &hc, m_tableModel->allData()) {
    if (hc.amplitud() != 0.0) {
      m_hcVector.push_back(hc);
    }
  }
}

/*QVector<HarmonicConstant>
ManualHarmonicConstantIntroDialog::manualIntroducedHarmonicConstant() const
{
    QVector<HarmonicConstant> hcVector;

    foreach (const HarmonicConstant &hc, m_tableModel->allData()) {
        if (hc.amplitud() != 0.0){
            hcVector.push_back(hc);
        }
    }
    return hcVector;
}*/

void ManualHarmonicConstantIntroDialog::uploadHCToDataBase() {
  if (m_hcVector.isEmpty()) {
    QMessageBox::information(this, tr("Error Al Subir Constantes Armónicas"),
                             tr("Todas las constantes armónicas tienen"
                                " amplitud nula."));

  } else {
    QRegExp regexp("\\s+");

    m_provincia = m_provinciaEdit->text().toUpper().replace(regexp, " ");
    m_localidad = m_localidadEdit->text().toUpper().replace(regexp, " ");

    if (m_provincia.isEmpty() || m_localidad.isEmpty()) {
      QMessageBox::information(
          this, tr("Error Al Subir Constantes Armónicas"),
          tr("Faltan datos necesarios para el correcto guardado de "
             "las Constantes Armónicas."));
    } else {
      QString fileName(m_provincia + "_" + m_localidad + "_" + "MANUAL" + "_" +
                       "MANUAL" + ".hcr");

      QString infoFileName(m_provincia + "_" + m_localidad + "_" + "MANUAL" +
                           "_" + "MANUAL" + ".txt");

      QString filePath(SPMmainWindow::hcDataBaseDir() + "/" + fileName);
      QString infoFilePath(SPMmainWindow::hcDataBaseDir() + "/" + infoFileName);

      saveHCToDataBase(filePath);
      saveHCInfoToDataBase(infoFilePath);

      this->close();
    }
  }
}

bool ManualHarmonicConstantIntroDialog::saveHCToDataBase(
    const QString &filePath) {
  QFile file(filePath);

  if (file.open(QIODevice::WriteOnly)) {
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_7);

    QApplication::setOverrideCursor(Qt::WaitCursor);

    out << qint32(SPMmainWindow::HCMagicNumber);

    out << QString(m_provincia); // QString
    out << QString(m_localidad); // QString
    out << QString();            // QString
    // out << int(m_metadataStorage.timeZoneOffset()); //int
    // out << bool(m_metadataStorage.isDaylightTimeSaving()); //bool
    // out << double(m_metadataStorage.nivelReferencia()); //double
    // out << int(m_metadataStorage.referenciaUnit());
    // //MeasurementUnitEditWidget; out <<
    // double(m_metadataStorage.ceroPuesto()); //double out <<
    // int(m_metadataStorage.ceroUnit()); //MeasurementUnitEditWidget
    out << double(m_latitudEditor->coordinate());  // double
    out << double(m_longitudEditor->coordinate()); // double
    // out << QString(m_metadataStorage.equipmentID()); //QString

    // QVector<HarmonicConstant> hcVector = manualIntroducedHarmonicConstant();

    quint32 dataNumber = m_hcVector.size();

    out << quint32(dataNumber);

    foreach (HarmonicConstant hc, m_hcVector) {
      out << QString(hc.name()) << double(hc.frequency())
          << double(hc.amplitud()) << double(hc.phase())
          << double(hc.correctedPhase()) << int(hc.origin())
          << int(hc.doodsonNumbers().D1()) << int(hc.doodsonNumbers().D2())
          << int(hc.doodsonNumbers().D3()) << int(hc.doodsonNumbers().D4())
          << int(hc.doodsonNumbers().D5()) << int(hc.doodsonNumbers().D6())
          << int(hc.doodsonNumbers().Extended());
    }

    QApplication::restoreOverrideCursor();

  } else {
    QMessageBox::warning(this, tr("Error al escribir archivo"),
                         tr("No se puede escribir el archivo %1:\n%2.")
                             .arg(file.fileName().arg(file.errorString())));

    return false;
  }
  file.close();
  return true;
}

bool ManualHarmonicConstantIntroDialog::saveHCInfoToDataBase(
    const QString &filePath) {
  QFile file(filePath);

  if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    QTextStream out(&file);

    out << "CONSTANTES ARMONICAS" << endl;
    out << endl;

    qreal latitud = m_latitudEditor->coordinate();
    qreal longitud = m_longitudEditor->coordinate();

    out << "PROYECTO: " << QString() << endl;
    out << "ESTACION: " << QString() << endl;
    out << "SITUACION: " << QString() << endl;

    out << "PROVINCIA: " << m_provincia << endl;
    out << "LOCALIDAD: " << m_localidad << endl;

    out.setRealNumberNotation(QTextStream::FixedNotation);
    out.setRealNumberPrecision(3);
    if (latitud < 0.0)
      out << "LATITUD: " << qFabs(latitud) << "S" << endl;
    if (latitud > 0.0)
      out << "LATITUD: " << latitud << "N" << endl;
    if (latitud == 0.0)
      out << "LATITUD: "
          << "0.000" << endl;

    if (longitud < 0.0)
      out << "LONGITUD: " << qFabs(longitud) << "W" << endl;
    if (longitud > 0.0)
      out << "LONGITUD: " << longitud << "E" << endl;
    if (longitud == 0.0)
      out << "LONGITUD: "
          << "0.000" << endl;

    out << endl;

    QString constituente("CONSTITUENTE");
    QString v_ang("V. ANGULAR[grad/seg]");
    QString amp("AMPLITUD[m]");
    QString fase("FASE[grad]");
    QString faseC("FASE.C[grad]");
    QString origen("ORIGEN");
    QString numDod("NUMERO_DOODSON");

    out.setPadChar('-');

    out << constituente << "  " << v_ang << "  " << amp << "  " << fase << "  "
        << faseC << "  " << origen << "  " << numDod << endl;
    // out << "------------" << "  " << "--------------------" << "  " <<
    // "-----------" << "  " << "----------" << endl;

    foreach (HarmonicConstant hc, m_hcVector) {
      out.setFieldWidth(constituente.length());
      out.setFieldAlignment(QTextStream::AlignCenter);
      out << hc.name();

      out.setFieldWidth(0);
      out.setFieldAlignment(QTextStream::AlignCenter);
      out << "  ";

      out.setFieldWidth(v_ang.length());
      out.setFieldAlignment(QTextStream::AlignCenter);
      out.setRealNumberPrecision(7);
      out << hc.frequency();

      out.setFieldWidth(0);
      out.setFieldAlignment(QTextStream::AlignCenter);
      out << "  ";

      out.setFieldWidth(amp.length());
      out.setFieldAlignment(QTextStream::AlignCenter);
      out.setRealNumberPrecision(6);
      out << hc.amplitud();

      out.setFieldWidth(0);
      out.setFieldAlignment(QTextStream::AlignCenter);
      out << "  ";

      out.setFieldWidth(fase.length());
      out.setFieldAlignment(QTextStream::AlignCenter);
      out.setRealNumberPrecision(3);
      out << hc.phase();

      out.setFieldWidth(0);
      out.setFieldAlignment(QTextStream::AlignCenter);
      out << "  ";

      out.setFieldWidth(faseC.length());
      out.setFieldAlignment(QTextStream::AlignCenter);
      out << hc.correctedPhase();

      out.setFieldWidth(0);
      out.setFieldAlignment(QTextStream::AlignCenter);
      out << "  ";

      out.setFieldWidth(origen.length());
      out.setFieldAlignment(QTextStream::AlignCenter);
      out << hc.origin();

      out.setFieldWidth(0);
      out.setFieldAlignment(QTextStream::AlignCenter);
      out << "  ";

      // out.setFieldWidth(numDod.length());
      out.setFieldAlignment(QTextStream::AlignCenter);
      out << "(" << hc.doodsonNumbers().D1() << "," << hc.doodsonNumbers().D2()
          << "," << hc.doodsonNumbers().D3() << "," << hc.doodsonNumbers().D4()
          << "," << hc.doodsonNumbers().D5() << "," << hc.doodsonNumbers().D6()
          << "," << hc.doodsonNumbers().Extended() << ")";

      out.setFieldWidth(0);
      out.setFieldAlignment(QTextStream::AlignCenter);
      out << endl;
    }

  } else {
    QMessageBox::information(this, tr("Error Guardando Archivo"),
                             tr("No se puede escribir el archivo"
                                "%1")
                                 .arg(file.fileName()));

    return false;
  }
  file.close();

  return true;
}
