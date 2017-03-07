#include "intropage.h"
#include <QLabel>
#include <QVBoxLayout>

IntroPage::IntroPage(QWidget *parent):QWizardPage(parent)
{
    setTitle(tr("Introducción"));

    m_label = new QLabel(tr("Este asistente lo guiara durante el proceso de creación"
                            " del formulario del puesto de nivel. Siga las"
                            " instrucciones y llene los campos de información requeridos."));
    m_label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_label);

    setLayout(layout);

    setPixmap(QWizard::WatermarkPixmap,QPixmap(":/images/watermark.jpg"));

}
