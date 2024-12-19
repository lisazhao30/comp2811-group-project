#pragma once

#include <QFont>
#include <QTableView>
#include <QFontDatabase>
#include <QLineEdit>
#include <QWidget>
#include "page.hpp"
#include "../table_model.hpp"

class HelpPage: public Page {

public:
    HelpPage(WaterSampleTableModel* model, QWidget* parent = nullptr);
};