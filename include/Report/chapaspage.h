#ifndef CHAPASPAGE_H
#define CHAPASPAGE_H

#include <QWizardPage>

class QGroupBox;
class QPlainTextEdit;

class ChapasPage : public QWizardPage
{
    Q_OBJECT
public:
    ChapasPage(QWidget *parent = 0);

    QString descripcionChapaPartida() const;
    QString descripcionChapaPrincipal() const;
    QString descripcionChapaTrabajo() const;

private:
    QGroupBox *m_descrChapaPartidaGroupBox;
    QGroupBox *m_descrChapaPrincipalGroupBox;
    QGroupBox *m_descrChapaTrabajoGroupBox;


    QPlainTextEdit *m_descrChapaPartidaTextEdit;
    QPlainTextEdit *m_descrChapaPrincipalTextEdit;
    QPlainTextEdit *m_descrChapaTrabajoTextEdit;

};

#endif // CHAPASPAGE_H
