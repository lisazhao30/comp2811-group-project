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
#include "../pollutant_scatter_chart.hpp"

class ComplianceDashboardPage: public Page {
    Q_OBJECT // Q_OBJECT required for signals

public:
    ComplianceDashboardPage(WaterSampleTableModel* model, QWidget* parent = nullptr);
    
public slots:
    void modelUpdated();

private:
    QLineEdit* filterPollutantInput;
    QLineEdit* filterLocationInput;
    QSortFilterProxyModel* filterProxyModel;
    CustomProxyModel* customProxyModel;
    PollutantScatterChart* nitrateScatterChart;
    PollutantScatterChart* phosphateScatterChart;
    PollutantScatterChart* pcbsScatterChart;
    PollutantScatterChart* fluorinatedScatterChart;


private slots:
    void applyFilter(const QString& text);
    void applyLocationFilter(const QString& text);
};
