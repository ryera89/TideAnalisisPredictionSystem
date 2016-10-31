#include "tidalschemeselectionwidget.h"

#include <QVBoxLayout>
#include <QScrollArea>
#include <QTextEdit>
#include <QDataStream>
#include <QFile>
#include <QApplication>
#include <QMessageBox>
#include <QGroupBox>
#include <QComboBox>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QSignalMapper>

TidalSchemeSelectionWidget::TidalSchemeSelectionWidget(const QStringList &componentLabels, QWidget *parent):QWidget(parent)
{
    //m_componentGroupBox = new QGroupBox(tr("Componentes de Marea"),this);

    /*QFont font = m_componentGroupBox->font();
    font.setPixelSize(12);
    m_componentGroupBox->setFont(font);*/

    QWidget *myWidget = new QWidget;
    createComponentsCheckBoxes(componentLabels); //Aqui se crean los checkboxes de los componentes
    myWidget->setLayout(m_checkBoxLayout);

    QScrollArea *scrollArea =  new QScrollArea;
    scrollArea->setWidget(myWidget);
    scrollArea->setWidgetResizable(true);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout->addWidget(scrollArea);

    //m_componentGroupBox->setLayout(mainLayout);

    //QHBoxLayout *lay =  new QHBoxLayout;

    //lay->addWidget(m_componentGroupBox);

    this->setLayout(mainLayout);
}

void TidalSchemeSelectionWidget::setCheckBoxesEnabledStatus(bool enable)
{
    foreach (QCheckBox *checkBoxPointer, m_componentsCheckBoxes) {
        checkBoxPointer->setEnabled(enable);
    }
}

void TidalSchemeSelectionWidget::setCheckBoxesStatus(const QMap<QString, bool> &componentStatusMap)
{
    foreach (QCheckBox *checkBoxPointer, m_componentsCheckBoxes) {
        if (componentStatusMap.contains(checkBoxPointer->text())){
            checkBoxPointer->setChecked(componentStatusMap.value(checkBoxPointer->text()));
        }else{
            checkBoxPointer->setChecked(false);
        }
    }

}

void TidalSchemeSelectionWidget::changingCheckBoxStatus(int i)
{
    QString label = m_componentsCheckBoxes.at(i)->text();
    bool status = m_componentsCheckBoxes.at(i)->isChecked();

    emit checkBoxStatusChanged(label,status);
}

/*bool TidalSchemeSelectionWidget::readFile(const QString &filePath)
{
    QFile file(filePath);

    if (file.open(QIODevice::ReadOnly)){
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_5_6);

        qint32 number;

        QApplication::setOverrideCursor(Qt::WaitCursor);

        in >> number;

        if (number != 0x7F51C883) return false;

        qint16 rowNumber;
        qint16 columnNumber;

        QStringList headerList;
        QString headerLabel;

        in >> rowNumber >> columnNumber;

        for (int i = 0; i < columnNumber; ++i){
            in >> headerLabel;
            headerList.push_back(headerLabel);
        }
        //freqTable->setUpTable(rowNumber,columnNumber, headerList);
        QStringList labels;
        for (int i = 0; i < rowNumber; ++i){  //NOTE: Ver si lo puedo implementar con QVariant
            for (int j = 0; j < columnNumber; ++j){
               QString str;
               in >> str;                        //WARNING: may be a bug
               if (j == 0) labels.push_back(str);
            }
        }

        //loadComponents(labels); //ESto es para crear los checkboxes.

        QApplication::restoreOverrideCursor();

        return true;
    }

    QMessageBox::information(this,tr("Marea"),tr("No se puede leer el archivo %1:\n%2.")
                             .arg(file.fileName().arg(file.errorString())));

    return false;
}*/

void TidalSchemeSelectionWidget::createComponentsCheckBoxes(const QStringList &labels) //Aqui se crean los checkboxes del los componenetes
{
    m_checkBoxLayout = new QVBoxLayout;  //Layout que contine a los richTextCheckBoxes

    QSignalMapper *mapper = new QSignalMapper(this);


    foreach (QString str, labels) {
        QCheckBox *componentCheckBoxes =  new QCheckBox;   //NOTE: aqui se puede cambiar por richtextcheck box si lo decido despues
        componentCheckBoxes->setText(str);      //componentCheckBoxes->Label()->setText(QString('A'+ i) + "<sub>a</sub>");   //font size='5'
        m_componentsCheckBoxes.push_back(componentCheckBoxes);
        mapper->setMapping(componentCheckBoxes,m_componentsCheckBoxes.size() - 1);
        m_checkBoxLayout->addWidget(componentCheckBoxes);
        connect(componentCheckBoxes,SIGNAL(clicked(bool)),mapper,SLOT(map()));
    }
    connect(mapper,SIGNAL(mapped(int)),this,SLOT(changingCheckBoxStatus(int)));
}
