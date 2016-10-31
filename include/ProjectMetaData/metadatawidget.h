#ifndef METADATAWIDGET_H
#define METADATAWIDGET_H

/*Facilities for project metadata introduction and edition*/

#include <QWidget>

class QLineEdit;
class QLabel;

class metaDataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit metaDataWidget(QWidget *parent = 0);

    QString projectName() const;
    QString stationName() const;
    QString localizationName() const;
    QString latitud() const;
    QString longitud() const;
    QString equipmentID() const;

    void setProjectName(const QString &str);
    void setStationName(const QString &str);
    void setLocalizationName(const QString &str);
    void setLatitud(const QString &str);
    void setLongitud(const QString &str);
    void setEquipmentID(const QString &str);

signals:

public slots:

private:
    QLabel *m_projectNameLabel;
    QLabel *m_stationNameLabel;
    QLabel *m_localizationNameLabel;
    QLabel *m_latitudLabel;
    QLabel *m_longitudLabel;
    QLabel *m_equipmentIdLabel;

    QLineEdit *m_projectNameLineEdit;
    QLineEdit *m_stationNameLineEdit;
    QLineEdit *m_localizationNameLineEdit;
    QLineEdit *m_latitudLineEdit;
    QLineEdit *m_longitudLineEdit;
    QLineEdit *m_equipmentIdLineEdit;

    void createComponents();
    void interfazLayout();


};

#endif // METADATAWIDGET_H
