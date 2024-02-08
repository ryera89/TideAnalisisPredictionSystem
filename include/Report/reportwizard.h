#ifndef REPORTWIZARD_H
#define REPORTWIZARD_H

#include "../HarmonicConstantClass/harmonicconstant.h"
#include "../ProjectMetaData/projectmetadata.h"
#include "ceroprofpage.h"
#include "chapaspage.h"
#include "conclusionpage.h"
#include "finalpage.h"
#include "generalidadespage.h"
#include "intropage.h"
#include "metadatapage.h"
#include <QWizard>

class ReportWizard : public QWizard {
  Q_OBJECT
public:
  ReportWizard(QWidget *parent = 0);

  void setHarmonicConstants(const QVector<HarmonicConstant> &hcVector);

  void setMetaData(const ProjectMetaData &metadata);
  void setMeasurementsPeriod(const QDate &begin, const QDate &end);

  QString m_HoraDelPuestoMedia;
  QString m_HoraDelPuesto;
  QString m_DuracionDelVaciante;
  QString m_DuracionDelLlenate;
  QString m_CrecimientoDeLaMareaSemidiurna;
  QString m_CrecimientoDeLaMareaParalactica;
  QString m_CrecimientoDeLaMareaDiurna;
  QString m_HoraCotidianaDeLaMareaSemidiurna;
  QString m_HoraCotidianaDeLaMareaDiurna;
  QString m_AlturaPromedioDeLaMareaSemidiurna;
  QString m_AlturaPromedioDeLaMareaSicigias;
  QString m_AlturaPromedioDeLaMareaCuadratura;
  QString m_AlturaPromedioDeLaMareaTropical;
  QString m_RelacionDeAmplitud;

public slots:
  void accept();

private:
  IntroPage *m_introPage;
  MetadataPage *m_metadataPage;
  GeneralidadesPage *m_generalidadesPage;
  ChapasPage *m_chapasReferenciasPage;
  CeroProfPage *m_ceroProfundidadPage;
  FinalPage *m_responsablesPage;
  ConclusionPage *m_conclusionPage;

  QVector<HarmonicConstant> m_hcVector;
};

#endif // REPORTWIZARD_H
