#include "conclusionpage.h"

#include <QLabel>
#include <QVBoxLayout>

ConclusionPage::ConclusionPage(QWidget *parent):QWizardPage(parent)
{
    setTitle(tr("Conclusión"));

    m_conclusionLabel = new QLabel(tr("Presione finalizar para generar el "
                                      "formulario del puesto de nivel."));

    m_conclusionLabel->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_conclusionLabel);

    setLayout(layout);

    setPixmap(QWizard::WatermarkPixmap,QPixmap(":/images/watermark.jpg"));
}
