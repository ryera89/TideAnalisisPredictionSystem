#ifndef SCHEMECONFIGDIALOG_H
#define SCHEMECONFIGDIALOG_H

#include "../tidalschemeselectionwidget.h"
#include <QDialog>
// #include "mylistwidget.h"
// #include "Model_View/mylistmodel.h"
#include "../Model_View/mylistmodeldelegate.h"
#include "../Model_View/mylistview.h"

class QListWidget;
class PushButton;
class QStringListModel;
class QPlainTextEdit;

class SchemeConfigDialog : public QDialog {
  Q_OBJECT

public:
  explicit SchemeConfigDialog(
      const QStringList &schemesLabels, const QStringList &componentsLabels,
      const QMap<QString, QMap<QString, bool>> &schemes_componentMap,
      const QMap<QString, QString> &schemeDescription, QWidget *parent = 0,
      Qt::WindowFlags f = Qt::WindowFlags());
  QStringList schemes() const;
  QMap<QString, QMap<QString, bool>> schemeComponentStatus() const;
  QMap<QString, QString> schemeDescription() const {
    return m_schemesDescriptionMap;
  }

private slots:
  void updateSchemeDescription();
  void selectAnalisisScheme(
      const QModelIndex &current,
      const QModelIndex
          &previous); // Este slot es el que me permite al cambiar de esquema en
                      // la vista que se me acualicen los checkBoxes
  void updateSchemeComponentStatus(const QString &label, bool status);
  void handleSchemeRename(const QString &oldName, const QString &newName);
  void handleSchemeRemoved(const QString &schemeName);
  bool writeSchemesFile();

signals:
  void acceptButtonClicked();

private:
  enum { SchemesMagicNumber = 18041989 };

  const QString m_schemeFilePath = "data/schemes.sch";

  QStringList m_componentsList;
  QMap<QString, QMap<QString, bool>> m_schemes_componentMap;
  QMap<QString, bool> m_defaultAllCheckBoxesFalse;
  QMap<QString, QString> m_schemesDescriptionMap;

  QGroupBox *m_schemesGroupBox;
  QGroupBox *m_componentGroupBox; // Para el Widget de los componentes

  MyListView *m_schemesList;
  MyListModelDelegate *m_myDelegate;

  QPushButton *m_addButton;
  QPushButton *m_removeButton;
  QPushButton *m_okButton;
  QPushButton *m_cancelButton;
  QGroupBox *m_buttonGroupBox;

  TidalSchemeSelectionWidget *m_tidalSchemeComponents;

  QPlainTextEdit *m_descriptionEdit;
  QGroupBox *m_descriptionGroupBox;

  // MyListModel *m_myModel;

  QStringListModel *m_myModel;

  void createComponent(const QStringList &schemesLabels,
                       const QStringList &componentsLabels);
  void settingLayout();
};

#endif // SCHEMECONFIGDIALOG_H
