#include "home.hpp"

HomePage::HomePage(WaterSampleTableModel* model, QWidget* parent): Page(model, parent) {
    pageLayout->setAlignment(Qt::AlignCenter);
    pageLayout->setContentsMargins(0, 0, 0, 0);
    pageLayout->setSpacing(0);

    // add text
    addHeaderText("Spot the Trends, Shape the Future:\nWater Quality Insights at Your Fingertips");

    // add chart
    chart = new PollutantTrendLineChart("Nitrate-N", model);
    QChartView* chartView = new QChartView(this);
    chartView->setRenderHint(QPainter::Antialiasing);
    addWidget(chartView);

    // Create a label for the page
    QLabel* label = new QLabel("Home Page", this);
    label->setAlignment(Qt::AlignCenter);
    addWidget(label);
}

void HomePage::modelUpdated() {
    auto series = chart->series().at(0);
    // Refreshes the chart, probably shouldn't need this, bug?
    chart->removeSeries(series);
    chart->addSeries(series);
    
    chart->setAxes();
}
