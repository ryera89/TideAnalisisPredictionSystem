#include "reportwizard.h"

#include "reportwindow.h"
#include <QTextTable>

ReportWizard::ReportWizard(QWidget *parent):QWizard(parent,Qt::WindowCloseButtonHint)
{

    m_introPage = new IntroPage;
    m_metadataPage = new MetadataPage;
    m_generalidadesPage = new GeneralidadesPage;
    m_chapasReferenciasPage = new ChapasPage;
    m_ceroProfundidadPage = new CeroProfPage;
    m_responsablesPage = new FinalPage;
    m_conclusionPage = new ConclusionPage;

    addPage(m_introPage);
    addPage(m_metadataPage);
    addPage(m_generalidadesPage);
    addPage(m_chapasReferenciasPage);
    addPage(m_ceroProfundidadPage);
    addPage(m_responsablesPage);
    addPage(m_conclusionPage);

    setWizardStyle(QWizard::ModernStyle);

    setButtonText(QWizard::BackButton, tr("< Anterior"));
    setButtonText(QWizard::NextButton, tr("Siguiente >"));
    setButtonText(QWizard::FinishButton, tr("Finalizar"));

    setWindowIcon(QIcon(":images/Wizard.png"));
    setWindowTitle(tr("Asistente de reporte"));
    setAttribute(Qt::WA_DeleteOnClose);
}

void ReportWizard::setHarmonicConstants(const QVector<HarmonicConstant> &hcVector)
{
    m_hcVector = hcVector;
}

void ReportWizard::setMetaData(const ProjectMetaData &metadata)
{
    m_metadataPage->setMetaData(metadata);
}

void ReportWizard::setMeasurementsPeriod(const QDate &begin, const QDate &end)
{
    m_metadataPage->setMeasurementsPeriod(begin,end);
}

