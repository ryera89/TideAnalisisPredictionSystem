#-------------------------------------------------
#
# Project created by QtCreator 2016-08-09T13:10:02
#
#-------------------------------------------------

QT       += core gui charts qml quick positioning quickwidgets concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TideAnalisisPredictionSystem
TEMPLATE = app


SOURCES += main.cpp\
    include/loadDialog/linenumbereditor.cpp \
    include/loadDialog/loaddialog.cpp \
    include/mainComponents/centralwidget.cpp \
    include/mainComponents/spmchart.cpp \
    include/mainComponents/spmmainwindow.cpp \
    include/maths/common_math_algorithms.cpp \
    include/maths/fft.cpp \
    include/maths/gauss_jordan.cpp \
    include/maths/ludcmp.cpp \
    include/maths/math_function_utils.cpp \
    include/maths/matrix.cpp \
    include/maths/minsqr.cpp \
    include/maths/numericalvector.cpp \
    include/maths/slice_iter.cpp \
    include/maths/statisticalfacilities.cpp \
    include/maths/tridiagonal.cpp \
    include/measurement/measurement.cpp \
    include/model_view/tablemodel.cpp \
    include/model_view/tidaltabledelegate.cpp \
    include/ChartModelMapper/xytidalchartmodelmapper.cpp \
    include/mainComponents/customchartview.cpp \
    include/measurement/tidaldata.cpp \
    include/mainComponents/customtableview.cpp \
    include/model_view/readonlytablemodel.cpp \
    include/model_view/hourlytidaltablemodel.cpp \
    include/TablaHorariaDeMarea/tablahorariademarea.cpp \
    include/TablaHorariaDeMarea/tablahorariawidget.cpp \
    include/EditionComponents/editiontable.cpp \
    include/EditionComponents/manualdataintroductionwidget.cpp \
    include/ProjectMetaData/metadatadialog.cpp \
    include/ProjectMetaData/metadatawidget.cpp \
    include/ProjectMetaData/projectmetadata.cpp \
    include/HarmonicConstantsModule/Model_View/mylistmodeldelegate.cpp \
    include/HarmonicConstantsModule/Model_View/mylistview.cpp \
    include/HarmonicConstantsModule/SchemeConfigDialog/schemeconfigdialog.cpp \
    include/HarmonicConstantsModule/schemewidget.cpp \
    include/HarmonicConstantsModule/tidalschemeselectionwidget.cpp \
    mainwindow.cpp \
    include/HarmonicConstantsModule/HarmonicConstantClass/harmonicconstant.cpp \
    include/HarmonicConstantsModule/Model_View/harmonicconstantfrequencytablemodel.cpp \
    include/HarmonicConstantsModule/Model_View/harmonicconstantfrequencytabledelegate.cpp \
    include/HarmonicConstantsModule/FrequencyEditor/freqeditor.cpp \
    include/EditionComponents/myheader.cpp \
    include/HarmonicConstantsModule/Model_View/harmonicconstantfulltablemodel.cpp \
    include/maths/minimoscuadradosbookcopy.cpp \
    include/maths/svd.cpp \
    include/mainComponents/displayeddatalabels.cpp \
    include/NonHarmonicConstantsModule/NonHarmonicConstants/hpm.cpp \
    include/NonHarmonicConstantsModule/NonHarmonicConstants/duracionvaciante.cpp \
    include/NonHarmonicConstantsModule/NonHarmonicConstants/duracionllenante.cpp \
    include/NonHarmonicConstantsModule/NonHarmonicConstants/crecimientomareasemidiurna.cpp \
    include/NonHarmonicConstantsModule/NonHarmonicConstants/crecimientomareaparactica.cpp \
    include/NonHarmonicConstantsModule/NonHarmonicConstants/creciemientomareadiurna.cpp \
    include/NonHarmonicConstantsModule/NonHarmonicConstants/alturapromediomarea.cpp \
    include/NonHarmonicConstantsModule/NonHarmonicConstants/alturasemimarea.cpp \
    include/NonHarmonicConstantsModule/NonHarmonicConstants/pleabajamedia.cpp \
    include/NonHarmonicConstantsModule/NonHarmonicConstants/semidiurnalrelation.cpp \
    include/NonHarmonicConstantsModule/NonHarmonicConstants/amplitudrelation.cpp \
    include/NonHarmonicConstantsModule/NonHarmonicConstants/horapuesto.cpp \
    include/NonHarmonicConstantsModule/NonHarmonicConstants/horacotidianasemidiurna.cpp \
    include/NonHarmonicConstantsModule/NonHarmonicConstants/horacotidianadiurna.cpp \
    include/CoordinatesEditionWidget/mycoordinateseditorwidget.cpp \
    include/mainComponents/mychart.cpp \
    include/NonHarmonicConstantsModule/FrontEnd/displayresultwidget.cpp \
    include/NonHarmonicConstantsModule/FrontEnd/nonharmoninccalcdialog.cpp \
    include/MeasurementUnitEditWidget/measurementuniteditwidget.cpp \
    include/SelectionRangeLabel/selectionrangelabel.cpp \
    include/NivelacionAcuatica/nivelacion_acuatica_calculo.cpp \
    include/NivelacionAcuatica/Model_View_Delegate/nivelacionacuaticatablemodel.cpp \
    include/NivelacionAcuatica/NivelacionAcuaticaWidget/nivelacionacuaticawidget.cpp \
    include/SamplingDialog/samplingdialog.cpp \
    include/FilterFacilities/FilterFunctions/filter_facilities.cpp \
    include/FilterFacilities/FilterDialog/filtersdialog.cpp

