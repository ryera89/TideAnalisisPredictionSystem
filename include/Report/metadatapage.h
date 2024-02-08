#ifndef METADATAPAGE_H
#define METADATAPAGE_H

#include "../ProjectMetaData/projectmetadata.h"
#include <QWizardPage>

class QLabel;
class QLineEdit;
class QDateEdit;
class QGroupBox;

class MetadataPage : public QWizardPage {
  Q_OBJECT
public:
  MetadataPage(QWidget *parent = 0);

  QString nombrePuesto() const;
  QString establecimiento() const;
  QString ceroPuesto() const;
  QString nivelReferencia() const;
  QString latitud() const;
  QString longitud() const;
  QString fechaInicio() const;
  QString fechaFinal() const;
  QString duracion() const;
  QString usoHorario() const;
  QString responsableHeader() const;
  QString responsable() const;
  QString responsabeDpto() const;

  void setMetaData(const ProjectMetaData &metadata);
  void setMeasurementsPeriod(const QDate &begin, const QDate &end);

private:
  QLabel *m_nombrePuestoLabel;
  QLabel *m_establecimientoLabel;
  QLabel *m_ceroPuestoLabel;
  QLabel *m_nivelReferenciaLabel;
  QLabel *m_latitudLabel;
  QLabel *m_longitudLabel;
  QLabel *m_fechaInicioLabel;
  QLabel *m_fechaFinalLabel;
  QLabel *m_duracionLabel;
  QLabel *m_usoHorarioLabel;
  QLabel *m_nombreResponsableLabel;
  QLabel *m_apellidosResponsableLabel;
  QLabel *m_dptoLabel;

  QLineEdit *m_nombrePuestoEdit;
  QLineEdit *m_establecimientoEdit;
  QLineEdit *m_ceroPuestoEdit;
  QLineEdit *m_nivelReferenciaEdit;
  QLineEdit *m_latitudEdit;
  QLineEdit *m_longitudEdit;
  QDateEdit *m_fechaInicioDateEdit;
  QDateEdit *m_fechaFinalDateEdit;
  QLineEdit *m_duracionEdit;
  QLineEdit *m_usoHorarioEdit;
  QLineEdit *m_nombreResponsableEdit;
  QLineEdit *m_apellidosResponsableEdit;
  QLineEdit *m_dptoEdit;

  QGroupBox *m_responsabeGroupBox;
};

#endif // METADATAPAGE_H
