#include "pollutant_overview.hpp"

PollutantOverviewPage::PollutantOverviewPage(WaterSampleTableModel* model, QWidget* parent): Page(model, parent) {
    addHeader2Text("Pollutant Insights: Trends, Compliance, and Safety at a Glance");
}
