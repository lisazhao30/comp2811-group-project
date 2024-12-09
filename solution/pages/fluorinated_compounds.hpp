#pragma once

#include <QWidget>
#include "page.hpp"

class FluorinatedCompoundsPage: public Page {
    public:
        FluorinatedCompoundsPage(WaterSampleTableModel* model, QWidget* parent = nullptr);
};
