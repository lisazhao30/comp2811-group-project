#include "compliance_dashboard.hpp"

ComplianceDashboardPage::ComplianceDashboardPage(WaterSampleTableModel* model, QWidget* parent): Page(model, parent) {
    addHeader2Text("Compliance Dashboard:\nTracking Safety Standards Across Pollutants");

    // hero description
    QLabel* heroDescription = addParagraphText("The Compliance Dashboard provides an overview of\n"
        "pollutant compliance with safety standards. Use summary\n"
        "cards for quick status checks, apply filters to focus on specific\n"
        "locations or pollutants, and access pop-up details for non-\n"
        "compliant areas to understand trends and potential causes.");

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
}
