#include "compliance_dashboard.hpp"

ComplianceDashboardPage::ComplianceDashboardPage(WaterSampleTableModel* model, QWidget* parent): Page(model, parent) {
    addHeader2Text("Compliance Dashboard:\nTracking Safety Standards Across Pollutants");
}