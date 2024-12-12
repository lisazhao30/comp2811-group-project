#pragma once

#include <QWidget>
#include <QMovie>
#include <QFont>
#include <QTableView>
#include <QSortFilterProxyModel>
#include <QFontDatabase>
#include <QLineEdit>
#include "page.hpp"
#include "../table_model.hpp"

class EnvironmentalLitterIndicatorsPage: public Page {
    Q_OBJECT

    public:
        EnvironmentalLitterIndicatorsPage(WaterSampleTableModel* model, QWidget* parent = nullptr);
    
    private:
        QLineEdit* filterLocationInput;
        QLineEdit* filterWaterBodyTypeInput;
        QSortFilterProxyModel* filterProxyModel;

    private slots:
        void applyLocationFilter(const QString& text);
        void applyWaterBodyTypeFilter(const QString& text);
};
