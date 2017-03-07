#ifndef MANUALHARMONICCONSTANTINTRODIALOG_H
#define MANUALHARMONICCONSTANTINTRODIALOG_H

#include <QDialog>
#include "include/CoordinatesEditionWidget/mycoordinateseditorwidget.h"
#include "include/ProjectMetaData/timezoneselection.h"
#include "manualharmonicconstantsmodel.h"
#include "manualharmonicconstantsdelegate.h"

class QPushButton;
class QTableView;
class QLineEdit;
class QLabel;

class ManualHarmonicConstantIntroDialog : public QDialog
{
    Q_OBJECT
public:
    ManualHarmonicConstantIntroDialog(QWidget *parent = 0);

    void setHCVector(const QVector<HarmonicConstant> &hcVector);

private:
    QLabel *m_provinciaLabel;
    QLabel *m_localidadLabel;
    QLabel *m_latitudLabel;
    QLabel *m_longitudLabel;

    QLineEdit *m_provinciaEdit;
    QLineEdit *m_localidadEdit;

    MyCoordinatesEditorWidget *m_latitudEditor;
    MyCoordinatesEditorWidget *m_longitudEditor;

    TimeZoneSelection *m_timeZoneSelection;

    QTableView *m_tableView;
    ManualHarmonicConstantsModel *m_tableModel;

    QPushButton *m_acceptButton;
    QPushButton *m_cancelButton;
};

#endif // MANUALHARMONICCONSTANTINTRODIALOG_H
