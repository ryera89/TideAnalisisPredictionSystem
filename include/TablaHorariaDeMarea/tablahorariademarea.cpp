#include "tablahorariademarea.h"

#include <QTableWidgetItem>
#include <QHeaderView>

void TablaHorariaDeMarea::createTable(const TidalData &m_data)
{
    this->clear();

    this->setRowCount(m_data.m_measurementDates.size()+4);
    this->setColumnCount(m_data.m_measurementTimes.size() + 6);

    this->horizontalHeader()->hide();

    this->setSpan(0,0,2,1);
    this->setSpan(0,1,1,m_data.m_measurementTimes.size());
    this->setSpan(0,m_data.m_measurementTimes.size() + 1,2,1);
    this->setSpan(0,m_data.m_measurementTimes.size() + 2,2,1);
    this->setSpan(0,m_data.m_measurementTimes.size() + 3,1,2);
    this->setSpan(0,m_data.m_measurementTimes.size() + 5,2,1);

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
    item->setTextAlignment(Qt::AlignCenter);
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    this->setItem(0,0,item);

    QTableWidgetItem *item1 = new QTableWidgetItem;
    item1->setData(Qt::DisplayRole,hora);
    item1->setBackgroundColor(Qt::lightGray);
    item1->setTextAlignment(Qt::AlignCenter);
    item1->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    this->setItem(0,1,item1);

    QTableWidgetItem *item2 = new QTableWidgetItem;
    item2->setData(Qt::DisplayRole,suma);
    item2->setBackgroundColor(Qt::lightGray);
    item2->setTextAlignment(Qt::AlignCenter);
    item2->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    this->setItem(0,m_data.m_measurementTimes.size() + 1,item2);

    QTableWidgetItem *item3 = new QTableWidgetItem;
    item3->setData(Qt::DisplayRole,nivel_medio);
    item3->setBackgroundColor(Qt::lightGray);
    item3->setTextAlignment(Qt::AlignCenter);
    item3->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    this->setItem(0,m_data.m_measurementTimes.size() + 2,item3);

    QTableWidgetItem *item4 = new QTableWidgetItem;
    item4->setData(Qt::DisplayRole,extremos);
    item4->setBackgroundColor(Qt::lightGray);
    item4->setTextAlignment(Qt::AlignCenter);
    item4->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    this->setItem(0,m_data.m_measurementTimes.size() + 3,item4);

    QTableWidgetItem *item5 = new QTableWidgetItem;
    item5->setData(Qt::DisplayRole,diff);
    item5->setBackgroundColor(Qt::lightGray);
    item5->setTextAlignment(Qt::AlignCenter);
    item5->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    this->setItem(0,m_data.m_measurementTimes.size() + 5,item5);

    QTableWidgetItem *item6 = new QTableWidgetItem;
    item6->setData(Qt::DisplayRole,max);
    item6->setBackgroundColor(Qt::lightGray);
    item6->setTextAlignment(Qt::AlignCenter);
    item6->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    this->setItem(1,m_data.m_measurementTimes.size() + 3,item6);

    QTableWidgetItem *item7 = new QTableWidgetItem;
    item7->setData(Qt::DisplayRole,min);
    item7->setBackgroundColor(Qt::lightGray);
    item7->setTextAlignment(Qt::AlignCenter);
    item7->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    this->setItem(1,m_data.m_measurementTimes.size() + 4,item7);

    QTableWidgetItem *item8 = new QTableWidgetItem;
    item8->setData(Qt::DisplayRole,suma);
    item8->setBackgroundColor(Qt::lightGray);
    item8->setTextAlignment(Qt::AlignCenter);
    item8->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    this->setItem(this->rowCount() - 2,0,item8);

    QTableWidgetItem *item9 = new QTableWidgetItem;
    item9->setData(Qt::DisplayRole,promedio);
    item9->setBackgroundColor(Qt::lightGray);
    item9->setTextAlignment(Qt::AlignCenter);
    item9->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    this->setItem(this->rowCount() - 1,0,item9);

}

