#pragma once

#include <QWidget>
#include <QMovie>
#include <QPixmap>
#include <QChart>
#include <QChartView>
#include <QFont>
#include <QTableView>
#include <QSortFilterProxyModel>
#include <QFontDatabase>
#include <QLineEdit>
#include <QDateEdit>
#include "page.hpp"
#include "../pollutant_line_chart.hpp"
#include "../custom_proxy_model.hpp"

class HomePage: public Page {
    Q_OBJECT

public:
    HomePage(WaterSampleTableModel* model, QWidget* parent = nullptr);
    QLabel *fromLabel;
    QLabel *toLabel;
    QLineEdit *filterPatternLineEdit;
    QDateEdit *fromDateEdit;
    QDateEdit *toDateEdit;
    CustomProxyModel* customProxyModel;
    
public slots:
    void modelUpdated();

private:
    QLineEdit* filterLocationInput;
    PollutantTrendLineChart* chart1;
    PollutantTrendLineChart* chart2;
    PollutantTrendLineChart* chart3;
    PollutantTrendLineChart* chart4;
    
private slots:
    void applyLocationFilter(const QString& text);
    void dateFilterChanged();
};
