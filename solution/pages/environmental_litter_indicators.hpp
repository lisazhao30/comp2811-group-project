#pragma once

#include <QWidget>
#include "page.hpp"

class EnvironmentalLitterIndicatorsPage: public Page {
    public:
        EnvironmentalLitterIndicatorsPage(WaterSampleTableModel* model, QWidget* parent = nullptr);
};
