#include "tablahorariawidget.h"
#include "tablahorariareport.h"
#include <QDateEdit>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QTextTable>
#include <QToolButton>
#include <QVBoxLayout>

TablaHorariaWidget::TablaHorariaWidget(QWidget *parent) : QWidget(parent) {

  createComponents();
  this->setWindowTitle(tr("Niveles Medios y Extremos"));

  this->setWindowIcon(QIcon(":images/timetable.png"));
  this->setAttribute(Qt::WA_DeleteOnClose);
}

QSize TablaHorariaWidget::sizeHint() const { return this->maximumSize(); }

void TablaHorariaWidget::createTable() {
  TablaHorariaReport *reportWindow = new TablaHorariaReport;
  reportWindow->setWindowIcon(QIcon(":images/timetable.png"));
  reportWindow->setWindowTitle(tr("Tabla Horaria de Marea"));

  QTextCursor cursor = reportWindow->reportEdit()->textCursor();

  QTextBlockFormat titleBlockFormat;
  titleBlockFormat.setAlignment(Qt::AlignHCenter);

  QTextCharFormat titleCharFormat;
  titleCharFormat.setFontWeight(QFont::Bold);
  titleCharFormat.setFontPointSize(14);

  QTextCharFormat subTitleCharFormat;
  subTitleCharFormat.setFontWeight(QFont::Bold);
  subTitleCharFormat.setFontPointSize(12);

  cursor.insertBlock(titleBlockFormat);
  cursor.insertText(tr("TABLA HORARIA DE MAREA [m]"), titleCharFormat);

  cursor.insertBlock(titleBlockFormat);
  cursor.insertText("Puesto: " + m_nombreDelPuesto + ". " + "Latitud: " +
                        m_latitudStr + ", " + "Longitud: " + m_longitudStr,
                    subTitleCharFormat);

  cursor.insertBlock();
  cursor.insertBlock();

  int rowNumber = nonHiddenRowNumber();
  int colNumber = m_tablaHoraria->columnCount();

  QTextTableFormat tableFormat;
  QBrush blackBrush(Qt::SolidPattern);
  tableFormat.setBorderBrush(blackBrush);
  tableFormat.setBorder(0.5);
  tableFormat.setBorderStyle(QTextTableFormat::BorderStyle_Solid);
  tableFormat.setAlignment(Qt::AlignCenter);

  QTextCharFormat boldCharFormat;
  boldCharFormat.setFontWeight(QFont::Bold);
  boldCharFormat.setFontPointSize(7);

  QTextCharFormat normalCharFormat;
  normalCharFormat.setFontWeight(QFont::Normal);
  normalCharFormat.setFontPointSize(7);

  QTextTableCellFormat cellFormat;
  cellFormat.setLeftPadding(2);
  cellFormat.setRightPadding(2);
  cellFormat.setTopPadding(2);

  QTextTable *tablaHoraria =
      cursor.insertTable(rowNumber, colNumber, tableFormat);
  QTextBlockFormat cellBlockFormat;
  cellBlockFormat.setAlignment(Qt::AlignCenter);

  tablaHoraria->mergeCells(0, 0, 2, 1);
  tablaHoraria->mergeCells(0, 1, 1, colNumber - 6);
  tablaHoraria->mergeCells(0, colNumber - 5, 2, 1);
  tablaHoraria->mergeCells(0, colNumber - 4, 2, 1);
  tablaHoraria->mergeCells(0, colNumber - 3, 1, 2);
  tablaHoraria->mergeCells(0, colNumber - 1, 2, 1);

  const QString fecha = "FECHA";
  const QString hora = "HORA";
  const QString suma = "SUMA";
  const QString nivel_medio = " NIVEL \n MEDIO";
  const QString extremos = "EXTREMOS";
  const QString max = "MAX";
  const QString min = "MIN";
  const QString diff = "DIF";

  cursor = tablaHoraria->cellAt(0, 0).firstCursorPosition();
  tablaHoraria->cellAt(0, 0).setFormat(cellFormat);
  cursor.setBlockFormat(cellBlockFormat);
  cursor.insertText(fecha, boldCharFormat);

  cursor = tablaHoraria->cellAt(0, 1).firstCursorPosition();
  tablaHoraria->cellAt(0, 1).setFormat(cellFormat);
  cursor.setBlockFormat(cellBlockFormat);
  cursor.insertText(hora, boldCharFormat);

  cursor = tablaHoraria->cellAt(0, colNumber - 5).firstCursorPosition();
  tablaHoraria->cellAt(0, colNumber - 5).setFormat(cellFormat);
  cursor.setBlockFormat(cellBlockFormat);
  cursor.insertText(suma, boldCharFormat);

  cursor = tablaHoraria->cellAt(0, colNumber - 4).firstCursorPosition();
  tablaHoraria->cellAt(0, colNumber - 4).setFormat(cellFormat);
  cursor.setBlockFormat(cellBlockFormat);
  cursor.insertText(nivel_medio, boldCharFormat);

  cursor = tablaHoraria->cellAt(0, colNumber - 3).firstCursorPosition();
  tablaHoraria->cellAt(0, colNumber - 3).setFormat(cellFormat);
  cursor.setBlockFormat(cellBlockFormat);
  cursor.insertText(extremos, boldCharFormat);

  cursor = tablaHoraria->cellAt(0, colNumber - 1).firstCursorPosition();
  tablaHoraria->cellAt(0, colNumber - 1).setFormat(cellFormat);
  cursor.setBlockFormat(cellBlockFormat);
  cursor.insertText(diff, boldCharFormat);

  cursor = tablaHoraria->cellAt(1, colNumber - 3).firstCursorPosition();
  tablaHoraria->cellAt(1, colNumber - 3).setFormat(cellFormat);
  cursor.setBlockFormat(cellBlockFormat);
  cursor.insertText(max, boldCharFormat);

  cursor = tablaHoraria->cellAt(1, colNumber - 2).firstCursorPosition();
  tablaHoraria->cellAt(1, colNumber - 2).setFormat(cellFormat);
  cursor.setBlockFormat(cellBlockFormat);
  cursor.insertText(min, boldCharFormat);

  /*cursor = tablaHoraria->cellAt(rowNumber - 2,0).firstCursorPosition();
  cursor.setBlockFormat(cellBlockFormat);
  cursor.insertText(suma);

  cursor = tablaHoraria->cellAt(rowNumber - 1,0).firstCursorPosition();
  cursor.setBlockFormat(cellBlockFormat);
  cursor.insertText(promedio);*/

  /*cursor = tablaHoraria->cellAt(1,colNumber - 2).firstCursorPosition();
  cursor.setBlockFormat(cellBlockFormat);
  cursor.insertText(min);*/

  for (int i = 1; i <= colNumber - 6; ++i) {
    QString h = m_tablaHoraria->item(1, i)->text();
    cursor = tablaHoraria->cellAt(1, i).firstCursorPosition();
    tablaHoraria->cellAt(1, i).setFormat(cellFormat);
    cursor.setBlockFormat(cellBlockFormat);
    cursor.insertText(h, normalCharFormat);
  }

  int rowCont = m_tablaHoraria->rowCount();
  int colCont = m_tablaHoraria->columnCount();
  int k = 2; // Row for text table

  for (int j = 2; j < rowCont; ++j) { // j rows, i columns
    if (!m_tablaHoraria->isRowHidden(j)) {
      for (int i = 0; i < colCont; ++i) {

        if (j < rowCont - 2 && i == 0) {
          QString str = m_tablaHoraria->item(j, i)
                            ->data(Qt::DisplayRole)
                            .toDate()
                            .toString("d/M/yy");
          cursor = tablaHoraria->cellAt(k, i).firstCursorPosition();
          tablaHoraria->cellAt(k, i).setFormat(cellFormat);
          cursor.setBlockFormat(cellBlockFormat);
          cursor.insertText(str, normalCharFormat);
        } else {
          QString str = m_tablaHoraria->item(j, i)->text();
          cursor = tablaHoraria->cellAt(k, i).firstCursorPosition();
          tablaHoraria->cellAt(k, i).setFormat(cellFormat);
          cursor.setBlockFormat(cellBlockFormat);
          cursor.insertText(str, normalCharFormat);
        }
      }
      ++k;
    }
  }

  reportWindow->show();
}

