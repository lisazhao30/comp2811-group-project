#include <stdexcept>
#include <sstream>
#include "water_sample.hpp"
#include <iomanip>

using namespace std;

WaterSample::WaterSample(
    const QString& id,
    const QString& sampling_point,
    const QString& sampling_point_notation,
    const QString& sampling_point_label,
    const QString& sample_date_time,
    const QString& determinand_label,
    const QString& determinand_definition,
    int determinand_notation,
    ResultQualifierNotation result_qualifier_notation,
    double result,
    const QString& determinand_unit_label,
    const QString& sampled_material_type_label,
    bool is_compliance_sample,
    const QString& sample_purpose_label,
    int sampling_point_easting,
    int sampling_point_northing
    ):
    id(id), sampling_point(sampling_point), sampling_point_notation(sampling_point_notation),
    sampling_point_label(sampling_point_label), determinand_label(determinand_label),
    determinand_definition(determinand_definition), determinand_notation(determinand_notation),
    result_qualifier_notation(result_qualifier_notation), result(result),
    determinand_unit_label(determinand_unit_label), sampled_material_type_label(sampled_material_type_label),
    is_compliance_sample(is_compliance_sample), sample_purpose_label(sample_purpose_label),
    sampling_point_easting(sampling_point_easting), sampling_point_northing(sampling_point_northing)
{
    this->sample_date_time = QDateTime::fromString(sample_date_time, "yyyy-MM-ddTHH:mm:ss");
}

ostream& operator<<(ostream& out, const WaterSample& water_sample)
{
    return out << "WaterSample(" << water_sample.get_id().toStdString() << ", " << water_sample.get_sampling_point().toStdString() << ", "
               << water_sample.get_sampling_point_notation().toStdString() << ", " << water_sample.get_sampling_point_label().toStdString() << ", "
               << water_sample.get_sample_date_time_string().toStdString() << ", " << water_sample.get_determinand_label().toStdString() << ", "
               << water_sample.get_determinand_definition().toStdString() << ", " << water_sample.get_determinand_notation() << ", "
               << water_sample.get_result_qualifier_notation() << ", " << water_sample.get_result() << ", "
               << water_sample.get_determinand_unit_label().toStdString() << ", " << water_sample.get_sampled_material_type_label().toStdString() << ", "
               << water_sample.get_is_compliance_sample() << ", " << water_sample.get_sample_purpose_label().toStdString() << ", "
               << water_sample.get_sampling_point_easting() << ", " << water_sample.get_sampling_point_northing() << ")";
}
