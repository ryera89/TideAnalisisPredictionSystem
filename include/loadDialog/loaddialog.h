#ifndef LOADDIALOG_H
#define LOADDIALOG_H

#include <QDialog>
#include "linenumbereditor.h" //Custom Text Editor with line Numbers
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QComboBox>
#include <QIntValidator>

#include <QString>
#include <QStringList>
#include <QVector>

//TODO que el dialogo salga mas grande

class LoadDialog : public QDialog
{
    Q_OBJECT

public:
    LoadDialog(QWidget *parent = 0);
    LoadDialog(const QString &filePath, QWidget *parent = 0);
    ~LoadDialog();

    //QString getLocationName() const {return m_locationLineEdit->text();} //Obtiene el nombre de la localizacion
    //QString getEquipmentId() const {return m_equipmentIDLineEdit->text();} //Retorna el id del equipo

    //NOTE: Ver despues el formato en que se trabaja de latitud y longitud
   // QString getLatitud() const {return m_latitudLineEdit->text();}
    //QString getLongitud() const {return m_longitudLineEdit->text();}

public slots:
    void getDataPoints();
    void setTopFieldValidValue(const QString &text);


    void enableFieldEditorsEdition();
    void enableImportButton();
    void fillFirstAndLastDataPoints();

signals:
    void dataGeted(const QVector<QStringList>&, int, int, int, const QString &dateFormat, const QString &timeFormat);

    void sendLocationName(const QString &);
    void sendEquipmentID(const QString &);
    void sendLatitud(const QString &);
    void sendLongitud(const QString &);
    //void sendDateTimeStringFormat(const QString &dateFormat, const QString &timeFormat); //signal para transmitir el formato

private:
    QPushButton* m_importButton;
    QPushButton* m_cancelButton;

    LineNumberEditor* m_importTextEdit;

    QLabel *m_dateLabel;
    QLabel *m_timeLabel;
    QLabel *m_heigthLabel;

    QLabel *m_fieldLabel;
    QLabel *m_separatorLabel;
    QLabel *m_firstPointLabel;
    QLabel *m_lastPointLabel; //

    QLineEdit *m_fieldDateEdit;
    QLineEdit *m_fieldTimeEdit;
    QLineEdit *m_fieldHeightEdit;

    QLineEdit *m_separatorDateEdit;
    QLineEdit *m_separatorTimeEdit;
    QLineEdit *m_separatorHeigthEdit;

    QLineEdit *m_firstPointDateEdit;
    QLineEdit *m_firstPointTimeEdit;
    QLineEdit *m_firstPointHeigthEdit;

    QLineEdit *m_lastPointDateEdit;  //
    QLineEdit *m_lastPointTimeEdit;  //
    QLineEdit *m_lastPointHeigthEdit; //

    QGroupBox *m_measurementGroupBox;     //General measurement
    QGroupBox *m_unitGroupBox;             //unidad de medicion
    QGroupBox *m_correctionGroupBox;      //Para la correccion al nivel
    QGroupBox *m_localizationGroupBox;   //Para localizacion
    QGroupBox *m_firstLineGroupBox;

    QGroupBox *m_lastLineGroupBox;       //ultima linea a cargar.

    QComboBox *m_unitComboBox;
    QLineEdit *m_correctionLineEdit;

    QLineEdit *m_locationLineEdit; //Para los metadatos localizacion.
    QLineEdit *m_latitudLineEdit;
    QLineEdit *m_longitudLineEdit;
    QLineEdit *m_equipmentIDLineEdit; //

    QLineEdit *m_firstLineLineEdit;
    QLineEdit *m_lastLineLineEdit;

    QLabel *m_locationLabel;
    QLabel *m_equimentIDLabel; //
    QLabel *m_latitudLabel;
    QLabel *m_longitudLabel;


    QIntValidator *m_fValidator;
    QIntValidator *m_lValidator;
    QIntValidator *m_fieldValidator;

    QGroupBox *m_dateFormatGroupBox;
    QGroupBox *m_timeFormatGroupBox;

    QLineEdit *m_dateFormatLineEdit;
    QLineEdit *m_timeFormatLineEdit;

    void settingUpEveryThing();
};

#endif // LOADDIALOG_H
