#ifndef PROJECTMETADATA_H
#define PROJECTMETADATA_H

#include <QString>

class ProjectMetaData
{
public:
    ProjectMetaData(){}
    ProjectMetaData(const QString &projectName, const QString &stationName, const QString &localizationName,
                    const QString &latitud, const QString &longitud, const QString &equipmentId):m_projectName(projectName),
        m_stationName(stationName),m_localizationName(localizationName),m_latitud(latitud),m_longitud(longitud),m_equipmentId(equipmentId){}

    QString projectName() const {return m_projectName;}
    QString stationName() const {return m_stationName;}
    QString localizationName() const {return m_localizationName;}
    QString latitud() const {return m_latitud;}
    QString longitud() const {return m_longitud;}
    QString equipmentID() const {return m_equipmentId;}

    void setProjectName(const QString &str){m_projectName = str;}
    void setStationName(const QString &str){m_stationName = str;}
    void setLocalizationName(const QString &str){m_localizationName = str;}
    void setLatitud(const QString &str){m_latitud = str;}
    void setLongitud(const QString &str){m_longitud = str;}
    void setEquipmentID(const QString &str){m_equipmentId = str;}
    
private:
    QString m_projectName;
    QString m_stationName;
    QString m_localizationName;
    QString m_latitud;
    QString m_longitud;
    QString m_equipmentId;
};

#endif // PROJECTMETADATA_H
