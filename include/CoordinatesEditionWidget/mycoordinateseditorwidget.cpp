#include "mycoordinateseditorwidget.h"
#include <QHBoxLayout>
#include <QDoubleValidator>
#include <iostream>

MyCoordinatesEditorWidget::MyCoordinatesEditorWidget(QWidget *parent)
    : QFrame(parent)
{
    m_coordinate = 0.0;
    m_hType = latitud;
    m_type = 0;

    m_HemisphereComboBox = new QComboBox(this);
    m_HemisphereComboBox->addItem("N");
    m_HemisphereComboBox->addItem("S");
    m_HemisphereComboBox->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);

    m_coordinatesSpinBox = new QDoubleSpinBox(this);
    //m_HemisphereComboBox->setFrame(false);
    //m_coordinatesLineEdit->setFrame(false);
    m_coordinatesSpinBox->setRange(0.0,90.0);
    m_coordinatesSpinBox->setDecimals(3);
    m_coordinatesSpinBox->setSuffix("°");

    QHBoxLayout *editLayout = new QHBoxLayout;
    editLayout->addWidget(m_coordinatesSpinBox);
    editLayout->addWidget(m_HemisphereComboBox);
    editLayout->setSpacing(0);

    //this->setFrameStyle(QFrame::Box | QFrame::Raised);
    this->setLayout(editLayout);
    this->layout()->setMargin(0);


    connect(m_HemisphereComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(setHemisphere(int)));
    connect(m_coordinatesSpinBox,SIGNAL(valueChanged(double)),this,SLOT(setCoordinate(double)));
    connect(this,SIGNAL(hTypeChanged(HemisphereType)),this,SLOT(setHemisphereComboBoxItems(HemisphereType)));

}
MyCoordinatesEditorWidget::~MyCoordinatesEditorWidget()
{

}
void MyCoordinatesEditorWidget::setEditorAndComboValue(double value)
{
    double val = qAbs(value);
    m_coordinatesSpinBox->setValue(val);
    if (value < 0.0){
        m_HemisphereComboBox->setCurrentIndex(1);

    }else{
        m_HemisphereComboBox->setCurrentIndex(0);
    }
}

void MyCoordinatesEditorWidget::setHemisphere(int hemis){
    double value = qAbs(m_coordinate);
    if (!hemis){
        if (m_coordinate == value) return;
        m_coordinate = value;
    }else{
        value*=-1;
        if (m_coordinate == value) return;
        m_coordinate = value;
    }

    emit coordinateChanged(value);

}
double MyCoordinatesEditorWidget::coordinate() const
{
    return m_coordinate;
}

MyCoordinatesEditorWidget::HemisphereType MyCoordinatesEditorWidget::hType() const
{
    return m_hType;
}

void MyCoordinatesEditorWidget::setCoordinate(double coordinate)
{
    double value = qAbs(coordinate);
    if (!m_HemisphereComboBox->currentIndex()){
        if (m_coordinate == value) return;
        m_coordinate = value;
        emit coordinateChanged(value);
    }else{
        value*=-1;
        if (m_coordinate == value) return;
        m_coordinate = value;
        emit coordinateChanged(value);
    }

}

void MyCoordinatesEditorWidget::setHType(MyCoordinatesEditorWidget::HemisphereType hType)
{
    if (m_hType == hType)
        return;

    m_hType = hType;
    emit hTypeChanged(hType);
}

void MyCoordinatesEditorWidget::setHemisphereComboBoxItems(MyCoordinatesEditorWidget::HemisphereType hType)
{
    if (hType == latitud){
        m_HemisphereComboBox->clear();
        m_HemisphereComboBox->addItem("N");
        m_HemisphereComboBox->addItem("S");
        m_coordinatesSpinBox->setRange(0.0,90.0);
    }else{
        m_HemisphereComboBox->clear();
        m_HemisphereComboBox->addItem("E");
        m_HemisphereComboBox->addItem("W");
        m_coordinatesSpinBox->setRange(0.0,180.0);
    }

}
