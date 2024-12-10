#include <stdexcept>
#include <algorithm>
#include <numeric>
#include "dataset.hpp"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>

using namespace std;

void WaterDataset::loadData(const QString& filename)
{
  if (!QFile::exists(filename)) {
    throw std::runtime_error("Database file does not exist: " + filename.toStdString());
  }

  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(filename);

  if (!db.open()) {
    throw std::runtime_error(db.lastError().text().toStdString());
  }

  data.clear();

  QSqlQuery query;
  query.exec("SELECT * FROM water_samples");

  while (query.next()) {
    ResultQualifierNotation result_qualifier_notation = ResultQualifierNotation::Empty;
    QString result_qualifier_string = query.value("resultQualifier.notation").toString();

    if (result_qualifier_string == "<") {
      result_qualifier_notation = ResultQualifierNotation::LessThan;
    }
    else if (result_qualifier_string == ">") {
      result_qualifier_notation = ResultQualifierNotation::GreaterThan;
    }

    bool is_compliance_sample = query.value("sample.isComplianceSample").toString() == "true";

    WaterSample water_sample{
      query.value("@id").toString(),
      query.value("sample.samplingPoint").toString(),
      query.value("sample.samplingPoint.notation").toString(),
      query.value("sample.samplingPoint.label").toString(),
      query.value("sample.sampleDateTime").toString(),
      query.value("determinand.label").toString(),
      query.value("determinand.definition").toString(),
      query.value("determinand.notation").toInt(),
      result_qualifier_notation,
      query.value("result").toDouble(),
      query.value("determinand.unit.label").toString(),
      query.value("sample.sampledMaterialType.label").toString(),
      is_compliance_sample,
      query.value("sample.purpose.label").toString(),
      query.value("sample.samplingPoint.easting").toInt(),
      query.value("sample.samplingPoint.northing").toInt()
    };
    data.push_back(water_sample);
  }

  db.close();
}


void WaterDataset::checkDataExists() const
{
  if (size() == 0) {
    throw std::runtime_error("Dataset is empty!");
  }
}
