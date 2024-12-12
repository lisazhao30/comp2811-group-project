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
