#pragma once

#include <QWidget>
#include <QChart>
#include <QChartView>
#include "page.hpp"
#include "../pollutant_line_chart.hpp"

class HomePage: public Page {
    Q_OBJECT

    public:
        HomePage(WaterSampleTableModel* model, QWidget* parent = nullptr);
    
    public slots:
        void modelUpdated();

    private:
        PollutantTrendLineChart* chart;
        QChartView* chartView;
};
