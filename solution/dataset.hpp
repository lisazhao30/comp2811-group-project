#pragma once

#include <vector>
#include <QString>
#include "water_sample.hpp"

class WaterDataset
{
  public:
    WaterDataset() {}
    WaterDataset(const QString& filename) { loadData(filename); }
    void loadData(const QString&);
    int size() const { return data.size(); }
    WaterSample operator[](int index) const { return data.at(index); }

  private:
    std::vector<WaterSample> data;
    void checkDataExists() const;
};
