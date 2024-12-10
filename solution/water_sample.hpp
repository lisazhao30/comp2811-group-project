#pragma once

#include <QString>
#include <QDateTime>
#include <iostream>

enum ResultQualifierNotation {
  Empty,
  LessThan,
  GreaterThan
};

class WaterSample
{
  public:
    WaterSample(
      const QString&,
      const QString&,
      const QString&,
      const QString&,
      const QString&,
      const QString&,
      const QString&,
      int,
      ResultQualifierNotation,
      double,
      const QString&,
      const QString&,
      bool,
      const QString&,
      int,
      int
    );

    QString get_id() const { return id; }
    QString get_sampling_point() const { return sampling_point; }
    QString get_sampling_point_notation() const { return sampling_point_notation; }
    QString get_sampling_point_label() const { return sampling_point_label; }
    QDateTime get_sample_date_time() const { return sample_date_time; }
    QString get_sample_date_time_string() const {
      return sample_date_time.toString();
    }
    QString get_determinand_label() const { return determinand_label; }
    QString get_determinand_definition() const { return determinand_definition; }
    int get_determinand_notation() const { return determinand_notation; }
    ResultQualifierNotation get_result_qualifier_notation() const { return result_qualifier_notation; }
    double get_result() const { return result; }
    QString get_determinand_unit_label() const { return determinand_unit_label; }
    QString get_sampled_material_type_label() const { return sampled_material_type_label; }
    bool get_is_compliance_sample() const { return is_compliance_sample; }
    QString get_sample_purpose_label() const { return sample_purpose_label; }
    int get_sampling_point_easting() const { return sampling_point_easting; }
    int get_sampling_point_northing() const { return sampling_point_northing; }

  private:
    QString id;
    QString sampling_point;
    QString sampling_point_notation;
    QString sampling_point_label;
    QDateTime sample_date_time;
    QString determinand_label;
    QString determinand_definition;
    int determinand_notation;
    ResultQualifierNotation result_qualifier_notation;
    double result;
    QString determinand_unit_label;
    QString sampled_material_type_label;
    bool is_compliance_sample;
    QString sample_purpose_label;
    int sampling_point_easting;
    int sampling_point_northing;
};

std::ostream& operator << (std::ostream&, const WaterSample&);
