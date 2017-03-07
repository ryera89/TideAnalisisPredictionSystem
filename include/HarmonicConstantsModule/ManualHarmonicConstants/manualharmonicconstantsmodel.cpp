#include "manualharmonicconstantsmodel.h"


ManualHarmonicConstantsModel::ManualHarmonicConstantsModel(QObject *parent):QAbstractTableModel(parent)
{
    m_headers << "Componente" << "V. Angular[°/h]" << "Amplitud[m]" << "Fase[°]";

    m_data = QVector<HarmonicConstant>(60,HarmonicConstant());
}

ManualHarmonicConstantsModel::ManualHarmonicConstantsModel(const QVector<HarmonicConstant> &datos, QObject *parent):QAbstractTableModel(parent),
    m_data(datos)

{
    m_headers << "Componente" << "V. Angular[°/h]" << "Amplitud[m]" << "Fase[°]";
}

int ManualHarmonicConstantsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_data.size();
}

int ManualHarmonicConstantsModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 4;
}

QVariant ManualHarmonicConstantsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();

    if (role == Qt::TextAlignmentRole){
        return int(Qt::AlignVCenter | Qt::AlignRight);
    }else{
        if (role == Qt::DisplayRole){
            switch (index.column()) {
            case 0:
                return m_data.at(index.row()).name();
            case 1:
                return m_data.at(index.row()).frequency();
            case 2:
                return m_data.at(index.row()).amplitud();
            case 3:
                return m_data.at(index.row()).phase();
            default:
                return QVariant();
            }

        }
    }
    return QVariant();
}

QVariant ManualHarmonicConstantsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::TextAlignmentRole){
        return int(Qt::AlignCenter);
    }else{
        if (role == Qt::DisplayRole){
            if (orientation == Qt::Horizontal){
                return m_headers.at(section);
            }
            if (orientation == Qt::Vertical){
                return section + 1;
            }
        }

    }

    return QVariant();
}

bool ManualHarmonicConstantsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole){
        switch (index.column()) {
        case 2:
            m_data[index.row()].setAmplitud(value.toDouble());
            return true;
        case 3:
            m_data[index.row()].setPhase(value.toDouble());
            return true;
        default:
            return false;
        }
    }
    return false;
}

Qt::ItemFlags ManualHarmonicConstantsModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    if (index.column() == 2 || index.column() == 3)
        flags |= Qt::ItemIsEditable;

    return flags;
}

QVector<HarmonicConstant> ManualHarmonicConstantsModel::allData() const
{
    return m_data;
}

void ManualHarmonicConstantsModel::setAllData(const QVector<HarmonicConstant> &datos)
{
    beginResetModel();
    m_data = datos;
    endResetModel();
}
