#pragma once

#include <QWidget>
#include <QMovie>
#include <QFont>
#include <QTableView>
#include <QFontDatabase>
#include "page.hpp"
#include <QChart>
#include <QChartView>
#include <QFont>
#include "../table_model.hpp"
#include "../custom_proxy_model.hpp"
#include "../pollutant_line_chart.hpp"

class FluorinatedCompoundsPage: public Page {
    public:
        FluorinatedCompoundsPage(WaterSampleTableModel* model, QWidget* parent = nullptr);
    
    public slots:
        void modelUpdated();

    private:
        QLineEdit* filterPollutantInput;
        CustomProxyModel* customFluorinatedProxyModel;
        PollutantTrendLineChart* chart;

    private slots:
        void applyFilter(const QString& text);
};
