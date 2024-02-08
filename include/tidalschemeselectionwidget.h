#ifndef TIDALSCHEMESELECTIONWIDGET_H
#define TIDALSCHEMESELECTIONWIDGET_H

#include <QWidget>

class QCheckBox;
class QGroupBox;
class QComboBox;
class QVBoxLayout;

class TidalSchemeSelectionWidget : public QWidget {
  Q_OBJECT

public:
  explicit TidalSchemeSelectionWidget(const QStringList &componentLabels,
                                      QWidget *parent = 0);
  ~TidalSchemeSelectionWidget() {}

  QVector<QCheckBox *> componentsCheckBoxes() const {
    return m_componentsCheckBoxes;
  }
  void setCheckBoxesEnabledStatus(bool enable);

signals:
  void checkBoxStatusChanged(const QString &label, bool checked);

public slots:
  void setCheckBoxesStatus(
      const QMap<QString, bool>
          &componentStatusMap); // For change the check status of the checkBoxes
  void changingCheckBoxStatus(int i);

private:
  QVBoxLayout *m_checkBoxLayout;
  QVector<QCheckBox *> m_componentsCheckBoxes;

  // bool readFile(const QString &filePath);
  void createComponentsCheckBoxes(const QStringList &labels);

  // QCheckBox *componentCheckBoxes;   //checkeable box para las componentes de
  // marea
};

#endif // TIDALSCHEMESELECTIONWIDGET_H
