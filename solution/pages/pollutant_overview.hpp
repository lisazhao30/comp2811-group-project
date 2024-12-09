#pragma once

#include <QWidget>
#include "page.hpp"

class PollutantOverviewPage: public Page {
    public:
        PollutantOverviewPage(WaterSampleTableModel* model, QWidget* parent = nullptr);
};
