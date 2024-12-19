#include "environmental_litter_indicators.hpp"
/*
Pollutants include: Bathers 100m, BWP - Ma, BWP - A.F., BWP - O.L., Sld Sus@105C, BOD ATU, TarryResidus
*/

EnvironmentalLitterIndicatorsPage::EnvironmentalLitterIndicatorsPage(WaterSampleTableModel* model, QWidget* parent): Page(model, parent) {
    addHeader2Text(tr("Environmental Litter Indicators:\nTracking Trends, Risks, and Compliance"));

    // hero description
    QLabel* heroDescription = addSubtitleText(tr("The Environmental Litter Indicators Page provides an\n"
                                               "overview of visible pollutants like plastic litter in water.\n"
                                               "Compare litter levels across locations and water body types\n"
                                               "using the charts, and check compliance with EU Bathing\n"
                                               "Water standards. Interactive filters allow you to explore\n"
                                               "trends by location or litter type for deeper insights."));

    // animation
    QLabel* gifLabel = new QLabel(this);
    QMovie* gif = new QMovie(QCoreApplication::applicationDirPath() + "/statics/water-pollution-3.gif");
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

    // location filter
    filterLocationInput = new QLineEdit();
    filterLocationInput->setPlaceholderText(tr("Search for location"));
    QHBoxLayout* locationIconLayout = createHelpInfoPopup(
        tr("Search by Location:"),
        tr("Enter a location to filter the data by geographic area.\n" 
            "Available locations are under the column 'sample.samplingPoint.label'.")
    );
    pageLayout->addLayout(locationIconLayout);
    connect(filterLocationInput, SIGNAL(textChanged(const QString&)), this, SLOT(applyLocationFilter(const QString&)));
    addWidget(filterLocationInput);

    filterWaterBodyTypeInput = new QLineEdit();
    filterWaterBodyTypeInput->setPlaceholderText(tr("Search for water body type"));
    // water body type filter
    QHBoxLayout* waterBodyTypeIconLayout = createHelpInfoPopup(
        tr("Search by Water Body Type:"),
        tr("Filter the data by water body types.\n" 
            "Available water bodies are under the column 'sample.sampledMaterialType.label'.")
    );
    pageLayout->addLayout(waterBodyTypeIconLayout);
    connect(filterWaterBodyTypeInput, SIGNAL(textChanged(const QString&)), this, SLOT(applyWaterBodyTypeFilter(const QString&)));
    addWidget(filterWaterBodyTypeInput);

    // create filter proxy model
    customProxyModel = new CustomProxyModel(this);
    customProxyModel->setSourceModel(model);
    customProxyModel->setDynamicSortFilter(true);
    // specify pollutants allowed
    customProxyModel->setAllowedPollutants({"Bathers 100m", "BWP - Ma", "BWP - A.F.", 
                                            "BWP - O.L.", "Sld Sus@105C", "BOD ATU", "TarryResidus"});
    customProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    // add table for testing
    QTableView* table = new QTableView(this);
    table->setModel(customProxyModel);
    table->setMinimumHeight(400);
    QFont tableFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    table->setFont(tableFont);

    addWidget(table);

    // add charts
    chart = new PollutantTrendLineChart({"Bathers 100m", "BWP - Ma", "BWP - A.F.", 
                                         "BWP - O.L.", "Sld Sus@105C", "BOD ATU", "TarryResidus"}, customProxyModel);
    chart->setVerticalAxisTitle(tr("Pollutant Unit (garber c)"));
    chart->setTitle(tr("Environmental Litter Levels vs. Date"));
    QChartView* chartView = new QChartView(chart);
    chartView->setMinimumHeight(400);
    addWidget(chartView);

    // footer credits
    addFooterCredits();
}

void EnvironmentalLitterIndicatorsPage::applyLocationFilter(const QString& text) {
    customProxyModel->setLocationFilter(text);
}

void EnvironmentalLitterIndicatorsPage::applyWaterBodyTypeFilter(const QString& text) {
    customProxyModel->setWaterBodyFilter(text);
}

void EnvironmentalLitterIndicatorsPage::modelUpdated() {
    // Refreshes the chart
    auto series1 = chart->series().at(0);
    chart->removeSeries(series1);
    chart->addSeries(series1);
    chart->setAxes();
}
