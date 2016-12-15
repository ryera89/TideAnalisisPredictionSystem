#include "filter_facilities.h"

QVector<int> Filters::glitchFilter(qreal glitchValue, const QVector<TidesMeasurement> &data)
{
   if (data.isEmpty()) return QVector<int>();//Si la data esta vacia retorna un vector vacio

   QVector<int> glichPosVector;
   int totalGlitchFounds = 0;
   for (int i = 0; i < data.size()-1;++i){
       TidesMeasurement currentMeasurement = data.at(i);
       TidesMeasurement nextMeasurement = data.at(i+1);

       qreal delta_y = nextMeasurement.seaLevel() - currentMeasurement.seaLevel();

       qreal delta_x = currentMeasurement.measurementDateTime().secsTo(nextMeasurement.measurementDateTime()); //intervalo de tiempo en horas
       delta_x/=3600;

       qreal slope = delta_y/delta_x;

       if (qFabs(slope) >= glitchValue){
           glichPosVector.push_back(i+1);
           ++totalGlitchFounds;
           emit matchesFound(totalGlitchFounds,i+2,data.at(i+1));
       }
       emit filterProgress(i);

   }
   return glichPosVector;
}

QVector<int> Filters::blocksFilter(int flag, const QVector<TidesMeasurement> &data)
{
    if (data.isEmpty()) return QVector<int>();
    if (data.size() == 1) return QVector<int>();

    QVector<int> blocks;

    QVector<int> counter(1,0);

    qreal compValue = data.at(0).seaLevel();

    for (int i  = 1; i < data.size(); ++i){
        qreal currValue = data.at(i).seaLevel();
        if (currValue != compValue){
            compValue = currValue;
            if (counter.size() >= flag){
                blocks.append(counter);
                emit matchesFoundForBlockFilter(blocks.size(),counter);
            }
            counter.clear();
            counter.push_back(i);
        }else{
            counter.push_back(i);
        }
        emit filterProgress(i);
    }
    if (counter.size() >= flag){
        blocks.append(counter);
        emit matchesFoundForBlockFilter(blocks.size(),counter);
    }
    return blocks;
}

QVector<int> Filters::valueFilter(qreal value, const QVector<TidesMeasurement> &data, Filters::ByValue criteria)
{
    QVector<int> matchesPos;
    switch (criteria) {
    case LESS:{
        for (int i = 0; i < data.size(); ++i){
            if (data.at(i).seaLevel() < value){
                matchesPos.push_back(i);
                emit matchesFound(matchesPos.size(),i+1,data.at(i));
            }
            emit filterProgress(i);
        }
        break;
    }
    case EQUAL:{
        for (int i = 0; i < data.size(); ++i){
            if (data.at(i).seaLevel() == value){
                matchesPos.push_back(i);
               emit matchesFound(matchesPos.size(),i+1,data.at(i));
            }
            emit filterProgress(i);
        }
        break;
    }
    case GREATER:{
        for (int i = 0; i < data.size(); ++i){
            if (data.at(i).seaLevel() > value){
                matchesPos.push_back(i);
               emit matchesFound(matchesPos.size(),i+1,data.at(i));
            }
            emit filterProgress(i);
        }
        break;
    }
    case LESS_EQUAL:{
        for (int i = 0; i < data.size(); ++i){
            if (data.at(i).seaLevel() <= value){
                matchesPos.push_back(i);
                emit matchesFound(matchesPos.size(),i+1,data.at(i));
            }
            emit filterProgress(i);
        }
        break;
    }
    case GREATER_EQUAL:{
        for (int i = 0; i < data.size(); ++i){
            if (data.at(i).seaLevel() >= value){
                matchesPos.push_back(i);
                emit matchesFound(matchesPos.size(),i+1,data.at(i));
            }
            emit filterProgress(i);
        }
        break;
    }
    default:
        break;
    }

    return matchesPos;
}

