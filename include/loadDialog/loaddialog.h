#ifndef LOADDIALOG_H
#define LOADDIALOG_H

#include <QDialog>
#include "linenumbereditor.h" //Custom Text Editor with line Numbers
#include "include/ProjectMetaData/metadatawidget.h"
#include "include/ProjectMetaData/projectmetadata.h"

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
class QProgressBar;


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
    //Meta Data
    QString projectName() const{return m_metaDataWidget->projectName();}
    QString stationName() const{return m_metaDataWidget->stationName();}
    QString localizationName() const{return m_metaDataWidget->localizationName();}
    double ceroPuesto() const{return m_metaDataWidget->ceroPuesto();}
    double nivelReferencia() const{return m_metaDataWidget->nivelReferencia();}
    MeasurementUnitEditWidget::Units ceroUnit() const{return m_metaDataWidget->ceroUnit();}
    MeasurementUnitEditWidget::Units referenceUnit() const{return m_metaDataWidget->referenciaUnit();}
    double latitud() const{return m_metaDataWidget->latitud();}
    double longitud() const{return m_metaDataWidget->longitud();}
    QString equipmentID() const{return m_metaDataWidget->equipmentID();}

    int timeZoneOffset() const{return m_metaDataWidget->timeZoneOffset();}
    bool isDaylightTimeSaving() const{return m_metaDataWidget->isDaylightTimeSaving();}

    void setProjectMetaData(const ProjectMetaData &metadata);

public slots:
    void getDataPoints();
    void getDataPointAndAppendData();
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
    void importButtonClicked(); //Para remplazar los datos del proyecto
    void appendDataActionTrigered(); //Para agregar los nuevos datos a los datos del proyecto

private:
    QVector<TidesMeasurement> measurements;

    QPushButton* m_importButton;

    //Import Button Menu and Actions
    QMenu *m_importMenu;
    QAction *m_replaceDataAction;
    QAction *m_appendDataAction;

    QPushButton* m_cancelButton;

    LineNumberEditor* m_importTextEdit;
    metaDataWidget *m_metaDataWidget;
    //ProjectMetaData m_metaData;

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

    QProgressBar *m_importProgressBar;

    QString m_timeFormat;
    QString m_dateFormat;

    void settingUpEveryThing();
};

#endif // LOADDIALOG_H
