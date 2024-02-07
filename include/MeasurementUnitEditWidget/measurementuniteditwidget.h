#ifndef MEASUREMENTUNITEDITWIDGET_H
#define MEASUREMENTUNITEDITWIDGET_H

#include <QFrame>

class QDoubleSpinBox;
class QComboBox;
class MeasurementUnitEditWidget : public QFrame {
  Q_OBJECT
public:
  explicit MeasurementUnitEditWidget(QWidget *parent = Q_NULLPTR);
  enum Units { M, DM, CM, MM };

  double value() const;
  Units unit() const;
signals:
  void value_type_Changed(int index, double value);

private slots:
  void spinBoxValueChanged(double value);
  void comboBoxIndexChanged(int index);
  void setValue(int index, double value);

public slots:
  void setSpinAndComboBoxesValues(Units u, double value);

private:
  QDoubleSpinBox *m_spinBox;
  QComboBox *m_comboBox;

  double m_value;
};

#endif // MEASUREMENTUNITEDITWIDGET_H
