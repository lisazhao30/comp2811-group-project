#include "environmental_litter_indicators.hpp"
/*
Pollutants include: Bathers 100m, BWP - Ma, BWP - A.F., BWP - O.L., Sld Sus@105C, BOD ATU, TarryResidus
*/

EnvironmentalLitterIndicatorsPage::EnvironmentalLitterIndicatorsPage(WaterSampleTableModel* model, QWidget* parent): Page(model, parent) {
    addHeader2Text("Environmental Litter Indicators:\nTracking Trends, Risks, and Compliance");

    // hero description
    QLabel* heroDescription = addParagraphText("The Environmental Litter Indicators Page provides an\n"
        "overview of visible pollutants like plastic litter in water.\n"
        "Compare litter levels across locations and water body types\n"
        "using the charts, and check compliance with EU Bathing\n"
        "Water standards. Interactive filters allow you to explore\n"
        "trends by location or litter type for deeper insights.");

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
    filterLocationInput->setPlaceholderText("Search for location");
    connect(filterLocationInput, SIGNAL(textChanged(const QString&)), this, SLOT(applyLocationFilter(const QString&)));
    addWidget(filterLocationInput);

    // water body type filter
    filterWaterBodyTypeInput = new QLineEdit();
    filterWaterBodyTypeInput->setPlaceholderText("Search for water body type");
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
    chart->setVerticalAxisTitle("Pollutant Unit (garber c)");
    chart->setTitle("Environmental Litter Levels vs. Date");
    QChartView* chartView = new QChartView(chart);
    chartView->setMinimumHeight(400);
    addWidget(chartView);
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