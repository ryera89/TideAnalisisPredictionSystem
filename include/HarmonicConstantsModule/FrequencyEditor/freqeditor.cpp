#include "freqeditor.h"
#include "include/HarmonicConstantsModule/Model_View/harmonicconstantfrequencytablemodel.h"
#include "include/HarmonicConstantsModule/Model_View/harmonicconstantfrequencytabledelegate.h"
#include "include/HarmonicConstantsModule/HarmonicConstantClass/harmonicconstant.h"
#include "include/EditionComponents/editiontable.h"
#include "include/model_view/tidaltabledelegate.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QApplication>
#include <QFile>
#include <QDataStream>
#include <QMessageBox>
#include <QTextStream>

/*void FreqEditor::saveFile()
{
    this->writeFile(m_filePath);
    this->close();
}*/

void FreqEditor::setfilePath(const QString &filePath)
{
    if (filePath == m_filePath) return;

    m_filePath = filePath;

    emit filePathChanged(m_filePath);
}

bool FreqEditor::insertRow()
{
    return m_frequencyModel->insertRow(m_frequencyModel->rowCount(QModelIndex()),QModelIndex());
}

FreqEditor::FreqEditor(const QString &filePath, QWidget *parent):QDialog(parent),m_filePath(filePath)
{
    m_frequencyModel = new HarmonicConstantFrequencyTableModel;

    m_frequencyTable = new EditionTable;
    m_frequencyTable->setModel(m_frequencyModel);
    m_frequencyTable->setItemDelegate(new HarmonicConstantFrequencyTableDelegate(this));

    this->readFile(filePath);

    m_frequencyTable->setColumnWidth(1,150);
    m_frequencyTable->setColumnWidth(2,400);

    createButtons();

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(m_addButton);
    rightLayout->addWidget(m_removeButton);
    rightLayout->addStretch();
    rightLayout->addWidget(m_okButton);
    rightLayout->addWidget(m_cancelButton);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(m_frequencyTable);
    mainLayout->addLayout(rightLayout);

    this->setLayout(mainLayout);

    this->setWindowTitle(tr("Editor de Componentes de Marea"));
    this->setFixedSize(QSize(800,500));  //Fija el tamano del widget
    this->setModal(true);

    this->setAttribute(Qt::WA_DeleteOnClose);
}

void FreqEditor::createButtons()
{
    m_okButton = new QPushButton(QIcon(":images/Ok.png"),tr("Aceptar"),this);
    connect(m_okButton,SIGNAL(clicked(bool)),this,SIGNAL(acceptButtonClicked()));


    m_cancelButton = new QPushButton(QIcon(":images/No.png"),tr("Cancelar"),this);
    connect(m_cancelButton,SIGNAL(clicked(bool)),this,SLOT(close()));

    m_addButton = new QPushButton(QIcon(":images/add.png"),tr("Agregar"),this);
    m_addButton->setToolTip(tr("Agregar fila"));
    connect(m_addButton,SIGNAL(clicked(bool)),this,SLOT(insertRow()));

    m_removeButton = new QPushButton(QIcon(":images/delete.png"),tr("Eliminar"),this);
    m_removeButton->setToolTip(tr("Eliminar filas"));
    connect(m_removeButton,SIGNAL(clicked(bool)),m_frequencyTable,SLOT(removeRows()));
}

bool FreqEditor::readFile(const QString &filePath)
{

    QFile file(filePath);

    if (file.open(QIODevice::ReadOnly)){
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_5_7);

        qint32 number;

        QApplication::setOverrideCursor(Qt::WaitCursor);

        in >> number;

        if (number != MagicNumber){
            QMessageBox::information(this,tr("Error al leer archivo"),tr("El archivo %1 no tiene el formato requerido.").arg(file.fileName()));
            return false;
        }

        qint16 rowNumber;
        //qint16 columnNumber;

        in >> rowNumber;

        QVector<HarmonicConstant> datos;


        QString name;
        double frequency;
        QString description;

        for (int i = 0; i < rowNumber; ++i){
            in >> name >> frequency >> description;
            datos.push_back(HarmonicConstant(name,frequency,description));
        }

        m_frequencyModel->setAllData(datos);

        QApplication::restoreOverrideCursor();

        return true;
    }

    QMessageBox::information(this,tr("Error al leer archivo"),tr("No se puede leer el archivo %1:\n%2.")
                             .arg(file.fileName().arg(file.errorString())));

    return false;
}

/*bool FreqEditor::writeFile(const QString &filePath)
{
    QFile file(filePath);

    if (file.open(QIODevice::WriteOnly)){
       QDataStream out(&file);
       out.setVersion(QDataStream::Qt_5_7);

       QApplication::setOverrideCursor(Qt::WaitCursor);

       out << qint32(MagicNumber);

       out << qint16(m_frequencyModel->rowCount(QModelIndex()));

       foreach (HarmonicConstant harmonicConstant, m_frequencyModel->allData()) {
           out << harmonicConstant.name() << (double)harmonicConstant.frequency() << harmonicConstant.description();
       }

       QApplication::restoreOverrideCursor();

    }else{
        QMessageBox::warning(this,tr("Error al escribir archivo"),
                             tr("No se puede escribir el archivo %1:\n%2.")
                             .arg(file.fileName().arg(file.errorString())));

        return false;
    }

    return true;
}*/
