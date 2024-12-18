#pragma once

#include <QWidget>
#include <QMovie>
#include <QFont>
#include <QTableView>
#include <QSortFilterProxyModel>
#include <QFontDatabase>
#include <QLineEdit>
#include <QChart>
#include <QChartView>
#include <QFont>
#include "page.hpp"
#include "../table_model.hpp"
#include "../custom_proxy_model.hpp"
#include "../pollutant_line_chart.hpp"

class PollutantOverviewPage: public Page {
    Q_OBJECT // Q_OBJECT required for signals

    public:
        PollutantOverviewPage(WaterSampleTableModel* model, QWidget* parent = nullptr);

    public slots:
        void modelUpdated();

    private:
        QLineEdit* filterPollutantInput;
        QSortFilterProxyModel* filterProxyModel;
        CustomProxyModel* customProxyModel;
        PollutantTrendLineChart* chart;

    private slots:
        void applyFilter(const QString& text);
};
