#include "displayresultwidget.h"
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

displayResultWidget::displayResultWidget(QWidget *parent):QGroupBox(parent)
{
    createComponets();
    setIntefaceLayout();
}

displayResultWidget::displayResultWidget(const QString &title, QWidget *parent):QGroupBox(title,parent)
{
    createComponets();
    setIntefaceLayout();
}
void displayResultWidget::setLineEditText(const QString &text)
{
    m_lineEdit->setText(text);
}

void displayResultWidget::setPushButtonStatus(bool status)
{
    m_pushButton->setEnabled(status);
}

bool displayResultWidget::pushButtonStatus() const
{
    return m_pushButton->isEnabled();
}

QString displayResultWidget::lineEditText() const
{
    return m_lineEdit->text();
}

/*QString displayResultWidget::groupBoxText() const
{
    return m_groupBox->title();
}*/
void displayResultWidget::createComponets()
{
    m_lineEdit = new QLineEdit;
    m_lineEdit->setReadOnly(true);

    m_pushButton = new QPushButton(tr("Calcular"));
    connect(m_pushButton,SIGNAL(clicked(bool)),this,SIGNAL(pushButtonClicked()));
}

void displayResultWidget::setIntefaceLayout()
{
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(m_lineEdit);
    mainLayout->addWidget(m_pushButton);
    mainLayout->setSpacing(0);
    this->setLayout(mainLayout);
}
