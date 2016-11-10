#ifndef PROJECTMETADATA_H
#define PROJECTMETADATA_H

#include <QString>

class ProjectMetaData
{
public:
    ProjectMetaData(){}
    ProjectMetaData(const QString &projectName, const QString &stationName, const QString &localizationName,
                    const double &latitud, const double &longitud, const QString &equipmentId):m_projectName(projectName),
        m_stationName(stationName),m_localizationName(localizationName),m_latitud(latitud),m_longitud(longitud),m_equipmentId(equipmentId){}

    QString projectName() const {return m_projectName;}
    QString stationName() const {return m_stationName;}
    QString localizationName() const {return m_localizationName;}
    double latitud() const {return m_latitud;}
    double longitud() const {return m_longitud;}
    QString equipmentID() const {return m_equipmentId;}

    void setProjectName(const QString &str){m_projectName = str;}
    void setStationName(const QString &str){m_stationName = str;}
    void setLocalizationName(const QString &str){m_localizationName = str;}
    void setLatitud(double latitud){m_latitud = latitud;}
    void setLongitud(double longitud){m_longitud = longitud;}
    void setEquipmentID(const QString &str){m_equipmentId = str;}
    
private:
    QString m_projectName;
    QString m_stationName;
    QString m_localizationName;
    double m_latitud;
    double m_longitud;
    QString m_equipmentId;
};

#endif // PROJECTMETADATA_H