void TablaHorariaDeMarea::populateTable(const TidalData &m_data)
{
    for (int i = 0; i < m_data.m_measurementDates.size(); ++i){
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setData(Qt::DisplayRole, m_data.m_measurementDates[i]);
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        this->setItem(i+2,0,item);

        item = new QTableWidgetItem;
        item->setData(Qt::DisplayRole,m_data.m_dateSums.value(m_data.m_measurementDates[i]));
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        this->setItem(i+2,columnCount() - 5,item);

        item = new QTableWidgetItem;
        item->setData(Qt::DisplayRole,m_data.m_meanSeaLevel.value(m_data.m_measurementDates[i]));
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        this->setItem(i+2,columnCount() - 4,item);

        item = new QTableWidgetItem;
        item->setData(Qt::DisplayRole,m_data.m_extremes.value(m_data.m_measurementDates[i]).x());
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        this->setItem(i+2,columnCount() - 3,item);

        item = new QTableWidgetItem;
        item->setData(Qt::DisplayRole,m_data.m_extremes.value(m_data.m_measurementDates[i]).y());
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        this->setItem(i+2,columnCount() - 2,item);

        item = new QTableWidgetItem;
        item->setData(Qt::DisplayRole,m_data.m_differences.value(m_data.m_measurementDates[i]));
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        this->setItem(i+2,columnCount() - 1,item);

    }
    for (int i = 0; i < m_data.m_measurementTimes.size(); ++i){
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(m_data.m_measurementTimes.at(i).toString("hh:mm:ss"));   //setData(Qt::DisplayRole, m_data.m_measurements[i].measurementTime());
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        this->setItem(1,i+1,item);
    }

    int count = 0; //Contador para llenar la tabla correctamente

    //TODO: Arreglar esto de aqui
    for (int i = 0; i < m_data.m_measurementDates.size(); ++i){
        int kprima = 0;
        for (int j = 0; j < m_data.m_measurementNumberPerDay.value(m_data.m_measurementDates[i]); ++j){
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setData(Qt::DisplayRole, m_data.m_measurements[j + count].seaLevel());
            item->setTextAlignment(Qt::AlignCenter);
            item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            for (int k = kprima; k < m_data.m_measurementTimes.size(); ++k){ //Para poner el valor del nivel en la celda correcta
                if (m_data.m_measurements.at(j + count).measurementTime() == m_data.m_measurementTimes.at(k)){
                    this->setItem(i+2,k+1,item);
                    kprima = k+1;
                    break;
                }else{  //Pone un item vacio en la celda que no tenga mediciones
                    QTableWidgetItem *item = new QTableWidgetItem;
                    item->setData(Qt::DisplayRole, QVariant());
                    item->setTextAlignment(Qt::AlignCenter);
                    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                    this->setItem(i+2,k+1,item);
                }
            }
            if ((kprima-1) < (m_data.m_measurementTimes.size()-1) && j == (m_data.m_measurementNumberPerDay.value(m_data.m_measurementDates[i])-1)){
                for (int t = kprima; t < m_data.m_measurementTimes.size();++t){
                    QTableWidgetItem *item = new QTableWidgetItem;
                    item->setData(Qt::DisplayRole, QVariant());
                    item->setTextAlignment(Qt::AlignCenter);
                    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                    this->setItem(i+2,t+1,item);
                }
            }
        }

        /*if (m_data.m_measurementNumberPerDay.value(m_data.m_measurementDates[i])
                < m_data.maxMeasurementNumberPerDay){
            for (int j = m_data.
                 m_measurementNumberPerDay.value(m_data.m_measurementDates[i]);
                 j < m_data.maxMeasurementNumberPerDay; ++j){

                QTableWidgetItem *item = new QTableWidgetItem;
                item->setData(Qt::DisplayRole, QVariant());
                item->setTextAlignment(Qt::AlignCenter);
                item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                this->setItem(i+2,j+1,item);

            }
        }*/

        count += m_data.m_measurementNumberPerDay.value(m_data.m_measurementDates[i]);
    }

    for (int column = 1; column < columnCount(); ++column){
        double suma = 0.0;
        int counter = 0;
        for (int row = 2; row < m_data.m_measurementDates.size() + 2; ++row){
           bool ok;
           double number = this->item(row,column)->data(Qt::DisplayRole).toDouble(&ok);
           if (ok) ++counter;
           suma += number;
        }
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setData(Qt::DisplayRole, suma);
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        this->setItem(rowCount() - 2,column,item);

        double promedio = suma/counter;
        QTableWidgetItem *item1 = new QTableWidgetItem;
        item1->setData(Qt::DisplayRole, promedio);
        item1->setTextAlignment(Qt::AlignCenter);
        item1->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        this->setItem(rowCount() - 1,column,item1);
    }

    for (int column = 1; column < columnCount() - 5; ++column){
        setColumnWidth(column,55);
    }

    setColumnWidth(0,70);

    for (int column = columnCount() - 1; column >= columnCount() - 5; --column){
        setColumnWidth(column,70);
    }


}



void TablaHorariaDeMarea::loadData(const TidalData &m_data)
{
    createTable(m_data);
    populateTable(m_data);

}
