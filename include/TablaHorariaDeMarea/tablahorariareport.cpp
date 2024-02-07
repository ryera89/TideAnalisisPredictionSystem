#include "tablahorariareport.h"
#include <QFileDialog>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>

TablaHorariaReport::TablaHorariaReport(QWidget *parent)
    : ReportWindow(parent) {}

void TablaHorariaReport::print() {
  QPrinter printer(QPrinter::ScreenResolution);
  // printer.setOrientation(QPrinter::Landscape);
  // printer.setPageMargins(5, 5, 5, 5, QPrinter::Millimeter);
  QPrintDialog printDialog(&printer, this);
  if (printDialog.exec() == QDialog::Accepted) {
    // this->reportEdit()->document()->setPageSize(printer.pageRect().size());
    this->reportEdit()->document()->print(&printer);
  }
}

void TablaHorariaReport::printPDF() {
  QString fileName = QFileDialog::getSaveFileName(this, tr("Exportar como PDF"),
                                                  QString(), "*.pdf");
  if (QFileInfo(fileName).suffix().isEmpty())
    fileName.append(".pdf");

  QPrinter printer(QPrinter::ScreenResolution);

  // printer.setOrientation(QPrinter::Landscape);
  printer.setOutputFormat(QPrinter::PdfFormat);
  // printer.setPaperSize(QPrinter::A4);
  // printer.setPageMargins(5, 5, 5, 5, QPrinter::Millimeter);
  printer.setOutputFileName(fileName);

  // this->reportEdit()->document()->setPageSize(printer.pageRect().size());

  this->reportEdit()->print(&printer);
}
