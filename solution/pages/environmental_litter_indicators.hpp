#pragma once

#include <QWidget>
#include <QMovie>
#include "page.hpp"

class EnvironmentalLitterIndicatorsPage: public Page {
    public:
        EnvironmentalLitterIndicatorsPage(WaterSampleTableModel* model, QWidget* parent = nullptr);
};
