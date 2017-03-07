#ifndef UPLOADHCDIALOG_H
#define UPLOADHCDIALOG_H

#include <QDialog>

namespace Ui {
class UploadHCDialog;
}

class UploadHCDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UploadHCDialog(QWidget *parent = 0);
    ~UploadHCDialog();

    QString provincia() const;
    QString localidad() const;

public slots:
    void accept();

private:
    Ui::UploadHCDialog *ui;
};

#endif // UPLOADHCDIALOG_H