void TablaHorariaWidget::loadMetaData(const ProjectMetaData &metadata) {
  m_nombreDelPuesto = metadata.stationName();

  double latitud = metadata.latitud();
  m_latitudStr = "0.000";
  if (latitud > 0.0) {
    m_latitudStr = QString::number(latitud, 'f', 3) + "⁰ N";
  }
  if (latitud < 0.0) {
    m_latitudStr = QString::number(qAbs(latitud), 'f', 3) + "⁰ S";
  }

  double longitud = metadata.longitud();
  m_longitudStr = "0.000";
  if (longitud > 0.0) {
    m_longitudStr = QString::number(longitud, 'f', 3) + "⁰ E";
  }
  if (longitud < 0.0) {
    m_longitudStr = QString::number(qAbs(longitud), 'f', 3) + "⁰ W";
  }
}

void TablaHorariaWidget::loadTableData(const TidalData &m_data) {
  m_tablaHoraria->loadData(m_data);

  m_minimo = m_data.m_minimo;
  m_maximo = m_data.m_maximo;

  m_minimoInInterval = m_minimo;
  m_maximoInInterval = m_maximo;

  m_iniDateEdit->setMinimumDate(m_data.m_measurementDates.at(0));
  m_iniDateEdit->setMaximumDate(
      m_data.m_measurementDates.at(m_data.m_measurementDates.size() - 1));
  m_iniDateEdit->setDate(m_data.m_measurementDates.at(0));

  m_endDateEdit->setMinimumDate(m_data.m_measurementDates.at(0));
  m_endDateEdit->setMaximumDate(
      m_data.m_measurementDates.at(m_data.m_measurementDates.size() - 1));
  m_endDateEdit->setDate(
      m_data.m_measurementDates.at(m_data.m_measurementDates.size() - 1));

  // QVariant max = m_data.m_maximo.seaLevel();
  // QVariant min = m_data.m_minimo.seaLevel();

  m_maxLabel->setText(
      tr("Nivel Máximo: %1  Fecha: %2 %3")
          .arg(m_data.m_maximo.seaLevel())
          .arg(m_data.m_maximo.measurementDate().toString("dd/MM/yyyy"))
          .arg(m_data.m_maximo.measurementTime().toString("hh:mm:ss")));

  m_minLabel->setText(
      tr("Nivel Mínimo: %1  Fecha: %2 %3")
          .arg(m_data.m_minimo.seaLevel())
          .arg(m_data.m_minimo.measurementDate().toString("dd/MM/yyyy"))
          .arg(m_data.m_minimo.measurementTime().toString("hh:mm:ss")));

  /*m_maxLabel->setText("Nivel Máximo: " + max.toString() + " Fecha: " +
  m_data.m_maximo.measurementDate().toString("dd/MM/yyyy")
                      + " " +
  m_data.m_maximo.measurementTime().toString("hh:mm"));

  m_minLabel->setText("Nivel Mínimo: " + min.toString() + " Fecha: " +
  m_data.m_minimo.measurementDate().toString("dd/MM/yyyy")
                      + " " +
  m_data.m_minimo.measurementTime().toString("hh:mm"));*/
}

