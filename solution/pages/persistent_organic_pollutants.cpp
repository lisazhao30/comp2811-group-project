#include "persistent_organic_pollutants.hpp"

/*
Organic pollutants: PCB Con 028
*/

PersistentOrganicPollutantsPage::PersistentOrganicPollutantsPage(WaterSampleTableModel* model, QWidget* parent): Page(model, parent) {
    addHeader2Text("Persistent Organic Pollutants:\nTracking Trends, Risks, and Compliance");

    // hero description
    QLabel* heroDescription = addParagraphText("This page displays data on pollutants like PCBs and their\n"
        "environmental and health impacts. View trends over time\n"
        "through line charts and access additional details on health\n"
        "risks and safety levels with rollover pop-ups. Colour-coded\n"
        "indicators show compliance with UK/EU safety standards.");

    // animation
    QLabel* gifLabel = new QLabel(this);
    QMovie* gif = new QMovie(QCoreApplication::applicationDirPath() + "/statics/water-pollution-2.gif");
    if (!gif->isValid()) 
    {
        std::cout << "error encountered when loading gif" << std::endl;
    }
    else {
        gif->setScaledSize(QSize(300, 300)); 
        gifLabel->setMovie(gif);
        gifLabel->setAlignment(Qt::AlignCenter);
        gifLabel->setContentsMargins(0, 20, 0, 20);
        gif->start();
    }

    addHorizontalLayout(heroDescription, gifLabel, 20);

    // create filter proxy model
    customProxyModel = new CustomProxyModel(this);
    customProxyModel->setSourceModel(model);
    customProxyModel->setDynamicSortFilter(true);
    // specify pollutants allowed
    customProxyModel->setAllowedPollutants({"PCB Con 028", "PCB Con 101", "PCB Con 118", 
        "PCB Con 153", "PCB Con 180", "PCB 118 DW", "PCB 170 DW"});
    customProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    // add table for testing
    QTableView* table = new QTableView(this);
    table->setModel(customProxyModel);
    table->setMinimumHeight(400);
    QFont tableFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    table->setFont(tableFont);

    addWidget(table);

    // add charts
    chart = new PollutantTrendLineChart({"PCB Con 028", "PCB Con 101", "PCB Con 118", 
        "PCB Con 153", "PCB Con 180", "PCB 118 DW", "PCB 170 DW"}, customProxyModel);
    chart->setTitle("Persistent Organic Pollutant Levels vs. Date");
    chart->setVerticalAxisTitle("PCB Units (ug/L)");
    QChartView* chartView = new QChartView(chart);
    chartView->setMinimumHeight(400);
    addWidget(chartView);
}

void PersistentOrganicPollutantsPage::modelUpdated() {
    // Refreshes the chart
    auto series1 = chart->series().at(0);
    chart->removeSeries(series1);
    chart->addSeries(series1);
    chart->setAxes();
}