HEADERS  += \
    include/loadDialog/linenumbereditor.h \
    include/loadDialog/loaddialog.h \
    include/mainComponents/centralwidget.h \
    include/mainComponents/spmchart.h \
    include/mainComponents/spmmainwindow.h \
    include/maths/common_math_algorithms.h \
    include/maths/fft.h \
    include/maths/gauss_jordan.h \
    include/maths/ludcmp.h \
    include/maths/math_function_utils.h \
    include/maths/matrix.h \
    include/maths/minsqr.h \
    include/maths/numericalvector.h \
    include/maths/slice_iter.h \
    include/maths/statisticalfacilities.h \
    include/maths/tridiagonal.h \
    include/measurement/measurement.h \
    include/model_view/tablemodel.h \
    include/model_view/tidaltabledelegate.h \
    include/ChartModelMapper/xytidalchartmodelmapper.h \
    include/mainComponents/customchartview.h \
    include/measurement/tidaldata.h \
    include/mainComponents/customtableview.h \
    include/model_view/readonlytablemodel.h \
    include/model_view/hourlytidaltablemodel.h \
    include/TablaHorariaDeMarea/tablahorariademarea.h \
    include/TablaHorariaDeMarea/tablahorariawidget.h \
    include/EditionComponents/editiontable.h \
    include/EditionComponents/manualdataintroductionwidget.h \
    include/ProjectMetaData/metadatawidget.h \
    include/ProjectMetaData/metadatadialog.h \
    include/ProjectMetaData/projectmetadata.h \
    include/HarmonicConstantsModule/Model_View/mylistmodeldelegate.h \
    include/HarmonicConstantsModule/Model_View/mylistview.h \
    include/HarmonicConstantsModule/SchemeConfigDialog/schemeconfigdialog.h \
    include/HarmonicConstantsModule/schemewidget.h \
    include/HarmonicConstantsModule/tidalschemeselectionwidget.h \
    mainwindow.h \
    include/HarmonicConstantsModule/HarmonicConstantClass/harmonicconstant.h \
    include/HarmonicConstantsModule/Model_View/harmonicconstantfrequencytablemodel.h \
    include/HarmonicConstantsModule/Model_View/harmonicconstantfrequencytabledelegate.h \
    include/HarmonicConstantsModule/FrequencyEditor/freqeditor.h \
    include/EditionComponents/myheader.h \
    include/HarmonicConstantsModule/Model_View/harmonicconstantfulltablemodel.h \
    include/maths/minimoscuadradosbookcopy.h \
    include/maths/svd.h \
    include/maths/fitsvd.h \
    include/mainComponents/displayeddatalabels.h \
    include/NonHarmonicConstantsModule/NonHarmonicConstants/hpm.h \
    include/NonHarmonicConstantsModule/NonHarmonicConstants/duracionvaciante.h \
    include/NonHarmonicConstantsModule/NonHarmonicConstants/duracionllenante.h \
    include/NonHarmonicConstantsModule/NonHarmonicConstants/crecimientomareasemidiurna.h \
    include/NonHarmonicConstantsModule/NonHarmonicConstants/crecimientomareaparactica.h \
    include/NonHarmonicConstantsModule/NonHarmonicConstants/creciemientomareadiurna.h \
    include/NonHarmonicConstantsModule/NonHarmonicConstants/alturapromediomarea.h \
    include/NonHarmonicConstantsModule/NonHarmonicConstants/alturasemimarea.h \
    include/NonHarmonicConstantsModule/NonHarmonicConstants/pleabajamedia.h \
    include/NonHarmonicConstantsModule/NonHarmonicConstants/semidiurnalrelation.h \
    include/NonHarmonicConstantsModule/NonHarmonicConstants/amplitudrelation.h \
    include/NonHarmonicConstantsModule/NonHarmonicConstants/horapuesto.h \
    include/NonHarmonicConstantsModule/NonHarmonicConstants/horacotidianasemidiurna.h \
    include/NonHarmonicConstantsModule/NonHarmonicConstants/horacotidianadiurna.h \
    include/CoordinatesEditionWidget/mycoordinateseditorwidget.h \
    include/mainComponents/mychart.h \
    include/NonHarmonicConstantsModule/FrontEnd/displayresultwidget.h \
    include/NonHarmonicConstantsModule/FrontEnd/nonharmoninccalcdialog.h \
    include/MeasurementUnitEditWidget/measurementuniteditwidget.h \
    include/SelectionRangeLabel/selectionrangelabel.h \
    include/NivelacionAcuatica/nivelacion_acuatica_calculo.h \
    include/NivelacionAcuatica/Model_View_Delegate/nivelacionacuaticatablemodel.h \
    include/NivelacionAcuatica/NivelacionAcuaticaWidget/nivelacionacuaticawidget.h \
    include/SamplingDialog/samplingdialog.h \
    include/FilterFacilities/FilterFunctions/filter_facilities.h \
    include/FilterFacilities/FilterDialog/filtersdialog.h

RC_ICONS = aquarius-48.ico

RESOURCES += \
    images.qrc

DISTFILES += \
    TideAnalisisPredictionSystem.pro.aV1876 \
    images/add.png \
    images/analisis.png \
    images/configure.png \
    images/erase.png \
    Processing.qml \
    analizing.qml \
    images/supercargando.gif