void TablaHorariaWidget::setIntervalState(bool enabledState) {
  m_iniDateEdit->setEnabled(enabledState);
  m_endDateEdit->setEnabled(enabledState);
  m_applyPushButton->setEnabled(enabledState);
}

void TablaHorariaWidget::setMinimumEndDateEditValue(const QDate &date) {
  if (m_endDateEdit->date() < date) {
    m_endDateEdit->setDate(date);
  }
  m_endDateEdit->setMinimumDate(date);
}

void TablaHorariaWidget::showInterval() {
  m_notHiddenRows.clear();

  QDate begin = m_iniDateEdit->date();
  QDate end = m_endDateEdit->date();
  for (int row = 2; row <= m_tablaHoraria->rowCount() - 3; ++row) {
    if (begin <= m_tablaHoraria->item(row, 0)->data(Qt::DisplayRole).toDate() &&
        end >= m_tablaHoraria->item(row, 0)->data(Qt::DisplayRole).toDate()) {
      m_tablaHoraria->setRowHidden(row, false);
      m_notHiddenRows.push_back(row);
    } else {
      m_tablaHoraria->setRowHidden(row, true);
    }
  }
  // Actualización de los datos solo se calculan valores para los datos
  // mostrados en la tabla
  setSumAndMeanOfNotHiddenRows();
}

