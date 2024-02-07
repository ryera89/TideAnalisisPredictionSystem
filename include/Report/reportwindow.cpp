#include "reportwindow.h"

#include <QAction>
#include <QFileDialog>
#include <QLayout>
#include <QMenu>
#include <QMenuBar>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
ReportWindow::ReportWindow(QWidget *parent) : QMainWindow(parent) {
  m_printAction = new QAction(QIcon(":images/print.png"), tr("Imprimir"));
  connect(m_printAction, &QAction::triggered, this, &ReportWindow::print);

  m_printAsPdfAction =
      new QAction(QIcon(":images/pdfPrint.png"), tr("Imprimir como pdf"));
  connect(m_printAsPdfAction, &QAction::triggered, this,
          &ReportWindow::printPDF);

  m_printMenu = menuBar()->addMenu(tr("Imprimir"));
  m_printMenu->addAction(m_printAsPdfAction);
  m_printMenu->addAction(m_printAction);

  m_reportEdit = new QTextEdit;

  // m_reportEdit->setFixedWidth((printer.paperRect().size().width()));

  QWidget *central = new QWidget;

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(m_reportEdit);
  layout->setAlignment(Qt::AlignCenter);
  // layout->setMargin(10);

  central->setLayout(layout);

  setCentralWidget(central);

  // setMinimumWidth(m_reportEdit->width() + 10);
  // setMaximumWidth(m_reportEdit->width() + 10);

  setMinimumHeight(500);

  // setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);

  // setWindowIcon(QIcon(":images/report-icon.png"));
  // setWindowTitle(tr("Formulario del Puesto de Nivel"));
  setAttribute(Qt::WA_DeleteOnClose);
}

void ReportWindow::setPageSize() {
  QPrinter printer(QPrinter::PrinterResolution);
  printer.setOutputFormat(QPrinter::PdfFormat);
  // printer.setPaperSize(QPrinter::A4);
  // m_reportEdit->document()->setPageSize(printer.paperRect().size());
  // m_reportEdit->setFixedWidth(printer.paperRect().size().width());
}

void ReportWindow::print() {
  QPrinter *printer = new QPrinter;

  QPrintDialog printDialog(printer, this);
  if (printDialog.exec() == QDialog::Accepted) {
    // this->reportEdit()->document()->setPageSize(printer->pageRect().size());
    this->reportEdit()->document()->print(printer);
  }
}

void ReportWindow::printPDF() {
  QString fileName = QFileDialog::getSaveFileName(this, tr("Exportar como PDF"),
                                                  QString(), "*.pdf");
  if (QFileInfo(fileName).suffix().isEmpty())
    fileName.append(".pdf");

  QPrinter printer(QPrinter::PrinterResolution);

  printer.setOutputFormat(QPrinter::PdfFormat);
  // printer.setPaperSize(QPrinter::A4);
  printer.setOutputFileName(fileName);

  // this->reportEdit()->document()->setPageSize(printer.pageRect().size());

  this->reportEdit()->print(&printer);
}
