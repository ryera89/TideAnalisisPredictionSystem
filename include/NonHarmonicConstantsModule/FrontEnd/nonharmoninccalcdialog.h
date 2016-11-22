#ifndef NONHARMONINCCALCDIALOG_H
#define NONHARMONINCCALCDIALOG_H

#include <QDialog>
#include "displayresultwidget.h"
#include <QSignalMapper>
#include "include/HarmonicConstantsModule/HarmonicConstantClass/harmonicconstant.h"

class QLabel;
class QDoubleSpinBox;
class MyCoordinatesEditorWidget;

class NonHarmonicCalcDialog : public QDialog
{
    Q_OBJECT

public:
    NonHarmonicCalcDialog(QWidget *parent = 0);
    void loadHarmonicConstants(const QVector<HarmonicConstant> &harmonicConstants);
    ~NonHarmonicCalcDialog(){}

private slots:
    void calculate(int index);

private:
    QVector<displayResultWidget*> m_displayResultWidgetVector;

    QFrame *m_inputFrame;
    QFrame *m_relationFrame;

    QFrame *m_column1Frame;
    QFrame *m_column2Frame;
    QFrame *m_column3Frame;

    QLabel *m_NMMLabel;
    QLabel *m_longitudLabel;
    QLabel *m_ampRelationLabel;
    QLabel *m_semidiurnalRelationLabel;
    QLabel *m_tipoMareaLabel;

    QDoubleSpinBox *m_NMMSpinBox;
    MyCoordinatesEditorWidget *m_longitudEditor;
    QLineEdit *m_ampRelationLineEdit;
    QLineEdit *m_semidiurnalRelationLineEdit;
    QLineEdit *m_tipoMareaLineEdit;

    QPushButton *m_calcAllPushButton;
    QPushButton *m_savePushButton;
    QPushButton *m_closePushButton;

    QSignalMapper *m_mapper;

    HarmonicConstant m_M2; //Semidiurnal
    HarmonicConstant m_S2;
    HarmonicConstant m_N2;
    HarmonicConstant m_K2;

    HarmonicConstant m_K1; //Diurnal
    HarmonicConstant m_O1;
    HarmonicConstant m_P1;
    HarmonicConstant m_Q1;

    HarmonicConstant m_M4; //Bajo Fondo
    HarmonicConstant m_M6;

    void createComponents();
    void createDisplaysResultWidgets();
    void setInterfaceLayout();

    void checkForMainComponents();
};

#endif // NONHARMONINCCALCDIALOG_H
