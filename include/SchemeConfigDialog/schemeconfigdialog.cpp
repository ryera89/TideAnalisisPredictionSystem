#include "schemeconfigdialog.h"
#include <QApplication>
#include <QDataStream>
#include <QFile>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QStringListModel>
#include <QVBoxLayout>

SchemeConfigDialog::SchemeConfigDialog(
    const QStringList &schemesLabels, const QStringList &componentsLabels,
    const QMap<QString, QMap<QString, bool>> &schemes_componentMap,
    const QMap<QString, QString> &schemeDescription, QWidget *parent,
    Qt::WindowFlags f)
    : QDialog(parent, f), m_componentsList(componentsLabels),
      m_schemes_componentMap(schemes_componentMap),
      m_schemesDescriptionMap(schemeDescription) {
  foreach (QString key, componentsLabels) {
    m_defaultAllCheckBoxesFalse[key] = false;
  }

  createComponent(schemesLabels, componentsLabels);
  settingLayout();

  Qt::WindowFlags flag = Qt::Dialog | Qt::WindowCloseButtonHint;
  this->setWindowFlags(flag);

  this->setWindowTitle(tr("Configuración de Esquemas"));
  this->setWindowIcon(QIcon(":images/configure1.png"));
  this->setAttribute(Qt::WA_DeleteOnClose);
}

QStringList SchemeConfigDialog::schemes() const {
  return m_myModel->stringList();
}

QMap<QString, QMap<QString, bool>>
SchemeConfigDialog::schemeComponentStatus() const {
  return m_schemes_componentMap;
}

void SchemeConfigDialog::updateSchemeDescription() {
  QModelIndex index = m_schemesList->currentIndex();
  if (index.isValid()) {
    QString schemeName =
        m_schemesList->model()->data(index, Qt::DisplayRole).toString();
    m_schemesDescriptionMap[schemeName] = m_descriptionEdit->toPlainText();
  }
}

void SchemeConfigDialog::selectAnalisisScheme(const QModelIndex &current,
                                              const QModelIndex &previous) {

  Q_UNUSED(previous);

  if (current.isValid()) {
    QString str = m_myModel->stringList().at(current.row());

    if (!m_schemes_componentMap.contains(str)) {
      m_schemes_componentMap[str] = m_defaultAllCheckBoxesFalse;
      // new code
      m_schemesDescriptionMap[str] = QString();
    }
    m_tidalSchemeComponents->setCheckBoxesStatus(
        m_schemes_componentMap.value(str));
    // Codigo nuevo
    /*if (previous.isValid()){
        QString prev = m_myModel->stringList().at(previous.row());
        m_schemesDescriptionMap[prev] = m_descriptionEdit->toPlainText();
    }*/
    m_descriptionEdit->setPlainText(m_schemesDescriptionMap.value(str));
  }
}

void SchemeConfigDialog::updateSchemeComponentStatus(const QString &label,
                                                     bool status) {
  QModelIndex index = m_schemesList->currentIndex();
  QString schemeLabel = m_schemesList->model()->data(index).toString();

  m_schemes_componentMap[schemeLabel][label] = status;
}

void SchemeConfigDialog::handleSchemeRename(const QString &oldName,
                                            const QString &newName) {
  if (oldName != newName) {
    m_schemes_componentMap.insert(newName,
                                  m_schemes_componentMap.value(oldName));
    m_schemes_componentMap.remove(oldName);

    // new code
    m_schemesDescriptionMap.insert(newName,
                                   m_schemesDescriptionMap.value(oldName));
    m_schemesDescriptionMap.remove(oldName);
  }
}

void SchemeConfigDialog::handleSchemeRemoved(const QString &schemeName) {
  m_schemes_componentMap.remove(schemeName);
  // new code
  m_schemesDescriptionMap.remove(schemeName);
}

bool SchemeConfigDialog::writeSchemesFile() {
  QFile file(m_schemeFilePath);
  if (file.open(QIODevice::WriteOnly)) {
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_7);

    out << (quint32)SchemesMagicNumber;

    out << (uint)m_myModel->stringList().size()
        << (uint)m_componentsList.size();

    QApplication::setOverrideCursor(Qt::WaitCursor);

    foreach (QString schemeName, m_myModel->stringList()) {
      out << schemeName << m_schemesDescriptionMap.value(schemeName);
      foreach (QString componentName, m_componentsList) {
        out << componentName
            << m_schemes_componentMap.value(schemeName).value(componentName);
      }
    }
    QApplication::restoreOverrideCursor();

  } else {
    QMessageBox::information(
        this, tr("Error escribiendo archivo"),
        tr("Error escribiendo el archivo de configuracion %1")
            .arg(file.fileName()));
    emit acceptButtonClicked();
    return false;
  }
  emit acceptButtonClicked();
  return true;
}

