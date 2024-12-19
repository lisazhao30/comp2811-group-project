#include <QCompleter>
#include "compliance_dashboard.hpp"

/*
For compliance requirements, focus on thresholds for determinands specified in UK/EU water quality standards. Some examples:
Nitrates: Max of 50 mg/L for drinking water (EU Water Framework Directive).
Phosphates: Typically below 0.1 mg/L in surface waters to prevent eutrophication.
PCBs: Maximum of 0.5 µg/L in drinking water, stricter limits for environmental water.
Fluorinated Compounds (PFAS): 100 ng/L for individual PFAS in drinking water, 500 ng/L combined.
These standards can be derived from public resources like the UK Drinking Water Inspectorate or EU compliance documents.
*/

ComplianceDashboardPage::ComplianceDashboardPage(WaterSampleTableModel* model, QWidget* parent): Page(model, parent) {
    addHeader2Text(tr("Compliance Dashboard:\nTracking Safety Standards Across Pollutants"));

    // hero description
    QLabel* heroDescription = addSubtitleText(tr("The Compliance Dashboard provides an overview of\n"
                                               "pollutant compliance with safety standards. Use summary\n"
                                               "cards for quick status checks, apply filters to focus on specific\n"
                                               "locations or pollutants, and access pop-up details for non-\n"
                                               "compliant areas to understand trends and potential causes."));

    // animation
    QLabel* gifLabel = new QLabel(this);
    QMovie* gif = new QMovie(QCoreApplication::applicationDirPath() + "/statics/water-pollution-5.gif");
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

    // // Inline autocomplete on search
    // don't know if this can work for multiple columns?
    // QCompleter* completer = new QCompleter(this);
    // completer->setModel(model);
    // completer->setCompletionColumn(5);
    // completer->setCompletionMode(QCompleter::CompletionMode::InlineCompletion);
    // completer->setCompletionRole(Qt::DisplayRole);
    // completer->setCaseSensitivity(Qt::CaseInsensitive);

    // pollutant filter
    QHBoxLayout* pollutantIconLayout = createHelpInfoPopup(
        tr("Search by Pollutant:"),
        tr("Filter by pollutant.\n" 
            "Available pollutants are under the column 'determinand.label'.")
    );
    pageLayout->addLayout(pollutantIconLayout);
    filterPollutantInput = new QLineEdit();
    filterPollutantInput->setPlaceholderText(tr("Search for pollutant"));
    connect(filterPollutantInput, SIGNAL(textChanged(const QString&)), this, SLOT(applyFilter(const QString&)));
    addWidget(filterPollutantInput);

    // location filter
    QHBoxLayout* locationIconLayout = createHelpInfoPopup(
        tr("Search by Location:"),
        tr("Enter a location to filter the data by geographic area.\n" 
            "Available locations are under the column 'sample.samplingPoint.label'.")
    );
    pageLayout->addLayout(locationIconLayout);
    filterLocationInput = new QLineEdit();
    filterLocationInput->setPlaceholderText(tr("Search for location"));
    connect(filterLocationInput, SIGNAL(textChanged(const QString&)), this, SLOT(applyLocationFilter(const QString&)));
    addWidget(filterLocationInput);

    // create filter proxy model
    customProxyModel = new CustomProxyModel(this);
    customProxyModel->setSourceModel(model);
    customProxyModel->setDynamicSortFilter(true);
    // specify pollutants allowed
    customProxyModel->setAllowedPollutants({"Nitrate-N"});
    customProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    // add table for testing
    QTableView* table = new QTableView(this);
    table->setModel(customProxyModel);
    table->setMinimumHeight(400);
    QFont tableFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    table->setFont(tableFont);

    addWidget(table);

    // chart isn't refreshing???
    scatterChart = new PollutantScatterChart("Nitrate-N", customProxyModel);
    scatterChart->setTitle(tr("Compliance Overview"));
    QChartView* scatterChartView = new QChartView(scatterChart);
    scatterChartView->setMinimumHeight(400);
    addWidget(scatterChartView);

    // footer credits
    addFooterCredits();
}

void ComplianceDashboardPage::modelUpdated() {
    // Refreshes the chart
    auto series1 = scatterChart->series().at(0);
    scatterChart->removeSeries(series1);
    scatterChart->addSeries(series1);
    scatterChart->setAxes();
}

void ComplianceDashboardPage::applyFilter(const QString& text) {
    customProxyModel->setPollutantFilter(text);
}

void ComplianceDashboardPage::applyLocationFilter(const QString& text) {
    customProxyModel->setFilterKeyColumn(3);  
    customProxyModel->setLocationFilter(text);
}
