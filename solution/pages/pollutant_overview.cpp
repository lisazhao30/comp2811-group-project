#include "pollutant_overview.hpp"

PollutantOverviewPage::PollutantOverviewPage(WaterSampleTableModel* model, QWidget* parent): Page(model, parent) {
    // header text
    addHeader2Text("Pollutant Insights: Trends, Compliance, and Safety at a Glance");
    
    // hero description
    QLabel* heroDescription = addParagraphText("Explore detailed information about water pollutants,\n"
        "including trends over time, compliance with safety\n"
        "standards, and associated risks. Use the search bar to find\n"
        "specific pollutants, view interactive charts, and understand\n"
        "safety levels with clear colour-coded indicators. Hover or\n"
        "click for more insights into risks and thresholds.");

    // animation
    QLabel* gifLabel = new QLabel(this);
    QMovie* gif = new QMovie("../statics/water-pollution.gif");
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

    // add search functionality for pollutant
    filterInput = new QLineEdit();
    filterInput->setPlaceholderText("Search for pollutant");
    connect(filterInput, SIGNAL(textChanged(const QString&)), this, SLOT(applyFilter(const QString&)));
    addWidget(filterInput);

    // create filter proxy model
    filterProxyModel = new QSortFilterProxyModel(this);
    filterProxyModel->setSourceModel(model);
    filterProxyModel->setFilterKeyColumn(5); // filter for pollutant label only
    filterProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    // add table
    QTableView* table = new QTableView(this);
    table->setModel(filterProxyModel);

    QFont tableFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    table->setFont(tableFont);

    addWidget(table);
}

void PollutantOverviewPage::applyFilter(const QString& text) {
    filterProxyModel->setFilterFixedString(text);
}