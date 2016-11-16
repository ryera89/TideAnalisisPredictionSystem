#include "projectmetadata.h"


ProjectMetaData::ProjectMetaData()
{
    m_projectName = QString();
    m_stationName = QString();
    m_localizationName = QString();
    m_ceroPuesto = 0.0;
    m_nivelReferencia = 0.0;
    m_latitud = 0.0;
    m_longitud = 0.0;
    m_equipmentId = QString();

    displayZeroUnits = MeasurementUnitEditWidget::M;
    displayReferenceUnits = MeasurementUnitEditWidget::M;
}

void ProjectMetaData::setCeroUnits(MeasurementUnitEditWidget::Units ceroUnits)
{
    displayZeroUnits = ceroUnits;
}

void ProjectMetaData::setReferenceUnits(MeasurementUnitEditWidget::Units referenceUnits)
{
    displayReferenceUnits = referenceUnits;
}