void TablaHorariaWidget::showAllData(bool showAll) {
  if (showAll) {
    m_notHiddenRows.clear();

    for (int row = 2; row <= m_tablaHoraria->rowCount() - 3; ++row) {
      m_tablaHoraria->setRowHidden(row, false);
      m_notHiddenRows.push_back(row);
    }

    setSumAndMeanOfAllRows();
  }
}

void TablaHorariaWidget::createComponents() {
  m_tablaHoraria = new TablaHorariaDeMarea(this);
  m_tablaHoraria->verticalHeader()->hide();

  m_showDataGroupBox = new QGroupBox(tr("Datos Mostrados"));
  m_intervalGroupBox = new QGroupBox(tr("Intervalo Personalizado"));
  m_extremesGroupBox = new QGroupBox(tr("Extremos"));

  m_allRadioButton = new QRadioButton(tr("Todos"));
  m_allRadioButton->setChecked(true);
  connect(m_allRadioButton, SIGNAL(clicked(bool)), this,
          SLOT(showAllData(bool)));

  m_customRadioButton = new QRadioButton(tr("Intervalo Personalizado"));
  connect(m_customRadioButton, SIGNAL(toggled(bool)), this,
          SLOT(setIntervalState(bool)));

  m_iniDateLabel = new QLabel(tr("Fecha de Inicio"));
  m_iniDateLabel->setAlignment(Qt::AlignCenter);
  m_endDateLabel = new QLabel(tr("Fecha de Fin"));
  m_endDateLabel->setAlignment(Qt::AlignCenter);
  m_maxLabel = new QLabel;
  m_minLabel = new QLabel;

  m_iniDateEdit = new QDateEdit;
  m_iniDateEdit->setCalendarPopup(true);
  m_iniDateEdit->setDisplayFormat("dd/MM/yyyy");
  m_iniDateEdit->setDisabled(true);
  connect(m_iniDateEdit, SIGNAL(dateChanged(QDate)), this,
          SLOT(setMinimumEndDateEditValue(QDate)));

  m_endDateEdit = new QDateEdit;
  m_endDateEdit->setCalendarPopup(true);
  m_endDateEdit->setDisplayFormat("dd/MM/yyyy");
  m_endDateEdit->setDisabled(true);

  m_applyPushButton = new QPushButton(tr("Aplicar"));
  m_applyPushButton->setDisabled(true);
  connect(m_applyPushButton, SIGNAL(clicked(bool)), this, SLOT(showInterval()));

  m_printToolButton = new QToolButton;
  m_printToolButton->setIcon(QIcon(":images/print-icon.png"));
  m_printToolButton->setMinimumSize(90, 90);
  m_printToolButton->setIconSize(QSize(90, 90));
  connect(m_printToolButton, SIGNAL(clicked(bool)), this, SLOT(createTable()));

  QVBoxLayout *datosMostradoLayout = new QVBoxLayout;
  datosMostradoLayout->addWidget(m_allRadioButton);
  datosMostradoLayout->addWidget(m_customRadioButton);
  m_showDataGroupBox->setLayout(datosMostradoLayout);

  QGridLayout *intervaloLayout = new QGridLayout;
  intervaloLayout->addWidget(m_iniDateLabel, 0, 0);
  intervaloLayout->addWidget(m_endDateLabel, 0, 1);
  intervaloLayout->addWidget(m_iniDateEdit, 1, 0);
  intervaloLayout->addWidget(m_endDateEdit, 1, 1);
  intervaloLayout->addWidget(m_applyPushButton, 2, 1);
  m_intervalGroupBox->setLayout(intervaloLayout);

  QVBoxLayout *extremeLayout = new QVBoxLayout;
  extremeLayout->addWidget(m_maxLabel);
  extremeLayout->addWidget(m_minLabel);
  m_extremesGroupBox->setLayout(extremeLayout);

  QHBoxLayout *upLayout = new QHBoxLayout;
  upLayout->addWidget(m_showDataGroupBox);
  upLayout->addSpacing(40);
  upLayout->addWidget(m_intervalGroupBox);
  upLayout->addSpacing(40);
  upLayout->addWidget(m_extremesGroupBox);
  upLayout->addWidget(m_printToolButton);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addLayout(upLayout);
  mainLayout->addWidget(m_tablaHoraria);

  this->setLayout(mainLayout);
}

