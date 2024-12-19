#include "help_page.hpp"

HelpPage::HelpPage(WaterSampleTableModel* model, QWidget* parent): Page(model, parent) {
    addHeader2Text(tr("Help and Resources"));

    addSubtitleText(tr("User Guides"));
    addParagraphText(tr("https://dwi.gov.uk/drinking-water-standards-and-regulations/"));
    addParagraphText(tr("https://dwi.gov.uk/water-companies/guidance-and-codes-of-practice/"));
    addParagraphText(tr("https://environment.ec.europa.eu/topics/water/drinking-water_en"));
    
    addSubtitleText(tr("Help Resources"));
    addParagraphText(tr("https://www.eureau.org/news/906-eu-bathing-water-report-published"));
    addParagraphText(tr("https://theriverstrust.org/key-issues/water-quality"));

    addSubtitleText(tr("Data Sources"));
    addParagraphText(tr("https://environment.data.gov.uk/water-quality/view/download"));

    // footer credits
    addFooterCredits();
}