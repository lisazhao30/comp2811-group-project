#pragma once

#include <QWidget>
#include <QMovie>
#include "page.hpp"

class FluorinatedCompoundsPage: public Page {
    public:
        FluorinatedCompoundsPage(WaterSampleTableModel* model, QWidget* parent = nullptr);
};
