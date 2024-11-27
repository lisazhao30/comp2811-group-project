#pragma once

#include <vector>
#include "water_sample.hpp"

class WaterDataset
{
  public:
    WaterDataset() {}
    WaterDataset(const std::string& filename) { loadData(filename); }
    void loadData(const std::string&);
    int size() const { return data.size(); }
    WaterSample operator[](int index) const { return data.at(index); }

  private:
    std::vector<WaterSample> data;
    void checkDataExists() const;
};
