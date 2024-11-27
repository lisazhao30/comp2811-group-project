#include <stdexcept>
#include <algorithm>
#include <numeric>
#include "dataset.hpp"
#include "csv.hpp"

using namespace std;


void WaterDataset::loadData(const string& filename)
{
  csv::CSVReader reader(filename);
  data.clear();

  for (const auto& row: reader) {
    ResultQualifierNotation result_qualifier_notation = ResultQualifierNotation::Empty;
    std::string result_qualifier_string = row["resultQualifier.notation"].get<>();

    if (result_qualifier_string == "<") {
      result_qualifier_notation = ResultQualifierNotation::LessThan;
    }
    else if (result_qualifier_string == ">") {
      result_qualifier_notation = ResultQualifierNotation::GreaterThan;
    }

    bool is_compliance_sample = row["sample.isComplianceSample"].get<>() == "true";

    WaterSample water_sample{
      row["@id"].get<>(),
      row["sample.samplingPoint"].get<>(),
      row["sample.samplingPoint.notation"].get<>(),
      row["sample.samplingPoint.label"].get<>(),
      row["sample.sampleDateTime"].get<>(),
      row["determinand.label"].get<>(),
      row["determinand.definition"].get<>(),
      row["determinand.notation"].get<int16_t>(),
      result_qualifier_notation,
      row["result"].get<double>(),
      row["determinand.unit.label"].get<>(),
      row["sample.sampledMaterialType.label"].get<>(),
      is_compliance_sample,
      row["sample.purpose.label"].get<>(),
      row["sample.samplingPoint.easting"].get<int32_t>(),
      row["sample.samplingPoint.northing"].get<int32_t>()
    };
    data.push_back(water_sample);
  }
}


void WaterDataset::checkDataExists() const
{
  if (size() == 0) {
    throw std::runtime_error("Dataset is empty!");
  }
}
