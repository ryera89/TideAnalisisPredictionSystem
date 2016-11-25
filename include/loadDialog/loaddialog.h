#ifndef LOADDIALOG_H
#define LOADDIALOG_H

#include <QDialog>
#include "linenumbereditor.h" //Custom Text Editor with line Numbers
#include "include/ProjectMetaData/metadatawidget.h"
//#include "include/metadatawidget.h"

class QLabel;
class QLineEdit;
class QPushButton;
class QGridLayout;
class QVBoxLayout;
class QHBoxLayout;
class QGroupBox;
class QComboBox;
class QString;
class QStringList;
class QIntValidator;
class QSpinBox;
class QRadioButton;

#include <QVector>
#include "include/measurement/measurement.h"

class LoadDialog : public QDialog
{
    Q_OBJECT

public:
    LoadDialog(QWidget *parent = 0);
    LoadDialog(const QString &filePath, QWidget *parent = 0);
    ~LoadDialog();

    QVector<TidesMeasurement> measurementsData() const {return measurements;}
    //metaDataWidget* metaData() const{return m_dataWidget;}

    bool isLevelRadioButtonChecked();
    //QString loacationName() const;
    //QString equipmentID() const;
    //QString latitud() const;
    //QString longitud() const;

    //QString getLocationName() const {return m_locationLineEdit->text();} //Obtiene el nombre de la localizacion
    //QString getEquipmentId() const {return m_equipmentIDLineEdit->text();} //Retorna el id del equipo

    //NOTE: Ver despues el formato en que se trabaja de latitud y longitud
   // QString getLatitud() const {return m_latitudLineEdit->text();}
    //QString getLongitud() const {return m_longitudLineEdit->text();}

public slots:
    void getDataPoints();
    void setTopFieldValidValue(int value);

    void setTopFieldValidValue(); //PAra conectar los separators editors


    void enableFieldEditorsEdition();
    void enableImportButton();
    void fillFirstAndLastDataPoints();
    void fillFirstAndLastDate(int index);
    void fillFirstAndLastTime(int index);
    void fillFirstAndLastHeigth(int index);

private slots:
    //void enableTimeFormatEdit(const QString &str);
    //void enableDateFormatEdit(const QString &str);

    void setTimeFormat(const QString &format);
    void setDateFormat(const QString &format);
    void setCustomTimeFormat(const QString &format);
    void setCustomDateFormat(const QString &format);

    void setMinimumLastLineValue(int);

signals:
    void importButtonClicked();

    //void dataGeted(const QVector<QStringList>&, int, int, int, const QString &dateFormat, const QString &timeFormat);
    //void sendLocationName(const QString &);
    //void sendEquipmentID(const QString &);
    //void sendLatitud(const QString &);
    //void sendLongitud(const QString &);
    //void sendDateTimeStringFormat(const QString &dateFormat, const QString &timeFormat); //signal para transmitir el formato

private:
    QVector<TidesMeasurement> measurements;

    QPushButton* m_importButton;
    QPushButton* m_cancelButton;

    LineNumberEditor* m_importTextEdit;
    metaDataWidget *m_metaDataWidget;

    QLabel *m_dateLabel;
    QLabel *m_timeLabel;
    QLabel *m_heigthLabel;

    QLabel *m_fieldLabel;
    QLabel *m_separatorLabel;
    QLabel *m_firstPointLabel;
    QLabel *m_lastPointLabel; //

    QSpinBox *m_fieldDateEdit;
    QSpinBox *m_fieldTimeEdit;
    QSpinBox *m_fieldHeightEdit;

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
    //QGroupBox *m_unitGroupBox;             //unidad de medicion
    //QGroupBox *m_correctionGroupBox;      //Para la correccion al nivel
    //QGroupBox *m_localizationGroupBox;   //Para localizacion
    QGroupBox *m_firstLineGroupBox;

    QGroupBox *m_lastLineGroupBox;       //ultima linea a cargar.

    //QComboBox *m_unitComboBox;
    //QLineEdit *m_correctionLineEdit;

    //QLineEdit *m_locationLineEdit; //Para los metadatos localizacion.
    //QLineEdit *m_latitudLineEdit;
    //QLineEdit *m_longitudLineEdit;
    //QLineEdit *m_equipmentIDLineEdit; //

    QSpinBox *m_firstLineLineEdit;
    QSpinBox *m_lastLineLineEdit;

    //QLabel *m_locationLabel;
    //QLabel *m_equimentIDLabel; //
    //QLabel *m_latitudLabel;
    //QLabel *m_longitudLabel;


    //QIntValidator *m_fValidator;
    //QIntValidator *m_lValidator;
    //QIntValidator *m_fieldValidator;

    QGroupBox *m_dateFormatGroupBox;
    QGroupBox *m_timeFormatGroupBox;
    QGroupBox *m_measurementUnitGroupBox;

    QComboBox *m_dateFormatComboBox;
    QComboBox *m_timeFormatComboBox;
    QComboBox *m_measurementUnitComboBox;

    QLineEdit *m_dateFormatLineEdit;
    QLineEdit *m_timeFormatLineEdit;

    QRadioButton *m_corrRadioButton;
    QRadioButton *m_levelRadioButton;

    QString m_timeFormat;
    QString m_dateFormat;

    void settingUpEveryThing();
};

#endif // LOADDIALOG_H
