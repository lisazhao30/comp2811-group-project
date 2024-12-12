#include "environmental_litter_indicators.hpp"

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
    QMovie* gif = new QMovie("../statics/water-pollution-3.gif");
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

    filterProxyModel = new QSortFilterProxyModel(this);
    filterProxyModel->setSourceModel(model);
    filterProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    // data table
    QTableView* table = new QTableView(this);
    table->setModel(filterProxyModel);
    QFont tableFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    table->setFont(tableFont);
    addWidget(table);
}

void EnvironmentalLitterIndicatorsPage::applyLocationFilter(const QString& text) {
    filterProxyModel->setFilterKeyColumn(3);  
    filterProxyModel->setFilterFixedString(text);
}

void EnvironmentalLitterIndicatorsPage::applyWaterBodyTypeFilter(const QString& text) {
    filterProxyModel->setFilterKeyColumn(11);
    filterProxyModel->setFilterFixedString(text);
}
