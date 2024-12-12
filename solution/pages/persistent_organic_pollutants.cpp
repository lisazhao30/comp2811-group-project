#include "persistent_organic_pollutants.hpp"

PersistentOrganicPollutantsPage::PersistentOrganicPollutantsPage(WaterSampleTableModel* model, QWidget* parent): Page(model, parent) {
    addHeader2Text("Persistent Organic Pollutants:\nTracking Trends, Risks, and Compliance");

    // hero description
    QLabel* heroDescription = addParagraphText("This page displays data on pollutants like PCBs and their\n"
        "environmental and health impacts. View trends over time\n"
        "through line charts and access additional details on health\n"
        "risks and safety levels with rollover pop-ups. Colour-coded\n"
        "indicators show compliance with UK/EU safety standards.");

    // animation
    QLabel* gifLabel = new QLabel(this);
    QMovie* gif = new QMovie("../statics/water-pollution-2.gif");
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
