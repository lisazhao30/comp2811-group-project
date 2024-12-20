#include <QCompleter>
#include "pollutant_overview.hpp"
/*
Pollutants: 
Heavy Metals: Examples include Lead (Pb), Mercury (Hg), Cadmium (Cd), and Chromium (Cr).
Nutrients: Examples include Nitrate (NO3-) and Phosphate (PO4³-).
Volatile Organic Compounds (VOCs): Examples like Chloroform or 1,1,2-Trichloroethane.
*/

PollutantOverviewPage::PollutantOverviewPage(WaterSampleTableModel* model, QWidget* parent): Page(model, parent) {
    // header text
    addHeader2Text(tr("Pollutant Insights: Trends, Compliance, and Safety at a Glance"));
    
    // hero description
    QLabel* heroDescription = addSubtitleText(tr("Explore detailed information about water pollutants,\n"
                                               "including trends over time, compliance with safety\n"
                                               "standards, and associated risks. Use the search bar to find\n"
                                               "specific pollutants, view interactive charts, and understand\n"
                                               "safety levels with clear colour-coded indicators. Hover or\n"
                                               "click for more insights into risks and thresholds."));

    // animation
    QLabel* gifLabel = new QLabel(this);
    QMovie* gif = new QMovie(QCoreApplication::applicationDirPath() + "/statics/water-pollution.gif");
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

    // Inline autocomplete on search
    QCompleter* completer = new QCompleter(this);
    completer->setModel(model);
    completer->setCompletionColumn(5);
    completer->setCompletionMode(QCompleter::CompletionMode::InlineCompletion);
    completer->setCompletionRole(Qt::DisplayRole);
    completer->setCaseSensitivity(Qt::CaseInsensitive);

    // pollutant filter
    filterPollutantInput = new QLineEdit();
    filterPollutantInput->setPlaceholderText(tr("Search for pollutant"));
    // add help information
    QHBoxLayout* pollutantIconLayout = createHelpInfoPopup(
        tr("Search by Pollutant:"),
        tr("Filter by pollutant.\n" 
            "Available pollutants are under the column 'determinand.label'.")
    );
    pageLayout->addLayout(pollutantIconLayout);
    connect(filterPollutantInput, SIGNAL(textChanged(const QString&)), this, SLOT(applyFilter(const QString&)));
    addWidget(filterPollutantInput);

    // create filter proxy model
    customProxyModel = new CustomProxyModel(this);
    customProxyModel->setSourceModel(model);
    customProxyModel->setDynamicSortFilter(true);
    // specify pollutants allowed
    customProxyModel->setAllowedPollutants({"Nitrate-N", "Nitrate Filt", "Phosphate", "Orthophospht",
                                            "Pb Filtered", "Lead - as Pb", "Pb BLM Bio", "Chloroform", "123TriClProp", "1,2,3-TCB"});
    customProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    // add table for testing
    QTableView* table = new QTableView(this);
    table->setModel(customProxyModel);
    table->setMinimumHeight(400);
    QFont tableFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    table->setFont(tableFont);

    addWidget(table);

    // add charts
    chart = new PollutantTrendLineChart({"Lead - as Pb", "Nitrate-N", "Nitrate Filt", "Phosphate", "Orthophospht",
                                         "Pb Filtered", "Pb BLM Bio", "Chloroform", "123TriClProp", "1,2,3-TCB"}, customProxyModel);
    chart->setVerticalAxisTitle(tr("Pollutant Unit (mg/L)"));
    chart->setTitle(tr("Pollutant Levels vs. Date"));
    QChartView* chartView = new QChartView(chart);
    chartView->setMinimumHeight(400);
    addWidget(chartView);

    // footer credits
    addFooterCredits();
}

void PollutantOverviewPage::modelUpdated() {
    // Refreshes the chart
    auto series1 = chart->series().at(0);
    chart->removeSeries(series1);
    chart->addSeries(series1);
    chart->setAxes();
}

void PollutantOverviewPage::applyFilter(const QString& text) {
    customProxyModel->setPollutantFilter(text);
}
