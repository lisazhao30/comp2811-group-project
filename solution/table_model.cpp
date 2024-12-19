#include "table_model.hpp"
#include <QModelIndex>

void WaterSampleTableModel::updateFromFile(const QString& filename)
{
    beginResetModel();
    dataset.loadData(filename);
    endResetModel();
}


QVariant WaterSampleTableModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignRight | Qt::AlignVCenter);
    }

    else if (role == Qt::DisplayRole) {
        WaterSample ws = dataset[index.row()];

        switch (index.column()) {
        case 0: return QVariant(ws.get_id());
        case 1: return QVariant(ws.get_sampling_point());
        case 2: return QVariant(ws.get_sampling_point_notation());
        case 3: return QVariant(ws.get_sampling_point_label());
        case 4: return QVariant(ws.get_sample_date_time());
        case 5: return QVariant(ws.get_determinand_label());
        case 6: return QVariant(ws.get_determinand_definition());
        case 7: return QVariant(ws.get_determinand_notation());
        case 8: return QVariant(ws.get_result_qualifier_notation());
        case 9: return QVariant(ws.get_result());
        case 10: return QVariant(ws.get_determinand_unit_label());
        case 11: return QVariant(ws.get_sampled_material_type_label());
        case 12: return QVariant(ws.get_is_compliance_sample());
        case 13: return QVariant(ws.get_sample_purpose_label());
        case 14: return QVariant(ws.get_sampling_point_easting());
        case 15: return QVariant(ws.get_sampling_point_northing());
        }
    }

    return QVariant();
}


QVariant WaterSampleTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Vertical) {
        return QVariant(section + 1);
    }

    switch (section) {
    case 0: return QString(tr("ID"));
    case 1: return QString(tr("Sampling Point"));
    case 2: return QString(tr("Sampling Point Notation"));
    case 3: return QString(tr("Sampling Point Label"));
    case 4: return QString(tr("Sample Date Time"));
    case 5: return QString(tr("Determinand Label"));
    case 6: return QString(tr("Determinand Definition"));
    case 7: return QString(tr("Determinand Notation"));
    case 8: return QString(tr("Result Qualifier Notation"));
    case 9: return QString(tr("Result"));
    case 10: return QString(tr("Determinand Unit Label"));
    case 11: return QString(tr("Sampled Material Type Label"));
    case 12: return QString(tr("Is Compliance Sample"));
    case 13: return QString(tr("Sample Purpose Label"));
    case 14: return QString(tr("Sampling Point Easting"));
    case 15: return QString(tr("Sampling Point Northing"));
    default: return QVariant();
    }
}

QVariant WaterSampleTableTimeSinceEpochProxy::data(const QModelIndex& index, int role) const
{
    QModelIndex sourceIndex = mapToSource(index);
    QVariant value = sourceModel()->data(sourceIndex, role);

    if (index.column() == 4) {
        return QVariant(value.toDateTime().toMSecsSinceEpoch());
    }

    return value;
}
