#include "harmonicconstantfulltablemodel.h"

HarmonicConstantFullTableModel::HarmonicConstantFullTableModel(QObject *parent):QAbstractTableModel(parent)
{
    m_headers << "Componente" << "Velocidad Angular" << "C" << "S" << "Amplitud" << "fase";

    m_data = QVector<HarmonicConstant>(28,HarmonicConstant());
}

HarmonicConstantFullTableModel::HarmonicConstantFullTableModel(const QVector<HarmonicConstant> &datos, QObject *parent):QAbstractTableModel(parent),
    m_data(datos)
{
    m_headers << "Componente" << "Velocidad Angular" << "C" << "S" << "Amplitud" << "fase";

}

int HarmonicConstantFullTableModel::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

int HarmonicConstantFullTableModel::columnCount(const QModelIndex &parent) const
{
    return 6;
}

QVariant HarmonicConstantFullTableModel::data(const QModelIndex &index, int role) const
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
                return m_data.at(index.row()).cosComponent();
            case 3:
                return m_data.at(index.row()).senComponent();
            case 4:
                return m_data.at(index.row()).amplitud();
            case 5:
                return m_data.at(index.row()).phase();
            default:
                return QVariant();
            }

        }
    }
    return QVariant();
}

QVariant HarmonicConstantFullTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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

QVector<HarmonicConstant> HarmonicConstantFullTableModel::allData() const
{
    return m_data;
}

void HarmonicConstantFullTableModel::setAllData(const QVector<HarmonicConstant> &datos)
{
    beginResetModel();
    m_data = datos;
    endResetModel();
}
