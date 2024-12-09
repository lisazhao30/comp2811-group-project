#pragma once

#include <QWidget>
#include "page.hpp"

class PersistentOrganicPollutantsPage: public Page {
    public:
        PersistentOrganicPollutantsPage(WaterSampleTableModel* model, QWidget* parent = nullptr);
};
