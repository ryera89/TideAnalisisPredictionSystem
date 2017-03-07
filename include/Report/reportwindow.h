#ifndef REPORTWINDOW_H
#define REPORTWINDOW_H

#include <QMainWindow>
#include <QTextEdit>

class QAction;
class QMenu;

class ReportWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ReportWindow(QWidget *parent = 0);
    virtual void setPageSize();
    QTextEdit* reportEdit() const{return m_reportEdit;}


signals:

public slots:
    virtual void print();
    virtual void printPDF();

private:
    QAction *m_printAction;
    QAction *m_printAsPdfAction;

    QMenu *m_printMenu;


    QTextEdit *m_reportEdit;

};

#endif // REPORTWINDOW_H
