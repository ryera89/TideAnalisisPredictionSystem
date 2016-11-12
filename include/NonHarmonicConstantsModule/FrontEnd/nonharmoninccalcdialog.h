#ifndef NONHARMONINCCALCDIALOG_H
#define NONHARMONINCCALCDIALOG_H

#include <QDialog>
#include "displayresultwidget.h"
#include <QSignalMapper>

class QLabel;
class QDoubleSpinBox;
class MyCoordinatesEditorWidget;

class NonHarmonicCalcDialog : public QDialog
{
    Q_OBJECT

public:
    NonHarmonicCalcDialog(QWidget *parent = 0);
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

    void createComponents();
    void createDisplaysResultWidgets();
    void setInterfaceLayout();
};

#endif // NONHARMONINCCALCDIALOG_H
