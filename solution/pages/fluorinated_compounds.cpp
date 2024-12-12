#include "fluorinated_compounds.hpp"

FluorinatedCompoundsPage::FluorinatedCompoundsPage(WaterSampleTableModel* model, QWidget* parent): Page(model, parent) {
    addHeader2Text("Fluorinated Compounds:\nMonitoring PFAS Levels and Environmental Impact");

    // hero description
    QLabel* heroDescription = addParagraphText("View data on PFAS and other fluorinated pollutants, and\n"
        "learn about their distribution and persistence in the\n"
        "environment. View maps or time-series charts with colour-\n"
        "coded markers to track levels and assess compliance with\n"
        "safety thresholds. Rollover pop-ups offer additional\n"
        "information on the environmental and health impacts of\n"
        "these compounds.");

    // animation
    QLabel* gifLabel = new QLabel(this);
    QMovie* gif = new QMovie("../statics/water-pollution-4.gif");
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
}
