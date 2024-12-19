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

class EnvironmentalLitterIndicatorsPage: public Page {
    Q_OBJECT

public:
    EnvironmentalLitterIndicatorsPage(WaterSampleTableModel* model, QWidget* parent = nullptr);
    
public slots:
    void modelUpdated();
    
private:
    QLineEdit* filterLocationInput;
    QLineEdit* filterWaterBodyTypeInput;
    CustomProxyModel* customProxyModel;
    PollutantTrendLineChart* chart;

private slots:
    void applyLocationFilter(const QString& text);
    void applyWaterBodyTypeFilter(const QString& text);
};
