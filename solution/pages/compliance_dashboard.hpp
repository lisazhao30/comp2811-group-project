#pragma once

#include <QWidget>
#include "page.hpp"

class ComplianceDashboardPage: public Page {
    public:
        ComplianceDashboardPage(WaterSampleTableModel* model, QWidget* parent = nullptr);
};
