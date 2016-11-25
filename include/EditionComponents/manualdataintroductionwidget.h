#ifndef MANUALDATAINTRODUCTIONWIDGET_H
#define MANUALDATAINTRODUCTIONWIDGET_H

#include <QDialog>

#include "editiontable.h"
#include "include/model_view/tablemodel.h"
#include "include/ProjectMetaData/metadatawidget.h"

class QLabel;
class QTimeEdit;
class QDateEdit;
class QPushButton;
class QGroupBox;
class QComboBox;
class QRadioButton;


class ManualDataIntroductionWidget : public QDialog
{
    Q_OBJECT
public:
    explicit ManualDataIntroductionWidget(QWidget *parent = 0);

    TableModel* model()const{return m_model;}

signals:
    void dataTrenfer(const QVector<TidesMeasurement> &data);
    void okButtonClicked();

public slots:


private slots:
    void setMinimumDateEditValue(const QDate &date);//Para setear el minimo valor permitido del m_endDateEdit
    //void setMinimumTimeEditValue(const QTime &time);//Para setear el minimo valor permitido del m_endTimeEdit
    void enableTimeIntervalEdit(int index);
    void updateTimeInterval(int index); //Para conectar con el combo box
    void setTimeInterval(const QTime &time); //Para conectar con el m_intervalTimeEdit

    void removeLastMeasurement();
    void removeRows(int row,int cont);
    void insertMeasurement();
    void clearMeasurements();
    //void beginDataTranfer();

    void generateData(); //Para conectar con el genPushButton

private:
    EditionTable *m_editionTable;
    TableModel *m_model;

    metaDataWidget *m_metaData;

    quint64 m_timeInterval;

    QLabel *m_iniDateLabel;
    QLabel *m_endDateLabel;
    QLabel *m_iniTimeLabel;
    QLabel *m_endTimeLabel;
    QLabel *m_timeIntervalLabel;
    QLabel *m_customIntervalLabel;

    QDateEdit *m_iniDateEdit;
    QDateEdit *m_endDateEdit;

    QTimeEdit *m_iniTimeEdit;
    QTimeEdit *m_endTimeEdit;

    QComboBox *m_timeIntervalComboBox;
    QTimeEdit *m_timeIntervalTimeEdit;

    QGroupBox *m_mainGroupBox;
    QGroupBox *m_ini_endGroupBox;
    //QGroupBox *m_timeIntervalGroupBox;

    QPushButton *m_genPushButton;

    QGroupBox *m_buttonsGroupBox;

    QPushButton *m_insertPushButton;
    QPushButton *m_removePushButton;
    QPushButton *m_clearPushButton;

    QGroupBox *m_desitionButtonsGroupBox;

    QPushButton *m_okPushButton;
    QPushButton *m_cancelPushButton;

    QRadioButton *m_levelRadioButton;
    QRadioButton *m_correctionsRadioButton;

    QComboBox *m_measurementUnitComboBox;

    void createComponents();
    void settingTableWidth();



};

#endif // MANUALDATAINTRODUCTIONWIDGET_H
