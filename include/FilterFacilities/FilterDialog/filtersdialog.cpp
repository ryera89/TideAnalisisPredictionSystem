#include "filtersdialog.h"

#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QFrame>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QGroupBox>
#include <QProgressBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QPlainTextEdit>
#include <iostream>

FiltersDialog::FiltersDialog(const QVector<TidesMeasurement> &data, QWidget *parent):
    QDialog(parent), m_data(data)
{
    setAttribute(Qt::WA_DeleteOnClose);

    Qt::WindowFlags flags = Qt::Dialog | Qt::WindowCloseButtonHint;
    this->setWindowFlags(flags);

    setWindowTitle(tr("Filtros"));
    setModal(true);

    //m_checkBoxesLayout = new QVBoxLayout;

    m_criteria = Filters::LESS;

    //m_mapper = new QSignalMapper(this);

    m_filterPushButton = new QPushButton(tr("Filtrar"));
    connect(m_filterPushButton,SIGNAL(clicked(bool)),this,SLOT(applyFilter()));

    m_deleteDataPushButton = new QPushButton(tr("Eliminar"));
    m_deleteDataPushButton->setDisabled(true);
    m_deleteDataPushButton->setToolTip(tr("Eliminar los datos seleccionados"));

    m_okPushButton = new QPushButton(QIcon(":images/Ok.png"),tr("Aceptar"));
    m_okPushButton->setDisabled(true);
    connect(m_okPushButton,SIGNAL(clicked(bool)),this, SIGNAL(accepted()));

    m_cancelPushButton = new QPushButton(QIcon(":images/No.png"),tr("Cancelar"));
    connect(m_cancelPushButton,SIGNAL(clicked(bool)),this,SLOT(close()));

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(m_filterPushButton);
    buttonLayout->addWidget(m_deleteDataPushButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_okPushButton);
    buttonLayout->addWidget(m_cancelPushButton);

    m_byGlitchRadioButton = new QRadioButton(tr("Glitch"));
    m_byGlitchRadioButton->setChecked(true);
    m_byValueRadioButton = new QRadioButton(tr("Valor"));
    m_byBlockRadioButton = new QRadioButton(tr("Bloque"));

    m_glithSpinBox = new QDoubleSpinBox;
    m_glithSpinBox->setValue(4.0);
    m_glithSpinBox->setDecimals(3);
    m_glithSpinBox->setSuffix("m/h");

    m_valueSpinBox = new QDoubleSpinBox;
    m_valueSpinBox->setDecimals(3);
    m_valueSpinBox->setRange(INT32_MIN,INT32_MAX);
    m_valueSpinBox->setSuffix("m");

    m_blockSpinBox = new QSpinBox;
    m_blockSpinBox->setRange(2,UINT16_MAX);

    m_glitchInfoLabel = new QLabel(tr("Pendiente entre Puntos Consecutivos, Limite Superior"));

    m_blockInfoLabel = new QLabel(tr("Mínimo de Puntos Adyacentes de Igual Nivel"));

    m_criteriaSelectionComboBox = new QComboBox;
    m_criteriaSelectionComboBox->addItem(tr("Menor"));
    m_criteriaSelectionComboBox->addItem(tr("Igual"));
    m_criteriaSelectionComboBox->addItem(tr("Mayor"));
    m_criteriaSelectionComboBox->addItem(tr("Menor o Igual"));
    m_criteriaSelectionComboBox->addItem(tr("Mayor o Igual"));
    connect(m_criteriaSelectionComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(setCriteria(int)));

    QGridLayout *filtersLayout = new QGridLayout;
    filtersLayout->addWidget(m_byGlitchRadioButton,0,0,1,1);
    filtersLayout->addWidget(m_byValueRadioButton,1,0,1,1);
    filtersLayout->addWidget(m_byBlockRadioButton,2,0,1,1);
    filtersLayout->addWidget(m_glithSpinBox,0,1,1,1);
    filtersLayout->addWidget(m_valueSpinBox,1,1,1,1);
    filtersLayout->addWidget(m_blockSpinBox,2,1,1,1);
    filtersLayout->addWidget(m_glitchInfoLabel,0,2,1,2);
    filtersLayout->addWidget(m_criteriaSelectionComboBox,1,2,1,1);
    filtersLayout->addWidget(m_blockInfoLabel,2,2,1,2);

    m_filterGroupBox = new QGroupBox(tr("Filtros"));
    m_filterGroupBox->setLayout(filtersLayout);

    m_resultEdit = new QPlainTextEdit;
    m_resultEdit->setReadOnly(true);
    //QFrame *containerFrame = new QFrame;

    //m_resultsFrame = new QFrame;
    //m_resultsFrame->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    //m_resultsFrame->setFixedHeight(300);
    //m_resultsFrame->setLayout(m_checkBoxesLayout);

    //QScrollArea *scrollArea =  new QScrollArea;
    //scrollArea->setWidget(m_resultsFrame);
    //scrollArea->setWidgetResizable(true);

    //QVBoxLayout *scrollLayout = new QVBoxLayout;
    //scrollLayout->addWidget(scrollArea);

    //m_resultsFrame->setLayout(m_checkBoxesLayout);

    //containerFrame->setLayout(m_checkBoxesLayout);

    //m_selectAllCheckBox = new QCheckBox(tr("Seleccionar Todos"));
    //m_selectAllCheckBox->setDisabled(true);

    //QHBoxLayout *selectAllLayout = new QHBoxLayout;
    //selectAllLayout->addWidget(m_selectAllCheckBox);
    //selectAllLayout->addStretch();

    //QVBoxLayout *resultsLayout = new QVBoxLayout;
    //resultsLayout->addWidget(m_resultsFrame);
    //resultsLayout->addLayout(scrollLayout);
    //resultsLayout->addLayout(selectAllLayout);
    //resultsLayout->setSpacing(0);

    m_progressBar = new QProgressBar;
    m_progressBar->setTextVisible(true);
    connect(&m_filter,SIGNAL(filterProgress(int)),m_progressBar,SLOT(setValue(int)));

    m_opInfoLabel = new QLabel(tr("Datos de Entrada <b><font color = green>%1</b></font>.").arg(m_data.size()));
    m_opInfoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    connect(&m_filter,SIGNAL(matchesFound(int)),this,SLOT(updateInfoLabel(int)));

    QVBoxLayout *progressInfoLayout = new QVBoxLayout;
    progressInfoLayout->addWidget(m_progressBar);
    progressInfoLayout->addWidget(m_opInfoLabel);
    progressInfoLayout->setSpacing(0);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(m_filterGroupBox);
    leftLayout->addWidget(m_resultEdit);
    leftLayout->addLayout(progressInfoLayout);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

void FiltersDialog::updateInfoLabel(int matches)
{
    m_opInfoLabel->setText(tr("Datos de Entrada <b><font color = green>%1</b></font>. ").arg(m_data.size()) + tr("Datos de Encontrados para Eliminación <b><font color = red>%1</b></font>.").arg(matches));
}

void FiltersDialog::applyFilter()
{
    m_resultEdit->clear();
    m_matchedDataPos.clear();

    if (m_byGlitchRadioButton->isChecked()){
        m_progressBar->setMaximum(m_data.size()-2);
        qreal glitch = m_glithSpinBox->value();
        m_matchedDataPos = m_filter.glitchFilter(glitch,m_data);
    }
    if (m_byValueRadioButton->isChecked()){
        m_progressBar->setMaximum(m_data.size()-1);
        qreal value = m_valueSpinBox->value();
        m_matchedDataPos = m_filter.valueFilter(value,m_data,m_criteria);
    }
    if (m_byBlockRadioButton->isChecked()){
        m_progressBar->setMaximum(m_data.size()-1);
        int number = m_blockSpinBox->value();
        m_matchedDataPos = m_filter.blocksFilter(number,m_data);
    }

    displayResults();
}

void FiltersDialog::setCriteria(int index)
{
    switch (index) {
    case 0:
        m_criteria = Filters::LESS;
        break;
    case 1:
        m_criteria = Filters::EQUAL;
        break;
    case 2:
        m_criteria = Filters::GREATER;
        break;
    case 3:
        m_criteria = Filters::LESS_EQUAL;
        break;
    case 4:
        m_criteria = Filters::GREATER_EQUAL;
        break;
    default:
        break;
    }
}

void FiltersDialog::displayResults()
{
    QString text;
    for (int i = 0; i < m_matchedDataPos.size(); ++i){
        text = (tr("%1 ").arg(m_matchedDataPos.at(i)+1) +
                        tr("%1 ").arg(m_data.at(m_matchedDataPos.at(i)).measurementDateTime().toString("dd/MM/yyyy hh:mm"))
                        + tr("%1").arg(m_data.at(m_matchedDataPos.at(i)).seaLevel()) + "m");

        m_resultEdit->appendPlainText(text);
    }
}


/*void FiltersDialog::setDataForElimination(int index)
{
    m_resultsCheckBoxesStatusMap[index] = !m_resultsCheckBoxesStatusMap[index];

    std::cout << index <<" " << m_resultsCheckBoxesStatusMap[index] <<std::endl;
}*/

/*void FiltersDialog::createChechBoxesResult()
{
    for (int i = 0; i < m_resultsCheckBoxes.size(); ++i){
        m_mapper->removeMappings(m_resultsCheckBoxes[i]);
        disconnect(m_resultsCheckBoxes[i],SIGNAL(stateChanged(int)),m_mapper,SLOT(map()));
        m_checkBoxesLayout->removeWidget(m_resultsCheckBoxes[i]);
        delete m_resultsCheckBoxes[i];
    }

    m_resultsCheckBoxes.clear();
    m_resultsCheckBoxesStatusMap.clear();
    disconnect(m_mapper,SIGNAL(mapped(int)),this,SLOT(setDataForElimination(int)));
    //m_resultsFrame->update();

    for (int i = 0; i < m_matchedDataPos.size(); ++i){
        m_resultsCheckBoxesStatusMap[m_matchedDataPos.at(i)] = false;
        QCheckBox *checkBox = new QCheckBox(tr("%1 ").arg(m_matchedDataPos.at(i)+1) +
                                            tr("%1 ").arg(m_data.at(m_matchedDataPos.at(i)).measurementDateTime().toString("dd/MM/yyyy hh:mm"))
                                            + tr("%1").arg(m_data.at(m_matchedDataPos.at(i)).seaLevel()) + "m");


        m_checkBoxesLayout->addWidget(checkBox);
        m_resultsCheckBoxes.push_back(checkBox);
        m_mapper->setMapping(checkBox,m_matchedDataPos.at(i));
        connect(checkBox,SIGNAL(stateChanged(int)),m_mapper,SLOT(map()));
    }
    if (m_matchedDataPos.size() > 0){
        connect(m_mapper,SIGNAL(mapped(int)),this,SLOT(setDataForElimination(int)));
    }


    //m_resultsFrame->setLayout(m_checkBoxesLayout);


}*/
