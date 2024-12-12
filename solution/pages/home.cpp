#include "home.hpp"

HomePage::HomePage(WaterSampleTableModel* model, QWidget* parent): Page(model, parent) {
    pageLayout->setAlignment(Qt::AlignCenter);
    pageLayout->setContentsMargins(20, 20, 20, 20);
    pageLayout->setSpacing(0);

    // header components
    addHeaderText("Spot the Trends, Shape the Future:\n"
        "Water Quality Insights at Your Fingertips");

    // create horizontal layout for hero description
    QHBoxLayout* horizontalLayout = new QHBoxLayout;
    QVBoxLayout* verticalLayout = new QVBoxLayout;
   
    // add hero description
    QLabel* subHeaderText = addHeader2Text("Welcome to AquaTrack");
    QLabel* paragraphText = addParagraphText("AquaTrack is designed to help you explore\n"
        "water pollutant levels, safety compliance,\n"
        "and geographic trends across the UK and EU.\n"
        "Easily navigate by location and time to gain\n"
        "insights into various environmental factors.");
    
    verticalLayout->addWidget(subHeaderText);
    verticalLayout->addWidget(paragraphText);

    // animation
    QLabel* gifLabel = new QLabel(this);
    QMovie* gif = new QMovie("../statics/europe.gif");
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

    // location filter
    filterLocationInput = new QLineEdit();
    filterLocationInput->setPlaceholderText("Search for location");
    connect(filterLocationInput, SIGNAL(textChanged(const QString&)), this, SLOT(applyLocationFilter(const QString&)));
    addWidget(filterLocationInput);

    // special proxy model to filter for location and date
    customProxyModel = new CustomProxyModel(this);
    customProxyModel->setSourceModel(model);
    customProxyModel->setDynamicSortFilter(true);
    customProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    // date range labels
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
    
    // table view
    QTableView* table = new QTableView(this);
    table->setModel(customProxyModel);
    table->setMinimumHeight(400);
    QFont tableFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    table->setFont(tableFont);

    addWidget(table);

    // add chart and set a min height
    chart = new PollutantTrendLineChart("Nitrate-N", model);
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumHeight(400);
    addWidget(chartView);
}

void HomePage::modelUpdated() {
    auto series = chart->series().at(0);
    // Refreshes the chart, probably shouldn't need this, bug?
    chart->removeSeries(series);
    chart->addSeries(series);
    
    chart->setAxes();
}

void HomePage::applyLocationFilter(const QString& text) {
    std::cout << "applying location filter" << std::endl;
    customProxyModel->setFilterKeyColumn(3);  
    customProxyModel->setFilterRegularExpression(text);
}

void HomePage::dateFilterChanged()
 {
    customProxyModel->setFilterMinimumDate(fromDateEdit->date());
    customProxyModel->setFilterMaximumDate(toDateEdit->date());
 }