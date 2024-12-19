#include "help_page.hpp"

HelpPage::HelpPage(WaterSampleTableModel* model, QWidget* parent): Page(model, parent) {
    addHeader2Text(tr("Help and Resources"));

    // footer credits
    addFooterCredits();
}