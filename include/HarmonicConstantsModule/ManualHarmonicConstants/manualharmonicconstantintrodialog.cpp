#include "manualharmonicconstantintrodialog.h"

#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTableView>
#include <QFormLayout>
#include <QHeaderView>

ManualHarmonicConstantIntroDialog::ManualHarmonicConstantIntroDialog(QWidget *parent):
    QDialog(parent,Qt::WindowCloseButtonHint)
{
    m_provinciaLabel = new QLabel(tr("Provincia:"));
    m_localidadLabel = new QLabel(tr("Localidad:"));

    m_latitudLabel = new QLabel(tr("Latitud:"));
    m_longitudLabel = new QLabel(tr("Longitud"));

    m_provinciaEdit = new QLineEdit;
    m_localidadEdit = new QLineEdit;

    m_latitudEditor = new MyCoordinatesEditorWidget;

    m_longitudEditor = new MyCoordinatesEditorWidget;
    m_longitudEditor->setHType(MyCoordinatesEditorWidget::longitud);

    m_tableView = new QTableView;
    m_tableModel = new ManualHarmonicConstantsModel;
    m_tableView->setModel(m_tableModel);
    m_tableView->setItemDelegate(new ManualHarmonicConstantsDelegate);

    int width = m_tableView->verticalHeader()->width() + 20;

    for (int i = 0; i < m_tableView->model()->columnCount(QModelIndex());++i){
        width += m_tableView->columnWidth(i);
    }
    m_tableView->setFixedWidth(width);

    m_tableView->resizeRowsToContents();

    m_timeZoneSelection = new TimeZoneSelection;
    m_timeZoneSelection->setTimeZone(7);

    m_acceptButton = new QPushButton(QIcon(":images/data-upload.png"),tr("Registrar"));

    m_cancelButton = new QPushButton(QIcon(":images/No.png"),tr("Cancelar"));

    QFormLayout *layout1 = new QFormLayout;
    layout1->addRow(m_provinciaLabel,m_provinciaEdit);
    layout1->addRow(m_localidadLabel,m_localidadEdit);
    layout1->addRow(m_latitudLabel,m_latitudEditor);
    layout1->addRow(m_longitudLabel,m_longitudEditor);

    QVBoxLayout *layout2 = new QVBoxLayout;
    layout2->addLayout(layout1);
    layout2->addWidget(m_timeZoneSelection);
    layout2->addStretch();
    layout2->addWidget(m_acceptButton);
    layout2->addWidget(m_cancelButton);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(m_tableView);
    layout->addLayout(layout2);

    setLayout(layout);

    this->setMinimumHeight(500);
    setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);
    setAttribute(Qt::WA_DeleteOnClose);
}

void ManualHarmonicConstantIntroDialog::setHCVector(const QVector<HarmonicConstant> &hcVector)
{
    m_tableModel->setAllData(hcVector);
}
