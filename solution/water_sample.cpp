#include <stdexcept>
#include <sstream>
#include "water_sample.hpp"
#include <iomanip>

using namespace std;


WaterSample::WaterSample(
  const std::string& id,
  const std::string& sampling_point,
  const std::string& sampling_point_notation,
  const std::string& sampling_point_label,
  const std::string& sample_date_time,
  const std::string& determinand_label,
  const std::string& determinand_definition,
  int16_t determinand_notation,
  ResultQualifierNotation result_qualifier_notation,
  double result,
  const std::string& determinand_unit_label,
  const std::string& sampled_material_type_label,
  bool is_compliance_sample,
  const std::string& sample_purpose_label,
  int32_t sampling_point_easting,
  int32_t sampling_point_northing
):
  id(id), sampling_point(sampling_point), sampling_point_notation(sampling_point_notation),
  sampling_point_label(sampling_point_label), determinand_label(determinand_label),
  determinand_definition(determinand_definition), determinand_notation(determinand_notation),
  result_qualifier_notation(result_qualifier_notation), result(result),
  determinand_unit_label(determinand_unit_label), sampled_material_type_label(sampled_material_type_label),
  is_compliance_sample(is_compliance_sample), sample_purpose_label(sample_purpose_label),
  sampling_point_easting(sampling_point_easting), sampling_point_northing(sampling_point_northing)
{
  std::tm tm = {};
  istringstream ss(sample_date_time);
  ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%S");

  if (ss.fail()) {
    throw invalid_argument("Invalid date time format");
  }

  this->sample_date_time = QDateTime::fromString(QString::fromStdString(sample_date_time), "yyyy-MM-ddTHH:mm:ss");
}

ostream& operator<<(ostream& out, const WaterSample& water_sample)
{
  return out << "WaterSample(" << water_sample.get_id() << ", " << water_sample.get_sampling_point() << ", "
    << water_sample.get_sampling_point_notation() << ", " << water_sample.get_sampling_point_label() << ", "
    << water_sample.get_sample_date_time_string() << ", " << water_sample.get_determinand_label() << ", "
    << water_sample.get_determinand_definition() << ", " << water_sample.get_determinand_notation() << ", "
    << water_sample.get_result_qualifier_notation() << ", " << water_sample.get_result() << ", "
    << water_sample.get_determinand_unit_label() << ", " << water_sample.get_sampled_material_type_label() << ", "
    << water_sample.get_is_compliance_sample() << ", " << water_sample.get_sample_purpose_label() << ", "
    << water_sample.get_sampling_point_easting() << ", " << water_sample.get_sampling_point_northing() << ")";
}
