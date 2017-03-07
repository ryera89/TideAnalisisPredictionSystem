#include "uploadhcdialog.h"
#include "ui_uploadhcdialog.h"

UploadHCDialog::UploadHCDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UploadHCDialog)
{


    ui->setupUi(this);

    Qt::WindowFlags flags = Qt::Dialog | Qt::WindowCloseButtonHint;
    this->setWindowFlags(flags);

    //this->setWindowTitle(tr("Metadatos"));

    this->setAttribute(Qt::WA_DeleteOnClose);
}

UploadHCDialog::~UploadHCDialog()
{
    delete ui;
}

QString UploadHCDialog::provincia() const
{
    return ui->provinciaLineEdit->text();
}

QString UploadHCDialog::localidad() const
{
    return ui->localidadLineEdit->text();
}

void UploadHCDialog::accept()
{
    emit accepted();
}
