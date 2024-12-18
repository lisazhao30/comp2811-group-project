#include "fluorinated_compounds.hpp"

/*
Fluorinated compounds refer to substances containing fluorine, typically known for their persistence and bioaccumulative properties. In the dataset, focus on determinands like:
PFAS Compounds: Look for entries with names including "Perfluoro" (e.g., Perfluorohexanesulfonamide, 9-Chlorohexadecafluoro-3-oxanonane-1-sulfonic acid).
These compounds are often regulated due to their long-term environmental impacts and potential risks to health.
*/

FluorinatedCompoundsPage::FluorinatedCompoundsPage(WaterSampleTableModel* model, QWidget* parent): Page(model, parent) {
    addHeader2Text("Fluorinated Compounds:\nMonitoring PFAS Levels and Environmental Impact");

    // hero description
    QLabel* heroDescription = addParagraphText("View data on PFAS and other fluorinated pollutants, and\n"
        "learn about their distribution and persistence in the\n"
        "environment. View maps or time-series charts with colour-\n"
        "coded markers to track levels and assess compliance with\n"
        "safety thresholds. Rollover pop-ups offer additional\n"
        "information on the environmental and health impacts of\n"
        "these compounds.");

    // animation
    QLabel* gifLabel = new QLabel(this);
    QMovie* gif = new QMovie(QCoreApplication::applicationDirPath() + "/statics/water-pollution-4.gif");
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

    // add table
    // create filter proxy model
    customFluorinatedProxyModel = new CustomProxyModel(this);
    customFluorinatedProxyModel->setSourceModel(model);
    customFluorinatedProxyModel->setDynamicSortFilter(true);
    // specify pollutants allowed
    customFluorinatedProxyModel->setAllowedPollutants({"PFOS", "PFOS (B)", "PFHxS-L", "PFMOPrA",
    "PFNS", "PFHxS-L","PFHpS"});
    customFluorinatedProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    // add table for testing
    QTableView* table = new QTableView(this);
    table->setModel(customFluorinatedProxyModel);
    table->setMinimumHeight(400);
    QFont tableFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    table->setFont(tableFont);

    addWidget(table);

    // add charts
    chart = new PollutantTrendLineChart({"PFOS", "PFOS (B)", "PFHxS-L", "PFMOPrA",
    "PFNS", "PFHxS-L","PFHpS"}, customFluorinatedProxyModel);
    chart->setTitle("Fluorinated Compounds vs. Date");
    chart->setVerticalAxisTitle("Fluorinated Compound Unit (ug/L)");
    QChartView* chartView = new QChartView(chart);
    chartView->setMinimumHeight(400);
    addWidget(chartView);
}

void FluorinatedCompoundsPage::modelUpdated() {
    // Refreshes the chart
    auto series1 = chart->series().at(0);
    chart->removeSeries(series1);
    chart->addSeries(series1);
    chart->setAxes();
}
