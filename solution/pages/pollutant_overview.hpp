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

class PollutantOverviewPage: public Page {
    Q_OBJECT // Q_OBJECT required for signals

    public:
        PollutantOverviewPage(WaterSampleTableModel* model, QWidget* parent = nullptr);

    private:
        QLineEdit* filterInput;
        QSortFilterProxyModel* filterProxyModel;

    private slots:
        void applyFilter(const QString& text);
};
