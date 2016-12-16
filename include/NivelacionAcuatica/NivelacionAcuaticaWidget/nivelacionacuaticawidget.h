#ifndef NIVELACIONACUATICAWIDGET_H
#define NIVELACIONACUATICAWIDGET_H

#include <QWidget>
#include "include/MeasurementUnitEditWidget/measurementuniteditwidget.h"
#include "include/CoordinatesEditionWidget/mycoordinateseditorwidget.h"
#include "include/NivelacionAcuatica/Model_View_Delegate/nivelacionacuaticatablemodel.h"
#include "include/mainComponents/customchartview.h"
#include "include/loadDialog/loaddialog.h"
#include "include/EditionComponents/manualdataintroductionwidget.h"

class QGroupBox;
class QFrame;
class QLabel;
class QToolButton;
class QTableView;
class QPushButton;

class NivelacionAcuaticaWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NivelacionAcuaticaWidget(const QVector<TidesMeasurement> &data, QWidget *parent = 0);

signals:

public slots:

private slots:
    void createProvDataLoadDialog();
    void createPerm1DataLoadDialog();
    void createPerm2DataLoadDialog();
    void createProvManualDataIntro();
    void createPerm1ManualDataIntro();
    void createPerm2ManualDataIntro();

    void importProvDataFromMain();
    void importPerm1DataFromMain();
    void importPerm2DataFromMain();
    //void loadProvDataFromMainProject();
    //void loadProvDataFromMainProject();
    //void loadProvDataFromMainProject();

    void beginDataExtrationFromFile();
    void appendDataFromFile();
    void beginDataExtration();
    void appendDataFromManual();
    void importDataFromMainForm();

    void setMetodoDeNivelacion(int index);

    void calculate();

private:
    //Import Dialog && Manual Data Introduction Widget
    LoadDialog *m_loadDialog;
    ManualDataIntroductionWidget *m_manualDataIntroWidget;

    //Chart stuff
    QFrame *m_chartFrame;
    customChartView *m_chartView;
    QChart *m_chart;
    QSplineSeries *m_puestoProvSerie;
    QSplineSeries *m_puestoPerm1Serie;
    QSplineSeries *m_puestoPerm2Serie;
    QLineSeries *m_nivelMedioLineSerie;

    QValueAxis *m_puestoProvYAxis;
    QValueAxis *m_puestoPerm1YAxis;
    QValueAxis *m_puestoPerm2YAxis;

    QDateTimeAxis *m_dateTimeXAxis;

    //Table View-Model
    QTableView *m_dataTableView;
    NivelacionAcuaticaTableModel *m_dataTableModel;

    //Group Boxes
    QGroupBox *m_metodoGroupBox;
    QGroupBox *m_cargaDeDatosGroupBox;
    QGroupBox *m_puestoProvMetaDataGroupBox;
    QGroupBox *m_puestoPerm1MetaDataGroupBox;
    QGroupBox *m_puestoPerm2MetaDataGroupBox;

    //Combo Box
    QComboBox *m_metodoComboBox;

    //Labels
    QLabel *m_puestoProvDataLoadLabel;
    QLabel *m_puestoPerm1DataLoadLabel;
    QLabel *m_puestoPerm2DataLoadLabel;

    QLabel *m_puestoProvStationLabel;
    QLabel *m_puestoProvLocationLabel;
    QLabel *m_puestoProvLatitudLabel;
    QLabel *m_puestoProvLongitudLabel;
    QLabel *m_puestoProvNMMLabel;

    QLabel *m_puestoPerm1StationLabel;
    QLabel *m_puestoPerm1LocationLabel;
    QLabel *m_puestoPerm1LatitudLabel;
    QLabel *m_puestoPerm1LongitudLabel;
    QLabel *m_puestoPerm1NMMLabel;

    QLabel *m_puestoPerm2StationLabel;
    QLabel *m_puestoPerm2LocationLabel;
    QLabel *m_puestoPerm2LatitudLabel;
    QLabel *m_puestoPerm2LongitudLabel;
    QLabel *m_puestoPerm2NMMLabel;

    //QFrames
    QFrame *m_puestoProvDataLoadFrame;
    QFrame *m_puestoPerm1DataLoadFrame;
    QFrame *m_puestoPerm2DataLoadFrame;

    //Tools Buttons
    QToolButton *m_puestoProvImportButton;
    QToolButton *m_puestoProvManualButton;
    QToolButton *m_puestoProvGetButton;

    QToolButton *m_puestoPerm1ImportButton;
    QToolButton *m_puestoPerm1ManualButton;
    QToolButton *m_puestoPerm1GetButton;

    QToolButton *m_puestoPerm2ImportButton;
    QToolButton *m_puestoPerm2ManualButton;
    QToolButton *m_puestoPerm2GetButton;

    //Coordinates Widget
    MyCoordinatesEditorWidget *m_puestoProvLatitudEdit;
    MyCoordinatesEditorWidget *m_puestoProvLongitudEdit;

    MyCoordinatesEditorWidget *m_puestoPerm1LatitudEdit;
    MyCoordinatesEditorWidget *m_puestoPerm1LongitudEdit;

    MyCoordinatesEditorWidget *m_puestoPerm2LatitudEdit;
    MyCoordinatesEditorWidget *m_puestoPerm2LongitudEdit;

    //Measurement Unit
    MeasurementUnitEditWidget *m_puestoPerm1NMMEdit;
    MeasurementUnitEditWidget *m_puestoPerm2NMMEdit;

    //Especial Label
    QLabel *m_puestoProvNMMDisplayResult;

    //QLineEdits
    QLineEdit *m_puestoProvStationEdit;
    QLineEdit *m_puestoProvLocationEdit;

    QLineEdit *m_puestoPerm1StationEdit;
    QLineEdit *m_puestoPerm1LocationEdit;

    QLineEdit *m_puestoPerm2StationEdit;
    QLineEdit *m_puestoPerm2LocationEdit;

    //PushButtons
    QPushButton *m_calcNMMButton;

    QVector<TidesMeasurement> m_mainFormData;

    bool m_provDataLoadFlag;
    bool m_perm1DataLoadFlag;
    bool m_perm2DataLoadFlag;

    void createComponents();

    void setPuestoProvAxis();
    void setPuestoPerm1Axis();
    void setPuestoPerm2Axis();

    void setPuestoProvXAxis();
    void setPuestoPerm1XAxis();
    void setPuestoPerm2XAxis();

    void createLoadDialog();
    void createManualDataIntroWidget();

    void calculateMetodoDeUnPuestoPermanente();
    void calculateMetodoDeDosPuestosPermanentes();
};

#endif // NIVELACIONACUATICAWIDGET_H
