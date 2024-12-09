#pragma once

#include <QFont>
#include <QTableView>
#include <QSortFilterProxyModel>
#include <QFontDatabase>
#include <QWidget>
#include "page.hpp"
#include "../table_model.hpp"

class DataPage: public Page {
    public:
        DataPage(WaterSampleTableModel* model, QWidget* parent = nullptr);
};
