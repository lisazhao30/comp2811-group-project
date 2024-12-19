#include "home.hpp"

HomePage::HomePage(WaterSampleTableModel* model, QWidget* parent): Page(model, parent) {
    pageLayout->setAlignment(Qt::AlignCenter);
    pageLayout->setContentsMargins(20, 20, 20, 20);
    pageLayout->setSpacing(10);

    // header components
    addHeaderText(tr("Spot the Trends, Shape the Future:\n"
                  "Water Quality Insights at Your Fingertips"));

    // create horizontal layout for hero description
    QHBoxLayout* horizontalLayout = new QHBoxLayout;
    QVBoxLayout* verticalLayout = new QVBoxLayout;

    // add hero description
    QLabel* subHeaderText = addHeader2Text(tr("Welcome to AquaTrack"));
    QLabel* paragraphText = addSubtitleText(tr("AquaTrack is designed to help you explore\n"
                                             "water pollutant levels, safety compliance,\n"
                                             "and geographic trends across the UK and EU.\n"
                                             "Easily navigate by location and time to gain\n"
                                             "insights into various environmental factors."));
    
    verticalLayout->addWidget(subHeaderText);
    verticalLayout->addWidget(paragraphText);

    // animation
    QLabel* gifLabel = new QLabel(this);
    QMovie* gif = new QMovie(QCoreApplication::applicationDirPath() + "/statics/europe.gif");
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

    horizontalLayout->addLayout(verticalLayout);
    horizontalLayout->addWidget(gifLabel);
    horizontalLayout->setContentsMargins(0,40,0,40);

    pageLayout->addLayout(horizontalLayout);

    addHeaderText(tr("Pollutant Overview"));

    // location filter
    filterLocationInput = new QLineEdit();
    filterLocationInput->setPlaceholderText(tr("Search for location"));

    // location help
    QHBoxLayout* locationIconLayout = createHelpInfoPopup(
        tr("Search by Location:"),
        tr("Enter a location to filter the data by geographic area.\n" 
            "Available locations are under the column 'sample.samplingPoint.label'.")
    );
    pageLayout->addLayout(locationIconLayout);

    connect(filterLocationInput, SIGNAL(textChanged(const QString&)), this, SLOT(applyLocationFilter(const QString&)));
    addWidget(filterLocationInput);

    // special proxy model to filter for location and date
    customProxyModel = new CustomProxyModel(this);
    customProxyModel->setSourceModel(model);
    customProxyModel->setDynamicSortFilter(true);
    customProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    // date range filter
    fromDateEdit = new QDateEdit;
    fromDateEdit->setDate(QDate(2024, 01, 01));
    fromLabel = new QLabel(tr("&From:"));
    fromLabel->setStyleSheet("color: black;");
    fromLabel->setBuddy(fromDateEdit);

    toDateEdit = new QDateEdit;
    toDateEdit->setDate(QDate(2024, 12, 31));
    toLabel = new QLabel(tr("&To:"));
    toLabel->setStyleSheet("color: black;");
    toLabel->setBuddy(toDateEdit);

    addWidget(fromLabel);
    addWidget(fromDateEdit);
    addWidget(toLabel);
    addWidget(toDateEdit);

    connect(fromDateEdit, SIGNAL(dateChanged(QDate)),
            this, SLOT(dateFilterChanged()));
    connect(toDateEdit, SIGNAL(dateChanged(QDate)),
            this, SLOT(dateFilterChanged()));
    
    // table view for testing
    QTableView* table = new QTableView(this);
    table->setModel(customProxyModel);
    table->setMinimumHeight(400);
    QFont tableFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    table->setFont(tableFont);

    addWidget(table);

    QGridLayout* grid = new QGridLayout();
    pageLayout->addLayout(grid);

    // add charts and set a min height
    chart1 = new PollutantTrendLineChart("Nitrate-N", customProxyModel);
    chart1->setTitle(tr("Nitrate-N"));
    QChartView* chartView1 = new QChartView(chart1);
    chartView1->setMinimumHeight(400);
    grid->addWidget(chartView1, 0, 0);

    chart2 = new PollutantTrendLineChart("O Diss %sat", customProxyModel);
    chart2->setTitle(tr("Dissolved Oxygen Saturation %"));
    QChartView* chartView2 = new QChartView(chart2);
    chartView2->setMinimumHeight(400);
    grid->addWidget(chartView2, 0, 1);

    chart3 = new PollutantTrendLineChart("pH", customProxyModel);
    chart3->setTitle(tr("pH"));
    QChartView* chartView3 = new QChartView(chart3);
    chartView3->setMinimumHeight(400);
    grid->addWidget(chartView3, 1, 0);

    chart4 = new PollutantTrendLineChart("Temp Water", customProxyModel);
    chart4->setTitle(tr("Water Temperature"));
    QChartView* chartView4 = new QChartView(chart4);
    chartView4->setMinimumHeight(400);
    grid->addWidget(chartView4, 1, 1);

    // footer
    QVBoxLayout* footerVerticalLayout = new QVBoxLayout;
    QLabel* footerHeaderText = addHeader2Text(tr("Learn More"));
    QLabel* footerSubtitleText = addSubtitleText(tr("Check out our help page for user guides, resources, and our data sources."));
    footerHeaderText->setAlignment(Qt::AlignRight);
    footerVerticalLayout->addWidget(footerHeaderText);
    footerVerticalLayout->addWidget(footerSubtitleText);
    footerVerticalLayout->setAlignment(Qt::AlignRight);
    footerVerticalLayout->setSpacing(10);
    pageLayout->addLayout(footerVerticalLayout, 0);

    // footer credits
    addFooterCredits();
}

void HomePage::modelUpdated() {
    // Refreshes the chart
    auto series1 = chart1->series().at(0);
    chart1->removeSeries(series1);
    chart1->addSeries(series1);
    chart1->setAxes();

    auto series2 = chart2->series().at(0);
    chart2->removeSeries(series2);
    chart2->addSeries(series2);
    chart2->setAxes();

    auto series3 = chart3->series().at(0);
    chart3->removeSeries(series3);
    chart3->addSeries(series3);
    chart3->setAxes();

    auto series4 = chart4->series().at(0);
    chart4->removeSeries(series4);
    chart4->addSeries(series4);
    chart4->setAxes();
}

void HomePage::applyLocationFilter(const QString& text) {
    customProxyModel->setFilterKeyColumn(3);  
    customProxyModel->setLocationFilter(text);
}

void HomePage::dateFilterChanged()
{
    customProxyModel->setFilterMinimumDate(fromDateEdit->date());
    customProxyModel->setFilterMaximumDate(toDateEdit->date());

    chart1->setAxes();
    chart2->setAxes();
    chart3->setAxes();
    chart4->setAxes();
}