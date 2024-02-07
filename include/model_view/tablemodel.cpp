#include "tablemodel.h"

TableModel::TableModel(QObject *parent) : QAbstractTableModel(parent) {
  headers << "Fecha"
          << "Hora"
          << "Nivel [m]";
}

int TableModel::rowCount(const QModelIndex & /*parent*/) const {
  return measurements.size();
}

int TableModel::columnCount(const QModelIndex & /*parent*/) const { return 3; }

QVariant TableModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();

  if (role == Qt::TextAlignmentRole) {
    return int(Qt::AlignVCenter | Qt::AlignRight);
  } else {
    if (role == Qt::DisplayRole) {
      switch (index.column()) {
      case 0:
        return measurements[index.row()].measurementDate();
      case 1:
        return measurements[index.row()].measurementTime();
      case 2:
        return measurements[index.row()].seaLevel();
      default:
        return QVariant();
      }
    }
  }
  return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation,
                                int role) const {
  if (role == Qt::DisplayRole) {
    if (orientation == Qt::Horizontal) {
      return headers[section];
    }
    if (orientation == Qt::Vertical) {
      return section + 1;
    }
  }

  return QVariant();
}
bool TableModel::setData(const QModelIndex &index, const QVariant &value,
                         int role) {
  if (index.isValid() && role == Qt::EditRole) {
    switch (index.column()) {
    case 0:
      measurements[index.row()].setMeasurementDate(value.toDate());
      emit dataChanged(index, index);
      return true;
    case 1:
      measurements[index.row()].setMeasurementTime(value.toTime());
      emit dataChanged(index, index);
      return true;
    case 2:
      measurements[index.row()].setSeaLevel(value.toDouble());
      emit dataChanged(index, index);
      return true;
    default:
      return false;
    }
  }
  return false;
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const {
  Qt::ItemFlags flags = QAbstractItemModel::flags(index);
  flags |= Qt::ItemIsEditable;
  return flags;
}

bool TableModel::insertRows(int row, int count, const QModelIndex &parent) {
  beginInsertRows(parent, row, row + count - 1);
  for (int i = 0; i < count; ++i) {
    measurements.insert(row, TidesMeasurement(0.0, QDate(), QTime()));
    ++row;
  }
  endInsertRows();
  return true;
}

bool TableModel::insertRow(int row, const QModelIndex &parent) {
  beginInsertRows(parent, row, row);
  measurements.insert(row, TidesMeasurement(0.0, QDate(), QTime()));
  endInsertRows();
  return true;
}

bool TableModel::removeRows(int row, int count, const QModelIndex &parent) {
  // if (!parent.isValid()) return false;
  // int r = row;

  beginRemoveRows(parent, row, row + count);
  measurements.remove(row, count + 1);
  endRemoveRows();
  return true;
}

bool TableModel::removeRow(int row, const QModelIndex &parent) {
  // if (!parent.isValid()) return false;

  beginRemoveRows(parent, row, row);
  measurements.remove(row);
  endRemoveRows();
  return true;
}

void TableModel::setMeasurements(const QVector<TidesMeasurement> &measurement) {
  beginResetModel();
  measurements.clear();
  foreach (const TidesMeasurement &meas, measurement) {
    if (meas.isValid())
      measurements.push_back(meas);
  }
  endResetModel();
}

QVector<QPointF> TableModel::measurementDataRealPoints() const {
  QVector<QPointF> points;
  foreach (TidesMeasurement m, measurements) {
    qint64 x = m.measurementDateTime().toMSecsSinceEpoch();

    QPointF point(x, m.seaLevel());
    points.append(point);
  }
  return points;
}
