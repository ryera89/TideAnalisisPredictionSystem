#include "myheader.h"

#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <QMouseEvent>

MyHeader::MyHeader(Qt::Orientation orientation, QWidget *parent):QHeaderView(orientation,parent)
{
    this->setSectionsClickable(true);
    createContextMenu();
}

void MyHeader::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event);
    m_contextMenu->exec(QCursor::pos());
}

void MyHeader::mousePressEvent(QMouseEvent *event)
{
    if (!event) return;

    if (event->button() == Qt::RightButton){
        int index = logicalIndexAt(event->pos());
        emit sectionPressed(index);
    }else{
        QHeaderView::mousePressEvent(event);
    }
}

void MyHeader::createContextMenu()
{
    m_contextMenu = new QMenu;

    m_removeRowAction = new QAction(QIcon(":images/Remove.png"),tr("Eliminar fila"));
    m_insertRowAction = new QAction(QIcon(":images/Add.png"),tr("Insertar fila"));
    connect(m_removeRowAction,SIGNAL(triggered(bool)),this,SIGNAL(removeRowActionTriggered(bool)));

    m_contextMenu->addAction(m_insertRowAction);
    m_contextMenu->addAction(m_removeRowAction);
    connect(m_insertRowAction,SIGNAL(triggered(bool)),this,SIGNAL(insertRowActionTriggered(bool)));
}
