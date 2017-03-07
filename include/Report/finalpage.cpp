#include "finalpage.h"

#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QFormLayout>
#include <QVBoxLayout>

FinalPage::FinalPage(QWidget *parent):QWizardPage(parent)
{
    setTitle(tr("Responsables"));

    m_procesoApellidosLabel = new QLabel(tr("Apellidos:"));
    m_procesoNombreLabel = new QLabel(tr("Nombre:"));
    m_procesoDptoLabel = new QLabel(tr("Departamento:"));
    m_revisoApellidosLabel = new QLabel(tr("Apellidos:"));
    m_revisoNombreLabel = new QLabel(tr("Nombre:"));
    m_revisoDptoLabel = new QLabel(tr("Departamento:"));

    m_procesoApellidosEdit = new QLineEdit;
    m_procesoApellidosEdit->setPlaceholderText(tr("Apellidos"));
    m_procesoNombreEdit = new QLineEdit;
    m_procesoNombreEdit->setPlaceholderText(tr("Nombre"));
    m_procesoDptoEdit = new QLineEdit;
    m_procesoDptoEdit->setPlaceholderText(tr("Departamento"));
    m_revisoApellidosEdit = new QLineEdit;
    m_revisoApellidosEdit->setPlaceholderText(tr("Apellidos"));
    m_revisoNombreEdit = new QLineEdit;
    m_revisoNombreEdit->setPlaceholderText(tr("Nombre"));
    m_revisoDptoEdit = new QLineEdit;
    m_revisoDptoEdit->setPlaceholderText(tr("Departamento"));

    m_procesoGroupBox = new QGroupBox(tr("Procesó"));
    m_revisoGroupBox = new QGroupBox(tr("Revisó"));


    QFormLayout *layout1 = new QFormLayout;
    layout1->addRow(m_procesoApellidosLabel,m_procesoApellidosEdit);
    layout1->addRow(m_procesoNombreLabel,m_procesoNombreEdit);
    layout1->addRow(m_procesoDptoLabel,m_procesoDptoEdit);

    QFormLayout *layout2 = new QFormLayout;
    layout2->addRow(m_revisoApellidosLabel,m_revisoApellidosEdit);
    layout2->addRow(m_revisoNombreLabel,m_revisoNombreEdit);
    layout2->addRow(m_revisoDptoLabel,m_revisoDptoEdit);

    m_procesoGroupBox->setLayout(layout1);
    m_revisoGroupBox->setLayout(layout2);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_procesoGroupBox);
    layout->addWidget(m_revisoGroupBox);

    setLayout(layout);
}

QString FinalPage::procesoNombre() const
{
    return m_procesoNombreEdit->text() + " " + m_procesoApellidosEdit->text();
}

QString FinalPage::procesoDpto() const
{
    return m_procesoDptoEdit->text();
}

QString FinalPage::revisoNombre() const
{
    return m_revisoNombreEdit->text() + " " + m_revisoApellidosEdit->text();
}

QString FinalPage::revisoDpto() const
{
    return m_revisoDptoEdit->text();
}

QString FinalPage::proceso() const
{
    return m_procesoGroupBox->title() + ":";
}

QString FinalPage::reviso() const
{
    return m_revisoGroupBox->title() + ":";
}
