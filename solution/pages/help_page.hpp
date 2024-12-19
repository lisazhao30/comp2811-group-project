#pragma once

#include "page.hpp"

class HelpPage: public Page {

public:
    HelpPage(WaterSampleTableModel* model, QWidget* parent = nullptr);
};