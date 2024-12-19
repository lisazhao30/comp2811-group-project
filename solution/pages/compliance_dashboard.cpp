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

    QCompleter* completer = new QCompleter(this);
    completer->setModel(model);
    completer->setCompletionColumn(5);
    completer->setCompletionMode(QCompleter::CompletionMode::InlineCompletion);
    completer->setCompletionRole(Qt::DisplayRole);
    completer->setCaseSensitivity(Qt::CaseInsensitive);

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
    customProxyModel->setAllowedPollutants({"Nitrate-N", "Phosphate", "PCB Con 028", "PFODA"});
    customProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    // add table for testing
    QTableView* table = new QTableView(this);
    table->setModel(customProxyModel);
    table->setMinimumHeight(400);
    QFont tableFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    table->setFont(tableFont);

    addWidget(table);

    // nitrates
    QHBoxLayout* nitrateIconLayout = createHelpInfoPopup(
        tr("Nitrate Compliance"),
        tr("See the compliance of Nitrate-N.\n" 
            "Any value above 50.0 mg/L is considered unsafe. Yellow indicators are set to 20.0 mg/L.")
    );
    pageLayout->addLayout(nitrateIconLayout);

    nitrateScatterChart = new PollutantScatterChart("Nitrate-N", customProxyModel, 20.0, 20.0, 50.0, false);
    nitrateScatterChart->setTitle(tr("Compliance of Nitrate-N Overview"));
    nitrateScatterChart->setVerticalAxisTitle(tr("Pollutant Unit (mg/L)"));
    QChartView* nitrateScatterChartView = new QChartView(nitrateScatterChart);
    nitrateScatterChartView->setMinimumHeight(400);
    addWidget(nitrateScatterChartView);

    // phosphates
    QHBoxLayout* phosphateIconLayout = createHelpInfoPopup(
        tr("Phosphate Compliance"),
        tr("See the compliance of phosphates.\n" 
            "Any value below 0.1 mg/L is considered unsafe. Yellow indicators are set to 0.2 mg/L and above.")
    );
    pageLayout->addLayout(phosphateIconLayout);

    phosphateScatterChart = new PollutantScatterChart("Phosphate", customProxyModel, 0.4, 0.2, 0.1, true);
    phosphateScatterChart->setTitle(tr("Compliance of Phosphate Overview"));
    phosphateScatterChart->setVerticalAxisTitle(tr("Pollutant Unit (mg/L)"));
    QChartView* phosphateScatterChartView = new QChartView(phosphateScatterChart);
    phosphateScatterChartView->setMinimumHeight(400);
    addWidget(phosphateScatterChartView);

    // PCBs
    QHBoxLayout* pcbsIconLayout = createHelpInfoPopup(
        tr("PCBs Compliance"),
        tr("See the compliance of PCBs.\n" 
            "Any value above 0.5 µg/L is considered unsafe. Yellow indicators are set to 0.3 µg/L and above.")
    );
    pageLayout->addLayout(pcbsIconLayout);

    pcbsScatterChart = new PollutantScatterChart("PCB Con 028", customProxyModel, 0.0, 0.3, 0.5, false);
    pcbsScatterChart->setTitle(tr("Compliance of PCBs Overview"));
    pcbsScatterChart->setVerticalAxisTitle(tr("Pollutant Unit (µg/L)"));
    QChartView* pcbsScatterChartView = new QChartView(pcbsScatterChart);
    pcbsScatterChartView->setMinimumHeight(400);
    addWidget(pcbsScatterChartView);

    // fluorinated compounds
    QHBoxLayout* fluorinatedIconLayout = createHelpInfoPopup(
        tr("Fluorinated Compounds Compliance"),
        tr("See the compliance of fluorinated compounds.\n" 
            "Any value above 0.1 µg/L is considered unsafe. Yellow indicators are set to 0.5 µg/L and above.")
    );
    pageLayout->addLayout(fluorinatedIconLayout);

    fluorinatedScatterChart = new PollutantScatterChart("PFODA", customProxyModel, 0, 0.05, 0.1, true);
    fluorinatedScatterChart->setTitle(tr("Compliance of Fluorinated Compounds Overview"));
    fluorinatedScatterChart->setVerticalAxisTitle(tr("Pollutant Unit (µg/L)"));
    QChartView* fluorinatedScatterChartView = new QChartView(fluorinatedScatterChart);
    fluorinatedScatterChartView->setMinimumHeight(400);
    addWidget(fluorinatedScatterChartView);

    // footer credits
    addFooterCredits();
}

void ComplianceDashboardPage::modelUpdated() {
    // Refreshes the chart
    auto series1 = nitrateScatterChart->series().at(0);
    nitrateScatterChart->removeSeries(series1);
    nitrateScatterChart->addSeries(series1);
    nitrateScatterChart->setAxes();

    auto series2 = phosphateScatterChart->series().at(0);
    phosphateScatterChart->removeSeries(series1);
    phosphateScatterChart->addSeries(series1);
    phosphateScatterChart->setAxes();

    auto series3 = pcbsScatterChart->series().at(0);
    pcbsScatterChart->removeSeries(series1);
    pcbsScatterChart->addSeries(series1);
    pcbsScatterChart->setAxes();

    auto series4 = fluorinatedScatterChart->series().at(0);
    fluorinatedScatterChart->removeSeries(series1);
    fluorinatedScatterChart->addSeries(series1);
    fluorinatedScatterChart->setAxes();
}

void ComplianceDashboardPage::applyFilter(const QString& text) {
    customProxyModel->setPollutantFilter(text);
}

void ComplianceDashboardPage::applyLocationFilter(const QString& text) {
    customProxyModel->setFilterKeyColumn(3);  
    customProxyModel->setLocationFilter(text);
}