void TablaHorariaWidget::setSumAndMeanOfNotHiddenRows() {
  bool ok;
  double minimo = m_tablaHoraria->item(m_notHiddenRows.at(0), 1)
                      ->data(Qt::DisplayRole)
                      .toDouble(&ok);
  double maximo = m_tablaHoraria->item(m_notHiddenRows.at(0), 1)
                      ->data(Qt::DisplayRole)
                      .toDouble(&ok);

  int k = 0;
  while (!ok && (k < m_notHiddenRows.size())) {
    minimo = m_tablaHoraria->item(m_notHiddenRows.at(++k), 1)
                 ->data(Qt::DisplayRole)
                 .toDouble(&ok);
    maximo = m_tablaHoraria->item(m_notHiddenRows.at(++k), 1)
                 ->data(Qt::DisplayRole)
                 .toDouble(&ok);
  }

  for (int column = 1; column < m_tablaHoraria->columnCount(); ++column) {
    double suma = 0.0;
    int counter = 0;
    for (int i = 0; i < m_notHiddenRows.size(); ++i) {
      // bool ok;
      double number = m_tablaHoraria->item(m_notHiddenRows.at(i), column)
                          ->data(Qt::DisplayRole)
                          .toDouble(&ok);
      if (ok) {
        ++counter;
        if (column < m_tablaHoraria->columnCount() - 5) {
          if (number < minimo) {
            minimo = number;
            m_minimoInInterval.setSeaLevel(minimo);
            m_minimoInInterval.setMeasurementDate(
                m_tablaHoraria->item(m_notHiddenRows.at(i), 0)
                    ->data(Qt::DisplayRole)
                    .toDate());
            m_minimoInInterval.setMeasurementTime(QTime::fromString(
                m_tablaHoraria->item(1, column)->text(), "hh:mm"));
          }
          if (number > maximo) {
            maximo = number;
            m_maximoInInterval.setSeaLevel(maximo);
            m_maximoInInterval.setMeasurementDate(
                m_tablaHoraria->item(m_notHiddenRows.at(i), 0)
                    ->data(Qt::DisplayRole)
                    .toDate());
            m_maximoInInterval.setMeasurementTime(QTime::fromString(
                m_tablaHoraria->item(1, column)->text(), "hh:mm"));
          }
        }
      }
      suma += number;
    }
    double promedio = suma / counter;

    m_tablaHoraria->item(m_tablaHoraria->rowCount() - 2, column)
        ->setData(Qt::DisplayRole, suma);
    m_tablaHoraria->item(m_tablaHoraria->rowCount() - 2, column)
        ->setText(QString::number(suma, 'f', 3));
    m_tablaHoraria->item(m_tablaHoraria->rowCount() - 1, column)
        ->setData(Qt::DisplayRole, promedio);
    m_tablaHoraria->item(m_tablaHoraria->rowCount() - 1, column)
        ->setText(QString::number(promedio, 'f', 3));
  }
  m_maxLabel->setText(
      tr("Nivel Máximo: %1  Fecha: %2 %3")
          .arg(m_maximoInInterval.seaLevel())
          .arg(m_maximoInInterval.measurementDate().toString("dd/MM/yyyy"))
          .arg(m_maximoInInterval.measurementTime().toString("hh:mm:ss")));

  m_minLabel->setText(
      tr("Nivel Mínimo: %1  Fecha: %2 %3")
          .arg(m_minimoInInterval.seaLevel())
          .arg(m_minimoInInterval.measurementDate().toString("dd/MM/yyyy"))
          .arg(m_minimoInInterval.measurementTime().toString("hh:mm:ss")));
}

