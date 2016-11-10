#ifndef METADATADIALOG_H
#define METADATADIALOG_H

#include <QDialog>

class ProjectMetaData;
class metaDataWidget;
class QPushButton;
class QGroupBox;

class MetaDataDialog : public QDialog
{
    Q_OBJECT
public:
    MetaDataDialog(const ProjectMetaData &metadata, QWidget *parent, Qt::WindowFlags f = Qt::WindowFlags());

    QString projectName() const;
    QString stationName() const;
    QString localizationName() const;
    double latitud() const;
    double longitud() const;
    QString equipmentId() const;

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
