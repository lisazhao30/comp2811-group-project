#pragma once

#include <string>
#include <iostream>
#include <chrono>

enum ResultQualifierNotation {
  Empty,
  LessThan,
  GreaterThan
};

class WaterSample
{
  public:
    WaterSample(
      const std::string&,
      const std::string&,
      const std::string&,
      const std::string&,
      const std::string&,
      const std::string&,
      const std::string&,
      int16_t,
      ResultQualifierNotation,
      double,
      const std::string&,
      const std::string&,
      bool,
      const std::string&,
      int32_t,
      int32_t
    );

    std::string get_id() const { return id; }
    std::string get_sampling_point() const { return sampling_point; }
    std::string get_sampling_point_notation() const { return sampling_point_notation; }
    std::string get_sampling_point_label() const { return sampling_point_label; }
    std::time_t get_sample_date_time() const { return sample_date_time; }
    std::string get_sample_date_time_string() const {
      return std::asctime(std::localtime(&sample_date_time));
    }
    std::string get_determinand_label() const { return determinand_label; }
    std::string get_determinand_definition() const { return determinand_definition; }
    int16_t get_determinand_notation() const { return determinand_notation; }
    ResultQualifierNotation get_result_qualifier_notation() const { return result_qualifier_notation; }
    double get_result() const { return result; }
    std::string get_determinand_unit_label() const { return determinand_unit_label; }
    std::string get_sampled_material_type_label() const { return sampled_material_type_label; }
    bool get_is_compliance_sample() const { return is_compliance_sample; }
    std::string get_sample_purpose_label() const { return sample_purpose_label; }
    int32_t get_sampling_point_easting() const { return sampling_point_easting; }
    int32_t get_sampling_point_northing() const { return sampling_point_northing; }

  private:
    std::string id;
    std::string sampling_point;
    std::string sampling_point_notation;
    std::string sampling_point_label;
    std::time_t sample_date_time;
    std::string determinand_label;
    std::string determinand_definition;
    int16_t determinand_notation; // Largest number in dataset is 9993, store with 16 bits
    ResultQualifierNotation result_qualifier_notation;
    double result;
    // skip codedResultInterpretation.interpretation, it is empty
    std::string determinand_unit_label;
    std::string sampled_material_type_label;
    bool is_compliance_sample;
    std::string sample_purpose_label;
    int32_t sampling_point_easting; // Largest number in dataset is 657400, store with 32 bits
    int32_t sampling_point_northing; // Largets number in dataset is 658000, store with 32 bits
};

std::ostream& operator << (std::ostream&, const WaterSample&);
