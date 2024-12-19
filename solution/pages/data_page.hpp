#pragma once

#include <QFont>
#include <QTableView>
#include <QSortFilterProxyModel>
#include <QFontDatabase>
#include <QWidget>
#include <QLineEdit>
#include "page.hpp"
#include "../table_model.hpp"

class DataPage: public Page {
    Q_OBJECT

public:
    DataPage(WaterSampleTableModel* model, QWidget* parent = nullptr);
    
private:
    QLineEdit* filterInput;
    QSortFilterProxyModel* filterProxyModel;
    
private slots:
    void applyFilter(const QString& text);
};
