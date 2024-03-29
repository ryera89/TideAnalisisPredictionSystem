#ifndef METADATADIALOG_H
#define METADATADIALOG_H

#include "projectmetadata.h"
#include <QDialog>

class metaDataWidget;
class QPushButton;
class QGroupBox;

class MetaDataDialog : public QDialog {
  Q_OBJECT
public:
  explicit MetaDataDialog(const ProjectMetaData &metadata, QWidget *parent,
                          Qt::WindowFlags f = Qt::WindowFlags());

  QString projectName() const;
  QString stationName() const;
  QString localizationName() const;
  double ceroPuesto() const;
  double nivelReferencia() const;
  double latitud() const;
  double longitud() const;
  MeasurementUnitEditWidget::Units ceroPuestoUnit() const;
  MeasurementUnitEditWidget::Units nivelReferenciaUnit() const;
  QString equipmentId() const;

  int timeZoneOffset() const;
  bool isDaylightTimeSaving() const;

signals:
  void okButtonClicked(bool);

private:
  metaDataWidget *m_metadata;
  QPushButton *m_okButton;
  QPushButton *m_cancelButton;
  QGroupBox *m_groupBox;

  void createComponets();
  void interfazLayout();
};

#endif // METADATADIALOG_H
