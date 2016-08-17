#ifndef SPMMAINWINDOW_H
#define SPMMAINWINDOW_H

#include <QMainWindow>

#include <QMenuBar>

#include "centralwidget.h"
#include "include/loadDialog/loaddialog.h"
#include "include/TablaHorariaDeMarea/tablahorariawidget.h"
#include "include/measurement/tidaldata.h"


class SPMmainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit SPMmainWindow(QWidget *parent = 0);

    TidalData* datosDeMarea() const{return m_datosDeMarea;}
    QAbstractTableModel* model()const{return m_tidalTableModel;}

signals:

public slots:
    void loadDataFile();
    void crearTablaHoraria();

    void recieveData(const QVector<QStringList> &data, int dateField, int timeField,
                     int heightField, const QString &dateFormat, const QString &timeFormat);

protected slots:
    //void gettingData(const QVector<QStringList> &data, int dateField, int timeField, int heightField);

private:

     CentralWidget *m_central;
     LoadDialog *m_loadDialog;
     TablaHorariaWidget *m_tablaHorariaWidget;



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

     //View Actions-----------------------------------------------------------------------

     QAction *m_tablaHorariadeMareaAction;


     /***********************************************************************************/


     /************************MENUS******************************************************/
     QMenu *m_fileMenu;
     QMenu *m_viewMenu;
     //QMenu *m_importSubMenu;

     /***********************************************************************************/
    //NOTE: va el widget especial que contiene el chart

    //NOTE: van las acciones que se ejecutan en el programa.


     void createActions();
     void createMenus();

     //DOnde se almacenan los datos
     TidalData *m_datosDeMarea;
     ReadOnlyTableModel *m_tidalTableModel;

};

#endif // SPMMAINWINDOW_H