void TablaHorariaWidget::setSumAndMeanOfAllRows() {
  bool ok;
  // double minimo =
  // m_tablaHoraria->item(m_notHiddenRows.at(0),1)->data(Qt::DisplayRole).toDouble(&ok);
  // double maximo =
  // m_tablaHoraria->item(m_notHiddenRows.at(0),1)->data(Qt::DisplayRole).toDouble(&ok);

  /*int k = 0;
  while (!ok && (k < m_notHiddenRows.size())){
      minimo =
  m_tablaHoraria->item(m_notHiddenRows.at(++k),1)->data(Qt::DisplayRole).toDouble(&ok);
      maximo =
  m_tablaHoraria->item(m_notHiddenRows.at(++k),1)->data(Qt::DisplayRole).toDouble(&ok);
  }*/

  for (int column = 1; column < m_tablaHoraria->columnCount(); ++column) {
    double suma = 0.0;
    int counter = 0;
    for (int i = 0; i < m_notHiddenRows.size(); ++i) {
      // bool ok;
      double number = m_tablaHoraria->item(m_notHiddenRows.at(i), column)
                          ->data(Qt::DisplayRole)
                          .toDouble(&ok);
      if (ok) {
        ++counter;
        /*if (column < m_tablaHoraria->columnCount() - 5){
            if (number < minimo){
                minimo = number;
                m_minimoInInterval.setSeaLevel(minimo);
                m_minimoInInterval.setMeasurementDate(m_tablaHoraria->item(m_notHiddenRows.at(i),0)->data(Qt::DisplayRole).toDate());
                m_minimoInInterval.setMeasurementTime(QTime::fromString(m_tablaHoraria->item(1,column)->text(),"hh:mm:ss"));
            }
            if (number > maximo){
                maximo = number;
                m_maximoInInterval.setSeaLevel(maximo);
                m_maximoInInterval.setMeasurementDate(m_tablaHoraria->item(m_notHiddenRows.at(i),0)->data(Qt::DisplayRole).toDate());
                m_maximoInInterval.setMeasurementTime(QTime::fromString(m_tablaHoraria->item(1,column)->text(),"hh:mm:ss"));

            }
        }*/
      }
      suma += number;
    }
    double promedio = suma / counter;

    m_tablaHoraria->item(m_tablaHoraria->rowCount() - 2, column)
        ->setData(Qt::DisplayRole, suma);
    m_tablaHoraria->item(m_tablaHoraria->rowCount() - 2, column)
        ->setText(QString::number(suma, 'f', 3));
    m_tablaHoraria->item(m_tablaHoraria->rowCount() - 1, column)
        ->setData(Qt::DisplayRole, promedio);
    m_tablaHoraria->item(m_tablaHoraria->rowCount() - 1, column)
        ->setText(QString::number(promedio, 'f', 3));
  }
  m_maxLabel->setText(
      tr("Nivel Máximo: %1  Fecha: %2 %3")
          .arg(m_maximo.seaLevel())
          .arg(m_maximo.measurementDate().toString("dd/MM/yyyy"))
          .arg(m_maximo.measurementTime().toString("hh:mm:ss")));

  m_minLabel->setText(
      tr("Nivel Mínimo: %1  Fecha: %2 %3")
          .arg(m_minimo.seaLevel())
          .arg(m_minimo.measurementDate().toString("dd/MM/yyyy"))
          .arg(m_minimo.measurementTime().toString("hh:mm:ss")));
}

int TablaHorariaWidget::nonHiddenRowNumber() {
  int rows = 0;
  for (int i = 0; i < m_tablaHoraria->rowCount(); ++i) {
    if (!m_tablaHoraria->isRowHidden(i))
      ++rows;
  }

  return rows;
}
