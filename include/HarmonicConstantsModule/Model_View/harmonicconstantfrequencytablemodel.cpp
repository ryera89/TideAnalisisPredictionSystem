#include "harmonicconstantfrequencytablemodel.h"

HarmonicConstantFrequencyTableModel::HarmonicConstantFrequencyTableModel(
    QObject *parent)
    : QAbstractTableModel(parent) {
  m_headers << "Componente"
            << "Velocidad Angular"
            << "Descripcion";

  m_data = QVector<HarmonicConstant>(28, HarmonicConstant());
}

HarmonicConstantFrequencyTableModel::HarmonicConstantFrequencyTableModel(
    QVector<HarmonicConstant> &datos, QObject *parent)
    : QAbstractTableModel(parent), m_data(datos) {
  m_headers << "Componente"
            << "Velocidad Angular"
            << "Descripcion";
}

int HarmonicConstantFrequencyTableModel::rowCount(
    const QModelIndex &parent) const {
  return m_data.size();
}

int HarmonicConstantFrequencyTableModel::columnCount(
    const QModelIndex &parent) const {
  return 3;
}

QVariant HarmonicConstantFrequencyTableModel::data(const QModelIndex &index,
                                                   int role) const {
  if (!index.isValid())
    return QVariant();

  switch (index.column()) {
  case 0: {
    if (role == Qt::TextAlignmentRole) {
      return int(Qt::AlignVCenter | Qt::AlignRight);
    } else {
      if (role == Qt::DisplayRole) {
        return m_data.at(index.row()).name();
      }
    }
    break;
  }
  case 1: {
    if (role == Qt::TextAlignmentRole) {
      return int(Qt::AlignVCenter | Qt::AlignRight);
    } else {
      if (role == Qt::DisplayRole) {
        return m_data.at(index.row()).frequency();
      }
    }
    break;
  }
  case 2: {
    if (role == Qt::TextAlignmentRole) {
      return int(Qt::AlignVCenter | Qt::AlignLeft);
    } else {
      if (role == Qt::DisplayRole) {
        return m_data.at(index.row()).description();
      }
    }
    break;
  }
  default:
    return QVariant();
  }

  return QVariant();
}

QVariant HarmonicConstantFrequencyTableModel::headerData(
    int section, Qt::Orientation orientation, int role) const {
  if (role == Qt::TextAlignmentRole) {
    return int(Qt::AlignCenter);
  } else {
    if (role == Qt::DisplayRole) {
      if (orientation == Qt::Horizontal) {
        return m_headers.at(section);
      }
      if (orientation == Qt::Vertical) {
        return section + 1;
      }
    }
  }

  return QVariant();
}

bool HarmonicConstantFrequencyTableModel::setData(const QModelIndex &index,
                                                  const QVariant &value,
                                                  int role) {
  if (index.isValid() && role == Qt::EditRole) {
    switch (index.column()) {
    case 0:
      m_data[index.row()].setName(value.toString());
      emit dataChanged(index, index);
      return true;
    case 1:
      m_data[index.row()].setFrequency(value.toDouble());
      emit dataChanged(index, index);
      return true;
    case 2:
      m_data[index.row()].setDescription(value.toString());
      emit dataChanged(index, index);
      return true;
    default:
      return false;
    }
  }
  return false;
}

bool HarmonicConstantFrequencyTableModel::setHeaderData(
    int section, Qt::Orientation orientation, const QVariant &value, int role) {
  if (orientation == Qt::Horizontal) {
    if (role == Qt::DisplayRole) {
      m_headers[section] = value.toString();
      emit headerDataChanged(orientation, section, section);
      return true;
    }
  } else {
    return QAbstractTableModel::setHeaderData(section, orientation, value,
                                              role);
  }
  return true;
}

Qt::ItemFlags
HarmonicConstantFrequencyTableModel::flags(const QModelIndex &index) const {
  Qt::ItemFlags flags = QAbstractItemModel::flags(index);
  flags |= Qt::ItemIsEditable;
  return flags;
}

bool HarmonicConstantFrequencyTableModel::insertRows(
    int row, int count, const QModelIndex &parent) {
  beginInsertRows(parent, row, row + count - 1);
  for (int i = 0; i < count; ++i) {
    m_data.insert(row, HarmonicConstant());
    ++row;
  }
  endInsertRows();
  return true;
}

bool HarmonicConstantFrequencyTableModel::insertRow(int row,
                                                    const QModelIndex &parent) {
  beginInsertRows(parent, row, row);
  m_data.insert(row, HarmonicConstant());
  endInsertRows();
  return true;
}

bool HarmonicConstantFrequencyTableModel::removeRows(
    int row, int count, const QModelIndex &parent) {
  beginRemoveRows(parent, row, row + count);
  for (int i = row; i <= row + count; ++i) {
    m_data.remove(row);
  }
  endRemoveRows();
  return true;
}

bool HarmonicConstantFrequencyTableModel::removeRow(int row,
                                                    const QModelIndex &parent) {
  beginRemoveRows(parent, row, row);
  m_data.remove(row);
  endRemoveRows();
  return true;
}

QVector<HarmonicConstant> HarmonicConstantFrequencyTableModel::allData() const {
  return m_data;
}

void HarmonicConstantFrequencyTableModel::setAllData(
    const QVector<HarmonicConstant> &datos) {
  beginResetModel();
  m_data = datos;
  endResetModel();
}
