#include "model.hpp"

void WaterSampleModel::updateFromFile(const QString& filename)
{
  beginResetModel();
  dataset.loadData(filename.toStdString());
  endResetModel();
}


QVariant WaterSampleModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid()) {
    return QVariant();
  }

  if (role == Qt::TextAlignmentRole) {
    return int(Qt::AlignRight | Qt::AlignVCenter);
  }
  else if (role == Qt::DisplayRole) {
    WaterSample ws = dataset[index.row()];
    // TODO: do we want all columns to be displayed?
    switch (index.column()) {
      case 0: return QVariant(ws.get_id().c_str());
      case 1: return QVariant(ws.get_sampling_point().c_str());
      case 2: return QVariant(ws.get_sampling_point_notation().c_str());
      case 3: return QVariant(ws.get_sampling_point_label().c_str());
      case 4: return QVariant(ws.get_sample_date_time_string().c_str()); // TODO: add method to get string representation of string
      case 5: return QVariant(ws.get_determinand_label().c_str());
      case 6: return QVariant(ws.get_determinand_definition().c_str());
      case 7: return QVariant(ws.get_determinand_notation());
      case 8: return QVariant(ws.get_result_qualifier_notation());
      case 9: return QVariant(ws.get_result());
      case 10: return QVariant(ws.get_determinand_unit_label().c_str());
      case 11: return QVariant(ws.get_sampled_material_type_label().c_str());
      case 12: return QVariant(ws.get_is_compliance_sample());
      case 13: return QVariant(ws.get_sample_purpose_label().c_str());
      case 14: return QVariant(ws.get_sampling_point_easting());
      case 15: return QVariant(ws.get_sampling_point_northing());
    }
  }

  return QVariant();
}


QVariant WaterSampleModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role != Qt::DisplayRole) {
    return QVariant();
  }

  if (orientation == Qt::Vertical) {
    return QVariant(section + 1);
  }

  switch (section) {
    case 0: return QString("ID");
    case 1: return QString("Sampling Point");
    case 2: return QString("Sampling Point Notation");
    case 3: return QString("Sampling Point Label");
    case 4: return QString("Sample Date Time");
    case 5: return QString("Determinand Label");
    case 6: return QString("Determinand Definition");
    case 7: return QString("Determinand Notation");
    case 8: return QString("Result Qualifier Notation");
    case 9: return QString("Result");
    case 10: return QString("Determinand Unit Label");
    case 11: return QString("Sampled Material Type Label");
    case 12: return QString("Is Compliance Sample");
    case 13: return QString("Sample Purpose Label");
    case 14: return QString("Sampling Point Easting");
    case 15: return QString("Sampling Point Northing");
    default: return QVariant();
  }
}
