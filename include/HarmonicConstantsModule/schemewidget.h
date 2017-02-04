#ifndef SCHEMEWIDGET_H
#define SCHEMEWIDGET_H

#include <QDialog>

#include "SchemeConfigDialog/schemeconfigdialog.h"
#include "tidalschemeselectionwidget.h"
#include "include/HarmonicConstantsModule/HarmonicConstantClass/harmonicconstant.h"
#include <QDateTime>
#include <QMovie>
#include <QPropertyAnimation>
#include <QFrame>

class QComboBox;
class QPushButton;
class QPlainTextEdit;
class QProgressBar;
class QToolButton;
class QGroupBox;
class QPlainTextEdit;
class QTableView;
class HarmonicConstantFullTableModel;
class QRadioButton;
class QDateTimeEdit;
class QTimeEdit;
class QLabel;
class QDateEdit;
//class QDateTime;

class SchemeWidget : public QDialog
{  
    Q_OBJECT
public:
    explicit SchemeWidget(const QStringList &schemesLabels, const QStringList &componentsLabels, const QMap<QString,QMap<QString,bool>> &schemes_componentMap,const QMap<QString,QString> &schemeDescription,QWidget *parent = 0);

    QMap<QString,bool> selectedSchemeComponentStatus() const;
    void setHarmonicConstantModelData(const QVector<HarmonicConstant> &datos);
    void showHarmonicConstantTable();
    int harmonicAnalisisTypeMethod();
    int equationSystemSolutionMethod();

    //QDateTime initialDateTime() const{return m_initialDateTime;}
    //QDateTime endDateTime() const{return m_endDateTime;}
    //quint64 timeInterval() const{return m_timeInterval;}

    int currentSelectionComboBoxIndex() const;
signals:
    void analizeButtonClicked();
    void saveDataButtonClicked();
    void saveHarmonicConstantsButtonClicked();
public slots:
    void enableSaveHarmonicConstantButton();
    void beginHarmonicAnalisis();
private slots:
    void createConfigSchemeDialog();
    void selectAnalisisScheme(const QString &str);
    void updateInternalData();
    void changeScheme(const QString &newScheme);

    //void setIniDate(QDate date);
    //void setEndDate(QDate date);

    //void setIniTime(QTime time);
    //void setEndTime(QTime time);

    //void updateTimeInterval(QTime time);
    //void enableCustomDataSelection(int index);

private:
    QStringList m_schemesLabels;
    QStringList m_componentsLabels;
    QMap<QString,QMap<QString,bool>> m_schemes_componentMap;
    QMap<QString,QString> m_schemeDescriptionMap; 

    QGroupBox *m_descriptionGroupBox;
    QGroupBox *m_componentGroupBox; //Para el Widget de los componentes

    QComboBox *m_schemeComboBox;
    TidalSchemeSelectionWidget *m_tidalSchemeComponents;
    QPlainTextEdit *m_schemeDescriptionPlainTextEdit;

    QToolButton *m_configEsquemaToolButton;
    QPushButton *m_analizarPushButton;

    QFrame *m_tableFrame;
    QTableView *m_harmonicConstantTableView;
    HarmonicConstantFullTableModel *m_harmonicConstantTableModel;

    QPushButton *m_saveHarmonicConstantsButton;

    QGroupBox *m_analisisTypeGroupBox;
    QGroupBox *m_fitMethodGroupBox;
    QComboBox *m_HarmonicAnalisisMethodComboBox;
    QComboBox *m_SystemSolutionMethodComboBox;
    //QRadioButton *m_luRadioButton;
    //QRadioButton *m_svdRadioButton;

    //*********************Data time filter***********************************
    //QComboBox *m_dataSelectionComboBox;
    //QGroupBox *m_dataSelectionGroupBox;
    //QGroupBox *m_customDataSelectionGroupBox;

    //QDateEdit *m_iniDateEdit;
    //QDateEdit *m_endDateEdit;
    //QTimeEdit *m_iniTimeEdit;
    //QTimeEdit *m_endTimeEdit;

    //QLabel *m_customIntervalLabel;
    //QTimeEdit *m_customIntervalTimeEdit;

    //QDateTime m_initialDateTime;
    //QDateTime m_endDateTime;

    //quint64 m_timeInterval;

    //QPushButton *m_saveSelectedData;

    //************************************************************************

    //Loading Label
    QLabel *m_loadingLabel;
    QMovie *m_loadingMovie;

    //QML component
    //QQuickWidget *m_loadingQuickWidget;

    SchemeConfigDialog *m_configSchemeDialog;

    QPropertyAnimation *m_animation;

    //QPushButton *m_createSchemePushButton;
    //QPushButton *m_modifySchemePushButton;
    //QPushButton *m_eliminateSchemePushButton;

    void setSchemesLabels(const QStringList &schemesLabels);
    //void setComponentsLabels(const QStringList &componentsNames);
    void setSchemesComponentsMap(const QMap<QString,QMap<QString,bool>> &schemes_componentMap);

    void crearComponentes(const QStringList &schemesLabels, const QStringList &componentsLabels);
    void interfazLayout();

    //void createLoadingWidget(); //Funcion que crea el componente QML;

};

#endif // SCHEMEWIDGET_H
