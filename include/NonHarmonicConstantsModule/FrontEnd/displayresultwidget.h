#ifndef DISPLAYRESULTWIDGET_H
#define DISPLAYRESULTWIDGET_H

#include <QGroupBox>

class QLineEdit;
class QPushButton;

class displayResultWidget : public QGroupBox
{
    Q_OBJECT
public:
    explicit displayResultWidget(QWidget *parent = Q_NULLPTR);
    explicit displayResultWidget(const QString &title, QWidget *parent = Q_NULLPTR);

    void setLineEditText(const QString &text);
    void setPushButtonStatus(bool status);

    bool pushButtonStatus() const;

signals:
    void pushButtonClicked();

private:
    QGroupBox *m_groupBox;
    QLineEdit *m_lineEdit;
    QPushButton *m_pushButton;

    void createComponets();
    void setIntefaceLayout();
};

#endif // DISPLAYRESULTWIDGET_H
