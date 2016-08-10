#ifndef SPMMAINWINDOW_H
#define SPMMAINWINDOW_H

#include <QMainWindow>

#include <QMenuBar>

#include "centralwidget.h"
#include "include/loadDialog/loaddialog.h"


class SPMmainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit SPMmainWindow(QWidget *parent = 0);

signals:

public slots:
    void loadDataFile();

protected slots:
    //void gettingData(const QVector<QStringList> &data, int dateField, int timeField, int heightField);

private:

     CentralWidget *m_central;
     LoadDialog *m_loadDialog;


     /*************************ACTIONS*************************************************/
     //File Menu Actions
     QAction *m_newProjectAction;
     QAction *m_loadProjectAction;
     QAction *m_saveProjectAction;
     QAction *m_saveAsProjectAction;

     //QAction *m_importFrom_CVS_Action;
     QAction *m_importFrom_ASCII_Action;
     //QAction *m_importAction;
     //QAction *m_exportAction;
     QAction *m_exitAction;


     /***********************************************************************************/


     /************************MENUS******************************************************/
     QMenu *m_fileMenu;
     //QMenu *m_importSubMenu;

     /***********************************************************************************/
    //NOTE: va el widget especial que contiene el chart

    //NOTE: van las acciones que se ejecutan en el programa.


     void createActions();
     void createMenus();

};

#endif // SPMMAINWINDOW_H
