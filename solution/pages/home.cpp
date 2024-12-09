#include "home.hpp"

HomePage::HomePage(WaterSampleTableModel* model, QWidget* parent): Page(model, parent) {
    pageLayout->setAlignment(Qt::AlignCenter);
    pageLayout->setContentsMargins(0, 0, 0, 0);
    pageLayout->setSpacing(0);

    // add text
    addHeaderText("Spot the Trends, Shape the Future:\nWater Quality Insights at Your Fingertips");

    // add chart
    chart = new PollutantTrendLineChart("Nitrate-N", model);
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    addWidget(chartView);
}

void HomePage::modelUpdated() {
    auto series = chart->series().at(0);
    // Refreshes the chart, probably shouldn't need this, bug?
    chart->removeSeries(series);
    chart->addSeries(series);
    
    chart->setAxes();
}