void SchemeConfigDialog::createComponent(const QStringList &schemesLabels,
                                         const QStringList &componentsLabels) {
  m_schemesGroupBox = new QGroupBox(tr("Esquema"), this);
  m_schemesGroupBox->setFixedWidth(200);

  m_schemesList = new MyListView(this);
  m_schemesList->setFocus();
  m_myModel = new QStringListModel(schemesLabels);
  m_schemesList->setModel(m_myModel);
  m_myDelegate = new MyListModelDelegate;
  connect(m_myDelegate, SIGNAL(schemeNameChanged(QString, QString)), this,
          SLOT(handleSchemeRename(QString, QString)));
  m_schemesList->setItemDelegate(m_myDelegate); // My Own Delegate.
  QModelIndex index = m_schemesList->model()->index(0, 0);
  if (index.isValid())
    m_schemesList->selectionModel()->select(index,
                                            QItemSelectionModel::SelectCurrent);

  connect(m_schemesList, SIGNAL(currentIndexChanged(QModelIndex, QModelIndex)),
          this, SLOT(selectAnalisisScheme(QModelIndex, QModelIndex)));
  connect(m_schemesList, SIGNAL(schemeDeleted(QString)), this,
          SLOT(handleSchemeRemoved(QString)));

  m_componentGroupBox = new QGroupBox(tr("Componentes"));
  m_componentGroupBox->setFixedWidth(200);

  m_tidalSchemeComponents =
      new TidalSchemeSelectionWidget(componentsLabels, this);
  connect(m_tidalSchemeComponents, SIGNAL(checkBoxStatusChanged(QString, bool)),
          this, SLOT(updateSchemeComponentStatus(QString, bool)));

  m_addButton = new QPushButton(QIcon(":images/add.png"), tr("Agregar"), this);
  m_addButton->setToolTip(tr("Agregar esquema"));
  m_addButton->setFocusPolicy(Qt::NoFocus);
  connect(m_addButton, SIGNAL(clicked(bool)), m_schemesList,
          SLOT(insertNewItem()));

  m_removeButton =
      new QPushButton(QIcon(":images/delete.png"), tr("Eliminar"), this);
  m_removeButton->setToolTip(tr("Eliminar esquema"));
  m_removeButton->setFocusPolicy(Qt::NoFocus);
  connect(m_removeButton, SIGNAL(clicked(bool)), m_schemesList,
          SLOT(removeItem()));

  m_okButton = new QPushButton(QIcon(":images/Ok.png"), tr("Aceptar"), this);
  m_okButton->setFocusPolicy(Qt::NoFocus);
  connect(m_okButton, SIGNAL(clicked(bool)), this, SLOT(writeSchemesFile()));

  m_cancelButton =
      new QPushButton(QIcon(":images/No.png"), tr("Cancelar"), this);
  m_cancelButton->setFocusPolicy(Qt::NoFocus);
  connect(m_cancelButton, SIGNAL(clicked(bool)), this, SLOT(close()));

  m_buttonGroupBox = new QGroupBox(this);

  m_descriptionEdit = new QPlainTextEdit(this);
  connect(m_descriptionEdit, SIGNAL(textChanged()), this,
          SLOT(updateSchemeDescription()));

  m_descriptionGroupBox = new QGroupBox("Descripción", this);
}

void SchemeConfigDialog::settingLayout() {
  QHBoxLayout *boxLayout = new QHBoxLayout; // Layout de la lista
  boxLayout->addWidget(m_schemesList);
  m_schemesGroupBox->setLayout(boxLayout);

  QHBoxLayout *componetesLayout = new QHBoxLayout; // Layout de los componentes
  componetesLayout->addWidget(m_tidalSchemeComponents);
  m_componentGroupBox->setLayout(componetesLayout);

  QHBoxLayout *descriptionLayout =
      new QHBoxLayout; // Layout del edit para la descripcion del esquema
  descriptionLayout->addWidget(m_descriptionEdit);
  m_descriptionGroupBox->setLayout(descriptionLayout);

  QHBoxLayout *upLayout = new QHBoxLayout;
  upLayout->addWidget(m_schemesGroupBox);
  upLayout->addWidget(m_componentGroupBox);

  QVBoxLayout *leftLayout = new QVBoxLayout;
  leftLayout->addLayout(upLayout);
  leftLayout->addWidget(m_descriptionGroupBox);

  QVBoxLayout *buttonLayout = new QVBoxLayout;
  buttonLayout->addWidget(m_addButton);
  buttonLayout->addWidget(m_removeButton);
  buttonLayout->addStretch();
  buttonLayout->addWidget(m_okButton);
  buttonLayout->addWidget(m_cancelButton);
  m_buttonGroupBox->setLayout(buttonLayout);

  QHBoxLayout *mainLayout = new QHBoxLayout;
  mainLayout->addLayout(leftLayout);
  mainLayout->addWidget(m_buttonGroupBox);

  this->setLayout(mainLayout);
}
