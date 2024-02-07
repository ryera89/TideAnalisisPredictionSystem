#ifndef MYCOORDINATESEDITORWIDGET_H
#define MYCOORDINATESEDITORWIDGET_H

#include <QComboBox>
#include <QDoubleSpinBox>
#include <QFrame>

class MyCoordinatesEditorWidget : public QFrame {
  Q_OBJECT
  Q_PROPERTY(double coordinate READ coordinate WRITE setCoordinate NOTIFY
                 coordinateChanged)
  Q_PROPERTY(HemisphereType hType READ hType WRITE setHType NOTIFY hTypeChanged)
public:
  MyCoordinatesEditorWidget(QWidget *parent = 0);
  ~MyCoordinatesEditorWidget();

  enum HemisphereType { latitud, longitud };

  double coordinate() const;
  HemisphereType hType() const;

public slots:
  void setHType(HemisphereType hType);
  void setEditorAndComboValue(double value);

signals:
  void coordinateChanged(double coordinate);
  void hTypeChanged(HemisphereType hType);

private slots:
  void setHemisphereComboBoxItems(HemisphereType hType);
  void setCoordinate(double coordinate);

  void setHemisphere(int);

private:
  // const QString dmsMask = "00° 00' 00'';_";
  // const QString dmMask = "00° 00x000';_";

  QComboBox *m_HemisphereComboBox;
  QDoubleSpinBox *m_coordinatesSpinBox;

  QStringList m_comboItems;

  double m_coordinate;
  int m_type;
  HemisphereType m_hType;
};

#endif // MYCOORDINATESEDITORWIDGET_H