void ReportWizard::accept()
{
    ReportWindow *reportWindow = new ReportWindow;
    reportWindow->setWindowIcon(QIcon(":images/report-icon.png"));
    reportWindow->setWindowTitle(tr("Formulario del Puesto de Nivel"));
    reportWindow->setPageSize();


    QFont font = reportWindow->reportEdit()->font();
    font.setFamily("Courier New");
    //font.setPointSize(12);

    reportWindow->reportEdit()->setFont(font);

    QTextCursor cursor = reportWindow->reportEdit()->textCursor();

    //QTextFrame *headerFrame = cursor.currentFrame();

    QTextCharFormat titleCharFormat;
    titleCharFormat.setFontWeight(QFont::Bold);
    titleCharFormat.setFontPointSize(14);

    QTextCharFormat headerCharFormat;
    headerCharFormat.setFontWeight(QFont::Bold);
    headerCharFormat.setFontPointSize(12);

    QTextCharFormat boldCharFormat;
    boldCharFormat.setFontWeight(QFont::Bold);
    boldCharFormat.setFontPointSize(10);

    QTextCharFormat normalCharFormat;
    normalCharFormat.setFontWeight(QFont::Normal);
    normalCharFormat.setFontPointSize(10);

    QTextBlockFormat titleBlockFormat;
    titleBlockFormat.setAlignment(Qt::AlignHCenter);

    QTextBlockFormat headerBlockFormat;
    headerBlockFormat.setLeftMargin(6);

    QTextBlockFormat textBlockFormat;
    textBlockFormat.setLeftMargin(24);

    QTextBlockFormat subTextBlockFormat;
    subTextBlockFormat.setLeftMargin(48);

    cursor.insertBlock(titleBlockFormat); //Title
    cursor.insertText(tr("Formulario del Puesto"),titleCharFormat);
    cursor.insertBlock();

    cursor.insertBlock(headerBlockFormat);
    cursor.insertText("1-" + m_metadataPage->title(),headerCharFormat);
    //cursor.insertBlock();

    cursor.insertBlock(textBlockFormat);
    cursor.insertText(tr("Puesto: "),boldCharFormat);
    cursor.insertText(m_metadataPage->nombrePuesto(),normalCharFormat);

    cursor.insertBlock(textBlockFormat);
    cursor.insertText(tr("Establecimiento: "),boldCharFormat);
    cursor.insertText(m_metadataPage->establecimiento(),normalCharFormat);

    cursor.insertBlock(textBlockFormat);
    cursor.insertText(tr("Cero del puesto: "),boldCharFormat);
    cursor.insertText(m_metadataPage->ceroPuesto(),normalCharFormat);

    cursor.insertBlock(textBlockFormat);
    cursor.insertText(tr("Nivel de referencia: "),boldCharFormat);
    cursor.insertText(m_metadataPage->nivelReferencia(),normalCharFormat);

    cursor.insertBlock(textBlockFormat);
    cursor.insertText(tr("Latitud: "),boldCharFormat);
    cursor.insertText(m_metadataPage->latitud(),normalCharFormat);

    cursor.insertBlock(textBlockFormat);
    cursor.insertText(tr("Longitud: "),boldCharFormat);
    cursor.insertText(m_metadataPage->longitud(),normalCharFormat);

    cursor.insertBlock(textBlockFormat);
    cursor.insertText(tr("Inicio de observaciones: "),boldCharFormat);
    cursor.insertText(m_metadataPage->fechaInicio(),normalCharFormat);

    cursor.insertBlock(textBlockFormat);
    cursor.insertText(tr("Fin de observaciones: "),boldCharFormat);
    cursor.insertText(m_metadataPage->fechaFinal(),normalCharFormat);

    cursor.insertBlock(textBlockFormat);
    cursor.insertText(tr("Duración de observaciones: "),boldCharFormat);
    cursor.insertText(m_metadataPage->duracion(),normalCharFormat);

    cursor.insertBlock(textBlockFormat);
    cursor.insertText(tr("Huso Horario: "),boldCharFormat);
    cursor.insertText(m_metadataPage->usoHorario(),normalCharFormat);
    cursor.insertBlock(textBlockFormat);
    //cursor.insertBlock();
    cursor.insertText(m_metadataPage->responsableHeader(),boldCharFormat);

    cursor.insertBlock(subTextBlockFormat);
    cursor.insertText(tr("-Nombre: "),boldCharFormat);
    cursor.insertText(m_metadataPage->responsable(),normalCharFormat);

    cursor.insertBlock(subTextBlockFormat);
    cursor.insertText("-Departamento: ",boldCharFormat);
    cursor.insertText(m_metadataPage->responsabeDpto(),normalCharFormat);

    cursor.insertBlock();

    //reportWindow->reportEdit()->appendPlainText(m_metadataPage->nombrePuesto());
    //reportWindow->reportEdit()->appendPlainText(m_metadataPage->establecimiento());
    //reportWindow->reportEdit()->appendPlainText(m_metadataPage->latitud());
    //reportWindow->reportEdit()->appendPlainText(m_metadataPage->longitud());
    //reportWindow->reportEdit()->appendPlainText(m_metadataPage->fechaInicio());
    //reportWindow->reportEdit()->appendPlainText(m_metadataPage->fechaFinal());
    //reportWindow->reportEdit()->appendPlainText(m_metadataPage->duracion());
    //reportWindow->reportEdit()->appendPlainText(m_metadataPage->usoHorario());
    //reportWindow->reportEdit()->appendPlainText(m_metadataPage->responsable());
    //reportWindow->reportEdit()->appendPlainText(m_metadataPage->responsabeDpto());

    cursor.insertBlock(headerBlockFormat);
    cursor.insertText("2-" + m_generalidadesPage->title(),headerCharFormat);

    cursor.insertBlock(textBlockFormat);
    cursor.insertText(tr("Descripción de la costa: "),boldCharFormat);
    cursor.insertText(m_generalidadesPage->descripcionCosta(),normalCharFormat);
    cursor.insertBlock();

    cursor.insertBlock(textBlockFormat);
    cursor.insertText(tr("Datos del mareógrafo: "),boldCharFormat);
    cursor.insertText(m_generalidadesPage->descripcionMareografo(),normalCharFormat);
    cursor.insertBlock();

    cursor.insertBlock(textBlockFormat);
    cursor.insertText(tr("Descripción de la instalación del mareógrafo: "),boldCharFormat);
    cursor.insertText(m_generalidadesPage->descripcionInstalacionMareografo(),normalCharFormat);
    cursor.insertBlock();

    cursor.insertBlock(textBlockFormat);
    cursor.insertText(tr("Datos sobre averías en los dispositivos de nivel: "),boldCharFormat);
    cursor.insertText(m_generalidadesPage->descripcionAverias(),normalCharFormat);
    cursor.insertBlock();


    cursor.insertBlock(headerBlockFormat);
    cursor.insertText("3-" + m_chapasReferenciasPage->title(),headerCharFormat);

    cursor.insertBlock(textBlockFormat);
    cursor.insertText(tr("Datos de la chapa de partida: "),boldCharFormat);
    cursor.insertText(m_chapasReferenciasPage->descripcionChapaPartida(),normalCharFormat);
    cursor.insertBlock();

    cursor.insertBlock(textBlockFormat);
    cursor.insertText(tr("Datos de la chapa de principal: "),boldCharFormat);
    cursor.insertText(m_chapasReferenciasPage->descripcionChapaPrincipal(),normalCharFormat);
    cursor.insertBlock();

    cursor.insertBlock(textBlockFormat);
    cursor.insertText(tr("Datos de la chapa de trabajo: "),boldCharFormat);
    cursor.insertText(m_chapasReferenciasPage->descripcionChapaTrabajo(),normalCharFormat);
    cursor.insertBlock();

    cursor.insertBlock(headerBlockFormat);
    cursor.insertText("4-" + m_ceroProfundidadPage->title(),headerCharFormat);

    cursor.insertBlock(textBlockFormat);
    cursor.insertText("Cero de profundidad: ",boldCharFormat);
    cursor.insertText(m_ceroProfundidadPage->ceroDeProfundidad(),normalCharFormat);

    cursor.insertBlock(textBlockFormat);
    cursor.insertText("Método de determinacion: ",boldCharFormat);
    cursor.insertText(m_ceroProfundidadPage->metodoCeroDeProfundidad(),normalCharFormat);

    cursor.insertBlock(textBlockFormat);
    cursor.insertText("Período de observaciones: ",boldCharFormat);
    cursor.insertText(m_ceroProfundidadPage->periodoObsCeroDeProfundidad(),normalCharFormat);
    //cursor.insertBlock();

    cursor.insertBlock(textBlockFormat);
    cursor.insertText(m_ceroProfundidadPage->situacionCeroProfundidad(),boldCharFormat);

    cursor.insertBlock(subTextBlockFormat);
    cursor.insertText(tr("-Cero del puesto: "),boldCharFormat);
    cursor.insertText(m_ceroProfundidadPage->situacionCeroProfCeroPuesto(),normalCharFormat);

    cursor.insertBlock(subTextBlockFormat);
    cursor.insertText(tr("-Nivel medio del mar: "),boldCharFormat);
    cursor.insertText(m_ceroProfundidadPage->situacionCeroProfNMM(),normalCharFormat);

    cursor.insertBlock(subTextBlockFormat);
    cursor.insertText(tr("-Chapa principal: "),boldCharFormat);
    cursor.insertText(m_ceroProfundidadPage->situacionCeroProfChapaPrincipal(),normalCharFormat);

    //cursor.insertBlock();
    cursor.insertBlock(textBlockFormat);
    cursor.insertText(m_ceroProfundidadPage->oscilacionesRespectoACeroProfundidad(),boldCharFormat);

    cursor.insertBlock(subTextBlockFormat);
    cursor.insertText(tr("-Nivel mínimo observado: "),boldCharFormat);
    cursor.insertText(m_ceroProfundidadPage->nivelMinimo(),normalCharFormat);

    cursor.insertBlock(subTextBlockFormat);
    cursor.insertText(tr("-Nivel máximo observado: "),boldCharFormat);
    cursor.insertText(m_ceroProfundidadPage->nivelMaximo(),normalCharFormat);
    cursor.insertBlock();

    cursor.insertBlock(headerBlockFormat);
    cursor.insertText(tr("5-Constantes Armónicas"),headerCharFormat);

    cursor.insertBlock(textBlockFormat);
    int rowNumber = m_hcVector.size() + 1;
    int colNumber = 5;

    QTextTableFormat tableFormat;
    tableFormat.setAlignment(Qt::AlignHCenter);

    QTextTable *hcTable = cursor.insertTable(rowNumber,colNumber,tableFormat);

    QTextBlockFormat cellsFormat;
    cellsFormat.setAlignment(Qt::AlignCenter);

    cursor = hcTable->cellAt(0,0).firstCursorPosition();
    cursor.setBlockFormat(cellsFormat);
    cursor.insertText(tr("Constante"),boldCharFormat);

    cursor = hcTable->cellAt(0,1).firstCursorPosition();
    cursor.setBlockFormat(cellsFormat);
    cursor.insertText(tr("Frecuencia[ᵒ/h]"),boldCharFormat);

    cursor = hcTable->cellAt(0,2).firstCursorPosition();
    cursor.setBlockFormat(cellsFormat);
    cursor.insertText(tr("Amplitud[m]"),boldCharFormat);

    cursor = hcTable->cellAt(0,3).firstCursorPosition();
    cursor.setBlockFormat(cellsFormat);
    cursor.insertText(tr("Fase[ᵒ]"),boldCharFormat);

    cursor = hcTable->cellAt(0,4).firstCursorPosition();
    cursor.setBlockFormat(cellsFormat);
    cursor.insertText(tr("Fase Corr[ᵒ]"),boldCharFormat);

    for (int i = 0; i < m_hcVector.size(); ++i){
        cursor = hcTable->cellAt(i+1,0).firstCursorPosition();
        cursor.setBlockFormat(cellsFormat);
        cursor.insertText(m_hcVector.at(i).name(),normalCharFormat);

        cursor = hcTable->cellAt(i+1,1).firstCursorPosition();
        cursor.setBlockFormat(cellsFormat);
        cursor.insertText(QString::number(m_hcVector.at(i).frequency(),'f',6),normalCharFormat);

        cursor = hcTable->cellAt(i+1,2).firstCursorPosition();
        cursor.setBlockFormat(cellsFormat);
        cursor.insertText(QString::number(m_hcVector.at(i).amplitud(),'f',6),normalCharFormat);

        cursor = hcTable->cellAt(i+1,3).firstCursorPosition();
        cursor.setBlockFormat(cellsFormat);
        cursor.insertText(QString::number(m_hcVector.at(i).phase(),'f',3),normalCharFormat);

        cursor = hcTable->cellAt(i+1,4).firstCursorPosition();
        cursor.setBlockFormat(cellsFormat);
        cursor.insertText(QString::number(m_hcVector.at(i).correctedPhase(),'f',3),normalCharFormat);
    }

    cursor.setPosition(reportWindow->reportEdit()->document()->lastBlock().position());

    cursor.insertBlock(headerBlockFormat);
    cursor.insertBlock(headerBlockFormat);
    cursor.insertText("6-Constantes No Armónicas",headerCharFormat);

    cursor.insertBlock(textBlockFormat);
    cursor.insertText(tr("Hora del puesto media: "),boldCharFormat);
    cursor.insertText(m_HoraDelPuestoMedia,normalCharFormat);

    cursor.insertBlock(textBlockFormat);
    cursor.insertText(tr("Hora del puesto: "),boldCharFormat);
    cursor.insertText(m_HoraDelPuesto,normalCharFormat);

    cursor.insertBlock(textBlockFormat);
    cursor.insertText(tr("Duración del vaciante: "),boldCharFormat);
    cursor.insertText(m_DuracionDelVaciante,normalCharFormat);

    cursor.insertBlock(textBlockFormat);
    cursor.insertText(tr("Duración del llenante: "),boldCharFormat);
    cursor.insertText(m_DuracionDelLlenate,normalCharFormat);

    cursor.insertBlock(textBlockFormat);
    cursor.insertText(tr("Crecimiento de la marea semidiurna: "),boldCharFormat);
    cursor.insertText(m_CrecimientoDeLaMareaSemidiurna,normalCharFormat);

    cursor.insertBlock(textBlockFormat);
    cursor.insertText(tr("Crecimiento de la marea paraláctica: "),boldCharFormat);
    cursor.insertText(m_CrecimientoDeLaMareaParalactica,normalCharFormat);

    cursor.insertBlock(textBlockFormat);
    cursor.insertText(tr("Crecimiento de la marea diurna: "),boldCharFormat);
    cursor.insertText(m_CrecimientoDeLaMareaDiurna,normalCharFormat);

    cursor.insertBlock(textBlockFormat);
    cursor.insertText(tr("Altura promedio de la marea semidiurna: "),boldCharFormat);
    cursor.insertText(m_AlturaPromedioDeLaMareaSemidiurna,normalCharFormat);

    cursor.insertBlock(textBlockFormat);
    cursor.insertText(tr("Altura promedio de la marea en sicígias: "),boldCharFormat);
    cursor.insertText(m_AlturaPromedioDeLaMareaSicigias,normalCharFormat);

    cursor.insertBlock(textBlockFormat);
    cursor.insertText(tr("Altura promedio de la marea en cuadratura: "),boldCharFormat);
    cursor.insertText(m_AlturaPromedioDeLaMareaCuadratura,normalCharFormat);

    cursor.insertBlock(textBlockFormat);
    cursor.insertText(tr("Altura promedio de la marea tropical: "),boldCharFormat);
    cursor.insertText(m_AlturaPromedioDeLaMareaTropical,normalCharFormat);

    cursor.insertBlock(textBlockFormat);
    cursor.insertText(tr("Relación de amplitudes: "),boldCharFormat);
    cursor.insertText(m_RelacionDeAmplitud,normalCharFormat);

    cursor.insertBlock(headerBlockFormat);
    cursor.insertText("7-" + m_responsablesPage->title(),headerCharFormat);

    cursor.insertBlock(textBlockFormat);
    cursor.insertText(m_responsablesPage->proceso(),boldCharFormat);

    cursor.insertBlock(subTextBlockFormat);
    cursor.insertText(tr("-Nombre: "),boldCharFormat);
    cursor.insertText(m_responsablesPage->procesoNombre(),normalCharFormat);

    cursor.insertBlock(subTextBlockFormat);
    cursor.insertText(tr("-Departamento: "),boldCharFormat);
    cursor.insertText(m_responsablesPage->procesoDpto(),normalCharFormat);

    cursor.insertBlock(textBlockFormat);
    cursor.insertText(m_responsablesPage->reviso(),boldCharFormat);

    cursor.insertBlock(subTextBlockFormat);
    cursor.insertText(tr("-Nombre: "),boldCharFormat);
    cursor.insertText(m_responsablesPage->revisoNombre(),normalCharFormat);

    cursor.insertBlock(subTextBlockFormat);
    cursor.insertText(tr("-Departamento: "),boldCharFormat);
    cursor.insertText(m_responsablesPage->revisoDpto(),normalCharFormat);

    reportWindow->show();

    QDialog::accept();
}
