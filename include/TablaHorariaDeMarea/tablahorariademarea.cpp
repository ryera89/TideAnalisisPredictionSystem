#include "tablahorariademarea.h"

#include <QTableWidgetItem>
#include <QHeaderView>

void TablaHorariaDeMarea::createTable(TidalData *m_data)
{
    this->setRowCount(m_data->m_measurementDates.size()+4);
    this->setColumnCount(m_data->maxMeasurementNumberPerDay + 6);

    this->horizontalHeader()->hide();

    this->setSpan(0,0,1,0);
    this->setSpan(0,1,0,m_data->maxMeasurementNumberPerDay);
    this->setSpan(0,m_data->maxMeasurementNumberPerDay + 1,1,0);
    this->setSpan(0,m_data->maxMeasurementNumberPerDay + 2,1,0);
    this->setSpan(0,m_data->maxMeasurementNumberPerDay + 3,0,2);
    this->setSpan(0,m_data->maxMeasurementNumberPerDay + 5,1,0);

    const QString fecha = "FECHA";
    const QString hora = "HORA";
    const QString suma = "SUMA";
    const QString promedio = "PROM";
    const QString nivel_medio = "NIVEL MEDIO";
    const QString extremos = "EXTREMOS";
    const QString max = "MAX";
    const QString min = "MIN";
    const QString diff = "DIFERENCIA";


    QTableWidgetItem *item = new QTableWidgetItem;
    item->setData(Qt::DisplayRole,fecha);
    item->setBackgroundColor(Qt::lightGray);
    this->setItem(0,0,item);

    QTableWidgetItem *item1 = new QTableWidgetItem;
    item1->setData(Qt::DisplayRole,hora);
    item1->setBackgroundColor(Qt::lightGray);
    this->setItem(0,1,item1);

    QTableWidgetItem *item2 = new QTableWidgetItem;
    item2->setData(Qt::DisplayRole,suma);
    item2->setBackgroundColor(Qt::lightGray);
    this->setItem(0,m_data->maxMeasurementNumberPerDay + 1,item2);

    QTableWidgetItem *item3 = new QTableWidgetItem;
    item3->setData(Qt::DisplayRole,nivel_medio);
    item3->setBackgroundColor(Qt::lightGray);
    this->setItem(0,m_data->maxMeasurementNumberPerDay + 2,item3);

    QTableWidgetItem *item4 = new QTableWidgetItem;
    item4->setData(Qt::DisplayRole,extremos);
    item4->setBackgroundColor(Qt::lightGray);
    this->setItem(0,m_data->maxMeasurementNumberPerDay + 3,item4);

    QTableWidgetItem *item5 = new QTableWidgetItem;
    item5->setData(Qt::DisplayRole,diff);
    item5->setBackgroundColor(Qt::lightGray);
    this->setItem(0,m_data->maxMeasurementNumberPerDay + 5,item5);

    QTableWidgetItem *item6 = new QTableWidgetItem;
    item6->setData(Qt::DisplayRole,max);
    item6->setBackgroundColor(Qt::lightGray);
    this->setItem(1,m_data->maxMeasurementNumberPerDay + 3,item6);

    QTableWidgetItem *item7 = new QTableWidgetItem;
    item7->setData(Qt::DisplayRole,min);
    item7->setBackgroundColor(Qt::lightGray);
    this->setItem(1,m_data->maxMeasurementNumberPerDay + 4,item7);

    QTableWidgetItem *item8 = new QTableWidgetItem;
    item8->setData(Qt::DisplayRole,suma);
    item8->setBackgroundColor(Qt::lightGray);
    this->setItem(this->columnCount() - 2,0,item8);

    QTableWidgetItem *item9 = new QTableWidgetItem;
    item9->setData(Qt::DisplayRole,promedio);
    item9->setBackgroundColor(Qt::lightGray);
    this->setItem(this->columnCount() - 1,0,item9);

}

void TablaHorariaDeMarea::populateTable(TidalData *m_data)
{
    for (int i = 0; i < m_data->m_measurementDates.size(); ++i){
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setData(Qt::DisplayRole, m_data->m_measurementDates[i]);
        item->setTextAlignment(Qt::AlignCenter);
        this->setItem(i+2,0,item);

        item = new QTableWidgetItem;
        item->setData(Qt::DisplayRole,m_data->m_dateSums.value(m_data->m_measurementDates[i]));
        item->setTextAlignment(Qt::AlignCenter);
        this->setItem(i+2,columnCount() - 5,item);

        item = new QTableWidgetItem;
        item->setData(Qt::DisplayRole,m_data->m_meanSeaLevel.value(m_data->m_measurementDates[i]));
        item->setTextAlignment(Qt::AlignCenter);
        this->setItem(i+2,columnCount() - 4,item);

        item = new QTableWidgetItem;
        item->setData(Qt::DisplayRole,m_data->m_extremes.value(m_data->m_measurementDates[i]).x());
        item->setTextAlignment(Qt::AlignCenter);
        this->setItem(i+2,columnCount() - 3,item);

        item = new QTableWidgetItem;
        item->setData(Qt::DisplayRole,m_data->m_extremes.value(m_data->m_measurementDates[i]).y());
        item->setTextAlignment(Qt::AlignCenter);
        this->setItem(i+2,columnCount() - 2,item);

        item = new QTableWidgetItem;
        item->setData(Qt::DisplayRole,m_data->m_differences.value(m_data->m_measurementDates[i]));
        item->setTextAlignment(Qt::AlignCenter);
        this->setItem(i+2,columnCount() - 1,item);

    }

    //WARNING Esto para datos muestrados a la misma hora todos los dias
    for (int i = 0; i < m_data->maxMeasurementNumberPerDay; ++i){
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setData(Qt::DisplayRole, m_data->m_measurements[i].measurementTime());
        item->setTextAlignment(Qt::AlignCenter);
        this->setItem(1,i+1,item);
    }

    int count = 0; //Contador para llenar la tabla correctamente

    for (int i = 0; i < m_data->m_measurementDates.size(); ++i){
        for (int j = 0; m_data->m_measurementNumberPerDay.value(m_data->m_measurementDates[i]); ++j){
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setData(Qt::DisplayRole, m_data->m_measurements[j + count].seaLevel());
            item->setTextAlignment(Qt::AlignCenter);
            this->setItem(i,j,item);
        }
        count += m_data->m_measurementNumberPerDay.value(m_data->m_measurementDates[i]);
    }

    //NOTE: falta las dos ultimas filas


}



void TablaHorariaDeMarea::loadData(TidalData *m_data)
{
    if (m_data){
        createTable(m_data);
        populateTable(m_data);
    }
}
